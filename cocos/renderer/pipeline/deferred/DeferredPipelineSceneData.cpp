#include "renderer/pipeline/deferred/DeferredPipelineSceneData.h"
#include "renderer/pipeline/RenderPipeline.h"
#include "renderer/pipeline/deferred/BloomStage.h"
#include "scene/Shadow.h"

namespace cc {
namespace pipeline {

void DeferredPipelineSceneData::activate(gfx::Device *device, RenderPipeline *pipeline) {
    PipelineSceneData::activate(device, pipeline);
    initPipelinePassInfo();
}

void DeferredPipelineSceneData::onGlobalPipelineStateChanged() {
    updatePipelinePassInfo();
}

void DeferredPipelineSceneData::initPipelinePassInfo() {
    // builtin deferred material
    auto *deferredMat = new Material();
    deferredMat->setUuid("builtin-deferred-material");
    IMaterialInfo materialInfo;
    materialInfo.effectName = "deferred-lighting";
    deferredMat->initialize(materialInfo);
    for (const auto &pass : deferredMat->getPasses()) {
        pass->tryCompile();
    }
    _deferredLightingMaterial = deferredMat;

    auto *bloomMat = new Material();
    bloomMat->setUuid("builtin-bloom-material");
    materialInfo.effectName = "bloom";
    bloomMat->initialize(materialInfo);
    for (const auto &pass : bloomMat->getPasses()) {
        pass->tryCompile();
    }
    _bloomMaterial = bloomMat;

    auto *postMat = new Material();
    postMat->setUuid("builtin-post-process-material");
    //TODO(minggo):
    //    if (macro.ENABLE_ANTIALIAS_FXAA) {
    //        _antiAliasing = AntiAliasing::FXAA;
    //    }
    materialInfo.effectName = "post-process";
    MacroRecord record{{"ANTIALIAS_TYPE", static_cast<int32_t>(_antiAliasing)}};
    materialInfo.defines = record;
    for (const auto &pass : postMat->getPasses()) {
        pass->tryCompile();
    }
    _postProcessMaterial = postMat;

    updatePipelinePassInfo();
}

void DeferredPipelineSceneData::setAntiAliasing(AntiAliasing value) {
    _antiAliasing = value;
    if (_postProcessMaterial) {
        auto &defines = _postProcessMaterial->getPasses()[0]->getDefines();
        defines.emplace("ANTIALIAS_TYPE", static_cast<int32_t>(value));
        auto *        renderMat = new Material();
        IMaterialInfo materialInfo;
        materialInfo.effectAsset = _postProcessMaterial->getEffectAsset();
        materialInfo.defines     = defines;
        renderMat->initialize(materialInfo);
        for (const auto &pass : renderMat->getPasses()) {
            pass->tryCompile();
        }
        _postProcessMaterial = renderMat;
    }
}

void DeferredPipelineSceneData::updateBloomPass() {
    if (!_bloomMaterial) {
        return;
    }

    scene::Pass *prefilterPass = _bloomMaterial->getPasses()[BLOOM_PREFILTERPASS_INDEX];
    prefilterPass->beginChangeStatesSilently();
    prefilterPass->tryCompile();
    prefilterPass->endChangeStatesSilently();

    for (uint32_t i = 0; i < MAX_BLOOM_FILTER_PASS_NUM; ++i) {
        scene::Pass *downsamplePass = _bloomMaterial->getPasses()[BLOOM_DOWNSAMPLEPASS_INDEX + i];
        downsamplePass->beginChangeStatesSilently();
        downsamplePass->tryCompile();
        downsamplePass->endChangeStatesSilently();

        scene::Pass *upsamplePass = _bloomMaterial->getPasses()[BLOOM_UPSAMPLEPASS_INDEX + i];
        upsamplePass->beginChangeStatesSilently();
        upsamplePass->tryCompile();
        upsamplePass->endChangeStatesSilently();
    }

    scene::Pass *combinePass = _bloomMaterial->getPasses()[BLOOM_COMBINEPASS_INDEX];
    combinePass->beginChangeStatesSilently();
    combinePass->tryCompile();
    combinePass->endChangeStatesSilently();
}

void DeferredPipelineSceneData::updatePostProcessPass() {
    if (!_postProcessMaterial) {
        return;
    }

    scene::Pass *passPost = _postProcessMaterial->getPasses()[0];
    passPost->beginChangeStatesSilently();
    passPost->tryCompile();
    passPost->endChangeStatesSilently();
}

void DeferredPipelineSceneData::updatePipelinePassInfo() {
    updateBloomPass();
    updatePostProcessPass();
    updateDeferredPassInfo();
}

void DeferredPipelineSceneData::updateDeferredPassInfo() {
    updateDeferredLightPass();
}

void DeferredPipelineSceneData::updateDeferredLightPass() {
    if (!_deferredLightingMaterial) {
        return;
    }

    // It's temporary solution for main light shadowmap
    if (_shadow->isEnabled()) {
        _pipeline->setValue("CC_RECEIVE_SHADOW", 1);
    }

    scene::Pass *passLit = _deferredLightingMaterial->getPasses()[0];
    passLit->beginChangeStatesSilently();
    passLit->tryCompile();
    passLit->endChangeStatesSilently();
}

} // namespace pipeline
} // namespace cc
