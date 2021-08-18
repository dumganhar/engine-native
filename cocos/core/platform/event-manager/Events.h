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

#include "math/Vec2.h"
#include "core/event/Event.h"
#include "core/platform/event-manager/Acceleration.h"
#include "core/platform/event-manager/Touch.h"
#include "core/platform/event-manager/KeyCode.h"

namespace cc {

/**
 * @en
 * The acceleration event.
 * @zh
 * 加速计事件。
 */
class EventAccelerometer final : public event::Event {
public:
    /**
     * @param acc - The acceleration
     * @param bubbles - Indicate whether the event bubbles up through the hierarchy or not.
     */
    EventAccelerometer(Acceleration acc, bool bubbles);
    ~EventAccelerometer() = default;

    /**
     * @en The acceleration object
     * @zh 加速度对象
     */
    Acceleration acc;

};

/**
 * @en
 * The touch event.
 *
 * @zh
 * 触摸事件。
 */
class EventTouch final : public event::Event {
public:

    EventTouch() = default;
    ~EventTouch() = default;

    /**
     * @param touches - An array of current touches
     * @param bubbles - Indicate whether the event bubbles up through the hierarchy or not.
     * @param eventType - The type of the event
     */
    // EventKeyboard (std::vector<Touch> *changedTouches, bool bubbles, SystemEventTypeUnion eventType, std::vector<Touch> *touch);

    /**
     * @en Returns touches of event.
     * @zh 获取有变动的触摸点的列表。
     * 注意：第一根手指按下不动，接着按第二根手指，这时候触点信息就只有变动的这根手指（第二根手指）的信息。
     * 如果需要获取全部手指的信息，请使用 `getAllTouches`。
     */
    const std::vector<Touch *>& getTouches() const;

    /**
     * @en Returns touches of event.
     * @zh 获取所有触摸点的列表。
     * 注意：如果手指行为是 touch end，这个时候列表是没有该手指信息的。如需知道该手指信息，可通过 `getTouches` 获取识别。
     */
    const std::vector<Touch *>& getAllTouches() const;

    /**
     * @en Sets touch location.
     * @zh 设置当前触点位置
     * @param x - The current touch location on the x axis
     * @param y - The current touch location on the y axis
     */
    void setLocation(float x, float y);

    /**
     * @en Returns the current touch location.
     * @zh 获取触点位置。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getLocation() const;

    /**
     * @en Returns the current touch location in UI coordinates.
     * @zh 获取 UI 坐标系下的触点位置。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getUILocation() const;

    /**
     * @en Returns the current touch location in game screen coordinates.
     * @zh 获取当前触点在游戏窗口中的位置。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getLocationInView() const;

    /**
     * @en Returns the previous touch location.
     * @zh 获取触点在上一次事件时的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getPreviousLocation() const;

    /**
     * @en Returns the start touch location.
     * @zh 获取触点落下时的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getStartLocation() const;

    /**
     * @en Returns the start touch location in UI coordinates.
     * @zh 获取触点落下时的 UI 世界下位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getUIStartLocation() const;

    /**
     * @en Returns the id of the current touch point.
     * @zh 获取触点的标识 ID，可以用来在多点触摸中跟踪触点。
     */
    uint32_t getID() const;

    /**
     * @en Returns the delta distance from the previous location to current location.
     * @zh 获取触点距离上一次事件移动的距离对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getDelta() const;

    /**
     * @en Returns the delta distance from the previous location to current location.
     * @zh 获取触点距离上一次事件 UI 世界下移动的距离对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
    */
    const Vec2& getUIDelta() const;

    /**
     * @en Returns the X axis delta distance from the previous location to current location.
     * @zh 获取触点距离上一次事件移动的 x 轴距离。
     */
    float getDeltaX() const;

    /**
     * @en Returns the Y axis delta distance from the previous location to current location.
     * @zh 获取触点距离上一次事件移动的 y 轴距离。
     */
    float getDeltaY() const;

