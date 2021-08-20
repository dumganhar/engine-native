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

#include <vector>
#include <unordered_map>

#include "math/Vec2.h"
#include "core/platform/event-manager/Touch.h"


// const uint32_t TOUCH_TIMEOUT = macro.TOUCH_TIMEOUT;
namespace cc {

struct IView {
    float devicePixelRatio{1};
};

/**
 *  This class manages all events of input. include: touch, mouse, accelerometer, keyboard
 */
class InputManager final {
public:

    static InputManager& getInstance() { 
        static InputManager instance;
        return instance;
    }

    /**
     * Clear events when game is resumed.
     */
    void clearEvents() const;

    void frameDispatchEvents() const;

private:

    InputManager() = default;
    
    ~InputManager() = default;

    // #region Mouse Handle
    // void _dispatchMouseEvent(MouseInputEvent inputEvent);

    // void _dispatchTouchEvent (TouchInputEvent inputEvent);

    void handleTouchesStart(const std::vector<Touch>& touches) const;

    void handleTouchesMove(const std::vector<Touch>& touches) const;

    void handleTouchesEnd(const std::vector<Touch>& touches) const;

    void handleTouchesCancel(const std::vector<Touch>& touches) const;

    std::vector<Touch> getSetOfTouchesEndOrCancel(const std::vector<Touch>& touches) const;

    void setPreTouch(Touch touch);

    Touch getPreTouch(Touch touch) const;

    // TODO(PP): remove this private method
    void getViewPixelRatio() const;
    
    // Touch getTouch(MouseInputEvent inputEvent) const;

    // EventMouse getMouseEvent(MouseInputEvent inputEvent) const;

    // void getTouchList(TOuchInputEvent inputEvent);

    uint32_t getUnusedIndex() const;

    void removeUsedIndexBit(uint32_t index);

    void getUsefulTouches() const;
    // #endregion Touch Handle

    // #region Keyboard Handle
    // void dispatchKeyboardEvent(KeyboardEvent inputEvent);
    // #endregion Keyboard Handle

    // void dispatchAccelerometerEvent(AccelerometerEvent inputEvent);

    /**
     * Whether enable accelerometer event.
     */
    void setAccelerometer(bool isEnabled) const;

    /**
     * set accelerometer interval value in mile seconds
     * @method setAccelerometerInterval
     * @param {Number} intervalInMileSeconds
     */
    void setAccelerometerInterval(uint32_t intervalInMileSeconds) const;

    Vec2 _preTouchPoint; 
    Vec2 _prevMousePoint;
    std::vector<Touch> _prevTouchPool;
    uint32_t _preTouchPoolPointer{0};

    std::vector<Touch> _touches;
    std::unordered_map<uint32_t, uint32_t> _touchesIntegerDict;
    uint32_t _indexBitsUsed{0};
    uint32_t _maxTouches{0};

    IView* _glView{nullptr};
};

} // namespace cc
