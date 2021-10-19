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

#include "core/data/Object.h"
#include "core/platform/event-manager/EventEnum.h"

NS_CC_EVENT_BEGIN

class Event : public Ref {
public:
    // Event types
    enum class Type {
        TOUCH,
        KEYBOARD,
        ACCELERATION,
        MOUSE,
        FOCUS,
        GAME_CONTROLLER,
        CUSTOM
    };

    Event() = default;
    explicit Event(Type eventType);
    Event(Type eventType, bool bubbles);
    virtual ~Event() = default;

    // Event phases
    enum class Phase {
        /**
         * @en
         * Events not currently dispatched are in this phase.
         *
         * @zh
         * 尚未派发事件阶段。
         */
        NONE = 0,

        /**
         * @en
         * The capturing phase comprises the journey from the root to the last node before the event target's node
         * [markdown](http://www.w3.org/TR/DOM-Level-3-Events/#event-flow)
         *
         * @zh
         * 捕获阶段，包括事件目标节点之前从根节点到最后一个节点的过程。
         */
        CAPTURING = 1,

        /**
         * @en
         * The target phase comprises only the event target node
         * [markdown] (http://www.w3.org/TR/DOM-Level-3-Events/#event-flow)
         *
         * @zh
         * 目标阶段仅包括事件目标节点。
         */
        AT_TARGET = 2,

        /**
         * @en
         * The bubbling phase comprises any subsequent nodes encountered on the return trip to the root of the hierarchy
         * [markdown] (http://www.w3.org/TR/DOM-Level-3-Events/#event-flow)
         *
         * @zh
         * 冒泡阶段， 包括回程遇到到层次根节点的任何后续节点。
         */
        BUBBLING = 3
    };

    /**
     * @en
     * Checks whether the event has been stopped.
     *
     * @zh
     * 检查该事件是否已经停止传递。
     */
    inline bool isStopped() const { return _propagationStopped || _propagationImmediateStopped; }

    /**
     * @en
     * Gets current target of the event                                                            <br/>
     * note: It only be available when the event listener is associated with node.                <br/>
     * It returns 0 when the listener is associated with fixed priority.
     * @zh
     * 获取当前目标节点
     * @returns - The target with which the event associates.
     */
    inline CCObject *getCurrentTarget() const { return _currentTarget; }
    inline void      setCurrentTarget(CCObject *target) { _currentTarget = target; }

    /**
     * @en
     * A reference to the target to which the event was originally dispatched.
     *
     * @zh
     * 最初事件触发的目标。
     */
    inline CCObject *getTarget() const { return _target; }
    inline void      setTarget(CCObject *target) { _target = target; } //cjh shared_ptr?

    /**
     * @en
     * Gets the event type.
     * @zh
     * 获取事件类型。
     */
    inline Type getEventType() const { return _eventType; }

    inline const std::string &getEventName() const { return _eventName; }
    inline void               setEventName(const std::string &eventName) { _eventName = eventName; }

    /**
     * @en
     * Indicate whether the event bubbles up through the hierarchy or not.
     *
     * @zh
     * 表示该事件是否进行冒泡。
     */
    inline bool isUseBubbles() const { return _bubbles; }
    inline void setUseBubbles(bool useBubbles) { _bubbles = useBubbles; };

    /**
     * @en
     * Indicates which phase of the event flow is currently being evaluated.
     * Returns an integer value represented by 4 constants:
     *  - Event.NONE = 0
     *  - Event.CAPTURING_PHASE = 1
     *  - Event.AT_TARGET = 2
     *  - Event.BUBBLING_PHASE = 3
     * The phases are explained in the [section 3.1, Event dispatch and DOM event flow]
     * [markdown](http://www.w3.org/TR/DOM-Level-3-Events/#event-flow), of the DOM Level 3 Events specification.
     *
     * @zh
     * 事件阶段。
     */
    inline Phase getEventPhase() const { return _eventPhase; }
    inline void  setEventPhase(Phase phase) { _eventPhase = phase; }

    /**
     * @en
     * Stops propagation for current event.
     *
     * @zh
     * 停止传递当前事件。
     */
    inline bool isPropagationStopped() const { return _propagationStopped; }
    inline void setPropagationStopped(bool stopped) { _propagationStopped = stopped; }

    /**
     * @en
     * Stops propagation for current event immediately,
     * the event won't even be dispatched to the listeners attached in the current target.
     *
     * @zh
     * 立即停止当前事件的传递，事件甚至不会被分派到所连接的当前目标。
     */
    bool isPropagationImmediateStopped() const { return _propagationImmediateStopped; }
    void setPropagationImmediateStopped(bool stopped) { _propagationImmediateStopped = stopped; }

    /**
     * @en
     * Reset the event for being stored in the object pool.
     *
     * @zh
     * 重置事件对象以便在对象池中存储。
     */
    void unuse();

    /**
     * @en
     * Reinitialize the event for being used again after retrieved from the object pool.
     * @zh
     * 重新初始化让对象池中取出的事件可再次使用。
     * @param type - The name of the event (case-sensitive), e.g. "click", "fire", or "submit"
     * @param bubbles - A boolean indicating whether the event bubbles up through the tree or not
     */
    void reuse(const std::string &type, bool bubbles = false);

protected:
    CCObject *  _target{nullptr};
    CCObject *  _currentTarget{nullptr};
    Phase       _eventPhase{Phase::NONE};
    Type        _eventType;
    std::string _eventName;
    bool        _bubbles{false};
    bool        _propagationStopped{false};
    bool        _propagationImmediateStopped{false};
};

NS_CC_EVENT_END
