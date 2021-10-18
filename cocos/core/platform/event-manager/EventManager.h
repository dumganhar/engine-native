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

#include <string>
#include <unordered_map>

#include "core/Types.h"
#include "core/event/Event.h"
#include "core/platform/event-manager/EventEnum.h"
#include "core/platform/event-manager/EventListener.h"
#include "core/platform/event-manager/Touch.h"

namespace cc {
class Node;

class EventListenerVector {
public:
    int32_t gt0Index{0};

    uint32_t size() const;

    bool empty() const;

    void push() const;

    void clearSceneGraphListeners();

    void clearFIxedListeners();

    void clear();

    const std::vector<EventListener *> &getFixedPriorityListeners() const;

    const std::vector<EventListener *> &getSceneGraphPriorityListeners() const;

    std::string getListenerID(Event *event) const;

private:
    std::vector<EventListener *> _fixedListeners;

    std::vector<EventListener *> _sceneGraphListeners;
};

/**
 * @en
 * This class has been deprecated, please use `systemEvent` or `EventTarget` instead.
 * See [Listen to and launch events](../../../manual/en/scripting/events.html) for details.<br>
 * <br>
 * `eventManager` is a singleton object which manages event listener subscriptions and event dispatching.
 * The EventListener list is managed in such way so that event listeners can be added and removed
 * while events are being dispatched.
 *
 * @zh
 * 该类已废弃，请使用 `systemEvent` 或 `EventTarget` 代替，详见 [监听和发射事件](../../../manual/zh/scripting/events.html)。<br>
 * <br>
 * 事件管理器，它主要管理事件监听器注册和派发系统事件。
 *
 * @class eventManager
 * @static
 * @example {@link cocos/core/event-manager/CCEventManager/addListener.js}
 * @deprecated
 */

class EventManager final {
public:
    static EventManager &getInstance() {
        static EventManager instance;
        return instance;
    }

    /**
     * @en Pauses all listeners which are associated the specified target.
     * @zh 暂停传入的 node 相关的所有监听器的事件响应。
     * @param node - 暂停目标节点
     * @param recursive - 是否往子节点递归暂停。默认为 false。
     */
    void pauseTarget(Node *node, bool recursive = false) const;

    /**
     * @en
     * Resumes all listeners which are associated the specified target.
     *
     * @zh
     * 恢复传入的 node 相关的所有监听器的事件响应。
     *
     * @param node - 监听器节点。
     * @param recursive - 是否往子节点递归。默认为 false。
     */
    void resumeTarget(Node *node, bool recursive = false) const;

    void frameUpdateListeners() const;

    /**
     * @en
     * Query whether the specified event listener id has been added.
     *
     * @zh
     * 查询指定的事件 ID 是否存在。
     *
     * @param listenerID - 查找监听器 ID。
     * @returns 是否已查找到。
     */
    bool hasEventListener(std::string listenerID) const;

    /**
     * @en
     * <p>
     * Adds a event listener for a specified event.<br/>
     * if the parameter "nodeOrPriority" is a node,
     * it means to add a event listener for a specified event with the priority of scene graph.<br/>
     * if the parameter "nodeOrPriority" is a Number,
     * it means to add a event listener for a specified event with the fixed priority.<br/>
     * </p>
     *
     * @zh
     * 将事件监听器添加到事件管理器中。<br/>
     * 如果参数 “nodeOrPriority” 是节点，优先级由 node 的渲染顺序决定，显示在上层的节点将优先收到事件。<br/>
     * 如果参数 “nodeOrPriority” 是数字，优先级则固定为该参数的数值，数字越小，优先级越高。<br/>
     *
     * @param listener - 指定事件监听器。
     * @param nodeOrPriority - 监听程序的优先级。
     * @returns
     */
    inline void addListener(EventListener *listener, Node *node) const {} // TODO(xwx): need to implement

    inline void addListener(EventListener *listener, int32_t priority) const {} // TODO(xwx): need to implement

    /**
     * @en
     * Adds a Custom event listener. It will use a fixed priority of 1.
     *
     * @zh
     * 向事件管理器添加一个自定义事件监听器。
     *
     * @param eventName - 自定义事件名。
     * @param callback - 事件回调。
     * @returns 返回自定义监听器。
     */

    const EventListener *&addCustomListener(std::string eventName, std::function<void()> callback) const;

    /**
     * @en
     * Remove a listener.
     *
     * @zh
     * 移除一个已添加的监听器。
     *
     * @param listener - 需要移除的监听器。
     */
    inline void removeListener(EventListener *listener) const {} // TODO(xwx): need to implement

