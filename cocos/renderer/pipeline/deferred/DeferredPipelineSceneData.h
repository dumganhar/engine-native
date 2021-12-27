#pragma once

#include "base/Ptr.h"
#include "core/assets/Material.h"
#include "renderer/gfx-base/GFXShader.h"
#include "renderer/pipeline/PipelineSceneData.h"
#include "scene/Pass.h"

#define BLOOM_PREFILTERPASS_INDEX  0
#define BLOOM_DOWNSAMPLEPASS_INDEX 1
#define BLOOM_UPSAMPLEPASS_INDEX   (BLOOM_DOWNSAMPLEPASS_INDEX + 1)
#define BLOOM_COMBINEPASS_INDEX    (BLOOM_UPSAMPLEPASS_INDEX + 1)

namespace cc {
namespace pipeline {

enum class AntiAliasing {
    NONE,
    FXAA
};

class DeferredPipelineSceneData : public PipelineSceneData {
public:
    DeferredPipelineSceneData()           = default;
    ~DeferredPipelineSceneData() override = default;

    void activate(gfx::Device *device, RenderPipeline *pipeline) override;
    void onGlobalPipelineStateChanged() override;

    void initPipelinePassInfo();

    void                setAntiAliasing(AntiAliasing value);
    inline AntiAliasing getAntiAliasing() const { return _antiAliasing; }

    inline Material *getBloomMaterial() const { return _bloomMaterial; }
    inline void      setBloomMaterial(Material *mat) {
        if (mat == _bloomMaterial.get()) {
            return;
        }
        _bloomMaterial = mat;
        updatePipelinePassInfo();
    }

    inline Material *getPostProcessMaterial() const { return _postProcessMaterial; }
    inline void      setPostProcessMaterial(Material *mat) {
        if (mat == _postProcessMaterial.get()) {
            return;
        }
        _postProcessMaterial = mat;
        updatePipelinePassInfo();
    }

    inline Material *getDeferredPostMaterial() const { return _deferredPostMaterial; }
    inline void      setDeferredPostMaterial(Material *mat) {
        if (mat == _deferredPostMaterial.get()) {
            return;
        }
        _deferredPostMaterial = mat;
        updatePipelinePassInfo();
    }

    inline void      setDeferredLightingMaterial(Material *mat) { _deferredLightingMaterial = mat; }
    inline Material *getDeferredLightingMaterial() const { return _deferredLightingMaterial; }

    inline gfx::Shader *getDeferredLightPassShader() const { return _deferredLightPassShader; }
    inline gfx::Shader *getDeferredPostPassShader() const { return _deferredPostPassShader; }
    inline scene::Pass *getDeferredLightPass() const { return _deferredLightPass; }
    inline scene::Pass *getDeferredPostPass() const { return _deferredPostPass; }

private:
    void updateBloomPass();
    void updatePostProcessPass();
    void updatePipelinePassInfo();
    void updateDeferredPassInfo();
    void updateDeferredLightPass();

    SharedPtr<Material> _deferredLightingMaterial;
    SharedPtr<Material> _deferredPostMaterial;
    SharedPtr<Material> _bloomMaterial;
    SharedPtr<Material> _postProcessMaterial;

    SharedPtr<gfx::Shader> _deferredLightPassShader;
    SharedPtr<scene::Pass> _deferredLightPass;
    SharedPtr<gfx::Shader> _deferredPostPassShader;

    SharedPtr<scene::Pass> _deferredPostPass;

    AntiAliasing _antiAliasing{AntiAliasing::NONE};
};

} // namespace pipeline
} // namespace cc
