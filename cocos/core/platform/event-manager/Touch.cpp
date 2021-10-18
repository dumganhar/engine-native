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

#include "core/platform/event-manager/Touch.h"

NS_CC_EVENT_BEGIN

// returns the current touch location in screen coordinates
Vec2 Touch::getLocationInView() const {
    return _point;
}

// returns the previous touch location in screen coordinates
Vec2 Touch::getPreviousLocationInView() const {
    return _prevPoint;
}

// returns the start touch location in screen coordinates
Vec2 Touch::getStartLocationInView() const {
    return _startPoint;
}

// returns the current touch location in OpenGL coordinates
Vec2 Touch::getLocation() const {
    return Vec2::ZERO; //cjh Director::getInstance()->convertToGL(_point);
}

Vec2 Touch::getUILocation() const {
    return Vec2::ZERO; //cjh TODO:
}

// returns the previous touch location in OpenGL coordinates
Vec2 Touch::getPreviousLocation() const {
    return Vec2::ZERO; //cjh Director::getInstance()->convertToGL(_prevPoint);
}

// returns the start touch location in OpenGL coordinates
Vec2 Touch::getStartLocation() const {
    return Vec2::ZERO; //cjh Director::getInstance()->convertToGL(_startPoint);
}

// returns the delta position between the current location and the previous location in OpenGL coordinates
Vec2 Touch::getDelta() const {
    return getLocation() - getPreviousLocation();
}

// Returns the current touch force for 3d touch.
float Touch::getCurrentForce() const {
    return _curForce;
}

// Returns the maximum touch force for 3d touch.
float Touch::getMaxForce() const {
    return _maxForce;
}

NS_CC_EVENT_END
