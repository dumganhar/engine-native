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

#include <iostream>
#include "base/Macros.h"
#include "core/Scheduler.h"

namespace {
constexpr uint32_t CC_REPEAT_FOREVER{UINT_MAX - 1};
constexpr uint32_t MAX_FUNC_TO_PERFORM{30};
constexpr uint32_t INITIAL_TIMER_COUND{10};
constexpr uint32_t MAX_POOL_SIZE{ 20 };

template <typename A, typename ... Values>
static size_t ccGetFuncAddress(const std::function<A(Values...)>& func) {
    typedef A(fnType)(Values...);
    return (size_t)(func.template target<fnType*>());
}
template<class T>
static void releaseVector(std::vector<T*>& v) {
    //if it's still in use, then should not consider the capacity
    for (auto i : v) {
        delete i;
    }v.clear();
}

template<class F, class S>
static void releaseMap(std::unordered_map<F, S*>& m) {
    for (auto i : m) {
        delete i.second;
    }
    m.clear();
}


} // namespace

namespace cc {
    /******** TimerTargetCallback *********/
    void TimerTargetCallback::setupTimerWithInterval(float interval, uint32_t repeat, float delay) {
        _elapsed = -1.f;
        _interval = interval;
        _delay = delay;
        _useDelay = _delay > 0.0F;
        _repeat = repeat;
        _runForever = _repeat == CC_REPEAT_FOREVER;
    }

    void TimerTargetCallback::update(float dt) {
        if (_elapsed == -1.f) {
            _elapsed = 0.f;
            _timesExecuted = 0;
            return;
        }

        // accumulate elapsed time
        _elapsed += dt;
        if (_runForever && !_useDelay) {
            if (_elapsed >= _interval) {
                trigger();
                _elapsed = 0;
            }
            return;
        }


        // deal with delay
        if (_useDelay) {
            if (_elapsed >= _delay) {
                trigger();
                _elapsed -= _delay;
                _timesExecuted++;
                _useDelay = false;
            }
        }
        else if (_elapsed >= _interval) {
            trigger();
            _elapsed = 0.f;
            _timesExecuted++;

        }
        if (_callback != nullptr && !_runForever && _timesExecuted > _repeat)
        {
            cancel();
        }
    }

    bool TimerTargetCallback::initWithCallback(
        Scheduler* scheduler,
        const ccSchedulerFunc& callback,
        System* target,
        float interval,
        uint32_t repeat,
        float delay) {

        _lock = false;
        _scheduler = scheduler;
        _target = target;
        _callback = callback;

        setupTimerWithInterval(interval, repeat, delay);
        return true;
    }

    void TimerTargetCallback::trigger() {
        if (_callback && _target) {
            _lock = true;
            _callback(_target, _elapsed);
            _lock = false;
        }
    }

    void TimerTargetCallback::cancel() {
        this->_scheduler->unschedule(_callback, _target);
    }
    /***** List Entry *****/
    std::vector<ListEntry*> ListEntry::_listEntries = std::vector<ListEntry*>();

    ListEntry::ListEntry(System* target,
        Priority priority,
        bool paused,
        bool markedForDeletion) :
        _target(target),
        _priority(priority),
        _markedForDeletion(markedForDeletion),
        _paused(paused) {}
    ListEntry::~ListEntry() {
        delete _target;
    }

    ListEntry* ListEntry::getFromPool(System* target,
        Priority priority,
        bool paused,
        bool markedForDeletion) {
        if (!_listEntries.empty()) {
            ListEntry* result = _listEntries.back();
            _listEntries.pop_back();
            delete result->_target;
            result->_target = target;
            result->_priority = priority;
            result->_paused = paused;
            result->_markedForDeletion = markedForDeletion;
            return result;
        }
        else {
            ListEntry* result = new ListEntry(target, priority, paused, markedForDeletion);
            return result;
        }
    }
    void ListEntry::pushToPool(ListEntry* entry) {
        if (_listEntries.size() < MAX_POOL_SIZE) {
            delete entry->_target;
            entry->_target = nullptr;
            _listEntries.push_back(entry);
        }
    }

    /**** HashUpdateEntry ****/

    std::vector<HashUpdateEntry*> HashUpdateEntry::_hashUpdateEntries = std::vector<HashUpdateEntry*>();

    HashUpdateEntry::HashUpdateEntry(std::vector<ListEntry*> &list,
        ListEntry* entry,
        System* target,
        ccSchedulerFunc& callback) :
        _entry(entry),
        _target(target),
        _callback(callback) {
        _list = list;
    }

