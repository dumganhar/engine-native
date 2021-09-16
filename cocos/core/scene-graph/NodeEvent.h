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

namespace cc {

class NodeEventType {
public:
    static const std::string TOUCH_START;
    static const std::string TOUCH_MOVE;
    static const std::string TOUCH_END;
    static const std::string TOUCH_CANCEL;
    static const std::string MOUSE_DOWN;
    static const std::string MOUSE_MOVE;
    static const std::string MOUSE_UP;
    static const std::string MOUSE_WHEEL;
    static const std::string MOUSE_ENTER;
    static const std::string MOUSE_LEAVE;
    static const std::string KEY_DOWN;
    static const std::string KEY_UP;
    static const std::string DEVICEMOTION;
    static const std::string TRANSFORM_CHANGED;
    static const std::string SCENE_CHANGED_FOR_PERSISTS;
    static const std::string SIZE_CHANGED;
    static const std::string ANCHOR_CHANGED;
    static const std::string COLOR_CHANGED;
    static const std::string CHILD_ADDED;
    static const std::string CHILD_REMOVED;
    static const std::string PARENT_CHANGED;
    static const std::string NODE_DESTROYED;
    static const std::string LAYER_CHANGED;
    static const std::string SIBLING_ORDER_CHANGED;
};

} // namespace cc
