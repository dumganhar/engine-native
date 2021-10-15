
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

#include "core/platform/event-manager/Events.h"

#include <utility>

namespace cc {

// EventMouse

EventMouse::EventMouse(const std::string &eventType, bool bubbles) : Event(eventType, bubbles), _eventType(eventType) {}

EventMouse::EventMouse(const std::string &eventType, bool bubbles, const Vec2 &prevLoc) : Event(eventType, bubbles), _eventType(eventType), _prevX(prevLoc.x), _prevY(prevLoc.y) {}

void EventMouse::setScrollData(float scrollX, float scrollY) {
    _scrollX = scrollX;
    _scrollY = scrollY;
}

float EventMouse::getScrollX() const {
    return _scrollX;
}

float EventMouse::getScrollY() const {
    return _scrollY;
}

void EventMouse::setLocation(float x, float y) {
    _x = x;
    _y = y;
}

Vec2 EventMouse::getLocation() const {
    return Vec2(_x, _y);
}

Vec2 EventMouse::getLocation(Vec2 &out) const {
    out.set(_x, _y);
    return out;
}

Vec2 EventMouse::getUILocation() const {
    Vec2 out(_x, _y);
    View::getInstance().convertPointWithScale(out);
    return out;
}

Vec2 EventMouse::getUILocation(Vec2 &out) const {
    out.set(_x, _y);
    View::getInstance().convertPointWithScale(out);
    return out;
}

Vec2 EventMouse::getLocationInView() const {
    return Vec2(_x, _y);
}

Vec2 EventMouse::getLocationInView(Vec2 &out) const {
    out.set(_x, View::getInstance()._designResolutionSize.height - _y); // from ts: not sure?
    return out;
}

Vec2 EventMouse::getPreviousLocation() const {
    return Vec2(_prevX, _prevY);
}

Vec2 EventMouse::getPreviousLocation(Vec2 &out) const {
    out.set(_prevX, _prevY);
    return out;
}

Vec2 EventMouse::getUIPreviousLocation() const {
    Vec2 out(_prevX, _prevY);
    View::getInstance().convertPointWithScale(out);
    return out;
}

Vec2 EventMouse::getUIPreviousLocation(Vec2 &out) const {
    out.set(_prevX, _prevY);
    View::getInstance().convertPointWithScale(out);
    return out;
}

Vec2 EventMouse::getDelta() const {
    Vec2 out(_x - _prevX, _y - _prevY);
    return out;
}

Vec2 EventMouse::getDelta(Vec2 &out) const {
    out.set(_x - _prevX, _y - _prevY);
    return out;
}

float EventMouse::getDeltaX() const {
    return _x - _prevX;
}

float EventMouse::getDeltaY() const {
    return _y - _prevY;
}

Vec2 EventMouse::getUIDelta() const {
    Vec2 out((_x - _prevX) / View::getInstance().getScaleX(), (_y - _prevY) / View::getInstance().getScaleY());
    return out;
}

Vec2 EventMouse::getUIDelta(Vec2 &out) const {
    out.set((_x - _prevX) / View::getInstance().getScaleX(), (_y - _prevY) / View::getInstance().getScaleY());
    return out;
}

float EventMouse::getUIDeltaX() const {
    return (_x - _prevX) / View::getInstance().getScaleX();
}

float EventMouse::getUIDeltaY() const {
    return (_y - _prevY) / View::getInstance().getScaleY();
}

void EventMouse::setButton(int32_t button) {
    _button = button;
}

int32_t EventMouse::getButton() const {
    return _button;
}

float EventMouse::getLocationX() const {
    return _x;
}

float EventMouse::getLocationY() const {
    return _y;
}

float EventMouse::getUILocationX() const {
    const Rect &viewport = View::getInstance().getViewportRect();
    return (_x - viewport.getMinX()) / View::getInstance().getScaleX();
}

float EventMouse::getUILocationY() const {
    const Rect &viewport = View::getInstance().getViewportRect();
    return (_y - viewport.getMinY()) / View::getInstance().getScaleY();
}

// EventTouch

uint32_t EventTouch::MAX_TOUCHES{5};

EventTouch::EventTouch(std::vector<Touch> changedTouches, bool bubbles, const std::string &eventType, std::vector<Touch> touches)
: Event(eventType, bubbles), _eventCode(eventType), _touches(std::move(changedTouches)), _allTouches(std::move(touches)) {}

const std::vector<Touch> &EventTouch::getTouches() const {
    return _touches;
}

const std::vector<Touch> &EventTouch::getAllTouches() const {
    return _allTouches;
}

void EventTouch::setLocation(float x, float y) {
    if (touch) {
        touch->setTouchInfo(touch->getID(), x, y);
    }
}

Vec2 EventTouch::getLocation() const {
    return touch ? touch->getLocation() : Vec2();
}

Vec2 EventTouch::getLocation(Vec2 &out) const {
    return touch ? touch->getLocation(out) : Vec2();
}

Vec2 EventTouch::getUILocation() const {
    return touch ? touch->getUILocation() : Vec2();
}

Vec2 EventTouch::getUILocation(Vec2 &out) const {
    return touch ? touch->getUILocation(out) : Vec2();
}

Vec2 EventTouch::getLocationInView() const {
    return touch ? touch->getLocationInView() : Vec2();
}

Vec2 EventTouch::getLocationInView(Vec2 &out) const {
    return touch ? touch->getLocationInView(out) : Vec2();
}

Vec2 EventTouch::getPreviousLocation() const {
    return touch ? touch->getPreviousLocation() : Vec2();
}

Vec2 EventTouch::getPreviousLocation(Vec2 &out) const {
    return touch ? touch->getPreviousLocation(out) : Vec2();
}

Vec2 EventTouch::getStartLocation() const {
    return touch ? touch->getStartLocation() : Vec2();
}

Vec2 EventTouch::getStartLocation(Vec2 &out) const {
    return touch ? touch->getStartLocation(out) : Vec2();
}

Vec2 EventTouch::getUIStartLocation() const {
    return touch ? touch->getUIStartLocation() : Vec2();
}

Vec2 EventTouch::getUIStartLocation(Vec2 &out) const {
    return touch ? touch->getUIStartLocation(out) : Vec2();
}

int32_t EventTouch::getID() const {
    return touch ? touch->getID() : -1; // -1 means null in ts
}

Vec2 EventTouch::getDelta() const {
    return touch ? touch->getDelta() : Vec2();
}

Vec2 EventTouch::getDelta(Vec2 &out) const {
    return touch ? touch->getDelta(out) : Vec2();
}

Vec2 EventTouch::getUIDelta() const {
    return touch ? touch->getUIDelta() : Vec2();
}

Vec2 EventTouch::getUIDelta(Vec2 &out) const {
    return touch ? touch->getUIDelta(out) : Vec2();
}

float EventTouch::getDeltaX() const {
    return touch ? getDelta().x : 0;
}

float EventTouch::getDeltaY() const {
    return touch ? getDelta().y : 0;
}

float EventTouch::getLocationX() const {
    return touch ? touch->getLocationX() : 0;
}

float EventTouch::getLocationY() const {
    return touch ? touch->getLocationY() : 0;
}

// EventAcceleration
EventAcceleration::EventAcceleration(const Acceleration &acc, bool bubbles) : Event(SystemEventType::DEVICEMOTION, bubbles), acc(acc) {}

// EventKeyboard

EventKeyboard::EventKeyboard(const event::KeyCode &keyCode, bool isPressed, bool bubbles) : Event(isPressed ? SystemEventType::KEY_DOWN : SystemEventType::KEY_UP, bubbles), _isPressed(isPressed), keyCode(keyCode) {}

EventKeyboard::EventKeyboard(const event::KeyCode &keyCode, const std::string &eventType, bool bubbles) : Event(eventType, bubbles), keyCode(keyCode) {}

} // namespace cc
