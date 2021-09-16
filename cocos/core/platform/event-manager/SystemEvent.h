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

#include <unordered_map>

#include "core/event/EventEmitter.h"
#include "core/platform/event-manager/EventEnum.h"
#include "core/platform/event-manager/Events.h"
#include "core/platform/event-manager/Touch.h"

namespace cc {

/**
* @en
* The System event, it currently supports keyboard events and accelerometer events.<br/>
* You can get the `SystemEvent` instance with `systemEvent`.<br/>
* @zh
* 系统事件，它目前支持按键事件和重力感应事件。<br/>
* 你可以通过 `systemEvent` 获取到 `SystemEvent` 的实例。<br/>
* @example
* ```
* import { systemEvent, SystemEvent } from 'cc';
* systemEvent.on(SystemEvent.EventType.DEVICEMOTION, this.onDeviceMotionEvent, this);
* systemEvent.off(SystemEvent.EventType.DEVICEMOTION, this.onDeviceMotionEvent, this);
* ```
*/
class SystemEvent final : public EventEmitter {
public:
    using EventType = SystemEventType;

    using EventMouseCallback        = std::function<void(const EventMouse &)>;
    using EventTouchCallback        = std::function<void(const EventTouch &)>;
    using TouchEventTouchCallback   = std::function<void(const Touch &, const EventTouch &)>;
    using EventKeyboardCallback     = std::function<void(const EventKeyboard &)>;
    using EventAccelerationCallback = std::function<void(const EventAcceleration &)>;

    // void on(SystemEventType event, MouseEventCallback cb);
    /**
    * @en The singleton of the SystemEvent, there should only be one instance to be used globally
    * @zh 系统事件单例，方便全局使用。
    */
    static SystemEvent &getInstance() {
        static SystemEvent instance;
        return instance;
    }

    /**
     * @en
     * Sets whether to enable the accelerometer event listener or not.
     *
     * @zh
     * 是否启用加速度计事件。
     */
    void setAccelerometerEnabled(bool isEnabled) const;

    /**
     * @en
     * Sets the accelerometer interval value.
     *
     * @zh
     * 设置加速度计间隔值。
     */
    void setAccelerometerInterval(uint32_t interval) const;

    /**
     * @en
     * Register an callback of a specific system event type.
     * @zh
     * 注册特定事件类型回调。
     *
     * @param type - The event type
     * @param callback - The event listener's callback
     * @param target - The event listener's target and callee
     */
    // @ts-expect-error Property 'on' in type 'SystemEvent' is not assignable to the same property in base type
    // public on<K extends keyof SystemEventMap> (type: K, callback: SystemEventMap[K], target?: any, once?: boolean)
    void on(EventType event, EventMouseCallback cb);
    void on(EventType event, EventTouchCallback cb);
    void on(EventType event, TouchEventTouchCallback cb);
    void on(EventType event, EventKeyboardCallback cb);
    void on(EventType event, EventAccelerationCallback cb);

    /**
     * @en
     * Removes the listeners previously registered with the same type, callback, target and or useCapture,
     * if only type is passed as parameter, all listeners registered with that type will be removed.
     * @zh
     * 删除之前用同类型，回调，目标或 useCapture 注册的事件监听器，如果只传递 type，将会删除 type 类型的所有事件监听器。
     *
     * @param type - A string representing the event type being removed.
     * @param callback - The callback to remove.
     * @param target - The target (this object) to invoke the callback, if it's not given, only callback without target will be removed
     */
    // public off<K extends keyof SystemEventMap> (type: K, callback?: SystemEventMap[K], target?: any)
    void off(EventType event, EventMouseCallback cb);
    void off(EventType event, EventTouchCallback cb);
    void off(EventType event, TouchEventTouchCallback cb);
    void off(EventType event, EventKeyboardCallback cb);
    void off(EventType event, EventAccelerationCallback cb);

private:
    SystemEvent()  = default;
    ~SystemEvent() = default;
};
} // namespace cc
