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
#include "primitive/Primitive.h"
#include "3d/misc/CreateMesh.h"

namespace cc {

Primitive::Primitive(PrimitiveType t /* = PrimitiveType.BOX*/)
: Mesh(), type(t) {
}

void Primitive::onLoaded() {
    createMesh(create(type), this);
}

IGeometry create(PrimitiveType type, const std::optional<std::variant<IBoxOptions /*, ICapsuleOptions, ..., ...*/>> &options) {
    switch (type) {
        case PrimitiveType::BOX: {
            return options.has_value() ? cc::box(std::get<IBoxOptions>(options.value())) : cc::box();
            break;
        }
        case PrimitiveType::SPHERE: {
            //return cc::sphere();
            break;
        }
        case PrimitiveType::CYLINDER: {
            //return cc::cylinder();
            break;
        }
        case PrimitiveType::CONE: {
            //return cc::cone();
            break;
        }
        case PrimitiveType::CAPSULE: {
            //return cc::capsule();
            break;
        }
        case PrimitiveType::TORUS: {
            //return cc::torus();
            break;
        }
        case PrimitiveType::QUAD: {
            //return cc::quad();
            break;
        }
        default:
            break;
    }
    return cc::box();
}

} // namespace cc
