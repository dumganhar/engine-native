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

#include "PassInstance.h"

namespace cc {

PassInstance::PassInstance(scene::Pass *parent, MaterialInstance *owner) {
    // super(parent.root); // no such constructor
    // parent->getRoot();
    _parent = parent;
    _owner  = owner;
    //cjh    doInit(_parent, true); // defines may change now
    for (const auto &b : _shaderInfo->blocks) { // seem logically useless in ts?
        scene::IBlockRef block       = _blocks[b.binding];
        scene::IBlockRef parentBlock = _parent->getBlocks()[b.binding];
        block                        = parentBlock;
    }
    // setRootBufferDirty(true); // error in ts
    auto *paren = dynamic_cast<PassInstance *>(_parent);
    for (const auto &samplerTexture : _shaderInfo->samplerTextures) {
        for (uint32_t i = 0; i < samplerTexture.count; ++i) {
            auto *sampler = paren->_descriptorSet->getSampler(samplerTexture.binding, i);
            auto *texture = paren->_descriptorSet->getTexture(samplerTexture.binding, i);
            _descriptorSet->bindSampler(samplerTexture.binding, sampler, i);
            _descriptorSet->bindTexture(samplerTexture.binding, texture, i);
        }
    }
    Super::tryCompile();
}

scene::Pass *PassInstance::getParent() const {
    return _parent;
}

void PassInstance::overridePipelineStates(const IPassInfo &original, const PassOverrides &override) {
    _blendState->reset();
    _rs->reset();
    _depthStencilState->reset();

    Pass::fillPipelineInfo(this, original);
    Pass::fillPipelineInfo(this, override);
    onStateChange();
}

bool PassInstance::tryCompile(const std::optional<MacroRecord> &defineOverrides) {
    if (!defineOverrides.has_value()) {
        if (!overrideMacros(_defines, defineOverrides.value())) return false;
    }
    bool ret = Super::tryCompile();
    onStateChange();
    return ret;
}

void PassInstance::beginChangeStatesSilently() {
    _dontNotify = true;
}

void PassInstance::endChangeStatesSilently() {
    _dontNotify = false;
}

void PassInstance::syncBatchingScheme() {
    _defines["USE_INSTANCING"] = false;
    _defines["USE_BATCHING"]   = false;
    _batchingScheme            = scene::BatchingSchemes::NONE;
}

void PassInstance::onStateChange() {
    _hash = Pass::getPassHash(this);
    _owner->onPassStateChange(_dontNotify);
}

} // namespace cc
