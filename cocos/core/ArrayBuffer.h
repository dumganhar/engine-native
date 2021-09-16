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

#include <memory>
#include "base/Macros.h"

namespace cc {

//class ArrayBufferView;

class ArrayBuffer final {
public:
    using Ptr = std::shared_ptr<ArrayBuffer>;

    explicit ArrayBuffer(uint32_t length) : _byteLength{length} {
        _data = static_cast<uint8_t*>(malloc(length));
    }
    
    ~ArrayBuffer() {
        free(_data);
    }
    
    inline uint32_t byteLength() const { return _byteLength; }
    
    // Just use it to copy data. Use TypedArray to get/set data.
    const uint8_t * getData() const { return _data; }
    
private:
    uint8_t *_data{nullptr};
    uint32_t _byteLength{0};
    
    template<class T> friend class TypedArrayTemp;
    friend class DataView;
    
    CC_DISALLOW_COPY_MOVE_ASSIGN(ArrayBuffer);
};

//template <typename T>
//class ArrayBufferView final {
//public:
//    using value_type      = T;
//    using reference       = value_type &;
//    using const_reference = const value_type &;
//
//    explicit ArrayBufferView(ArrayBuffer &ab) : _ab(ab) {}
//
//    const_reference operator[](index_t index) const {
//        return at(index);
//    }
//
//    reference operator[](index_t index) {
//        return at(index);
//    }
//
//    const_reference at(index_t i) const {
//        CC_ASSERT(i < size());
//        return *(static_cast<T *>(_ab.data()) + i);
//    }
//
//    reference at(index_t i) {
//        CC_ASSERT(i < size());
//        return *(static_cast<T *>(_ab.data()) + i);
//    }
//
//    void set(index_t i, const_reference value) {
//        CC_ASSERT(i < size());
//        *(static_cast<T *>(_ab.data()) + i) = value;
//    }
//
//    int32_t size() const {
//        return static_cast<int32_t>(_ab.size() / sizeof(T));
//    }
//
//private:
//    ArrayBuffer &_ab;
//};

} // namespace cc
