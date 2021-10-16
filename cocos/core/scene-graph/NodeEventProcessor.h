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
#include <functional>
#include <string>
#include <variant>
#include "core/event/CallbacksInvoker.h"
#include "core/event/Event.h"
#include "core/platform/event-manager/EventListener.h"
#include "core/platform/event-manager/EventManager.h"
#include "core/scene-graph/NodeEvent.h"
namespace cc {
const std::vector<std::string> TOUCH_EVENTS{cc::NodeEventType::TOUCH_START, cc::NodeEventType::TOUCH_MOVE, cc::NodeEventType::TOUCH_END, cc::NodeEventType::TOUCH_CANCEL};
const std::vector<std::string> MOUSE_EVENTS{cc::NodeEventType::MOUSE_DOWN, cc::NodeEventType::MOUSE_ENTER, cc::NodeEventType::MOUSE_MOVE, cc::NodeEventType::MOUSE_LEAVE, cc::NodeEventType::MOUSE_UP, cc::NodeEventType::MOUSE_WHEEL};

class Node;
class NodeEventProcessor final {
public:
    NodeEventProcessor() = default;
    explicit NodeEventProcessor(Node *node);
    ~NodeEventProcessor() = default;

    inline Node *getNode() { return _node; }
    void         reattach();
    void         destroy();

    /**
     * @zh
     * 分发事件到事件流中。
     *
     * @param event - 分派到事件流中的事件对象。
     */
    void dispatchEvent(const Event &event) const;

    bool hasEventListener(const std::string &type);
    bool hasEventListener(const std::string &type, const std::function<void(Node *)> &callback);
    bool hasEventListener(const std::string &type, const std::function<void(Node *)> &callback, void *target);
    static bool checkListeners(Node *node, const std::vector<std::string> &events);

    template <typename... Args>
    void on(const std::string &type, std::function<void(Args...)> &&callback);
    template <typename Target, typename... Args>
    void on(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture = false);
    template <typename Target, typename... Args>
    void on(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture = false);
    //TODO(xwx): LambdaType on
    template <typename... Args>
    void once(const std::string &type, std::function<void(Args...)> &&callback);
    template <typename Target, typename... Args>
    void once(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture = false);
    template <typename Target, typename... Args>
    void once(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture = false);
    //TODO(xwx): LambdaType once
    void off(const std::string &type);
    void off(const std::string &type, void *target, bool useCapture = false);
    template <typename Target, typename... Args>
    void off(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture = false);
    /**
     * @zh
     * 通过事件名发送自定义事件
     *
     * @param type - event type
     * @param args - The  arguments to be passed to the callback
     */
    template <typename... Args>
    void emit(const std::string &type, Args &&...args);

    void targetOff(const std::string &);

    void getCapturingTargets(const std::string &type, std::vector<Node *> &targets) const;
    void getBubblingTargets(const std::string &type, std::vector<Node *> &targets) const;

    inline CallbacksInvoker *getBubblingTargets() const { return _bubblingTargets; }
    inline CallbacksInvoker *getCapturingTargets() const { return _capturingTargets; }
    inline EventListener *   getTouchListener() const { return _touchListener; }
    inline EventListener *   getMouseListener() const { return _mouseListener; }

private:
    /**
     * @zh
     * 节点冒泡事件监听器
     */
    CallbacksInvoker *_bubblingTargets{nullptr};

    /**
     * @zh
     * 节点捕获事件监听器
     */
    CallbacksInvoker *_capturingTargets{nullptr};

    /**
     * @zh
     * 触摸监听器
     */
    EventListener *_touchListener{nullptr};

    /**
     * @zh
     * 鼠标监听器
     */
    EventListener *_mouseListener{nullptr};

    CallbackInfoBase::ID _cbID{0};

    Node *_node{nullptr};

    bool checknSetupSysEvent(const std::string &type);

