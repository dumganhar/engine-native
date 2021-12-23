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

#include <string>
#include <vector>

#include "renderer/core/PassUtils.h"
#include "scene/Ambient.h"

namespace cc {
namespace scene {

class Pass;
class Ambient;
class Shadows;
class Skybox;
class Fog;

struct IMacroPatch {
    std::string name;
    MacroValue  value;
};

struct OctreeInfo {
    bool     enabled{false};
    Vec3     minPos;
    Vec3     maxPos;
    uint32_t depth{0};
};

struct PipelineSharedSceneData {
    bool                 isHDR{true};
    float                shadingScale{1.0F};
    Ambient *            ambient{nullptr};
    Shadow *             shadow{nullptr};
    Skybox *             skybox{nullptr};
    Fog *                fog{nullptr};
    OctreeInfo *         octree{nullptr};
    gfx::InputAssembler *occlusionQueryInputAssembler{nullptr};
    Pass *               occlusionQueryPass{nullptr};
    gfx::Shader *        occlusionQueryShader{nullptr};
    Pass *               deferredLightPass{nullptr};
    gfx::Shader *        deferredLightPassShader{nullptr};
    Pass *               bloomPrefilterPass{nullptr};
    gfx::Shader *        bloomPrefilterPassShader{nullptr};
    std::vector<Pass *>  bloomDownsamplePass;
    gfx::Shader *        bloomDownsamplePassShader{nullptr};
    std::vector<Pass *>  bloomUpsamplePass;
    gfx::Shader *        bloomUpsamplePassShader{nullptr};
    Pass *               bloomCombinePass{nullptr};
    gfx::Shader *        bloomCombinePassShader{nullptr};
    Pass *               pipelinePostPass{nullptr};
    gfx::Shader *        pipelinePostPassShader{nullptr};
};

} // namespace scene
} // namespace cc
