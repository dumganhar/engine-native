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
#include "core/scene-graph/SceneGlobal.h"
#include "math/Color.h"
#include "base/Macros.h"

namespace cc {
namespace scene {

class Ambient final {
public:
    static constexpr float SUN_ILLUM{65000.0F};
    static constexpr float SKY_ILLUM{20000.0F};

    Ambient(/* args */) = default;
    ~Ambient()          = default;
    
    void initialize(scenegraph::AmbientInfo *info);

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
        _skyColor = color;
        _colorArray[0] = color.r / 255;
        _colorArray[1] = color.g / 255;
        _colorArray[2] = color.b / 255;
        _colorArray[3] = color.a / 255;
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
    inline void         setGroundAlbedo(const Color &color) { _groundAlbedo.set(color); }

protected:
    Color                _skyColor{51, 128, 204, 1.0};
    Color                _groundAlbedo{51, 51, 51, 255};
    bool                 _enabled{false};
    float                _skyIllum{0.F};
    std::array<float, 4> _colorArray;
    std::array<float, 4> _albedoArray;
    
    CC_DISALLOW_COPY_MOVE_ASSIGN(Ambient);
};

} // namespace scene
} // namespace cc
