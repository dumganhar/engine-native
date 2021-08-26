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
#include <variant>
#include "base/TypeDef.h"
#include "core/Types.h"
#include "core/assets/TextureBase.h"
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Quaternion.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "renderer/gfx-base/GFXDef.h"

namespace cc {

static const uint32_t dtMask      = 0xf0000000; //  4 bits => 16 property types
static const uint32_t typeMask    = 0x0fc00000; //  6 bits => 64 types
static const uint32_t setMask     = 0x00300000; //  2 bits => 4 sets
static const uint32_t bindingMask = 0x000fc000; //  6 bits => 64 bindings
static const uint32_t offsetMask  = 0x00003fff; // 14 bits => 4096 vectors

/**
 * @en The type enums of the property
 * @zh Uniform 的绑定类型（UBO 或贴图等）
 */
enum class PropertyType : uint32_t {
    /**
     * Uniform buffer object
     */
    BUFFER,
    /**
     * Texture sampler
     */
    TEXTURE,
};
CC_ENUM_CONVERSION_OPERATOR(PropertyType);

inline uint32_t genHandle(PropertyType pt, uint32_t set, uint32_t binding, gfx::Type type, uint32_t offset /* = 0 */) {
    return ((static_cast<uint32_t>(pt) << 28) & dtMask) | ((static_cast<uint32_t>(type) << 22) & typeMask) | ((set << 20) & setMask) | ((binding << 14) & bindingMask) | (offset & offsetMask);
}

inline PropertyType getPropertyTypeFromHandle(uint32_t handle) {
    return static_cast<PropertyType>((handle & dtMask) >> 28);
}

inline gfx::Type getTypeFromHandle(uint32_t handle) {
    return static_cast<gfx::Type>((handle & typeMask) >> 22);
}

inline uint32_t getSetIndexFromHandle(uint32_t handle) {
    return (handle & setMask) >> 20;
}

inline uint32_t getBindingFromHandle(uint32_t handle) {
    return (handle & bindingMask) >> 14;
}

inline uint32_t getOffsetFromHandle(uint32_t handle) {
    return (handle & offsetMask);
}

inline uint32_t customizeType(uint32_t handle, gfx::Type type) {
    return (handle & ~typeMask) | ((static_cast<uint32_t>(type) << 22) & typeMask);
}

/**
 * @en Combination of preprocess macros
 * @zh 预处理宏组合
 */
using MacroRecord = Record<std::string, std::variant<float, bool, std::string>>;

//cjh TODO:
class Color {
public:
    uint8_t r{0}, g{0}, b{0}, a{0};
};

using MaterialProperty = std::variant<std::monostate /*0*/, float /*1*/, int32_t /*2*/, Vec2 /*3*/, Vec3 /*4*/, Vec4 /*5*/, Color, /*6*/ Mat3 /*7*/, Mat4 /*8*/, Quaternion /*9*/, TextureBase * /*10*/, gfx::Texture * /*11*/>;

using MaterialPropertyList = std::vector<MaterialProperty>;

using MaterialPropertyVariant = std::variant<std::monostate /*0*/, MaterialProperty /*1*/, MaterialPropertyList /*2*/>;

#define MaterialPropertyIndexSingle (1)
#define MaterialPropertyIndexList   (2)

} // namespace cc
