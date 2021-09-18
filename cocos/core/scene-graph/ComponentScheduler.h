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

namespace cc {

using Invoker = std::function<void(const std::vector<Component *> &, std::optional<float>)>;
class LifeCycleInvoker {
public:
    static void    stableRemoveInactive(std::vector<Component *> &components);
    static void    stableRemoveInactive(std::vector<Component *> &components, CCObject::Flags flagToClear);
    static Invoker invokeStart();
    static Invoker invokeUpdate();
    static Invoker invokeLateUpdate();

    static int32_t sortedIndex(std::vector<Component *> &components, Component *comp);
    explicit LifeCycleInvoker(Invoker invokeFunc);
    ~LifeCycleInvoker();

protected:
    Invoker _invoke;

    std::vector<Component *> _zero;
    std::vector<Component *> _neg;
    std::vector<Component *> _pos;

private:
};

class OneOffInvoker : LifeCycleInvoker {
public:
    using LifeCycleInvoker::LifeCycleInvoker;
    void add(Component *comp);
    void remove(Component *comp);
    void cancelInactive(CCObject::Flags flagToClear);
    void invoke();
};

class ReusableInvoker : LifeCycleInvoker {
public:
    using LifeCycleInvoker::LifeCycleInvoker;
    void add(Component *comp);
    void remove(Component *comp);
    void invoke(float);
};

class ComponentScheduler final {
public:
    ComponentScheduler();
    ~ComponentScheduler();
    OneOffInvoker *  startInvoker;
    ReusableInvoker *updateInvoker;
    ReusableInvoker *lateUpdateInvoker;
    void             unscheduleAll();
    void             onEnabled(Component *comp);
    void             onDisabled(Component *comp);
    void             enableComp(Component *comp, std::optional<LifeCycleInvoker *> invoker = std::nullopt);
    void             disableComp(Component *comp);
    void             startPhase();
    void             updatePhase(float) const;
    void             lateUpdatePhase(float);

private:
    std::vector<Component *> _deferredComps;
    bool                     _updating{true};
    void                     startForNewComps();
    void                     scheduleImmediate(Component *comp);
    void                     deferredSchedule();
};

} // namespace cc
