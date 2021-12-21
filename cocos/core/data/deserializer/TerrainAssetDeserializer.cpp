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
#include "core/data/deserializer/TerrainAssetDeserializer.h"
#include "base/Log.h"
#include "core/assets/Texture2D.h"
#include "core/data/deserializer/AssetDeserializerFactory.h"
#include "core/utils/ImageUtils.h"
#include "platform/FileUtils.h"
#include "platform/Image.h"

namespace cc {

namespace {

//TODO(): Copied from EffectAssetDeserializer.cpp, need to make it as common functions
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

Texture2D *createTextureFromUUID(const std::string &texJsonFile) {
    auto *      texture2DExportedFromEditor = new Texture2D();
    std::string texture2DJsonContent        = FileUtils::getInstance()->getStringFromFile(texJsonFile);
    if (texture2DJsonContent.empty()) {
        return nullptr;
    }

    {
        rapidjson::Document texture2DDoc;
        texture2DDoc.Parse(texture2DJsonContent.c_str());
        auto deserializer = AssetDeserializerFactory::createAssetDeserializer(DeserializeAssetType::TEXTURE2D);
        deserializer->deserialize(texture2DDoc, texture2DExportedFromEditor);
    }
    // setImageForMaterial
    auto *image = new Image();
    bool  ret   = image->initWithImageFile(texture2DExportedFromEditor->getMipmapsUuids()[0] + ".jpg"); // TODO(xwx): HACK
    ImageUtils::convert2RGBA(image);                                                                    // TODO(xwx): HACK: image file is RGB8 and Metal do not support
    if (ret) {
        auto *imgAsset = new ImageAsset(); //cjh shared_ptr ?
        imgAsset->setNativeAsset(image);   //cjh HOW TO RELEASE?

        texture2DExportedFromEditor->setImage(imgAsset);
        texture2DExportedFromEditor->onLoaded();
    } else {
        CC_SAFE_DELETE(texture2DExportedFromEditor);
    }
    image->release();
    return texture2DExportedFromEditor; //cjh return shared_ptr
}

/*
 [
   {
     "__type__": "cc.TerrainAsset",
     "_name": "terrain",
     "_objFlags": 0,
     "_native": ".bin",
     "_layerInfos": [
       {
         "__id__": 1
       },
       {
         "__id__": 2
       }
     ]
   },
   {
     "__type__": "cc.TerrainLayerInfo",
     "slot": 0,
     "tileSize": 2,
     "detailMap": {
       "__uuid__": "f347c2bf-7870-43ac-b2e7-3fc168d27ad6@6c48a",
       "__expectedType__": "cc.Texture2D"
     },
     "normalMap": null,
     "roughness": 1,
     "metallic": 0.9800000190734863
   },
   {
     "__type__": "cc.TerrainLayerInfo",
     "slot": 1,
     "tileSize": 1,
     "detailMap": {
       "__uuid__": "52ef29ed-bd92-4e94-ab2f-0ebc91bf3a60@6c48a",
       "__expectedType__": "cc.Texture2D"
     },
     "normalMap": null,
     "roughness": 1,
     "metallic": 0
   }
 ]
 */

} // namespace
//

void TerrainAssetDeserializer::deserializeTerrainAsset(const rapidjson::Value &terrainAsset, TerrainAsset *cTerrainAsset) {
    if (terrainAsset.HasMember("_layerInfos")) {
        const auto &layerInfos = terrainAsset["_layerInfos"];
        CC_ASSERT(layerInfos.IsArray());
        cTerrainAsset->_layerInfos.resize(layerInfos.Size());
    }
}

void TerrainAssetDeserializer::deserializeTexture2D(const rapidjson::Value &mapInfo, Texture2D *&cTexture2D) {
    if (mapInfo.IsNull()) {
        cTexture2D = nullptr;
        return;
    }

    if (mapInfo.HasMember("__uuid__")) {
        if (mapInfo.HasMember("__expectedType__") && mapInfo["__expectedType__"] == "cc.Texture2D") {
            cTexture2D = createTextureFromUUID(std::string(mapInfo["__uuid__"].GetString()) + ".json");
        }
    }
}

void TerrainAssetDeserializer::deserializeTerrainLayerInfo(const rapidjson::Value &terrainLayerInfo, TerrainLayerInfo &cTerrainLayerInfo) {
    if (terrainLayerInfo.HasMember("slot")) {
        cTerrainLayerInfo.slot = terrainLayerInfo["slot"].GetInt();
    }

    if (terrainLayerInfo.HasMember("tileSize")) {
        cTerrainLayerInfo.tileSize = terrainLayerInfo["tileSize"].GetFloat();
    }

    if (terrainLayerInfo.HasMember("detailMap")) {
        deserializeTexture2D(terrainLayerInfo["detailMap"], cTerrainLayerInfo.detailMap);
    }

    if (terrainLayerInfo.HasMember("normalMap")) {
        deserializeTexture2D(terrainLayerInfo["normalMap"], cTerrainLayerInfo.normalMap);
    }

    if (terrainLayerInfo.HasMember("roughness")) {
        cTerrainLayerInfo.roughness = terrainLayerInfo["roughness"].GetFloat();
    }

    if (terrainLayerInfo.HasMember("metallic")) {
        cTerrainLayerInfo.metallic = terrainLayerInfo["metallic"].GetFloat();
    }
}

void TerrainAssetDeserializer::deserialize(const rapidjson::Value &serializedData, Asset *asset) {
    auto *cTerrainAsset = static_cast<TerrainAsset *>(asset);
    CC_ASSERT(serializedData.IsArray());
    int32_t layerInfoID = 0;
    for (const auto &val : serializedData.GetArray()) {
        CC_ASSERT(val.IsObject());
        if (val.HasMember("__type__")) {
            const auto *typeStr = val["__type__"].GetString();
            if (0 == strcmp(typeStr, "cc.TerrainAsset")) {
                deserializeTerrainAsset(val, cTerrainAsset);
            } else if (0 == strcmp(typeStr, "cc.TerrainLayerInfo")) {
                CC_ASSERT(layerInfoID < cTerrainAsset->_layerInfos.size());
                deserializeTerrainLayerInfo(val, cTerrainAsset->_layerInfos[layerInfoID]);
                ++layerInfoID;
            }
        }
    }
}

} // namespace cc
