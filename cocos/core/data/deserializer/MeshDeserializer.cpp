/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/
#include "core/data/deserializer/MeshDeserializer.h"
#include "3d/assets/Mesh.h"
#include "base/Log.h"

namespace cc {

namespace {

//TODO: Copied from EffectAssetDeserializer.cpp, need to make it as common functions
template <typename T>
using DeserializeArrayElementCallback = std::function<void(const rapidjson::Value &, T &)>;

template <typename T>
void deserializeArray(const rapidjson::Value &valArray, std::vector<T> &cValArray, const DeserializeArrayElementCallback<T> &deserializeArrayElement) {
    CC_ASSERT(valArray.IsArray());
    index_t i = 0;
    cValArray.resize(valArray.Size());
    for (const auto &val : valArray.GetArray()) {
        deserializeArrayElement(val, cValArray[i]);
        ++i;
    }
}

void deserializeArray(const rapidjson::Value &valArray, std::vector<std::string> &cValArray) {
    deserializeArray<std::string>(valArray, cValArray, [](const rapidjson::Value &val, std::string &cVal) {
        cVal = val.GetString();
    });
}

void deserializeArray(const rapidjson::Value &valArray, std::vector<bool> &cValArray) {
    CC_ASSERT(valArray.IsArray());
    index_t i = 0;
    cValArray.resize(valArray.Size());
    // note: candidate function not viable: no known conversion from 'std::__1::vector<bool>::reference' (aka '__bit_reference<std::__1::vector<bool>>') to 'bool &' for 2nd argument

    for (const auto &val : valArray.GetArray()) {
        cValArray[i] = val.GetBool();
        ++i;
    }
}

template <typename T, typename Enabled = std::enable_if_t<!std::is_same_v<std::string, T> && !std::is_same_v<bool, T>, T>>
void deserializeArray(const rapidjson::Value &valArray, std::vector<T> &cValArray) {
    DeserializeArrayElementCallback<T> cb{[](const rapidjson::Value &val, T &cVal) {
        cVal = val.Get<T>();
    }};
    deserializeArray<T>(valArray, cValArray, cb);
}
//

void deserializeBufferView(const rapidjson::Value &bufferView, Mesh::IBufferView &cBufferView) {
    if (bufferView.HasMember("offset")) {
        cBufferView.offset = bufferView["offset"].GetUint();
    }

    if (bufferView.HasMember("length")) {
        cBufferView.length = bufferView["length"].GetUint();
    }

    if (bufferView.HasMember("count")) {
        cBufferView.count = bufferView["count"].GetUint();
    }

    if (bufferView.HasMember("stride")) {
        cBufferView.stride = bufferView["stride"].GetUint();
    }
}

/*
 "morph": {
   "subMeshMorphs": [
     {
       "attributes": [
         "a_position",
         "a_tangent"
       ],
       "targets": [
         {
           "displacements": [
             {
               "offset": 1032,
               "length": 288,
               "stride": 4,
               "count": 72
             },
             {
               "offset": 1320,
               "length": 288,
               "stride": 4,
               "count": 72
             }
           ]
         },
         {
           "displacements": [
             {
               "offset": 1608,
               "length": 288,
               "stride": 4,
               "count": 72
             },
             {
               "offset": 1896,
               "length": 288,
               "stride": 4,
               "count": 72
             }
           ]
         }
       ]
     }
   ],
   "weights": [
     0,
     0
   ]
 }
 */

void deserializeSubMeshMorphTarget(const rapidjson::Value &morphTarget, MorphTarget &cMorphTarget) {
    if (morphTarget.HasMember("displacements")) {
        deserializeArray<IMeshBufferView>(morphTarget["displacements"], cMorphTarget.displacements, deserializeBufferView);
    }
}

void deserializeSubMeshMorph(const rapidjson::Value &subMeshMorph, SubMeshMorph &cSubMeshMorph) {
    if (subMeshMorph.HasMember("attributes")) {
        deserializeArray(subMeshMorph["attributes"], cSubMeshMorph.attributes);
    }

    if (subMeshMorph.HasMember("targets")) {
        deserializeArray<MorphTarget>(subMeshMorph["targets"], cSubMeshMorph.targets, deserializeSubMeshMorphTarget);
    }

    if (subMeshMorph.HasMember("weights")) {
        cSubMeshMorph.weights = MeshWeightsType{};
        deserializeArray(subMeshMorph["weights"], cSubMeshMorph.weights.value());
    }
}

void deserializeMorph(const rapidjson::Value &morph, std::optional<Morph> &cMorph) {
    cMorph            = Morph{};
    auto &cMorphValue = cMorph.value();
    if (morph.HasMember("subMeshMorphs")) {
        //TODO:minggo
//        deserializeArray<SubMeshMorph>(morph["subMeshMorphs"], cMorphValue.subMeshMorphs, deserializeSubMeshMorph);
    }

    if (morph.HasMember("weights")) {
        cMorphValue.weights = MeshWeightsType(morph["weights"].Size());
        deserializeArray(morph["weights"], cMorphValue.weights.value());
    }

    if (morph.HasMember("targetNames")) {
        cMorphValue.targetNames = std::vector<std::string>(morph["targetNames"].Size());
        deserializeArray(morph["targetNames"], cMorphValue.targetNames.value());
    }
}

/*
 "jointMaps": [
   [
     0,
     1,
     2,
     3,
     4,
     5,
     6,
     7,
     8,
     9,
     10,
     11,
     12,
     13,
     14,
     15,
     16,
     17,
     18,
     19,
     20
   ]
 ]
 */
void deserializeJointMaps(const rapidjson::Value &jointMaps, std::optional<std::vector<std::vector<index_t>>> &cJointMaps) {
    cJointMaps = std::vector<std::vector<index_t>>{};
    deserializeArray<std::vector<index_t>>(jointMaps, cJointMaps.value(), [](const rapidjson::Value &jointMap, std::vector<index_t> &cJointMap) {
        deserializeArray<index_t>(jointMap, cJointMap, [](const rapidjson::Value &jointIndex, index_t &cJointIndex) {
            cJointIndex = jointIndex.GetInt();
        });
    });
}

/*
 "minPosition": {
   "__type__": "cc.Vec3",
   "x": -0.010000004433095455,
   "y": -0.01000000536441803,
   "z": -0.009999999776482582
 },
 "maxPosition": {
   "__type__": "cc.Vec3",
   "x": 0.01000000350177288,
   "y": 0.01000000350177288,
   "z": 0.009999999776482582
 },
 */
void deserializePosition(const rapidjson::Value &position, std::optional<Vec3> &cPosition) {
    cPosition = Vec3{};
    if (position.HasMember("x")) {
        cPosition.value().x = position["x"].GetFloat();
    }

    if (position.HasMember("y")) {
        cPosition.value().y = position["y"].GetFloat();
    }

    if (position.HasMember("z")) {
        cPosition.value().z = position["z"].GetFloat();
    }
}

/*
 "vertexBundles": [
   {
     "view": {
       "offset": 0,
       "length": 960,
       "count": 24,
       "stride": 40
     },
     "attributes": [
       {
         "name": "a_position",
         "format": 32,
         "isNormalized": false
       },
       {
         "name": "a_normal",
         "format": 32,
         "isNormalized": false
       },
       {
         "name": "a_tangent",
         "format": 44,
         "isNormalized": false
       }
     ]
   }
 ],
 */

void deserializeVertexAttribute(const rapidjson::Value &attribute, gfx::Attribute &cAttribute) {
    if (attribute.HasMember("name")) {
        cAttribute.name = attribute["name"].GetString();
    }

    if (attribute.HasMember("format")) {
        cAttribute.format = static_cast<gfx::Format>(attribute["format"].GetInt());
    }

    if (attribute.HasMember("isNormalized")) {
        cAttribute.isNormalized = attribute["isNormalized"].GetBool();
    }

    if (attribute.HasMember("stream")) {
        cAttribute.stream = attribute["stream"].GetUint();
    }

    if (attribute.HasMember("isInstanced")) {
        cAttribute.isInstanced = attribute["isInstanced"].GetBool();
    }

    if (attribute.HasMember("location")) {
        cAttribute.location = attribute["location"].GetUint();
    }
}

void deserializeVertexBundle(const rapidjson::Value &vertexBundle, Mesh::IVertexBundle &cVertexBundle) {
    if (vertexBundle.HasMember("view")) {
        deserializeBufferView(vertexBundle["view"], cVertexBundle.view);
    }

    if (vertexBundle.HasMember("attributes")) {
        deserializeArray<gfx::Attribute>(vertexBundle["attributes"], cVertexBundle.attributes, deserializeVertexAttribute);
    }
}

/*
 "primitives": [
   {
     "primitiveMode": 7,
     "vertexBundelIndices": [
       0
     ],
     "indexView": {
       "offset": 960,
       "length": 72,
       "count": 36,
       "stride": 2
     }
   }
 ],
 */

void deserializePrimitive(const rapidjson::Value &primitive, Mesh::ISubMesh &cPrimitive) {
    if (primitive.HasMember("primitiveMode")) {
        cPrimitive.primitiveMode = static_cast<gfx::PrimitiveMode>(primitive["primitiveMode"].GetInt());
    }

    if (primitive.HasMember("vertexBundelIndices")) {
        deserializeArray<uint32_t>(primitive["vertexBundelIndices"], cPrimitive.vertexBundelIndices, [](const rapidjson::Value &vertexBundelIndex, uint32_t &index) {
            index = vertexBundelIndex.GetUint();
        });
    }

    if (primitive.HasMember("indexView")) {
        const auto &indexView = primitive["indexView"];
        cPrimitive.indexView  = Mesh::IBufferView{};
        auto &cIndexView      = cPrimitive.indexView.value();
        deserializeBufferView(indexView, cIndexView);
    }

    if (primitive.HasMember("jointMapIndex")) {
        cPrimitive.jointMapIndex = primitive["jointMapIndex"].GetUint();
    }
}

void deserializeStruct(const rapidjson::Value &structInfo, Mesh::IStruct &cStructInfo) {
    if (structInfo.HasMember("primitives")) {
        deserializeArray<Mesh::ISubMesh>(structInfo["primitives"], cStructInfo.primitives, deserializePrimitive);
    }

    if (structInfo.HasMember("vertexBundles")) {
        deserializeArray<Mesh::IVertexBundle>(structInfo["vertexBundles"], cStructInfo.vertexBundles, deserializeVertexBundle);
    }

    if (structInfo.HasMember("minPosition")) {
        deserializePosition(structInfo["minPosition"], cStructInfo.minPosition);
    }

    if (structInfo.HasMember("maxPosition")) {
        deserializePosition(structInfo["maxPosition"], cStructInfo.maxPosition);
    }

    if (structInfo.HasMember("jointMaps")) {
        deserializeJointMaps(structInfo["jointMaps"], cStructInfo.jointMaps);
    }

    if (structInfo.HasMember("morph")) {
        deserializeMorph(structInfo["morph"], cStructInfo.morph);
    }
}

} // namespace

void MeshDeserializer::deserialize(const rapidjson::Value &serializedData, Asset *asset) {
    Mesh *mesh = static_cast<Mesh *>(asset);

    if (serializedData.HasMember("_struct")) {
        deserializeStruct(serializedData["_struct"], mesh->_struct);
    }

    if (serializedData.HasMember("_hash")) {
        mesh->_hash = serializedData["_hash"].GetInt64();
    }
}

} // namespace cc
