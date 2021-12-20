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

#include "core/platform/event-manager/EventListenerAcceleration.h"
#include "base/Log.h"
#include "base/Macros.h"
#include "base/DeferredReleasePool.h"
#include "core/platform/event-manager/EventAcceleration.h"

NS_CC_EVENT_BEGIN

const EventListener::ListenerID EventListenerAcceleration::LISTENER_ID = 0; //"__cc_acceleration";

EventListenerAcceleration::EventListenerAcceleration() {
}

EventListenerAcceleration::~EventListenerAcceleration() {
    CC_LOG_DEBUG("In the destructor of AccelerationEventListener. %p", this);
}

EventListenerAcceleration *EventListenerAcceleration::create(const std::function<void(Acceleration *, Event *)> &callback) {
    EventListenerAcceleration *ret = new (std::nothrow) EventListenerAcceleration();
    if (ret && ret->init(callback)) {
        cc::DeferredReleasePool::add(ret);
    } else {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool EventListenerAcceleration::init(const std::function<void(Acceleration *, Event *event)> &callback) {
    auto listener = [this](Event *event) {
        auto accEvent = static_cast<EventAcceleration *>(event);
        this->onAccelerationEvent(&accEvent->_acc, event);
    };

    if (EventListener::init(Type::ACCELERATION, LISTENER_ID, listener)) {
        onAccelerationEvent = callback;
        return true;
    }

    return false;
}

EventListenerAcceleration *EventListenerAcceleration::clone() {
    auto ret = new (std::nothrow) EventListenerAcceleration();

    if (ret) {
        if (!ret->init(onAccelerationEvent)) {
            CC_SAFE_DELETE(ret);
        }
    }

    return ret;
}

bool EventListenerAcceleration::checkAvailable() {
    CCASSERT(onAccelerationEvent, "onAccelerationEvent can't be nullptr!");

    return true;
}

NS_CC_EVENT_END