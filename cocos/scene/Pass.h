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

#include <cstdint>
#include <string>
#include <vector>
#include "base/TypeDef.h"
#include "renderer/gfx-base/GFXBuffer.h"
#include "renderer/gfx-base/GFXDef-common.h"
#include "renderer/gfx-base/GFXDescriptorSet.h"
#include "renderer/pipeline/Define.h"
#include "scene/Define.h"
#include "renderer/core/PassUtils.h"
#include "core/assets/EffectAsset.h"

namespace cc {
namespace scene {

struct PassDynamicsValue {
    bool  dirty{false};
    float value{0.F};
};
using IPassDynamics = std::unordered_map<uint32_t, PassDynamicsValue>;


struct IPassInfoFull final : public IPassInfo {
    // generated part
    index_t passIndex{0};
    MacroRecord defines;
    std::optional<PassOverrides> stateOverrides;
};

class Pass final {
public:
    /**
     * @en Fill a pass represented by the given pass handle with the given override info
     * @param pass The pass handle point to the pass
     * @param info The pass override info
     */
    static void fillPipelineInfo(Pass *pass, const PassOverrides &info);

    /**
     * @en Get pass hash value by [[Pass]] hash information.
     * @zh 根据 [[Pass]] 的哈希信息获取哈希值。
     *
     * @param pass Handle of the pass info used to compute hash value.
     */
    static uint64_t getPassHash(Pass *pass);

    Pass() { _phase = pipeline::getPhaseID("default"); }
    Pass(const Pass &) = delete;
    Pass(Pass &&)      = delete;
    ~Pass()            = default;
    Pass &operator=(const Pass &) = delete;
    Pass &operator=(Pass &&) = delete;
    
    /**
     * @en Initialize the pass with given pass info, shader will be compiled in the init process
     * @zh 根据指定参数初始化当前 pass，shader 会在这一阶段就尝试编译。
     */
    void initialize (const IPassInfoFull &info);

    void update();
    
    /**
     * @en Get the handle of a UBO member, or specific channels of it.
     * @zh 获取指定 UBO 成员，或其更具体分量的读写句柄。默认以成员自身的类型为目标读写类型（即读写时必须传入与成员类型相同的变量）。
     * @param name Name of the target UBO member.
     * @param offset Channel offset into the member.
     * @param targetType Target type of the handle, i.e. the type of data when read/write to it.
     * @example
     * ```
     * import { Vec3, gfx } from 'cc';
     * // say 'pbrParams' is a uniform vec4
     * const hParams = pass.getHandle('pbrParams'); // get the default handle
     * pass.setUniform(hAlbedo, new Vec3(1, 0, 0)); // wrong! pbrParams.w is NaN now
     *
     * // say 'albedoScale' is a uniform vec4, and we only want to modify the w component in the form of a single float
     * const hThreshold = pass.getHandle('albedoScale', 3, gfx.Type.FLOAT);
     * pass.setUniform(hThreshold, 0.5); // now, albedoScale.w = 0.5
     * ```
     */
    uint32_t getHandle(const std::string &name, uint32_t offset = 0, gfx::Type targetType = gfx::Type::UNKNOWN) const;
    
    /**
     * @en Gets the uniform binding with its name
     * @zh 获取指定 uniform 的 binding。
     * @param name The name of target uniform
     */
    int32_t getBinding(const std::string &name) const;
    
    /**
     * @en Sets a vector type uniform value, if a uniform requires frequent update, please use this method.
     * @zh 设置指定普通向量类 uniform 的值，如果需要频繁更新请尽量使用此接口。
     * @param handle The handle for the target uniform
     * @param value New value
     */
    void setUniform (uint32_t handle, const MaterialProperty &value);
    
    /**
     * @en Gets a uniform's value.
     * @zh 获取指定普通向量类 uniform 的值。
     * @param handle The handle for the target uniform
     * @param out The output property to store the result
     */
    template<typename T, std::enable_if_t<std::is_base_of<MaterialProperty, T>::value>>
    T* getUniform(uint32_t handle, T *out) const;
    
    /**
     * @en Sets an array type uniform value, if a uniform requires frequent update, please use this method.
     * @zh 设置指定数组类 uniform 的值，如果需要频繁更新请尽量使用此接口。
     * @param handle The handle for the target uniform
     * @param value New value
     */
    void setUniformArray(uint32_t handle, const std::vector<MaterialProperty> &value);
    
    /**
     * @en Bind a GFX [[Texture]] the the given uniform binding
     * @zh 绑定实际 GFX [[Texture]] 到指定 binding。
     * @param binding The binding for target uniform of texture type
     * @param value Target texture
     */
    void bindTexture(uint32_t binding, gfx::Texture *value);
    void bindTexture(uint32_t binding, gfx::Texture *value, index_t index);
    
