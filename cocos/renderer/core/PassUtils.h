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

#include <variant>
#include <string>
#include "base/TypeDef.h"
#include "core/Types.h"
#include "core/assets/TextureBase.h"

namespace cc {

/**
 * @en The type enums of the property
 * @zh Uniform 的绑定类型（UBO 或贴图等）
 */
enum class PropertyType {
    /**
     * Uniform buffer object
     */
    BUFFER,
    /**
     * Texture sampler
     */
    TEXTURE,
};

/**
 * @en Combination of preprocess macros
 * @zh 预处理宏组合
 */
using MacroRecord = Record<std::string, std::variant<float, bool, std::string>>;

using MaterialProperty = std::variant<
float, int32_t, Vec2, Vec3, Vec4, /* Color,*/ Mat3, Mat4, Quaternion, TextureBase *, gfx::Texture *,
std::vector<float>, std::vector<int32_t>, std::vector<Vec2>, std::vector<Vec3>, std::vector<Vec4>, /* std::vector<Color>, */
std::vector<Mat3>, std::vector<Mat4>, std::vector<Quaternion>, std::vector<TextureBase *>, std::vector<gfx::Texture *>>;

}
