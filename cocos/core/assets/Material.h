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

#include "core/assets/Asset.h"

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "core/Types.h"
#include "core/assets/EffectAsset.h"
#include "core/assets/TextureBase.h"

#include "renderer/gfx-base/GFXTexture.h"
#include "renderer/core/PassUtils.h"

#include "math/Math.h"

namespace cc {

namespace scene {
class Pass;
}

class RenderableComponent;

/**
 * @en The basic infos for material initialization.
 * @zh 用来初始化材质的基本信息。
 */
struct IMaterialInfo {
    /**
     * @en The EffectAsset to use. Must provide if `effectName` is not specified.
     * @zh
     * 这个材质将使用的 EffectAsset，直接提供资源引用，和 `effectName` 至少要指定一个。
     */
    EffectAsset *effectAsset{nullptr};
    /**
     * @en
     * The name of the EffectAsset to use. Must provide if `effectAsset` is not specified.
     * @zh
     * 这个材质将使用的 EffectAsset，通过 effect 名指定，和 `effectAsset` 至少要指定一个。
     */
    std::string effectName;
    /**
     * @en
     * The index of the technique to use.
     * @zh
     * 这个材质将使用第几个 technique，默认为 0。
     */
    uint32_t technique{0};

    using DefinesType = std::vector<MacroRecord>;
    /**
     * @en
     * The shader macro definitions. Default to 0 or the specified value in [[EffectAsset]].
     * @zh
     * 这个材质定义的预处理宏，默认全为 0，或 [[EffectAsset]] 中的指定值。
     */
    DefinesType defines;

    using PassOverridesType = std::vector<PassOverrides>;
    /**
     * @en
     * The override values on top of the pipeline states specified in [[EffectAsset]].
     * @zh
     * 这个材质的自定义管线状态，将覆盖 effect 中的属性。<br>
     * 注意在可能的情况下请尽量少的自定义管线状态，以减小对渲染效率的影响。
     */
    PassOverridesType states;
};

class Material final : public Asset {
public:
    /**
     * @en Get hash for a material
     * @zh 获取一个材质的哈希值
     * @param material
     */
    static uint64_t getHashForMaterial(Material *material);

    Material() = default;

    /**
     * @en Initialize this material with the given information.
     * @zh 根据所给信息初始化这个材质，初始化正常结束后材质即可立即用于渲染。
     * @param info Material description info.
     */
    void initialize(const IMaterialInfo &info);
    void reset(const IMaterialInfo &info);

    /**
     * @en
     * Destroy the material definitively.<br>
     * Cannot re-initialize after destroy.<br>
     * For re-initialize purposes, call [[Material.initialize]] directly.
     * @zh
     * 彻底销毁材质，注意销毁后无法重新初始化。<br>
     * 如需重新初始化材质，不必先调用 destroy。
     */
    virtual bool destroy() override;

    /**
     * @en Recompile the shader with the specified macro overrides. Allowed only on material instances.
     * @zh 使用指定预处理宏重新编译当前 pass（数组）中的 shader。只允许对材质实例执行。
     * @param overrides The shader macro override values.
     * @param passIdx The pass to apply to. Will apply to all passes if not specified.
     */
    void recompileShaders(const MacroRecord &overrides, index_t passIdx);

    /**
     * @en Override the passes with the specified pipeline states. Allowed only on material instances.
     * @zh 使用指定管线状态重载当前的 pass（数组）。只允许对材质实例执行。
     * @param overrides The pipeline state override values.
     * @param passIdx The pass to apply to. Will apply to all passes if not specified.
     */
    void overridePipelineStates(const PassOverrides &overrides, index_t passIdx);

    /**
     * @en Callback function after material is loaded in [[Loader]]. Initialize the resources automatically.
     * @zh 通过 [[Loader]] 加载完成时的回调，将自动初始化材质资源。
     */
    virtual void onLoaded() override;

    /**
     * @en Reset all the uniforms to the default value specified in [[EffectAsset]].
     * @zh 重置材质的所有 uniform 参数数据为 [[EffectAsset]] 中的默认初始值。
     * @param clearPasses Will the rendering data be cleared too?
     */
    void resetUniforms(bool clearPasses = true);