    /**
     * @en Bind a GFX [[Sampler]] the the given uniform binding
     * @zh 绑定实际 GFX [[Sampler]] 到指定 binding。
     * @param binding The binding for target uniform of sampler type
     * @param value Target sampler
     */
    void bindSampler (uint32_t binding, gfx::Sampler *value);
    void bindSampler (uint32_t binding, gfx::Sampler *value, index_t index);
    
    /**
     * @en Sets the dynamic pipeline state property at runtime
     * @zh 设置运行时 pass 内可动态更新的管线状态属性。
     * @param state Target dynamic state
     * @param value Target value
     */
    void setDynamicState (gfx::DynamicStateFlagBit state, int32_t value);

    inline void setBatchingScheme(BatchingSchemes value) { _batchingScheme = value; }
    inline void setBlendState(gfx::BlendState *blendState) { _blendState = blendState; }
    inline void setDepthStencilState(gfx::DepthStencilState *state) { _depthStencilState = state; }
    inline void setDescriptorSet(gfx::DescriptorSet *descriptorSet) { _descriptorSet = descriptorSet; }
    inline void setDynamicState(gfx::DynamicStateFlagBit value) { _dynamicStates = value; }
    inline void setHash(uint32_t hash) { _hash = hash; }
    inline void setPhase(uint32_t phase) { _phase = phase; }
    inline void setPipelineLayout(gfx::PipelineLayout *layout) { _pipelineLayout = layout; }
    inline void setPrimitive(gfx::PrimitiveMode mode) { _primitive = mode; }
    inline void setPriority(pipeline::RenderPriority priority) { _priority = priority; }
    inline void setRasterizerState(gfx::RasterizerState *state) { _rs = state; }
    inline void setStage(pipeline::RenderPassStage stage) { _stage = stage; }
    inline void setRootBufferAndBlock(gfx::Buffer *buffer, uint8_t *block) {
        _rootBuffer = buffer;
        _rootBlock  = block;
    }
    inline void setRootBufferDirty(bool val) { _rootBufferDirty = val; }

    inline BatchingSchemes          getBatchingScheme() const { return _batchingScheme; }
    inline gfx::BlendState *        getBlendState() const { return _blendState; }
    inline gfx::DepthStencilState * getDepthStencilState() const { return _depthStencilState; }
    inline gfx::DescriptorSet *     getDescriptorSet() const { return _descriptorSet; }
    inline gfx::DynamicStateFlagBit getDynamicState() const { return _dynamicStates; }
    inline uint32_t                 getHash() const { return _hash; }
    inline uint32_t                 getPhase() const { return _phase; }
    inline gfx::PipelineLayout *    getPipelineLayout() const { return _pipelineLayout; }
    inline gfx::PrimitiveMode       getPrimitive() const { return _primitive; }
    inline pipeline::RenderPriority           getPriority() const { return _priority; }
    inline gfx::RasterizerState *   getRasterizerState() const { return _rs; }
    inline pipeline::RenderPassStage          getStage() const { return _stage; }

protected:
    // internal resources
    gfx::Buffer *              _rootBuffer{nullptr};
    std::vector<gfx::Buffer *> _buffers;
    gfx::DescriptorSet *       _descriptorSet{nullptr};
    gfx::PipelineLayout *      _pipelineLayout{nullptr};
    // internal data
    index_t                    _passIndex{0};
    index_t                    _propertyIndex{0};
    std::string                _programName;
    std::vector<IPassDynamics> _dynamics;
    Record<std::string, float> _propertyHandleMap;
    uint8_t *                  _rootBlock{nullptr};
    std::vector<float>         _blocks;
    //TODO
    //    protected _shaderInfo: IProgramInfo = null!;
    MacroRecord                        _defines;
    Record<std::string, IPropertyInfo> _properties;
    gfx::Shader *                      _shader{nullptr};
    gfx::BlendState *                  _blendState{nullptr};
    gfx::DepthStencilState *           _depthStencilState{nullptr};
    gfx::RasterizerState *             _rs{nullptr};
    pipeline::RenderPriority           _priority{pipeline::RenderPriority::DEFAULT};
    pipeline::RenderPassStage          _stage{pipeline::RenderPassStage::DEFAULT};
    uint                               _phase{0};
    gfx::PrimitiveMode                 _primitive{gfx::PrimitiveMode::TRIANGLE_LIST};
    BatchingSchemes                    _batchingScheme{BatchingSchemes::NONE};
    gfx::DynamicStateFlagBit           _dynamicStates{gfx::DynamicStateFlagBit::NONE};
    uint64_t                           _hash{0};
    // external references
    Root *       _root{nullptr};
    gfx::Device *_device{nullptr};

    bool _rootBufferDirty{false};
};

} // namespace scene
} // namespace cc
