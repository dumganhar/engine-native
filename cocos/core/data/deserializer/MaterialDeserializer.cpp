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
#include "core/data/deserializer/MaterialDeserializer.h"
#include "base/Log.h"
#include "core/assets/Material.h"

namespace cc {
//TODO(xwx): Copied from EffectAssetDeserializer.cpp, need to make it as common functions
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

//TODO(xwx): Copied from EffectAssetDeserializer.cpp, need to make it as common functions
static MacroRecord jsonToMacroRecord(const rapidjson::Value &embeddedMacrosVal) {
    MacroRecord cEmbeddedMacros;
    for (const auto &macro : embeddedMacrosVal.GetObject()) {
        const auto *name  = macro.name.GetString();
        const auto &value = macro.value;

        // using MacroValue = cc::variant<int32_t, float, bool, std::string>;
        // MacroValue only support one of int32_t, float, bool, std::string
        if (value.IsInt()) {
            cEmbeddedMacros.emplace(name, value.GetInt());
            //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%d", name, value.GetInt());
        } else if (value.IsInt64()) {
            cEmbeddedMacros.emplace(name, static_cast<int32_t>(value.GetInt64())); //cjh TODO: need int64?
                                                                                   //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%ld", name, value.GetInt64());
        } else if (value.IsFloat()) {
            cEmbeddedMacros.emplace(name, value.GetFloat());
            //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%f", name, value.GetFloat());
        } else if (value.IsDouble()) {
            cEmbeddedMacros.emplace(name, static_cast<float>(value.GetDouble())); //cjh TODO: need double?
                                                                                  //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%lf", name, value.GetDouble());
        } else if (value.IsBool()) {
            cEmbeddedMacros.emplace(name, value.GetBool());
            //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%d", name, static_cast<int32_t>(value.GetBool()));
        } else if (value.IsString()) {
            cEmbeddedMacros.emplace(name, value.GetString());
            //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%s", name, value.GetString());
        } else {
            CC_LOG_WARNING("Unknown macro value type: %s", name);
        }
    }

    return cEmbeddedMacros;
}

//TODO(xwx): Copied from EffectAssetDeserializer.cpp, need to make it as common functions
static RasterizerStateInfo jsonToRasterizerState(const rapidjson::Value &rasterizerStateVal) {
    RasterizerStateInfo rasterizerState;

    CC_ASSERT(rasterizerStateVal.IsObject());

    if (rasterizerStateVal.HasMember("cullMode")) {
        rasterizerState.cullMode = static_cast<gfx::CullMode>(rasterizerStateVal["cullMode"].GetInt());
        //        CC_LOG_DEBUG("cullMode: %d", static_cast<int32_t>(rasterizerState->cullMode));
    }

    if (rasterizerStateVal.HasMember("isDiscard")) {
        rasterizerState.isDiscard = rasterizerStateVal["isDiscard"].GetUint();
    }

    if (rasterizerStateVal.HasMember("polygonMode")) {
        rasterizerState.polygonMode = static_cast<gfx::PolygonMode>(rasterizerStateVal["polygonMode"].GetInt());
    }

    if (rasterizerStateVal.HasMember("shadeModel")) {
        rasterizerState.shadeModel = static_cast<gfx::ShadeModel>(rasterizerStateVal["shadeModel"].GetInt());
    }

    if (rasterizerStateVal.HasMember("isFrontFaceCCW")) {
        rasterizerState.isFrontFaceCCW = rasterizerStateVal["isFrontFaceCCW"].GetUint();
    }

    if (rasterizerStateVal.HasMember("depthBiasEnabled")) {
        rasterizerState.depthBiasEnabled = rasterizerStateVal["depthBiasEnabled"].GetUint();
    }

    if (rasterizerStateVal.HasMember("depthBias")) {
        rasterizerState.depthBias = rasterizerStateVal["depthBias"].GetFloat();
    }

    if (rasterizerStateVal.HasMember("depthBiasClamp")) {
        rasterizerState.depthBiasClamp = rasterizerStateVal["depthBiasClamp"].GetFloat();
    }

    if (rasterizerStateVal.HasMember("depthBiasSlop")) {
        rasterizerState.depthBiasSlop = rasterizerStateVal["depthBiasSlop"].GetFloat();
    }

    if (rasterizerStateVal.HasMember("isDepthClip")) {
        rasterizerState.isDepthClip = rasterizerStateVal["isDepthClip"].GetUint();
    }

    if (rasterizerStateVal.HasMember("isMultisample")) {
        rasterizerState.isMultisample = rasterizerStateVal["isMultisample"].GetUint();
    }

    if (rasterizerStateVal.HasMember("lineWidth")) {
        rasterizerState.lineWidth = rasterizerStateVal["lineWidth"].GetFloat();
    }

    return rasterizerState;
}

//TODO(xwx): Copied from EffectAssetDeserializer.cpp, need to make it as common functions
static DepthStencilStateInfo jsonToDepthStencilState(const rapidjson::Value &val) {
    DepthStencilStateInfo dss;

    CC_ASSERT(val.IsObject());

    if (val.HasMember("depthTest")) {
        dss.depthTest = val["depthTest"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("depthWrite")) {
        dss.depthWrite = val["depthWrite"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("depthFunc")) {
        dss.depthFunc = static_cast<gfx::ComparisonFunc>(val["depthFunc"].GetInt());
    }

    if (val.HasMember("stencilTestFront")) {
        dss.stencilTestFront = val["stencilTestFront"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("stencilFuncFront")) {
        dss.stencilFuncFront = static_cast<gfx::ComparisonFunc>(val["stencilFuncFront"].GetInt());
    }

    if (val.HasMember("stencilReadMaskFront")) {
        dss.stencilReadMaskFront = val["stencilReadMaskFront"].GetUint();
    }

    if (val.HasMember("stencilWriteMaskFront")) {
        dss.stencilWriteMaskFront = val["stencilWriteMaskFront"].GetUint();
    }

    if (val.HasMember("stencilFailOpFront")) {
        dss.stencilFailOpFront = static_cast<gfx::StencilOp>(val["stencilFailOpFront"].GetUint());
    }

    if (val.HasMember("stencilZFailOpFront")) {
        dss.stencilZFailOpFront = static_cast<gfx::StencilOp>(val["stencilZFailOpFront"].GetUint());
    }

    if (val.HasMember("stencilPassOpFront")) {
        dss.stencilPassOpFront = static_cast<gfx::StencilOp>(val["stencilPassOpFront"].GetUint());
    }

    if (val.HasMember("stencilRefFront")) {
        dss.stencilRefFront = val["stencilRefFront"].GetUint();
    }

    if (val.HasMember("stencilTestBack")) {
        dss.stencilTestBack = val["stencilTestBack"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("stencilFuncBack")) {
        dss.stencilFuncBack = static_cast<gfx::ComparisonFunc>(val["stencilFuncBack"].GetInt());
    }

    if (val.HasMember("stencilReadMaskBack")) {
        dss.stencilReadMaskBack = val["stencilReadMaskBack"].GetUint();
    }

    if (val.HasMember("stencilWriteMaskBack")) {
        dss.stencilWriteMaskBack = val["stencilWriteMaskBack"].GetUint();
    }

    if (val.HasMember("stencilFailOpBack")) {
        dss.stencilFailOpBack = static_cast<gfx::StencilOp>(val["stencilFailOpBack"].GetInt());
    }

    if (val.HasMember("stencilZFailOpBack")) {
        dss.stencilZFailOpBack = static_cast<gfx::StencilOp>(val["stencilZFailOpBack"].GetInt());
    }

    if (val.HasMember("stencilPassOpBack")) {
        dss.stencilPassOpBack = static_cast<gfx::StencilOp>(val["stencilPassOpBack"].GetInt());
    }

    if (val.HasMember("stencilRefBack")) {
        dss.stencilWriteMaskBack = val["stencilRefBack"].GetUint();
    }

    return dss;
}

//TODO(xwx): Copied from EffectAssetDeserializer.cpp, need to make it as common functions
static void jsonToBlendTarget(const rapidjson::Value &val, BlendTargetInfo *outBlendTarget) {
    if (outBlendTarget == nullptr) {
        return;
    }

    CC_ASSERT(val.IsObject());

    if (val.HasMember("blend")) {
        outBlendTarget->blend = val["blend"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("blendSrc")) {
        outBlendTarget->blendSrc = static_cast<gfx::BlendFactor>(val["blendSrc"].GetInt());
    }

    if (val.HasMember("blendDst")) {
        outBlendTarget->blendDst = static_cast<gfx::BlendFactor>(val["blendDst"].GetInt());
    }

    if (val.HasMember("blendEq")) {
        outBlendTarget->blendEq = static_cast<gfx::BlendOp>(val["blendEq"].GetInt());
    }

    if (val.HasMember("blendSrcAlpha")) {
        outBlendTarget->blendSrcAlpha = static_cast<gfx::BlendFactor>(val["blendSrcAlpha"].GetInt());
    }

    if (val.HasMember("blendDstAlpha")) {
        outBlendTarget->blendDstAlpha = static_cast<gfx::BlendFactor>(val["blendDstAlpha"].GetInt());
    }

    if (val.HasMember("blendAlphaEq")) {
        outBlendTarget->blendAlphaEq = static_cast<gfx::BlendOp>(val["blendAlphaEq"].GetInt());
    }

    if (val.HasMember("blendColorMask")) {
        outBlendTarget->blendColorMask = static_cast<gfx::ColorMask>(val["blendColorMask"].GetInt());
    }
}

static void deserializeGfxColor(const rapidjson::Value &color, cc::optional<gfx::Color> &gfxColor) {
    if (gfxColor.has_value()) {
        if (color.HasMember("x")) {
            gfxColor->x = color["x"].GetFloat();
        }

        if (color.HasMember("y")) {
            gfxColor->y = color["y"].GetFloat();
        }

        if (color.HasMember("z")) {
            gfxColor->z = color["z"].GetFloat();
        }

        if (color.HasMember("w")) {
            gfxColor->w = color["w"].GetFloat();
        }
    }
}

//TODO(xwx): Copied from EffectAssetDeserializer.cpp, need to make it as common functions
static BlendStateInfo jsonToBlendState(const rapidjson::Value &val) {
    CC_ASSERT(val.IsObject());

    BlendStateInfo bs;

    if (val.HasMember("isA2C")) {
        bs.isA2C = val["isA2C"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("isIndepend")) {
        bs.isIndepend = val["isIndepend"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("blendColor")) {
        deserializeGfxColor(val["blendColor"], bs.blendColor);
    }

    if (val.HasMember("targets")) {
        if (val["targets"].IsArray()) {
            const auto &        targetsVal = val["targets"].GetArray();
            BlendTargetInfoList targets;
            targets.resize(targetsVal.Size());
            int32_t i = 0;
            for (const auto &targetVal : targetsVal) {
                jsonToBlendTarget(targetVal, &targets[i]);
                ++i;
            }
            bs.targets = targets;
        }
    }

    return bs;
}

static PassOverrides jsonToPassOverrides(const rapidjson::Value &stateVal) {
    PassOverrides passOverrides;

    if (stateVal.HasMember("rasterizerState")) {
        passOverrides.rasterizerState = jsonToRasterizerState(stateVal["rasterizerState"]);
    }
    if (stateVal.HasMember("blendState")) {
        passOverrides.blendState = jsonToBlendState(stateVal["blendState"]);
    }
    if (stateVal.HasMember("depthStencilState")) {
        passOverrides.depthStencilState = jsonToDepthStencilState(stateVal["depthStencilState"]);
    }
    return passOverrides;
}

static void deserializeDefine(const rapidjson::Value &defineVal, MacroRecord &cMarcoRecord) {
    cMarcoRecord = jsonToMacroRecord(defineVal);
}

static void deserializeState(const rapidjson::Value &stateVal, PassOverrides &cPassOverrides) {
    cPassOverrides = jsonToPassOverrides(stateVal);
}

static Vec2 jsonToVec2(const rapidjson::Value &position) {
    Vec2 ret;
    if (position.HasMember("x")) {
        ret.x = position["x"].GetFloat();
    }

    if (position.HasMember("y")) {
        ret.y = position["y"].GetFloat();
    }

    return ret;
}

static Vec3 jsonToVec3(const rapidjson::Value &position) {
    Vec3 ret;
    if (position.HasMember("x")) {
        ret.x = position["x"].GetFloat();
    }

    if (position.HasMember("y")) {
        ret.y = position["y"].GetFloat();
    }

    if (position.HasMember("z")) {
        ret.z = position["z"].GetFloat();
    }
    return ret;
}

static Vec4 jsonToVec4(const rapidjson::Value &position) {
    Vec4 ret;
    if (position.HasMember("x")) {
        ret.x = position["x"].GetFloat();
    }

    if (position.HasMember("y")) {
        ret.y = position["y"].GetFloat();
    }

    if (position.HasMember("z")) {
        ret.z = position["z"].GetFloat();
    }

    if (position.HasMember("w")) {
        ret.z = position["w"].GetFloat();
    }
    return ret;
}

static Color jsonToColor(const rapidjson::Value &color) {
    Color ret;
    if (color.HasMember("r")) {
        ret.r = color["r"].GetUint();
    }

    if (color.HasMember("g")) {
        ret.g = color["g"].GetUint();
    }

    if (color.HasMember("b")) {
        ret.b = color["b"].GetUint();
    }

    if (color.HasMember("a")) {
        ret.a = color["a"].GetUint();
    }
    return ret;
}

static Mat3 jsonToMat3(const rapidjson::Value &mat) {
    Mat3 ret;
    if (mat.HasMember("m00")) {
        ret.m[0] = mat["m00"].GetFloat();
    }
    if (mat.HasMember("m01")) {
        ret.m[1] = mat["m01"].GetFloat();
    }
    if (mat.HasMember("m02")) {
        ret.m[2] = mat["m02"].GetFloat();
    }
    if (mat.HasMember("m03")) {
        ret.m[3] = mat["m03"].GetFloat();
    }
    if (mat.HasMember("m04")) {
        ret.m[4] = mat["m04"].GetFloat();
    }
    if (mat.HasMember("m05")) {
        ret.m[5] = mat["m05"].GetFloat();
    }
    if (mat.HasMember("m06")) {
        ret.m[6] = mat["m06"].GetFloat();
    }
    if (mat.HasMember("m07")) {
        ret.m[7] = mat["m07"].GetFloat();
    }
    if (mat.HasMember("m08")) {
        ret.m[8] = mat["m08"].GetFloat();
    }
    return ret;
}

static Mat4 jsonToMat4(const rapidjson::Value &mat) {
    Mat4 ret;
    if (mat.HasMember("m00")) {
        ret.m[0] = mat["m00"].GetFloat();
    }
    if (mat.HasMember("m01")) {
        ret.m[1] = mat["m01"].GetFloat();
    }
    if (mat.HasMember("m02")) {
        ret.m[2] = mat["m02"].GetFloat();
    }
    if (mat.HasMember("m03")) {
        ret.m[3] = mat["m03"].GetFloat();
    }
    if (mat.HasMember("m04")) {
        ret.m[4] = mat["m04"].GetFloat();
    }
    if (mat.HasMember("m05")) {
        ret.m[5] = mat["m05"].GetFloat();
    }
    if (mat.HasMember("m06")) {
        ret.m[6] = mat["m06"].GetFloat();
    }
    if (mat.HasMember("m07")) {
        ret.m[7] = mat["m07"].GetFloat();
    }
    if (mat.HasMember("m08")) {
        ret.m[8] = mat["m08"].GetFloat();
    }
    if (mat.HasMember("m09")) {
        ret.m[9] = mat["m09"].GetFloat();
    }
    if (mat.HasMember("m10")) {
        ret.m[10] = mat["m10"].GetFloat();
    }
    if (mat.HasMember("m11")) {
        ret.m[11] = mat["m11"].GetFloat();
    }
    if (mat.HasMember("m12")) {
        ret.m[12] = mat["m12"].GetFloat();
    }
    if (mat.HasMember("m13")) {
        ret.m[13] = mat["m13"].GetFloat();
    }
    if (mat.HasMember("m14")) {
        ret.m[14] = mat["m14"].GetFloat();
    }
    if (mat.HasMember("m15")) {
        ret.m[15] = mat["m15"].GetFloat();
    }
    return ret;
}

static Quaternion jsonToQuaternion(const rapidjson::Value &quat) {
    Quaternion ret;
    if (quat.HasMember("x")) {
        ret.x = quat["x"].GetFloat();
    }

    if (quat.HasMember("y")) {
        ret.y = quat["y"].GetFloat();
    }

    if (quat.HasMember("z")) {
        ret.z = quat["z"].GetFloat();
    }

    if (quat.HasMember("w")) {
        ret.z = quat["w"].GetFloat();
    }
    return ret;
}

static MaterialProperty jsonToMaterialProperty(const rapidjson::Value &val) {
    MaterialProperty matProp; //MaterialPropert: float, int32_t, Vec2, Vec3, Vec4, Color, Mat3, Mat4, Quaternion, TextureBase * , gfx::Texture *
    if (val.IsNumber()) {
        matProp = val.GetFloat();
    } else if (val.IsObject()) { // Vec2, Vec3, Vec4, Color, Mat3, Mat4, Quaternion, TextureBase * , gfx::Texture *
        if (val.HasMember("__type__")) {
            std::string type = val["__type__"].GetString();
            // TODO(xwx): use std::move statement below ?
            if (type == "cc.Vec2") {
                matProp = jsonToVec2(val);
            } else if (type == "cc.Vec3") {
                matProp = jsonToVec3(val);
            } else if (type == "cc.Vec4") {
                matProp = jsonToVec4(val);
            } else if (type == "cc.Color") {
                matProp = jsonToColor(val);
            } else if (type == "cc.Mat3") {
                matProp = jsonToMat3(val);
            } else if (type == "cc.Mat4") {
                matProp = jsonToMat4(val);
            } else if (type == "cc.Quat") {
                matProp = jsonToQuaternion(val);
            } else if (type == "cc.Texture2D") {
                // TODO(xwx): should use __type__ or __expectedType__ ?
            } else { // TODO(xwx): which keywork should be gfx::Texture * ?
            }
        }
        if (val.HasMember("__expectedType__")) {
            std::string type = val["__expectedType__"].GetString();
            if (type == "cc.Texture2D") {
                // TODO(xwx): temporary default
            }
        }
    }

    return matProp;
}

static void deserializeMaterialProperty(const rapidjson::Value &val, MaterialProperty &cMaterialProperty) {
    cMaterialProperty = jsonToMaterialProperty(val);
}

static MaterialPropertyVariant jsonToMaterialPropertyVariant(const rapidjson::Value &val) {
    MaterialPropertyVariant matPropVariant; //MaterialPropert, std::vector<MaterialProperty>

    if (val.IsArray()) { // MaterialPropertyList
        deserializeArray<MaterialProperty>(val, cc::get<MaterialPropertyList>(matPropVariant), deserializeMaterialProperty);
    } else { // MaterialProperty
        matPropVariant = jsonToMaterialProperty(val);
    }
    return matPropVariant;
}

static Record<std::string, MaterialPropertyVariant> jsonToPropMap(const rapidjson::Value &propVal) {
    Record<std::string, MaterialPropertyVariant> propMap;

    for (const auto &propertyVal : propVal.GetObject()) {
        const auto *name  = propertyVal.name.GetString();
        const auto &value = propertyVal.value;
        propMap.emplace(name, jsonToMaterialPropertyVariant(value));
    }

    return propMap;
}

static void deserializeProp(const rapidjson::Value &propVal, Record<std::string, MaterialPropertyVariant> &cRecord) {
    cRecord = jsonToPropMap(propVal);
}

void MaterialDeserializer::deserialize(const rapidjson::Value &serializedData, Asset *asset) {
    CC_ASSERT(serializedData.IsObject());
    auto *material = static_cast<Material *>(asset);

    // _effectAsset
    if (serializedData.HasMember("_techIdx")) {
        material->_techIdx = serializedData["_techIdx"].GetUint();
    }

    if (serializedData.HasMember("_defines")) {
        deserializeArray<MacroRecord>(serializedData["_defines"], material->_defines, deserializeDefine);
    }

    if (serializedData.HasMember("_states")) {
        deserializeArray<PassOverrides>(serializedData["_states"], material->_states, deserializeState);
    }

    if (serializedData.HasMember("_props")) {
        deserializeArray<Record<std::string, MaterialPropertyVariant>>(serializedData["_props"], material->_props, deserializeProp);
    }
}

} // namespace cc
