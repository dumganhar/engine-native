#pragma once

#include "core/assets/Material.h"
#include "renderer/gfx-base/GFXShader.h"
#include "scene/Pass.h"
#include "renderer/pipeline/PipelineSceneData.h"

namespace cc {
namespace pipeline {

class DeferredPipelineSceneData : public PipelineSceneData {
public:
    DeferredPipelineSceneData() = default;
    ~DeferredPipelineSceneData() override = default;
    
    //TODO minggo
    void activate(gfx::Device *device, RenderPipeline *pipeline) override {};
    void onGlobalPipelineStateChanged() override {};
    
    //TODO: minggo
    void initPipelinePassInfo() {}
    
    inline void setDeferredPostMaterial(Material *mat) { _deferredPostMaterial = mat; }
    inline Material *getDeferredPostMaterial() const { return _deferredPostMaterial; }
    
    inline void setDeferredLightingMaterial(Material *mat) { _deferredLightingMaterial = mat; }
    inline Material *getDeferredLightingMaterial() const { return _deferredLightingMaterial; }
    
    inline gfx::Shader *getDeferredLightPassShader() const { return _deferredLightPassShader; }
    inline gfx::Shader *getDeferredPostPassShader() const { return _deferredPostPassShader; }
    inline scene::Pass *getDeferredLightPass() const { return _deferredLightPass; }
    inline scene::Pass *getDeferredPostPass() const { return _deferredPostPass; }

private:
    //TODO: minggo
    void updateDeferredPassInfo() {}
    void updateDeferredLightPass() {}
    void updateDeferredPostPass() {}
    
    Material *_deferredLightingMaterial{nullptr};
    Material *_deferredPostMaterial{nullptr};
    
    gfx::Shader *_deferredLightPassShader{nullptr};
    scene::Pass *_deferredLightPass{nullptr};
    
    gfx::Shader *_deferredPostPassShader{nullptr};
    scene::Pass *_deferredPostPass{nullptr};
};

}
}
