#pragma once
#include <iostream>
#include <stdexcept>
#include <functional>
#include <typeinfo>
#include <string>
#include <map>

class EventEmitter {
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
    typename Traits<Callback>::fn
        to_function(Callback& cb) {

        return static_cast<typename Traits<Callback>::fn>(cb);
    }

    int _listeners = 0;

public:
    int maxListeners = 10;

    int listeners() const {
        return this->_listeners;
    }

    template <typename Callback>
    void on(const std::string& name, Callback cb) {

        auto it = _events.find(name);
        if (it != _events.end()) {
            throw *new std::runtime_error("duplicate listener");
        }

        if (++this->_listeners >= this->maxListeners) {
            std::cout
                << "warning: possible EventEmitter memory leak detected. "
                << this->_listeners
                << " listeners added. "
                << std::endl;
        };

        auto f = to_function(cb);
        auto fn = new decltype(f)(to_function(cb));
        _events[name] = static_cast<void*>(fn);
    }

    template <typename Callback>
    void once(const std::string& name, Callback cb) {
        this->on(name, cb);
        _events_once[name] = true;
    }

    void off() {
        _events.clear();
        _events_once.clear();
        this->_listeners = 0;
    }

    void off(const std::string& name) {

        auto it = _events.find(name);

        if (it != _events.end()) {
            _events.erase(it);
            this->_listeners--;

            auto once = _events_once.find(name);
            if (once != _events_once.end()) {
                _events_once.erase(once);
            }
        }
    }

    template <typename ...Args>
    void emit(const std::string& name, Args... args) {

        auto it = _events.find(name);
        if (it != _events.end()) {

            auto *cb = _events.at(name);
            auto fp = static_cast<std::function<void(Args...)>*>(cb);
            (*fp)(args...);
        }

        auto once = _events_once.find(name);
        if (once != _events_once.end()) {
            this->off(name);
        }
    }

    EventEmitter() = default;

    ~EventEmitter() {
        _events.clear();
    }
};
