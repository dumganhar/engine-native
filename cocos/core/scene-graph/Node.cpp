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

#include "Node.h"
#include <string>
#include "NodeEnum.h"
#include "core/scene-graph/BaseNode.h"
#include "math/Mat3.h"
#include "math/Mat4.h"
#include "math/Vec3.h"

namespace cc {

std::vector<BaseNode *> Node::dirtyNodes;
uint                    Node::clearFrame{0};
uint                    Node::clearRound{1000};
bool                    Node::isStatic{false};

namespace {
std::unordered_map<Node *, int32_t /* place_holder */> allNodes; //cjh how to clear ?
}

Node::Node() : BaseNode("") {
    allNodes.emplace(this, 0);
}

Node::Node(const std::string &name) : BaseNode(name) {
    allNodes.emplace(this, 0);
}

Node::~Node() {
    auto iter = allNodes.find(this);
    if (iter != allNodes.end()) {
        allNodes.erase(iter);
    }
}

void Node::setPosition(float x, float y, float z) {
    _localPosition.set(x, y, z);
    invalidateChildren(TransformBit::POSITION);

    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::POSITION);
    }
}

void Node::setRotation(float x, float y, float z, float w) {
    _localRotation.set(x, y, z, w);
    _eulerDirty = true;

    invalidateChildren(TransformBit::ROTATION);

    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::ROTATION);
    }
}

void Node::setRotationFromEuler(float x, float y, float z) {
    _euler.set(x, y, z);
    Quaternion::fromEuler(x, y, z, &_localRotation);
    _eulerDirty = false;
    invalidateChildren(TransformBit::ROTATION);
    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::ROTATION);
    }
}

void Node::setScale(float x, float y, float z) {
    _localScale.set(x, y, z);

    invalidateChildren(TransformBit::SCALE);
    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::SCALE);
    }
}

void Node::updateWorldTransform() {
    if (!getDirtyFlag()) {
        return;
    }
    index_t    i    = 0;
    BaseNode * curr = this;
    Mat3       mat3;
    Mat3       m43;
    Quaternion quat;
    while (curr && curr->getDirtyFlag()) {
        setDirtyNode(i++, curr);
        curr = curr->getParent();
    }
    BaseNode *child{nullptr};
    uint      dirtyBits = 0;
    while (i) {
        child = getDirtyNode(--i);
        if (!child) {
            continue;
        }
        dirtyBits |= child->getDirtyFlag();
        auto *currChild = child;
        if (curr) {
            if (dirtyBits & static_cast<uint>(TransformBit::POSITION)) {
                currChild->_worldPosition.transformMat4(currChild->_localPosition, curr->getWorldMatrix());
                currChild->_worldMatrix.m[12] = currChild->_worldPosition.x;
                currChild->_worldMatrix.m[13] = currChild->_worldPosition.y;
                currChild->_worldMatrix.m[14] = currChild->_worldPosition.z;
            }
            if (dirtyBits & static_cast<uint>(TransformBit::RS)) {
                Mat4::fromRTS(currChild->_localRotation, currChild->_localPosition, currChild->_localScale, &currChild->_worldMatrix);
                Mat4::multiply(curr->getWorldMatrix(), currChild->_worldMatrix, &currChild->_worldMatrix);
                if (dirtyBits & static_cast<uint>(TransformBit::ROTATION)) {
                    Quaternion::multiply(curr->getWorldRotation(), currChild->_localRotation, &currChild->_worldRotation);
                }
                quat = currChild->_worldRotation;
                quat.conjugate();
                Mat3::fromQuat(mat3, quat);
                Mat3::fromMat4(m43, currChild->_worldMatrix);
                Mat3::multiply(mat3, mat3, m43);
                currChild->_worldScale.set(mat3.m[0], mat3.m[4], mat3.m[8]);
            }
        } else if (child) {
            if (dirtyBits & static_cast<uint>(TransformBit::POSITION)) {
                currChild->_worldPosition.set(currChild->_localPosition);
                currChild->_worldMatrix.m[12] = currChild->_worldPosition.x;
                currChild->_worldMatrix.m[13] = currChild->_worldPosition.y;
                currChild->_worldMatrix.m[14] = currChild->_worldPosition.z;
            }
            if (dirtyBits & static_cast<uint>(TransformBit::RS)) {
                if (dirtyBits & static_cast<uint>(TransformBit::ROTATION)) {
                    currChild->_worldRotation.set(currChild->_localRotation);
                }
                if (dirtyBits & static_cast<uint>(TransformBit::SCALE)) {
                    currChild->_worldScale.set(currChild->_localScale);
                    Mat4::fromRTS(currChild->_worldRotation, currChild->_worldPosition, currChild->_worldScale, &currChild->_worldMatrix);
                }
            }
        }
        child->setDirtyFlag(static_cast<uint>(TransformBit::NONE));
        curr = child;
    }
}

const Mat4 &Node::getWorldMatrix() {
    updateWorldTransform();
    return _worldMatrix;
}

