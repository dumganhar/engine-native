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

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "base/Ref.h"
#include "core/System.h"

namespace cc {

using ccSchedulerFunc = std::function<void(float)>;
class Scheduler;
/**
	 * @cond
	 */
class CC_DLL Timer {
public:
    /** get interval in seconds */
    inline float getInterval() const { return _interval; };
    /** set interval in seconds */
    inline void setInterval(float interval) { _interval = interval; };

    void setupTimerWithInterval(float seconds, unsigned int repeat, float delay);

    virtual void trigger(float dt) = 0;
    virtual void cancel()          = 0;

    /** triggers the timer */
    void update(float dt);

protected:
    Timer() = default;

protected:
    Scheduler* _scheduler{nullptr};
    float      _elapsed{0.f};
    bool       _runForever{false};
    bool       _useDelay{false};
    uint32_t   _timesExecuted{0};
    uint32_t   _repeat{0}; //0 = once, 1 is 2 x executed
    float      _delay{0.f};
    float      _interval{0.f};
};

class CC_DLL TimerTargetCallback final : public Timer {
public:
    TimerTargetCallback() = default;

    // Initializes a timer with a target, a lambda and an interval in seconds, repeat in number of times to repeat, delay in seconds.
    bool initWithCallback(Scheduler* scheduler, const ccSchedulerFunc& callback, ISchedulable* target, const std::string& key, float seconds, uint32_t repeat, float delay);

    inline const ccSchedulerFunc& getCallback() const { return _callback; };
    inline const std::string&     getKey() const { return _key; };

    void trigger(float dt) override;
    void cancel() override;

private:
    ISchedulable*   _target{nullptr};
    ccSchedulerFunc _callback{nullptr};
    std::string     _key;
};

/**
 * @en A list double-linked list used for "updates with priority"
 * @zh 用于“优先更新”的列表
 * @class ListEntry
 * @param target not retained (retained by hashUpdateEntry)
 * @param priority
 * @param paused
 * @param markedForDeletion selector will no longer be called and entry will be removed at end of the next tick
 */
class ListEntry {
public:
    ISchedulable* _target{nullptr};
    Priority      _priority{Priority::LOW};
    bool          _paused{false};
    bool          _markedForDeletion{false};

    ListEntry(ISchedulable* target, uint32_t priority, bool paused, bool markedForDeletion);
    ~ListEntry();

    static ListEntry* get(ISchedulable* target, uint32_t priority, bool paused, bool markedForDeletion);
    static void       put(ListEntry* entry);

private:
    static std::vector<ListEntry*> _listEntries;
};

/**
 * @en A update entry list
 * @zh 更新条目列表
 * @class HashUpdateEntry
 * @param list Which list does it belong to ?
 * @param entry entry in the list
 * @param target hash key (retained)
 * @param callback
 */
class HashUpdateEntry {
public:
    void*           _list; //unknown usage
    ListEntry*      _entry{nullptr};
    ISchedulable*   _target{nullptr};
    ccSchedulerFunc _callback{nullptr};

    HashUpdateEntry(void* list, ListEntry* entry, ISchedulable* target, ccSchedulerFunc* callback);
    ~HashUpdateEntry();

    static HashUpdateEntry* get(std::vector<HashUpdateEntry*>& list, ListEntry* entry, ISchedulable* target, ccSchedulerFunc* callback);
    static void             put(HashUpdateEntry* entry);

private:
    static std::vector<HashUpdateEntry*> _hashUpdateEntries;
};

/**
 * @en Hash Element used for "selectors with interval"
 * @zh “用于间隔选择”的哈希元素
 * @class HashTimerEntry
 * @param timers
 * @param target  hash key (retained)
 * @param timerIndex
 * @param currentTimer
 * @param currentTimerSalvaged
 * @param paused
 */
class HashTimerEntry {
public:
    std::vector<Timer*> _timers;
    ISchedulable*       _target{nullptr};
    uint32_t            _timerIndex{0};
    Timer*              _currentTimer{nullptr};
    bool                _currentTimerSalvaged{false};
    bool                _paused{false};

    static HashTimerEntry* get(std::vector<Timer*>& timers, ISchedulable* target, uint32_t timerIndex, Timer* currentTimer, bool currentTimerSalvaged, bool paused);
    static void            put(HashTimerEntry* entry);

private:
    static std::vector<HashTimerEntry*> _hashTimerEntries;
};

/**
 * @en
 * Scheduler is responsible of triggering the scheduled callbacks.<br>
 * You should not use NSTimer. Instead use this class.<br>
 * <br>
 * There are 2 different types of callbacks (selectors):<br>
 *     - update callback: the 'update' callback will be called every frame. You can customize the priority.<br>
 *     - custom callback: A custom callback will be called every frame, or with a custom interval of time<br>
 * <br>
 * The 'custom selectors' should be avoided when possible. It is faster,<br>
 * and consumes less memory to use the 'update callback'. *
 * @zh
 * Scheduler 是负责触发回调函数的类。<br>
 * 通常情况下，建议使用 `director.getScheduler()` 来获取系统定时器。<br>
 * 有两种不同类型的定时器：<br>
 *     - update 定时器：每一帧都会触发。您可以自定义优先级。<br>
 *     - 自定义定时器：自定义定时器可以每一帧或者自定义的时间间隔触发。<br>
 * 如果希望每帧都触发，应该使用 update 定时器，使用 update 定时器更快，而且消耗更少的内存。
 *
 * @class Scheduler
 */
class Scheduler final : public System {
private:
    double                  _timeScale;
    std::vector<ListEntry*> _updatesNegList;
    std::vector<ListEntry*> _updates0List;
    std::vector<ListEntry*> _updatesPosList;

