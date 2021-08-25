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
    // super(parent.root);
    // parent->getRoot();
    _parent = parent;
    _owner  = owner;
    // this._doInit(this._parent, true); // defines may change now
    // TODO(xwx) _shaderInfo not implement
    //     for (let i = 0; i < this._shaderInfo.blocks.length; i++) {
    //     const u = this._shaderInfo.blocks[i];
    //     const block = this._blocks[u.binding];
    //     const parentBlock = this._parent.blocks[u.binding];
    //     block.set(parentBlock);
    // }
    setRootBufferDirty(true);
    // const paren = this._parent as PassInstance;
    // for (let i = 0; i < this._shaderInfo.samplerTextures.length; i++) {
    //     const u = this._shaderInfo.samplerTextures[i];
    //     for (let j = 0; j < u.count; j++) {
    //         const sampler = paren._descriptorSet.getSampler(u.binding, j);
    //         const texture = paren._descriptorSet.getTexture(u.binding, j);
    //         this._descriptorSet.bindSampler(u.binding, sampler, j);
    //         this._descriptorSet.bindTexture(u.binding, texture, j);
    //     }
    // }
    Super::tryCompile();
}

scene::Pass *PassInstance::getParent() const {
    return _parent;
}

void PassInstance::overridePipelineStates(const IPassInfo &original, const PassOverrides &override) {
    // TODO(?) not implemented reset()
    // _blendState->reset();
    // _rs->reset();
    // _depthStencilState->reset();

    Pass::fillPipelineInfo(this, original);
    Pass::fillPipelineInfo(this, override);
    onStateChange();
}

bool PassInstance::tryCompile(const MacroRecord &defineOverrides) {
    if (!defineOverrides.empty()) {
        // if (!overrideMacros(_defines, defineOverrides)) return false; //overrideMacros not implement
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
    // this._defines.USE_BATCHING = this._defines.USE_INSTANCING = false;
    _defines["USE_INSTANCING"] = false; // not sure?
    _defines["USE_BATCHING"]   = false; // not sure?
    setBatchingScheme(scene::BatchingSchemes::NONE);
}

void PassInstance::onStateChange() {
    setHash(Pass::getPassHash(this));
    _owner->onPassStateChange(_dontNotify);
}

} // namespace cc