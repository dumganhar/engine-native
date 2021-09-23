/****************************************************************************
// References: https://github.com/pcgpcgpcg/testbeastclion/blob/b2b441b4642e68302166d98f42fc42c988132e90/utils/EventEmitter.hpp
// Modified by wanxiang.xie@cocos.com
****************************************************************************/
#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>

#include "base/Log.h"

namespace cc {

class EventEmitter {
public:
    uint32_t maxListeners{10};

    uint32_t listeners() const {
        return this->_listeners;
    }

    template <typename Callback>
    void on(const std::string &name, Callback cb);

    template <typename Callback>
    void once(const std::string &name, Callback cb) {
        this->on(name, cb);
        _events_once[name] = true;
    }

    void off();

    void off(const std::string &name);

    template <typename... Args>
    void emit(const std::string &name, Args... args);

    EventEmitter() = default;

    virtual ~EventEmitter() {
        _events.clear();
    }

private:
    std::map<std::string, void *> _events;
    std::map<std::string, bool>   _events_once;

    template <typename Callback>
    struct Traits : public Traits<decltype(&Callback::operator())> {
    };

    template <typename ClassType, typename R, typename... Args>
    struct Traits<R (ClassType::*)(Args...) const> {
        using fn = std::function<R(Args...)>;
    };

    template <typename Callback>
    typename Traits<Callback>::fn toFunction(Callback &cb) {
        return static_cast<typename Traits<Callback>::fn>(cb);
    }

    uint32_t _listeners{0};
};

template <typename Callback>
void EventEmitter::on(const std::string &name, Callback cb) {
    auto it = _events.find(name);
    if (it != _events.end()) {
        //        throw *new std::runtime_error("duplicate listener");
        CC_LOG_ERROR("duplicate listener on event (%s)", name.c_str());
    }

    if (++this->_listeners >= this->maxListeners) {
        std::cout
            << "warning: possible EventEmitter memory leak detected. "
            << this->_listeners
            << " listeners added. "
            << std::endl;
    };

    auto f        = toFunction(cb);
    auto fn       = new decltype(f)(toFunction(cb));
    _events[name] = static_cast<void *>(fn);
}

template <typename... Args>
void EventEmitter::emit(const std::string &name, Args... args) {
    auto it = _events.find(name);
    if (it != _events.end()) {
        auto *cb = _events.at(name);
        auto  fp = static_cast<std::function<void(Args...)> *>(cb);
        (*fp)(args...);
    }

    auto once = _events_once.find(name);
    if (once != _events_once.end()) {
        this->off(name);
    }
}

} // namespace cc