    HashUpdateEntry::~HashUpdateEntry() {
        release();
    }
    HashUpdateEntry* HashUpdateEntry::getFromPool(
        std::vector<ListEntry*> &list,
        ListEntry* entry,
        System* target,
        ccSchedulerFunc& callback) {
        if (!_hashUpdateEntries.empty()) {
            HashUpdateEntry* result = _hashUpdateEntries.back();
            _hashUpdateEntries.pop_back();
            result->release();
            //TODO: as the list is not the same vector, even it contains same ListEntry, it will release the same address but release twice
            result->_list = list;
            result->_entry = entry;
            result->_target = target;
            result->_callback = callback;
            return result;
        }
        else {
            return new HashUpdateEntry(list, entry, target, callback);
        }

    }
    void HashUpdateEntry::pushToPool(HashUpdateEntry* entry) {
        if (_hashUpdateEntries.size() < MAX_POOL_SIZE) {
            entry->release();
            entry->_callback = nullptr;
            _hashUpdateEntries.push_back(entry);
        }
    }
    
    void HashUpdateEntry::release() {
        delete _entry;
        delete _target;
    }
    /**** HashTimerEntry ****/
    std::vector<HashTimerEntry*> HashTimerEntry::_hashTimerEntries = std::vector<HashTimerEntry*>();
    HashTimerEntry::HashTimerEntry(std::vector<TimerTargetCallback*>& timers,
        System* target,
        uint32_t timerIndex,
        TimerTargetCallback* currentTimer,
        bool currentTimerSalvaged,
        bool paused) :
        _target(target),
        _currentTimer(currentTimer),
        _timerIndex(timerIndex),
        _currentTimerSalvaged(currentTimerSalvaged),
        _paused(paused),
        _timers(timers) {}
    HashTimerEntry::~HashTimerEntry() {
        release();
    }
    void HashTimerEntry::release() {

        _currentTimer = nullptr;// _currentTimer get from _timers logically, so it would be released with _timers
        delete _target;
        for (TimerTargetCallback* t : _timers)
        {
            delete t;
        }
        _timers.clear();

    }
    HashTimerEntry* HashTimerEntry::getFromPool(std::vector<TimerTargetCallback*>& timers,
        System* target,
        uint32_t timerIndex,
        TimerTargetCallback* currentTimer,
        bool currentTimerSalvaged,
        bool paused) {
        if (!_hashTimerEntries.empty()) {
            //get from vector pool
            auto result = _hashTimerEntries.back();
            _hashTimerEntries.pop_back();
            result->release();
            result->_timers = timers;
            result->_currentTimer = currentTimer;
            result->_timerIndex = timerIndex;
            result->_currentTimerSalvaged = currentTimerSalvaged;
            result->_paused = paused;
            return result;
        }
        else {
            return new HashTimerEntry();
        }
    }
    void HashTimerEntry::pushToPool(HashTimerEntry* entry) {
        _hashTimerEntries.push_back(entry);
    }
    /***** Scheduler *****/
    void Scheduler::enableForTarget(System* target) {
        bool found{ false };
        if (target->uuid != "" || target->id != "") {
            found = true;
        }
        if (!found) {
            //TODO: use native idGenerator
            target->id = "FakeUUid";
        }
        
    }
    void Scheduler::resumeTarget(System* target) {
        CCASSERT(target, 1504);
        const std::string targetId{ target->uuid != "" ? target->uuid : target->id };
        CC_ASSERT(!targetId.empty());
        HashTimerEntry* element = _hashForTimers.find(targetId)->second;
        if (element) {
            element->_paused = false;
        }
        HashUpdateEntry* elementUpdate = _hashForUpdates.find(targetId)->second;
        if (elementUpdate) {
            elementUpdate->_entry->_paused = false;
        }
    }
    void Scheduler::resumeTargets(const std::vector<System*>& targetsToResume) {
        if (!targetsToResume.empty()) {
            for (auto i : targetsToResume) {
                resumeTarget(i);
            }
        }
    }
    //Remove TimerEntry From _arrayTimers, then push to static TimerEntry Pool
    void Scheduler::_removeTimerFromHash(HashTimerEntry* element) {
        const std::string targetId{ element->_target->uuid != "" ? element->_target->uuid : element->_target->id };
        delete _hashForTimers[targetId];
        _hashForTimers.erase(targetId);
        
        for (auto i = 0; i< _arrayForTimers.size(); ++i) {
            if (_arrayForTimers[i] ==  element) {
                _arrayForTimers.erase(_arrayForTimers.begin()+i);//?TODO: optimize usage
                break;
            }
        }
        HashTimerEntry::pushToPool(element); 
    }

    
    void Scheduler::_removeUpdateFromHash(ListEntry* entry) {
        const std::string targetId{ !entry->_target->uuid.empty() ? entry->_target->uuid : entry->_target->id };
        auto element = _hashForUpdates[targetId];
        //element is indicating the same HashUpdateEntry
        
        const ListEntry* listEntry = element->_entry;


        for (auto i = 0; i < element->_list.size(); ++i) {
            if (element->_list[i] == listEntry) {
                element->_list.erase(element->_list.begin() + i);
                //TODO: then what is it inside the element? an element not exist?
                break;
            }
        }

        
        _hashForUpdates.erase(targetId);

        ListEntry::pushToPool(element->_entry);
        HashUpdateEntry::pushToPool(element);
        
    }
    //sort insert in with priority
    void Scheduler::_priorityIn(std::vector<ListEntry*>& pplist, ListEntry* listElement, Priority priority) {
        for (auto i = 0; i < pplist.size(); i++) {
            if (priority < pplist[i]->_priority) {
                //@ts: ppList.splice(i, 0, listElement); its actually add one element in
                pplist.insert(pplist.begin() + i, listElement);
                return;
            }
        }
        pplist.push_back(listElement);
    }
    void Scheduler::_appendIn(std::vector<ListEntry*>& pplist, ListEntry* listElement) {
        pplist.push_back(listElement);
    }
    
