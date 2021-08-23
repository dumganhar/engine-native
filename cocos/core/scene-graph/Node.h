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
#include "core/scene-graph/BaseNode.h"
#include "core/scene-graph/NodeEnum.h"
#include "core/scene-graph/Scene.h"
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Quaternion.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "base/TypeDef.h"

namespace cc {
namespace scenegraph {
/**
 * Event types emitted by Node
 */
using EventType = NodeEventType;
/**
 * Bit masks for Node transformation parts
 */
using TransformDirtyBit = TransformBit;
class NodeUiProperties;
// This struct defines the memory layout shared between JS and C++.
struct NodeLayout {
    uint       dirtyFlag{0};
    uint           layer{0};
    cc::Vec3       worldScale;
    cc::Vec3       worldPosition;
    cc::Quaternion worldRotation;
    cc::Mat4       worldMatrix;
    cc::Vec3       localScale;
    cc::Vec3       localPosition;
    cc::Quaternion localRotation;
};

class Node final : public BaseNode {
public:
    Node();
    explicit Node(const std::string &name);
    Node(const Node &) = delete;
    Node(Node &&)      = delete;
    ~Node() override   = default;
    Node &operator=(const Node &) = delete;
    Node &operator=(Node &&) = delete;

    static bool  isStatic;
    static void  setDirtyNode(const index_t idx, Node *node);
    static Node *getDirtyNode(const index_t idx);
    static Node *find(const std::string &, Node *referenceNode = nullptr);
    template <typename T>
    static bool isNode(T *obj);
    static void resetHasChangedFlags();
    static void clearNodeArray();

    NodeUiProperties *uiProps;
    void              invalidateChildren(TransformBit dirtyBit);

    void updateWorldTransform() override;
    void updateWorldRTMatrix() override;

    void translate(const Vec3 &, NodeSpace ns = NodeSpace::LOCAL);
    void rotate(const Quaternion &rot, NodeSpace ns);
    void lookAt(const Vec3 &pos, const Vec3 &up);
    void setWorldPosition(float x, float y, float z) override;
    void setWorldRotation(float x, float y, float z, float w) override;
    void setRotationFromEuler(float x, float y, float z);
    void setParent(BaseNode *val, bool isKeepWorld) override;
    void inverseTransformPoint(Vec3 &out, const Vec3 &p);
    void setWorldRotationFromEuler(float x, float y, float z);
    /**
     * Set local transformation with rotation, position and scale separately.
     */
    void        setRTS(Quaternion *rot = nullptr, Vec3 *pos = nullptr, Vec3 *scale = nullptr);
    inline void pauseSystemEvents(bool recursive) {}
    inline void resumeSystemEvents(bool recursive) {}

    inline void setRotationFromEuler(float x, float y) {
        setRotationFromEuler(x, y, _euler.z);
    }
    inline void setRotationFromEuler(const Vec3 &val) {
        setRotationFromEuler(val.x, val.y, val.z);
    }

    inline void setFlagsChanged(uint value) override { _flagChange = value; }
    inline void setDirtyFlag(uint value) override { _dirtyFlag = value; }
    inline void setLayer(uint layer) override { _layer = layer; }
    inline void setWorldMatrix(const Mat4 &matrix) override { _worldMatrix.set(matrix); }
    inline void setWorldPosition(const Vec3 &pos) override { setWorldPosition(pos.x, pos.y, pos.z); }
    inline void setWorldRotation(const Quaternion &rotation) override { setWorldRotation(rotation.x, rotation.y, rotation.z, rotation.w); }
    inline void setWorldScale(const Vec3 &scale) override { _worldScale.set(scale); }
    inline void setLocalPosition(const Vec3 &pos) override { _localPosition.set(pos); }
    inline void setLocalPosition(float x, float y, float z) override { _localPosition.set(x, y, z); }
    inline void setLocalRotation(const Quaternion &rotation) override { _localRotation.set(rotation); }
    inline void setLocalRotation(float x, float y, float z, float w) override { _localRotation.set(x, y, z, w); }
    inline void setLocalScale(const Vec3 &scale) override { _localScale.set(scale); }
    inline void setEulerAngles(const Vec3 &val) {
        setRotationFromEuler(val.x, val.y, val.z);
    }
    inline void setForward(const Vec3 &dir) {
        uint   len    = dir.length();
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

protected:
    bool onPreDestroy() override;
    bool _eulerDirty{false};
    void onSetParent(BaseNode *oldParent, bool keepWorldTransform) override;

private:
    static std::vector<BaseNode *> dirtyNodes;
    static uint                clearFrame;
    static uint                clearRound;
    TransformBit                   _dirtyFlagsPri{TransformBit::NONE};
    Vec3                           _euler{0, 0, 0};
};

} // namespace scenegraph
} // namespace cc
