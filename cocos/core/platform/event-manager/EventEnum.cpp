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

#include "core/platform/event-manager/EventEnum.h"

namespace cc {

const std::string SystemEventType::TOUCH_START{"touch-start"};
const std::string SystemEventType::TOUCH_MOVE{"touch-move"};
const std::string SystemEventType::TOUCH_END{"touch-end"};
const std::string SystemEventType::TOUCH_CANCEL{"touch-cancel"};
const std::string SystemEventType::MOUSE_DOWN{"mouse-down"};
const std::string SystemEventType::MOUSE_MOVE{"mouse-move"};
const std::string SystemEventType::MOUSE_UP{"mouse-up"};
const std::string SystemEventType::MOUSE_WHEEL{"mouse-wheel"};
const std::string SystemEventType::MOUSE_ENTER{"mouse-enter"};
const std::string SystemEventType::MOUSE_LEAVE{"mouse-leave"};
const std::string SystemEventType::KEY_DOWN{"keydown"};
const std::string SystemEventType::KEY_UP{"keyup"};
const std::string SystemEventType::DEVICEMOTION{"devicemotion"};
const std::string SystemEventType::TRANSFORM_CHANGED{"transform-changed"};
const std::string SystemEventType::SCENE_CHANGED_FOR_PERSISTS{"scene-changed-for-persists"};
const std::string SystemEventType::SIZE_CHANGED{"size-changed"};
const std::string SystemEventType::ANCHOR_CHANGED{"anchor-changed"};
const std::string SystemEventType::COLOR_CHANGED{"color-changed"};
const std::string SystemEventType::CHILD_ADDED{"child-added"};
const std::string SystemEventType::CHILD_REMOVED{"child-removed"};
const std::string SystemEventType::PARENT_CHANGED{"parent-changed"};
const std::string SystemEventType::NODE_DESTROYED{"node-destroyed"};
const std::string SystemEventType::LAYER_CHANGED{"layer-changed"};
const std::string SystemEventType::SIBLING_ORDER_CHANGED{"sibling-order-changed"};

const std::string InputEventType::TOUCH_START{"touch-start"};
const std::string InputEventType::TOUCH_MOVE{"touch-move"};
const std::string InputEventType::TOUCH_END{"touch-end"};
const std::string InputEventType::TOUCH_CANCEL{"touch-cancel"};
const std::string InputEventType::MOUSE_DOWN{"mouse-down"};
const std::string InputEventType::MOUSE_MOVE{"mouse-move"};
const std::string InputEventType::MOUSE_UP{"mouse-up"};
const std::string InputEventType::MOUSE_WHEEL{"mouse-wheel"};
const std::string InputEventType::KEY_DOWN{"keydown"};
const std::string InputEventType::KEY_PRESSING{"key-pressing"};
const std::string InputEventType::KEY_UP{"keyup"};
const std::string InputEventType::DEVICEMOTION{"devicemotion"};
} // namespace cc
