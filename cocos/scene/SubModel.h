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

#include <vector>
#include "base/RefCounted.h"
#include "core/assets/RenderingSubMesh.h"
#include "renderer/gfx-base/GFXDescriptorSet.h"
#include "renderer/gfx-base/GFXInputAssembler.h"
#include "renderer/gfx-base/GFXShader.h"
#include "renderer/pipeline/Define.h"
#include "scene/Define.h"

namespace cc {
namespace scene {
class Pass;
class SubModel : public RefCounted {
public:
    SubModel()           = default;
    ~SubModel() override = default;

    void update();

    gfx::Shader *getShader(uint) const;
    Pass *       getPass(uint) const;

    inline void setDescriptorSet(gfx::DescriptorSet *descriptorSet) { _descriptorSet = descriptorSet; }
    inline void setInputAssembler(gfx::InputAssembler *ia) { _inputAssembler = ia; }
    inline void setShaders(const std::vector<SharedPtr<gfx::Shader>> &shaders) { _shaders = shaders; }
    void        setPasses(const std::vector<SharedPtr<Pass>> &passes);
    inline void setPlanarInstanceShader(gfx::Shader *shader) { _planarInstanceShader = shader; }
    inline void setPlanarShader(gfx::Shader *shader) { _planarShader = shader; }
    inline void setPriority(pipeline::RenderPriority priority) { _priority = priority; }
    void        setSubMesh(RenderingSubMesh *subMesh);

    inline gfx::DescriptorSet *                       getDescriptorSet() const { return _descriptorSet; }
    inline gfx::InputAssembler *                      getInputAssembler() const { return _inputAssembler; }
    inline const std::vector<SharedPtr<gfx::Shader>> &getShaders() const { return _shaders; }
    inline const std::vector<SharedPtr<Pass>> &       getPasses() const { return _passes; }
    inline const std::vector<IMacroPatch> &           getPatches() const { return _patches; }
    inline gfx::Shader *                              getPlanarInstanceShader() const { return _planarInstanceShader; }
    inline gfx::Shader *                              getPlanarShader() const { return _planarShader; }
    inline pipeline::RenderPriority                   getPriority() const { return _priority; }
    inline RenderingSubMesh *                         getSubMesh() const { return _subMesh; }

    void initialize(RenderingSubMesh *subMesh, const std::vector<SharedPtr<Pass>> &passes, const std::vector<IMacroPatch> &patches);
    void initPlanarShadowShader();
    void initPlanarShadowInstanceShader();
    void destroy();
    void onPipelineStateChanged();
    void onMacroPatchesStateChanged(const std::vector<IMacroPatch> &patches);

protected:
    void flushPassInfo();

    gfx::Device *                       _device{nullptr};
    std::vector<IMacroPatch>            _patches;
    SharedPtr<gfx::InputAssembler>      _inputAssembler;
    SharedPtr<gfx::DescriptorSet>       _descriptorSet;
    SharedPtr<gfx::Texture>             _reflectionTex;
    SharedPtr<gfx::Sampler>             _reflectionSampler;
    pipeline::RenderPriority            _priority{pipeline::RenderPriority::DEFAULT};
    SharedPtr<gfx::Shader>              _planarShader;
    SharedPtr<gfx::Shader>              _planarInstanceShader;
    SharedPtr<RenderingSubMesh>         _subMesh;
    std::vector<SharedPtr<Pass>>        _passes;
    std::vector<SharedPtr<gfx::Shader>> _shaders;

    CC_DISALLOW_COPY_MOVE_ASSIGN(SubModel);
};

} // namespace scene
} // namespace cc
