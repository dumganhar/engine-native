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

#include <array>
#include "base/Macros.h"
#include "base/RefCounted.h"
#include "math/Color.h"

namespace cc {
namespace scene {

class Ambient;

class AmbientInfo : public RefCounted {
public:
    AmbientInfo(/* args */) = default;
    ~AmbientInfo() override = default;

    /**
     * @en Sky color
     * @zh 天空颜色
     */
    void                setSkyColor(const Color &val);
    inline const Color &getSkyColor() const { return _skyColor; }

    /**
     * @en Sky illuminance
     * @zh 天空亮度
     */
    void         setSkyIllum(float val);
    inline float getSkyIllum() const { return _skyIllum; }

    /**
     * @en Ground color
     * @zh 地面颜色
     */
    void                setGroundAlbedo(const Color &val);
    inline const Color &getGroundAlbedo() const { return _groundAlbedo; }
    void                activate(Ambient *resource);

    //cjh JSB need to bind the property, so need to make it public
    //private:
    Color    _skyColor{51, 128, 204, 1};
    float    _skyIllum{20000.0F};
    Color    _groundAlbedo{51, 51, 51, 255};
    Ambient *_resource{nullptr};
};

class Ambient final {
public:
    friend class Skybox;

    static constexpr float SUN_ILLUM{65000.0F};
    static constexpr float SKY_ILLUM{20000.0F};

    Ambient(/* args */) = default;
    ~Ambient()          = default;

    void initialize(AmbientInfo *info);

    inline const std::array<float, 4> &getColorArray() const { return _colorArray; }
    inline const std::array<float, 4> &getAlbedoArray() const { return _albedoArray; }

    /**
     * @en Enable ambient
     * @zh 是否开启环境光
     */
    inline void setEnabled(bool val) { _enabled = val; }
    inline bool isEnabled() const { return _enabled; }

    /**
     * @en Sky color
     * @zh 天空颜色
     */
    inline const Color &getSkyColor() const { return _skyColor; }
    inline void         setSkyColor(const Color &color) {
        _skyColor      = color;
        _colorArray[0] = static_cast<float>(color.r) / 255.F;
        _colorArray[1] = static_cast<float>(color.g) / 255.F;
        _colorArray[2] = static_cast<float>(color.b) / 255.F;
        _colorArray[3] = static_cast<float>(color.a) / 255.F;
    }

    /**
     * @en Sky illuminance
     * @zh 天空亮度
     */
    inline float getSkyIllum() const { return _skyIllum; }
    inline void  setSkyIllum(float illum) { _skyIllum = illum; }

    /**
     * @en Ground color
     * @zh 地面颜色
     */
    inline const Color &getGroundAlbedo() const { return _groundAlbedo; }
    inline void         setGroundAlbedo(const Color &color) {
        _groundAlbedo.set(color);
        _albedoArray[0] = static_cast<float>(_groundAlbedo.r) / 255.F;
        _albedoArray[1] = static_cast<float>(_groundAlbedo.g) / 255.F;
        _albedoArray[2] = static_cast<float>(_groundAlbedo.b) / 255.F;
        _albedoArray[3] = static_cast<float>(_groundAlbedo.a) / 255.F;
    }

protected:
    Color                _skyColor{51, 128, 204, 1};
    Color                _groundAlbedo{51, 51, 51, 255};
    bool                 _enabled{false};
    float                _skyIllum{0.F};
    std::array<float, 4> _colorArray{0.2F, 0.5F, 0.8F, 1.0F};
    std::array<float, 4> _albedoArray{0.2F, 0.2F, 0.2F, 1.0F};

    CC_DISALLOW_COPY_MOVE_ASSIGN(Ambient);
};

} // namespace scene
} // namespace cc
