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

#include "scene/Ambient.h"

namespace {
cc::Vec4  v4;
cc::Color col;

// Normalize HDR color
void normalizeHDRColor(cc::Vec4 &color) {
    const float intensity = 1.F / std::max(std::max(std::max(color.x, color.y), color.z), 0.0001F);
    if (intensity < 1.F) {
        color.x *= intensity;
        color.y *= intensity;
        color.z *= intensity;
    }
}

} // namespace
namespace cc {
namespace scene {

void AmbientInfo::setSkyLightingColor(const Color &val) {
    v4.set(static_cast<float>(val.r) / 255.F, static_cast<float>(val.g) / 255.F, static_cast<float>(val.b) / 255.F, static_cast<float>(val.a) / 255.F);
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        _skyColorHDR.set(v4);
    } else {
        _skyColorLDR.set(v4);
    }
    if (_resource != nullptr) {
        _resource->setSkyColor(v4);
    }
}

const Color &AmbientInfo::getSkyLightingColor() const {
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    v4.set(isHDR ? _skyColorHDR : _skyColorLDR);
    normalizeHDRColor(v4);
    col.set(static_cast<uint8_t>(v4.x) * 255, static_cast<uint8_t>(v4.y) * 255, static_cast<uint8_t>(v4.z) * 255, 255);
    return col;
}

void AmbientInfo::setSkyColor(const Vec4 &val) {
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        _skyColorHDR.set(val);
    } else {
        _skyColorLDR.set(val);
    }
    if (_resource != nullptr) {
        _resource->setSkyColor(val);
    }
}

void AmbientInfo::setSkyIllum(float val) {
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        _skyIllumHDR = val;

    } else {
        _skyIllumLDR = val;
    }

    if (_resource != nullptr) {
        _resource->setSkyIllum(val);
    }
}

void AmbientInfo::setGroundLightingColor(const Color &val) {
    v4.set(static_cast<float>(val.r) / 255.F, static_cast<float>(val.g) / 255.F, static_cast<float>(val.b) / 255.F, static_cast<float>(val.a) / 255.F);
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        _groundAlbedoHDR.set(v4);
    } else {
        _groundAlbedoHDR.set(v4);
    }

    if (_resource != nullptr) {
        _resource->setGroundAlbedo(v4);
    }
}

const Color &AmbientInfo::getGroundLightingColor() const {
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    v4.set(isHDR ? _groundAlbedoHDR : _groundAlbedoLDR);
    normalizeHDRColor(v4);
    col.set(static_cast<uint8_t>(v4.x) * 255, static_cast<uint8_t>(v4.y) * 255, static_cast<uint8_t>(v4.z) * 255, 255);
    return col;
}

void AmbientInfo::setGroundAlbedo(const Vec4 &val) {
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        _groundAlbedoHDR.set(val);
    } else {
        _groundAlbedoLDR.set(val);
    }

    if (_resource != nullptr) {
        _resource->setGroundAlbedo(val);
    }
}

void AmbientInfo::activate(Ambient *resource) {
    _resource = resource;
    _resource->initialize(this);
}

//
void Ambient::initialize(AmbientInfo *info) {
    // setSkyColor(info->getSkyColor());
    // setGroundAlbedo(info->getGroundAlbedo());
    // _skyIllum = info->getSkyIllum();

    // Init HDR/LDR from serialized data on load
    _skyColorHDR       = info->getSkyColorHDR();
    _groundAlbedoHDR.x = info->groundAlbedoHDR.x;
    _groundAlbedoHDR.y = info->groundAlbedoHDR.y;
    _groundAlbedoHDR.z = info->groundAlbedoHDR.z;
    _skyIllumHDR       = info->skyIllum;
    _skyColorLDR       = info->skyColorLDR;
    _groundAlbedoLDR.x = info->groundAlbedoLDR.x;
    _groundAlbedoLDR.y = info->groundAlbedoLDR.y;
    _groundAlbedoLDR.z = info->groundAlbedoLDR.z;
    _skyIllumLDR       = info->skyIllumLDR;
}

} // namespace scene
} // namespace cc
