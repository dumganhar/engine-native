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
#include "core/data/deserializer/TextureBaseDeserializer.h"
#include <sstream>
#include <string>
#include "base/Log.h"
#include "core/assets/TextureBase.h"

namespace cc {

static std::vector<uint32_t> splitStrToUint(const std::string &s, char delim) {
    std::vector<uint32_t> result;
    std::stringstream     ss(s);
    std::string           item;

    while (getline(ss, item, delim)) {
        const uint32_t i = stoi(item);
        result.emplace_back(i);
    }

    return result;
}

void TextureBaseDeserializer::deserialize(const rapidjson::Value &serializedData, Asset *asset) {
    CC_ASSERT(serializedData.IsObject());
    auto *textureBaseAsset = static_cast<TextureBase *>(asset);
    CC_ASSERT(textureBaseAsset != nullptr);
    if (serializedData.HasMember("base")) {
        std::string                 baseData = serializedData["base"].GetString();
        const std::vector<uint32_t> fields   = splitStrToUint(baseData, ',');
        if (fields.size() >= 4) {
            // decode filters
            textureBaseAsset->setFilters(static_cast<Filter>(fields[0]), static_cast<Filter>(fields[1]));
            // decode wraps
            textureBaseAsset->setWrapMode(static_cast<WrapMode>(fields[2]), static_cast<WrapMode>(fields[3]));
        }
        if (fields.size() >= 6) {
            textureBaseAsset->setMipFilter(static_cast<Filter>(fields[4]));
            textureBaseAsset->setAnisotropy(fields[5]);
        }
    }
}

} // namespace cc
