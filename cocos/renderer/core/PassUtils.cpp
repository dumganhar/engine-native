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
#include <boost/variant/variant_fwd.hpp>
namespace cc {

//NOLINTNEXTLINE
const std::unordered_map<gfx::Type, GFXTypeReaderCallback> type2reader = {
    {gfx::Type::UNKNOWN, [](const float * /*a*/, MaterialProperty & /*v*/, index_t /*idx*/) {
         CC_LOG_ERROR("type2reader unknown type");
     }},
    {gfx::Type::INT, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(int32_t)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<int32_t>(&v);
         CC_ASSERT(p != nullptr);
         p[0] = a[idx];
     }},
    {gfx::Type::INT2, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec2)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<Vec2>(&v);
         CC_ASSERT(p != nullptr);
         p->x = a[idx];
         p->y = a[idx + 1];
     }},
    {gfx::Type::INT3, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec3)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<Vec3>(&v);
         CC_ASSERT(p != nullptr);
         p->x = a[idx];
         p->y = a[idx + 1];
         p->z = a[idx + 2];
     }},
    {gfx::Type::INT4, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec4)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<Vec4>(&v);
         CC_ASSERT(p != nullptr);
         p->x = a[idx];
         p->y = a[idx + 1];
         p->z = a[idx + 2];
         p->w = a[idx + 3];
     }},
    {gfx::Type::FLOAT, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(float)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<float>(&v);
         CC_ASSERT(p != nullptr);
         p[0] = a[idx];
     }},
    {gfx::Type::FLOAT2, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec2)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<Vec2>(&v);
         CC_ASSERT(p != nullptr);
         p->x = a[idx];
         p->y = a[idx + 1];
     }},
    {gfx::Type::FLOAT3, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec3)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<Vec3>(&v);
         CC_ASSERT(p != nullptr);
         p->x = a[idx];
         p->y = a[idx + 1];
         p->z = a[idx + 2];
     }},
    {gfx::Type::FLOAT4, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec4)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<Vec4>(&v);
         CC_ASSERT(p != nullptr);
         p->x = a[idx];
         p->y = a[idx + 1];
         p->z = a[idx + 2];
         p->w = a[idx + 3];
     }},
    {gfx::Type::MAT3, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Mat3)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<Mat3>(&v);
         CC_ASSERT(p != nullptr);
         memcpy(&p->m[0], &a[idx], sizeof(Mat3));
     }},
    {gfx::Type::MAT4, [](const float *a, MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Mat4)) {
             CC_ASSERT(false);
         }
         auto *p = boost::get<Mat4>(&v);
         CC_ASSERT(p != nullptr);
         memcpy(&p->m[0], &a[idx], sizeof(Mat4));
     }},
};

