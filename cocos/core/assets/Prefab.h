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

#include <any>

namespace cc {



/**
 * @en Class for prefab handling.
 * @zh 预制资源类。
 */
class Prefab final : public Asset {
public:

    /**
     * @en An enumeration used with the [[Prefab.optimizationPolicy]] to specify how to optimize the instantiate operation.
     * @zh Prefab 创建实例所用的优化策略，配合 [[Prefab.optimizationPolicy]] 使用。
     */
    enum class OptimizationPolicy {
        /**
         * @en The optimization policy is automatically chosen based on the number of instantiations.
         * When you first create an instance, the behavior is the same as SINGLE_INSTANCE.
         * MULTI_INSTANCE will be automatically used after multiple creation.
         * @zh 根据创建次数自动调整优化策略。初次创建实例时，行为等同 SINGLE_INSTANCE，多次创建后将自动采用 MULTI_INSTANCE。
         */
        AUTO = 0,
        /**
         * @en Optimize for single instance creation.<br>
         * This option skips code generation for this prefab.
         * When this prefab will usually create only one instances, please select this option.
         * @zh 优化单次创建性能。<br>
         * 该选项会跳过针对这个 prefab 的代码生成优化操作。当该 prefab 加载后，一般只会创建一个实例时，请选择此项。
         */
        SINGLE_INSTANCE = 1,
        /**
         * @en Optimize for creating instances multiple times.<br>
         * This option enables code generation for this prefab.
         * When this prefab will usually create multiple instances, please select this option.
         * It is also recommended to select this option if the prefab instance in the scene
         * has Auto Sync enabled and there are multiple instances in the scene.
         * @zh 优化多次创建性能。<br>
         * 该选项会启用针对这个 prefab 的代码生成优化操作。当该 prefab 加载后，一般会创建多个实例时，请选择此项。如果该 prefab 在场景中的节点启用了自动关联，并且在场景中有多份实例，也建议选择此项。
         */
        MULTI_INSTANCE = 2,
    };


    static constexpr uint32_t OptimizationPolicyThreshold = 3;

    /**
     * @en The main [[Node]] in the prefab
     * @zh Prefab 中的根节点，[[Node]] 类型

    @serializable
    @editable*/
    std::any _data;

    /**
     * @zh
     * 设置实例化这个 prefab 时所用的优化策略。根据使用情况设置为合适的值，能优化该 prefab 实例化所用的时间。推荐在编辑器的资源中设置。
     * @en
     * Indicates the optimization policy for instantiating this prefab.
     * Set to a suitable value based on usage, can optimize the time it takes to instantiate this prefab.
     * Suggest to set this policy in the editor's asset inspector.
     * @default Prefab.OptimizationPolicy.AUTO
     * @example
     * ```ts
     * import { Prefab } from 'cc';
     * prefab.optimizationPolicy = Prefab.OptimizationPolicy.MULTI_INSTANCE;
     * ```

    @serializable
    @editable*/
    OptimizationPolicy optimizationPolicy = OptimizationPolicy::AUTO;

    Prefab() = default;

    virtual void createNode(const CreateNodeCallback& cb) override;

    Node* _instantiate();

    virtual void initDefault(const std::string& uuid) override;
    virtual bool validate() const override { _data.has_value(); }

};

} // namespace cc {

