/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "core/platform/event-manager/EventManager.h"
#include <algorithm>

#include "base/Macros.h"
#include "core/platform/event-manager/EventCustom.h"
#include "core/platform/event-manager/EventListenerAcceleration.h"
#include "core/platform/event-manager/EventListenerCustom.h"
#include "core/platform/event-manager/EventListenerKeyboard.h"
#include "core/platform/event-manager/EventListenerMouse.h"
#include "core/platform/event-manager/EventListenerTouch.h"
#include "core/platform/event-manager/EventTouch.h"
#include "core/platform/event-manager/EventType.h"
#include "core/platform/event-manager/Touch.h"
#include "core/scene-graph/Node.h"

#define DUMP_LISTENER_ITEM_PRIORITY_INFO 0

namespace {

class DispatchGuard {
public:
    DispatchGuard(int &count) : _count(count) {
        ++_count;
    }

    ~DispatchGuard() {
        --_count;
    }

private:
    int &_count;
};

} // namespace

NS_CC_EVENT_BEGIN

namespace {
EventManager *eventManager = nullptr;
}

EventManager *EventManager::getInstance() {
    if (eventManager == nullptr) {
        eventManager = new EventManager();
    }
    return eventManager;
}

void EventManager::destroyInstance(EventManager *manager) {
    CC_SAFE_DELETE(eventManager);
}

static EventListener::ListenerID __getListenerID(Event *event) {
    EventListener::ListenerID ret;
    switch (event->getEventType()) {
        case Event::Type::ACCELERATION:
            ret = EventListenerAcceleration::LISTENER_ID;
            break;
        case Event::Type::CUSTOM: {
            auto customEvent = static_cast<EventCustom *>(event);
            ret              = customEvent->getEventName();
        } break;
        case Event::Type::KEYBOARD:
            ret = EventListenerKeyboard::LISTENER_ID;
            break;
        case Event::Type::MOUSE:
            ret = EventListenerMouse::LISTENER_ID;
            break;
        case Event::Type::TOUCH:
            // Touch listener is very special, it contains two kinds of listeners, EventListenerTouchOneByOne and EventListenerTouchAllAtOnce.
            // return UNKNOWN instead.
            CCASSERT(false, "Don't call this method if the event is for touch.");
            break;
        default:
            CCASSERT(false, "Invalid type!");
            break;
    }

    return ret;
}

EventManager::EventListenerVector::EventListenerVector() : _fixedListeners(nullptr),
                                                           _sceneGraphListeners(nullptr),
                                                           _gt0Index(0) {
}

EventManager::EventListenerVector::~EventListenerVector() {
    CC_SAFE_DELETE(_sceneGraphListeners);
    CC_SAFE_DELETE(_fixedListeners);
}

size_t EventManager::EventListenerVector::size() const {
    size_t ret = 0;
    if (_sceneGraphListeners)
        ret += _sceneGraphListeners->size();
    if (_fixedListeners)
        ret += _fixedListeners->size();

    return ret;
}

bool EventManager::EventListenerVector::empty() const {
    return (_sceneGraphListeners == nullptr || _sceneGraphListeners->empty()) && (_fixedListeners == nullptr || _fixedListeners->empty());
}

void EventManager::EventListenerVector::push_back(EventListener *listener) {
#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
    CCASSERT(_sceneGraphListeners == nullptr ||
                 std::count(_sceneGraphListeners->begin(), _sceneGraphListeners->end(), listener) == 0,
             "Listener should not be added twice!");

    CCASSERT(_fixedListeners == nullptr ||
                 std::count(_fixedListeners->begin(), _fixedListeners->end(), listener) == 0,
             "Listener should not be added twice!");
#endif

    if (listener->getFixedPriority() == 0) {
        if (_sceneGraphListeners == nullptr) {
            _sceneGraphListeners = new (std::nothrow) std::vector<EventListener *>();
            _sceneGraphListeners->reserve(100);
        }

        _sceneGraphListeners->push_back(listener);
    } else {
        if (_fixedListeners == nullptr) {
            _fixedListeners = new std::vector<EventListener *>();
            _fixedListeners->reserve(100);
        }

        _fixedListeners->push_back(listener);
    }
}

void EventManager::EventListenerVector::clearSceneGraphListeners() {
    if (_sceneGraphListeners) {
        _sceneGraphListeners->clear();
        delete _sceneGraphListeners;
        _sceneGraphListeners = nullptr;
    }
}

void EventManager::EventListenerVector::clearFixedListeners() {
    if (_fixedListeners) {
        _fixedListeners->clear();
        delete _fixedListeners;
        _fixedListeners = nullptr;
    }
}

void EventManager::EventListenerVector::clear() {
    clearSceneGraphListeners();
    clearFixedListeners();
}

EventManager::EventManager()
: _inDispatch(0), _isEnabled(false), _nodePriorityIndex(0) {
    _toAddedListeners.reserve(50);
    _toRemovedListeners.reserve(50);

    // fixed #4129: Mark the following listener IDs for internal use.
    // Therefore, internal listeners would not be cleaned when removeAllEventListeners is invoked.
    _internalCustomListenerIDs.insert(EVENT_COME_TO_FOREGROUND);
    _internalCustomListenerIDs.insert(EVENT_COME_TO_BACKGROUND);
    _internalCustomListenerIDs.insert(EVENT_RENDERER_RECREATED);
}

EventManager::~EventManager() {
    // Clear internal custom listener IDs from set,
    // so removeAllEventListeners would clean internal custom listeners.
    _internalCustomListenerIDs.clear();
    removeAllEventListeners();
}

