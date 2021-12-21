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
#include "cocos/base/Variant.h"

#include "core/scene-graph/NodeEvent.h"

namespace cc {

class SystemEventType {
public:
    /**
     * @en
     * The event type for touch start event
     *
     * @zh
     * 手指开始触摸事件。
    */
    static const std::string TOUCH_START;

    /**
     * @en
     * The event type for touch move event
     *
     * @zh
     * 当手指在屏幕上移动时。
    */
    static const std::string TOUCH_MOVE;

    /**
     * @en
     * The event type for touch end event
     *
     * @zh
     * 手指结束触摸事件。
    */
    static const std::string TOUCH_END;

    /**
     * @en
     * The event type for touch end event
     *
     * @zh
     * 当手指在目标节点区域外离开屏幕时。
    */
    static const std::string TOUCH_CANCEL;

    /**
     * @en
     * The event type for mouse down events
     *
     * @zh
     * 当鼠标按下时触发一次。
    */
    static const std::string MOUSE_DOWN;

    /**
     * @en
     * The event type for mouse move events
     *
     * @zh
     * 当鼠标在目标节点在目标节点区域中移动时，不论是否按下。
    */
    static const std::string MOUSE_MOVE;

    /**
     * @en
     * The event type for mouse up events
     *
     * @zh
     * 当鼠标从按下状态松开时触发一次。
    */
    static const std::string MOUSE_UP;

    /**
     * @en
     * The event type for mouse wheel events
     *
     * @zh 手指开始触摸事件
    */
    static const std::string MOUSE_WHEEL;

    /**
     * @en
     * The event type for mouse leave target events
     *
     * @zh
     * 当鼠标移入目标节点区域时，不论是否按下.
     *
     * @deprecated since v3.3, please use Node.EventType.MOUSE_ENTER instead.
    */
    static const std::string MOUSE_ENTER;

    /**
     * @en
     * The event type for mouse leave target events
     *
     * @zh
     * 当鼠标移出目标节点区域时，不论是否按下。
     *
     * @deprecated sincev3.3, please use Node.EventType.MOUSE_LEAVE instead.
    */
    static const std::string MOUSE_LEAVE;

    /**
     * @en The event type for press the key down event, the event will be continuously dispatched in the key pressed state
     * @zh 当按下按键时触发的事件, 该事件在按下状态会持续派发
    */
    static const std::string KEY_DOWN;

    /**
     * @en The event type for press the key up event
     * @zh 当松开按键时触发的事件
    */
    static const std::string KEY_UP;

    /**
     * @en
     * The event type for press the devicemotion event
     *
     * @zh
     * 重力感应
    */
    static const std::string DEVICEMOTION;

    /**
     * @en
     * The event type for position, rotation, scale changed.Use the type parameter as [[Node.TransformBit]] to check which part is changed
     *
     * @zh
     * 节点改变位置、旋转或缩放事件。如果具体需要判断是哪一个事件，可通过判断回调的第一个参数类型是 [[Node.TransformBit]] 中的哪一个来获取
     * @example
     * ```
     * this.node.on(Node.EventType.TRANSFORM_CHANGED, (type)=>{
     *  if (type & Node.TransformBit.POSITION) {
     *       //...
     *   }
     * }, this);
     * ```
     *
     * @deprecated sincev3.3, please use Node.EventType.TRANSFORM_CHANGED instead
    */
    static const std::string TRANSFORM_CHANGED;

    /**
     * @en The event type for notifying the host scene has been changed for a persist node.
     * @zh 当场景常驻节点的场景发生改变时触发的事件，一般在切换场景过程中触发。
     *
     * @deprecated sincev3.3, please use Node.EventType.SCENE_CHANGED_FOR_PERSISTS instead
    */
    static const std::string SCENE_CHANGED_FOR_PERSISTS;

    /**
     * @en
     * The event type for size change events.
     * Performance note, this event will be triggered every time corresponding properties being changed,
     * if the event callback have heavy logic it may have great performance impact, try to avoid such scenario.
     *
     * @zh
     * 当节点尺寸改变时触发的事件。
     * 性能警告：这个事件会在每次对应的属性被修改时触发，如果事件回调损耗较高，有可能对性能有很大的负面影响，请尽量避免这种情况。
     *
     * @deprecated sincev3.3, please use Node.EventType.SIZE_CHANGED instead
    */
    static const std::string SIZE_CHANGED;

    /**
     * @en
     * The event type for anchor point change events.
     * Performance note, this event will be triggered every time corresponding properties being changed,
     * if the event callback have heavy logic it may have great performance impact, try to avoid such scenario.
     *
     * @zh
     * 当节点的 UITransform 锚点改变时触发的事件。
     * 性能警告：这个事件会在每次对应的属性被修改时触发，如果事件回调损耗较高，有可能对性能有很大的负面影响，请尽量避免这种情况。
     *
     * @deprecated sincev3.3, please use Node.EventType.ANCHOR_CHANGED instead
    */
    static const std::string ANCHOR_CHANGED;

    /**
     * @en
     * The event type for color change events.
     * Performance note, this event will be triggered every time corresponding properties being changed,
     * if the event callback have heavy logic it may have great performance impact, try to avoid such scenario.
     *
     * @zh
     * 当节点的 UI 渲染组件颜色属性改变时触发的事件。
     * 性能警告：这个事件会在每次对应的属性被修改时触发，如果事件回调损耗较高，有可能对性能有很大的负面影响，请尽量避免这种情况。
     *
     * @deprecated sincev3.3, please use Node.EventType.COLOR_CHANGED instead
    */
    static const std::string COLOR_CHANGED;

    /**
     * @en
     * The event type for adding a new child node to the target node.
     *
     * @zh
     * 给目标节点添加子节点时触发的事件。
     *
     * @deprecated sincev3.3, please use Node.EventType.CHILD_ADDED instead
    */
    static const std::string CHILD_ADDED;

    /**
     * @en
     * The event type for removing a child node from the target node.
     *
     * @zh
     * 给目标节点移除子节点时触发的事件。
     *
     * @deprecated sincev3.3, please use Node.EventType.CHILD_REMOVED instead
    */
    static const std::string CHILD_REMOVED;

    /**
     * @en The event type for changing the parent of the target node
     * @zh 目标节点的父节点改变时触发的事件。
     *
     * @deprecated sincev3.3, please use Node.EventType.PARENT_CHANGED instead
    */
    static const std::string PARENT_CHANGED;

    /**
     * @en The event type for destroying the target node
     * @zh 目标节点被销毁时触发的事件。
     *
     * @deprecated sincev3.3, please use Node.EventType.NODE_DESTROYED instead
    */
    static const std::string NODE_DESTROYED;

    /**
     * @en The event type for node layer change events.
     * @zh 节点 layer 改变时触发的事件。
     *
     * @deprecated sincev3.3, please use Node.EventType.LAYER_CHANGED instead
    */
    static const std::string LAYER_CHANGED;

    /**
     * @en The event type for node's sibling order changed.
     * @zh 当节点在兄弟节点中的顺序发生变化时触发的事件。
     *
     * @deprecated sincev3.3, please use Node.EventType.SIBLING_ORDER_CHANGED instead
    */
    static const std::string SIBLING_ORDER_CHANGED;
};

using SystemEventTypeUnion = cc::variant<SystemEventType, NodeEventType>;

} // namespace cc
