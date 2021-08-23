
#include "cocos/core/geometry/Intersect.h"
#include "cocos/core/geometry/Ray.h"
#include "cocos/core/geometry/Sphere.h"
#include "cocos/math/Vec3.h"

#include <iostream>

using namespace cc; //NOLINT

int main(int argc, char **argv) {
    geometry::Ray    ray;
    geometry::Sphere sphere;
    auto             result = geometry::intersects(ray, sphere);
    std::cout << "intersects: " << result << std::endl;
    return 0;
}