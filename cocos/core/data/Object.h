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

#define EDITOR 0 //cjh
#define warnID //cjh

namespace cc {

// definitions for CCObject.Flags

enum ObjectState {
    Destroyed = 1 << 0,
    RealDestroyed = 1 << 1,
    ToDestroy = 1 << 2,
    DontSave = 1 << 3,
    EditorOnly = 1 << 4,
    Dirty = 1 << 5,
    DontDestroy = 1 << 6,
    Destroying = 1 << 7,
    Deactivating = 1 << 8,
    LockedInEditor = 1 << 9,
    HideInHierarchy = 1 << 10,

    IsOnEnableCalled = 1 << 11,
    IsEditorOnEnableCalled = 1 << 12,
    IsPreloadStarted = 1 << 13,
    IsOnLoadCalled = 1 << 14,
    IsOnLoadStarted = 1 << 15,
    IsStartCalled = 1 << 16,

    IsRotationLocked = 1 << 17,
    IsScaleLocked = 1 << 18,
    IsAnchorLocked = 1 << 19,
    IsSizeLocked = 1 << 20,
    IsPositionLocked = 1 << 21,

    // Distributed
    IsReplicated = 1 << 22,
    IsClientLoad = 1 << 23,

    // var Hide = HideInGame | HideInEditor;
    // should not clone or serialize these flags
    PersistentMask = ~(ToDestroy | Dirty | Destroying | DontDestroy | Deactivating
                           | IsPreloadStarted | IsOnLoadStarted | IsOnLoadCalled | IsStartCalled
                           | IsOnEnableCalled | IsEditorOnEnableCalled
                           | IsRotationLocked | IsScaleLocked | IsAnchorLocked | IsSizeLocked | IsPositionLocked
    /* RegisteredInEditor */),

    // all the hideFlags
    AllHideMasks = DontSave | EditorOnly | LockedInEditor | HideInHierarchy,
};

/**
 * @en
 * The base class of most of all the objects in Fireball.
 * @zh
 * 大部分对象的基类。
 * @private
 */
class CCObject /*cjh implements EditorExtendableObject*/ {
public:
    enum class Flags {
        Destroyed,
        // ToDestroy: ToDestroy,

        /**
         * @en The object will not be saved.
         * @zh 该对象将不会被保存。
         */
        DontSave,

        /**
         * @en The object will not be saved when building a player.
         * @zh 构建项目时，该对象将不会被保存。
         */
        EditorOnly,

        Dirty,

        /**
         * @en Dont destroy automatically when loading a new scene.
         * @zh 加载一个新场景时，不自动删除该对象。
         * @private
         */
        DontDestroy,

        /**
         * @en
         * @zh
         * @private
         */
        PersistentMask,

        // FLAGS FOR ENGINE

        /**
         * @en
         * @zh
         * @private
         */
        Destroying,

        /**
         * @en The node is deactivating.
         * @zh 节点正在反激活的过程中。
         * @private
         */
        Deactivating,

        /**
         * @en
         * Hide in game and hierarchy.
         * This flag is readonly, it can only be used as an argument of scene.addEntity() or Entity.createWithFlags().
         * @zh
         * 在游戏和层级中隐藏该对象。<br/>
         * 该标记只读，它只能被用作 scene.addEntity()的一个参数。
         */
        // HideInGame: HideInGame,

        /**
         * @en The lock node, when the node is locked, cannot be clicked in the scene.
         * @zh 锁定节点，锁定后场景内不能点击。
         * @private
         */
        LockedInEditor,

        /**
          * @en Hide the object in editor.
          * @zh 在编辑器中隐藏该对象。
          */
        HideInHierarchy,

        /**
          * @en The object will not be saved and hide the object in editor,and lock node, when the node is locked,
          * cannot be clicked in the scene,and The object will not be saved when building a player.
          * @zh 该对象将不会被保存,构建项目时，该对象将不会被保存, 锁定节点，锁定后场景内不能点击, 在编辑器中隐藏该对象。
          */
        AllHideMasks,

        // FLAGS FOR EDITOR

        /**
         * @en
         * Hide in game view, hierarchy, and scene view... etc.
         * This flag is readonly, it can only be used as an argument of scene.addEntity() or Entity.createWithFlags().
         * @zh
         * 在游戏视图，层级，场景视图等等...中隐藏该对象。
         * 该标记只读，它只能被用作 scene.addEntity()的一个参数。
         */
        // Hide: Hide,