    std::unordered_map<void*, HashUpdateEntry*> _hashForUpdates;
    std::unordered_map<void*, HashTimerEntry*>  _hashForTimers;

    //Old ts code for _currentTarget, _currentTargetSalved
    HashTimerEntry*     _currentTimer{nullptr};
    bool                _currentTimerSalvaged{false};
    bool                _updateHashLocked{false};
    std::vector<Timer*> _arrayForTimers;

    //Previous: _removeHashElement, now: _removeTimerFromHash
    void _removeTimerFromHash(HashTimerEntry* element);
    void _removeUpdateFromHash(HashUpdateEntry* element);
    void _priorityIn(std::vector<ListEntry*>& pplist, ListEntry* listElement, Priority priority);
    void _appendIn(std::vector<ListEntry*>& pplist, ListEntry* listElement);

public:
    Scheduler();
    ~Scheduler();
    static void enableForTarget(ISchedulable* target);

    bool inline isCurrentTimerSalvaged() const { return _currentTimerSalvaged; }

    bool inline isUpdateHashLocked() const { return _updateHashLocked; }

    /**
     * @en
     * Modifies the time of all scheduled callbacks.<br>
     * You can use this property to create a 'slow motion' or 'fast forward' effect.<br>
     * Default is 1.0. To create a 'slow motion' effect, use values below 1.0.<br>
     * To create a 'fast forward' effect, use values higher than 1.0.<br>
     * Note：It will affect EVERY scheduled selector / action.
     * @zh
     * 设置时间间隔的缩放比例。<br>
     * 您可以使用这个方法来创建一个 “slow motion（慢动作）” 或 “fast forward（快进）” 的效果。<br>
     * 默认是 1.0。要创建一个 “slow motion（慢动作）” 效果,使用值低于 1.0。<br>
     * 要使用 “fast forward（快进）” 效果，使用值大于 1.0。<br>
     * 注意：它影响该 Scheduler 下管理的所有定时器。
     * @param timeScale
     */
    void inline setTimeScale(double& t) { _timeScale = t; }
    double inline getTimeScale() { return _timeScale; }

    /**
     * @en 'update' the scheduler. (You should NEVER call this method, unless you know what you are doing.)
     * @zh update 调度函数。(不应该直接调用这个方法，除非完全了解这么做的结果)
     * @param dt delta time
     */
    void update(uint32_t& dt);

    /**
     * @en
     * <p>
     *   The scheduled method will be called every 'interval' seconds.<br/>
     *   If paused is YES, then it won't be called until it is resumed.<br/>
     *   If 'interval' is 0, it will be called every frame, but if so, it recommended to use 'scheduleUpdateForTarget:' instead.<br/>
     *   If the callback function is already scheduled, then only the interval parameter will be updated without re-scheduling it again.<br/>
     *   repeat let the action be repeated repeat + 1 times, use `macro.REPEAT_FOREVER` to let the action run continuously<br/>
     *   delay is the amount of time the action will wait before it'll start<br/>
     * </p>
     * @zh
     * 指定回调函数，调用对象等信息来添加一个新的定时器。<br/>
     * 如果 paused 值为 true，那么直到 resume 被调用才开始计时。<br/>
     * 当时间间隔达到指定值时，设置的回调函数将会被调用。<br/>
     * 如果 interval 值为 0，那么回调函数每一帧都会被调用，但如果是这样，
     * 建议使用 scheduleUpdateForTarget 代替。<br/>
     * 如果回调函数已经被定时器使用，那么只会更新之前定时器的时间间隔参数，不会设置新的定时器。<br/>
     * repeat 值可以让定时器触发 repeat + 1 次，使用 `macro.REPEAT_FOREVER`
     * 可以让定时器一直循环触发。<br/>
     * delay 值指定延迟时间，定时器会在延迟指定的时间之后开始计时。
     * @param callback
     * @param target
     * @param interval
     * @param [repeat]
     * @param [delay=0]
     * @param [paused=fasle]
     */
    void schedule(ccSchedulerFunc& callback, ISchedulable* target, uint32_t interval, uint32_t repeat, uint32_t delay, bool paused = false);

