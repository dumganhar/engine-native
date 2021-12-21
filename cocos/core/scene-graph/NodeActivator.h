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

#include <memory>
#include <vector>

#include "core/scene-graph/ComponentScheduler.h"
#include "core/scene-graph/Node.h"
#include "core/utils/Pool.h"

namespace cc {

class UnsortedInvoker;
class OneOffInvoker;

class NodeActivator final {
public:
    NodeActivator();
    ~NodeActivator() = default;

    /**
     * @en Reset all activation or des-activation tasks
     * @zh 重置所有激活或非激活任务
     */
    inline void reset() {
        _activatingStack.clear();
    }

    /**
     * @en Activate or des-activate a node
     * @zh 激活或者停用某个节点
     * @param node Target node
     * @param active Which state to set the node to
     */
    void activateNode(Node *node, bool active);

    /**
     * @en Activate or des-activate a component
     * @zh 激活或者停用某个组件
     * @param comp Target component
     * @param preloadInvoker The invoker for `_preload` method, normally from [[ComponentScheduler]]
     * @param onLoadInvoker The invoker for `onLoad` method, normally from [[ComponentScheduler]]
     * @param onEnableInvoker The invoker for `onEnable` method, normally from [[ComponentScheduler]]
     */
    static void activateComp(Component *comp, LifeCycleInvoker *preloadInvoker = nullptr, LifeCycleInvoker *onLoadInvoker = nullptr, LifeCycleInvoker *onEnableInvoker = nullptr);

    /**
     * @en Destroy a component
     * @zh 销毁一个组件
     * @param comp Target component
     */
    static void destroyComp(Component *comp);

    Component *_resetComp{nullptr};

    class Task;

protected:
    void activateNodeRecursively(Node *node, LifeCycleInvoker *preloadInvoker = nullptr, LifeCycleInvoker *onLoadInvoker = nullptr, LifeCycleInvoker *onEnableInvoker = nullptr);

    void deactivateNodeRecursively(Node *node);

    std::vector<std::shared_ptr<Task>> _activatingStack;

private:
    CC_DISALLOW_COPY_MOVE_ASSIGN(NodeActivator);
};

} // namespace cc