void EventManager::visitTarget(Node *node, bool isRootNode) {
    //cjh    node->sortAllChildren();
    //
    //    int i = 0;
    //    auto& children = node->getChildren();
    //
    //    auto childrenCount = children.size();
    //
    //    if(childrenCount > 0)
    //    {
    //        Node* child = nullptr;
    //        // visit children zOrder < 0
    //        for( ; i < childrenCount; i++ )
    //        {
    //            child = children.at(i);
    //
    //            if ( child && child->getLocalZOrder() < 0 )
    //                visitTarget(child, false);
    //            else
    //                break;
    //        }
    //
    //        if (_nodeListenersMap.find(node) != _nodeListenersMap.end())
    //        {
    //            _globalZOrderNodeMap[node->getGlobalZOrder()].push_back(node);
    //        }
    //
    //        for( ; i < childrenCount; i++ )
    //        {
    //            child = children.at(i);
    //            if (child)
    //                visitTarget(child, false);
    //        }
    //    }
    //    else
    //    {
    //        if (_nodeListenersMap.find(node) != _nodeListenersMap.end())
    //        {
    //            _globalZOrderNodeMap[node->getGlobalZOrder()].push_back(node);
    //        }
    //    }

    if (isRootNode) {
        std::vector<float> globalZOrders;
        globalZOrders.reserve(_globalZOrderNodeMap.size());

        for (const auto &e : _globalZOrderNodeMap) {
            globalZOrders.push_back(e.first);
        }

        std::stable_sort(globalZOrders.begin(), globalZOrders.end(), [](const float a, const float b) {
            return a < b;
        });

        for (const auto &globalZ : globalZOrders) {
            for (const auto &n : _globalZOrderNodeMap[globalZ]) {
                _nodePriorityMap[n] = ++_nodePriorityIndex;
            }
        }

        _globalZOrderNodeMap.clear();
    }
}

void EventManager::pauseEventListenersForTarget(Node *target, bool recursive /* = false */) {
    auto listenerIter = _nodeListenersMap.find(target);
    if (listenerIter != _nodeListenersMap.end()) {
        auto listeners = listenerIter->second;
        for (auto &l : *listeners) {
            l->setPaused(true);
        }
    }

    for (auto &listener : _toAddedListeners) {
        if (listener->getAssociatedNode() == target) {
            listener->setPaused(true);
        }
    }

    if (recursive) {
        //cjh        const auto& children = target->getChildren();
        //        for (const auto& child : children)
        //        {
        //            pauseEventListenersForTarget(child, true);
        //        }
    }
}

void EventManager::resumeEventListenersForTarget(Node *target, bool recursive /* = false */) {
    auto listenerIter = _nodeListenersMap.find(target);
    if (listenerIter != _nodeListenersMap.end()) {
        auto listeners = listenerIter->second;
        for (auto &l : *listeners) {
            l->setPaused(false);
        }
    }

    for (auto &listener : _toAddedListeners) {
        if (listener->getAssociatedNode() == target) {
            listener->setPaused(false);
        }
    }

    setDirtyForNode(target);

    if (recursive) {
        //cjh        const auto& children = target->getChildren();
        //        for (const auto& child : children)
        //        {
        //            resumeEventListenersForTarget(child, true);
        //        }
    }
}

void EventManager::removeEventListenersForTarget(Node *target, bool recursive /* = false */) {
    // Ensure the node is removed from these immediately also.
    // Don't want any dangling pointers or the possibility of dealing with deleted objects..
    _nodePriorityMap.erase(target);
    _dirtyNodes.erase(target);

    auto listenerIter = _nodeListenersMap.find(target);
    if (listenerIter != _nodeListenersMap.end()) {
        auto listeners     = listenerIter->second;
        auto listenersCopy = *listeners;
        for (auto &l : listenersCopy) {
            removeEventListener(l);
        }
    }

    // Bug fix: ensure there are no references to the node in the list of listeners to be added.
    // If we find any listeners associated with the destroyed node in this list then remove them.
    // This is to catch the scenario where the node gets destroyed before it's listener
    // is added into the event dispatcher fully. This could happen if a node registers a listener
    // and gets destroyed while we are dispatching an event (touch etc.)
    for (auto iter = _toAddedListeners.begin(); iter != _toAddedListeners.end();) {
        EventListener *listener = *iter;

        if (listener->getAssociatedNode() == target) {
            listener->setAssociatedNode(nullptr); // Ensure no dangling ptr to the target node.
            listener->setRegistered(false);
            releaseListener(listener);
            iter = _toAddedListeners.erase(iter);
        } else {
            ++iter;
        }
    }

    if (recursive) {
        //cjh        const auto& children = target->getChildren();
        //        for (const auto& child : children)
        //        {
        //            removeEventListenersForTarget(child, true);
        //        }
    }
}

void EventManager::associateNodeAndEventListener(Node *node, EventListener *listener) {
    std::vector<EventListener *> *listeners = nullptr;
    auto                          found     = _nodeListenersMap.find(node);
    if (found != _nodeListenersMap.end()) {
        listeners = found->second;
    } else {
        listeners = new (std::nothrow) std::vector<EventListener *>();
        _nodeListenersMap.emplace(node, listeners);
    }

    listeners->push_back(listener);
}

void EventManager::dissociateNodeAndEventListener(Node *node, EventListener *listener) {
    std::vector<EventListener *> *listeners = nullptr;
    auto                          found     = _nodeListenersMap.find(node);
    if (found != _nodeListenersMap.end()) {
        listeners = found->second;
        auto iter = std::find(listeners->begin(), listeners->end(), listener);
        if (iter != listeners->end()) {
            listeners->erase(iter);
        }

        if (listeners->empty()) {
            _nodeListenersMap.erase(found);
            delete listeners;
        }
    }
}