    /**
     * @en Returns location X axis data.
     * @zh 获取当前触点 X 轴位置。
     */
    float getLocationX() const;

    /**
     * @en Returns location Y axis data.
     * @zh 获取当前触点 Y 轴位置。
     */
    float getLocationY() const;

    /**
     * @en The maximum touch point numbers simultaneously
     * @zh 同时存在的最大触点数量。
     */
    static uint32_t MAX_TOUCHES;

    /**
     * @en The current touch object
     * @zh 当前触点对象
     */
    Touch* touch;

    /**
     * @en Indicate whether the touch event is simulated or real
     * @zh 表示触摸事件是真实触点触发的还是模拟的
     */
    bool simulate{false};

private:
    std::vector<Touch *> _touches;
    std::vector<Touch *> _allTouches;

};

/**
 * @en
 * The keyboard event.
 * @zh
 * 键盘事件。
 */
class EventKeyboard final : public event::Event {
public:

    /**
     * @param keyCode - The key code of the current key or the DOM KeyboardEvent
     * @param isPressed - Indicates whether the current key is being pressed, this is the DEPRECATED parameter.
     * @param bubbles - Indicates whether the event bubbles up through the hierarchy or not.
     */
    // constructor (keyCode: number | KeyboardEvent, isPressed: boolean, bubbles?: boolean);
    EventKeyboard (uint32_t keyCode, bool isPressed, bool bubbles);

    /**
     * @param keyCode - The key code of the current key or the DOM KeyboardEvent
     * @param eventType - The type of the event
     * @param bubbles - Indicates whether the event bubbles up through the hierarchy or not.
     */
    // constructor (keyCode: KeyCode | KeyboardEvent, eventType: SystemEventTypeUnion, bubbles?: boolean);
    // EventKeyboard (KeyCode keyCode, SystemEventType eventType, bool bubbles);

    ~EventKeyboard() = default;

    /**
     * @en The KeyCode enum value of current keyboard event.
     * @zh 当前键盘事件的 KeyCode 枚举值
     */
    event_manager::KeyCode keyCode;

    /**
     * @en Indicates whether the current key is being pressed
     * @zh 表示当前按键是否正在被按下
     *
     * @deprecated since v3.3, please use Event.prototype.type !== SystemEvent.EventType.KEY_UP instead
     */
    inline bool isPressed() const{
        return _isPressed;
    }

private:
    bool _isPressed{false};

};

/**
 * @en The mouse event
 * @zh 鼠标事件类型
 */
class EventMouse final : public event::Event {
public:

    EventMouse() = default;
    ~EventMouse() = default;

    /**
     * @param eventType - The type of the event
     * @param bubbles - Indicate whether the event bubbles up through the hierarchy or not.
     */
    // EventMouse(SystemEventTypeUnion eventType, bool bubbles, Vec2 prevLoc);

    /**
     * @en Sets scroll data of the mouse.
     * @zh 设置鼠标滚轮的滚动数据。
     * @param scrollX - The scroll value on x axis
     * @param scrollY - The scroll value on y axis
     */
    void setScrollData(float scrollX, float scrollY);

    /**
     * @en Returns the scroll value on x axis.
     * @zh 获取鼠标滚动的 X 轴距离，只有滚动时才有效。
     */
    float getScrollX() const;

    /**
     * @en Returns the scroll value on y axis.
     * @zh 获取滚轮滚动的 Y 轴距离，只有滚动时才有效。
     */
    float getScrollY() const;

    /**
     * @en Sets cursor location.
     * @zh 设置当前鼠标位置。
     * @param x - The location on x axis
     * @param y - The location on y axis
     */
    void setLocation(float x, float y);

