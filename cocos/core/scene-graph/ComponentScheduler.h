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
#include <functional>
#include <vector>
#include "base/TypeDef.h"
#include "core/components/Component.h"
#include "core/scene-graph/Node.h"
#include "core/utils/MutableForwardIterator.h"

namespace cc {

using Invoker = std::function<void(MutableForwardIterator<Component *> &, const std::optional<float> &)>;

using SingleInvokeCallback = std::function<void(Component *, const std::optional<float> &)>;
using FastPathCallback     = Invoker;

Invoker createInvokeImpl(const SingleInvokeCallback &singleInvoke, const FastPathCallback &fastPath, std::optional<CCObject::Flags> ensureFlag);

class LifeCycleInvoker {
public:
    // remove disabled and not invoked component from array
    static void stableRemoveInactive(MutableForwardIterator<Component *> &iterator, const std::optional<CCObject::Flags> &flagToClear);

    static Invoker invokeStart();
    static Invoker invokeUpdate();
    static Invoker invokeLateUpdate();

    static int32_t sortedIndex(std::vector<Component *> &components, Component *comp);

    explicit LifeCycleInvoker(const Invoker &invokeFunc);
    ~LifeCycleInvoker();

    virtual void add(Component *comp)    = 0;
    virtual void remove(Component *comp) = 0;

protected:
    Invoker _invoke{nullptr};

    std::vector<Component *> _zeroCompArr;
    std::vector<Component *> _negCompArr;
    std::vector<Component *> _posCompArr;

public:
    MutableForwardIterator<Component *> _zero;
    MutableForwardIterator<Component *> _neg;
    MutableForwardIterator<Component *> _pos;
};

// for onLoad: sort once all components registered, invoke once
class OneOffInvoker final : public LifeCycleInvoker {
public:
    using LifeCycleInvoker::LifeCycleInvoker;
    void add(Component *comp) override;
    void remove(Component *comp) override;
    void cancelInactive();
    void cancelInactive(CCObject::Flags flagToClear);
    void invoke();
};

// for update: sort every time new component registered, invoke many times
class ReusableInvoker final : public LifeCycleInvoker {
public:
    using LifeCycleInvoker::LifeCycleInvoker;
    void add(Component *comp) override;
    void remove(Component *comp) override;
    void invoke(float dt);
};

/**
 * @en The Manager for Component's life-cycle methods.
 * It collaborates with [[NodeActivator]] to schedule and invoke life cycle methods for components
 * @zh 组件生命周期函数的调度器。
 * 它和 [[NodeActivator]] 一起调度并执行组件的生命周期函数。
 */
class ComponentScheduler final {
public:
    ComponentScheduler();
    ~ComponentScheduler();

    void unscheduleAll();
    void onEnabled(Component *comp);
    void onDisabled(Component *comp);

    /**
     * @en Enable a component
     * @zh 启用一个组件
     * @param comp The component to be enabled
     * @param invoker The invoker which is responsible to schedule the `onEnable` call
     */
    void enableComp(Component *comp, std::optional<LifeCycleInvoker *> invoker = std::nullopt);

    /**
     * @en Disable a component
     * @zh 禁用一个组件
     * @param comp The component to be disabled
     */
    void disableComp(Component *comp);

    /**
     * @en Process start phase for registered components
     * @zh 为当前注册的组件执行 start 阶段任务
     */
    void startPhase();

    /**
     * @en Process update phase for registered components
     * @zh 为当前注册的组件执行 update 阶段任务
     * @param dt 距离上一帧的时间
     */
    void updatePhase(float) const;

    /**
     * @en Process late update phase for registered components
     * @zh 为当前注册的组件执行 late update 阶段任务
     * @param dt 距离上一帧的时间
     */
    void lateUpdatePhase(float);

private:
    void startForNewComps();
    void scheduleImmediate(Component *comp);
    void deferredSchedule();

    /**
     * @en The invoker of `start` callback
     * @zh `start` 回调的调度器
     */
    OneOffInvoker *_startInvoker{nullptr};

    /**
     * @en The invoker of `update` callback
     * @zh `update` 回调的调度器
     */
    ReusableInvoker *_updateInvoker{nullptr};

    /**
     * @en The invoker of `lateUpdate` callback
     * @zh `lateUpdate` 回调的调度器
     */
    ReusableInvoker *_lateUpdateInvoker{nullptr};

    // components deferred to schedule
    std::vector<Component *> _deferredComps;

    bool _updating{false};
};

} // namespace cc