//NOLINTNEXTLINE
const std::unordered_map<gfx::Type, GFXTypeWriterCallback> type2writer = {
    {gfx::Type::UNKNOWN, [](float * /*a*/, const MaterialProperty & /*v*/, index_t /*idx*/) {
         CC_LOG_ERROR("type2writer unknown type");
     }},
    {gfx::Type::INT, [](float *a, const MaterialProperty &v, index_t idx) {
         const int32_t *p      = nullptr;
         const float *  pFloat = nullptr;
         if (v.type() == typeid(int32_t)) {
             p = boost::get<int32_t>(&v);
             a[idx] = static_cast<float>(*p);
         } else if (v.type() == typeid(float)) {
             pFloat = boost::get<float>(&v);
             a[idx] = *pFloat;
         }
         CC_ASSERT(p != nullptr || pFloat != nullptr);
     }},
    {gfx::Type::INT2, [](float *a, const MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec2)) {
             CC_ASSERT(false);
         }
         const auto *p = boost::get<Vec2>(&v);
         CC_ASSERT(p != nullptr);
         a[idx]     = p->x;
         a[idx + 1] = p->y;
     }},
    {gfx::Type::INT3, [](float *a, const MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec3)) {
             CC_ASSERT(false);
         }
         const auto *p = boost::get<Vec3>(&v);
         CC_ASSERT(p != nullptr);
         a[idx]     = p->x;
         a[idx + 1] = p->y;
         a[idx + 2] = p->z;
     }},
    {gfx::Type::INT4, [](float *a, const MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec4)) {
             CC_ASSERT(false);
         }
         const auto *p = boost::get<Vec4>(&v);
         CC_ASSERT(p != nullptr);
         a[idx]     = p->x;
         a[idx + 1] = p->y;
         a[idx + 2] = p->z;
         a[idx + 3] = p->w;
     }},
    {gfx::Type::FLOAT, [](float *a, const MaterialProperty &v, index_t idx) {
         const float *  p    = nullptr;
         const int32_t *pInt = nullptr;
         if (v.type() == typeid(float)) {
             p = boost::get<float>(&v);
             a[idx] = *p;
         } else if (v.type() == typeid(int32_t)) {
             pInt = boost::get<int32_t>(&v);
             a[idx] = static_cast<float>(*pInt);
         }
         CC_ASSERT(p != nullptr || pInt != nullptr);
     }},
    {gfx::Type::FLOAT2, [](float *a, const MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Vec2)) {
             CC_ASSERT(false);
         }
         const auto *p = boost::get<Vec2>(&v);
         CC_ASSERT(p != nullptr);
         a[idx]     = p->x;
         a[idx + 1] = p->y;
     }},
    {gfx::Type::FLOAT3, [](float *a, const MaterialProperty &v, index_t idx) {
         if (typeid(Vec3) == v.type()) {
             const auto &vec3 = boost::get<Vec3>(v);
             a[idx]           = vec3.x;
             a[idx + 1]       = vec3.y;
             a[idx + 2]       = vec3.z;
         } else if (typeid(Vec4) == v.type()) {
             const auto &vec4 = boost::get<Vec4>(v);
             a[idx]           = vec4.x;
             a[idx + 1]       = vec4.y;
             a[idx + 2]       = vec4.z;
         } else {
             assert(false);
         }
     }},
    {gfx::Type::FLOAT4, [](float *a, const MaterialProperty &v, index_t idx) {
         if (typeid(Vec4) == v.type()) {
             const auto &vec4 = boost::get<Vec4>(v);
             a[idx]           = vec4.x;
             a[idx + 1]       = vec4.y;
             a[idx + 2]       = vec4.z;
             a[idx + 3]       = vec4.w;
         } else if (typeid(Color) == v.type()) {
             const auto &color = boost::get<Color>(v);
             Vec4        colorFloat{color.toVec4()};
             a[idx]     = colorFloat.x;
             a[idx + 1] = colorFloat.y;
             a[idx + 2] = colorFloat.z;
             a[idx + 3] = colorFloat.w;
         } else if (typeid(Quaternion) == v.type()) {
             const auto &quat = boost::get<Quaternion>(v);
             a[idx]           = quat.x;
             a[idx + 1]       = quat.y;
             a[idx + 2]       = quat.z;
             a[idx + 3]       = quat.w;
         } else {
             assert(false);
         }
     }},
    {gfx::Type::MAT3, [](float *a, const MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Mat3)) {
             CC_ASSERT(false);
         }
         const auto *p = boost::get<Mat3>(&v);
         CC_ASSERT(p != nullptr);
         memcpy(&a[idx], &p->m[0], sizeof(Mat3));
     }},
    {gfx::Type::MAT4, [](float *a, const MaterialProperty &v, index_t idx) {
         if (v.type() != typeid(Mat4)) {
             CC_ASSERT(false);
         }
         const auto *p = boost::get<Mat4>(&v);
         CC_ASSERT(p != nullptr);
         memcpy(&a[idx], &p->m[0], sizeof(Mat4));
     }},
};

const std::vector<float> &getDefaultFloatArrayFromType(gfx::Type type) {
    static const std::vector<float> defaultFloatValues[] = {
        {0},
        {0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};

    switch (type) {
        case gfx::Type::BOOL:
        case gfx::Type::INT:
        case gfx::Type::UINT:
        case gfx::Type::FLOAT:
            return defaultFloatValues[0];
        case gfx::Type::BOOL2:
        case gfx::Type::INT2:
        case gfx::Type::UINT2:
        case gfx::Type::FLOAT2:
            return defaultFloatValues[1];
        case gfx::Type::BOOL4:
        case gfx::Type::INT4:
        case gfx::Type::UINT4:
        case gfx::Type::FLOAT4:
            return defaultFloatValues[2];
        case gfx::Type::MAT4:
            return defaultFloatValues[3];
        default:
            return defaultFloatValues[0];
    }
}

const std::string &getDefaultStringFromType(gfx::Type type) {
    static const std::string defaultTextureStr{"default-texture"};
    static const std::string defaultCubeTextureStr{"default-cube-texture"};

    switch (type) {
        case gfx::Type::SAMPLER2D:
            return defaultTextureStr;
        case gfx::Type::SAMPLER_CUBE:
            return defaultCubeTextureStr;
        default:
            return defaultTextureStr;
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
