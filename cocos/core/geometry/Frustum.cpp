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

#include "core/geometry/Frustum.h"
#include "scene/Define.h"

namespace cc {
namespace geometry {
namespace {
const std::vector<cc::Vec3> VEC_VALS{
    {1, 1, 1},
    {-1, 1, 1},
    {-1, -1, 1},
    {1, -1, 1},
    {1, 1, -1},
    {-1, 1, -1},
    {-1, -1, -1},
    {1, -1, -1}};
} // namespace

void Frustum::createOrtho(Frustum *out, float width,
                          float       height,
                          float       near,
                          float       far,
                          const Mat4 &transform) {
    auto halfWidth  = width / 2.0F;
    auto halfHeight = height / 2.0F;
    Vec3::transformMat4({halfWidth, halfHeight, near}, transform, &out->vertices[0]);
    Vec3::transformMat4({-halfWidth, halfHeight, near}, transform, &out->vertices[1]);
    Vec3::transformMat4({-halfWidth, -halfHeight, near}, transform, &out->vertices[2]);
    Vec3::transformMat4({halfWidth, -halfHeight, near}, transform, &out->vertices[3]);
    Vec3::transformMat4({halfWidth, halfHeight, far}, transform, &out->vertices[4]);
    Vec3::transformMat4({-halfWidth, halfHeight, far}, transform, &out->vertices[5]);
    Vec3::transformMat4({-halfWidth, -halfHeight, far}, transform, &out->vertices[6]);
    Vec3::transformMat4({halfWidth, -halfHeight, far}, transform, &out->vertices[7]);

    Plane::fromPoints(&out->planes[0], out->vertices[1], out->vertices[6], out->vertices[5]);
    Plane::fromPoints(&out->planes[1], out->vertices[3], out->vertices[4], out->vertices[7]);
    Plane::fromPoints(&out->planes[2], out->vertices[6], out->vertices[3], out->vertices[7]);
    Plane::fromPoints(&out->planes[3], out->vertices[0], out->vertices[5], out->vertices[4]);
    Plane::fromPoints(&out->planes[4], out->vertices[2], out->vertices[0], out->vertices[3]);
    Plane::fromPoints(&out->planes[5], out->vertices[7], out->vertices[5], out->vertices[6]);
}

void Frustum::update(const Mat4 &m, const Mat4 &inv) {
    // left plane
    planes[0].n.set(m.m[3] + m.m[0], m.m[7] + m.m[4], m.m[11] + m.m[8]);
    planes[0].d = -(m.m[15] + m.m[12]);
    // right plane
    planes[1].n.set(m.m[3] - m.m[0], m.m[7] - m.m[4], m.m[11] - m.m[8]);
    planes[1].d = -(m.m[15] - m.m[12]);
    // bottom plane
    planes[2].n.set(m.m[3] + m.m[1], m.m[7] + m.m[5], m.m[11] + m.m[9]);
    planes[2].d = -(m.m[15] + m.m[13]);
    // top plane
    planes[3].n.set(m.m[3] - m.m[1], m.m[7] - m.m[5], m.m[11] - m.m[9]);
    planes[3].d = -(m.m[15] - m.m[13]);
    // near plane
    planes[4].n.set(m.m[3] + m.m[2], m.m[7] + m.m[6], m.m[11] + m.m[10]);
    planes[4].d = -(m.m[15] + m.m[14]);
    // far plane
    planes[5].n.set(m.m[3] - m.m[2], m.m[7] - m.m[6], m.m[11] - m.m[10]);
    planes[5].d = -(m.m[15] - m.m[14]);

    if (getType() != ShapeEnum::SHAPE_FRUSTUM_ACCURATE) {
        return;
    }

    for (Plane &plane : planes) {
        float invDist = 1 / plane.n.length();
        plane.n *= invDist;
        plane.d *= invDist;
    }
    uint32_t i = 0;
    for (const Vec3 &vec : VEC_VALS) {
        vertices[i].transformMat4(vec, inv);
        i++;
    }
}

void Frustum::transform(const Mat4 &mat) {
    if (getType() != ShapeEnum::SHAPE_FRUSTUM_ACCURATE) {
        return;
    }
    for (auto i = 0; i < 8; i++) {
        vertices[i].transformMat4(vertices[i], mat);
    }
    Plane::fromPoints(&planes[0], vertices[1], vertices[5], vertices[6]);
    Plane::fromPoints(&planes[1], vertices[3], vertices[7], vertices[4]);
    Plane::fromPoints(&planes[2], vertices[6], vertices[7], vertices[3]);
    Plane::fromPoints(&planes[3], vertices[0], vertices[4], vertices[5]);
    Plane::fromPoints(&planes[4], vertices[2], vertices[3], vertices[0]);
    Plane::fromPoints(&planes[5], vertices[7], vertices[6], vertices[5]);
}

} // namespace geometry
} // namespace cc