#include "cocos/core/geometry/Capsule.h"
#include "cocos/math/Vec3.h"
namespace cc {
namespace geometry {

void Capsule::transform(const Mat4 &m, const Vec3 & /*pos*/, const Quaternion &rot, const Vec3 &scale, Capsule *out) const {
    const auto ws = scale;
    const auto s  = mathutils::absMaxComponent(ws);
    out->radius   = this->radius * abs(s);

    const auto halfTotalWorldHeight = (this->halfHeight + this->radius) * abs(ws.y);
    auto       halfWorldHeight      = halfTotalWorldHeight - out->radius;
    if (halfWorldHeight < 0) halfWorldHeight = 0;
    out->halfHeight = halfWorldHeight;

    out->center.transformMat4(this->center, m);
    // Quat::multiply(out.rotation, this->rotation, rot);
    Quaternion::multiply(this->rotation, rot, &out->rotation);
    out->updateCache();
}

void Capsule::updateCache() {
    updateLocalCenter();
    ellipseCenter0.transformQuat(this->rotation);
    ellipseCenter1.transformQuat(this->rotation);
    ellipseCenter0.add(center);
    ellipseCenter1.add(center);
}

void Capsule::updateLocalCenter() {
    switch (axis) {
        case CenterEnum::X:
            ellipseCenter0.set(halfHeight, 0, 0);
            ellipseCenter1.set(-halfHeight, 0, 0);
            break;
        case CenterEnum::Y:
            ellipseCenter0.set(0, halfHeight, 0);
            ellipseCenter1.set(0, -halfHeight, 0);
            break;
        case CenterEnum::Z:
            ellipseCenter0.set(0, 0, halfHeight);
            ellipseCenter1.set(0, 0, -halfHeight);
            break;
        default:
            assert(false);
    }
}
} // namespace geometry
} // namespace cc