Mat4 Node::getWorldRS() {
    updateWorldTransform();
    Mat4 target{_worldMatrix};
    target.m[12] = target.m[13] = target.m[14] = 0;
    return target;
}

Mat4 Node::getWorldRT() {
    updateWorldTransform();
    Mat4 target;
    Mat4::fromRT(_worldRotation, _worldPosition, &target);
    return target;
}

void Node::invalidateChildren(TransformBit dirtyBit) {
    uint       curDirtyBit{static_cast<uint>(dirtyBit)};
    const uint childDirtyBit{curDirtyBit | static_cast<uint>(TransformBit::POSITION)};
    setDirtyNode(0, this);
    int i{0};
    while (i >= 0) {
        BaseNode *cur = getDirtyNode(i--);
        if (cur == nullptr) {
            continue; //cjh TODO: remove BaseNode;
        }

        const uint hasChangedFlags = cur->getChangedFlags();
        if (cur->isValid() && (cur->getDirtyFlag() & hasChangedFlags & curDirtyBit) != curDirtyBit) {
            cur->setDirtyFlag(cur->getDirtyFlag() | curDirtyBit);
            cur->setChangedFlags(hasChangedFlags | curDirtyBit);
            int childCount{static_cast<int>(cur->getChildren().size())};
            for (BaseNode *curChild : cur->getChildren()) {
                setDirtyNode(++i, reinterpret_cast<Node *>(curChild));
            }
        }
        curDirtyBit = childDirtyBit;
    }
}

void Node::setWorldPosition(float x, float y, float z) {
    _worldPosition.set(x, y, z);
    if (_parent) {
        _parent->updateWorldTransform();
        Mat4 invertWMat{_parent->getWorldMatrix()};
        invertWMat.inverse();
        _localPosition.transformMat4(_worldPosition, invertWMat);
    } else {
        _localPosition.set(_worldPosition);
    }
    invalidateChildren(TransformBit::POSITION);

    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::POSITION);
    }
}

const Vec3 &Node::getWorldPosition() {
    updateWorldTransform();
    return _worldPosition;
}

void Node::setWorldRotation(float x, float y, float z, float w) {
    _worldRotation.set(x, y, z, w);
    if (_parent) {
        _parent->updateWorldTransform();
        _localRotation.set(_parent->getWorldRotation().getConjugated());
        _localRotation.multiply(_worldRotation);
    } else {
        _localRotation.set(_worldRotation);
    }

    _eulerDirty = true;

    invalidateChildren(TransformBit::ROTATION);

    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::ROTATION);
    }
}

const Quaternion &Node::getWorldRotation() {
    updateWorldTransform();
    return _worldRotation;
}

void Node::setWorldScale(float x, float y, float z) {
    _worldScale.set(x, y, z);
    if (_parent != nullptr) {
        _parent->updateWorldTransform();
        Mat3 m3_1;
        Mat3::fromQuat(m3_1, _parent->getWorldRotation().getConjugated());
        Mat3 b;
        Mat3::fromMat4(b, _parent->getWorldMatrix());
        Mat3::multiply(m3_1, m3_1, b);
        Mat3 m3_scaling;
        m3_scaling.m[0] = _worldScale.x;
        m3_scaling.m[4] = _worldScale.y;
        m3_scaling.m[8] = _worldScale.z;

        m3_1.inverse();
        Mat3::multiply(m3_1, m3_scaling, m3_1);
        _localScale.x = Vec3{m3_1.m[0], m3_1.m[1], m3_1.m[2]}.length();
        _localScale.y = Vec3{m3_1.m[3], m3_1.m[4], m3_1.m[5]}.length();
        _localScale.z = Vec3{m3_1.m[6], m3_1.m[7], m3_1.m[8]}.length();
    } else {
        _localScale = _worldScale;
    }

    invalidateChildren(TransformBit::SCALE);
    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::SCALE);
    }
}

const Vec3 &Node::getWorldScale() {
    updateWorldTransform();
    return _worldScale;
}

void Node::setDirtyNode(const index_t idx, BaseNode *node) {
    if (idx >= dirtyNodes.size()) {
        if (dirtyNodes.empty()) {
            dirtyNodes.reserve(16); // Make a pre-allocated size for dirtyNode vector for better grow performance.
        }
        dirtyNodes.resize(idx + 1, nullptr);
    }
    dirtyNodes[idx] = node;
}

BaseNode *Node::getDirtyNode(const index_t idx) {
    return dirtyNodes[idx];
}

void Node::setAngle(float val) {
    _euler.set(0, 0, val);
    Quaternion::createFromAxisAngle(Vec3(0, 0, 1), val, &_localRotation);
    _eulerDirty = false;
    invalidateChildren(TransformBit::ROTATION);
    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::ROTATION);
    }
}

void Node::setParent(BaseNode *val, bool isKeepWorld /* = false */) {
    if (isKeepWorld) updateWorldTransform();
    BaseNode::setParent(val, isKeepWorld);
}

