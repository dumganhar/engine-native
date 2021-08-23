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

#include <any>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "core/components/Component.h"
#include "core/platform/event-manager/Acceleration.h"
#include "core/platform/event-manager/Events.h"
#include "core/scene-graph/Node.h"

namespace cc {
namespace event_listener {

struct IEventListenerCreateInfo {
    int32_t                                   event;
    std::unordered_map<std::string, std::any> x;
};

struct IListenerMask {
    int32_t               index{0};
    components::Component comp;
};

class EventListener {
public:
    // ts: constructor (type: number, listenerID: string, callback: ((...args: any[]) => any) | null)
    // EventListener(int32_t event, std::string listenerID, cb);

    virtual ~EventListener() = default;

    /**
     * to cache camera priority
     * @internal
     */
    const int32_t _cameraPriority{0};
    /**
     * @en The type code of unknown event listener.<br/>
     * @zh 未知的事件监听器类型
     */
    static const int32_t UNKNOWN{0};

    /**
     * @en The type code of one by one touch event listener.<br/>
     * @zh 触摸事件监听器类型，触点会一个一个得分开被派发
     */
    static const int32_t TOUCH_ONE_BY_ONE{1};

    /**
     * @en The type code of all at once touch event listener.<br/>
     * @zh 触摸事件监听器类型，触点会被一次性全部派发
     */
    static const int32_t TOUCH_ALL_AT_ONCE{2};

    /**
     * @en The type code of keyboard event listener.<br/>
     * @zh 键盘事件监听器类型
     */
    static const int32_t KEYBOARD{3};

    /**
     * @en The type code of mouse event listener.<br/>
     * @zh 鼠标事件监听器类型
     */
    static const int32_t MOUSE{4};

    /**
     * @en The type code of acceleration event listener.<br/>
     * @zh 加速器事件监听器类型
     */
    static const int32_t ACCELERATION{6};

    /**
     * @en The type code of custom event listener.<br/>
     * @zh 自定义事件监听器类型
     */
    static const int32_t CUSTOM{8};

    enum class ListenerID {
        MOUSE,
        TOUCH_ONE_BY_ONE,
        TOUCH_ALL_AT_ONCE,
        KEYBOARD,
        ACCELRATION,
    };

    /**
     * @en Create a EventListener object with configuration including the event type, handlers and other parameters.<br/>
     * In handlers, this refer to the event listener object itself.<br/>
     * You can also pass custom parameters in the configuration object,<br/>
     * all custom parameters will be polyfilled into the event listener object and can be accessed in handlers.<br/>
     * @zh 通过指定不同的 Event 对象来设置想要创建的事件监听器。
     * @param argObj a json object
     */
    EventListener static create(IEventListenerCreateInfo* argObj);

    // hack: How to solve the problem of uncertain attribute
    // callback's this object
    std::any owner{nullptr};

    std::vector<IListenerMask*> mask;

    bool _previousIn{false};

    std::any _target{nullptr};

    // auto getOnEvent(){
    //     return _onEvent();
    // }

    /**
     * @en
     * <p><br/>
     *     Sets paused state for the listener<br/>
     *     The paused state is only used for scene graph priority listeners.<br/>
     *     `EventDispatcher.resumeAllEventListenersForTarget(node)` will set the paused state to `true`,<br/>
     *     while `EventDispatcher.pauseAllEventListenersForTarget(node)` will set it to `false`.<br/>
     *     @note 1) Fixed priority listeners will never get paused. If a fixed priority doesn't want to receive events,<br/>
     *              call `setEnabled(false)` instead.<br/>
     *            2) In `Node`'s onEnter and onExit, the `paused state` of the listeners<br/>
     *              which associated with that node will be automatically updated.<br/>
     * </p><br/>
     * @zh
     * *为侦听器设置暂停状态<br/>
     * 暂停状态仅用于场景图优先级侦听器。<br/>
     * `EventDispatcher :: resumeAllEventListenersForTarget（node）`将暂停状态设置为`true`，<br/>
     * 而`EventDispatcher :: pauseAllEventListenersForTarget（node）`将它设置为`false`。<br/>
     * 注意：<br/>
     * - 固定优先级侦听器永远不会被暂停。 如果固定优先级不想接收事件，改为调用`setEnabled（false）`。<br/>
     * - 在“Node”的onEnter和onExit中，监听器的“暂停状态”与该节点关联的*将自动更新。
     */
    void setPaused(bool paused);

    /**
     * @en Checks whether the listener was registered by EventDispatcher<br/>
     * @zh 检查监听器是否已由 EventDispatcher 注册。
     */

    inline bool isRegistered() const {
        return _registered;
    }

    /**
     * @en Gets the type of this listener<br/>
     * note： It's different from `EventType`, e.g.<br/>
     * TouchEvent has two kinds of event listeners - EventListenerOneByOne, EventListenerAllAtOnce<br/>
     * @zh 获取此侦听器的类型<br/>
     * 注意：它与`EventType`不同，例如<br/>
     * TouchEvent 有两种事件监听器 -  EventListenerOneByOne，EventListenerAllAtOnce
     */
    inline int32_t getType() const {
        return _type;
    }

    /**
     * @en Gets the listener ID of this listener<br/>
     * When event is being dispatched, listener ID is used as key for searching listeners according to event type.<br/>
     * @zh 获取此侦听器的侦听器 ID。<br/>
     * 调度事件时，侦听器 ID 用作根据事件类型搜索侦听器的键。
     */
    inline std::string getListenerID() const {
        return _listenerID;
    }

