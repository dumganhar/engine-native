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

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include <cstdint>

#include "base/TypeDef.h"
#include "core/ArrayBuffer.h"

#include "base/Value.h"
#include "math/Vec3.h"

namespace cc {

struct Error {
};

using HTMLElement = void *;

using Int8Array    = std::vector<int8_t>;
using Int16Array   = std::vector<int16_t>;
using Int32Array   = std::vector<int32_t>;
using Uint8Array   = std::vector<uint8_t>;
using Uint16Array  = std::vector<uint16_t>;
using Uint32Array  = std::vector<uint32_t>;
using Float32Array = std::vector<float>;
using Float64Array = std::vector<double>;

using TypedArray            = std::variant<std::monostate, Int8Array, Int16Array, Int32Array, Uint8Array, Uint16Array, Uint32Array, Float32Array, Float64Array>;
using TypedArrayElementType = std::variant<std::monostate, int8_t, int16_t, int32_t, uint8_t, uint16_t, uint32_t, float, double>;

using IndexArray = std::variant<Uint8Array, Uint16Array, Uint32Array>;

namespace typedarray {

template <typename T>
class TypedArrayRef {
public:
    TypedArrayRef(void *data, int32_t dataBytes, index_t byteOffset = CC_INVALID_INDEX, int32_t count = CC_INVALID_INDEX)
    : _data(static_cast<uint8_t *>(data)) //NOTE: weak reference
      ,
      _dataBytes(dataBytes) {
        _byteOffset = byteOffset == CC_INVALID_INDEX ? 0 : byteOffset;
        _count      = count == CC_INVALID_INDEX ? (dataBytes - _byteOffset) / sizeof(T) : count;
        CC_ASSERT(_byteOffset + _count * sizeof(T) <= dataBytes);
    }

    int32_t length() const {
        return _count;
    }

    T &operator[](index_t index) {
        CC_ASSERT(index < _count && index >= 0);
        return *(reinterpret_cast<T *>(_data + _byteOffset) + index);
    }

    const T &operator[](index_t index) const {
        CC_ASSERT(index < _count && index >= 0);
        return *(reinterpret_cast<T *>(_data + _byteOffset) + index);
    }

private:
    uint8_t *_data{nullptr};
    int32_t  _dataBytes{0};

    int32_t _byteOffset{0};
    int32_t _count{0};
};

using Int8ArrayRef    = TypedArrayRef<int8_t>;
using Int16ArrayRef   = TypedArrayRef<int16_t>;
using Int32ArrayRef   = TypedArrayRef<int32_t>;
using Uint8ArrayRef   = TypedArrayRef<uint8_t>;
using Uint16ArrayRef  = TypedArrayRef<uint16_t>;
using Uint32ArrayRef  = TypedArrayRef<uint32_t>;
using Float32ArrayRef = TypedArrayRef<float>;
using Float64ArrayRef = TypedArrayRef<double>;

int32_t getSize(const TypedArray &arr);
int32_t getBytesPerElement(const TypedArray &arr);

TypedArrayElementType get(const TypedArray &arr, index_t index);
bool                  set(TypedArray &arr, index_t index, const TypedArrayElementType &value);

float   castToFloat(const TypedArrayElementType &element);
int32_t castToInt32(const TypedArrayElementType &element);

class TypedArrayRange {
public:
    explicit TypedArrayRange(ArrayBuffer &ab)
    : _ab(ab) {}

    template <typename T>
    void updateRange(index_t byteOffset = CC_INVALID_INDEX, int32_t count = CC_INVALID_INDEX) {
        _byteOffset = byteOffset == CC_INVALID_INDEX ? 0 : byteOffset;
        _count      = count == CC_INVALID_INDEX ? (_ab.size() - _byteOffset) / sizeof(T) : count;
        CC_ASSERT(_byteOffset + _count * sizeof(T) <= _ab.size());
        _bytesPerElement = sizeof(T);
    }

    template <typename T>
    T &operator[](index_t index) {
        CC_ASSERT(index < _count && index >= 0);
        return *(reinterpret_cast<T *>(_ab.data() + _byteOffset) + index);
    }

    template <typename T>
    const T &operator[](index_t index) const {
        CC_ASSERT(index < _count && index >= 0);
        return *(reinterpret_cast<T *>(_ab.data() + _byteOffset) + index);
    }

    inline int32_t getCount() const {
        return _count;
    }

    inline int32_t getBytesPerElement() const { return _bytesPerElement; }

    void *getElement(index_t index) const {
        if (index >= _count) {
            return nullptr;
        }
        return (_ab.data() + _byteOffset) + index * _bytesPerElement;
    }

    bool copy(const TypedArrayRange &other) {
        if (_bytesPerElement == other._bytesPerElement) {
            if (_count >= other._count) {
                std::copy(other._ab.begin() + _byteOffset, other._ab.begin() + _byteOffset + _bytesPerElement * _count, _ab.begin() + _byteOffset);
                return true;
            }
        }

        return false;
    }

private:
    ArrayBuffer &_ab;
    int32_t      _byteOffset{0};
    int32_t      _count{0};
    int32_t      _bytesPerElement{0};
};

} // namespace typedarray

struct BoundingBox {
    Vec3 min;
    Vec3 max;
};

struct VertexIdChannel {
    uint32_t stream{0};
    uint32_t index{0};
};

struct NativeDep {
    std::string uuid;
    std::string ext;
    bool        __isNative__{false};

    explicit NativeDep() = default;

    explicit NativeDep(bool isNative_, const std::string &uuid_, const std::string &ext_)
    : uuid(uuid_), ext(ext_), __isNative__(isNative_), _isValid(true) {}

    inline bool isValid() const { return _isValid; }

private:
    bool _isValid{false};
};

} // namespace cc
