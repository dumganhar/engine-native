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

#include "cocos/base/Any.h"
#include <functional>

namespace cc {

/**
 * @en
 * use to cache something
 *
 * @zh
 * 用于缓存某些内容
 *
 */
template <typename T>
class Cache {
public:
    /**
     * @en
     * Create a cache
     *
     * @zh
     * 创建一个 cache
     *
     * @param map - An object used to initialize
     *
     */
    explicit Cache(const Record<std::string, T> &map) {
        if (!map.empty()) {
            _map   = map;
            _count = static_cast<uint32_t>(map.size());
        }
    }
    
    Cache() = default;

    /**
     * @en
     * Add Key-Value to cache
     *
     * @zh
     * 增加键值对到缓存中
     *
     * @param key - The key
     * @param val - The value
     * @returns The value
     *
     * @example
     * var cache = new Cache();
     * cache.add('test', null);
     *
     */
    void add(const std::string &key, const T &val) {
        auto iter = _map.find(key);
        if (iter == _map.end()) {
            ++_count;
        }

        _map.emplace(key, val);
    }

    /**
     * @en
     * Get the cached content by key
     *
     * @zh
     * 通过 key 获取对应的 value
     *
     * @param key - The key
     * @returns The corresponding content
     *
     * @example
     * let cache = new Cache();
     * let test = cache.get('test');
     *
     */
    T get(const std::string &key) const {
        auto iter = _map.find(key);
        if (iter != _map.end()) {
            return iter.second;
        }
        return nullptr;
    }

    /**
     * @en
     * Check whether or not content exists by key
     *
     * @zh
     * 通过 Key 判断是否存在对应的内容
     *
     * @param key - The key
     * @returns True indicates that content of the key exists
     *
     * @example
     * var cache = new Cache();
     * var exist = cache.has('test');
     *
     */
    bool has(const std::string &key) const {
        return (_map.find(key) != _map.end());
    }

    /**
     * @en
     * Remove the cached content by key
     *
     * @zh
     * 通过 Key 移除对应的内容
     *
     * @param key - The key
     * @returns The removed content
     *
     * @example
     * var cache = new Cache();
     * var content = cache.remove('test');
     *
     */
    T remove(const std::string &key) {
        auto    iter = _map.find(key);
        const T ret  = nullptr;
        if (iter != _map.end()) {
            ret = _map.second;
            _map.erase(iter);
            --_count;
        }

        return ret;
    }

    /**
     * @en
     * Clear all content
     *
     * @zh
     * 清除所有内容
     *
     * @example
     * var cache = new Cache();
     * cache.clear();
     *
     */
    void clear() {
        if (_count != 0) {
            _map.clear();
            _count = 0;
        }
    }

    /**
     * @en
     * Enumerate all content and invoke function
     *
     * @zh
     * 枚举所有内容并执行方法
     *
     * @param func - Function to be invoked
     * @param func.val - The value
     * @param func.key - The corresponding key
     *
     * @example
     * var cache = new Cache();
     * cache.forEach((val, key) => console.log(key));
     *
     */
    void forEach(const std::function<void(T, const std::string &)> &func) {
        for (const auto &e : _map) {
            func(e.second, e.first);
        }
    }

    /**
     * @en
     * Enumerate all content to find one element which can fulfill condition
     *
     * @zh
     * 枚举所有内容，找到一个可以满足条件的元素
     *
     * @param predicate - The condition
     * @returns content
     *
     * @example
     * var cache = new Cache();
     * var val = cache.find((val, key) => key === 'test');
     *
     */
    T find(const std::function<bool(T, const std::string &)> &predicate) {
        for (const auto &e : _map) {
            if (predicate(e.second, e.first)) {
                return e.second;
            }
        }
        return nullptr;
    }

    /**
     * @en
     * The count of cached content
     *
     * @zh
     * 缓存数量
     *
     */
    inline uint32_t getCount() const {
        return _count;
    }

    /**
     * @en
     * Destroy this cache
     *
     * @zh
     * 销毁这个 cache
     *
     */
    void destroy() {
        _map.clear();
    }

protected:
    Record<std::string, T> _map;
    uint32_t               _count{0};
};

} // namespace cc
