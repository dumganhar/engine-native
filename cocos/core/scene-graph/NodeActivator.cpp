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

namespace {

const cc::CCObject::Flags IS_PRELOAD_STARTED = cc::CCObject::Flags::IS_PRELOAD_STARTED;
const cc::CCObject::Flags IS_ON_LOAD_STARTED  = cc::CCObject::Flags::IS_ON_LOAD_STARTED;
const cc::CCObject::Flags IS_ON_LOAD_CALLED   = cc::CCObject::Flags::IS_ON_LOAD_CALLED;
const cc::CCObject::Flags DEACTIVATING     = cc::CCObject::Flags::DEACTIVATING;

void componentCorrupted(cc::Node *node, cc::Component *comp, uint32_t index) {
    // TODO(xwx): DEV & array & debug not implemented
    // if (DEV) {
    //     errorID(3817, node->getName(), index);
    //     console.log('Corrupted component value:', comp);
    // }
    // if (comp) {
    //     node->removeComponent(comp);
    // } else {
    //     array.removeAt(node._components, index);
    // }
}

} // namespace

namespace cc {

NodeActivator::NodeActivator() {
    reset();
}

void NodeActivator::activateNode(Node *node, bool active) {
    // TODO(xwx): activateTasksPool not implemented
    if (active) {
        // const task : any = activateTasksPool.get();
        // _activatingStack.emplace_back(task);

        // activateNodeRecursively(node, task.preload, task.onLoad, task.onEnable);
        // task.preload.invoke();
        // task.onLoad.invoke();
        // task.onEnable.invoke();

        // _activatingStack.pop_back();
        // activateTasksPool.put(task);
    } else {
        deactivateNodeRecursively(node);

        // remove children of this node from previous activating tasks to debounce
        // (this is an inefficient operation but it ensures general case could be implemented in a efficient way)
        for (const auto &lastTask : _activatingStack) {
            // lastTask.preload.cancelInactive(IsPreloadStarted);
            // lastTask.onLoad.cancelInactive(IsOnLoadStarted);
            // lastTask.onEnable.cancelInactive();
        }
    }

    node->emit("active-in-hierarchy-changed", node);
}

void NodeActivator::activateComp(Component *comp, LifeCycleInvoker *preloadInvoker, LifeCycleInvoker *onLoadInvoker, LifeCycleInvoker *onEnableInvoker) {
    // if (!isValid(comp, true)) { // TODO(xwx): isValid not implemented
    //     // destroyed before activating
    //     return;
    // }
    if (!(comp->_objFlags & IS_PRELOAD_STARTED)) {
        comp->_objFlags |= IS_PRELOAD_STARTED;
        // if (comp.__preload) { // TODO(xwx):__preload is prototype attribute in ts
        //     if (preloadInvoker) {
        //         preloadInvoker->add(comp);
        //     } else {
        //         comp->__preload();
        //     }
        // }
    }
    if (!(comp->_objFlags & IS_ON_LOAD_STARTED)) {
        comp->_objFlags |= IS_ON_LOAD_STARTED;
        //     if (comp.onLoad) { // TODO(xwx):onLoad is prototype attribute in ts
        //         if (onLoadInvoker) {
        //             onLoadInvoker->add(comp);
        //         } else {
        //             comp->onLoad();
        //             comp->_objFlags |= IsOnLoadCalled;
        //         }
        //     } else {
        //         comp->_objFlags |= IsOnLoadCalled;
        //     }
        // }
        if (comp->_enabled) {
            bool deactivatedOnLoading = !comp->getNode()->isActiveInHierarchy();
            if (deactivatedOnLoading) {
                return;
            }
            // Director::getInstance()._compScheduler->enableComp(comp, onEnableInvoker); //TODO(xwx): not sure Director will be used
        }
    }
}

void NodeActivator::destroyComp(Component *comp) {
    // ensure onDisable called
    // Director::getInstance()._compScheduler->disableComp(comp);  //TODO(xwx): not sure Director will be used
    // if (comp->onDestroy && (comp->_objFlags & IsOnLoadCalled)) {  //TODO(xwx): comp->onDestroy not define
    //     comp->onDestroy();
    // }
}

void NodeActivator::activateNodeRecursively(Node *node, LifeCycleInvoker *preloadInvoker, LifeCycleInvoker *onLoadInvoker, LifeCycleInvoker *onEnableInvoker) {
    if (hasFlag(node->_objFlags, DEACTIVATING)) {
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
        // if (component instanceof legacyCC.Component) {
        //     activateComp(component, preloadInvoker, onLoadInvoker, onEnableInvoker);
        // } else {
        //     componentCorrupted(node, component, i);
        //     --i;
        //     --originCount;
        // }
        activateComp(component, preloadInvoker, onLoadInvoker, onEnableInvoker);
    }
    // node->_childArrivalOrder = node->_children.size(); //TODO(xwx): not declare _childArrivalOrder attribute in c++, seems could remove this line
    // activate children recursively
    for (auto *child : node->_children) {
        if (child->_active) {
            activateNodeRecursively(dynamic_cast<Node *>(child), preloadInvoker, onLoadInvoker, onEnableInvoker); // TODO(xwx): not sure child should be Node or BaseNode
        }
    }
    node->onPostActivated(true);
}

void NodeActivator::deactivateNodeRecursively(Node *node) {
    // if (DEV) { // TODO(xwx): DEV is not defined
    //     CCASSERT(!(node._objFlags & Deactivating), "node should not deactivating");
    //     // ensures _activeInHierarchy is always changing when Deactivating flagged
    //     CCASSERT(node._activeInHierarchy, "node should not deactivated");
    // }
    node->_objFlags |= DEACTIVATING;
    node->_activeInHierarchy = false;

    // component maybe added during onEnable, and the onEnable of new component is already called
    // so we should record the origin length
    for (auto *component : node->_components) {
        if (component->_enabled) {
            // Director::getInstance()._compScheduler.disableComp(component); //TODO(xwx): not sure Director will be used

            if (node->_activeInHierarchy) {
                // reactivated from root
                node->_objFlags &= ~DEACTIVATING;
                return;
            }
        }
    }
    for (auto *child : node->_children) {
        if (child->_activeInHierarchy) {
            deactivateNodeRecursively(dynamic_cast<Node *>(child)); // TODO(xwx): not sure child should be Node or BaseNode

            if (node->_activeInHierarchy) {
                // reactivated from root
                node->_objFlags &= ~DEACTIVATING;
                return;
            }
        }
    }

    node->onPostActivated(false);
    node->_objFlags &= ~DEACTIVATING;
}

} // namespace cc

