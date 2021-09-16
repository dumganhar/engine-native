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

#include <vector>
#include "base/TypeDef.h"
#include "core/scene-graph/BaseNode.h"
#include "core/scene-graph/NodeEnum.h"
#include "core/scene-graph/Scene.h"
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Quaternion.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace cc {

/**
 * Event types emitted by Node
 */
using EventType = NodeEventType;
/**
 * Bit masks for Node transformation parts
 */
using TransformDirtyBit = TransformBit;
class NodeUiProperties;

class Node final : public BaseNode {
public:
    Node();
    explicit Node(const std::string &name);
    ~Node() override = default;

    static bool  isStatic;
    static void  setDirtyNode(const index_t idx, Node *node);
    static Node *getDirtyNode(const index_t idx);
    static Node *find(const std::string &, Node *referenceNode = nullptr);

    /**
     * @en Determine whether the given object is a normal Node. Will return false if [[Scene]] given.
     * @zh 指定对象是否是普通的节点？如果传入 [[Scene]] 会返回 false。
     */
    template <typename T>
    static bool isNode(T *obj);

    static void resetChangedFlags();
    static void clearNodeArray();

    NodeUiProperties *uiProps{nullptr};
    void              invalidateChildren(TransformBit dirtyBit);

    void translate(const Vec3 &, NodeSpace ns = NodeSpace::LOCAL);
    void rotate(const Quaternion &rot, NodeSpace ns);
    void lookAt(const Vec3 &pos, const Vec3 &up);

    void setParent(BaseNode *val, bool isKeepWorld = false) override;

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
    inline const Vec3 &getPosition() const { return _localPosition; }

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
    inline const Quaternion &getRotation() const { return _localRotation; }

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
    inline const Vec3 &getScale() const { return _localScale; }

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
    const Quaternion &getWorldRotation() override;

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
    void updateWorldTransform() override;

    /**
     * @en Get a world transform matrix
     * @zh 获取世界变换矩阵
     * @param out Set the result to out matrix
     * @return If `out` given, the return value equals to `out`, otherwise a new matrix will be generated and return
     */
    const Mat4 &getWorldMatrix() override;

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

    inline Vec3 getEulerAngles() {
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

    uint getChangedFlags() const override { return _flagChange; }
    void setChangedFlags(uint value) override { _flagChange = value; }
    void setDirtyFlag(uint value) override { _dirtyFlag = value; }
    uint getDirtyFlag() const { return _dirtyFlag; }
    void setLayer(uint layer) override { _layer = layer; }
    uint getLayer() const { return _layer; }

protected:
    bool onPreDestroy() override;

    void onSetParent(BaseNode *oldParent, bool keepWorldTransform) override;

    static std::vector<Node *> dirtyNodes;
    static uint                clearFrame;
    static uint                clearRound;

    TransformBit _dirtyFlagsPri{TransformBit::NONE};
    Vec3         _euler{0, 0, 0};

    uint _flagChange{0};
    uint _dirtyFlag{0};
    uint _layer{0};

    cc::Vec3       _worldPosition{Vec3::ZERO};
    cc::Quaternion _worldRotation{Quaternion::identity()};
    cc::Vec3       _worldScale{Vec3::ONE};

    Mat4     _rtMat{Mat4::IDENTITY};
    cc::Mat4 _worldMatrix{Mat4::IDENTITY};

    // local transform
    cc::Vec3       _localPosition{Vec3::ZERO};
    cc::Quaternion _localRotation{Quaternion::identity()};
    cc::Vec3       _localScale{Vec3::ONE};

    bool _eulerDirty{false};

    CC_DISALLOW_COPY_MOVE_ASSIGN(Node);
};

template <typename T>
bool Node::isNode(T *obj) {
    return dynamic_cast<Node *>(obj) != nullptr && dynamic_cast<Scene *>(obj) == nullptr;
}

} // namespace cc
