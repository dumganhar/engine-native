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
#include "core/Game.h"
#include "core/data/Object.h"
#include "core/scene-graph/NodeEventProcessor.h"
#include "core/scene-graph/Scene.h"

namespace cc {
namespace scenegraph {
using components::Component;
const uint32_t BaseNode::TRANSFORM_ON{1 << 0};
const uint32_t BaseNode::DESTROYING{static_cast<uint32_t>(CCObject::Flags::DESTROYING)};
const uint32_t BaseNode::DEACTIVATING{static_cast<uint32_t>(CCObject::Flags::DEACTIVATING)};
const uint32_t BaseNode::DONT_DESTROY{static_cast<uint32_t>(CCObject::Flags::DONT_DESTROY)};
int32_t        BaseNode::stackId{0};

BaseNode::BaseNode(const std::string& name) : CCObject(name.c_str()) {
    if (name.empty()) {
        _name = "New Node";
        return;
    }
    _name = name;
}

void BaseNode::onBatchCreated(bool  /*dontChildPrefab*/) {
    if (_parent) {
        int32_t idx = getIdxOfChilds(_parent, this);
        if (idx != -1) {
            _siblingIndex = idx;
        }
    }
}

BaseNode* BaseNode::instantiate(BaseNode* cloned, bool isSyncedNode) {
    if (!cloned) {
        // clone
        return nullptr;
    }
    cloned->_parent = nullptr;
    cloned->onBatchCreated(isSyncedNode);
    return cloned;
}

void BaseNode::on(NodeEventType type, const std::function<void(BaseNode*)>& callback, const std::any& target, bool useCapture) {
    switch (type) {
        case NodeEventType::TRANSFORM_CHANGED:
            _eventMask |= TRANSFORM_ON;
            break;
        default:
            break;
    }
    _eventProcessor->on(type, callback, target, useCapture);
}

void BaseNode::off(NodeEventType type, const std::function<void(BaseNode*)>& callback, const std::any& target, bool useCapture) {
    _eventProcessor->off(type, callback, target, useCapture);
    bool hasListeners = _eventProcessor->hasEventListener(type);
    if (!hasListeners) {
        switch (type) {
            case NodeEventType::TRANSFORM_CHANGED:
                _eventMask &= ~TRANSFORM_ON;
                break;
            default:
                break;
        }
    }
}

void BaseNode::once(NodeEventType type, const std::function<void(BaseNode*)>& callback, const std::any& target, bool useCapture) {
    _eventProcessor->once(type, callback, target, useCapture);
}
void BaseNode::emit(NodeEventType type, const std::any& arg) {
    _eventProcessor->emit(type, arg, nullptr, nullptr, nullptr);
}
void BaseNode::emit(NodeEventType type, const std::any& arg1, const std::any& arg2, const std::any& arg3, const std::any& arg4) {
    _eventProcessor->emit(type, arg1, arg2, arg3, arg4);
}
void BaseNode::dispatchEvent(event::Event eve) {
    _eventProcessor->dispatchEvent(eve);
}
bool BaseNode::hasEventListener(NodeEventType type, const std::function<void(BaseNode*)>& callback, const std::any& target) {
    return _eventProcessor->hasEventListener(type, callback, target);
}
void BaseNode::targetOff(NodeEventType target) {
    _eventProcessor->targetOff(target);
    if ((_eventMask & TRANSFORM_ON) && !_eventProcessor->hasEventListener(NodeEventType::TRANSFORM_CHANGED)) {
        _eventMask &= ~TRANSFORM_ON;
    }
}

void BaseNode::setParent(BaseNode* parent, bool  /*isKeepWorld*/) {
    if (_parent == parent) {
        return;
    }
    if (_parent != nullptr) {
        _parent->removeChild(this);
    }
    _parent = parent;
    if (_parent) {
        _parent->addChild(this);
    }
}

Scene* BaseNode::getScene() const {
    return _scene;
}

void BaseNode::walk(const std::function<void(BaseNode*)>& preFunc, const std::function<void(BaseNode*)>& postFunc) {
    uint32_t               index{1};
    int32_t                i{0};
    std::vector<BaseNode*> children;
    BaseNode*              curr{nullptr};
    auto                   stacksCount = static_cast<uint32_t>(stacks.size());
    if (stackId >= stacksCount) {
        stacks.resize(stackId + 1);
    }
    auto stack = stacks[stackId];
    stackId++;

    stack.clear();
    stack.resize(1);
    stack[0] = this;
    BaseNode* parent{nullptr};
    bool      afterChildren{false};
    while (index) {
        index--;
        auto stackCount = static_cast<uint32_t>(stack.size());
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
        auto childCount = static_cast<uint32_t>(children.size());
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
                    int32_t idx = getIdxOfChilds(this, parent);
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

components::Component* BaseNode::getComponent(const std::string& name) const {
    if (name.empty()) {
        return nullptr;
    }
    return findComponent(const_cast<BaseNode*>(this), name);
}

components::Component* BaseNode::getComponentInChildren(const std::string& name) const {
    if (name.empty()) {
        return nullptr;
    }
    return findChildComponent(_children, name);
}
std::vector<components::Component*> BaseNode::getComponentsInChildren(const std::string& name) const {
    if (name.empty()) {
        return _components;
    }
    return findChildComponents(_children, name, _components);
}

Component* BaseNode::addComponent(const std::string&  /*className*/) {
    return nullptr;
}

Component* BaseNode::addComponent(Component* comp) {
    auto iteComp = std::find(_components.begin(), _components.end(), comp);
    if (iteComp == _components.end()) {
        _components.emplace_back(comp);
        return comp;
    }
    return nullptr;
}

void BaseNode::removeComponent(const std::string& className) {}

void BaseNode::removeComponent(Component* comp) {
    auto iteComp = std::find(_components.begin(), _components.end(), comp);
    if (iteComp != _components.end()) {
        _components.erase(iteComp);
    }
}

bool BaseNode::onPreDestroyBase() {
    auto destroyingFlag = DESTROYING;
    _objFlags |= destroyingFlag;
    bool destroyByParent = (!!_parent) && ((_parent->_objFlags & destroyingFlag) != 0);
    if (_persistNode) {
    }
    if (!destroyByParent) {
        if (_parent) {
            emit(NodeEventType::PARENT_CHANGED, this);
            int32_t childIdx = getIdxOfChilds(_parent, this);
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
    for (auto* child : _children) {
        child->destroyImmediate();
    }
    for (auto* comp : _components) {
        // TODO(Lenovo): _destroyImmediate
    }
    return destroyByParent;
}

void BaseNode::onSetParent(BaseNode* oldParent, bool  /*keepWorldTransform*/) {
    if (_parent) {
        if ((oldParent == nullptr || oldParent->_scene != _parent->_scene) && _parent->_scene != nullptr) {
            walk(setScene, nullptr);
        }
    }
}

BaseNode* BaseNode::getChildByName(const std::string& name) const {
    if (!name.empty()) {
        return nullptr;
    }
    for (auto* child : _children) {
        if (child->_name == name) {
            return child;
        }
    }
    return nullptr;
}

void BaseNode::setScene(BaseNode* node) {
    node->updateScene();
}

int32_t BaseNode::getIdxOfChilds(BaseNode* parent, BaseNode* target) {
    auto iteChild = std::find(parent->_children.begin(), parent->_children.end(), target);
    if (iteChild != parent->_children.end()) {
        return std::distance(std::begin(parent->_children), iteChild);
    }
    return -1;
}

BaseNode* BaseNode::getChildByUuid(const std::string& uuid) const {
    if (!uuid.empty()) {
        return nullptr;
    }
    for (auto* child : _children) {
        if (child->_id == uuid) {
            return child;
        }
    }
    return nullptr;
}

bool BaseNode::isChildOf(BaseNode* parent) {
    BaseNode* child = this;
    do {
        if (child == parent) {
            return true;
        }
        child = child->_parent;
    } while (child);
    return false;
}

void BaseNode::removeAllChildren() {
    for (auto* child : _children) {
        if (child) {
            child->setParent(nullptr);
        }
    }
    _children.resize(0);
}

BaseNode* BaseNode::getChildByPath(const std::string& path) const {
    size_t                   start;
    size_t                   end = 0;
    std::vector<std::string> segments;
    auto*                    lastNode = const_cast<BaseNode*>(this);
    while ((start = path.find_first_not_of('/', end)) != std::string::npos) {
        end = path.find('/', start);
        segments.push_back(path.substr(start, end - start));
    }
    for (const std::string& segment : segments) {
        if (segment.empty()) {
            continue;
        }
        BaseNode* next{nullptr};
        for (auto* child : lastNode->_children) {
            if (child->_name == segment) {
                next = child;
                break;
            }
        }
        lastNode = next;
    }
    return lastNode;
}

// TODO(Lenovo): Component内部如何通过名称获取组件还未确定，所以这里暂时没有实现
components::Component* BaseNode::findComponent(BaseNode* /*unused*/, const std::string& /*unused*/) {
    return nullptr;
}

components::Component* BaseNode::findComponents(BaseNode* /*unused*/, const std::string& /*unused*/, const std::vector<components::Component*> /*unused*/&) {
    return nullptr;
}

components::Component* BaseNode::findChildComponent(const std::vector<BaseNode*>& /*unused*/, const std::string& /*unused*/) {
    return nullptr;
}

std::vector<components::Component*> BaseNode::findChildComponents(const std::vector<BaseNode*>&  /*childs*/, const std::string&  /*className*/, std::vector<components::Component*> comps) {
    return comps;
}

} // namespace scenegraph
} // namespace cc