        // FLAGS FOR COMPONENT

        IsPreloadStarted,
        IsOnLoadStarted,
        IsOnLoadCalled,
        IsOnEnableCalled,
        IsStartCalled,
        IsEditorOnEnableCalled,

        IsPositionLocked,
        IsRotationLocked,
        IsScaleLocked,
        IsAnchorLocked,
        IsSizeLocked,

        IsReplicated,
        IsClientLoad,
    };

    static void _deferredDestroy ();

//cjh    public declare [editorExtrasTag]: unknown;

    uint32_t _objFlags = 0;

protected:
    std::string _name;

    CCObject(const char* name = "");

public:
    // MEMBER

    /**
     * @en The name of the object.
     * @zh 该对象的名称。
     * @default ""
     * @example
     * ```
     * obj.name = "New Obj";
     * ```
     */
    const std::string& getName () const { return _name; }
    void setName (const std::string& value) { _name = value; }

    /**
     * @en After inheriting CCObject objects, control whether you need to hide, lock, serialize, and other functions.
     * @zh 在继承 CCObject 对象后，控制是否需要隐藏，锁定，序列化等功能。
     */
    void setHideFlags (Flags hideFlags);
    Flags getHideFlags ();

    void setReplicated (bool value) {
        if (value) {
            _objFlags |= IsReplicated;
        } else {
            _objFlags &= ~IsReplicated;
        }
    }

    bool isReplicated () {
        return !!(_objFlags & IsReplicated);
    }

    /**
     * @en
     * Indicates whether the object is not yet destroyed. (It will not be available after being destroyed)<br>
     * When an object's `destroy` is called, it is actually destroyed after the end of this frame.
     * So `isValid` will return false from the next frame, while `isValid` in the current frame will still be true.
     * If you want to determine whether the current frame has called `destroy`, use `isValid(obj, true)`,
     * but this is often caused by a particular logical requirements, which is not normally required.
     *
     * @zh
     * 表示该对象是否可用（被 destroy 后将不可用）。<br>
     * 当一个对象的 `destroy` 调用以后，会在这一帧结束后才真正销毁。<br>
     * 因此从下一帧开始 `isValid` 就会返回 false，而当前帧内 `isValid` 仍然会是 true。<br>
     * 如果希望判断当前帧是否调用过 `destroy`，请使用 `isValid(obj, true)`，不过这往往是特殊的业务需求引起的，通常情况下不需要这样。
     * @default true
     * @readOnly
     * @example
     * ```ts
     * import { Node, log } from 'cc';
     * const node = new Node();
     * log(node.isValid);    // true
     * node.destroy();
     * log(node.isValid);    // true, still valid in this frame
     * // after a frame...
     * log(node.isValid);    // false, destroyed in the end of last frame
     * ```
     */
    bool isValid () const {
        return !(_objFlags & Destroyed);
    }

    /**
     * @en
     * Destroy this Object, and release all its own references to other objects.<br/>
     * Actual object destruction will delayed until before rendering.
     * From the next frame, this object is not usable any more.
     * You can use `isValid(obj)` to check whether the object is destroyed before accessing it.
     * @zh
     * 销毁该对象，并释放所有它对其它对象的引用。<br/>
     * 实际销毁操作会延迟到当前帧渲染前执行。从下一帧开始，该对象将不再可用。
     * 您可以在访问对象之前使用 `isValid(obj)` 来检查对象是否已被销毁。
     * @return whether it is the first time the destroy being called
     * @example
     * ```
     * obj.destroy();
     * ```
     */
    virtual bool destroy ();

    /**
     * Clear all references in the instance.
     *
     * NOTE: this method will not clear the getter or setter functions which defined in the instance of CCObject.
     *       You can override the _destruct method if you need, for example:
     *       _destruct: function () {
     *           for (var key in this) {
     *               if (hasOwnProperty(key)) {
     *                   switch (typeof this[key]) {
     *                       case 'string':
     *                           this[key] = '';
     *                           break;
     *                       case 'object':
     *                       case 'function':
     *                           this[key] = null;
     *                           break;
     *               }
     *           }
     *       }
     *
     */
    void _destruct ();

    void _destroyImmediate ();

    virtual std::string toString() const { return ""; };
};

} // namespace cc {
