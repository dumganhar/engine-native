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
#include "scene/DirectionalLight.h"

namespace cc {

class DirectionalLight final : public Light {
public:
    using Super = Light;
    DirectionalLight();
    ~DirectionalLight() override = default;

    /**
     * @en
     * The light source intensity.
     * @zh
     * 光源强度。
     */
    inline float getIlluminance() const { return _illuminance; }
    inline void  setIlluminance(float val) {
        _illuminance = val;
        if (_light != nullptr) {
            static_cast<scene::DirectionalLight *>(_light)->setIlluminance(val);
        }
    };

protected:
    void createLight() override;

    //TODO(xwx): _illuminance @serializable
    float _illuminance{65000.F};

private:
    CC_DISALLOW_COPY_MOVE_ASSIGN(DirectionalLight);
};

} // namespace cc
