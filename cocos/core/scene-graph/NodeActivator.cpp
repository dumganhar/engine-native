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
#include "core/scene-graph/NodeActivator.h"
#include "base/TypeDef.h"
#include "base/Utils.h"
#include "core/Director.h"
#include "core/scene-graph/ComponentScheduler.h"

namespace cc {

void componentCorrupted(Node *node, Component *comp, uint32_t index) {
    // TODO(xwx): DEV & array & debug not implemented
    // if (DEV) {
    //     errorID(3817, node->getName(), index);
    //     console.log('Corrupted component value:', comp);
    // }
    if (comp) {
        node->removeComponent(comp);
    } else {
        utils::array::removeAt(node->_components, index);
    }
}

class UnsortedInvoker final : public LifeCycleInvoker {
public:
    using LifeCycleInvoker::LifeCycleInvoker;

    void add(Component *comp) override {
        _zero.array.emplace_back(comp);
    }

    void remove(Component *comp) override {
        _zero.fastRemove(comp);
    }

    inline void cancelInactive() {
        stableRemoveInactive(_zero, std::nullopt);
    }

    inline void cancelInactive(CCObject::Flags flagToClear) {
        stableRemoveInactive(_zero, flagToClear);
    }

    inline void invoke() {
        _invoke(_zero, std::nullopt);
        _zero.array.clear();
    }
};

class NodeActivator::Task final {
public:
    Task() = default;
    ~Task();

