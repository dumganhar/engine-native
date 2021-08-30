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

#include <cstdint>
#include <variant>
#include "base/Log.h"
#include "core/Types.h"
#include "gfx-base/GFXDef-common.h"
#include "math/Color.h"
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "renderer/gfx-base/GFXDef.h"

#include "renderer/core/PassUtils.h"

namespace cc {

//NOLINTNEXTLINE
const std::unordered_map<gfx::Type, std::function<void(const Float32Array &, void *, index_t id)>> type2reader = {
    {gfx::Type::UNKNOWN, [](const Float32Array & /*a*/, void * /*v*/, index_t /*idx*/) {
         CC_LOG_ERROR("type2reader unknown type");
     }},
    {gfx::Type::INT, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<int32_t *>(v);
         p[0]    = a[idx];
     }},
    {gfx::Type::INT2, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<int32_t *>(v);
         p[0]    = a[idx];
         p[1]    = a[idx + 1];
     }},
    {gfx::Type::INT3, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<int32_t *>(v);
         p[0]    = a[idx];
         p[1]    = a[idx + 1];
         p[2]    = a[idx + 2];
     }},
    {gfx::Type::INT4, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<int32_t *>(v);
         p[0]    = a[idx];
         p[1]    = a[idx + 1];
         p[2]    = a[idx + 2];
         p[3]    = a[idx + 3];
     }},
    {gfx::Type::FLOAT, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<float *>(v);
         p[0]    = a[idx];
     }},
    {gfx::Type::FLOAT2, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<float *>(v);
         p[0]    = a[idx];
         p[1]    = a[idx + 1];
     }},
    {gfx::Type::FLOAT3, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<float *>(v);
         p[0]    = a[idx];
         p[1]    = a[idx + 1];
         p[2]    = a[idx + 2];
     }},
    {gfx::Type::FLOAT4, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<float *>(v);
         p[0]    = a[idx];
         p[1]    = a[idx + 1];
         p[2]    = a[idx + 2];
         p[3]    = a[idx + 3];
     }},
    {gfx::Type::MAT3, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<Mat3 *>(v);
         for (int i = 0; i < 9; ++i) {
             p->m[i] = a[i + idx];
         }
     }},
    {gfx::Type::MAT4, [](const Float32Array &a, void *v, index_t idx) {
         auto *p = reinterpret_cast<Mat4 *>(v);
         for (int i = 0; i < 16; ++i) {
             p->m[i] = a[i + idx];
         }
     }},
};

//NOLINTNEXTLINE
const std::unordered_map<gfx::Type, std::function<void(Float32Array &, const void *, index_t id)>> type2writer = {
    {gfx::Type::UNKNOWN, [](Float32Array & /*a*/, const void * /*v*/, index_t /*idx*/) {
         CC_LOG_ERROR("type2writer unknown type");
     }},
    {gfx::Type::INT, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const int32_t *>(v);
         a[idx]        = p[0];
     }},
    {gfx::Type::INT2, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const int32_t *>(v);
         a[idx]        = p[0];
         a[idx + 1]    = p[1];
     }},
    {gfx::Type::INT3, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const int32_t *>(v);
         a[idx]        = p[0];
         a[idx + 1]    = p[1];
         a[idx + 2]    = p[2];
     }},
    {gfx::Type::INT4, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const int32_t *>(v);
         a[idx]        = p[0];
         a[idx + 1]    = p[1];
         a[idx + 2]    = p[2];
         a[idx + 3]    = p[3];
     }},
    {gfx::Type::FLOAT, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const int32_t *>(v);
         a[idx]        = p[0];
     }},
    {gfx::Type::FLOAT2, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const int32_t *>(v);
         a[idx]        = p[0];
         a[idx + 1]    = p[1];
     }},
    {gfx::Type::FLOAT3, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const int32_t *>(v);
         a[idx]        = p[0];
         a[idx + 1]    = p[1];
         a[idx + 2]    = p[2];
     }},
    {gfx::Type::FLOAT4, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const int32_t *>(v);
         a[idx]        = p[0];
         a[idx + 1]    = p[1];
         a[idx + 2]    = p[2];
         a[idx + 3]    = p[3];
     }},
    {gfx::Type::MAT3, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const Mat3 *>(v);
         for (int i = 0; i < 9; ++i) {
             a[idx + i] = p->m[i];
         }
     }},
    {gfx::Type::MAT4, [](Float32Array &a, const void *v, index_t idx) {
         const auto *p = reinterpret_cast<const Mat4 *>(v);
         for (int i = 0; i < 16; ++i) {
             a[idx + i] = p->m[i];
         }
     }},
};

std::variant<std::vector<float>, std::string> getDefaultFromType(gfx::Type type) {
    switch (type) {
        case gfx::Type::BOOL:
        case gfx::Type::INT:
        case gfx::Type::UINT:
        case gfx::Type::FLOAT:
            return std::vector<float>{0};
        case gfx::Type::BOOL2:
        case gfx::Type::INT2:
        case gfx::Type::UINT2:
        case gfx::Type::FLOAT2:
            return std::vector<float>{0, 0};
        case gfx::Type::BOOL4:
        case gfx::Type::INT4:
        case gfx::Type::UINT4:
        case gfx::Type::FLOAT4:
            return std::vector<float>{0, 0, 0, 0};
        case gfx::Type::MAT4:
            return std::vector<float>{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        case gfx::Type::SAMPLER2D:
            return "default-texture";
        case gfx::Type::SAMPLER_CUBE:
            return "default-cube-texture";
        default:
            return std::vector<float>{0};
    }
}

bool overrideMacros(MacroRecord &target, const MacroRecord &source) {
    bool isDifferent = false;
    for (const auto &p : source) {
        if (target[p.first] != p.second) {
            target[p.first] = p.second;
            isDifferent     = true;
        }
    }
    return isDifferent;
}

}; // namespace cc