void EventManager::addEventListener(EventListener *listener) {
    if (_inDispatch == 0) {
        forceAddEventListener(listener);
    } else {
        _toAddedListeners.push_back(listener);
    }
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine) {
        sEngine->retainScriptObject(this, listener);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    listener->addRef();
}

void EventManager::forceAddEventListener(EventListener *listener) {
    EventListenerVector *     listeners  = nullptr;
    EventListener::ListenerID listenerID = listener->getListenerID();
    auto                      itr        = _listenerMap.find(listenerID);
    if (itr == _listenerMap.end()) {
        listeners = new (std::nothrow) EventListenerVector();
        _listenerMap.emplace(listenerID, listeners);
    } else {
        listeners = itr->second;
    }

    listeners->push_back(listener);

    if (listener->getFixedPriority() == 0) {
        setDirty(listenerID, DirtyFlag::SCENE_GRAPH_PRIORITY);

        auto node = listener->getAssociatedNode();
        CCASSERT(node != nullptr, "Invalid scene graph priority!");

        associateNodeAndEventListener(node, listener);

        //cjh        if (!node->isRunning())
        //        {
        //            listener->setPaused(true);
        //        }
    } else {
        setDirty(listenerID, DirtyFlag::FIXED_PRIORITY);
    }
}

void EventManager::addEventListenerWithSceneGraphPriority(EventListener *listener, Node *node) {
    CCASSERT(listener && node, "Invalid parameters.");
    CCASSERT(!listener->isRegistered(), "The listener has been registered.");

    if (!listener->checkAvailable())
        return;

    listener->setAssociatedNode(node);
    listener->setFixedPriority(0);
    listener->setRegistered(true);

    addEventListener(listener);
}

#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS && COCOS2D_DEBUG > 0

void EventManager::debugCheckNodeHasNoEventListenersOnDestruction(Node *node) {
    // Check the listeners map
    for (const auto &keyValuePair : _listenerMap) {
        const EventListenerVector *eventListenerVector = keyValuePair.second;

        if (eventListenerVector) {
            if (eventListenerVector->getSceneGraphPriorityListeners()) {
                for (EventListener *listener : *eventListenerVector->getSceneGraphPriorityListeners()) {
                    CCASSERT(!listener ||
                                 listener->getAssociatedNode() != node,
                             "Node should have no event listeners registered for it upon destruction!");
                }
            }
        }
    }

    // Check the node listeners map
    for (const auto &keyValuePair : _nodeListenersMap) {
        CCASSERT(keyValuePair.first != node, "Node should have no event listeners registered for it upon destruction!");

        if (keyValuePair.second) {
            for (EventListener *listener : *keyValuePair.second) {
                CCASSERT(listener->getAssociatedNode() != node,
                         "Node should have no event listeners registered for it upon destruction!");
            }
        }
    }

    // Check the node priority map
    for (const auto &keyValuePair : _nodePriorityMap) {
        CCASSERT(keyValuePair.first != node,
                 "Node should have no event listeners registered for it upon destruction!");
    }

    // Check the to be added list
    for (EventListener *listener : _toAddedListeners) {
        CCASSERT(listener->getAssociatedNode() != node,
                 "Node should have no event listeners registered for it upon destruction!");
    }

    // Check the dirty nodes set
    for (Node *dirtyNode : _dirtyNodes) {
        CCASSERT(dirtyNode != node,
                 "Node should have no event listeners registered for it upon destruction!");
    }
}

#endif // #if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS && COCOS2D_DEBUG > 0

void EventManager::addEventListenerWithFixedPriority(EventListener *listener, int fixedPriority) {
    CCASSERT(listener, "Invalid parameters.");
    CCASSERT(!listener->isRegistered(), "The listener has been registered.");
    CCASSERT(fixedPriority != 0, "0 priority is forbidden for fixed priority since it's used for scene graph based priority.");

    if (!listener->checkAvailable())
        return;

    listener->setAssociatedNode(nullptr);
    listener->setFixedPriority(fixedPriority);
    listener->setRegistered(true);
    listener->setPaused(false);

    addEventListener(listener);
}

EventListenerCustom *EventManager::addCustomEventListener(const CallbacksInvoker::KeyType &eventName, const std::function<void(EventCustom *)> &callback) {
    EventListenerCustom *listener = EventListenerCustom::create(eventName, callback);
    addEventListenerWithFixedPriority(listener, 1);
    return listener;
}

