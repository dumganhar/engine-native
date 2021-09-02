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
#include "scene/SubModel.h"
#include "pipeline/Define.h"
#include "scene/Model.h"
#include "scene/Pass.h"
namespace cc {
namespace scene {
const static uint32_t  MAX_PASS_COUNT = 8;
gfx::DescriptorSetInfo dsInfo         = gfx::DescriptorSetInfo();

void SubModel::update() {
    for (Pass *pass : _passes) {
        pass->update();
    }
    _descriptSet->update();
}

SubModel::~SubModel() {
    CC_SAFE_DELETE(_subMesh);
}

void SubModel::setPasses(const std::vector<Pass *> &passes) {
    if (passes.size() > MAX_PASS_COUNT) {
        // errorID(12004, MAX_PASS_COUNT); //errorID not implemented
        return;
    }
    _passes = passes;
    flushPassInfo();
    // DS layout might change too
    if (_descriptorSet) {
        _descriptorSet->destroy();
        dsInfo.layout  = passes[0]->getLocalSetLayout();
        _descriptorSet = _device->createDescriptorSet(dsInfo);
    }
}

gfx::Shader *SubModel::getShader(uint index) const {
    if (index >= _shaders.size()) {
        return nullptr;
    }

    return _shaders[index];
}

Pass *SubModel::getPass(uint index) const {
    if (index >= _passes.size()) {
        return nullptr;
    }

    return _passes[index];
}

void SubModel::initialize(RenderingSubMesh *subMesh, const std::vector<Pass *> &passes, const std::vector<IMacroPatch> &patches) {
    _device = Director::getInstance().getRoot()->getDevice();
    // dsInfo
    _inputAssembler = _device->createInputAssembler(subMesh->getIaInfo());
    _descriptorSet  = _device->createDescriptorSet(dsInfo);
    _subMesh        = subMesh;
    _patches        = patches;
    setPasses(passes);

    flushPassInfo();
    if (passes[0]->getBatchingScheme() == BatchingSchemes::VB_MERGING) {
        subMesh->genFlatBuffers();
    }
    _priority = pipeline::RenderPriority::DEFAULT;

    // initialize resources for reflection material
    if (passes[0]->getPhase() == pipeline::getPhaseID("reflection")) {
        uint32_t   texWidth  = _device->getWidth();
        uint32_t   texHeight = _device->getHeight();
        const uint minSize   = 512;
        if (texHeight < texWidth) {
            texWidth  = minSize * texWidth / texHeight;
            texHeight = minSize;
        } else {
            texWidth  = minSize;
            texHeight = minSize * texHeight / texWidth;
        }
        _reflectionTex = _device->createTexture({
            gfx::TextureType::TEX2D,
            gfx::TextureUsageBit::STORAGE | gfx::TextureUsageBit::TRANSFER_SRC | gfx::TextureUsageBit::SAMPLED,
            gfx::Format::RGBA8,
            texWidth,
            texHeight,
            gfx::TextureFlagBit::IMMUTABLE,
        });
        _descriptorSet->bindTexture(pipeline::REFLECTIONTEXTURE::BINDING, _reflectionTex);

        uint32_t samplerHash = pipeline::SamplerLib::genSamplerHash({
            gfx::Filter::LINEAR,
            gfx::Filter::LINEAR,
            gfx::Filter::NONE,
            gfx::Address::CLAMP,
            gfx::Address::CLAMP,
            gfx::Address::CLAMP,
        });
        _reflectionSampler   = pipeline::SamplerLib::getSampler(samplerHash);
        _descriptorSet->bindSampler(pipeline::REFLECTIONTEXTURE::BINDING, _reflectionSampler);
        _descriptorSet->bindTexture(pipeline::REFLECTIONTEXTURE::BINDING, _reflectionTex);
    }
}

// TODO:
// This is a temporary solution
// It should not be written in a fixed way, or modified by the user
void SubModel::initPlanarShadowShader() {
    auto *  pipeline   = dynamic_cast<pipeline::ForwardPipeline *>(Director::getInstance().getRoot()->getPipeline());
    Shadow *shadowInfo = pipeline->getPipelineSceneData()->getShadow();
    _planarShader      = shadowInfo->getPlanarShader(_patches);
}

// TODO:
// This is a temporary solution
// It should not be written in a fixed way, or modified by the user
void SubModel::initPlanarShadowInstanceShader() {
    auto *  pipeline      = dynamic_cast<pipeline::ForwardPipeline *>(Director::getInstance().getRoot()->getPipeline());
    Shadow *shadowInfo    = pipeline->getPipelineSceneData()->getShadow();
    _planarInstanceShader = shadowInfo->getPlanarInstanceShader(_patches);
}

void SubModel::destroy() {
    CC_SAFE_DESTROY(_descriptSet);
    CC_SAFE_DESTROY(_inputAssembler);
    _priority = pipeline::RenderPriority::DEFAULT;
    _patches.clear();

    CC_SAFE_DELETE(_subMesh);

    for (Pass *pass : _passes) {
        CC_SAFE_DESTROY(pass);
    }
    _passes.clear();

    for (gfx::Shader *shader : _shaders) {
        CC_SAFE_DESTROY(shader);
    }
    _shaders.clear();

    CC_SAFE_DESTROY(_reflectionTex);
    CC_SAFE_DESTROY(_reflectionSampler);
}

void SubModel::onPipelineStateChanged() {
    if (_passes.empty()) return;

    for (Pass *pass : _passes) {
        pass->beginChangeStatesSilently();
        pass->tryCompile(); // force update shaders
        pass->endChangeStatesSilently();
    }
    flushPassInfo();
}

void SubModel::onMacroPatchesStateChanged(const std::vector<IMacroPatch> &patches) {
    _patches = patches;
    if (_passes.empty()) return;
    for (Pass *pass : _passes) {
        pass->beginChangeStatesSilently();
        pass->tryCompile(); // force update shaders
        pass->endChangeStatesSilently();
    }
    flushPassInfo();
}

void SubModel::flushPassInfo() {
    if (_passes.empty()) return;
    if (!_shaders.empty()) {
        for (gfx::Shader *shader : _shaders) {
            CC_SAFE_DESTROY(shader);
        }
    }
    _shaders.resize(_passes.size());
    for (uint i = 0; i < _passes.size(); ++i) {
        _shaders[i] = _passes[i]->getShaderVariant(_patches);
    }
}
} // namespace scene
} // namespace cc
