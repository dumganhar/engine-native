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

#include "math/Vec2.h"
namespace cc {

/**
 * @en The  point class
 * @zh 封装了触点相关的信息。
 */
class Touch final{
public:
    Touch(float x, float y) {
        setTouchInfo(0, x, y);
    }

    Touch(float x, float y, uint32_t id) {
        setTouchInfo(id, x, y);
    }

    ~Touch() = default;

    /**
     * @en Returns the current touch location in OpenGL coordinates.、
     * @zh 获取当前触点位置。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getLocation() const;

    /**
     * @en Returns X axis location value.
     * @zh 获取当前触点 X 轴位置。
     */
    inline float getLocationX() const {
        return _point.x;
    }

    /**
     * @en Returns Y axis location value.
     * @zh 获取当前触点 Y 轴位置。
     */
    inline float getLocationY() const {
        return _point.y;
    }

    /**
     * @en Returns the current touch location in UI coordinates.、
     * @zh 获取当前触点在 UI 坐标系中的位置。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    Vec2 getUILocation() const;

    /**
     * @en Returns X axis location value in UI coordinates.
     * @zh 获取当前触点在 UI 坐标系中 X 轴位置。
     */

    float getUILocationX() const;

    /**
     * @en Returns Y axis location value in UI coordinates.
     * @zh 获取当前触点在 UI 坐标系中 Y 轴位置。
     */
    float getUILocationY() const;

    /**
     * @en Returns the previous touch location.
     * @zh 获取触点在上一次事件时的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getPreviousLocation() const;

    /**
     * @en Returns the previous touch location in UI coordinates.
     * @zh 获取触点在上一次事件时在 UI 坐标系中的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    Vec2 getUIPreviousLocation() const;

    /**
     * @en Returns the start  location.
     * @zh 获取触点落下时的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    const Vec2& getStartLocation() const;

    /**
     * @en Returns the start  location in UI coordinates.
     * @zh 获取触点落下时在 UI 坐标系中的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    Vec2 getUIStartLocation() const; 

    /**
     * @en Returns the delta distance from the previous touche to the current one.
     * @zh 获取触点距离上一次事件移动的距离对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    Vec2 getDelta() const;

        /**
     * @en Returns the delta distance from the previous touche to the current one in UI coordinates.
     * @zh 获取触点距离上一次事件移动在 UI 坐标系中的距离对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    Vec2 getUIDelta() const;

    /**
     * @en Returns the current  location in screen coordinates.
     * @zh 获取当前事件在游戏窗口内的坐标位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    Vec2 getLocationInView() const;

    /**
     * @en Returns the previous  location in screen coordinates.
     * @zh 获取触点在上一次事件时在游戏窗口中的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    Vec2 getPreviousLocationInView() const;

    /**
     * @en Returns the start  location in screen coordinates.
     * @zh 获取触点落下时在游戏窗口中的位置对象，对象包含 x 和 y 属性。
     * @param out - Pass the out object to avoid object creation, very good practice
     */
    Vec2 getStartLocationInView() const;

    /**
     * @en Returns the id of the  point.
     * @zh 触点的标识 ID，可以用来在多点触摸中跟踪触点。
     */
    inline uint32_t getID() const { 
        return _id;
    }

    /**
     * @en Resets  point information.
     * @zh 重置触点相关的信息。
     * @param id - The id of the  point
     * @param x - x position of the  point
     * @param y - y position of the  point
     */
    void setTouchInfo(uint32_t id = 0);

    void setTouchInfo(uint32_t id, float x, float y);

    /**
     * @en Sets  point location.
     * @zh 设置触点位置。
     * @param point - The location
     */
    void setPoint(const Vec2& point);

    void setPoint(float x, float y);

    /**
     * @en Sets the location previously registered for the current .
     * @zh 设置触点在前一次触发时收集的位置。
     * @param point - The location
     */
    void setPrevPoint(const Vec2& point);

    void setPrevPoint(float x, float y);

    inline uint32_t getLastModified() const { 
        return _lastModified;
    }

private:
    Vec2 _point;
    Vec2 _prevPoint;
    uint32_t _lastModified{0};
    uint32_t _id{0};
    Vec2 _startPoint;
    bool _startPointCaptured{false};
};

} // namespace cc