    /**
     * @en
     * Removes all listeners with the same event listener type or removes all listeners of a node.
     *
     * @zh
     * 移除注册到 eventManager 中指定类型的所有事件监听器。<br/>
     * 1. 如果传入的第一个参数类型是 Node，那么事件管理器将移除与该对象相关的所有事件监听器。
     * （如果第二参数 recursive 是 true 的话，就会连同该对象的子控件上所有的事件监听器也一并移除）<br/>
     * 2. 如果传入的第一个参数类型是 Number（该类型 EventListener 中定义的事件类型），
     * 那么事件管理器将移除该类型的所有事件监听器。<br/>
     *
     * 下列是目前存在监听器类型：       <br/>
     * `EventListener.UNKNOWN`       <br/>
     * `EventListener.KEYBOARD`      <br/>
     * `EventListener.ACCELERATION`，<br/>
     *
     * @param listenerType - 监听器类型。
     * @param recursive - 递归子节点的同类型监听器一并移除。默认为 false。
     */
    inline void removeListeners(Node *node, bool recursive = false) const {} // TODO(xwx): need to implement

    inline void removeListeners(int32_t eventType, bool recursive = false) const {} // TODO(xwx): need to implement

    /**
     * @en
     * Removes all custom listeners with the same event name.
     *
     * @zh
     * 移除同一事件名的自定义事件监听器。
     *
     * @param customEventName - 自定义事件监听器名。
     */
    void removeCustomListeners(int32_t customEventName) const;

    /**
     * @en
     * Removes all listeners.
     *
     * @zh
     * 移除所有事件监听器。
     */
    void removeAllListeners() const;

    /**
     * @en
     * Sets listener's priority with fixed value.
     *
     * @zh
     * 设置 FixedPriority 类型监听器的优先级。
     *
     * @param listener - 监听器。
     * @param fixedPriority - 优先级。
     */
    void setPriority(EventListener *listener, int32_t fixedPriority) const;

    /**
     * @en
     * Whether to enable dispatching events.
     *
     * @zh
     * 启用或禁用事件管理器，禁用后不会分发任何事件。
     *
     * @param enabled - 是否启用事件管理器。
     */
    void setEnabled(bool enabled);

    /**
     * @en
     * Checks whether dispatching events is enabled.
     *
     * @zh 检测事件管理器是否启用。
     *
     * @returns
     */
    inline bool isEnabled() const {
        return _isEnabled;
    }

    /**
     * @en
     * Dispatches the event, also removes all EventListeners marked for deletion from the event dispatcher list.
     *
     * @zh
     * 分发事件。
     *
     * @param event - 分发事件。
     */

    void dispatchEvent(Event *event) const;

    bool onListenerCallback(EventListener *listener, Event *event) const;

    /**
     * @en
     * Dispatches a Custom Event with a event name an optional user data.
     *
     * @zh
     * 分发自定义事件。
     *
     * @param eventName - 自定义事件名。
     * @param optionalUserData
     */
    void dispatchCustomEvent(std::string eventName, std::any) const;

private:
    EventManager()  = default;
    ~EventManager() = default;
    void setDirtyForNode(Node *node) const;
    void addListener(EventListener *listener) const;
    void forceAddEventListener(EventListener *listener) const;
    void getListeners(std::string listenerID) const;
    void updateDirtyFlagForSceneGraph() const;
    void removeAllListenersInVector(std::vector<EventListener *> listenerVector) const;
    void removeListenersForListenerID(std::string listenerID) const;
    void sortEventListeners(std::string listenerID) const;
    void sortListenersOfSceneGraphPriority(std::string listenerID) const;
    void sortListenersOfFixedPriority(std::string listenerID) const;
    void sortListenersOfFixedPriorityAsc(EventListener *l1, EventListener *l2) const;
    void onUpdateListeners(EventListenerVector *listeners) const;
    void updateTouchListeners() const;
    void cleanToRemovedListeners() const;
    void onTouchEventCallback(TouchOneByOneEventListener *listeners, std::any argsObj) const;
    void dispatchTouchEvent(EventTouch *event) const;
    void onTouchesEventCallback(std::any listener, std::any callbackParams) const;
    void associateNodeAndEventListener(Node *node, EventListener *listener) const;
    void dissociateNodeAndEventListener(Node *node, EventListener *listener) const;
    void dispatchEventToListeners(EventListenerVector *listeners, std::function<bool>(std::any, std::any), std::any eventOrArgs) const;
    void setDirty(std::string listenerID, int32_t flag) const;
    void clearCurTouch() const;
    void removeListenerInVector(std::vector<EventListener *> listeners, EventListener *listener) const;

    std::unordered_map<std::string, EventListenerVector *>         _listenersMap;
    std::unordered_map<std::string, int32_t>                       _priorityDirtyFlagMap;
    std::unordered_map<std::string, std::vector<EventListener *> > _nodeListenersMap;
    std::vector<EventListener *>                                   _toAddedListeners;
    std::vector<EventListener *>                                   _toRemoveListeners;

    Record<std::string, bool> _dirtyListener;
    int32_t                   _inDispatch{0};
    bool                      _isEnabled{false};
    std::vector<std::string>  _internalCustomListenersIDs;
    Touch *                   _currentTouch{nullptr};
    std::any                  _currentTouchListener{nullptr};
};

} // namespace cc
