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

#include "base/Macros.h"
#include "base/TypeDef.h"
#include "core/ArrayBuffer.h"

namespace cc {

class DataView final {
public:
    DataView() = default;
    explicit DataView(ArrayBuffer::Ptr buffer);
    DataView(ArrayBuffer::Ptr buffer, uint32_t byteOffset);
    DataView(ArrayBuffer::Ptr buffer, uint32_t byteOffset, uint32_t byteLength);

    void assign(ArrayBuffer::Ptr buffer);
    void assign(ArrayBuffer::Ptr buffer, uint32_t byteOffset);
    void assign(ArrayBuffer::Ptr buffer, uint32_t byteOffset, uint32_t byteLength);

    uint8_t  getUint8(index_t offset) const;
    uint16_t getUint16(index_t offset) const;
    uint32_t getUint32(index_t offset) const;
    int8_t   getInt8(index_t offset) const;
    int16_t  getInt16(index_t offset) const;
    int32_t  getInt32(index_t offset) const;
    float    getFloat32(index_t offset) const;

    void setUint8(index_t offset, uint8_t value);
    void setUint16(index_t offset, uint16_t value);
    void setUint32(index_t offset, uint32_t value);
    void setInt8(index_t offset, int8_t value);
    void setInt16(index_t offset, int16_t value);
    void setInt32(index_t offset, int32_t value);
    void setFloat32(index_t offset, float value);

    inline const ArrayBuffer::Ptr &buffer() const { return _buffer; }

private:
    ArrayBuffer::Ptr _buffer{nullptr};
    uint8_t *        _data{nullptr};
    uint32_t         _byteOffset{0};
    uint32_t         _byteEndPos{0};

    CC_DISALLOW_COPY_MOVE_ASSIGN(DataView);
};

} // namespace cc