void EventManager::removeEventListener(EventListener *listener) {
    if (listener == nullptr)
        return;

    // just return if listener is in _toRemovedListeners to avoid remove listeners more than once
    if (std::find(_toRemovedListeners.begin(), _toRemovedListeners.end(), listener) != _toRemovedListeners.end())
        return;

    bool isFound = false;

    auto removeListenerInVector = [&](std::vector<EventListener *> *listeners) {
        if (listeners == nullptr)
            return;

        for (auto iter = listeners->begin(); iter != listeners->end(); ++iter) {
            auto l = *iter;
            if (l == listener) {
                l->addRef();
                l->setRegistered(false);
                if (l->getAssociatedNode() != nullptr) {
                    dissociateNodeAndEventListener(l->getAssociatedNode(), l);
                    l->setAssociatedNode(nullptr); // nullptr out the node pointer so we don't have any dangling pointers to destroyed nodes.
                }

                if (_inDispatch == 0) {
                    iter = listeners->erase(iter);
                    releaseListener(l);
                } else {
                    _toRemovedListeners.push_back(l);
                }

                isFound = true;
                break;
            }
        }
    };

    for (auto iter = _listenerMap.begin(); iter != _listenerMap.end();) {
        auto listeners                   = iter->second;
        auto fixedPriorityListeners      = listeners->getFixedPriorityListeners();
        auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();

        removeListenerInVector(sceneGraphPriorityListeners);
        if (isFound) {
            // fixed #4160: Dirty flag need to be updated after listeners were removed.
            setDirty(listener->getListenerID(), DirtyFlag::SCENE_GRAPH_PRIORITY);
        } else {
            removeListenerInVector(fixedPriorityListeners);
            if (isFound) {
                setDirty(listener->getListenerID(), DirtyFlag::FIXED_PRIORITY);
            }
        }

#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS
        CCASSERT(_inDispatch != 0 ||
                     !sceneGraphPriorityListeners ||
                     std::count(sceneGraphPriorityListeners->begin(), sceneGraphPriorityListeners->end(), listener) == 0,
                 "Listener should be in no lists after this is done if we're not currently in dispatch mode.");

        CCASSERT(_inDispatch != 0 ||
                     !fixedPriorityListeners ||
                     std::count(fixedPriorityListeners->begin(), fixedPriorityListeners->end(), listener) == 0,
                 "Listener should be in no lists after this is done if we're not currently in dispatch mode.");
#endif

        if (iter->second->empty()) {
            _priorityDirtyFlagMap.erase(listener->getListenerID());
            auto list = iter->second;
            iter      = _listenerMap.erase(iter);
            CC_SAFE_DELETE(list);
        } else {
            ++iter;
        }

        if (isFound)
            break;
    }

    if (isFound) {
        releaseListener(listener);
    } else {
        for (auto iter = _toAddedListeners.begin(); iter != _toAddedListeners.end(); ++iter) {
            if (*iter == listener) {
                listener->setRegistered(false);
                releaseListener(listener);
                _toAddedListeners.erase(iter);
                break;
            }
        }
    }
}

void EventManager::setPriority(EventListener *listener, int fixedPriority) {
    if (listener == nullptr)
        return;

    for (auto &iter : _listenerMap) {
        auto fixedPriorityListeners = iter.second->getFixedPriorityListeners();
        if (fixedPriorityListeners) {
            auto found = std::find(fixedPriorityListeners->begin(), fixedPriorityListeners->end(), listener);
            if (found != fixedPriorityListeners->end()) {
                CCASSERT(listener->getAssociatedNode() == nullptr, "Can't set fixed priority with scene graph based listener.");

                if (listener->getFixedPriority() != fixedPriority) {
                    listener->setFixedPriority(fixedPriority);
                    setDirty(listener->getListenerID(), DirtyFlag::FIXED_PRIORITY);
                }
                return;
            }
        }
    }
}

void EventManager::dispatchEventToListeners(EventListenerVector *listeners, const std::function<bool(EventListener *)> &onEvent) {
    bool shouldStopPropagation       = false;
    auto fixedPriorityListeners      = listeners->getFixedPriorityListeners();
    auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();

    ssize_t i = 0;
    // priority < 0
    if (fixedPriorityListeners) {
        CCASSERT(listeners->getGt0Index() <= static_cast<ssize_t>(fixedPriorityListeners->size()), "Out of range exception!");

        if (!fixedPriorityListeners->empty()) {
            for (; i < listeners->getGt0Index(); ++i) {
                auto l = fixedPriorityListeners->at(i);
                if (l->isEnabled() && !l->isPaused() && l->isRegistered() && onEvent(l)) {
                    shouldStopPropagation = true;
                    break;
                }
            }
        }
    }

    if (sceneGraphPriorityListeners) {
        if (!shouldStopPropagation) {
            // priority == 0, scene graph priority
            for (auto &l : *sceneGraphPriorityListeners) {
                if (l->isEnabled() && !l->isPaused() && l->isRegistered() && onEvent(l)) {
                    shouldStopPropagation = true;
                    break;
                }
            }
        }
    }

    if (fixedPriorityListeners) {
        if (!shouldStopPropagation) {
            // priority > 0
            ssize_t size = fixedPriorityListeners->size();
            for (; i < size; ++i) {
                auto l = fixedPriorityListeners->at(i);

                if (l->isEnabled() && !l->isPaused() && l->isRegistered() && onEvent(l)) {
                    shouldStopPropagation = true;
                    break;
                }
            }
        }
    }
}

