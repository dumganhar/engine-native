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

#include "core/scene-graph/BaseNode.h"
#include "core/Director.h"
#include "core/Game.h"
#include "core/data/Object.h"
#include "core/scene-graph/NodeActivator.h"
#include "core/scene-graph/NodeEventProcessor.h"
#include "core/scene-graph/Scene.h"

namespace cc {

const uint                           BaseNode::TRANSFORM_ON{1 << 0};
const uint                           BaseNode::DESTROYING{static_cast<uint>(CCObject::Flags::DESTROYING)};
const uint                           BaseNode::DEACTIVATING{static_cast<uint>(CCObject::Flags::DEACTIVATING)};
const uint                           BaseNode::DONT_DESTROY{static_cast<uint>(CCObject::Flags::DONT_DESTROY)};
index_t                              BaseNode::stackId{0};
std::vector<std::vector<BaseNode *>> BaseNode::stacks;

BaseNode::BaseNode(const std::string &name) : CCObject(name) {
    if (name.empty()) {
        _name.append("New Node");
        return;
    }
    _name = name;
}

void BaseNode::onBatchCreated(bool /*dontChildPrefab*/) {
    if (_parent) {
        index_t idx = getIdxOfChild(_parent->_children, this);
        if (idx != -1) {
            _siblingIndex = idx;
        }
    }
}

BaseNode *BaseNode::instantiate(BaseNode *cloned, bool isSyncedNode) {
    if (!cloned) {
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

void BaseNode::onHierarchyChangedBase(BaseNode *oldParent) {
    BaseNode *newParent = _parent;
    Scene *   scene     = dynamic_cast<Scene *>(newParent);
    if (_persistNode && scene) {
        // TODO
        /*legacyCC.game.removePersistRootNode(this);
        if (EDITOR) {
            warnID(1623);
        }*/
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
    }
}

void BaseNode::on(const std::string &type, const std::function<void(BaseNode *)> &callback) {
    if (type.compare(NodeEventType::TRANSFORM_CHANGED) == 0) {
        _eventMask |= TRANSFORM_ON;
    }
    cc::NodeEventProcessor::on(type, callback);
}

void BaseNode::on(const std::string &type, const std::function<void(BaseNode *)> &callback, const std::any &target, bool useCapture) {
    if (type.compare(NodeEventType::TRANSFORM_CHANGED) == 0) {
        _eventMask |= TRANSFORM_ON;
    }
    cc::NodeEventProcessor::on(type, callback, target, useCapture);
}

void BaseNode::off(const std::string &type, const std::function<void(BaseNode *)> &callback) {
    cc::NodeEventProcessor::off(type, callback);
    bool hasListeners = cc::NodeEventProcessor::hasEventListener(type);
    if (!hasListeners) {
        if (type.compare(NodeEventType::TRANSFORM_CHANGED)) {
            _eventMask &= ~TRANSFORM_ON;
        }
    }
}

void BaseNode::off(const std::string &type, const std::function<void(BaseNode *)> &callback, const std::any &target, bool useCapture) {
    cc::NodeEventProcessor::off(type, callback, target, useCapture);
    bool hasListeners = cc::NodeEventProcessor::hasEventListener(type);
    if (!hasListeners) {
        if (type.compare(NodeEventType::TRANSFORM_CHANGED)) {
            _eventMask &= ~TRANSFORM_ON;
        }
    }
}

void BaseNode::once(const std::string &type, const std::function<void(BaseNode *)> &callback) {
    cc::NodeEventProcessor::once(type, callback);
}

void BaseNode::once(const std::string &type, const std::function<void(BaseNode *)> &callback, const std::any &target, bool useCapture) {
    cc::NodeEventProcessor::once(type, callback, target, useCapture);
}
void BaseNode::emit(const std::string &type, const std::any &arg) {
    _eventProcessor->emit(type, arg);
}
void BaseNode::emit(const std::string &type, const std::any &arg1, const std::any &arg2, const std::any &arg3, const std::any &arg4) {
    _eventProcessor->emit(type, arg1, arg2, arg3, arg4);
}
void BaseNode::dispatchEvent(const event::Event &eve) {
    _eventProcessor->dispatchEvent(eve);
}

bool BaseNode::hasEventListener(const std::string &type) {
    return cc::NodeEventProcessor::hasEventListener(type);
}

bool BaseNode::hasEventListener(const std::string &type, const std::function<void(BaseNode *)> &callback) {
    return cc::NodeEventProcessor::hasEventListener(type, callback);
}

bool BaseNode::hasEventListener(const std::string &type, const std::function<void(BaseNode *)> &callback, const std::any &target) {
    return cc::NodeEventProcessor::hasEventListener(type, callback, target);
}

bool BaseNode::onPreDestroy() {
    return onPreDestroyBase();
}

void BaseNode::targetOff(const std::string &type) {
    _eventProcessor->targetOff(type);
    if ((_eventMask & TRANSFORM_ON) && !cc::NodeEventProcessor::hasEventListener(NodeEventType::TRANSFORM_CHANGED)) {
        _eventMask &= ~TRANSFORM_ON;
    }
}

void BaseNode::setActive(bool isActive) {
    if (_active != isActive) {
        _active          = isActive;
        BaseNode *parent = _parent;
        if (parent) {
            bool couldActiveInScene = parent->_activeInHierarchy;
            if (couldActiveInScene) {
                // TODO: Director not implemented
            }
        }
    }
}

void BaseNode::setParent(BaseNode *parent, bool isKeepWorld /* = false */) {
    if (_parent == parent) {
        return;
    }
    BaseNode *oldParent = _parent;
    BaseNode *newParent = parent;
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
            std::remove(oldParent->_children.begin(), oldParent->_children.end(), this);
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

void BaseNode::onHierarchyChanged(BaseNode *) {}

Scene *BaseNode::getScene() const {
    return _scene;
}

void BaseNode::walkInternal(std::function<void(BaseNode *)> preFunc, std::function<void(BaseNode *)> postFunc) {
    uint                    index{1};
    index_t                 i{0};
    std::vector<BaseNode *> children;
    BaseNode *              curr{nullptr};
    auto                    stacksCount = static_cast<uint>(BaseNode::stacks.size());
    if (stackId >= stacksCount) {
        stacks.resize(stackId + 1);
    }
    auto stack = stacks[stackId];
    stackId++;

    stack.clear();
    stack.resize(1);
    stack[0] = this;
    BaseNode *parent{nullptr};
    bool      afterChildren{false};
    while (index) {
        index--;
        auto stackCount = static_cast<uint>(stack.size());
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
            if (static_cast<int>(curr->_children.size()) > 0) {
                parent       = curr;
                children     = curr->_children;
                i            = 0;
                stack[index] = children[i];
                stack.resize(++index);
            } else {
                stack[index] = curr;
                stack.resize(++index);
                afterChildren = true;
            }
            continue;
        }
        auto childCount = static_cast<uint>(children.size());
        if (childCount > 0) {
            i++;
            if (i < childCount && children[i] != nullptr) {
                stack[index] = children[i];
                stack.resize(++index);
            } else if (parent) {
                stack[index] = parent;
                stack.resize(++index);
                afterChildren = true;
                if (parent->_parent != nullptr) {
                    children    = parent->_parent->_children;
                    index_t idx = getIdxOfChild(_children, parent);
                    if (idx != -1) {
                        i = idx;
                    }
                    parent = parent->_parent;
                } else {
                    // At root
                    parent = nullptr;
                    children.clear();
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

void BaseNode::walk() {
    walkInternal(nullptr, nullptr);
}

void BaseNode::walk(const std::function<void(BaseNode *)> &preFunc) {
    walkInternal(preFunc, nullptr);
}

void BaseNode::walk(const std::function<void(BaseNode *)> &preFunc, const std::function<void(BaseNode *)> &postFunc) {
    walkInternal(preFunc, postFunc);
}

Component *BaseNode::getComponent(const std::string &name) const {
    if (name.empty()) {
        return nullptr;
    }
    return findComponent(const_cast<BaseNode *>(this), name);
}

Component *BaseNode::getComponentInChildren(const std::string &name) const {
    if (name.empty()) {
        return nullptr;
    }
    return findChildComponent(_children, name);
}
std::vector<Component *> BaseNode::getComponentsInChildren(const std::string &name) const {
    if (name.empty()) {
        return _components;
    }
    return findChildComponents(_children, name, _components);
}

// TODO: How to add components based on the class name is not defined
Component *BaseNode::addComponent(const std::string & /*className*/) {
    return nullptr;
}

Component *BaseNode::addComponent(Component *comp) {
    auto iteComp = std::find(_components.begin(), _components.end(), comp);
    if (iteComp == _components.end()) {
        comp->_node = this; //cjh TODO: shared_ptr
        _components.emplace_back(comp);
        return comp;
    }
    return nullptr;
}
// TODO: How to remove components based on the class name is not defined
void BaseNode::removeComponent(const std::string &className) {}

void BaseNode::removeComponent(Component *comp) {
    auto iteComp = std::find(_components.begin(), _components.end(), comp);
    if (iteComp != _components.end()) {
        _components.erase(iteComp);
    }
}

bool BaseNode::onPreDestroyBase() {
    Flags destroyingFlag = Flags::DESTROYING;
    _objFlags |= destroyingFlag;
    bool destroyByParent = (!!_parent) && (!!(_parent->_objFlags & destroyingFlag));
    // TODO
    /*if (!destroyByParent && EDITOR) {
        this._registerIfAttached !(false);
    }*/
    if (_persistNode) {
        // TODO
        // legacyCC.game.removePersistRootNode(this);
    }
    if (!destroyByParent) {
        if (_parent) {
            emit(NodeEventType::PARENT_CHANGED, this);
            index_t childIdx = getIdxOfChild(_parent->_children, this);
            if (childIdx != -1) {
                std::remove(_parent->_children.begin(), _parent->_children.end(), this);
            }
            _siblingIndex = 0;
            _parent->updateSiblingIndex();
            _parent->emit(NodeEventType::CHILD_REMOVED, this);
        }
    }
    emit(NodeEventType::NODE_DESTROYED, this);
    _eventProcessor->destroy();
    for (auto *child : _children) {
        child->destroyImmediate();
    }
    for (auto *comp : _components) {
        // TODO(Lenovo): _destroyImmediate
        // comps[i]._destroyImmediate();
    }
    return destroyByParent;
}

void BaseNode::onSetParent(BaseNode *oldParent, bool /*keepWorldTransform*/) {
    if (_parent) {
        if ((oldParent == nullptr || oldParent->_scene != _parent->_scene) && _parent->_scene != nullptr) {
            walk(setScene);
        }
    }
}

BaseNode *BaseNode::getChildByName(const std::string &name) const {
    if (!name.empty()) {
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

void BaseNode::setScene(BaseNode *node) {
    node->updateScene();
}

index_t BaseNode::getIdxOfChild(const std::vector<BaseNode *> &child, BaseNode *target) {
    auto iteChild = std::find(child.begin(), child.end(), target);
    if (iteChild != child.end()) {
        return iteChild - child.begin();
    }
    return CC_INVALID_INDEX;
}

BaseNode *BaseNode::getChildByUuid(const std::string &uuid) const {
    if (!uuid.empty()) {
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

bool BaseNode::isChildOf(BaseNode *parent) {
    BaseNode *child = this;
    do {
        if (child == parent) {
            return true;
        }
        child = child->_parent;
    } while (child);
    return false;
}

void BaseNode::removeAllChildren() {
    for (auto *child : _children) {
        if (child) {
            child->setParent(nullptr);
        }
    }
    _children.clear();
}

void BaseNode::setSiblingIndex(index_t index) {
    if (!_parent) {
        return;
    }
    if (!!(_parent->_objFlags & Flags::DEACTIVATING)) {
        // TODO: errorID(3821);
        return;
    }
    std::vector<BaseNode *> &siblings = _parent->_children;
    index                             = index != -1 ? index : siblings.size() - 1;
    index_t oldIdx                    = getIdxOfChild(siblings, this);
    if (index != oldIdx) {
        std::remove(siblings.begin(), siblings.end(), this);
        if (index < siblings.size()) {
            siblings.insert(siblings.begin() + 2, 1, this);
        } else {
            siblings.emplace_back(this);
        }
        _parent->updateSiblingIndex();
        onSiblingIndexChanged(index);
    }
}

BaseNode *BaseNode::getChildByPath(const std::string &path) const {
    size_t                   start;
    size_t                   end = 0;
    std::vector<std::string> segments;
    auto *                   lastNode = const_cast<BaseNode *>(this);
    while ((start = path.find_first_not_of('/', end)) != std::string::npos) {
        end = path.find('/', start);
        segments.push_back(path.substr(start, end - start));
    }
    for (const std::string &segment : segments) {
        if (segment.empty()) {
            continue;
        }
        BaseNode *next{nullptr};
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

// TODO(Lenovo): How to get a Component by name internally has not been determined, so there is no implementation here
Component *BaseNode::findComponent(BaseNode * /*unused*/, const std::string & /*unused*/) {
    return nullptr;
}

Component *BaseNode::findComponents(BaseNode * /*unused*/, const std::string & /*unused*/, const std::vector<Component *> /*unused*/ &) {
    return nullptr;
}

Component *BaseNode::findChildComponent(const std::vector<BaseNode *> & /*unused*/, const std::string & /*unused*/) {
    return nullptr;
}

std::vector<Component *> BaseNode::findChildComponents(const std::vector<BaseNode *> & /*childs*/, const std::string & /*className*/, std::vector<Component *> comps) {
    return comps;
}

} // namespace cc
