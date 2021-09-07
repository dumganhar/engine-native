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

#include "core/assets/ImageAsset.h"

#include "platform/Image.h"

#include "base/Log.h"

namespace cc {

ImageAsset::~ImageAsset() {
    if (_nativeData != nullptr) {
        _nativeData->release();
    }
}

void ImageAsset::setNativeAsset(const std::any &obj) {
    if (obj.has_value()) {
        if (const auto *pData = std::any_cast<Image *>(&obj); pData != nullptr) {
            _nativeData = *pData;
            _nativeData->retain();
        } else if (const auto *pData = std::any_cast<IMemoryImageSource>(&obj); pData != nullptr) {
            _imageSource = *pData;
        } else {
            CC_LOG_WARNING("ImageAsset::setNativeAsset, unknown type!");
        }
    }
}

const uint8_t *ImageAsset::getData() const {
    if (_nativeData != nullptr) {
        return _nativeData->getData();
    }

    if (_imageSource.has_value()) {
        return _imageSource.value()._data->data();
    }
    return nullptr;
}

uint32_t ImageAsset::getWidth() const {
    if (_nativeData != nullptr) {
        return _nativeData->getWidth();
    }

    if (_imageSource.has_value()) {
        return _imageSource.value().width;
    }
    return 0;
}

uint32_t ImageAsset::getHeight() const {
    if (_nativeData != nullptr) {
        return _nativeData->getHeight();
    }

    if (_imageSource.has_value()) {
        return _imageSource.value().height;
    }
    return 0;
}

PixelFormat ImageAsset::getFormat() const {
    if (_nativeData != nullptr) {
        return static_cast<PixelFormat>(_nativeData->getRenderFormat());
    }

    if (_imageSource.has_value()) {
        return _imageSource.value().format;
    }
    return PixelFormat::RGBA8888; //cjh TODO: use RGBA8888 as default value?
}

bool ImageAsset::isCompressed() const {
    if (_nativeData != nullptr) {
        return _nativeData->isCompressed();
    }

    if (_imageSource.has_value()) {
        return _imageSource.value()._compressed;
    }
    return false;
}

std::string ImageAsset::getUrl() const {
    if (_nativeData != nullptr) {
        return _nativeData->getFilePath();
    }
    return "";
}

} // namespace cc