    bool Scheduler::isTargetPaused(System* target) const {
        CC_ASSERT(target);
        const std::string targetId = target->uuid.empty() ? target->uuid : target->id;
        CCASSERT(!targetId.empty(),"error 1510");

        HashTimerEntry* element = _hashForTimers.find(targetId)->second;
        if (element) {
            return element->_paused;
        }
        const HashUpdateEntry* elementUpdate = _hashForUpdates.find(targetId)->second;
        if (elementUpdate) {
            return elementUpdate->_entry->_paused;
        }
        return false;
    }
    bool Scheduler::isScheduled(ccSchedulerFunc& callback, System* target) {
        CCASSERT(callback, 1508);
        CCASSERT(target, 1509);
        const std::string targetId{ target->uuid.empty() ? target->uuid : target->id };
        CCASSERT(!targetId.empty(), 1510);
        const HashTimerEntry* element = _hashForTimers.find(targetId)->second;
        if (element && !element->_timers.empty()) {
            for (auto t : element->_timers) {
                if (ccGetFuncAddress(callback) == ccGetFuncAddress(t->getCallback()))
                    return true;
            }
        }
        return false;
    }
    //Scheduler::Scheduler() {}
    Scheduler::~Scheduler() {
        release();
    }
    void Scheduler::release() {
        releaseVector(_updatesNegList);
        releaseVector(_updates0List);
        releaseVector(_updatesPosList);
        releaseVector(_arrayForTimers);
        releaseMap(_hashForTimers);
        releaseMap(_hashForUpdates);
        

    }
    void Scheduler::update(float dt) {
        _updateHashLocked = true;
        if (_timeScale != 1.f) {
            dt *= _timeScale;
        }
        for (auto i : _updatesNegList) {
            if (!i->_paused && !i->_markedForDeletion) {
                //TODO: Here we get an error as the System has no function of update.
                i->_target->update(dt);
            }
        }
        for (auto i : _updates0List) {
            if (!i->_paused && !i->_markedForDeletion) {
                //TODO: Here we get an error as the System has no function of update.
                i->_target->update(dt);
            }
        }
        for (auto i : _updatesPosList) {
            if (!i->_paused && !i->_markedForDeletion) {
                //TODO: Here we get an error as the System has no function of update.
                i->_target->update(dt);
            }
        }
        for (auto i : _arrayForTimers) {
            _currentTimer = i;
            _currentTimerSalvaged = false;
            if (!i->_paused) {
                for (i->_timerIndex = 0; i->_timerIndex < i->_timers.size(); ++i->_timerIndex) {
                    i->_currentTimer = i->_timers[i->_timerIndex];
                    i->_currentTimerSalvaged = false;
                    i->_currentTimer->update(dt);
                    i->_currentTimer = nullptr;
                }
            }
            if (_currentTimerSalvaged && _currentTimer->_timers.empty()) {
                _removeTimerFromHash(_currentTimer);
            }
        }
        for (auto i : this->_updatesNegList) {
            if (i->_markedForDeletion) {
                _removeUpdateFromHash(i);
            }
        }
        for (auto i : this->_updates0List) {
            if (i->_markedForDeletion) {
                _removeUpdateFromHash(i);
            }
        }for (auto i : this->_updatesPosList) {
            if (i->_markedForDeletion) {
                _removeUpdateFromHash(i);
            }
        }
        _updateHashLocked = false;
        _currentTimer = nullptr;
    }
    