    /**
     * @en
     * Convenient property setter provided for quick material setup.<br>
     * [[Pass.setUniform]] should be used instead if you need to do per-frame uniform update.
     * @zh
     * 设置材质 uniform 参数的统一入口。<br>
     * 注意如果需要每帧更新 uniform，建议使用 [[Pass.setUniform]] 以获得更好的性能。
     * @param name The target uniform name.
     * @param val The target value.
     * @param passIdx The pass to apply to. Will apply to all passes if not specified.
     */
    void setProperty(const std::string &name, const MaterialProperty &val, index_t passIdx = CC_INVALID_INDEX);

    /**
     * @en
     * Get the specified uniform value for this material.<br>
     * Note that only uniforms set through [[Material.setProperty]] can be acquired here.<br>
     * For the complete rendering data, use [[Pass.getUniform]] instead.
     * @zh
     * 获取当前材质的指定 uniform 参数的值。<br>
     * 注意只有通过 [[Material.setProperty]] 函数设置的参数才能从此函数取出，<br>
     * 如需取出完整的渲染数据，请使用 [[Pass.getUniform]]。
     * @param name The property or uniform name.
     * @param passIdx The target pass index. If not specified, return the first found value in all passes.
     */
    MaterialProperty *getProperty(const std::string &name, index_t passIdx = CC_INVALID_INDEX);

    /**
     * @en Copy the target material.
     * @zh 复制目标材质到当前实例。
     * @param mat The material to be copied.
     */
    void copy(const Material *mat);

protected:
    /* @type(EffectAsset) */
    const EffectAsset *_effectAsset{nullptr};

    /* @serializable */
    uint32_t _techIdx{0};

    /* @serializable */
    std::vector<MacroRecord> _defines;

    /* @serializable */
    std::vector<PassOverrides> _states;

    /* @serializable */
    std::vector<Record<std::string, MaterialProperty>> _props;

    std::vector<scene::Pass *> _passes;

    uint64_t _hash{0};

public:
    /**
     * @en The current [[EffectAsset]].
     * @zh 当前使用的 [[EffectAsset]] 资源。
     */
    inline const EffectAsset *getEffectAsset() {
        return _effectAsset;
    }

    /**
     * @en Name of the current [[EffectAsset]].
     * @zh 当前使用的 [[EffectAsset]] 资源名。
     */
    inline std::string getEffectName() {
        return _effectAsset ? _effectAsset->getName() : "";
    }

    /**
     * @en The current technique index.
     * @zh 当前的 technique 索引。
     */
    inline uint32_t getTechniqueIndex() const {
        return _techIdx;
    }

    /**
     * @en The passes defined in this material.
     * @zh 当前正在使用的 pass 数组。
     */
    std::vector<scene::Pass *> &getPasses() {
        return _passes;
    }

    /**
     * @en The hash value of this material.
     * @zh 材质的 hash。
     */
    inline uint64_t getHash() const {
        return _hash;
    }

    /**
     * @en The parent material
     * @zh 父材质
     */
    virtual Material *getParent() const {
        return nullptr;
    }

    /**
     * @en The owner render component
     * @zh 该材质所归属的渲染组件
     */
    virtual RenderableComponent *getOwner() const {
        return nullptr;
    }

protected:
    bool uploadProperty(scene::Pass *passs, const std::string &name, const MaterialProperty &val);
    void bindTexture(scene::Pass *pass, uint32_t handle, const MaterialProperty &val, index_t index);

    template <typename T>
    void prepareInfo(const T &patchArray, T &cur);

    void doDestroy();

    void                       update(bool keepProps = true);
    std::vector<scene::Pass *> createPasses();
};

template <>
void Material::prepareInfo(const IMaterialInfo::DefinesType &patchArray, IMaterialInfo::DefinesType &cur);

template <>
void Material::prepareInfo(const IMaterialInfo::PassOverridesType &patchArray, IMaterialInfo::PassOverridesType &cur);

} // namespace cc
