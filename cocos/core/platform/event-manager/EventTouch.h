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

#ifndef __cocos2d_libs__TouchEvent__
#define __cocos2d_libs__TouchEvent__

#include <vector>
#include "core/event/Event.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_EVENT_BEGIN

class Touch;

#define TOUCH_PERF_DEBUG 1

/** @class EventTouch
 * @brief Touch event.
 */
class CC_DLL EventTouch : public Event {
public:
    static const int MAX_TOUCHES = 15;

    /** EventCode Touch event code.*/
    enum class EventCode {
        BEGAN,
        MOVED,
        ENDED,
        CANCELLED
    };

    /**
     * Constructor.
     * @js NA
     */
    EventTouch(EventCode eventCode, bool bubbles);

    /** Get event code.
     *
     * @return The code of the event.
     */
    EventCode getEventCode() const { return _eventCode; }

    /** Get the touches.
     *
     * @return The touches of the event.
     */
    const std::vector<Touch *> &getTouches() const { return _touches; }

#if TOUCH_PERF_DEBUG
    /** Set the event code.
     * 
     * @param eventCode A given EventCode.
     */
    void setEventCode(EventCode eventCode) { _eventCode = eventCode; };
    /** Set the touches
     *
     * @param touches A given touches vector.
     */
    void setTouches(const std::vector<Touch *> &touches) { _touches = touches; };
#endif

    void         setTouch(Touch *touch) { _touch = touch; }
    const Touch *getTouch() const { return _touch; }

private:
    /**
     * @en The current touch object
     * @zh 当前触点对象
     */
    Touch *_touch{nullptr};
    /**
     * @en Indicate whether the touch event is simulated or real
     * @zh 表示触摸事件是真实触点触发的还是模拟的
     */
    bool simulate{false};

    EventCode            _eventCode{};
    std::vector<Touch *> _touches;
    std::vector<Touch *> _allTouches;
};

NS_CC_EVENT_END

// end of base group
/// @}

#endif /* defined(__cocos2d_libs__TouchEvent__) */