void EventManager::dispatchTouchEventToListeners(EventListenerVector *listeners, const std::function<bool(EventListener *)> &onEvent) {
    bool shouldStopPropagation       = false;
    auto fixedPriorityListeners      = listeners->getFixedPriorityListeners();
    auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();

    ssize_t i = 0;
    // priority < 0
    if (fixedPriorityListeners) {
        CCASSERT(listeners->getGt0Index() <= static_cast<ssize_t>(fixedPriorityListeners->size()), "Out of range exception!");

        if (!fixedPriorityListeners->empty()) {
            for (; i < listeners->getGt0Index(); ++i) {
                auto l = fixedPriorityListeners->at(i);
                if (l->isEnabled() && !l->isPaused() && l->isRegistered() && onEvent(l)) {
                    shouldStopPropagation = true;
                    break;
                }
            }
        }
    }

    //cjh    auto scene = Director::getInstance()->getRunningScene();
    //    if (scene && sceneGraphPriorityListeners)
    //    {
    //        if (!shouldStopPropagation)
    //        {
    //            // priority == 0, scene graph priority
    //
    //            // first, get all enabled, unPaused and registered listeners
    //            std::vector<EventListener*> sceneListeners;
    //            for (auto& l : *sceneGraphPriorityListeners)
    //            {
    //                if (l->isEnabled() && !l->isPaused() && l->isRegistered())
    //                {
    //                    sceneListeners.push_back(l);
    //                }
    //            }
    //            // second, for all camera call all listeners
    //            // get a copy of cameras, prevent it's been modified in listener callback
    //            // if camera's depth is greater, process it earlier
    //            auto cameras = scene->getCameras();
    //            for (auto rit = cameras.rbegin(), ritRend = cameras.rend(); rit != ritRend; ++rit)
    //            {
    //                Camera* camera = *rit;
    //                if (camera->isVisible() == false)
    //                {
    //                    continue;
    //                }
    //
    //                Camera::_visitingCamera = camera;
    //                auto cameraFlag = (unsigned short)camera->getCameraFlag();
    //                for (auto& l : sceneListeners)
    //                {
    //                    if (nullptr == l->getAssociatedNode() || 0 == (l->getAssociatedNode()->getCameraMask() & cameraFlag))
    //                    {
    //                        continue;
    //                    }
    //                    if (onEvent(l))
    //                    {
    //                        shouldStopPropagation = true;
    //                        break;
    //                    }
    //                }
    //                if (shouldStopPropagation)
    //                {
    //                    break;
    //                }
    //            }
    //            Camera::_visitingCamera = nullptr;
    //        }
    //    }

    if (fixedPriorityListeners) {
        if (!shouldStopPropagation) {
            // priority > 0
            ssize_t size = fixedPriorityListeners->size();
            for (; i < size; ++i) {
                auto l = fixedPriorityListeners->at(i);

                if (l->isEnabled() && !l->isPaused() && l->isRegistered() && onEvent(l)) {
                    shouldStopPropagation = true;
                    break;
                }
            }
        }
    }
}

void EventManager::dispatchEvent(Event *event) {
    if (!_isEnabled)
        return;

    updateDirtyFlagForSceneGraph();

    DispatchGuard guard(_inDispatch);

    if (event->getEventType() == Event::Type::TOUCH) {
        dispatchTouchEvent(static_cast<EventTouch *>(event));
        return;
    }

    auto listenerID = __getListenerID(event);

    sortEventListeners(listenerID);

    auto pfnDispatchEventToListeners = &EventManager::dispatchEventToListeners;
    if (event->getEventType() == Event::Type::MOUSE) {
        pfnDispatchEventToListeners = &EventManager::dispatchTouchEventToListeners;
    }
    auto iter = _listenerMap.find(listenerID);
    if (iter != _listenerMap.end()) {
        auto listeners = iter->second;

        auto onEvent = [&event](EventListener *listener) -> bool {
            event->setCurrentTarget(listener->getAssociatedNode());
            listener->_onEvent(event);
            return event->isStopped();
        };

        (this->*pfnDispatchEventToListeners)(listeners, onEvent);
    }

    updateListeners(event);
}

void EventManager::dispatchCustomEvent(const CallbacksInvoker::KeyType &eventName, void *optionalUserData) {
    EventCustom ev(eventName);
    ev.setUserData(optionalUserData);
    dispatchEvent(&ev);
}

bool EventManager::hasEventListener(const EventListener::ListenerID &listenerID) const {
    return getListeners(listenerID) != nullptr;
}