    void Scheduler::schedule(ccSchedulerFunc& callback, System* target, uint32_t interval, uint32_t repeat, uint32_t delay ,bool paused = false) {
        CCASSERT(target, 1502);
        const std::string targetId{ target->uuid.empty() ? target->id : target->uuid };
        CCASSERT(!targetId.empty(), 1510);
        //TODO: Here if not found will trigger assert function
        auto element = _hashForTimers.find(targetId)->second;

        if (!element) {
            std::vector<TimerTargetCallback *> timers;
            element = HashTimerEntry::getFromPool(timers, target, 0, nullptr, false, paused);
            _arrayForTimers.push_back(element);
            _hashForTimers[targetId] = element;

        }
        else if (element->_paused != paused) {
            std::cout << "Warning! element is paused";
        }
        
        for (auto timer : element->_timers) {
            if (ccGetFuncAddress(callback) == ccGetFuncAddress(timer->getCallback())) {
                //TODO: logID
                timer->setInterval(interval);
                return;
            }
        }
        TimerTargetCallback* timer = new TimerTargetCallback();
        timer->initWithCallback(this, callback, target, interval, repeat, delay);
        element->_timers.push_back(timer);

        if (_currentTimer == element && _currentTimerSalvaged) {
            _currentTimerSalvaged = false;
        }
    }

