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

#include "scene/Fog.h"
#include "core/Root.h"

namespace cc {
namespace scene {

void FogInfo::setEnabled(bool val) const {
    if (_isEnabled == val) {
        return;
    }

    if (_resource != nullptr) {
        _resource->setEnabled(val);
        if (val) {
            _resource->setType(_type);
        }
    }
}

void FogInfo::setFogColor(const Color &val) {
    _fogColor.set(val);
    if (_resource != nullptr) {
        _resource->setFogColor(_fogColor);
    }
}

void FogInfo::setType(FogType val) {
    _type = val;
    if (_resource != nullptr) {
        _resource->setType(_type);
    }
}

void FogInfo::setFogDensity(float val) {
    _fogDensity = val;
    if (_resource) {
        _resource->setFogDensity(_fogDensity);
    }
}

void FogInfo::setFogStart(float val) {
    _fogStart = val;
    if (_resource != nullptr) {
        _resource->setFogStart(_fogStart);
    }
}

void FogInfo::setFogEnd(float val) {
    _fogEnd = val;
    if (_resource != nullptr) {
        _resource->setFogEnd(_fogEnd);
    }
}

void FogInfo::setFogAtten(float val) {
    _fogAtten = val;
    if (_resource != nullptr) {
        _resource->setFogAtten(_fogAtten);
    }
}

void FogInfo::setFogTop(float val) {
    _fogTop = val;
    if (_resource != nullptr) {
        _resource->setFogTop(_fogTop);
    }
}

void FogInfo::setFogRange(float val) {
    _fogRange = val;
    if (_resource != nullptr) {
        _resource->setfogRange(_fogRange);
    }
}

void FogInfo::activate(Fog *resource) {
    _resource = resource;
    _resource->initialize(*this);
    _resource->activate();
}

//
void Fog::initialize(const FogInfo &fogInfo) {
    setFogColor(fogInfo.getFogColor());
    _enabled    = fogInfo.isEnabled();
    _type       = _enabled ? fogInfo.getType() : FogType::NONE;
    _fogDensity = fogInfo.getFogDensity();
    _fogStart   = fogInfo.getFogStart();
    _fogEnd     = fogInfo.getFogEnd();
    _fogAtten   = fogInfo.getFogAtten();
    _fogTop     = fogInfo.getFogTop();
    _fogRange   = fogInfo.getFogRange();
}

void Fog::updatePipeline() {
    auto *        root     = Root::getInstance();
    const FogType value    = _enabled ? _type : FogType::NONE;
    auto *        pipeline = root->getPipeline();

    if (auto iter = pipeline->getMacros().find("CC_USE_FOG"); iter != pipeline->getMacros().end()) {
        const MacroValue &macro    = iter->second;
        const int32_t *   macroPtr = CC_GET_IF<int32_t>(&macro);
        if (macroPtr != nullptr && *macroPtr == static_cast<int32_t>(value)) {
            return;
        }
    }

    pipeline->setValue("CC_USE_FOG", static_cast<int32_t>(value));
    root->onGlobalPipelineStateChanged();
}

} // namespace scene
} // namespace cc
