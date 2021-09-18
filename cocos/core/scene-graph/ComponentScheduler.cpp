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

#include <exception>
#include <utility>
namespace {
const cc::CCObject::Flags IS_START_CALLED            = cc::CCObject::Flags::IS_START_CALLED;
const cc::CCObject::Flags IS_ON_ENABLE_CALLED        = cc::CCObject::Flags::IS_ON_ENABLE_CALLED;
const cc::CCObject::Flags IS_EDITOR_ON_ENABLE_CALLED = cc::CCObject::Flags::IS_EDITOR_ON_ENABLE_CALLED;

using singleInvokeCB = std::function<void(cc::Component *)>;
using doubleInvokeCB = std::function<void(cc::Component *, float dt)>;
using fastPathCB     = std::function<void(std::vector<cc::Component *>, std::optional<float>)>;
// fastPathCB fast  = [](std::vector<cc::Component *> com, std::optional<float> dt) {
//     fastPathCB(com, 1);
// };

void func(const std::vector<cc::Component *> &components, std::optional<float> dt) {
}
cc::Invoker createInvokeImpl(singleInvokeCB, fastPathCB, std::optional<cc::CCObject::Flags> ensureFlag) {
    return [](std::vector<cc::Component *> components, std::optional<float> dt) {
        try {
        } catch (std::exception &e) {
        }
    };
    // [ensureFlag](std::vector<cc::Component *> , std::optional<float> dt) {
    //     fastPathCB(dtd);
    // };
}

cc::Invoker createInvokeImpl(doubleInvokeCB, fastPathCB, std::optional<cc::CCObject::Flags> ensureFlag) {
    return [](std::vector<cc::Component *> components, std::optional<float> dt) {
        try {
        } catch (std::exception &e) {
        }
    };
    // [ensureFlag](std::vector<cc::Component *> , std::optional<float> dt) {
    //     fastPathCB(dtd);
    // };
}

} // namespace
namespace cc {

// LifeCycleInvoker
LifeCycleInvoker::LifeCycleInvoker(Invoker invokeFunc) : _invoke(std::move(invokeFunc)) {}

// Invoker invokeStart = createInvokeImpl(
//     [](cc::Component *c) {c->start(); c->_objFlags |= IS_START_CALLED; },
//     [](const std::vector<cc::Component *> &components, std::optional<float> dt = std::nullopt) {
//         for (auto *comp : components) {
//             comp->start();
//             comp->_objFlags |= IS_START_CALLED;
//         }
//     },
//     IS_START_CALLED);

Invoker invokeUpdate = createInvokeImpl(
    [](cc::Component *c, float dt) { c->update(dt); },
    [](const std::vector<cc::Component *> &components, std::optional<float> dt = std::nullopt) {
        for (auto *comp : components) {
            if (dt.has_value()) {
                comp->update(dt.value());
            }
        }
    },
    IS_START_CALLED);

Invoker invokeLateUpdate = createInvokeImpl(
    [](cc::Component *c, float dt) { c->lateUpdate(dt); },
    [](const std::vector<cc::Component *> &components, std::optional<float> dt = std::nullopt) {
        for (auto *comp : components) {
            if (dt.has_value()) {
                comp->lateUpdate(dt.value());
            }
        }
    },
    IS_START_CALLED);

void LifeCycleInvoker::stableRemoveInactive(std::vector<Component *> &components) {
    for (auto iter = components.begin(); iter != components.end(); ++iter) {
        if ((*iter)->getNode()->isActiveInHierarchy()) {
            continue;
        }
        components.erase(iter);
    }
}

void LifeCycleInvoker::stableRemoveInactive(std::vector<Component *> &components, CCObject::Flags flagToClear) {
    // TODO(xwx): ts logic seems wrong, can't understand
    for (auto iter = components.begin(); iter != components.end(); ++iter) {
        if ((*iter)->getNode()->isActiveInHierarchy()) {
            continue;
        }
        (*iter)->_objFlags &= ~flagToClear;
        components.erase(iter);
    }
}

int32_t LifeCycleInvoker::sortedIndex(std::vector<Component *> &components, Component *comp) {
    // const order = comp.constructor._executionOrder; // TODO(xwx): no prototype attribute
    const int32_t      order = 1; // TODO(xwx): just for compile, remove after
    const std::string &id    = comp->getUuid();
    int32_t            l     = 0;
    for (int32_t h = components.size() - 1, m = static_cast<uint32_t>(h) >> 1; l <= h; m = static_cast<uint32_t>(l + h) >> 1) {
        auto *test = components[m];
        // const int32_t testOrder = constructor._executionOrder; // TODO(xwx): no prototype attribute
        const int32_t testOrder = 1; // TODO(xwx): just for compile, remove after
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
    //const int32_t order = comp.constructor._executionOrder; // TODO(xwx): no prototype attribute
    const int32_t order = 1; // TODO(xwx): just for compile, remove after
    if (order > 0) {
        _pos.emplace_back(comp);
    } else if (order < 0) {
        _neg.emplace_back(comp);
    } else {
        _zero.emplace_back(comp);
    }
}

void OneOffInvoker::remove(Component *comp) {
    // const int32_t order = comp.constructor._executionOrder; // TODO(xwx): no prototype attribute
    const int32_t order = 1; // TODO(xwx): just for compile, remove after
    if (order > 0) {
        auto iter = std::find(_pos.begin(), _pos.end(), comp);
        if (iter != _pos.end()) {
            _pos.erase(iter);
        }
    } else if (order < 0) {
        auto iter = std::find(_neg.begin(), _neg.end(), comp);
        if (iter != _neg.end()) {
            _neg.erase(iter);
        }
    } else {
        auto iter = std::find(_zero.begin(), _zero.end(), comp);
        if (iter != _zero.end()) {
            _zero.erase(iter);
        }
    }
}

void OneOffInvoker::cancelInactive(CCObject::Flags flagToClear) {
    stableRemoveInactive(_zero, flagToClear);
    stableRemoveInactive(_neg, flagToClear);
    stableRemoveInactive(_pos, flagToClear);
}

void OneOffInvoker::invoke() {
    if (!_neg.empty()) {
        // TODO(xwx):  no prototype attribute
        std::sort(_neg.begin(), _neg.end() /*, [](Component *a, Component *b) { return a.constructor._executionOrder - b.constructor._executionOrder } */);
        _invoke(_neg, std::nullopt);
        _neg.clear();
    }
    _invoke(_zero, std::nullopt);
    _zero.clear();

    if (!_pos.empty()) {
        // TODO(xwx):  no prototype attribute
        std::sort(_pos.begin(), _pos.end() /*, [](Component *a, Component *b) { return a.constructor._executionOrder - b.constructor._executionOrder } */);
        _invoke(_pos, std::nullopt);
        _pos.clear();
    }
}

// ReusableInvoker
void ReusableInvoker::add(Component *comp) {
    // const int32_t order = comp.constructor._executionOrder; // TODO(xwx): no prototype attribute
    const int32_t order = 1; // TODO(xwx): just for compile, remove after
    if (order == 0) {
        _zero.emplace_back(comp);
    } else if (order < 0) {
        const int32_t idx = sortedIndex(_neg, comp);
        if (idx < 0) {
            _neg.insert(_neg.begin() + (~idx), comp);
        }
        // else if (DEV) { //TODO(xwx): no DEV now
        //     error('component already added');
        // }
    } else {
        const int32_t idx = sortedIndex(_pos, comp);
        if (idx < 0) {
            _pos.insert(_pos.begin() + (~idx), comp);
        }
        // else if (DEV) { //TODO(xwx): no DEV now
        // //     error('component already added');
        // }
    }
}

void ReusableInvoker::remove(Component *comp) {
    // const int32_t order = comp.constructor._executionOrder; // TODO(xwx): no prototype attribute
    const int32_t order = 1; // TODO(xwx): just for compile, remove after
    if (order == 0) {
        auto iter = std::find(_zero.begin(), _zero.end(), comp);
        if (iter != _zero.end()) {
            _zero.erase(iter);
        }
    } else if (order < 0) {
        const int32_t idx = sortedIndex(_neg, comp);
        if (idx >= 0) {
            _neg.erase(_neg.begin() + idx);
        }
    } else {
        const int32_t idx = sortedIndex(_pos, comp);
        if (idx >= 0) {
            _pos.erase(_pos.begin() + idx);
        }
    }
}

void ReusableInvoker::invoke(float dt) {
    if (!_neg.empty()) {
        _invoke(_neg, dt);
    }

    _invoke(_zero, dt);

    if (!_pos.empty()) {
        _invoke(_pos, dt);
    }
}

// ComponentScheduler
ComponentScheduler::ComponentScheduler() {
    unscheduleAll();
}

ComponentScheduler::~ComponentScheduler() = default;

void ComponentScheduler::unscheduleAll() {
    // TODO(xwx): invokers cbs not defined and why this function called unscheduleAll?
    // startInvoker = new OneOffInvoker(invokeStart);
    // updateInvoker     = new ReusableInvoker(invokeUpdate);
    // lateUpdateInvoker = new ReusableInvoker(invokeLateUpdate);

    // during a loop
    _updating = false;
};

void ComponentScheduler::onEnabled(Component *comp) {
    // legacyCC.director.getScheduler().resumeTarget(comp); //TODO(xwx): not sure use Director
    comp->_objFlags |= IS_ON_ENABLE_CALLED;

    // schedule
    if (_updating) {
        _deferredComps.emplace_back(comp);
    } else {
        scheduleImmediate(comp);
    }
};

void ComponentScheduler::onDisabled(Component *comp) {
    // legacyCC.director.getScheduler().pauseTarget(comp); //TODO(xwx): not sure use Director
    comp->_objFlags &= ~IS_ON_ENABLE_CALLED;

    // cancel schedule task
    // auto index = this._deferredComps.indexOf(comp);
    // if (index >= 0) {
    //     fastRemoveAt(this._deferredComps, index);
    //     return;
    // }
    auto iter = std::find(_deferredComps.begin(), _deferredComps.end(), comp);
    if (iter != _deferredComps.end()) {
        _deferredComps.erase(iter);
    }

    // unschedule
    // TODO(xwx): how to deal with prototype attributes?
    if (/* comp.start  && */ !(comp->_objFlags & IS_START_CALLED)) { // TODO(xwx): no prototype attribute
        startInvoker->remove(comp);
    }
    // if (comp.update) { // TODO(xwx): no prototype attribute
    updateInvoker->remove(comp);
    // }
    // if (comp.lateUpdate) { // TODO(xwx): no prototype attribute
    lateUpdateInvoker->remove(comp);
    // }
};
void ComponentScheduler::enableComp(Component *comp, std::optional<LifeCycleInvoker *> invoker) {
    if (!(comp->_objFlags & IS_ON_ENABLE_CALLED)) {
        // if (comp.onEnable) { // TODO(xwx): no prototype attribute
        if (invoker.has_value()) {
            // invoker.value()->add(comp); // TODO(xwx): no function, need cast?
            return;
            // }
            comp->onEnable();
            bool deactivatedDuringOnEnable = !comp->getNode()->isActiveInHierarchy();
            if (deactivatedDuringOnEnable) {
                return;
            }
        }
        onEnabled(comp);
    }
};
void ComponentScheduler::disableComp(Component *comp) {
    if (hasFlag(comp->_objFlags, IS_ON_ENABLE_CALLED)) {
        // if (comp.onDisable) { // TODO(xwx): no prototype attribute
        comp->onDisable();
        // }
        onDisabled(comp);
    }
};
void ComponentScheduler::startPhase() {
    // Start of this frame
    _updating = true;

    // call start
    startInvoker->invoke();
    // Start components of new activated nodes during start
    startForNewComps();
};

void ComponentScheduler::updatePhase(float dt) const {
    updateInvoker->invoke(dt);
};

void ComponentScheduler::lateUpdatePhase(float dt) {
    lateUpdateInvoker->invoke(dt);

    // End of this frame
    _updating = false;

    // Start components of new activated nodes during update and lateUpdate
    // They will be running in the next frame
    startForNewComps();
};

// Call new registered start schedule immediately since last time start phase calling in this frame
// See cocos-creator/2d-tasks/issues/256
void ComponentScheduler::startForNewComps() {
    if (!_deferredComps.empty()) {
        deferredSchedule();
        startInvoker->invoke();
    }
};

void ComponentScheduler::scheduleImmediate(Component *comp) {
    if (/*typeof comp.start === 'function' && */ !(comp->_objFlags & IS_START_CALLED)) { // TODO(xwx): how to adapt ts usage?
        startInvoker->add(comp);
    }
    // if (typeof comp.update === 'function') { // TODO(xwx): how to adapt ts usage?
    updateInvoker->add(comp);
    // }
    // if (typeof comp.lateUpdate === 'function') { TODO(xwx): how to adapt ts usage?
    lateUpdateInvoker->add(comp);
    // }
};
void ComponentScheduler::deferredSchedule() {
    for (auto *comp : _deferredComps) {
        scheduleImmediate(comp);
    }
    _deferredComps.clear();
};

} // namespace cc