    void Scheduler::scheduleUpdate(System* target, Priority priority, bool paused) {
        const std::string targetId{ target->uuid.empty() ? target->uuid : target->id };
        CCASSERT(!targetId.empty(),1510);
        auto hashElement = _hashForUpdates[targetId];
        if (hashElement && hashElement->_entry) {
            if (hashElement->_entry->_priority != priority) {
                if (_updateHashLocked) {
                    //TODO: logID 1506
                    hashElement->_entry->_markedForDeletion = false;
                    hashElement->_entry->_paused = paused;
                    return;
                }
                else {
                    unscheduleUpdate(target);
                }
            }
            else {
                hashElement->_entry->_markedForDeletion = false;
                hashElement->_entry->_paused = false;
                return;
            }
        }
        auto listElement = ListEntry::getFromPool(target, priority, paused, false);
        ccSchedulerFunc c{ nullptr };
        if (priority == Priority::LOW) {
            _appendIn(_updates0List, listElement);
            _hashForUpdates[targetId] = HashUpdateEntry::getFromPool(_updates0List, listElement, target, c);
        }
        else {
            if (static_cast<uint32_t>(priority) < 0) {
                _priorityIn(_updatesNegList, listElement, priority);
                _hashForUpdates[targetId] = HashUpdateEntry::getFromPool(_updatesNegList, listElement, target, c);
            }
            else {
                _priorityIn(_updatesPosList, listElement, priority);
                _hashForUpdates[targetId] = HashUpdateEntry::getFromPool(_updatesNegList, listElement, target, c);
            }
            
        }
        
    }
    void Scheduler::unschedule(ccSchedulerFunc& callback, System* target) {
        if (!target || !callback) {
            return;
        }
        const std::string targetId = target->uuid.empty() ? target->uuid : target->id;
        if (targetId.empty()) {
            CC_ASSERT("Error 1510");
            return;
        }
        HashTimerEntry* element;
        CC_ASSERT(element = _hashForTimers[targetId]);
        TimerTargetCallback* timer{ nullptr };
        for (auto i = 0; i < element->_timers.size(); i++) {
            timer = element->_timers[i];
            if (ccGetFuncAddress(callback) == ccGetFuncAddress(timer->getCallback())) {
                if ((timer == element->_currentTimer) && (!element->_currentTimerSalvaged)) {
                    element->_currentTimerSalvaged = true;
                }

                element->_timers.erase(element->_timers.begin() + i);
                delete timer;
                if (element->_timerIndex >= i) {
                    --element->_timerIndex;
                }
                if (element->_timers.empty()) {
                    if (_currentTimer == element) {
                        _currentTimerSalvaged = true;
                    }
                    else {
                        _removeTimerFromHash(element);
                    }
                }
                return;
            }
        }


    }
    void Scheduler::unscheduleUpdate(System* target) {
        CCASSERT(target, 1509);
        const std::string targetId{ target->uuid.empty() ? target->uuid : target->id };
        CCASSERT(!targetId.empty(), 1510);
        
        auto element = _hashForUpdates[targetId];
        if (element) {
            if (_updateHashLocked) {
                element->_entry->_markedForDeletion = true;
            }
            else {
                _removeUpdateFromHash(element->_entry);
            }
        }
    }
    void Scheduler::unscheduleAllForTarget(System* target) {
        CCASSERT(target, 1509);
        const std::string targetId{ target->uuid.empty() ? target->uuid : target->id };
        CCASSERT(!targetId.empty(), 1510);

        auto element = _hashForTimers[targetId];
        if (std::find(element->_timers.begin(), element->_timers.end(), element->_currentTimer) != element->_timers.end()
            && !element->_currentTimerSalvaged) {
            element->_currentTimerSalvaged = true;
        }
        for (auto i: element->_timers) {
            delete i;
        }
        element->_timers.clear();
        if (_currentTimer == element) {
            _currentTimerSalvaged = true;
        }
        else {
            _removeTimerFromHash(element);
        }

        unscheduleUpdate(target);
    }
    void Scheduler::unscheduleAll() {
        unscheduleAllWithMinPriority(Priority::SCHEDULER);
    }
    void Scheduler::unscheduleAllWithMinPriority(Priority minPriority) {
        for (auto element : _arrayForTimers) {
            unscheduleAllForTarget(element->_target);
        }

        uint32_t temp_size;
        ListEntry* entry;
        if (static_cast<uint32_t>(minPriority) < 0) {
            for (uint32_t i = 0; i < _updatesNegList.size();) {
                temp_size = _updatesNegList.size();
                entry = _updatesNegList[i];
                if (entry && entry->_priority >= minPriority) {
                    unscheduleUpdate(entry->_target);
                }
                if (temp_size == _updatesNegList.size()) {
                    i++;
                }
            }
        }
        if (static_cast<uint32_t>(minPriority) <= 0) {
            for (uint32_t i = 0; i < _updates0List.size();) {
                temp_size = _updates0List.size();
                entry = _updates0List[i];
                if (entry ) {
                    unscheduleUpdate(entry->_target);
                }
                if (temp_size == _updates0List.size()) {
                    i++;
                }
            }
        }

        for (uint32_t i = 0; i < _updatesPosList.size();) {
            temp_size = _updatesPosList.size();
            entry = _updatesPosList[i];
            if (entry && entry->_priority >= minPriority) {
                unscheduleUpdate(entry->_target);
            }
            if (temp_size == _updatesPosList.size()) {
                i++;
            }
        }


    }

    void Scheduler::pauseTarget(System* target) {
        CCASSERT(target, 1509);
        const std::string targetId{ target->uuid.empty() ? target->uuid : target->id };
        CCASSERT(!targetId.empty(), 1510);
        
        auto element = _hashForTimers.find(targetId)->second;
        element->_paused = true;

        auto elementUpdate = _hashForUpdates.find(targetId)->second;
        elementUpdate->_entry->_paused = true;
    }

    std::vector<System*> Scheduler::pauseAllTargets() {
        return pauseAllTargetsWithMinPriority(Priority::SCHEDULER);
    }
    std::vector<System*> Scheduler::pauseAllTargetsWithMinPriority(Priority minPriority) {
        std::vector<System*> idsWithSelectors;
        for (auto element : _arrayForTimers) {
            element->_paused = true;
            idsWithSelectors.push_back(element->_target);
        }
        //ListEntry* entry{nullptr};
        if (minPriority < Priority::LOW) {
            for (auto entry : _updatesNegList) {
                if (entry->_priority >= minPriority) {
                    entry->_paused = true;
                    idsWithSelectors.push_back(entry->_target);
                }
            }
        }
        if (minPriority <= Priority::LOW) {
            for (auto entry : _updates0List) {
                
                entry->_paused = true;
                idsWithSelectors.push_back(entry->_target);
                
            }
        }
        
        for (auto entry : _updatesPosList) {
            
            entry->_paused = true;
            idsWithSelectors.push_back(entry->_target);
        }
        return idsWithSelectors;
    }

} // namespace cc

