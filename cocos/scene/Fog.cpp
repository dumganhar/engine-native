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

void Fog::initialize(const FogInfo &fogInfo) {
    _fogColor.set(fogInfo.fogColor);
    _enabled    = fogInfo.enabled;
    _type       = _enabled ? fogInfo.fogType : FogType::NONE;
    _fogDensity = fogInfo.fogDensity;
    _fogStart   = fogInfo.fogStart;
    _fogEnd     = fogInfo.fogEnd;
    _fogAtten   = fogInfo.fogAtten;
    _fogTop     = fogInfo.fogTop;
    _fogRange   = fogInfo.fogRange;
}

void Fog::updatePipeline() {
    auto *root = Root::getInstance();
    const FogType value = _enabled ? _type : FogType::NONE;
    auto *pipeline = root->getPipeline();
    const std::variant<float, bool, std::string> &macro = pipeline->getMacros().at("CC_USE_FOG");
    const float *macroPtr = std::get_if<float>(&macro);
    if (macroPtr && static_cast<int>(*macroPtr) == static_cast<int>(value)) {
        return;
    }
    
    pipeline->setValue("CC_USE_FOG", static_cast<float>(value));
    root->onGlobalPipelineStateChanged();
}

} // namespace scene
} // namespace cc