    /**
     * @en Returns cursor location.
     * @zh 获取鼠标相对于左下角位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getLocation() const;

    /**
     * @en Returns the current touch location in UI coordinates.
     * @zh 获取 UI 坐标系下的触点位置。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getUILocation() const;

    /**
     * @en Returns the current touch location in game screen coordinates.
     * @zh 获取当前触点在游戏窗口中的位置。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getLocationInView() const;

    /**
     * @en Returns the previous touch location.
     * @zh 获取触点在上一次事件时的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getPreviousLocation() const;

    /**
     * @en Returns the start touch location.
     * @zh 获取触点落下时的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getStartLocation() const;

    /**
     * @en Returns the start touch location in UI coordinates.
     * @zh 获取触点落下时的 UI 世界下位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getUIStartLocation() const;

    /**
     * @en Returns the id of the current touch point.
     * @zh 获取触点的标识 ID，可以用来在多点触摸中跟踪触点。
     */
    uint32_t getID() const;

    /**
     * @en Returns the delta distance from the previous location to current location.
     * @zh 获取触点距离上一次事件移动的距离对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getDelta() const;

    /**
     * @en Returns the delta distance from the previous location to current location.
     * @zh 获取触点距离上一次事件 UI 世界下移动的距离对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
    */
    const Vec2& getUIDelta() const;

    /**
     * @en Returns the X axis delta distance from the previous location to current location.
     * @zh 获取触点距离上一次事件移动的 x 轴距离。
     */
    float getDeltaX() const;

    /**
     * @en Returns the Y axis delta distance from the previous location to current location.
     * @zh 获取触点距离上一次事件移动的 y 轴距离。
     */
    float getDeltaY() const;

    /**
     * @en Returns location X axis data.
     * @zh 获取当前触点 X 轴位置。
     */
    float getLocationX() const;

    /**
     * @en Returns location Y axis data.
     * @zh 获取当前触点 Y 轴位置。
     */
    float getLocationY() const;

    /**
     * @en The default tag when no button is pressed
     * @zh 按键默认的缺省状态
     */
    static const int32_t BUTTON_MISSING{-1};

    /**
     * @en The tag of mouse's left button.
     * @zh 鼠标左键的标签。
     */
    static const int32_t BUTTON_LEFT{0};

    /**
     * @en The tag of mouse's middle button.
     * @zh 鼠标中键的标签。
     */
    static const int32_t BUTTON_MIDDLE{1};

    /**
     * @en The tag of mouse's right button  (The right button number is 2 on browser).
     * @zh 鼠标右键的标签。
     */
    static const int32_t BUTTON_RIGHT{2};

    /**
     * @en The tag of mouse's button 4.
     * @zh 鼠标按键 4 的标签。
     */
    static const int32_t BUTTON_4{3};

    /**
     * @en The tag of mouse's button 5.
     * @zh 鼠标按键 5 的标签。
     */
    static const int32_t BUTTON_5{4};

    /**
     * @en The tag of mouse's button 6.
     * @zh 鼠标按键 6 的标签。
     */
    static const int32_t BUTTON_6{5};

    /**
     * @en The tag of mouse's button 7.
     * @zh 鼠标按键 7 的标签。
     */
    static const int32_t BUTTON_7{6};

    /**
     * @en The tag of mouse's button 8.
     * @zh 鼠标按键 8 的标签。
     */
    static const int32_t BUTTON_8{7};

    /**
     * @en Mouse movement on x axis of the UI coordinate system.
     * @zh 鼠标在 UI 坐标系下 X 轴上的移动距离
     */
    float movementX{0};

    /**
     * @en Mouse movement on y axis of the UI coordinate system.
     * @zh 鼠标在 UI 坐标系下 Y 轴上的移动距离
     */
    float movementY{0};

    /**
     * @en The type of the event
     * @zh 鼠标事件类型
     *
     * @deprecated since v3.3, please use EventMouse.prototype.type instead.
     */
    // public get eventType () {
    //     return this._eventType;
    // }

private:
    // SystemEventTypeUnion _eventType;
    
    int32_t _button{EventMouse::BUTTON_MISSING};

    float _x{0};

    float _y{0};

    float _prevX{0};

    float _prevY{0};

    float _scrollX{0};

    float _scrollY{0};

};

} // namespace cc