    /**
     * @en
     * Schedules the update callback for a given target,
     * During every frame after schedule started, the "update" function of target will be invoked.
     * @zh
     * 使用指定的优先级为指定的对象设置 update 定时器。<br>
     * update 定时器每一帧都会被触发，触发时自动调用指定对象的 "update" 函数。<br>
     * 优先级的值越低，定时器被触发的越早。
     * @param target
     * @param priority
     * @param paused
     */
    void scheduleUpdate(ISchedulable* target, Priority priority, bool paused);

    /**
     * @en
     * Unschedules a callback for a callback and a given target.
     * If you want to unschedule the "update", use `unscheduleUpdate()`
     * @zh
     * 取消指定对象定时器。
     * 如果需要取消 update 定时器，请使用 unscheduleUpdate()。
     * @param callback The callback to be unscheduled
     * @param target The target bound to the callback.
     */
    void unschedule(ccSchedulerFunc& callback, ISchedulable* target);

    /**
		 * @en Unschedules the update callback for a given target.
		 * @zh 取消指定对象的 update 定时器。
		 * @param target The target to be unscheduled.
		 */
    void unscheduleUpdate(ISchedulable* target);

    /**
		 * @en
		 * Unschedules all scheduled callbacks for a given target.
		 * This also includes the "update" callback.
		 * @zh 取消指定对象的所有定时器，包括 update 定时器。
		 * @param target The target to be unscheduled.
		 */
    void unscheduleAllForTarget(ISchedulable* target);

    /**
     * @en
     * Unschedules all scheduled callbacks from all targets including the system callbacks.<br/>
     * You should NEVER call this method, unless you know what you are doing.
     * @zh
     * 取消所有对象的所有定时器，包括系统定时器。<br/>
     * 不要调用此函数，除非你确定你在做什么。
     */
    void unscheduleAll();

    /**
     * @en
     * Unschedules all callbacks from all targets with a minimum priority.<br/>
     * You should only call this with `PRIORITY_NON_SYSTEM_MIN` or higher.
     * @zh
     * 取消所有优先级的值大于指定优先级的定时器。<br/>
     * 你应该只取消优先级的值大于 PRIORITY_NON_SYSTEM_MIN 的定时器。
     * @param minPriority The minimum priority of selector to be unscheduled. Which means, all selectors which
     *        priority is higher than minPriority will be unscheduled.
     */
    void unscheduleAllWithMinPriority(uint32_t minPriority);

    /**
     * @en Checks whether a callback for a given target is scheduled.
     * @zh 检查指定的回调函数和回调对象组合是否存在定时器。
     * @param callback The callback to check.
     * @param target The target of the callback.
     * @return True if the specified callback is invoked, false if not.
     */
    bool isScheduled(ccSchedulerFunc& callback, ISchedulable* target);

    /**
     * @en
     * Pauses the target.<br/>
     * All scheduled selectors/update for a given target won't be 'ticked' until the target is resumed.<br/>
     * If the target is not present, nothing happens.
     * @zh
     * 暂停指定对象的定时器。<br/>
     * 指定对象的所有定时器都会被暂停。<br/>
     * 如果指定的对象没有定时器，什么也不会发生。
     * @param target
     */
    void pauseTarget(ISchedulable* target);

    /**
     * @en
     * Pause all selectors from all targets.<br/>
     * You should NEVER call this method, unless you know what you are doing.
     * @zh
     * 暂停所有对象的所有定时器。<br/>
     * 不要调用这个方法，除非你知道你正在做什么。
     */
    void pauseAllTarget();

    /**
     * @en
     * Pause all selectors from all targets with a minimum priority. <br/>
     * You should only call this with kCCPriorityNonSystemMin or higher.
     * @zh
     * 暂停所有优先级的值大于指定优先级的定时器。<br/>
     * 你应该只暂停优先级的值大于 PRIORITY_NON_SYSTEM_MIN 的定时器。
     * @param minPriority
     */
    void pauseAllTargetsWithMinPriority(uint32_t minPriority);

    /**
     * @en
     * Resume selectors on a set of targets.<br/>
     * This can be useful for undoing a call to pauseAllCallbacks.
     * @zh
     * 恢复指定数组中所有对象的定时器。<br/>
     * 这个函数是 pauseAllCallbacks 的逆操作。
     * @param targetsToResume
     */
    void resumeTargets(ccSchedulerFunc& targetsToResume);

    /**
     * @en
     * Resumes the target.<br/>
     * The 'target' will be unpaused, so all schedule selectors/update will be 'ticked' again.<br/>
     * If the target is not present, nothing happens.
     * @zh
     * 恢复指定对象的所有定时器。<br/>
     * 指定对象的所有定时器将继续工作。<br/>
     * 如果指定的对象没有定时器，什么也不会发生。
     * @param target
     */
    void resumeTarget(ISchedulable* target);

    /**
     * @en Returns whether or not the target is paused.
     * @zh 返回指定对象的定时器是否处于暂停状态。
     * @param target
     */
    bool isTargetPaused(ISchedulable* target);
};

} // namespace cc