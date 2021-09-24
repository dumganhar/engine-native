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

#include "core/scene-graph/ComponentScheduler.h"

#include <utility>

#include "base/Utils.h"

namespace cc {

namespace {

Invoker invokeStart = createInvokeImpl(
    [](Component *c, const std::optional<float> &dt) {
        c->start();
        c->_objFlags |= CCObject::Flags::IS_START_CALLED;
    },
    [](MutableForwardIterator<Component *> &iterator, const std::optional<float> &dt) {
        auto &array = iterator.array;
        for (iterator.i = 0; iterator.i < static_cast<int32_t>(array.size()); ++iterator.i) {
            Component *comp = array[iterator.i];
            comp->start();
            comp->_objFlags |= CCObject::Flags::IS_START_CALLED;
        }
    },
    CCObject::Flags::IS_START_CALLED);

Invoker invokeUpdate = createInvokeImpl(
    [](Component *c, const std::optional<float> &dt) {
        c->update(dt.value());
    },
    [](MutableForwardIterator<Component *> &iterator, const std::optional<float> &dt) {
        auto &array = iterator.array;
        for (iterator.i = 0; iterator.i < static_cast<int32_t>(array.size()); ++iterator.i) {
            Component *comp = array[iterator.i];
            comp->update(dt.value());
        }
    },
    std::nullopt);

Invoker invokeLateUpdate = createInvokeImpl(
    [](Component *c, const std::optional<float> &dt) {
        c->lateUpdate(dt.value());
    },
    [](MutableForwardIterator<Component *> &iterator, const std::optional<float> &dt) {
        auto &array = iterator.array;
        for (iterator.i = 0; iterator.i < static_cast<int32_t>(array.size()); ++iterator.i) {
            Component *comp = array[iterator.i];
            comp->lateUpdate(dt.value());
        }
    },
    std::nullopt);

} // namespace

Invoker createInvokeImpl(const SingleInvokeCallback &singleInvoke, const FastPathCallback &fastPath, std::optional<CCObject::Flags> ensureFlag) {
    return [=](MutableForwardIterator<Component *> iterator, const std::optional<float> &dt) {
        //TODO: cjh We don't wanna use c++ exception here, so just invoke fastPath.
        fastPath(iterator, dt);
    };
}

// LifeCycleInvoker
LifeCycleInvoker::LifeCycleInvoker(const Invoker &invokeFunc)
: _invoke(invokeFunc), _zero(_zeroCompArr), _neg(_negCompArr), _pos(_posCompArr) {
}

void LifeCycleInvoker::stableRemoveInactive(MutableForwardIterator<Component *> &iterator, const std::optional<CCObject::Flags> &flagToClear) {
    auto &  array = iterator.array;
    int32_t next  = iterator.i + 1;
    while (next < static_cast<int32_t>(array.size())) {
        auto *comp = array[next];
        if (comp->getNode()->isActiveInHierarchy()) {
            ++next;
        } else {
            iterator.removeAt(next);
            if (flagToClear.has_value()) {
                comp->_objFlags &= ~flagToClear.value();
            }
        }
    }
}

int32_t LifeCycleInvoker::sortedIndex(std::vector<Component *> &components, Component *comp) {
    const int32_t      order = comp->getExecutionOrder();
    const std::string &id    = comp->getUuid();
    int32_t            l     = 0;
    for (int32_t h = components.size() - 1, m = static_cast<uint32_t>(h) >> 1; l <= h; m = static_cast<uint32_t>(l + h) >> 1) {
        auto *        test      = components[m];
        const int32_t testOrder = test->getExecutionOrder();
        if (testOrder > order) {
            h = m - 1;
        } else if (testOrder < order) {
            l = m + 1;
        } else {
            const std::string &testId = test->getUuid();
            if (testId > id) {
                h = m - 1;
            } else if (testId < id) {
                l = m + 1;
            } else {
                return m;
            }
        }
    }
    return ~l;
}

LifeCycleInvoker::~LifeCycleInvoker() = default;

// OneOffInvoker
void OneOffInvoker::add(Component *comp) {
    const int32_t order = comp->getExecutionOrder();
    if (order > 0) {
        _pos.array.emplace_back(comp);
    } else if (order < 0) {
        _neg.array.emplace_back(comp);
    } else {
        _zero.array.emplace_back(comp);
    }
}

void OneOffInvoker::remove(Component *comp) {
    const int32_t order = comp->getExecutionOrder();
    if (order > 0) {
        _pos.fastRemove(comp);
    } else if (order < 0) {
        _neg.fastRemove(comp);
    } else {
        _zero.fastRemove(comp);
    }
}

void OneOffInvoker::cancelInactive(CCObject::Flags flagToClear) {
    stableRemoveInactive(_zero, flagToClear);
    stableRemoveInactive(_neg, flagToClear);
    stableRemoveInactive(_pos, flagToClear);
}

void OneOffInvoker::invoke() {
    if (!_neg.array.empty()) {
        std::stable_sort(_neg.array.begin(), _neg.array.end(), [](const Component *a, const Component *b) {
            return a->getExecutionOrder() < b->getExecutionOrder();
        });

        _invoke(_neg, std::nullopt);
        _neg.array.clear();
    }
    _invoke(_zero, std::nullopt);
    _zero.array.clear();

    if (!_pos.array.empty()) {
        std::stable_sort(_pos.array.begin(), _pos.array.end(), [](const Component *a, const Component *b) {
            return a->getExecutionOrder() < b->getExecutionOrder();
        });
        _invoke(_pos, std::nullopt);
        _pos.array.clear();
    }
}

// ReusableInvoker
void ReusableInvoker::add(Component *comp) {
    const int32_t order = comp->getExecutionOrder();
    if (order == 0) {
        _zero.array.emplace_back(comp);
    } else {
        auto &        array = order < 0 ? _neg.array : _pos.array;
        const int32_t i     = sortedIndex(array, comp);
        if (i < 0) {
            array.insert(array.begin() + (~i), comp);
        }
        // else if (DEV) { //TODO(xwx): no DEV now
        // //     error('component already added');
        // }
    }
}

void ReusableInvoker::remove(Component *comp) {
    const int32_t order = comp->getExecutionOrder();
    if (order == 0) {
        _zero.fastRemove(comp);
    } else {
        auto &        iterator = order < 0 ? _neg : _pos;
        const int32_t i        = sortedIndex(iterator.array, comp);
        if (i >= 0) {
            iterator.removeAt(i);
        }
    }
}

void ReusableInvoker::invoke(float dt) {
    if (!_neg.array.empty()) {
        _invoke(_neg, dt);
    }

    _invoke(_zero, dt);

    if (!_pos.array.empty()) {
        _invoke(_pos, dt);
    }
}

// ComponentScheduler
ComponentScheduler::ComponentScheduler() {
    unscheduleAll();
}

ComponentScheduler::~ComponentScheduler() {
    CC_SAFE_DELETE(_startInvoker);
    CC_SAFE_DELETE(_updateInvoker);
    CC_SAFE_DELETE(_lateUpdateInvoker);
}

void ComponentScheduler::unscheduleAll() {
    CC_SAFE_DELETE(_startInvoker);
    CC_SAFE_DELETE(_updateInvoker);
    CC_SAFE_DELETE(_lateUpdateInvoker);

    _startInvoker      = new OneOffInvoker(invokeStart);
    _updateInvoker     = new ReusableInvoker(invokeUpdate);
    _lateUpdateInvoker = new ReusableInvoker(invokeLateUpdate);

    // during a loop
    _updating = false;
}

void ComponentScheduler::onEnabled(Component *comp) {
    // legacyCC.director.getScheduler().resumeTarget(comp); //TODO(xwx): not sure use Director
    comp->_objFlags |= CCObject::Flags::IS_ON_ENABLE_CALLED;

    // schedule
    if (_updating) {
        _deferredComps.emplace_back(comp);
    } else {
        scheduleImmediate(comp);
    }
}

void ComponentScheduler::onDisabled(Component *comp) {
    // legacyCC.director.getScheduler().pauseTarget(comp); //TODO(xwx): not sure use Director
    comp->_objFlags &= ~CCObject::Flags::IS_ON_ENABLE_CALLED;

    // cancel schedule task
    if (utils::fastRemove(_deferredComps, comp)) {
        return;
    }

    // unschedule
    // TODO(xwx): how to deal with prototype attributes?
    if (/* comp.start  && */ !(comp->_objFlags & CCObject::Flags::IS_START_CALLED)) { // TODO(xwx): no prototype attribute
        _startInvoker->remove(comp);
    }
    // if (comp.update) { // TODO(xwx): no prototype attribute
    _updateInvoker->remove(comp);
    // }
    // if (comp.lateUpdate) { // TODO(xwx): no prototype attribute
    _lateUpdateInvoker->remove(comp);
    // }
}

void ComponentScheduler::enableComp(Component *comp, std::optional<LifeCycleInvoker *> invoker) {
    if (!(comp->_objFlags & CCObject::Flags::IS_ON_ENABLE_CALLED)) {
        // if (comp.onEnable) { // TODO(xwx): no prototype attribute
        if (invoker.has_value()) {
            invoker.value()->add(comp);
            return;
        }
        comp->onEnable();
        bool deactivatedDuringOnEnable = !comp->getNode()->isActiveInHierarchy();
        if (deactivatedDuringOnEnable) {
            return;
        }
        // }
        onEnabled(comp);
    }
}

void ComponentScheduler::disableComp(Component *comp) {
    if (hasFlag(comp->_objFlags, CCObject::Flags::IS_ON_ENABLE_CALLED)) {
        // if (comp.onDisable) { // TODO(xwx): no prototype attribute
        comp->onDisable();
        // }
        onDisabled(comp);
    }
}

void ComponentScheduler::startPhase() {
    // Start of this frame
    _updating = true;

    // call start
    _startInvoker->invoke();
    // Start components of new activated nodes during start
    startForNewComps();
}

void ComponentScheduler::updatePhase(float dt) const {
    _updateInvoker->invoke(dt);
}

void ComponentScheduler::lateUpdatePhase(float dt) {
    _lateUpdateInvoker->invoke(dt);

    // End of this frame
    _updating = false;

    // Start components of new activated nodes during update and lateUpdate
    // They will be running in the next frame
    startForNewComps();
}

// Call new registered start schedule immediately since last time start phase calling in this frame
// See cocos-creator/2d-tasks/issues/256
void ComponentScheduler::startForNewComps() {
    if (!_deferredComps.empty()) {
        deferredSchedule();
        _startInvoker->invoke();
    }
}

void ComponentScheduler::scheduleImmediate(Component *comp) {
    if (!(comp->_objFlags & CCObject::Flags::IS_START_CALLED)) {
        _startInvoker->add(comp);
    }

    _updateInvoker->add(comp);
    _lateUpdateInvoker->add(comp);
}

void ComponentScheduler::deferredSchedule() {
    for (auto *comp : _deferredComps) {
        scheduleImmediate(comp);
    }
    _deferredComps.clear();
}

} // namespace cc
