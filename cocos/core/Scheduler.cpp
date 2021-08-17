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
#include "Scheduler.h"

namespace {
constexpr unsigned CC_REPEAT_FOREVER{UINT_MAX - 1};
constexpr int      MAX_FUNC_TO_PERFORM{30};
constexpr int      INITIAL_TIMER_COUND{10};
} // namespace

namespace cc {

    void Timer::setupTimerWithInterval(float interval, uint32_t repeat, float delay) {
        _elapsed = -1;
        _interval = interval;
        _delay = delay;
        _useDelay = _delay > 0.0F;
        _repeat = repeat;
        _runForever = _repeat == CC_REPEAT_FOREVER;
    }

    void Timer::update(float dt) {
        if (_elapsed == -1) {
            _elapsed = 0;
            _timesExecuted = 0;
            return;
        }

        // accumulate elapsed time
        _elapsed += dt;

        // deal with delay
        if (_useDelay) {
            if (_elapsed < _delay) {
                return;
            }
            trigger(_delay);
            _elapsed = _elapsed - _delay;
            _timesExecuted += 1;
            _useDelay = false;
            // after delay, the rest time should compare with interval
            if (!_runForever && _timesExecuted > _repeat) { //unschedule timer
                cancel();
                return;
            }
        }

        // if _interval == 0, should trigger once every frame
        float interval = (_interval > 0) ? _interval : _elapsed;
        while (_elapsed >= interval) {
            trigger(interval);
            _elapsed -= interval;
            _timesExecuted += 1;

            if (!_runForever && _timesExecuted > _repeat) {
                cancel();
                break;
            }

            if (_elapsed <= 0.F) {
                break;
            }

            if (_scheduler->isCurrentTimerSalvaged()) {
                break;
            }
        }
    }

    // TimerTargetCallback

    bool TimerTargetCallback::initWithCallback(Scheduler* scheduler, const ccSchedulerFunc& callback, ISchedulable* target, const std::string& key, float seconds, uint32_t repeat, float delay) {
        _scheduler = scheduler;
        _target = target;
        _callback = callback;
        _key = key;
        setupTimerWithInterval(seconds, repeat, delay);
        return true;
    }

    void TimerTargetCallback::trigger(float dt) {
        if (_callback) {
            _callback(dt);
        }
    }

    void TimerTargetCallback::cancel() {
    }

} // namespace cc

