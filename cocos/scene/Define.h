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

#pragma once

#include "math/Mat4.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "renderer/gfx-base/GFXShader.h"
#include "scene/Model.h"
#include "scene/Ambient.h"
#include "scene/Skybox.h"
#include "scene/Fog.h"

namespace cc {
namespace scene {

// As Pass.h will include Define.h, so use forward declaration.
class Pass;

enum class ShadowType {
    PLANAR    = 0,
    SHADOWMAP = 1
};

struct Shadow {
    bool       enabled{false};
    bool       dirty{false};
    bool       shadowMapDirty{false};
    bool       autoAdapt{false};
    ShadowType shadowType{ShadowType::PLANAR};
    float      distance{0.0F};
    Pass *     instancePass{nullptr};
    Pass *     planarPass{nullptr};
    float      nearValue{0.0F};
    float      farValue{0.0F};
    uint32_t   pcfType{0};
    float      bias{0.0F};
    float      normalBias{0.0F};
    float      saturation{0.0F};
    float      orthoSize{0.0F};

    Vec4 color;
    Vec2 size;
    Vec3 normal;
    Mat4 matLight;
};

struct PipelineSharedSceneData {
    bool         isHDR{false};
    float        shadingScale{0.0F};
    float        fpScale{0.0F};
    Ambient *    ambient{nullptr};
    Shadow *     shadow{nullptr};
    Skybox *     skybox{nullptr};
    Fog *        fog{nullptr};
    Pass *       deferredLightPass{nullptr};
    gfx::Shader *deferredLightPassShader{nullptr};
    Pass *       deferredPostPass{nullptr};
    gfx::Shader *deferredPostPassShader{nullptr};
};

enum class BatchingSchemes {
    NONE       = 0,
    INSTANCING = 1,
    VB_MERGING = 2,
};

} // namespace scene
} // namespace cc
