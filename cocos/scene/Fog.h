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
#include "math/Color.h"

namespace cc {
namespace scene {

enum class FogType {
    /**
     * @zh
     * 线性雾。
     * @en
     * Linear fog
     * @readonly
     */
    LINEAR = 0,
    /**
     * @zh
     * 指数雾。
     * @en
     * Exponential fog
     * @readonly
     */
    EXP = 1,
    /**
     * @zh
     * 指数平方雾。
     * @en
     * Exponential square fog
     * @readonly
     */
    EXP_SQUARED = 2,
    /**
     * @zh
     * 层叠雾。
     * @en
     * Layered fog
     * @readonly
     */
    LAYERED = 3,
    NONE    = 4
};

class Fog;

class FogInfo final {
public:
    /**
     * @zh 是否启用全局雾效
     * @en Enable global fog
     */
    void        setEnabled(bool val);
    inline bool isEnabled() const { return _isEnabled; }

    /**
     * @zh 全局雾颜色
     * @en Global fog color
     */
    void                setFogColor(Color val);
    inline const Color &getFogColor() const { return _fogColor; }

    /**
     * @zh 全局雾类型
     * @en Global fog type
     */
    void           setType(FogType val);
    inline FogType getType() const { return _type; }

    /**
     * @zh 全局雾浓度
     * @en Global fog density
     */
    void         setFogDensity(float val);
    inline float getFogDensity() const { return _fogDensity; }

    /**
     * @zh 雾效起始位置，只适用于线性雾
     * @en Global fog start position, only for linear fog
     */
    void         setFogStart(float val);
    inline float getFogStart() const { return _fogStart; }

    /**
     * @zh 雾效结束位置，只适用于线性雾
     * @en Global fog end position, only for linear fog
     */
    void         setFogEnd(float val);
    inline float getFogEnd() const { return _fogEnd; }

    /**
     * @zh 雾效衰减
     * @en Global fog attenuation
     */
    void         setFogAtten(float val);
    inline float getFogAtten() const { return _fogAtten; }

    /**
     * @zh 雾效顶部范围，只适用于层级雾
     * @en Global fog top range, only for layered fog
     */
    void         setFogTop(float val);
    inline float getFogTop() const { return _fogTop; }

    /**
     * @zh 雾效范围，只适用于层级雾
     * @en Global fog range, only for layered fog
     */
    void         setFogRange(float val);
    inline float getFogRange() const { return _fogRange; }

    void activate(Fog *resource);

private:
    FogType _type{FogType::LINEAR};
    Color   _fogColor{200, 200, 200, 255};
    bool    _isEnabled{false};
    float   _fogDensity{0.3F};
    float   _fogStart{0.5F};
    float   _fogEnd{0.5F};
    float   _fogAtten{5.F};
    float   _fogTop{1.5F};
    float   _fogRange{1.2F};
    Fog *   _resource{nullptr};
};

class Fog final {
public:
    Fog()  = default;
    ~Fog() = default;

    void initialize(const FogInfo &fogInfo);

    inline void activate() { updatePipeline(); }

    /**
     * @zh 是否启用全局雾效
     * @en Enable global fog
     */
    inline void setEnabled(bool val) {
        _enabled = val;
        if (!val) {
            _type = FogType::NONE;
            updatePipeline();
        } else {
            activate();
        }
    }
    inline bool isEnabled() const { return _enabled; }

    /**
     * @zh 全局雾颜色
     * @en Global fog color
     */
    inline void setFogColor(const Color &val) {
        _fogColor.set(val);
        _colorArray[0] = val.r / 255.F;
        _colorArray[1] = val.g / 255.F;
        _colorArray[2] = val.b / 255.F;
        _colorArray[3] = val.a / 255.F;
    }
    inline const Color &getFogColor() const { return _fogColor; }

    /**
     * @zh 当前雾化类型。
     * @en The current global fog type.
     * @returns {FogType}
     * Returns the current global fog type
     * - -1:Disable global Fog
     * - 0:Linear fog
     * - 1:Exponential fog
     * - 2:Exponential square fog
     * - 3:Layered fog
     */
    inline FogType getType() const { return _type; }
    inline void    setType(FogType val) {
        _type = _enabled ? val : FogType::NONE;
        if (_enabled) {
            updatePipeline();
        }
    }

    /**
     * @zh 全局雾浓度
     * @en Global fog density
     */
    inline float getFogDensity() const { return _fogDensity; }
    inline void  setFogDensity(float val) { _fogDensity = val; }

    /**
     * @zh 雾效起始位置，只适用于线性雾
     * @en Global fog start position, only for linear fog
     */
    inline float getFogStart() const { return _fogStart; }
    inline void  setFogStart(float val) { _fogStart = val; }

    /**
     * @zh 雾效结束位置，只适用于线性雾
     * @en Global fog end position, only for linear fog
     */
    float getFogEnd() const { return _fogEnd; }
    void  setFogEnd(float val) { _fogEnd = val; }

    /**
     * @zh 雾效衰减
     * @en Global fog attenuation
     */
    inline float getFogAtten() const { return _fogAtten; }
    inline void  setFogAtten(float val) { _fogAtten = val; }

    /**
     * @zh 雾效顶部范围，只适用于层级雾
     * @en Global fog top range, only for layered fog
     */
    inline float getFogTop() const { return _fogTop; }

    inline void setFogTop(float val) { _fogTop = val; }

    /**
     * @zh 雾效范围，只适用于层级雾
     * @en Global fog range, only for layered fog
     */
    inline float getFogRange() const { return _fogRange; }
    inline void  setfogRange(float val) { _fogRange = val; }

    const std::array<float, 4> &getColorArray() const { return _colorArray; }

private:
    void updatePipeline();

    Color                _fogColor{200, 200, 200, 255};
    std::array<float, 4> _colorArray{0.2F, 0.2F, 0.2F, 1.0F};
    bool                 _enabled{false};
    FogType              _type{FogType::LINEAR};
    float                _fogDensity{0.3F};
    float                _fogStart{0.5F};
    float                _fogEnd{300.F};
    float                _fogAtten{5.F};
    float                _fogTop{1.5F};
    float                _fogRange{1.2F};

    CC_DISALLOW_COPY_MOVE_ASSIGN(Fog);
};

} // namespace scene
} // namespace cc
