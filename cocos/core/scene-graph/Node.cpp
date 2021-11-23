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

#include "core/scene-graph/Node.h"
#include "core/Director.h"
#include "core/Game.h"
#include "core/data/Object.h"
#include "core/event/EventTypesToJS.h"
#include "core/scene-graph/Find.h"
#include "core/scene-graph/NodeActivator.h"
#include "core/scene-graph/NodeEnum.h"
#include "core/scene-graph/Scene.h"
#include "core/utils/IDGenerator.h"

namespace cc {

// static variables
std::vector<Node *>              Node::dirtyNodes;
uint32_t                         Node::clearFrame{0};
uint32_t                         Node::clearRound{1000};
bool                             Node::isStatic{false};
const uint32_t                   Node::TRANSFORM_ON{1 << 0};
const uint32_t                   Node::DESTROYING{static_cast<uint>(CCObject::Flags::DESTROYING)};
const uint32_t                   Node::DEACTIVATING{static_cast<uint>(CCObject::Flags::DEACTIVATING)};
const uint32_t                   Node::DONT_DESTROY{static_cast<uint>(CCObject::Flags::DONT_DESTROY)};
index_t                          Node::stackId{0};
std::vector<std::vector<Node *>> Node::stacks;
//

namespace {
std::unordered_map<Node *, int32_t /* place_holder */> allNodes; //cjh how to clear ?
const std::string                                      EMPTY_NODE_NAME;
IDGenerator                                            idGenerator("Node");
} // namespace

Node::Node() : Node(EMPTY_NODE_NAME) {
}

Node::Node(const std::string &name) {
    _id = idGenerator.getNewId();
    if (name.empty()) {
        _name.append("New Node");
    } else {
        _name = name;
    }
    allNodes.emplace(this, 0);
    _eventProcessor = new NodeEventProcessor(this);
}

Node::~Node() {
    auto iter = allNodes.find(this);
    if (iter != allNodes.end()) {
        allNodes.erase(iter);
    }
    CC_SAFE_DELETE(_eventProcessor);
    CC_SAFE_DELETE(_userData);
}

void Node::onBatchCreated(bool dontChildPrefab) {
    // onBatchCreated was implemented in TS, so code should never go here.
    CC_ASSERT(false);
    emit(EventTypesToJS::NODE_ON_BATCH_CREATED, dontChildPrefab);
}

Node *Node::instantiate(Node *cloned, bool isSyncedNode) {
    if (!cloned) {
        CC_ASSERT(false);
        // TODO: cloned = legacyCC.instantiate._clone(this, this);
        return nullptr;
    }
    // TODO
    //const newPrefabInfo = cloned._prefab;
    //if (EDITOR && newPrefabInfo) {
    //    if (cloned == = newPrefabInfo.root) {
    //        // newPrefabInfo.fileId = '';
    //    } else {
    //        // var PrefabUtils = Editor.require('scene://utils/prefab');
    //        // PrefabUtils.unlinkPrefab(cloned);
    //    }
    //}
    //if (EDITOR && legacyCC.GAME_VIEW) {
    //    const syncing = newPrefabInfo&& cloned == = newPrefabInfo.root && newPrefabInfo.sync;
    //    if (!syncing) {
    //        cloned._name += ' (Clone)';
    //    }
    //}
    cloned->_parent = nullptr;
    cloned->onBatchCreated(isSyncedNode);
    return cloned;
}

void Node::onHierarchyChangedBase(Node *oldParent) {
    Node * newParent = _parent;
    auto *scene     = dynamic_cast<Scene *>(newParent);
    if (isPersistNode() && scene) {
        emit(EventTypesToJS::NODE_REMOVE_PERSIST_ROOT_NODE);

        //        if (EDITOR) {
        //            warnID(1623);
        //        }
    }
    // TODO
    //if (EDITOR) {
    //    const scene                = legacyCC.director.getScene() as this | null;
    //    const inCurrentSceneBefore = oldParent && oldParent.isChildOf(scene);
    //    const inCurrentSceneNow    = newParent && newParent.isChildOf(scene);
    //    if (!inCurrentSceneBefore && inCurrentSceneNow) {
    //        // attached
    //        this._registerIfAttached !(true);
    //    } else if (inCurrentSceneBefore && !inCurrentSceneNow) {
    //        // detached
    //        this._registerIfAttached !(false);
    //    }

    //    // conflict detection
    //    // _Scene.DetectConflict.afterAddChild(this);
    //}
    bool shouldActiveNow = _active && !!(newParent && newParent->_activeInHierarchy);
    if (_activeInHierarchy != shouldActiveNow) {
        Director::getInstance()->getNodeActivator()->activateNode(this, shouldActiveNow);
        emit(EventTypesToJS::NODE_ACTIVE_NODE, shouldActiveNow);
    }
}

void Node::off(const CallbacksInvoker::KeyType &type, bool useCapture) {
    _eventProcessor->off(type, useCapture);
    bool hasListeners = _eventProcessor->hasEventListener(type);
    if (!hasListeners) {
        if (type == NodeEventType::TRANSFORM_CHANGED) {
            _eventMask &= ~TRANSFORM_ON;
        }
    }
}

void Node::off(const CallbacksInvoker::KeyType &type, CallbackInfoBase::ID cbID, bool useCapture) {
    _eventProcessor->off(type, cbID, useCapture);
    bool hasListeners = _eventProcessor->hasEventListener(type);
    if (!hasListeners) {
        if (type == NodeEventType::TRANSFORM_CHANGED) {
            _eventMask &= ~TRANSFORM_ON;
        }
    }
}

void Node::off(const CallbacksInvoker::KeyType &type, void *target, bool useCapture) {
    _eventProcessor->off(type, target, useCapture);
    bool hasListeners = _eventProcessor->hasEventListener(type);
    if (!hasListeners) {
        if (type == NodeEventType::TRANSFORM_CHANGED) {
            _eventMask &= ~TRANSFORM_ON;
        }
    }
}

void Node::dispatchEvent(event::Event *eve) {
    _eventProcessor->dispatchEvent(eve);
}

bool Node::hasEventListener(const CallbacksInvoker::KeyType &type) const {
    return _eventProcessor->hasEventListener(type);
}

bool Node::hasEventListener(const CallbacksInvoker::KeyType &type, CallbackInfoBase::ID cbID) const {
    return _eventProcessor->hasEventListener(type, cbID);
}
bool Node::hasEventListener(const CallbacksInvoker::KeyType &type, void *target) const {
    return _eventProcessor->hasEventListener(type, target);
}
bool Node::hasEventListener(const CallbacksInvoker::KeyType &type, void *target, CallbackInfoBase::ID cbID) const {
    return _eventProcessor->hasEventListener(type, target, cbID);
}

void Node::targetOff(const CallbacksInvoker::KeyType &type) {
    _eventProcessor->targetOff(type);
    if ((_eventMask & TRANSFORM_ON) && !_eventProcessor->hasEventListener(NodeEventType::TRANSFORM_CHANGED)) {
        _eventMask &= ~TRANSFORM_ON;
    }
}

void Node::setActive(bool isActive) {
    if (_active != isActive) {
        _active      = isActive;
        Node *parent = _parent;
        if (parent) {
            bool couldActiveInScene = parent->_activeInHierarchy;
            if (couldActiveInScene) {
                emit(EventTypesToJS::NODE_ACTIVE_NODE, isActive);
            }
        }
    }
}

void Node::setParent(Node *parent, bool isKeepWorld /* = false */) {
    if (isKeepWorld) {
        updateWorldTransform();
    }

    if (_parent == parent) {
        return;
    }

    Node *oldParent = _parent;
    Node *newParent = parent;
    // if (CC_DEBUG && oldParent && !!(oldParent->_objFlags & Flags::DEACTIVATING)) {
    //     // TODO: errorID not implemented
    // }
    _parent       = newParent;
    _siblingIndex = 0;
    onSetParent(oldParent, isKeepWorld);
    emit(NodeEventType::PARENT_CHANGED, oldParent);
    if (oldParent) {
        if (!(oldParent->_objFlags & Flags::DESTROYING)) {
            index_t removeAt = getIdxOfChild(oldParent->_children, this);
            // TODO: DEV
            /*if (DEV && removeAt < 0) {
                errorID(1633);
                return;
            }*/
            if (removeAt < 0) {
                return;
            }
            oldParent->_children.erase(oldParent->_children.begin() + removeAt);
            oldParent->updateSiblingIndex();
            oldParent->emit(NodeEventType::CHILD_REMOVED, this);
        }
    }
    if (newParent) {
        // if (CC_DEBUG && !!(newParent->_objFlags & Flags::DEACTIVATING)) {
        //     // TODO:errorID(3821);
        // }
        newParent->_children.emplace_back(this);
        _siblingIndex = newParent->_children.size() - 1;
        newParent->emit(NodeEventType::CHILD_ADDED, this);
    }
    onHierarchyChanged(oldParent);
}

Scene *Node::getScene() const {
    return _scene;
}

void Node::walk(const std::function<void(Node *)> &preFunc) {
    walk(preFunc, nullptr);
}

void Node::walk(const std::function<void(Node *)> &preFunc, const std::function<void(Node *)> &postFunc) {
    index_t                    index{1};
    index_t                    i{0};
    const std::vector<Node *> *children = nullptr;
    Node *                     curr{nullptr};
    auto                       stacksCount = static_cast<index_t>(Node::stacks.size());
    if (stackId >= stacksCount) {
        stacks.resize(stackId + 1);
    }
    auto stack = stacks[stackId];
    stackId++;

    stack.clear();
    stack.resize(1);
    stack[0] = this;
    Node *parent{nullptr};
    bool  afterChildren{false};
    while (index) {
        index--;
        auto stackCount = static_cast<index_t>(stack.size());
        if (index >= stackCount) {
            continue;
        }
        curr = stack[index];
        if (curr == nullptr) {
            continue;
        }
        if (!afterChildren && preFunc != nullptr) {
            // pre call
            preFunc(curr);
        } else if (afterChildren && postFunc != nullptr) {
            // post call
            postFunc(curr);
        }
        stack[index] = nullptr;
        if (afterChildren) {
            if (parent == _parent) {
                break;
            }
            afterChildren = false;
        } else {
            if (static_cast<index_t>(curr->_children.size()) > 0) {
                parent       = curr;
                children     = &curr->_children;
                i            = 0;
                stack[index] = (*children)[i];
                stack.resize(++index);
            } else {
                stack[index] = curr;
                stack.resize(++index);
                afterChildren = true;
            }
            continue;
        }

        if (children != nullptr && !children->empty()) {
            i++;
            if (i < children->size() && children->at(i) != nullptr) {
                stack[index] = children->at(i);
                stack.resize(++index);
            } else if (parent) {
                stack[index] = parent;
                stack.resize(++index);
                afterChildren = true;
                if (parent->_parent != nullptr) {
                    children    = &parent->_parent->_children;
                    index_t idx = getIdxOfChild(*children, parent);
                    if (idx != CC_INVALID_INDEX) {
                        i = idx;
                    }
                    parent = parent->_parent;
                } else {
                    // At root
                    parent   = nullptr;
                    children = nullptr;
                }
                if (i < 0) {
                    break;
                }
            }
        }
    }
    stack.clear();
    stackId--;
}

Component *Node::addComponent(Component *comp) {
    comp->_node = this; //cjh TODO: shared_ptr
    _components.emplace_back(comp);

    if (_activeInHierarchy) {
        Director::getInstance()->getNodeActivator()->activateComp(comp);
    }

    return comp;
}

void Node::removeComponent(Component *comp) {
    auto iteComp = std::find(_components.begin(), _components.end(), comp);
    if (iteComp != _components.end()) {
        _components.erase(iteComp);
    }
}

bool Node::onPreDestroyBase() {
    Flags destroyingFlag = Flags::DESTROYING;
    _objFlags |= destroyingFlag;
    bool destroyByParent = (!!_parent) && (!!(_parent->_objFlags & destroyingFlag));
    // TODO
    /*if (!destroyByParent && EDITOR) {
        this._registerIfAttached !(false);
    }*/
    if (isPersistNode()) {
        emit(EventTypesToJS::NODE_REMOVE_PERSIST_ROOT_NODE);
    }
    if (!destroyByParent) {
        if (_parent) {
            emit(NodeEventType::PARENT_CHANGED, this);
            index_t childIdx = getIdxOfChild(_parent->_children, this);
            if (childIdx != -1) {
                _parent->_children.erase(_parent->_children.begin() + childIdx);
            }
            _siblingIndex = 0;
            _parent->updateSiblingIndex();
            _parent->emit(NodeEventType::CHILD_REMOVED, this);
        }
    }
    emit(NodeEventType::NODE_DESTROYED, this);
    for (auto *child : _children) {
        child->destroyImmediate();
    }

    emit(EventTypesToJS::NODE_DESTROY_COMPONENTS);
    _eventProcessor->destroy();
    return destroyByParent;
}

Node *Node::getChildByName(const std::string &name) const {
    if (name.empty()) {
        CC_LOG_INFO("Invalid name");
        return nullptr;
    }
    for (auto *child : _children) {
        if (child->_name == name) {
            return child;
        }
    }
    return nullptr;
}

void Node::setScene(Node *node) {
    node->updateScene();
}

index_t Node::getIdxOfChild(const std::vector<Node *> &child, Node *target) {
    auto iteChild = std::find(child.begin(), child.end(), target);
    if (iteChild != child.end()) {
        return iteChild - child.begin();
    }
    return CC_INVALID_INDEX;
}

Node *Node::getChildByUuid(const std::string &uuid) const {
    if (uuid.empty()) {
        CC_LOG_INFO("Invalid uuid");
        return nullptr;
    }
    for (auto *child : _children) {
        if (child->_id == uuid) {
            return child;
        }
    }
    return nullptr;
}

bool Node::isChildOf(Node *parent) {
    Node *child = this;
    do {
        if (child == parent) {
            return true;
        }
        child = child->_parent;
    } while (child);
    return false;
}

void Node::removeAllChildren() {
    for (auto *child : _children) {
        if (child) {
            child->setParent(nullptr);
        }
    }
    _children.clear();
}

void Node::setSiblingIndex(index_t index) {
    if (!_parent) {
        return;
    }
    if (!!(_parent->_objFlags & Flags::DEACTIVATING)) {
        // TODO: errorID(3821);
        return;
    }
    std::vector<Node *> &siblings = _parent->_children;
    index                         = index != -1 ? index : siblings.size() - 1;
    index_t oldIdx                = getIdxOfChild(siblings, this);
    if (index != oldIdx) {
        siblings.erase(siblings.begin() + oldIdx);
        if (index < siblings.size()) {
            siblings.insert(siblings.begin() + 2, 1, this);
        } else {
            siblings.emplace_back(this);
        }
        _parent->updateSiblingIndex();
        onSiblingIndexChanged(index);
    }
}

Node *Node::getChildByPath(const std::string &path) const {
    size_t                   start;
    size_t                   end      = 0;
    std::vector<std::string> segments = StringUtil::split(path, "/");
    auto *                   lastNode = const_cast<Node *>(this);
    for (const std::string &segment : segments) {
        if (segment.empty()) {
            continue;
        }
        Node *next{nullptr};
        if (lastNode) {
            for (auto *child : lastNode->_children) {
                if (child->_name == segment) {
                    next = child;
                    break;
                }
            }
            lastNode = next;
        } else {
            break;
        }
    }
    return lastNode;
}

//

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
    Node *     curr = this;
    Mat3       mat3;
    Mat3       m43;
    Quaternion quat;
    while (curr && curr->getDirtyFlag()) {
        setDirtyNode(i++, curr);
        curr = curr->getParent();
    }
    Node *   child{nullptr};
    uint32_t dirtyBits = 0;
    while (i) {
        child = getDirtyNode(--i);
        if (!child) {
            continue;
        }
        dirtyBits |= child->getDirtyFlag();
        auto *currChild = child;
        if (curr) {
            if (dirtyBits & static_cast<uint32_t>(TransformBit::POSITION)) {
                currChild->_worldPosition.transformMat4(currChild->_localPosition, curr->getWorldMatrix());
                currChild->_worldMatrix.m[12] = currChild->_worldPosition.x;
                currChild->_worldMatrix.m[13] = currChild->_worldPosition.y;
                currChild->_worldMatrix.m[14] = currChild->_worldPosition.z;
            }
            if (dirtyBits & static_cast<uint32_t>(TransformBit::RS)) {
                Mat4::fromRTS(currChild->_localRotation, currChild->_localPosition, currChild->_localScale, &currChild->_worldMatrix);
                Mat4::multiply(curr->getWorldMatrix(), currChild->_worldMatrix, &currChild->_worldMatrix);
                if (dirtyBits & static_cast<uint32_t>(TransformBit::ROTATION)) {
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
            if (dirtyBits & static_cast<uint32_t>(TransformBit::POSITION)) {
                currChild->_worldPosition.set(currChild->_localPosition);
                currChild->_worldMatrix.m[12] = currChild->_worldPosition.x;
                currChild->_worldMatrix.m[13] = currChild->_worldPosition.y;
                currChild->_worldMatrix.m[14] = currChild->_worldPosition.z;
            }
            if (dirtyBits & static_cast<uint32_t>(TransformBit::RS)) {
                if (dirtyBits & static_cast<uint32_t>(TransformBit::ROTATION)) {
                    currChild->_worldRotation.set(currChild->_localRotation);
                }
                if (dirtyBits & static_cast<uint32_t>(TransformBit::SCALE)) {
                    currChild->_worldScale.set(currChild->_localScale);
                    Mat4::fromRTS(currChild->_worldRotation, currChild->_worldPosition, currChild->_worldScale, &currChild->_worldMatrix);
                }
            }
        }
        child->setDirtyFlag(static_cast<uint32_t>(TransformBit::NONE));
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
    auto           curDirtyBit{static_cast<uint32_t>(dirtyBit)};
    const uint32_t childDirtyBit{curDirtyBit | static_cast<uint32_t>(TransformBit::POSITION)};
    setDirtyNode(0, this);
    int i{0};
    while (i >= 0) {
        Node *cur = getDirtyNode(i--);
        if (cur == nullptr) {
            continue;
        }

        const uint32_t hasChangedFlags = cur->getChangedFlags();
        if (cur->isValid() && (cur->getDirtyFlag() & hasChangedFlags & curDirtyBit) != curDirtyBit) {
            cur->setDirtyFlag(cur->getDirtyFlag() | curDirtyBit);
            if (_uiPropsTransformDirtyCallback != nullptr) {
                _uiPropsTransformDirtyCallback(&_uiTransformDirty);
            }
            //            emit(EventTypesToJS::NODE_UI_TRANSFORM_DIRTY, &_uiTransformDirty);
            cur->setChangedFlags(hasChangedFlags | curDirtyBit);

            for (Node *curChild : cur->getChildren()) {
                setDirtyNode(++i, curChild);
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

void Node::setDirtyNode(const index_t idx, Node *node) {
    if (idx >= dirtyNodes.size()) {
        if (dirtyNodes.empty()) {
            dirtyNodes.reserve(16); // Make a pre-allocated size for dirtyNode vector for better grow performance.
        }
        dirtyNodes.resize(idx + 1, nullptr);
    }
    dirtyNodes[idx] = node;
}

Node *Node::getDirtyNode(const index_t idx) {
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

void Node::onSetParent(Node *oldParent, bool keepWorldTransform) {
    if (_parent) {
        if ((oldParent == nullptr || oldParent->_scene != _parent->_scene) && _parent->_scene != nullptr) {
            walk(setScene);
        }
    }

    if (keepWorldTransform) {
        Node *parent = _parent;
        if (parent) {
            parent->updateWorldTransform();
            Mat4 mTemp{Mat4::IDENTITY}; //cjh FIXME: the logic is different from ts version.
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
    Node *  cur{this};
    index_t i{0};
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

void Node::setMatrix(const Mat4 &val) {
    val.decompose(&_localScale, &_localRotation, &_localPosition);
    invalidateChildren(TransformBit::TRS);
    _eulerDirty = true;
    if (_eventMask & TRANSFORM_ON) {
        emit(NodeEventType::TRANSFORM_CHANGED, TransformBit::TRS);
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
    uint32_t dirtyBit = 0;
    if (rot) {
        dirtyBit |= static_cast<uint32_t>(TransformBit::ROTATION);
        _localRotation = *rot;
        _eulerDirty    = true;
    }
    if (pos) {
        _localPosition = *pos;
        dirtyBit |= static_cast<uint32_t>(TransformBit::POSITION);
    }
    if (scale) {
        _localScale = *scale;
        dirtyBit |= static_cast<uint32_t>(TransformBit::SCALE);
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

void Node::onHierarchyChanged(Node *oldParent) {
    emit(EventTypesToJS::NODE_REATTACH);
    _eventProcessor->reattach();
    onHierarchyChangedBase(oldParent);
}

/* static */
Node *Node::find(const std::string &path, Node *referenceNode /* = nullptr*/) {
    return cc::find(path, referenceNode);
}

// For deserialization
void Node::_setChild(index_t i, Node *child) {
    if (i < _children.size()) {
        _children[i] = child;
    } else {
        CC_LOG_ERROR("Invalid index (%d) for Node children (size: %u)", i, static_cast<uint32_t>(_children.size()));
    }
}

Node *Node::_getChild(index_t i) {
    if (i < _children.size()) {
        return _children[i];
    }
    CC_LOG_ERROR("Invalid index (%d) for Node children (size: %u)", i, static_cast<uint32_t>(_children.size()));
    return nullptr;
}

void Node::_setChildrenSize(uint32_t size) {
    _children.resize(size);
}

uint32_t Node::_getChildrenSize() {
    return _children.size();
}

void Node::_setChildren(std::vector<Node *> &&children) {
    _children = std::move(children);
}

//

} // namespace cc
