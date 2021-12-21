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
#include "core/data/deserializer/Texture2DDeserializer.h"
#include "base/Log.h"
#include "core/assets/Texture2D.h"

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

static void deserializeMipmapsArray(const rapidjson::Value &val, std::string &mipmapStr) {
    CC_ASSERT(val.IsString());
    mipmapStr = val.GetString();
}

void Texture2DDeserializer::deserialize(const rapidjson::Value &serializedData, Asset *asset) {
    CC_ASSERT(serializedData.IsObject());
    auto *texture2DAsset = static_cast<Texture2D *>(asset);
    if (serializedData.HasMember("content")) {
        if (serializedData["content"].HasMember("base")) {
            TextureBaseDeserializer::deserialize(serializedData["content"], texture2DAsset);
        }
        if (serializedData["content"].HasMember("mipmaps")) {
            deserializeArray<std::string>(serializedData["content"]["mipmaps"], texture2DAsset->_mipmapsUuids, deserializeMipmapsArray);
        }
    }
}

} // namespace cc
