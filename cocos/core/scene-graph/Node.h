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

#include <any>
#include <vector>

#include "base/TypeDef.h"
#include "core/components/Component.h"
#include "core/data/Object.h"
#include "core/event/Event.h"
#include "core/scene-graph/NodeEnum.h"
#include "core/scene-graph/NodeEvent.h"
#include "core/scene-graph/NodeEventProcessor.h"
#include "core/utils/IDGenerator.h"
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Quaternion.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace cc {

class Scene;
class NodeEventProcessor;
class NodeUiProperties;

/**
 * Event types emitted by Node
 */
using EventType = NodeEventType;
/**
 * Bit masks for Node transformation parts
 */
using TransformDirtyBit = TransformBit;

class Node : public CCObject {
public:
    using Super = CCObject;

    static const uint TRANSFORM_ON;
    static const uint DESTROYING;
    static const uint DEACTIVATING;
    static const uint DONT_DESTROY;

    static Node *instantiate(Node *cloned, bool isSyncedNode);
    // for walk
    static std::vector<std::vector<Node *>> stacks;
    static index_t                          stackId;

    static void    setScene(Node *);
    static index_t getIdxOfChild(const std::vector<Node *> &, Node *);
    // TODO(Lenovo):

    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    static Component *findComponent(Node *, const T &);

    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    static Component *findComponents(Node *, const T &, const std::vector<Component *> &);

    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    static Component *findChildComponent(const std::vector<Node *> &, const T &);

    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    static std::vector<Component *> findChildComponents(const std::vector<Node *> &, const T &, std::vector<Component *>);

    static bool isStatic; //cjh TODO: add getter / setter

    static void  setDirtyNode(const index_t idx, Node *node);
    static Node *getDirtyNode(const index_t idx);

    /**
     * @en Determine whether the given object is a normal Node. Will return false if [[Scene]] given.
     * @zh 指定对象是否是普通的节点？如果传入 [[Scene]] 会返回 false。
     */
    template <typename T>
    static bool isNode(T *obj);

    static void resetChangedFlags();
    static void clearNodeArray();

    Node();
    explicit Node(const std::string &name);
    ~Node() override;

    void setParent(Node *parent, bool isKeepWorld = false);

    Scene *getScene() const;
    void   walk();
    void   walk(const std::function<void(Node *)> &);
    void   walk(const std::function<void(Node *)> &, const std::function<void(Node *)> &);

    template <typename... Args>
    void on(const std::string &type, std::function<void(Args...)> &&callback);

    template <typename Target, typename... Args>
    void on(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture = false);

    template <typename Target, typename... Args>
    void on(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture = false);

    template <typename Target, typename LambdaType>
    std::enable_if_t<!std::is_member_function_pointer_v<LambdaType>, void>
    on(const std::string &type, LambdaType &&callback, Target *target, bool useCapture = false);

    template <typename LambdaType>
    std::enable_if_t<!std::is_member_function_pointer_v<LambdaType>, void>
    on(const std::string &type, LambdaType &&callback, bool useCapture = false);

    template <typename... Args>
    void once(const std::string &type, std::function<void(Args...)> &&callback);

    template <typename Target, typename... Args>
    void once(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture = false);

    template <typename Target, typename... Args>
    void once(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture = false);

    template <typename Target, typename LambdaType>
    std::enable_if_t<!std::is_member_function_pointer_v<LambdaType>, void>
    once(const std::string &type, LambdaType &&callback, Target *target, bool useCapture = false);

    template <typename LambdaType>
    std::enable_if_t<!std::is_member_function_pointer_v<LambdaType>, void>
    once(const std::string &type, LambdaType &&callback, bool useCapture = false);

    void off(const std::string &type, bool useCapture = false);

    void off(const std::string &type, void *target, bool useCapture = false);

    template <typename Target, typename... Args>
    void off(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture = false);

    template <typename... Args>
    void emit(const std::string &type, Args &&...args);

    void dispatchEvent(event::Event *event);
    bool hasEventListener(const std::string &type);
    bool hasEventListener(const std::string &type, CallbackInfoBase::ID cbID);
    bool hasEventListener(const std::string &type, void *target);
    bool hasEventListener(const std::string &type, CallbackInfoBase::ID cbID, void *target);

    template <typename Target, typename... Args>
    bool hasEventListener(const std::string &type, void (Target::*memberFn)(Args...), Target *target);

    void targetOff(const std::string &);

    bool destroy() override {
        if (CCObject::destroy()) {
            _active = false;
            return true;
        }
        return false;
    }
    inline void destroyAllChildren() {
        for (auto *child : _children) {
            child->destroy();
        }
    }
    inline void updateSiblingIndex() {
        uint i = 0;
        for (auto *child : _children) {
            child->_siblingIndex = i++;
        }
        emit(NodeEventType::SIBLING_ORDER_CHANGED, NodeEventType::SIBLING_ORDER_CHANGED);
    }

    inline void addChild(Node *node) { node->setParent(this); }
    inline void removeChild(Node *node) {
        auto idx = getIdxOfChild(_children, node);
        if (idx != -1) {
            node->setParent(nullptr);
        }
    }
    inline void removeFromParent() {
        if (_parent) {
            _parent->removeChild(this);
        }
    }
    void removeAllChildren();
    bool isChildOf(Node *parent);

    inline void setPersistNode(bool val) {
        val ? _objFlags |= Flags::DONT_DESTROY : _objFlags &= ~Flags::DONT_DESTROY;
    };
    inline void setName(const std::string &name) {
        _name = name;
    }
    void setActive(bool isActive);
    void setSiblingIndex(index_t idx);

    inline bool getPersistNode() const {
        return static_cast<FlagBits>(_objFlags & Flags::DONT_DESTROY) > 0;
    }
    inline std::string getName() const {
        return _name;
    }
    inline std::string getUUid() const {
        return _id;
    }
    inline bool isActive() const { return _active; }
    inline bool isActiveInHierarchy() const { return _activeInHierarchy; }

    template <typename T, typename Enabled = std::enable_if_t<std::is_base_of_v<Component, T>, T>>
    T *addComponent() {
        T *comp = new T();
        return static_cast<T *>(addComponent(comp));
    }

    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    void removeComponent() {
        for (auto iter = _components.begin(); iter != _components.end(); ++iter) {
            if (dynamic_cast<T *>(*iter) != nullptr) {
                _components.erase(iter);
            }
        }
    }

    Component *addComponent(Component *comp);
    void       removeComponent(Component *comp);

    template <typename T, typename Enabled = std::enable_if_t<std::is_base_of<Component, T>::value>>
    Component *getComponent() const {
        for (auto iter = _components.begin(); iter != _components.end(); ++iter) {
            if (dynamic_cast<T *>(*iter) != nullptr) {
                return *iter;
            }
        }
        return nullptr;
    }

    // TODO(Lenovo):
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    inline std::vector<Component *> getComponents(const T & /*unused*/) const {};
    inline std::vector<Component *> getComponents(const std::string & /*unused*/) const {
        // TODO: validate return value
        CC_ASSERT(false);
        return _components;
    };
    Component *getComponentInChildren(const std::string &name) const;
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    Component *              getComponentInChildren(const T &comp) const {}
    std::vector<Component *> getComponentsInChildren(const std::string &name) const;
    template <typename T, typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    std::vector<Component *> getComponentsInChildren(const T &comp) const {}

    inline std::vector<Component *> getComponents() const { return _components; }

    virtual void                      onPostActivated(bool active) {}
    inline const std::vector<Node *> &getChildren() { return _children; }
    inline Node *                     getParent() const { return _parent; }
    inline NodeEventProcessor *       getEventProcessor() const { return _eventProcessor; }

    Node *      getChildByUuid(const std::string &) const;
    Node *      getChildByName(const std::string &) const;
    Node *      getChildByPath(const std::string &) const;
    inline uint getSiblingIndex() const { return _siblingIndex; }
    inline void insertChild(Node *child, uint32_t siblingIndex) {
        child->_parent = this;
        child->setSiblingIndex(siblingIndex);
    }

    void invalidateChildren(TransformBit dirtyBit);

    void translate(const Vec3 &, NodeSpace ns = NodeSpace::LOCAL);
    void rotate(const Quaternion &rot, NodeSpace ns);
    void lookAt(const Vec3 &pos, const Vec3 &up);

    void pauseSystemEvents(bool recursive) {}  //cjh TODO:
    void resumeSystemEvents(bool recursive) {} //cjh TODO:

    // ===============================
    // transform
    // ===============================

    /**
     * @en Set position in local coordinate system
     * @zh 设置本地坐标
     * @param position Target position
     */
    inline void setPosition(const Vec3 &pos) { setPosition(pos.x, pos.y, pos.z); }
    void        setPosition(float x, float y, float z);
    /**
     * @en Get position in local coordinate system, please try to pass `out` vector and reuse it to avoid garbage.
     * @zh 获取本地坐标，注意，尽可能传递复用的 [[Vec3]] 以避免产生垃圾。
     * @param out Set the result to out vector
     * @return If `out` given, the return value equals to `out`, otherwise a new vector will be generated and return
     */
    const Vec3 &getPosition() const { return _localPosition; }

    /**
     * @en Set rotation in local coordinate system with a quaternion representing the rotation
     * @zh 用四元数设置本地旋转
     * @param rotation Rotation in quaternion
     */
    inline void setRotation(const Quaternion &rotation) { setRotation(rotation.x, rotation.y, rotation.z, rotation.w); }
    void        setRotation(float x, float y, float z, float w);
    inline void setEulerAngles(const Vec3 &val) { setRotationFromEuler(val.x, val.y, val.z); }
    inline void setRotationFromEuler(float x, float y) { setRotationFromEuler(x, y, _euler.z); }
    inline void setRotationFromEuler(const Vec3 &val) { setRotationFromEuler(val.x, val.y, val.z); }
    void        setRotationFromEuler(float x, float y, float z);
    /**
     * @en Get rotation as quaternion in local coordinate system, please try to pass `out` quaternion and reuse it to avoid garbage.
     * @zh 获取本地旋转，注意，尽可能传递复用的 [[Quat]] 以避免产生垃圾。
     * @param out Set the result to out quaternion
     * @return If `out` given, the return value equals to `out`, otherwise a new quaternion will be generated and return
     */
    const Quaternion &getRotation() const { return _localRotation; }

    /**
     * @en Set scale in local coordinate system
     * @zh 设置本地缩放
     * @param scale Target scale
     */
    inline void setScale(const Vec3 &scale) { setScale(scale.x, scale.y, scale.z); }
    void        setScale(float x, float y, float z);
    /**
     * @en Get scale in local coordinate system, please try to pass `out` vector and reuse it to avoid garbage.
     * @zh 获取本地缩放，注意，尽可能传递复用的 [[Vec3]] 以避免产生垃圾。
     * @param out Set the result to out vector
     * @return If `out` given, the return value equals to `out`, otherwise a new vector will be generated and return
     */
    const Vec3 &getScale() const { return _localScale; }

    /**
     * @en Inversely transform a point from world coordinate system to local coordinate system.
     * @zh 逆向变换一个空间点，一般用于将世界坐标转换到本地坐标系中。
     * @param out The result point in local coordinate system will be stored in this vector
     * @param p A position in world coordinate system
     */
    void inverseTransformPoint(Vec3 &out, const Vec3 &p);

    /**
     * @en Set position in world coordinate system
     * @zh 设置世界坐标
     * @param position Target position
     */
    inline void setWorldPosition(const Vec3 &pos) { setWorldPosition(pos.x, pos.y, pos.z); }
    void        setWorldPosition(float x, float y, float z);

    /**
     * @en Get position in world coordinate system, please try to pass `out` vector and reuse it to avoid garbage.
     * @zh 获取世界坐标，注意，尽可能传递复用的 [[Vec3]] 以避免产生垃圾。
     * @param out Set the result to out vector
     * @return If `out` given, the return value equals to `out`, otherwise a new vector will be generated and return
     */
    const Vec3 &getWorldPosition();

    /**
     * @en Set rotation in world coordinate system with a quaternion representing the rotation
     * @zh 用四元数设置世界坐标系下的旋转
     * @param rotation Rotation in quaternion
     */
    inline void setWorldRotation(const Quaternion &rotation) { setWorldRotation(rotation.x, rotation.y, rotation.z, rotation.w); }
    void        setWorldRotation(float x, float y, float z, float w);
    /**
     * @en Get rotation as quaternion in world coordinate system, please try to pass `out` quaternion and reuse it to avoid garbage.
     * @zh 获取世界坐标系下的旋转，注意，尽可能传递复用的 [[Quat]] 以避免产生垃圾。
     * @param out Set the result to out quaternion
     * @return If `out` given, the return value equals to `out`, otherwise a new quaternion will be generated and return
     */
    const Quaternion &getWorldRotation();

    /**
     * @en Set rotation in world coordinate system with euler angles
     * @zh 用欧拉角设置世界坐标系下的旋转
     * @param x X axis rotation
     * @param y Y axis rotation
     * @param z Z axis rotation
     */
    inline void setWorldScale(const Vec3 &scale) { setWorldScale(scale.x, scale.y, scale.z); }
    void        setWorldScale(float x, float y, float z);

    /**
     * @en Get scale in world coordinate system, please try to pass `out` vector and reuse it to avoid garbage.
     * @zh 获取世界缩放，注意，尽可能传递复用的 [[Vec3]] 以避免产生垃圾。
     * @param out Set the result to out vector
     * @return If `out` given, the return value equals to `out`, otherwise a new vector will be generated and return
     */
    const Vec3 &getWorldScale();

    void setWorldRotationFromEuler(float x, float y, float z);

    /**
     * @en Update the world transform information if outdated
     * @zh 更新节点的世界变换信息
     */
    void updateWorldTransform();

    /**
     * @en Get a world transform matrix
     * @zh 获取世界变换矩阵
     * @param out Set the result to out matrix
     * @return If `out` given, the return value equals to `out`, otherwise a new matrix will be generated and return
     */
    const Mat4 &getWorldMatrix();

    /**
     * @en Get a world transform matrix with only rotation and scale
     * @zh 获取只包含旋转和缩放的世界变换矩阵
     * @param out Set the result to out matrix
     * @return If `out` given, the return value equals to `out`, otherwise a new matrix will be generated and return
     */
    Mat4 getWorldRS();

    /**
     * @en Get a world transform matrix with only rotation and translation
     * @zh 获取只包含旋转和位移的世界变换矩阵
     * @param out Set the result to out matrix
     * @return If `out` given, the return value equals to `out`, otherwise a new matrix will be generated and return
     */
    Mat4 getWorldRT();

    /**
     * @en Set local transformation with rotation, position and scale separately.
     * @zh 一次性设置所有局部变换（平移、旋转、缩放）信息
     * @param rot The rotation
     * @param pos The position
     * @param scale The scale
     */
    void setRTS(Quaternion *rot, Vec3 *pos, Vec3 *scale);

    inline void setForward(const Vec3 &dir) {
        uint       len    = dir.length();
        Vec3       v3Temp = dir * -1 / len;
        Quaternion qTemp{Quaternion::identity()};
        Quaternion::fromViewUp(qTemp, v3Temp);
        setWorldRotation(qTemp);
    }
    void setAngle(float);

    inline const Vec3 &getEulerAngles() {
        if (_eulerDirty) {
            Quaternion::toEuler(&_euler, _localRotation);
            _eulerDirty = false;
        }
        return _euler;
    }

    inline float getAngle() const {
        return _euler.z;
    }

    inline Vec3 getForward() {
        Vec3 forward{0, 0, -1};
        forward.transformQuat(_worldRotation);
        return forward;
    }

    inline Vec3 getUp() {
        Vec3 up{0, 1, 0};
        up.transformQuat(_worldRotation);
        return up;
    }

    inline Vec3 getRight() {
        Vec3 right{1, 0, 0};
        right.transformQuat(_worldRotation);
        return right;
    }

    /**
     * @en Whether the node's transformation have changed during the current frame.
     * @zh 这个节点的空间变换信息在当前帧内是否有变过？
     */
    uint getChangedFlags() const { return _flagChange; }
    void setChangedFlags(uint value) { _flagChange = value; }

    void setDirtyFlag(uint value) { _dirtyFlag = value; }
    uint getDirtyFlag() const { return _dirtyFlag; }
    void setLayer(uint layer) { _layer = layer; }
    uint getLayer() const { return _layer; }

    NodeUiProperties *getUIProps() const { return _uiProps; }

protected:
    bool onPreDestroy() override;

    void onSetParent(Node *oldParent, bool keepWorldTransform);

    inline void updateScene() {
        if (_parent == nullptr) {
            return;
        }
        _scene = _parent->_scene;
    }

    void onHierarchyChanged(Node *);
    void onHierarchyChangedBase(Node *oldParent);

    void         walkInternal(std::function<void(Node *)>, std::function<void(Node *)>);
    virtual void onBatchCreated(bool dontChildPrefab);

    bool onPreDestroyBase();
    void onSiblingIndexChanged(uint siblingIndex) {}
    void checkMultipleComp(Component *comp) {}

    std::vector<Node *>      _children;
    std::vector<Component *> _components;
    Node *                   _parent{nullptr};

    bool _persistNode{false};

    std::string         _id{IDGenerator("Node").getNewId()};
    bool                _active{true};
    bool                _activeInHierarchy{false};
    Scene *             _scene{nullptr};
    NodeEventProcessor *_eventProcessor{nullptr};
    index_t             _siblingIndex{0};
    uint                _eventMask{0};

    cc::Vec3       _worldPosition{Vec3::ZERO};
    cc::Quaternion _worldRotation{Quaternion::identity()};
    cc::Vec3       _worldScale{Vec3::ONE};

    Mat4     _rtMat{Mat4::IDENTITY};
    cc::Mat4 _worldMatrix{Mat4::IDENTITY};

    // local transform
    cc::Vec3       _localPosition{Vec3::ZERO};
    cc::Quaternion _localRotation{Quaternion::identity()};
    cc::Vec3       _localScale{Vec3::ONE};
    //

    static std::vector<Node *> dirtyNodes;
    static uint                clearFrame;
    static uint                clearRound;

    Vec3 _euler{0, 0, 0};

    uint _flagChange{0};
    uint _dirtyFlag{0};
    uint _layer{0};

    bool              _eulerDirty{false};
    NodeUiProperties *_uiProps{nullptr};

    friend void componentCorrupted(Node *node, Component *comp, uint32_t index);
    friend class NodeActivator;
    friend class Scene;

    CC_DISALLOW_COPY_MOVE_ASSIGN(Node);
};

template <typename T>
bool Node::isNode(T *obj) {
    return dynamic_cast<Node *>(obj) != nullptr && dynamic_cast<Scene *>(obj) == nullptr;
}

template <typename... Args>
void Node::emit(const std::string &type, Args &&...args) {
    _eventProcessor->emit(type, std::forward<Args>(args)...);
}

template <typename... Args>
void Node::on(const std::string &type, std::function<void(Args...)> &&callback) {
    if (type == NodeEventType::TRANSFORM_CHANGED) {
        _eventMask |= TRANSFORM_ON;
    }
    _eventProcessor->on(type, std::forward<std::function<void(Args...)>>(callback));
}

template <typename Target, typename... Args>
void Node::on(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture) {
    if (type == NodeEventType::TRANSFORM_CHANGED) {
        _eventMask |= TRANSFORM_ON;
    }
    _eventProcessor->on(type, std::forward<std::function<void(Args...)>>(callback), target, useCapture);
}

template <typename Target, typename... Args>
void Node::on(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture) {
    if (type == NodeEventType::TRANSFORM_CHANGED) {
        _eventMask |= TRANSFORM_ON;
    }
    _eventProcessor->on(type, memberFn, target, useCapture);
}

template <typename Target, typename LambdaType>
std::enable_if_t<!std::is_member_function_pointer_v<LambdaType>, void>
Node::on(const std::string &type, LambdaType &&callback, Target *target, bool useCapture) {
    if (type == NodeEventType::TRANSFORM_CHANGED) {
        _eventMask |= TRANSFORM_ON;
    }
    _eventProcessor->on(type, callback, target, useCapture);
}

template <typename LambdaType>
std::enable_if_t<!std::is_member_function_pointer_v<LambdaType>, void>
Node::on(const std::string &type, LambdaType &&callback, bool useCapture) {
    if (type == NodeEventType::TRANSFORM_CHANGED) {
        _eventMask |= TRANSFORM_ON;
    }
    _eventProcessor->on(type, callback, useCapture);
}

template <typename... Args>
void Node::once(const std::string &type, std::function<void(Args...)> &&callback) {
    _eventProcessor->once(type, callback);
}

template <typename Target, typename... Args>
void Node::once(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture) {
    _eventProcessor->once(type, memberFn, target, useCapture);
}

template <typename Target, typename... Args>
void Node::once(const std::string &type, std::function<void(Args...)> &&callback, Target *target, bool useCapture) {
    _eventProcessor->once(type, std::forward<std::function<void(Args...)>>(callback), target, useCapture);
}

template <typename Target, typename LambdaType>
std::enable_if_t<!std::is_member_function_pointer_v<LambdaType>, void>
Node::once(const std::string &type, LambdaType &&callback, Target *target, bool useCapture) {
    _eventProcessor->once(type, callback, target, useCapture);
}

template <typename LambdaType>
std::enable_if_t<!std::is_member_function_pointer_v<LambdaType>, void>
Node::once(const std::string &type, LambdaType &&callback, bool useCapture) {
    _eventProcessor->once(type, callback, useCapture);
}

template <typename Target, typename... Args>
void Node::off(const std::string &type, void (Target::*memberFn)(Args...), Target *target, bool useCapture) {
    _eventProcessor->off(type, memberFn, target, useCapture);
    bool hasListeners = _eventProcessor->hasEventListener(type);
    if (!hasListeners) {
        if (type == NodeEventType::TRANSFORM_CHANGED) {
            _eventMask &= ~TRANSFORM_ON;
        }
    }
}

template <typename Target, typename... Args>
bool Node::hasEventListener(const std::string &type, void (Target::*memberFn)(Args...), Target *target) {
    return _eventProcessor->hasEventListener(type, memberFn, target);
}

} // namespace cc
