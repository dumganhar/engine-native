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

#include "base/TypeDef.h"
#include "core/asset-manager/ICache.h"

#include "cocos/base/Any.h"
#include <functional>

namespace cc {

//cjh How to implement ES6 WeakRef in C++: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WeakRef
template <typename T>
class WeakRef {
public:
    WeakRef(T obj) {}
    T deref() {} //cjh How to implement deref?
};

template <typename T>
class WeakCache : public ICache<T> {
public:
    explicit WeakCache(const Record<std::string, T> &map) : ICache<T>() {
        if (map) {
            for (const auto &e : map) {
                _weakMap[e.first] = new WeakRef<T>(e.second);
            }
        }
    }

    ~WeakCache() {
        destroy();
    }

    void add(const std::string &key, T val) {
        _weakMap[key] = new WeakRef<T>(val);
    }

    bool has(const std::string &key) {
        bool found = false;
        auto iter  = _weakMap.find(key);
        if (iter != _weakMap.end() && iter.second->deref() != nullptr) {
            found = true;
        }
        return found;
    }

    T get(const std::string &key) {
        bool found = false;
        T    ret   = nullptr;
        auto iter  = _weakMap.find(key);
        if (iter != _weakMap.end() && iter.second->deref() != nullptr) {
            found = true;
        }

        if (found) {
            ret = iter.second;
        }
        return ret;
    }

    T remove(const std::string &key) {
        T    ret  = nullptr;
        auto iter = _weakMap.find(key);
        if (iter != _weakMap.end()) {
            T val = iter.second;
            _weakMap.erase(iter);
            delete val;
            ret = val->deref();
        }

        return ret;
    }

    void clear() {
        destroy(); //cjh clear & destroy is the same ?
    }

    void forEach(const std::function<void(T, const std::string &)> &func) {
        for (const auto &key : _weakMap) {
            const auto &val = get(key);
            if (val) {
                func(val, key);
            }
        }
    }

    T find(const std::function<bool(T, const std::string &)> &predicate) {
        for (const auto e : _weakMap) {
            const auto &key = e.first;
            const auto &val = get(key);
            if (val && predicate(val, key)) {
                return _weakMap[key].deref();
            }
        }
        return nullptr;
    }

    uint32_t getCount() const {
        uint32_t count = 0;
        for (const auto &key : _weakMap) {
            const auto &val = get(key);
            if (val != nullptr && val->deref() != nullptr) {
                ++count;
            }
        }
        return count;
    }

    void destroy() {
        for (const auto &e : _weakMap) {
            delete e.second;
        }
        _weakMap.clear();
    }

protected:
    Record<std::string, WeakRef<T>> _weakMap;
};

} // namespace cc
