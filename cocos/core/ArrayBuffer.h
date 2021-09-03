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

#include <vector>

#include "base/Macros.h"
#include "base/TypeDef.h"

namespace cc {

using ArrayBuffer = std::vector<uint8_t>;

template <typename T>
class ArrayBufferView final {
public:
    using value_type      = T;
    using reference       = value_type &;
    using const_reference = const value_type &;

    explicit ArrayBufferView(ArrayBuffer &ab) : _ab(ab) {}

    const_reference operator[](index_t index) const {
        return at(index);
    }

    reference operator[](index_t index) {
        return at(index);
    }

    const_reference at(index_t i) const {
        CC_ASSERT(index < size());
        return *(static_cast<T *>(_ab.data()) + i);
    }

    reference at(index_t i) {
        CC_ASSERT(index < size());
        return *(static_cast<T *>(_ab.data()) + i);
    }

    void set(index_t i, const_reference value) {
        CC_ASSERT(index < size());
        *(static_cast<T *>(_ab.data()) + i) = value;
    }

    int32_t size() const {
        CC_ASSERT(_ab != nullptr);
        return static_cast<int32_t>(_ab.size() / sizeof(T));
    }

private:
    ArrayBuffer &_ab;
};

class DataView final {
public:
    explicit DataView(ArrayBuffer &ab) {
        _buffer     = ab.data();
        _byteLength = ab.size();
    }

    explicit DataView(ArrayBuffer &ab, uint32_t byteOffset) {
        CC_ASSERT(byteOffset < ab.size());
        _buffer     = ab.data() + byteOffset;
        _byteLength = ab.size() - byteOffset;
    }

    explicit DataView(ArrayBuffer &ab, uint32_t byteOffset, uint32_t byteLength) {
        CC_ASSERT(byteOffset < ab.size());
        CC_ASSERT((byteLength + byteOffset) < ab.size());
        _buffer     = ab.data() + byteOffset;
        _byteLength = byteLength;
    }

    uint8_t getUint8(index_t offset) const {
        CC_ASSERT(offset < _byteLength);
        return _buffer[offset];
    }

    uint16_t getUint16(index_t offset) const {
        CC_ASSERT(offset < (_byteLength - 1));
        return *reinterpret_cast<uint16_t *>(&_buffer[offset]);
    }

    uint32_t getUint32(index_t offset) const {
        CC_ASSERT(offset < (_byteLength - 3));
        return *reinterpret_cast<uint32_t *>(&_buffer[offset]);
    }

    int8_t getInt8(index_t offset) const {
        CC_ASSERT(offset < _byteLength);
        return static_cast<int8_t>(_buffer[offset]);
    }

    int16_t getInt16(index_t offset) const {
        CC_ASSERT(offset < (_byteLength - 1));
        return *reinterpret_cast<int16_t *>(&_buffer[offset]);
    }

    int32_t getInt32(index_t offset) const {
        CC_ASSERT(offset < (_byteLength - 3));
        return *reinterpret_cast<int32_t *>(&_buffer[offset]);
    }

    float getFloat32(index_t offset) const {
        CC_ASSERT(offset < (_byteLength - 3));
        return *reinterpret_cast<float *>(&_buffer[offset]);
    }

    void setUint8(index_t offset, uint8_t value) {
        CC_ASSERT(offset < _byteLength);
        _buffer[offset] = value;
    }

    void setUint16(index_t offset, uint16_t value) {
        CC_ASSERT(offset < _byteLength - 1);
        *reinterpret_cast<uint16_t *>(&_buffer[offset]) = value;
    }

    void setUint32(index_t offset, uint32_t value) {
        CC_ASSERT(offset < _byteLength - 3);
        *reinterpret_cast<uint32_t *>(&_buffer[offset]) = value;
    }

    void setInt8(index_t offset, int8_t value) {
        CC_ASSERT(offset < _byteLength);
        *reinterpret_cast<int8_t *>(&_buffer[offset]) = value;
    }

    void setInt16(index_t offset, int16_t value) {
        CC_ASSERT(offset < _byteLength - 1);
        *reinterpret_cast<int16_t *>(&_buffer[offset]) = value;
    }

    void setInt32(index_t offset, int32_t value) {
        CC_ASSERT(offset < _byteLength - 3);
        *reinterpret_cast<int32_t *>(&_buffer[offset]) = value;
    }

    void setFloat32(index_t offset, float value) {
        CC_ASSERT(offset < _byteLength - 3);
        *reinterpret_cast<float *>(&_buffer[offset]) = value;
    }

private:
    uint8_t *_buffer{nullptr};
    uint32_t _byteLength{0};
};

} // namespace cc
