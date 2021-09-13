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

#include "ComponentScheduler.h"

namespace cc {

// LifeCycleInvoker
LifeCycleInvoker::LifeCycleInvoker(std::function<void(std::vector<Component *>, float)> invokeFunc) : _invoke(std::move(invokeFunc)) {}

void LifeCycleInvoker::stableRemoveInactive(const std::vector<Component *> &components, uint flagToClear) {
}

LifeCycleInvoker::~LifeCycleInvoker() = default;

// OneOffInvoker
void OneOffInvoker::add(Component *comp) {}

void OneOffInvoker::remove(Component *comp) {}

void OneOffInvoker::cancelInactive(uint flagToClear) {}

void OneOffInvoker::invoke() {}

// ReusableInvoker
void ReusableInvoker::add(Component *comp) {}

void ReusableInvoker::remove(Component *comp) {}

void ReusableInvoker::invoke(float dt) {}

// ComponentScheduler
ComponentScheduler::ComponentScheduler() {
    unscheduleAll();
}

ComponentScheduler::~ComponentScheduler() = default;

void ComponentScheduler::unscheduleAll(){};
void ComponentScheduler::onEnabled(Component *comp){};
void ComponentScheduler::onDisabled(Component *comp){};
void ComponentScheduler::enableComp(Component *comp, LifeCycleInvoker *invoke){};
void ComponentScheduler::disableComp(Component *comp){};
void ComponentScheduler::startPhase(){};
void ComponentScheduler::updatePhase(float dt){};
void ComponentScheduler::lateUpdatePhase(float dt){};
void ComponentScheduler::startForNewComps(){};
void ComponentScheduler::scheduleImmediate(Component *comp){};
void ComponentScheduler::deferredSchedule(){};

} // namespace cc
