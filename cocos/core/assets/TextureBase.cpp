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

#include "core/assets/TextureBase.h"
#include "base/StringUtil.h"
#include "core/event/EventTypesToJS.h"
#include "core/utils/IDGenerator.h"

#include "renderer/gfx-base/GFXDevice.h"
#include "renderer/pipeline/Define.h"

#include "MurmurHash2/MurmurHash2.h"

namespace cc {

namespace {
IDGenerator idGenerator("Tex");
}

TextureBase::TextureBase() {
    // Id for generate hash in material
    _id          = idGenerator.getNewId();
    _gfxDevice   = getGFXDevice();
    _textureHash = murmurhash2::MurmurHash2(_id.data(), _id.length(), 666); //cjh TODO: How about using boost hash functionality?
    _samplerHash = pipeline::SamplerLib::genSamplerHash(_samplerInfo);
}

void TextureBase::setWrapMode(WrapMode wrapS, WrapMode wrapT, WrapMode wrapR /* = WrapMode::REPEAT*/) {
    _wrapS                = wrapS;
    _samplerInfo.addressU = static_cast<gfx::Address>(wrapS),

    _wrapT                = wrapT;
    _samplerInfo.addressV = static_cast<gfx::Address>(wrapT),

    _wrapR                = wrapR;
    _samplerInfo.addressW = static_cast<gfx::Address>(wrapR);

    _samplerHash = pipeline::SamplerLib::genSamplerHash(_samplerInfo);
    // for editor assetDB
    if (_gfxDevice != nullptr) {
        _gfxSampler = pipeline::SamplerLib::getSampler(_samplerHash);
    }

    notifySamplerUpdated();
}

void TextureBase::setFilters(Filter minFilter, Filter magFilter) {
    _minFilter             = minFilter;
    _samplerInfo.minFilter = static_cast<gfx::Filter>(minFilter);
    _magFilter             = magFilter;
    _samplerInfo.magFilter = static_cast<gfx::Filter>(magFilter);
    _samplerHash           = pipeline::SamplerLib::genSamplerHash(_samplerInfo);
    if (_gfxDevice != nullptr) {
        _gfxSampler = pipeline::SamplerLib::getSampler(_samplerHash);
    }

    notifySamplerUpdated();
}

void TextureBase::setMipFilter(Filter mipFilter) {
    _mipFilter             = mipFilter;
    _samplerInfo.mipFilter = static_cast<gfx::Filter>(mipFilter);
    _samplerHash           = pipeline::SamplerLib::genSamplerHash(_samplerInfo);
    if (_gfxDevice) {
        _gfxSampler = pipeline::SamplerLib::getSampler(_samplerHash);
    }

    notifySamplerUpdated();
}

void TextureBase::setAnisotropy(uint32_t anisotropy) {
    _anisotropy                = anisotropy;
    _samplerInfo.maxAnisotropy = anisotropy;
    _samplerHash               = pipeline::SamplerLib::genSamplerHash(_samplerInfo);
    if (_gfxDevice != nullptr) {
        _gfxSampler = pipeline::SamplerLib::getSampler(_samplerHash);
    }

    notifySamplerUpdated();
}

bool TextureBase::destroy() {
    const bool destroyed = Super::destroy();
    //cjh TODO:    if (destroyed && legacyCC.director.root?.batcher2D) {
    //        legacyCC.director.root.batcher2D._releaseDescriptorSetCache(this._textureHash);
    //    }
    return destroyed;
}

gfx::Sampler *TextureBase::getGFXSampler() const {
    if (_gfxSampler == nullptr) {
        if (_gfxDevice != nullptr) {
            const_cast<TextureBase *>(this)->_gfxSampler = pipeline::SamplerLib::getSampler(_samplerHash);
        } else {
            //cjh            errorID(9302);
        }
    }
    return _gfxSampler.get();
}

std::any TextureBase::serialize(const std::any &ctxForExporting) {
    //cjh TODO:    if (EDITOR || TEST) {
    //        return `${this._minFilter},${this._magFilter},${
    //            this._wrapS},${this._wrapT},${
    //            this._mipFilter},${this._anisotropy}`;
    //    }
    return std::string("");
}

void TextureBase::deserialize(const std::any &serializedData, const std::any &handle) {
    const std::string *pData = std::any_cast<const std::string>(&serializedData);
    if (pData == nullptr) {
        return;
    }
    const std::string &data   = *pData;
    auto               fields = StringUtil::split(data, ",");
    fields.insert(fields.begin(), "");

    if (fields.size() >= 5) {
        // decode filters
        setFilters(static_cast<Filter>(atoi(fields[1].c_str())), static_cast<Filter>(atoi(fields[2].c_str())));
        // decode wraps
        setWrapMode(static_cast<WrapMode>(atoi(fields[3].c_str())), static_cast<WrapMode>(atoi(fields[4].c_str())));
    }

    if (fields.size() >= 7) {
        setMipFilter(static_cast<Filter>(atoi(fields[5].c_str())));
        setAnisotropy(atoi(fields[6].c_str()));
    }
}

gfx::Device *TextureBase::getGFXDevice() const {
    return gfx::Device::getInstance();
}

gfx::Format TextureBase::getGFXFormat() const {
    return getGFXPixelFormat(_format);
}

void TextureBase::setGFXFormat(const cc::optional<PixelFormat> &format) {
    _format = format.has_value() ? format.value() : PixelFormat::RGBA8888;
}

gfx::Format TextureBase::getGFXPixelFormat(PixelFormat format) const {
    if (format == PixelFormat::RGBA_ETC1) {
        format = PixelFormat::RGB_ETC1;
    } else if (format == PixelFormat::RGB_A_PVRTC_4BPPV1) {
        format = PixelFormat::RGB_PVRTC_4BPPV1;
    } else if (format == PixelFormat::RGB_A_PVRTC_2BPPV1) {
        format = PixelFormat::RGB_PVRTC_2BPPV1;
    }
    return static_cast<gfx::Format>(format);
}

bool TextureBase::isCompressed() const {
    return (_format >= PixelFormat::RGB_ETC1 && _format <= PixelFormat::RGBA_ASTC_12x12) || (_format >= PixelFormat::RGB_A_PVRTC_2BPPV1 && _format <= PixelFormat::RGBA_ETC1);
}

void TextureBase::notifySamplerUpdated() {
    emit(EventTypesToJS::TEXTURE_BASE_GFX_SAMPLER_UPDATED, _gfxSampler.get(), _samplerHash);
}

} // namespace cc
