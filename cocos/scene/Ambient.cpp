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

namespace cc {
namespace scene {

void AmbientInfo::setSkyColor(const Color &val) {
    _skyColor.set(val);
    if (_resource != nullptr) {
        _resource->setSkyColor(_skyColor);
    }
}

void AmbientInfo::setSkyIllum(float val) {
    _skyIllum = val;
    if (_resource != nullptr) {
        _resource->setSkyIllum(_skyIllum);
    }
}

void AmbientInfo::setGroundAlbedo(const Color &val) {
    _groundAlbedo.set(val);
    // only RGB channels are used, alpha channel are intensionally left unchanged here
    if (_resource != nullptr) {
        _resource->setGroundAlbedo(_groundAlbedo);
    }
}

void AmbientInfo::activate(Ambient *resource) {
    _resource = resource;
    _resource->initialize(this);
}

//
void Ambient::initialize(AmbientInfo *info) {
    setSkyColor(info->getSkyColor());
    setGroundAlbedo(info->getGroundAlbedo());
    _skyIllum = info->getSkyIllum();
}

} // namespace scene
} // namespace cc
