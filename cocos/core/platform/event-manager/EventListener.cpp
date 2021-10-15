
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
#include "core/platform/event-manager/EventListener.h"
namespace cc {

EventListener *EventListener::create(const IEventListenerCreateInfo &argObj) {
    // assertID(argObj && argObj.event, 1900);

    const int32_t &listenerType = argObj.event;
    EventListener *listener     = nullptr;

    // TODO(xwx): subclasses not implement
    if (listenerType == EventListener::TOUCH_ONE_BY_ONE) {
        // listener = new TouchOneByOneEventListener();
    } else if (listenerType == EventListener::TOUCH_ALL_AT_ONCE) {
        // listener = new TouchAllAtOnceEventListener();
    } else if (listenerType == EventListener::MOUSE) {
        // listener = new MouseEventListener();
    } else if (listenerType == EventListener::KEYBOARD) {
        // listener = new KeyboardEventListener();
    } else if (listenerType == EventListener::ACCELERATION) {
        // listener = new AccelerationEventListener(argObj.callback); // TODO(xwx)
        // delete argObj.callback;
    }
    // TODO(xwx): how to implement in cpp?
    // if (listener) {
    //     for (const key of Object.keys(argObj)) {
    //         listener[key] = argObj[key];
    //     }
    // }
    return listener;
}

} // namespace cc