    /**
     * @en Sets the fixed priority for this listener<br/>
     * note: This method is only used for `fixed priority listeners`,<br/>
     *   it needs to access a non-zero value. 0 is reserved for scene graph priority listeners<br/>
     * @zh 设置此侦听器的固定优先级。<br/>
     * 注意：此方法仅用于“固定优先级侦听器”，<br/>
     * 它需要访问非零值。 0保留给场景图优先级侦听器。
     */
    void setFixedPriority(int32_t fixedPriority);

    /**
     * @en Gets the fixed priority of this listener<br/>
     * @zh 获取此侦听器的固定优先级。
     * @return 如果它是场景图优先级侦听器则返回 0 ，则对于固定优先级侦听器则不为零
     */
    inline int32_t getFixedPriority() const {
        return _fixedPriority;
    }

    /**
     * @en Sets scene graph priority for this listener<br/>
     * @zh 设置此侦听器的场景图优先级。
     * @param {Node} node
     */
    void setSceneGraphPriority(scenegraph::Node* node);

    /**
     * @en Gets scene graph priority of this listener<br/>
     * @zh 获取此侦听器的场景图优先级。
     * @return 如果它是固定优先级侦听器，则为场景图优先级侦听器非 null 。
     */
    scenegraph::Node* getSceneGraphPriority() const {
        return _node;
    }

    /**
     * @en Checks whether the listener is available.<br/>
     * @zh 检测监听器是否有效
     */
    bool checkAvailable() const;

    /**
     * @en Clones the listener, its subclasses have to override this method.<br/>
     * @zh 克隆监听器,它的子类必须重写此方法。
     */
    virtual EventListener clone();

    /**
     * @en
     * Enables or disables the listener<br/>
     * note: Only listeners with `enabled` state will be able to receive events.<br/>
     * When an listener was initialized, it's enabled by default.<br/>
     * An event listener can receive events when it is enabled and is not paused.<br/>
     * paused state is always false when it is a fixed priority listener.<br/>
     * @zh
     * 启用或禁用监听器。<br/>
     * 注意：只有处于“启用”状态的侦听器才能接收事件。<br/>
     * 初始化侦听器时，默认情况下启用它。<br/>
     * 事件侦听器可以在启用且未暂停时接收事件。<br/>
     * 当固定优先级侦听器时，暂停状态始终为false。<br/>
     */
    inline void setEnabled(bool enabled) {
        _isEnabled = enabled;
    }

    /**
     * @en Checks whether the listener is enabled<br/>
     * @zh 检查监听器是否可用。
     */
    bool isEnabled() const {
        return _isEnabled;
    }

protected:
    // ts: _onEvent: ((...args: any[]) => any) | null;
    // using _onEvent = std::function<std::any(std::vector<std::any> )>;

private:
    // Event listener type
    int32_t _type{0};

    // Event listener ID
    std::string _listenerID;

    // Whether the listener has been added to dispatcher.
    bool _registered{false};

    // The higher the number, the higher the priority, 0 is for scene graph base priority.
    int32_t _fixedPriority{0};

    // scene graph based priority
    // @type {Node}
    scenegraph::Node* _node{nullptr}; // scene graph based priority

    // Whether the listener is paused
    bool _paused{true}; // Whether the listener is paused

    // Whether the listener is enabled
    bool _isEnabled{true}; // Whether the listener is enabled
};

class MouseEventListener final : public EventListener {
public:
    MouseEventListener() = default;

    ~MouseEventListener() override = default;

    // public onMouseDown: Function | null = null;
    // public onMouseUp: Function | null = null;
    // public onMouseMove: Function | null = null;
    // public onMouseScroll: Function | null = null;

    void callback(EventMouse* event) const;

    EventListener clone() override;

    bool checkAvailable() const;

private:
};

class TouchOneByOneEventListener final : public EventListener {
public:
    TouchOneByOneEventListener()           = default;
    ~TouchOneByOneEventListener() override = default;

    bool swallowTouches{false};
    // public onTouchBegan: Function | null = null;
    // public onTouchMoved: Function | null = null;
    // public onTouchEnded: Function | null = null;
    // public onTouchCancelled: Function | null = null;

    std::vector<std::any> _claimedTouches;

    inline void setSwallowTouches(std::vector<std::any> needSwallow) {
        _claimedTouches = std::move(needSwallow);
    }

    inline bool isSwallowTouches() const {
        return swallowTouches;
    }

    EventListener clone() override;

    bool checkAvailable() const;
};

class TouchAllAtOnceEventListener final : public EventListener {
public:
    TouchAllAtOnceEventListener()           = default;
    ~TouchAllAtOnceEventListener() override = default;

    // public onTouchesBegan: Function | null = null;
    // public onTouchesMoved: Function | null = null;
    // public onTouchesEnded: Function | null = null;
    // public onTouchesCancelled: Function | null = null;

    void checkAvailable() const;

    EventListener clone() override;
};

class AccelerationEventListener final : public EventListener {
public:
    // constructor (callback: Function | null)
    // public _onAccelerationEvent: Function | null = null;

    void callback(EventAcceleration* event) const;

    void checkAvailable() const;

    EventListener clone() override;
};

class KeyboardEventListener final : public EventListener {
    // public onKeyDown?: Function = undefined;
    // public onKeyPressed?: Function = undefined;  // deprecated
    // public onKeyReleased?: Function = undefined;

    KeyboardEventListener() = default;

    ~KeyboardEventListener() override = default;

    void callback(EventKeyboard* event) const;

    EventListener clone() override;

    bool checkAvailable() const;
};
} // namespace event_listener
} // namespace cc
