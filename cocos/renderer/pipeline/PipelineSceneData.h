/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#pragma once

#include "Define.h"
#include "core/geometry/Sphere.h"
#include "scene/Light.h"
#include "scene/Fog.h"
#include "scene/Ambient.h"
#include "scene/Skybox.h"
#include "scene/Shadow.h"

namespace cc {

namespace gfx {
class Framebuffer;
}

namespace pipeline {

class RenderPipeline;

class CC_DLL PipelineSceneData : public Object {
public:
    PipelineSceneData()           = default;
    ~PipelineSceneData() override = default;
    void activate(gfx::Device *device, RenderPipeline *pipeline);
    void destroy();

    inline void onGlobalPipelineStateChanged() {}

    inline bool isHDR() const { return _isHDR; }
    inline void setHDR(bool val) { _isHDR = val; }

    inline float getShadingScale() const { return _shadingScale; }
    inline void  setShadingScale(float val) { _shadingScale = val; }

    inline float getFpScale() const { return _fpScale; }
    inline void  setFpScale(float val) { _fpScale = val; }

    inline scene::Fog *getFog() const { return _fog; }
    inline void        setFog(scene::Fog *fog) { _fog = fog; }

    inline scene::Ambient *getAmbient() const { return _ambient; }
    inline void            setAmbient(scene::Ambient *ambient) { _ambient = ambient; }

    inline scene::Skybox *getSkybox() const { return _skybox; }
    inline void           setSkybox(scene::Skybox *skybox) { _skybox = skybox; }

    inline scene::Shadow *getShadow() const { return _shadow; }
    inline void           setShadow(scene::Shadow *shadow) { _shadow = shadow; }

    inline void setShadowFramebuffer(const scene::Light *light, gfx::Framebuffer *framebuffer) {
        _shadowFrameBufferMap.emplace(light, framebuffer);
    }

    inline const RenderObjectList &getRenderObjects() const { return _renderObjects; }
    inline const RenderObjectList &getShadowObjects() const { return _shadowObjects; }
    inline void                    setRenderObjects(RenderObjectList &&ro) { _renderObjects = std::forward<RenderObjectList>(ro); }
    inline void                    setShadowObjects(RenderObjectList &&ro) { _shadowObjects = std::forward<RenderObjectList>(ro); }
    inline geometry::Sphere *      getSphere() const { return _sphere; }

    inline const std::unordered_map<const scene::Light *, gfx::Framebuffer *> &getShadowFramebufferMap() const {
        return _shadowFrameBufferMap;
    }

private:
    RenderObjectList _renderObjects;
    RenderObjectList _shadowObjects;

    RenderPipeline *  _pipeline{nullptr};
    gfx::Device *     _device{nullptr};
    geometry::Sphere *_sphere{nullptr};
    scene::Fog *      _fog{nullptr};
    scene::Ambient *  _ambient{nullptr};
    scene::Skybox *   _skybox{nullptr};
    scene::Shadow *   _shadow{nullptr};
    bool              _isHDR{false};
    float             _shadingScale{1.0F};
    float             _fpScale{1.0F / 1024.F};

    std::unordered_map<const scene::Light *, gfx::Framebuffer *> _shadowFrameBufferMap;
};

} // namespace pipeline
} // namespace cc
