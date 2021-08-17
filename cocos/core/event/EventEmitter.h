/****************************************************************************
// References: https://github.com/pcgpcgpcg/testbeastclion/blob/b2b441b4642e68302166d98f42fc42c988132e90/utils/EventEmitter.hpp
// Modified by wanxiang.xie@cocos.com
****************************************************************************/

#pragma once
#include <iostream>
#include <stdexcept>
#include <functional>
#include <typeinfo>
#include <string>
#include <map>

class EventEmitter {
public:
    uint32_t maxListeners = 10;

    uint32_t listeners() const {
        return this->_listeners;
    }

    template <typename Callback>
    void on(const std::string& name, Callback cb);

    template <typename Callback>
    void once(const std::string& name, Callback cb) {
        this->on(name, cb);
        _events_once[name] = true;
    }

    void off();

    void off(const std::string& name);

    template <typename ...Args>
    void emit(const std::string& name, Args... args);

    EventEmitter() = default;

    ~EventEmitter() {
        _events.clear();
    }

private:
    std::map<std::string, void*> _events;
    std::map<std::string, bool> _events_once;

    template <typename Callback>
    struct Traits : public Traits<decltype(&Callback::operator())> {
    };

    template <typename ClassType, typename R, typename... Args>
    struct Traits<R(ClassType::*)(Args...) const> {
        using fn = std::function<R (Args...)>;
    };

    template <typename Callback>
    typename Traits<Callback>::fn toFunction(Callback& cb) {
        return static_cast<typename Traits<Callback>::fn>(cb);
    }

    uint32_t _listeners = 0;
};
