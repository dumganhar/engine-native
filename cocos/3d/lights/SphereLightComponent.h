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

#include "3d/lights/LightComponent.h"
#include "scene/SphereLight.h"

namespace cc {
class SphereLight final : public Light {
public:
    using Super = Light;
    SphereLight();
    ~SphereLight() override;

    /**
     * @en Luminous flux of the light.
     * @zh 光通量。
     */
    inline float getLuminousFlux() const { return _luminance * scene::Light::nt2lm(_size); }
    inline void  setLuminousFlux(float val) {
        _luminance = val / scene::Light::nt2lm(_size);
        if (_light != nullptr) static_cast<scene::SphereLight *>(_light)->setLuminance(_luminance);
    }

    /**
     * @en Luminance of the light.
     * @zh 光亮度。
     */
    inline float getLuminance() const { return _luminance; }
    inline void  setLuminance(float val) {
        _luminance = val;
        if (_light != nullptr) static_cast<scene::SphereLight *>(_light)->setLuminance(val);
    };

    /**
     * @en The photometric term currently being used.
     * @zh 当前使用的光度学计量单位。
     */
    inline PhotometricTerm getTerm() const { return _term; }
    inline void            setTerm(PhotometricTerm val) { _term = val; }

    /**
     * @en
     * Size of the light.
     * @zh
     * 光源大小。
     */
    inline float getSize() const { return _size; }
    inline void  setSize(float val) {
        _size = val;
        if (_light != nullptr) static_cast<scene::SphereLight *>(_light)->setSize(val);
    }

    /**
     * @en
     * Range of the light.
     * @zh
     * 光源范围。
     */
    inline float getRange() const { return _range; }
    inline void  setRange(float val) {
        _range = val;
        if (_light != nullptr) static_cast<scene::SphereLight *>(_light)->setRange(val);
    }

protected:
    void createLight() override;
    //TODO(xwx): need @serializable
    float _size{0.15F};
    //TODO(xwx): need @serializable
    float _luminance{1700.F / scene::Light::nt2lm(0.15F)};
    //TODO(xwx): need @serializable
    PhotometricTerm _term{PhotometricTerm::LUMINOUS_FLUX};
    //TODO(xwx): need @serializable
    float _range{1.F};

    scene::LightType _type{scene::LightType::SPHERE};

private:
    CC_DISALLOW_COPY_MOVE_ASSIGN(SphereLight);
};
} // namespace cc