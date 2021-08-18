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

#include <functional>
#include <cstdint>

namespace cc {

/**
 * @en
 * Cached array is a data structure for objects cache, it's designed for persistent data.
 * Its content array length will keep grow.
 * @zh
 * 适用于对象缓存的数组类型封装，一般用于不易被移除的常驻数据。
 * 它的内部数组长度会持续增长，不会减少。
 */
template <typename T>
class CachedArray final {
public:
    using CompareFn = std::function<int32_t(const T &, const T &)>;

    explicit CachedArray(uint32_t length);

    /**
     * @param length Initial length
     * @param compareFn Comparison function for sorting
     */
    CachedArray(uint32_t length, const CompareFn &compareFn);

    /**
     * @en
     * Push an element to the end of the array
     * @zh
     * 向数组末尾添加一个元素
     * @param item The item to be added
     */
    void push(const T &item);

    /**
     * @en
     * Pop the last element in the array. The [[length]] will reduce, but the internal array will keep its size.
     * @zh
     * 弹出数组最后一个元素，CachedArray 的 [[length]] 会减少，但是内部数组的实际长度不变
     * @return The last element.
     */
    const T &pop() const;
    T &      pop();

    /**
     * @en
     * Get the element at the specified index of the array
     * @zh
     * 得到数组中指定位置的元素
     * @param idx The index of the requested element
     * @return The element at given index
     */
    const T &get(uint32_t idx) const;
    T &      get(uint32_t idx);

    /**
     * @en
     * Clear the cache. The [[length]] will be set to 0, but the internal array will keep its size.
     * @zh
     * 清空数组所有元素。[[length]] 会被设为 0，但内部数组的实际长度不变
     */
    void clear();

    /**
     * @en
     * Clear the cache. The [[length]] will be set to 0, and clear the internal array.
     * @zh
     * 清空数组所有元素。[[length]] 会被设为 0，并且清空内部数组
     */
    void destroy();

    /**
     * @en
     * Sort the existing elements in cache
     * @zh
     * 排序所有现有元素
     */
    void sort();

    /**
     * @en
     * Add all elements of a given array to the end of the current array
     * @zh
     * 添加一个指定数组中的所有元素到当前数组末尾
     * @param array The given array to be appended
     */
    void concat(const std::vector<T> &array);

    /**
     * @en Delete the element at the specified location and move the last element to that location.
     * @zh 删除指定位置的元素并将最后一个元素移动至该位置。
     * @param idx The index of the element to be deleted
     */
    void fastRemove(uint32_t idx);

    /**
     * @en Returns the first index at which a given element can be found in the array.
     * @zh 返回在数组中可以找到一个给定元素的第一个索引。
     * @param val The element
     */
    int32_t indexOf(const T &val);

public:
    std::vector<T> _array;
    uint32_t       _length{0};

private:
    CompareFn _compareFn{nullptr};
};

} // namespace cc