void EventManager::dispatchTouchEvent(EventTouch *event) {
    sortEventListeners(EventListenerTouchOneByOne::LISTENER_ID);
    sortEventListeners(EventListenerTouchAllAtOnce::LISTENER_ID);

    auto oneByOneListeners  = getListeners(EventListenerTouchOneByOne::LISTENER_ID);
    auto allAtOnceListeners = getListeners(EventListenerTouchAllAtOnce::LISTENER_ID);

    // If there aren't any touch listeners, return directly.
    if (nullptr == oneByOneListeners && nullptr == allAtOnceListeners)
        return;

    bool isNeedsMutableSet = (oneByOneListeners && allAtOnceListeners);

    const std::vector<Touch *> &originalTouches = event->getTouches();
    std::vector<Touch *>        mutableTouches(originalTouches.size());
    std::copy(originalTouches.begin(), originalTouches.end(), mutableTouches.begin());

    //
    // process the target handlers 1st
    //
    if (oneByOneListeners) {
        auto mutableTouchesIter = mutableTouches.begin();

        for (auto &touches : originalTouches) {
            bool isSwallowed = false;

            auto onTouchEvent = [&](EventListener *l) -> bool { // Return true to break
                EventListenerTouchOneByOne *listener = static_cast<EventListenerTouchOneByOne *>(l);

                // Skip if the listener was removed.
                if (!listener->_isRegistered)
                    return false;

                event->setCurrentTarget(listener->_node);

                bool                           isClaimed = false;
                std::vector<Touch *>::iterator removedIter;

                EventTouch::EventCode eventCode = event->getEventCode();

                if (eventCode == EventTouch::EventCode::BEGAN) {
                    if (listener->onTouchBegan) {
                        isClaimed = listener->onTouchBegan(touches, event);
                        if (isClaimed && listener->_isRegistered) {
                            listener->_claimedTouches.push_back(touches);
                        }
                    }
                } else if (!listener->_claimedTouches.empty() && ((removedIter = std::find(listener->_claimedTouches.begin(), listener->_claimedTouches.end(), touches)) != listener->_claimedTouches.end())) {
                    isClaimed = true;

                    switch (eventCode) {
                        case EventTouch::EventCode::MOVED:
                            if (listener->onTouchMoved) {
                                listener->onTouchMoved(touches, event);
                            }
                            break;
                        case EventTouch::EventCode::ENDED:
                            if (listener->onTouchEnded) {
                                listener->onTouchEnded(touches, event);
                            }
                            if (listener->_isRegistered) {
                                listener->_claimedTouches.erase(removedIter);
                            }
                            break;
                        case EventTouch::EventCode::CANCELLED:
                            if (listener->onTouchCancelled) {
                                listener->onTouchCancelled(touches, event);
                            }
                            if (listener->_isRegistered) {
                                listener->_claimedTouches.erase(removedIter);
                            }
                            break;
                        default:
                            CCASSERT(false, "The eventcode is invalid.");
                            break;
                    }
                }

                // If the event was stopped, return directly.
                if (event->isStopped()) {
                    updateListeners(event);
                    return true;
                }

                CCASSERT(touches->getID() == (*mutableTouchesIter)->getID(),
                         "touches ID should be equal to mutableTouchesIter's ID.");

                if (isClaimed && listener->_isRegistered && listener->_needSwallow) {
                    if (isNeedsMutableSet) {
                        mutableTouchesIter = mutableTouches.erase(mutableTouchesIter);
                        isSwallowed        = true;
                    }
                    return true;
                }

                return false;
            };

            //
            dispatchTouchEventToListeners(oneByOneListeners, onTouchEvent);
            if (event->isStopped()) {
                return;
            }

            if (!isSwallowed)
                ++mutableTouchesIter;
        }
    }

    //
    // process standard handlers 2nd
    //
    if (allAtOnceListeners && !mutableTouches.empty()) {
        auto onTouchesEvent = [&](EventListener *l) -> bool {
            EventListenerTouchAllAtOnce *listener = static_cast<EventListenerTouchAllAtOnce *>(l);
            // Skip if the listener was removed.
            if (!listener->_isRegistered)
                return false;

            event->setCurrentTarget(listener->_node);

            switch (event->getEventCode()) {
                case EventTouch::EventCode::BEGAN:
                    if (listener->onTouchesBegan) {
                        listener->onTouchesBegan(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::MOVED:
                    if (listener->onTouchesMoved) {
                        listener->onTouchesMoved(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::ENDED:
                    if (listener->onTouchesEnded) {
                        listener->onTouchesEnded(mutableTouches, event);
                    }
                    break;
                case EventTouch::EventCode::CANCELLED:
                    if (listener->onTouchesCancelled) {
                        listener->onTouchesCancelled(mutableTouches, event);
                    }
                    break;
                default:
                    CCASSERT(false, "The eventcode is invalid.");
                    break;
            }

            // If the event was stopped, return directly.
            if (event->isStopped()) {
                updateListeners(event);
                return true;
            }

            return false;
        };

        dispatchTouchEventToListeners(allAtOnceListeners, onTouchesEvent);
        if (event->isStopped()) {
            return;
        }
    }

    updateListeners(event);
}

void EventManager::updateListeners(Event *event) {
    CCASSERT(_inDispatch > 0, "If program goes here, there should be event in dispatch.");

    if (_inDispatch > 1)
        return;

    auto onUpdateListeners = [this](const EventListener::ListenerID &listenerID) {
        auto listenersIter = _listenerMap.find(listenerID);
        if (listenersIter == _listenerMap.end())
            return;

        auto listeners = listenersIter->second;

        auto fixedPriorityListeners      = listeners->getFixedPriorityListeners();
        auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();

        if (sceneGraphPriorityListeners) {
            for (auto iter = sceneGraphPriorityListeners->begin(); iter != sceneGraphPriorityListeners->end();) {
                auto l = *iter;
                if (!l->isRegistered()) {
                    iter = sceneGraphPriorityListeners->erase(iter);
                    // if item in toRemove list, remove it from the list
                    auto matchIter = std::find(_toRemovedListeners.begin(), _toRemovedListeners.end(), l);
                    if (matchIter != _toRemovedListeners.end())
                        _toRemovedListeners.erase(matchIter);
                    releaseListener(l);
                } else {
                    ++iter;
                }
            }
        }

        if (fixedPriorityListeners) {
            for (auto iter = fixedPriorityListeners->begin(); iter != fixedPriorityListeners->end();) {
                auto l = *iter;
                if (!l->isRegistered()) {
                    iter = fixedPriorityListeners->erase(iter);
                    // if item in toRemove list, remove it from the list
                    auto matchIter = std::find(_toRemovedListeners.begin(), _toRemovedListeners.end(), l);
                    if (matchIter != _toRemovedListeners.end())
                        _toRemovedListeners.erase(matchIter);
                    releaseListener(l);
                } else {
                    ++iter;
                }
            }
        }

        if (sceneGraphPriorityListeners && sceneGraphPriorityListeners->empty()) {
            listeners->clearSceneGraphListeners();
        }

        if (fixedPriorityListeners && fixedPriorityListeners->empty()) {
            listeners->clearFixedListeners();
        }
    };

    if (event->getEventType() == Event::Type::TOUCH) {
        onUpdateListeners(EventListenerTouchOneByOne::LISTENER_ID);
        onUpdateListeners(EventListenerTouchAllAtOnce::LISTENER_ID);
    } else {
        onUpdateListeners(__getListenerID(event));
    }

    CCASSERT(_inDispatch == 1, "_inDispatch should be 1 here.");

    for (auto iter = _listenerMap.begin(); iter != _listenerMap.end();) {
        if (iter->second->empty()) {
            _priorityDirtyFlagMap.erase(iter->first);
            delete iter->second;
            iter = _listenerMap.erase(iter);
        } else {
            ++iter;
        }
    }

    if (!_toAddedListeners.empty()) {
        for (auto &listener : _toAddedListeners) {
            forceAddEventListener(listener);
        }
        _toAddedListeners.clear();
    }

    if (!_toRemovedListeners.empty()) {
        cleanToRemovedListeners();
    }
}

void EventManager::updateDirtyFlagForSceneGraph() {
    if (!_dirtyNodes.empty()) {
        for (auto &node : _dirtyNodes) {
            auto iter = _nodeListenersMap.find(node);
            if (iter != _nodeListenersMap.end()) {
                for (auto &l : *iter->second) {
                    setDirty(l->getListenerID(), DirtyFlag::SCENE_GRAPH_PRIORITY);
                }
            }
        }

        _dirtyNodes.clear();
    }
}

void EventManager::sortEventListeners(const EventListener::ListenerID &listenerID) {
    DirtyFlag dirtyFlag = DirtyFlag::NONE;

    auto dirtyIter = _priorityDirtyFlagMap.find(listenerID);
    if (dirtyIter != _priorityDirtyFlagMap.end()) {
        dirtyFlag = dirtyIter->second;
    }

    if (dirtyFlag != DirtyFlag::NONE) {
        // Clear the dirty flag first, if `rootNode` is nullptr, then set its dirty flag of scene graph priority
        dirtyIter->second = DirtyFlag::NONE;

        if ((int)dirtyFlag & (int)DirtyFlag::FIXED_PRIORITY) {
            sortEventListenersOfFixedPriority(listenerID);
        }

        if ((int)dirtyFlag & (int)DirtyFlag::SCENE_GRAPH_PRIORITY) {
            //cjh            auto rootNode = Director::getInstance()->getRunningScene();
            //            if (rootNode)
            //            {
            //                sortEventListenersOfSceneGraphPriority(listenerID, rootNode);
            //            }
            //            else
            //            {
            //                dirtyIter->second = DirtyFlag::SCENE_GRAPH_PRIORITY;
            //            }
        }
    }
}

void EventManager::sortEventListenersOfSceneGraphPriority(const EventListener::ListenerID &listenerID, Node *rootNode) {
    auto listeners = getListeners(listenerID);

    if (listeners == nullptr)
        return;
    auto sceneGraphListeners = listeners->getSceneGraphPriorityListeners();

    if (sceneGraphListeners == nullptr)
        return;

    // Reset priority index
    _nodePriorityIndex = 0;
    _nodePriorityMap.clear();

    visitTarget(rootNode, true);

    // After sort: priority < 0, > 0
    std::stable_sort(sceneGraphListeners->begin(), sceneGraphListeners->end(), [this](const EventListener *l1, const EventListener *l2) {
        return _nodePriorityMap[l1->getAssociatedNode()] > _nodePriorityMap[l2->getAssociatedNode()];
    });

#if DUMP_LISTENER_ITEM_PRIORITY_INFO
    log("-----------------------------------");
    for (auto &l : *sceneGraphListeners) {
        log("listener priority: node ([%s]%p), priority (%d)", typeid(*l->_node).name(), l->_node, _nodePriorityMap[l->_node]);
    }
#endif
}

void EventManager::sortEventListenersOfFixedPriority(const EventListener::ListenerID &listenerID) {
    auto listeners = getListeners(listenerID);

    if (listeners == nullptr)
        return;

    auto fixedListeners = listeners->getFixedPriorityListeners();
    if (fixedListeners == nullptr)
        return;

    // After sort: priority < 0, > 0
    std::stable_sort(fixedListeners->begin(), fixedListeners->end(), [](const EventListener *l1, const EventListener *l2) {
        return l1->getFixedPriority() < l2->getFixedPriority();
    });

    // FIXME: Should use binary search
    int index = 0;
    for (auto &listener : *fixedListeners) {
        if (listener->getFixedPriority() >= 0)
            break;
        ++index;
    }

    listeners->setGt0Index(index);

#if DUMP_LISTENER_ITEM_PRIORITY_INFO
    log("-----------------------------------");
    for (auto &l : *fixedListeners) {
        log("listener priority: node (%p), fixed (%d)", l->_node, l->_fixedPriority);
    }
#endif
}

EventManager::EventListenerVector *EventManager::getListeners(const EventListener::ListenerID &listenerID) const {
    auto iter = _listenerMap.find(listenerID);
    if (iter != _listenerMap.end()) {
        return iter->second;
    }

    return nullptr;
}

void EventManager::removeEventListenersForListenerID(const EventListener::ListenerID &listenerID) {
    auto listenerItemIter = _listenerMap.find(listenerID);
    if (listenerItemIter != _listenerMap.end()) {
        auto listeners                   = listenerItemIter->second;
        auto fixedPriorityListeners      = listeners->getFixedPriorityListeners();
        auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();

        auto removeAllListenersInVector = [&](std::vector<EventListener *> *listenerVector) {
            if (listenerVector == nullptr)
                return;

            for (auto iter = listenerVector->begin(); iter != listenerVector->end();) {
                auto l = *iter;
                l->setRegistered(false);
                if (l->getAssociatedNode() != nullptr) {
                    dissociateNodeAndEventListener(l->getAssociatedNode(), l);
                    l->setAssociatedNode(nullptr); // nullptr out the node pointer so we don't have any dangling pointers to destroyed nodes.
                }

                if (_inDispatch == 0) {
                    iter = listenerVector->erase(iter);
                    releaseListener(l);
                } else {
                    ++iter;
                }
            }
        };

        removeAllListenersInVector(sceneGraphPriorityListeners);
        removeAllListenersInVector(fixedPriorityListeners);

        // Remove the dirty flag according the 'listenerID'.
        // No need to check whether the dispatcher is dispatching event.
        _priorityDirtyFlagMap.erase(listenerID);

        if (!_inDispatch) {
            listeners->clear();
            delete listeners;
            _listenerMap.erase(listenerItemIter);
        }
    }

    for (auto iter = _toAddedListeners.begin(); iter != _toAddedListeners.end();) {
        if ((*iter)->getListenerID() == listenerID) {
            (*iter)->setRegistered(false);
            releaseListener(*iter);
            iter = _toAddedListeners.erase(iter);
        } else {
            ++iter;
        }
    }
}

void EventManager::removeEventListenersForType(EventListener::Type listenerType) {
    if (listenerType == EventListener::Type::TOUCH_ONE_BY_ONE) {
        removeEventListenersForListenerID(EventListenerTouchOneByOne::LISTENER_ID);
    } else if (listenerType == EventListener::Type::TOUCH_ALL_AT_ONCE) {
        removeEventListenersForListenerID(EventListenerTouchAllAtOnce::LISTENER_ID);
    } else if (listenerType == EventListener::Type::MOUSE) {
        removeEventListenersForListenerID(EventListenerMouse::LISTENER_ID);
    } else if (listenerType == EventListener::Type::ACCELERATION) {
        removeEventListenersForListenerID(EventListenerAcceleration::LISTENER_ID);
    } else if (listenerType == EventListener::Type::KEYBOARD) {
        removeEventListenersForListenerID(EventListenerKeyboard::LISTENER_ID);
    } else {
        CCASSERT(false, "Invalid listener type!");
    }
}

void EventManager::removeCustomEventListeners(const EventListener::ListenerID &customEventName) {
    removeEventListenersForListenerID(customEventName);
}

void EventManager::removeAllEventListeners() {
    bool                                   cleanMap = true;
    std::vector<EventListener::ListenerID> types;
    types.reserve(_listenerMap.size());

    for (const auto &e : _listenerMap) {
        if (_internalCustomListenerIDs.find(e.first) != _internalCustomListenerIDs.end()) {
            cleanMap = false;
        } else {
            types.push_back(e.first);
        }
    }

    for (const auto &type : types) {
        removeEventListenersForListenerID(type);
    }

    if (!_inDispatch && cleanMap) {
        _listenerMap.clear();
    }
}

void EventManager::setEnabled(bool isEnabled) {
    _isEnabled = isEnabled;
}

bool EventManager::isEnabled() const {
    return _isEnabled;
}

void EventManager::setDirtyForNode(Node *node) {
    // Mark the node dirty only when there is an eventlistener associated with it.
    if (_nodeListenersMap.find(node) != _nodeListenersMap.end()) {
        _dirtyNodes.insert(node);
    }

    // Also set the dirty flag for node's children
    //cjh    const auto& children = node->getChildren();
    //    for (const auto& child : children)
    //    {
    //        setDirtyForNode(child);
    //    }
}

void EventManager::setDirty(const EventListener::ListenerID &listenerID, DirtyFlag flag) {
    auto iter = _priorityDirtyFlagMap.find(listenerID);
    if (iter == _priorityDirtyFlagMap.end()) {
        _priorityDirtyFlagMap.emplace(listenerID, flag);
    } else {
        int ret      = (int)flag | (int)iter->second;
        iter->second = (DirtyFlag)ret;
    }
}

void EventManager::cleanToRemovedListeners() {
    for (auto &l : _toRemovedListeners) {
        auto listenersIter = _listenerMap.find(l->getListenerID());
        if (listenersIter == _listenerMap.end()) {
            releaseListener(l);
            continue;
        }

        bool find                        = false;
        auto listeners                   = listenersIter->second;
        auto fixedPriorityListeners      = listeners->getFixedPriorityListeners();
        auto sceneGraphPriorityListeners = listeners->getSceneGraphPriorityListeners();

        if (sceneGraphPriorityListeners) {
            auto machedIter = std::find(sceneGraphPriorityListeners->begin(), sceneGraphPriorityListeners->end(), l);
            if (machedIter != sceneGraphPriorityListeners->end()) {
                find = true;
                releaseListener(l);
                sceneGraphPriorityListeners->erase(machedIter);
            }
        }

        if (fixedPriorityListeners) {
            auto machedIter = std::find(fixedPriorityListeners->begin(), fixedPriorityListeners->end(), l);
            if (machedIter != fixedPriorityListeners->end()) {
                find = true;
                releaseListener(l);
                fixedPriorityListeners->erase(machedIter);
            }
        }

        if (find) {
            if (sceneGraphPriorityListeners && sceneGraphPriorityListeners->empty()) {
                listeners->clearSceneGraphListeners();
            }

            if (fixedPriorityListeners && fixedPriorityListeners->empty()) {
                listeners->clearFixedListeners();
            }
        } else
            CC_SAFE_RELEASE(l);
    }

    _toRemovedListeners.clear();
}

void EventManager::releaseListener(EventListener *listener) {
    CC_SAFE_RELEASE(listener);
}

NS_CC_EVENT_END