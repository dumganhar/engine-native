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
#include "core/assets/EffectAsset.h"
#include "core/assets/TextureBase.h"

#include "core/Types.h"

#include "renderer/gfx-base/GFXTexture.h"

#include "math/Math.h"

#include <variant>
#include <unordered_map>
#include <string>

namespace cc {

namespace gfx {
    class Pass;
}

class RenderableComponent;

using MaterialProperty = std::variant<float, int32_t, Vec2, Vec3, Vec4, /* Color //cjh ,*/Mat3, Mat4, Quaternion>;
using MaterialPropertyFull = std::variant<float, int32_t, Vec2, Vec3, Vec4, /* Color //cjh ,*/Mat3, Mat4, Quaternion, TextureBase, gfx::Texture>;
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
    EffectAsset* effectAsset{nullptr};
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
    /**
     * @en
     * The shader macro definitions. Default to 0 or the specified value in [[EffectAsset]].
     * @zh
     * 这个材质定义的预处理宏，默认全为 0，或 [[EffectAsset]] 中的指定值。
     */
    std::vector<MacroRecord> defines;
    /**
     * @en
     * The override values on top of the pipeline states specified in [[EffectAsset]].
     * @zh
     * 这个材质的自定义管线状态，将覆盖 effect 中的属性。<br>
     * 注意在可能的情况下请尽量少的自定义管线状态，以减小对渲染效率的影响。
     */
    std::vector<PassOverrides> states;
};

class Material final : public Asset {
public:
    /**
     * @en Get hash for a material
     * @zh 获取一个材质的哈希值
     * @param material
     */
    static uint64_t getHash(Material* material);

protected:
    /* @type(EffectAsset) */
    EffectAsset* _effectAsset{nullptr};

    /* @serializable */
    uint32_t _techIdx{0};

    /* @serializable */
    std::vector<MacroRecord> _defines;

    /* @serializable */
    std::vector<PassOverrides> _states;

    /* @serializable */
    std::vector<Record<std::string, std::vector<MaterialPropertyFull>>> _props;

    std::vector<gfx::Pass*> _passes;

    uint64_t _hash{0};

public:
    Material() = default;

    /**
     * @en The current [[EffectAsset]].
     * @zh 当前使用的 [[EffectAsset]] 资源。
     */
    inline EffectAsset* effectAsset() {
        return _effectAsset;
    }

    /**
     * @en Name of the current [[EffectAsset]].
     * @zh 当前使用的 [[EffectAsset]] 资源名。
     */
    inline std::string effectName() {
        return _effectAsset ? _effectAsset->getName() : "";
    }

    /**
     * @en The current technique index.
     * @zh 当前的 technique 索引。
     */
    inline uint32_t technique() const {
        return _techIdx;
    }

    /**
     * @en The passes defined in this material.
     * @zh 当前正在使用的 pass 数组。
     */
    std::vector<gfx::Pass*>& getPasses() {
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
    virtual Material* getParent() const {
        return nullptr;
    }

    /**
     * @en The owner render component
     * @zh 该材质所归属的渲染组件
     */
    virtual RenderableComponent* getOwner() const {
        return nullptr;
    }
};

} // namespace cc {

