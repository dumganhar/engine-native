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

#include "core/scene-graph/NodeEventProcessor.h"
#include "core/Director.h"
#include "core/components/Component.h"
#include "core/platform/event-manager/Events.h"
#include "core/platform/event-manager/Touch.h"
#include "core/scene-graph/Node.h"
#include "math/Vec2.h"

namespace {
std::vector<cc::Node *> cachedArray(16);
cc::Node *              currentHovered = nullptr;
cc::Vec2                pos;

bool touchStartHandler(cc::EventListener thiz, cc::Touch *touch, cc::EventTouch event) {
    auto *node = std::any_cast<cc::Node *>(thiz.owner);
    if (node == nullptr /*|| !node_uiProps.uiTransformComp */) { // TODO(xwx):uiTransformComp not define
        return false;
    }

    touch->getUILocation(pos);

    // if (node._uiProps.uiTransformComp.isHit(pos, this)) { // TODO(xwx):uiTransformComp not define
    event.type    = cc::NodeEventType::TOUCH_START;
    event.touch   = touch;
    event.bubbles = true;
    node->dispatchEvent(event);
    return true;
    // }

    return false;
}

bool touchMoveHandler(cc::EventListener thiz, cc::Touch *touch, cc::EventTouch event) {
    auto *node = std::any_cast<cc::Node *>(thiz.owner);
    if (node == nullptr /*|| !node_uiProps.uiTransformComp */) { // TODO(xwx):uiTransformComp not define
        return false;
    }

    event.type    = cc::NodeEventType::TOUCH_MOVE;
    event.touch   = touch;
    event.bubbles = true;
    node->dispatchEvent(event);
    return true;
}

void touchEndHandler(cc::EventListener thiz, cc::Touch *touch, cc::EventTouch event) {
    auto *node = std::any_cast<cc::Node *>(thiz.owner);
    if (node == nullptr /*|| !node_uiProps.uiTransformComp */) { // TODO(xwx):uiTransformComp not define
        return;
    }

    touch->getUILocation(pos);

    // if (node._uiProps.uiTransformComp.isHit(pos, this)) {  // TODO(xwx):uiTransformComp not define
    event.type = cc::NodeEventType::TOUCH_END;
    // } else {
    // event.type = cc::NodeEventType::TOUCH_CANCEL;
    // }

    event.touch   = touch;
    event.bubbles = true;
    node->dispatchEvent(event);
}

void touchCancelHandler(cc::EventListener thiz, cc::Touch *touch, cc::EventTouch event) {
    auto *node = std::any_cast<cc::Node *>(thiz.owner);
    if (node == nullptr /*|| !node_uiProps.uiTransformComp */) { // TODO(xwx):uiTransformComp not define
        return;
    }

    event.type    = cc::NodeEventType::TOUCH_CANCEL;
    event.touch   = touch;
    event.bubbles = true;
    node->dispatchEvent(event);
}

void mouseDownHandler(cc::EventListener thiz, cc::EventMouse event) {
    auto *node = std::any_cast<cc::Node *>(thiz.owner);
    if (node == nullptr /*|| !node_uiProps.uiTransformComp */) { // TODO(xwx):uiTransformComp not define
        return;
    }

    pos = event.getUILocation();

    // if (node._uiProps.uiTransformComp.isHit(pos, thiz)) {
    event.type    = cc::NodeEventType::MOUSE_DOWN;
    event.bubbles = true;
    node->dispatchEvent(event);
    // }
}

void mouseMoveHandler(cc::EventListener thiz, cc::EventMouse event) {
    auto *node = std::any_cast<cc::Node *>(thiz.owner);
    if (node == nullptr /*|| !node_uiProps.uiTransformComp */) { // TODO(xwx):uiTransformComp not define
        return;
    }

    pos = event.getUILocation();

    // const hit = node._uiProps.uiTransformComp.isHit(pos, this);  // TODO(xwx):uiTransformComp not define
    if (true) { // TODO(xwx):hit not define
        if (!thiz._previousIn) {
            // Fix issue when hover node switched, previous hovered node won't get MOUSE_LEAVE notification
            if (currentHovered && currentHovered->getEventProcessor()->getMouseListener()) {
                event.type = cc::NodeEventType::MOUSE_LEAVE;
                currentHovered->dispatchEvent(event);
                if (currentHovered->getEventProcessor()->getMouseListener()) {
                    currentHovered->getEventProcessor()->getMouseListener()->_previousIn = false;
                }
            }
            currentHovered = node;
            event.type     = cc::NodeEventType::MOUSE_ENTER;
            node->dispatchEvent(event);
            thiz._previousIn = true;
        }
        event.type    = cc::NodeEventType::MOUSE_MOVE;
        event.bubbles = true;
        node->dispatchEvent(event);
    } else if (thiz._previousIn) {
        event.type = cc::NodeEventType::MOUSE_LEAVE;
        node->dispatchEvent(event);
        thiz._previousIn = false;
        currentHovered   = nullptr;
    } else {
        // continue dispatching
        return;
    }

    // Event processed, cleanup
    event.propagationStopped = true;
}
void mouseUpHandler(cc::EventListener thiz, cc::EventMouse event) {
    auto *node = std::any_cast<cc::Node *>(thiz.owner);
    if (node == nullptr /*|| !node_uiProps.uiTransformComp */) { // TODO(xwx):uiTransformComp not define
        return;
    }

    pos = event.getUILocation();

    // if (node._uiProps.uiTransformComp.isHit(pos, thiz)) { / TODO(xwx):uiTransformComp not define
    event.type    = cc::NodeEventType::MOUSE_UP;
    event.bubbles = true;
    node->dispatchEvent(event);
    event.propagationStopped = true;
    // }
}

void mouseWheelHandler(cc::EventListener thiz, cc::EventMouse event) {
    auto *node = std::any_cast<cc::Node *>(thiz.owner);
    if (node == nullptr /*|| !node_uiProps.uiTransformComp */) { // TODO(xwx):uiTransformComp not define
        return;
    }

    pos = event.getUILocation();

    // if (node._uiProps.uiTransformComp.isHit(pos, thiz)) { / TODO(xwx):uiTransformComp not define
    event.type    = cc::NodeEventType::MOUSE_WHEEL;
    event.bubbles = true;
    node->dispatchEvent(event);
    event.propagationStopped = true;
    // }
}

void doDispatchEvent(cc::Node *owner, cc::Event event) {
    cc::Node *target = nullptr;
    event.target     = static_cast<cc::CCObject *>(owner);

    // Event.CAPTURING_PHASE
    cachedArray.clear();
    owner->getEventProcessor()->getCapturingTargets(event.type, cachedArray);
    // capturing
    event.eventPhase = 1;
    for (uint32_t i = cachedArray.size() - 1; i >= 0; --i) {
        target = cachedArray[i];
        if (target->getEventProcessor()->getCapturingTargets()) {
            event.currentTarget = target;
            // fire event
            target->getEventProcessor()->getCapturingTargets()->emit(event.type, event, cachedArray);
            // check if propagation stopped
            if (event.propagationStopped) {
                cachedArray.clear();
                return;
            }
        }
    }
    cachedArray.clear();

    // Event.AT_TARGET
    // checks if destroyed in capturing callbacks
    event.eventPhase    = 2;
    event.currentTarget = owner;
    if (owner->getEventProcessor()->getCapturingTargets()) {
        owner->getEventProcessor()->getCapturingTargets()->emit(event.type, event);
    }
    if (!event.propagationImmediateStopped && owner->getEventProcessor()->getBubblingTargets()) {
        owner->getEventProcessor()->getBubblingTargets()->emit(event.type, event);
    }

    if (!event.propagationStopped && event.bubbles) {
        // Event.BUBBLING_PHASE
        owner->getEventProcessor()->getBubblingTargets(event.type, cachedArray);
        // propagate
        event.eventPhase = 3;
        for (uint32_t i = 0; i < cachedArray.size(); ++i) {
            target = cachedArray[i];
            if (target->getEventProcessor()->getBubblingTargets()) {
                event.currentTarget = target;
                // fire event
                target->getEventProcessor()->getBubblingTargets()->emit(event.type, event);
                // check if propagation stopped
                if (event.propagationStopped) {
                    cachedArray.clear();
                    return;
                }
            }
        }
    }
    cachedArray.clear();
}

template <typename T, typename Enabled = std::enable_if_t<std::is_base_of_v<cc::Component, T>, T>>
std::vector<cc::IListenerMask> searchComponentsInParent(cc::Node *node) {
    index_t                        index = 0;
    std::vector<cc::IListenerMask> list;

    for (cc::Node *curr = node; curr != nullptr && cc::Node::isNode(curr); curr = curr->getParent(), ++index) {
        auto *comp = curr->getComponent<T>();
        if (comp != nullptr) {
            cc::IListenerMask next{
                .index = index,
                .comp  = comp,
            };
            list.emplace_back(next);
        }
    }
    return list.empty() ? std::vector<cc::IListenerMask>() : list;
}

} // namespace
namespace cc {
NodeEventProcessor::NodeEventProcessor(Node *node) : _node(node) {}

bool NodeEventProcessor::checkListeners(cc::Node *node, const std::vector<std::string> &events) {
    if (!node->getPersistNode()) {
        if (node->getEventProcessor()->_bubblingTargets) {
            for (const auto &event : events) {
                if (node->getEventProcessor()->_bubblingTargets->hasEventListener(event)) {
                    return true;
                }
            }
        }
        if (node->getEventProcessor()->_bubblingTargets) {
            for (const auto &event : events) {
                if (node->getEventProcessor()->_bubblingTargets->hasEventListener(event)) {
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}

void NodeEventProcessor::reattach() {
    std::vector<IListenerMask> currMask;
    _node->walk(
        [&](Node *node) {
            if (currMask.empty()) {
                currMask = searchComponentsInParent<Component>(dynamic_cast<Node *>(node));
            }
            if (node->getEventProcessor()->_touchListener != nullptr) {
                node->getEventProcessor()->_touchListener->mask = currMask;
            }
            if (node->getEventProcessor()->_mouseListener != nullptr) {
                node->getEventProcessor()->_mouseListener->mask = currMask;
            }
        });
}

void NodeEventProcessor::destroy() {
    if (currentHovered == _node) {
        currentHovered = nullptr;
    }

    // Remove all event listeners if necessary
    if (_touchListener || _mouseListener) {
        EventManager::getInstance().removeListeners(static_cast<Node *>(_node)); //TODO(xwx): remove Node
        if (_touchListener) {
            _touchListener->owner = nullptr;
            _touchListener->mask.clear();
            _touchListener = nullptr;
        }
        if (_mouseListener) {
            _mouseListener->owner = nullptr;
            _mouseListener->mask.clear();
            _mouseListener = nullptr;
        }
    }

    if (_capturingTargets) _capturingTargets->offAll();
    if (_bubblingTargets) _bubblingTargets->offAll();
}

void NodeEventProcessor::off(const std::string &type) {
    bool touchEventExist = std::find(TOUCH_EVENTS.begin(), TOUCH_EVENTS.end(), type) != TOUCH_EVENTS.end();
    bool mouseEventExist = std::find(MOUSE_EVENTS.begin(), MOUSE_EVENTS.end(), type) != MOUSE_EVENTS.end();
    if (touchEventExist || mouseEventExist) {
        offDispatch(type);

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
        _bubblingTargets->off(type, _cbID);
    }
}

void NodeEventProcessor::off(const std::string &type, void *target, bool useCapture) {
    bool touchEventExist = std::find(TOUCH_EVENTS.begin(), TOUCH_EVENTS.end(), type) != TOUCH_EVENTS.end();
    bool mouseEventExist = std::find(MOUSE_EVENTS.begin(), MOUSE_EVENTS.end(), type) != MOUSE_EVENTS.end();
    if (touchEventExist || mouseEventExist) {
        // offDispatch(type, callback, target, useCapture);

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
        _bubblingTargets->off(type, _cbID, target); // TODO(xwx): 3 parameters off not implemented
    }
}

void NodeEventProcessor::dispatchEvent(const Event &event) const {
    doDispatchEvent(_node, event);
    cachedArray.clear();
}

bool NodeEventProcessor::hasEventListener(const std::string &type) {
    bool has = false;
    if (_bubblingTargets) {
        has = _bubblingTargets->hasEventListener(type);
    }
    if (!has && _capturingTargets) {
        has = _capturingTargets->hasEventListener(type);
    }
    return has;
}

bool NodeEventProcessor::hasEventListener(const std::string &type, const std::function<void(Node *)> &callback, void *target) {
    bool has = false;
    // TODO(xwx): need to finish template usage
    // if (_bubblingTargets) {
    //     has = _bubblingTargets->hasEventListener(type, callback, target);
    // }
    // if (!has && _capturingTargets) {
    // has = _capturingTargets->hasEventListener(type, callback, target);
    // }
    return has;
}

bool NodeEventProcessor::hasEventListener(const std::string &type, const std::function<void(Node *)> &callback) {
    bool has = false;
    // TODO(xwx): need to finish template usage
    // if (_bubblingTargets) {
    //     has = _bubblingTargets->hasEventListener(type, callback);
    // }
    // if (!has && _capturingTargets) {
    //     has = _capturingTargets->hasEventListener(type, callback);
    // }
    return has;
}

void NodeEventProcessor::targetOff(const std::string &target) {
    if (_capturingTargets) {
        _capturingTargets->offAll(target);
    }
    if (_bubblingTargets) {
        _bubblingTargets->offAll(target);
    }

    if (_touchListener && !checkListeners(_node, TOUCH_EVENTS)) {
        EventManager::getInstance().removeListener(_touchListener);
        _touchListener = nullptr;
    }
    if (_mouseListener && !checkListeners(_node, MOUSE_EVENTS)) {
        EventManager::getInstance().removeListener(_mouseListener);
        _mouseListener = nullptr;
    }
}

void NodeEventProcessor::getCapturingTargets(const std::string &type, std::vector<Node *> &targets) const {
    auto *parent = _node->getParent();
    while (parent != nullptr) {
        if (parent->getEventProcessor()->_capturingTargets != nullptr && parent->getEventProcessor()->_capturingTargets->hasEventListener(type)) {
            targets.emplace_back(parent);
        }
        parent = parent->getParent();
    }
}

void NodeEventProcessor::getBubblingTargets(const std::string &type, std::vector<Node *> &targets) const {
    auto *parent = _node->getParent();
    while (parent != nullptr) {
        if (parent->getEventProcessor()->_bubblingTargets != nullptr && parent->getEventProcessor()->_bubblingTargets->hasEventListener(type)) {
            targets.emplace_back(parent);
        }
        parent = parent->getParent();
    }
}

bool NodeEventProcessor::checknSetupSysEvent(const std::string &type) {
    bool newAdded    = false;
    bool forDispatch = false;
    // just for ui

    const auto &eventManager = EventManager::getInstance();
    if (std::find(TOUCH_EVENTS.begin(), TOUCH_EVENTS.end(), type) != TOUCH_EVENTS.end()) {
        if (_touchListener != nullptr) {
            IEventListenerCreateInfo info{
                .event = EventListener::TOUCH_ONE_BY_ONE,
                // TODO(xwx): how to implement?
                // swallowTouches : true,
                // owner : this._node,
                // mask : _searchComponentsInParent(this._node as Node, NodeEventProcessor._comp),
                // onTouchBegan : _touchStartHandler,
                // onTouchMoved : _touchMoveHandler,
                // onTouchEnded : _touchEndHandler,
                // onTouchCancelled : _touchCancelHandler,
            };
            _touchListener = EventListener::create(info);
            eventManager.addListener(_touchListener, dynamic_cast<Node *>(_node));
            newAdded = true;
        }
        forDispatch = true;
    } else if (std::find(MOUSE_EVENTS.begin(), MOUSE_EVENTS.end(), type) != MOUSE_EVENTS.end()) {
        if (_mouseListener != nullptr) {
            IEventListenerCreateInfo info{
                .event = EventListener::MOUSE,
                // TODO(xwx): how to implement?
                // _previousIn : false,
                // owner : this._node,
                // mask : _searchComponentsInParent(this._node as Node, NodeEventProcessor._comp),
                // onMouseDown : _mouseDownHandler,
                // onMouseMove : _mouseMoveHandler,
                // onMouseUp : _mouseUpHandler,
                // onMouseScroll : _mouseWheelHandler,
            };
            _mouseListener = EventListener::create(info);
            eventManager.addListener(_mouseListener, dynamic_cast<Node *>(_node));
            newAdded = true;
        }
        forDispatch = true;
    }
    // TODO(xwx): not sure use scheduler
    // if (newAdded && !_node->isActiveInHierarchy()) {
    //     Director::getInstance()->getScheduler()->schedule([](){
    //         if (!_node->isActiveInHierarchy()) {
    //             eventManager.pauseTarget(dynamic_cast<Node *>(_node));
    //         }
    //         }, _node, 0, 0, 0, false);
    // }
    return forDispatch;
}

void NodeEventProcessor::offDispatch(const std::string &type, bool useCapture) const { // TODO(xwx): need to check with ts logic, slightly different
    // if (!callback) {
    // if (_capturingTargets != nullptr) {
    //     _capturingTargets->offAll(type);
    // }
    // if (_bubblingTargets != nullptr) {
    //     _bubblingTargets->offAll(type);
    // }
    // }
    CallbacksInvoker *listeners = useCapture ? _capturingTargets : _bubblingTargets;
    if (listeners != nullptr) {
        listeners->off(type, _cbID);
    }
}

void NodeEventProcessor::offDispatch(const std::string &type, void *target, bool useCapture) const {
    if (typeid(target) == typeid(bool)) {
        useCapture = std::any_cast<bool>(target);
        target     = nullptr;
    }
    CallbacksInvoker *listeners = useCapture ? _capturingTargets : _bubblingTargets;
    if (listeners != nullptr) {
        listeners->off(type, _cbID, target);
    }
}

} // namespace cc
