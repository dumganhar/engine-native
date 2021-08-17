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