    template <typename... Args>
    void onDispatch(const std::string &type, std::function<void(Args...)> &&callback, bool useCapture = false);

    template <typename Target, typename... Args>
    void onDispatch(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture = false);

    template <typename Target, typename... Args>
    void onDispatch(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture = false);

    void offDispatch(const std::string &type, bool useCapture = false) const;
    void offDispatch(const std::string &type, void *target, bool useCapture = false) const;

    CC_DISALLOW_COPY_MOVE_ASSIGN(NodeEventProcessor);
};

template <typename... Args>
void NodeEventProcessor::emit(const std::string &type, Args &&...args) {
    if (_bubblingTargets != nullptr) {
        _bubblingTargets->emit(type, std::forward<Args>(args)...);
    }
}
template <typename... Args>
void NodeEventProcessor::onDispatch(const std::string &type, std::function<void(Args...)> &&callback, bool useCapture) {
    CallbacksInvoker *listeners = nullptr;
    if (useCapture) {
        if (_capturingTargets == nullptr) {
            _capturingTargets = new CallbacksInvoker();
        }
        listeners = _capturingTargets;
    } else {
        if (_bubblingTargets == nullptr) {
            _bubblingTargets = new CallbacksInvoker();
        }
        listeners = _bubblingTargets;
    }
    if (!listeners->hasEventListener(type)) {
        listeners->on(type, std::forward<std::function<void(Args...)>>(callback), _cbID);
    }
}

template <typename Target, typename... Args>
void NodeEventProcessor::onDispatch(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture) {
    CallbacksInvoker *listeners = nullptr;
    if (useCapture) {
        if (_capturingTargets == nullptr) {
            _capturingTargets = new CallbacksInvoker();
        }
        listeners = _capturingTargets;
    } else {
        if (_bubblingTargets == nullptr) {
            _bubblingTargets = new CallbacksInvoker();
        }
        listeners = _bubblingTargets;
    }
    if (!listeners->hasEventListener(type)) {
        listeners->on<Target>(type, std::forward<std::function<void(Args...)>>(callback), target, _cbID);
    }
}

template <typename Target, typename... Args>
void NodeEventProcessor::onDispatch(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture) {
    CallbacksInvoker *listeners = nullptr;
    if (useCapture) {
        if (_capturingTargets == nullptr) {
            _capturingTargets = new CallbacksInvoker();
        }
        listeners = _capturingTargets;
    } else {
        if (_bubblingTargets == nullptr) {
            _bubblingTargets = new CallbacksInvoker();
        }
        listeners = _bubblingTargets;
    }
    if (!listeners->hasEventListener(type)) {
        listeners->on<Target>(type, memberFn, target, _cbID);
    }
}

template <typename... Args>
void NodeEventProcessor::on(const std::string &type, std::function<void(Args...)> &&callback) {
    // CallbackInfoBase::ID unusedID{0};
    // on<std::nullptr_t>(type, std::forward<std::function<void(Args...)>>(callback), nullptr, unusedID, once);
    bool forDispatch = checknSetupSysEvent(type);
    if (forDispatch) {
        onDispatch(type, std::forward<std::function<void(Args...)>>(callback));
    } else {
        if (_bubblingTargets == nullptr) {
            _bubblingTargets = new CallbacksInvoker();
        }
        _bubblingTargets->on(type, std::forward<std::function<void(Args...)>>(callback), _cbID);
    }
}

template <typename Target, typename... Args>
void NodeEventProcessor::on(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture) {
    // CallbackInfoBase::ID unusedID{0};
    // on<std::nullptr_t>(type, std::forward<std::function<void(Args...)>>(callback), nullptr, unusedID, once);
    bool forDispatch = checknSetupSysEvent(type);
    if (forDispatch) {
        onDispatch<Target>(type, std::forward<std::function<void(Args...)>>(callback), target, useCapture);
    } else {
        if (_bubblingTargets == nullptr) {
            _bubblingTargets = new CallbacksInvoker();
        }
        _bubblingTargets->on<Target>(type, std::forward<std::function<void(Args...)>>(callback), _cbID);
    }
}

template <typename Target, typename... Args>
void NodeEventProcessor::on(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture) {
    using CallbackInfoType = CallbackInfo<Args...>;
    bool forDispatch       = checknSetupSysEvent(type);
    if (forDispatch) {
        onDispatch<Target>(type, memberFn, target, useCapture);
    } else {
        if (_bubblingTargets == nullptr) {
            _bubblingTargets = new CallbacksInvoker();
        }
        _bubblingTargets->on<Target>(type, memberFn, target, _cbID);
    }
}

template <typename... Args>
void NodeEventProcessor::once(const std::string &type, std::function<void(Args...)> &&callback) {
    CallbacksInvoker *listeners = nullptr;
    if (_bubblingTargets == nullptr) {
        _bubblingTargets = new CallbacksInvoker();
    }
    listeners = _bubblingTargets;
    listeners->on(type, std::forward<std::function<void(Args...)>>(callback), _cbID, true);
}

template <typename Target, typename... Args>
void NodeEventProcessor::once(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture) {
    bool              forDispatch = checknSetupSysEvent(type);
    CallbacksInvoker *listeners   = nullptr;
    if (useCapture) {
        if (_capturingTargets == nullptr) {
            _capturingTargets = new CallbacksInvoker();
        }
        listeners = _capturingTargets;
    } else {
        if (_bubblingTargets == nullptr) {
            _bubblingTargets = new CallbacksInvoker();
        }
        listeners = _bubblingTargets;
    }
    listeners->on(type, memberFn, target, true);
    // TODO(xwx): FIXME: params not match
    // listeners->on(
    //     type, [&]() { off(type, callback, target); }, nullptr, true);
}

template <typename Target, typename... Args>
void NodeEventProcessor::once(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture) {
    bool              forDispatch = checknSetupSysEvent(type);
    CallbacksInvoker *listeners   = nullptr;
    if (useCapture) {
        if (_capturingTargets == nullptr) {
            _capturingTargets = new CallbacksInvoker();
        }
        listeners = _capturingTargets;
    } else {
        if (_bubblingTargets == nullptr) {
            _bubblingTargets = new CallbacksInvoker();
        }
        listeners = _bubblingTargets;
    }
    listeners->on(type, std::forward<std::function<void(Args...)>>(callback), _cbID, target, true);
    // TODO(xwx): FIXME: params not match
    // listeners->on(
    //     type, [&]() { off(type, callback, target); }, nullptr, true);
}

template <typename Target, typename... Args>
void NodeEventProcessor::off(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture) {
    bool touchEventExist = std::find(TOUCH_EVENTS.begin(), TOUCH_EVENTS.end(), type) != TOUCH_EVENTS.end();
    bool mouseEventExist = std::find(MOUSE_EVENTS.begin(), MOUSE_EVENTS.end(), type) != MOUSE_EVENTS.end();
    if (touchEventExist || mouseEventExist) {
        offDispatch(type, memberFn, target, useCapture);

        if (touchEventExist) {
            if (_touchListener && !checkListeners(_node, TOUCH_EVENTS)) { // TODO(xwx): why !checkListeners(_node, TOUCH_EVENTS) ???
                EventManager::getInstance().removeListener(_touchListener);
                _touchListener = nullptr;
            }
        } else if (mouseEventExist) {
            if (_mouseListener && !checkListeners(_node, MOUSE_EVENTS)) { // TODO(xwx): why !checkListeners(_node, MOUSE_EVENTS) ???
                EventManager::getInstance().removeListener(_mouseListener);
                _mouseListener = nullptr;
            }
        }
    } else if (_bubblingTargets != nullptr) {
        _bubblingTargets->off<Target>(type, memberFn, target);
    }
}
} // namespace cc
