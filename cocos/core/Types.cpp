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

#include "core/Types.h"

namespace cc {

namespace typedarray {

int32_t getSize(const TypedArray &arr) {
#define TYPEDARRAY_GET_SIZE(type)                          \
    if (auto *p = std::get_if<type>(&arr); p != nullptr) { \
        return p->size();                                  \
    }

    TYPEDARRAY_GET_SIZE(Float32Array)
    TYPEDARRAY_GET_SIZE(Uint32Array)
    TYPEDARRAY_GET_SIZE(Uint16Array)
    TYPEDARRAY_GET_SIZE(Uint8Array)
    TYPEDARRAY_GET_SIZE(Int32Array)
    TYPEDARRAY_GET_SIZE(Int16Array)
    TYPEDARRAY_GET_SIZE(Int8Array)
    TYPEDARRAY_GET_SIZE(Float64Array)

#undef TYPEDARRAY_GET_SIZE
    return 0;
}

int32_t getBytesPerElement(const TypedArray &arr) {
#define TYPEDARRAY_GET_BYTES_PER_ELEMENT(type, retVal)     \
    if (auto *p = std::get_if<type>(&arr); p != nullptr) { \
        return (retVal);                                   \
    }

    TYPEDARRAY_GET_BYTES_PER_ELEMENT(Float32Array, 4)
    TYPEDARRAY_GET_BYTES_PER_ELEMENT(Uint32Array, 4)
    TYPEDARRAY_GET_BYTES_PER_ELEMENT(Uint16Array, 2)
    TYPEDARRAY_GET_BYTES_PER_ELEMENT(Uint8Array, 1)
    TYPEDARRAY_GET_BYTES_PER_ELEMENT(Int32Array, 4)
    TYPEDARRAY_GET_BYTES_PER_ELEMENT(Int16Array, 2)
    TYPEDARRAY_GET_BYTES_PER_ELEMENT(Int8Array, 1)
    TYPEDARRAY_GET_BYTES_PER_ELEMENT(Float64Array, 8)

#undef TYPEDARRAY_GET_BYTES_PER_ELEMENT
    return 0;
}

TypedArrayElementType get(const TypedArray &arr, index_t index) {
#define TYPEDARRAY_GET(type)                               \
    if (auto *p = std::get_if<type>(&arr); p != nullptr) { \
        if (index >= 0 && index < p->size()) {             \
            return p->at(index);                           \
        }                                                  \
    }

    TYPEDARRAY_GET(Float32Array)
    TYPEDARRAY_GET(Uint32Array)
    TYPEDARRAY_GET(Uint16Array)
    TYPEDARRAY_GET(Uint8Array)
    TYPEDARRAY_GET(Int32Array)
    TYPEDARRAY_GET(Int16Array)
    TYPEDARRAY_GET(Int8Array)
    TYPEDARRAY_GET(Float64Array)

#undef TYPEDARRAY_GET

    return {};
}

bool set(TypedArray &arr, index_t index, const TypedArrayElementType &value) {
#define TYPEDARRAY_SET(type)                                          \
    if (auto *p = std::get_if<type>(&arr); p != nullptr) {            \
        if (index >= 0 && index < p->size()) {                        \
            if (auto *q = std::get_if<float>(&value); q != nullptr) { \
                (*p)[index] = *q;                                     \
                return true;                                          \
            }                                                         \
        }                                                             \
    }

    TYPEDARRAY_SET(Float32Array)
    TYPEDARRAY_SET(Uint32Array)
    TYPEDARRAY_SET(Uint16Array)
    TYPEDARRAY_SET(Uint8Array)
    TYPEDARRAY_SET(Int32Array)
    TYPEDARRAY_SET(Int16Array)
    TYPEDARRAY_SET(Int8Array)
    TYPEDARRAY_SET(Float64Array)

#undef TYPEDARRAY_SET

    return false;
}

float castToFloat(const TypedArrayElementType &element) {
#define CAST_TO_FLOAT(type)                                    \
    if (auto *p = std::get_if<type>(&element); p != nullptr) { \
        return static_cast<float>(*p);                         \
    }

    CAST_TO_FLOAT(float)
    CAST_TO_FLOAT(uint32_t)
    CAST_TO_FLOAT(uint16_t)
    CAST_TO_FLOAT(uint8_t)
    CAST_TO_FLOAT(int32_t)
    CAST_TO_FLOAT(int16_t)
    CAST_TO_FLOAT(int8_t)
    CAST_TO_FLOAT(double)

    return 0.F;
}

int32_t castToInt32(const TypedArrayElementType &element) {
#define CAST_TO_INT32(type)                                    \
    if (auto *p = std::get_if<type>(&element); p != nullptr) { \
        return static_cast<int32_t>(*p);                       \
    }

    CAST_TO_INT32(float)
    CAST_TO_INT32(int32_t)
    CAST_TO_INT32(uint32_t)
    CAST_TO_INT32(uint16_t)
    CAST_TO_INT32(uint8_t)
    CAST_TO_INT32(int16_t)
    CAST_TO_INT32(int8_t)
    CAST_TO_INT32(double)

    return 0;
}

} // namespace typedarray

} // namespace cc