    std::unique_ptr<UnsortedInvoker> preload;
    std::unique_ptr<OneOffInvoker>   onLoad;
    std::unique_ptr<OneOffInvoker>   onEnable;
};

NodeActivator::Task::~Task() = default;

namespace {

constexpr int32_t MAX_POOL_SIZE = 4;

Invoker invokePreload = createInvokeImpl(
    [](Component *c, const std::optional<float> &dt) {
        c->__preload();
    },
    [](MutableForwardIterator<Component *> &iterator, const std::optional<float> &dt) {
        auto &array = iterator.array;
        for (iterator.i = 0; iterator.i < static_cast<int32_t>(array.size()); ++iterator.i) {
            array[iterator.i]->__preload();
        }
    },
    std::nullopt);

Invoker invokeOnLoad = createInvokeImpl(
    [](Component *c, const std::optional<float> &dt) {
        c->onLoad();
        c->_objFlags |= CCObject::Flags::IS_ON_LOAD_CALLED;
    },
    [](MutableForwardIterator<Component *> &iterator, const std::optional<float> &dt) {
        auto &array = iterator.array;
        for (iterator.i = 0; iterator.i < array.size(); ++iterator.i) {
            auto *comp = array[iterator.i];
            comp->onLoad();
            comp->_objFlags |= CCObject::Flags::IS_ON_LOAD_CALLED;
        }
    },
    CCObject::Flags::IS_ON_LOAD_CALLED);

Invoker invokeOnEnable = [](MutableForwardIterator<Component *> &iterator, const std::optional<float> &dt) {
    auto *compScheduler = Director::getInstance()->getCompScheduler();
    auto &array         = iterator.array;
    for (iterator.i = 0; iterator.i < static_cast<int32_t>(array.size()); ++iterator.i) {
        auto *comp = array[iterator.i];
        if (comp->isEnabled()) {
            comp->onEnable();
            bool deactivatedDuringOnEnable = !comp->getNode()->isActiveInHierarchy();
            if (!deactivatedDuringOnEnable) {
                compScheduler->onEnabled(comp);
            }
        }
    }
};

Pool<std::shared_ptr<NodeActivator::Task>> activateTasksPool{MAX_POOL_SIZE}; //cjh how to release it?

} // namespace
//

NodeActivator::NodeActivator() {
    reset();
    if (activateTasksPool.get == nullptr) {
        activateTasksPool.get = [&]() -> std::shared_ptr<NodeActivator::Task> {
            auto task = activateTasksPool._get();
            if (task == nullptr) {
                task           = std::make_shared<NodeActivator::Task>();
                task->preload  = std::make_unique<UnsortedInvoker>(invokePreload);
                task->onLoad   = std::make_unique<OneOffInvoker>(invokeOnLoad);
                task->onEnable = std::make_unique<OneOffInvoker>(invokeOnEnable);
            }

            // reset index to -1 so we can skip invoked component in cancelInactive
            task->preload->_zero.i = -1;

            {
                auto &invoker    = task->onLoad;
                invoker->_zero.i = -1;
                invoker->_neg.i  = -1;
                invoker->_pos.i  = -1;
            }

            {
                auto &invoker    = task->onEnable;
                invoker->_zero.i = -1;
                invoker->_neg.i  = -1;
                invoker->_pos.i  = -1;
            }

            return task;
        };
    }
}

void NodeActivator::activateNode(BaseNode *node, bool active) {
    if (active) {
        auto task = activateTasksPool.get();
        _activatingStack.emplace_back(task);

        activateNodeRecursively(node, task->preload.get(), task->onLoad.get(), task->onEnable.get());

        task->preload->invoke();
        task->onLoad->invoke();
        task->onEnable->invoke();

        _activatingStack.pop_back();
        activateTasksPool.put(task);
    } else {
        deactivateNodeRecursively(node);

        // remove children of this node from previous activating tasks to debounce
        // (this is an inefficient operation but it ensures general case could be implemented in a efficient way)
        for (const auto &lastTask : _activatingStack) {
            lastTask->preload->cancelInactive(CCObject::Flags::IS_PRELOAD_STARTED);
            lastTask->onLoad->cancelInactive(CCObject::Flags::IS_ON_LOAD_STARTED);
            lastTask->onEnable->cancelInactive();
        }
    }

    node->emit("active-in-hierarchy-changed", node);
}

void NodeActivator::activateComp(Component *comp, LifeCycleInvoker *preloadInvoker, LifeCycleInvoker *onLoadInvoker, LifeCycleInvoker *onEnableInvoker) {
    if (!isObjectValid(comp, true)) { // TODO(xwx): isValid not implemented
        // destroyed before activating
        return;
    }
    if (!(comp->_objFlags & CCObject::Flags::IS_PRELOAD_STARTED)) {
        comp->_objFlags |= CCObject::Flags::IS_PRELOAD_STARTED;
        if (preloadInvoker != nullptr) {
            preloadInvoker->add(comp);
        } else {
            comp->__preload();
        }
    }
    if (!(comp->_objFlags & CCObject::Flags::IS_ON_LOAD_STARTED)) {
        comp->_objFlags |= CCObject::Flags::IS_ON_LOAD_STARTED;
        //        if (comp.onLoad) { // TODO(xwx):onLoad is prototype attribute in ts
        if (onLoadInvoker != nullptr) {
            onLoadInvoker->add(comp);
        } else {
            comp->onLoad();
            comp->_objFlags |= CCObject::Flags::IS_ON_LOAD_CALLED;
        }
        //        } else {
        //            comp->_objFlags |= CCObject::Flags::IS_ON_LOAD_CALLED;
        //        }
    }

    if (comp->isEnabled()) {
        bool deactivatedOnLoading = !comp->getNode()->isActiveInHierarchy();
        if (deactivatedOnLoading) {
            return;
        }
        Director::getInstance()->getCompScheduler()->enableComp(comp, onEnableInvoker);
    }
}

void NodeActivator::destroyComp(Component *comp) {
    // ensure onDisable called
    Director::getInstance()->getCompScheduler()->disableComp(comp);
    if (!!(comp->_objFlags & CCObject::Flags::IS_ON_LOAD_CALLED)) {
        comp->onDestroy();
    }
}

void NodeActivator::activateNodeRecursively(BaseNode *node, LifeCycleInvoker *preloadInvoker, LifeCycleInvoker *onLoadInvoker, LifeCycleInvoker *onEnableInvoker) {
    if (hasFlag(node->_objFlags, CCObject::Flags::DEACTIVATING)) {
        // en:
        // Forbid reactive the same node during its deactivating procedure
        // to avoid endless loop and simplify the implementation.
        // zh:
        // 对相同节点而言，无法撤销反激活，防止反激活 - 激活 - 反激活的死循环发生。
        // 这样设计简化了一些引擎的实现，而且对调用者来说能保证反激活操作都能成功。
        // errorID(3816, node.name); //TODO(xwx): errorID not implemented
        return;
    }

    node->_activeInHierarchy = true;

    // component maybe added during onEnable, and the onEnable of new component is already called
    // so we should record the origin length
    uint32_t originCount = node->_components.size();
    // activate components
    for (uint32_t i = 0; i < originCount; ++i) {
        Component *component = node->_components[i];
        // TODO(xwx): logical difference between ts and cpp, may need adjust
        //        if (component instanceof legacyCC.Component) {
        activateComp(component, preloadInvoker, onLoadInvoker, onEnableInvoker);
        //        } else {
        //            componentCorrupted(node, component, i);
        //            --i;
        //            --originCount;
        //        }
    }
    //    node->_childArrivalOrder = node->_children.size(); //TODO(xwx): not declare _childArrivalOrder attribute in c++, seems could remove this line
    // activate children recursively
    for (auto *child : node->_children) {
        if (child->_active) {
            activateNodeRecursively(child, preloadInvoker, onLoadInvoker, onEnableInvoker); // TODO(xwx): not sure child should be Node or BaseNode
        }
    }
    node->onPostActivated(true);
}

void NodeActivator::deactivateNodeRecursively(BaseNode *node) {
    // if (DEV) { // TODO(xwx): DEV is not defined
    //     CCASSERT(!(node._objFlags & Deactivating), "node should not deactivating");
    //     // ensures _activeInHierarchy is always changing when Deactivating flagged
    //     CCASSERT(node._activeInHierarchy, "node should not deactivated");
    // }
    node->_objFlags |= CCObject::Flags::DEACTIVATING;
    node->_activeInHierarchy = false;

    // component maybe added during onEnable, and the onEnable of new component is already called
    // so we should record the origin length
    for (auto *component : node->_components) {
        if (component->_enabled) {
            Director::getInstance()->getCompScheduler()->disableComp(component);

            if (node->_activeInHierarchy) {
                // reactivated from root
                node->_objFlags &= ~CCObject::Flags::DEACTIVATING;
                return;
            }
        }
    }
    for (auto *child : node->_children) {
        if (child->_activeInHierarchy) {
            deactivateNodeRecursively(dynamic_cast<Node *>(child)); // TODO(xwx): not sure child should be Node or BaseNode

            if (node->_activeInHierarchy) {
                // reactivated from root
                node->_objFlags &= ~CCObject::Flags::DEACTIVATING;
                return;
            }
        }
    }

    node->onPostActivated(false);
    node->_objFlags &= ~CCObject::Flags::DEACTIVATING;
}

} // namespace cc