void Node::onSetParent(BaseNode *oldParent, bool keepWorldTransform) {
    BaseNode::onSetParent(oldParent, keepWorldTransform);
    if (keepWorldTransform) {
        BaseNode *parent = _parent;
        if (parent) {
            parent->updateWorldTransform();
            Mat4 mTemp{Mat4::IDENTITY};
            Mat4::inverseTranspose(parent->getWorldMatrix(), &mTemp);
            mTemp *= _worldMatrix;

        } else {
            _localPosition.set(_worldPosition);
            _localRotation.set(_worldRotation);
            _localScale.set(_worldScale);
        }
        _eulerDirty = true;
    }
    invalidateChildren(TransformBit::TRS);
}

void Node::rotate(const Quaternion &rot, NodeSpace ns) {
    Quaternion qTempA{rot};
    Quaternion qTempB{Quaternion::identity()};
    qTempA.normalize();
    if (ns == NodeSpace::LOCAL) {
        _localRotation *= qTempA;
    } else if (ns == NodeSpace::WORLD) {
        qTempB = qTempA * _worldRotation;
        qTempA = _worldRotation;
        qTempA.inverse();
        qTempB         = qTempA * qTempB;
        _localRotation = _localRotation * qTempB;
    }
    _eulerDirty = true;
    invalidateChildren(TransformBit::ROTATION);
    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::ROTATION);
    }
}

void Node::lookAt(const Vec3 &pos, const Vec3 &up) {
    Vec3       vTemp = getWorldPosition();
    Quaternion qTemp{Quaternion::identity()};
    vTemp -= pos;
    vTemp.normalize();
    Quaternion::fromViewUp(qTemp, vTemp, up);
    setWorldRotation(qTemp);
}

void Node::inverseTransformPoint(Vec3 &out, const Vec3 &p) {
    out.set(p.x, p.y, p.z);
    BaseNode *cur{this};
    index_t   i{0};
    while (cur != nullptr && cur->getParent()) {
        setDirtyNode(i++, cur);
        cur = cur->getParent();
    }
    while (i >= 0) {
        Vec3::transformInverseRTS(out, out, cur->getRotation(), cur->getPosition(), cur->getScale());
        --i;
        cur = dirtyNodes[i];
    }
}

void Node::setWorldRotationFromEuler(float x, float y, float z) {
    Quaternion::fromEuler(x, y, z, &_worldRotation);
    if (_parent) {
        _parent->updateWorldTransform();
        _localRotation = _parent->getWorldRotation().getConjugated() * _worldRotation;
    } else {
        _localRotation = _worldRotation;
    }
    _eulerDirty = true;

    invalidateChildren(TransformBit::ROTATION);
    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::ROTATION);
    }
}

void Node::setRTS(Quaternion *rot, Vec3 *pos, Vec3 *scale) {
    uint dirtyBit = 0;
    if (rot) {
        dirtyBit |= static_cast<uint>(TransformBit::ROTATION);
        _localRotation = _worldRotation;
        _eulerDirty    = true;
    }
    if (pos) {
        _localPosition = _worldPosition;
        dirtyBit |= static_cast<uint>(TransformBit::POSITION);
    }
    if (scale) {
        _localScale = _worldScale;
        dirtyBit |= static_cast<uint>(TransformBit::SCALE);
    }
    if (dirtyBit) {
        invalidateChildren(static_cast<TransformBit>(dirtyBit));
        if (_eventMask & TRANSFORM_ON) {
            emit(NodeEventType::TRANSFORM_CHANGED, dirtyBit);
        }
    }
}

void Node::resetChangedFlags() {
    for (auto &e : allNodes) {
        e.first->setChangedFlags(0);
    }
}

void Node::clearNodeArray() {
    if (clearFrame < clearRound) {
        clearFrame++;
    } else {
        clearFrame = 0;
        dirtyNodes.clear();
    }
}

void Node::translate(const Vec3 &trans, NodeSpace ns) {
    Vec3 v3Temp{trans};
    if (ns == NodeSpace::LOCAL) {
        v3Temp.transformQuat(_localRotation);
        _localPosition.x += v3Temp.x;
        _localPosition.y += v3Temp.y;
        _localPosition.z += v3Temp.z;
    } else if (ns == NodeSpace::WORLD) {
        if (_parent) {
            Quaternion qTemp = _parent->getWorldRotation();
            qTemp.inverse();
            v3Temp.transformQuat(qTemp);
            Vec3 scale{_worldScale};
            _localPosition.x += v3Temp.x / scale.x;
            _localPosition.y += v3Temp.y / scale.y;
            _localPosition.z += v3Temp.z / scale.z;
        } else {
            _localPosition.x += trans.x;
            _localPosition.y += trans.y;
            _localPosition.z += trans.z;
        }
    }
    invalidateChildren(TransformBit::POSITION);
    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::POSITION);
    }
}

bool Node::onPreDestroy() {
    bool result = onPreDestroyBase();
    // TODO(Lenovo): bookOfChange free
    return result;
}

void Node::onHierarchyChanged(BaseNode *oldParent) {
    //cjh TODO:    this.eventProcessor.reattach();
    onHierarchyChangedBase(oldParent);
}

} // namespace cc
