#include "cocos/core/geometry/Distance.h"

#include "cocos/core/geometry/AABB.h"
#include "cocos/core/geometry/Obb.h"
#include "cocos/core/geometry/Plane.h"
#include "cocos/math/Mat4.h"
#include "cocos/math/Vec3.h"

#include <array>

namespace cc {
namespace geometry {

float pointPlane(const Vec3 &point, const Plane &plane) {
    return Vec3::dot(plane.n, point) - plane.d;
}

Vec3 *ptPointPlane(Vec3 *out, const Vec3 &point, const Plane &plane) {
    auto t = pointPlane(point, plane);
    *out   = point - t * plane.n;
    return out;
}

Vec3 *ptPointAabb(Vec3 *out, const Vec3 &point, const AABB &aabb) {
    *out     = point;
    auto min = aabb.getCenter() - aabb.getHalfExtents();
    auto max = aabb.getCenter() + aabb.getHalfExtents();

    out->x = (out->x < min.x) ? min.x : out->x;
    out->y = (out->y < min.y) ? min.y : out->y;
    out->z = (out->z < min.z) ? min.z : out->z;
    out->x = (out->x > max.x) ? max.x : out->x;
    out->y = (out->y > max.y) ? max.y : out->y;
    out->z = (out->z > max.z) ? max.z : out->z;
    return out;
}

Vec3 *ptPointObb(Vec3 *out, const Vec3 &point, const OBB &obb) {
    Vec3 xx = {obb.orientation.m[0], obb.orientation.m[1], obb.orientation.m[2]};
    Vec3 yy = {obb.orientation.m[3], obb.orientation.m[4], obb.orientation.m[5]};
    Vec3 zz = {obb.orientation.m[6], obb.orientation.m[7], obb.orientation.m[8]};

    std::array<Vec3, 3>  u = {xx, yy, zz};
    std::array<float, 3> e = {obb.halfExtents.x, obb.halfExtents.y, obb.halfExtents.z};

    auto d = point - obb.center;

    // Start result at center of obb; make steps from there
    *out = obb.center;

    // For each OBB axis...
    for (int i = 0; i < 3; i++) {
        // ...project d onto that axis to get the distance
        // along the axis of d from the obb center
        auto dist = Vec3::dot(d, u[i]);

        // if distance farther than the obb extents, clamp to the obb
        if (dist > e[i]) {
            dist = e[i];
        }
        if (dist < -e[i]) {
            dist = -e[i];
        }

        // Step that distance along the axis to get world coordinate
        out->x += dist * u[i].x;
        out->y += dist * u[i].y;
        out->z += dist * u[i].z;
    }
    return out;
}

Vec3 *ptPointLine(Vec3 *out, const Vec3 &point, const Vec3 &linePointA, const Vec3 &linePointB) {
    auto X                = linePointA - linePointB;
    auto dir              = X;
    auto dirSquaredLength = dir.lengthSquared();

    if (dirSquaredLength == 0) {
        // The point is at the segment start.
        *out = linePointA;
    } else {
        // Calculate the projection of the point onto the line extending through the segment.
        X      = point - linePointA;
        auto t = Vec3::dot(X, dir) / dirSquaredLength;

        if (t < 0) {
            // The point projects beyond the segment start.
            *out = linePointA;
        } else if (t > 1) {
            // The point projects beyond the segment end.
            *out = linePointB;
        } else {
            // The point projects between the start and end of the segment.
            *out = linePointA + dir * t;
        }
    }
    return out;
}

} // namespace geometry
} // namespace cc