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

#include "core/DataView.h"

namespace cc {

#include "base/Macros.h"
#include "core/ArrayBuffer.h"

DataView::DataView(ArrayBuffer::Ptr buffer) : DataView(buffer, 0) {}

DataView::DataView(ArrayBuffer::Ptr buffer, uint32_t byteOffset)
: DataView(buffer, byteOffset, buffer ? buffer->byteLength() : 0) {}

DataView::DataView(ArrayBuffer::Ptr buffer, uint32_t byteOffset, uint32_t byteLength) {
    assign(buffer, byteOffset, byteLength);
}

void DataView::assign(ArrayBuffer::Ptr buffer) {
    assign(buffer, 0);
}

void DataView::assign(ArrayBuffer::Ptr buffer, uint32_t byteOffset) {
    assign(buffer, byteOffset, buffer ? buffer->byteLength() : 0);
}

void DataView::assign(ArrayBuffer::Ptr buffer, uint32_t byteOffset, uint32_t byteLength) {
    CC_ASSERT(buffer != nullptr);
    CC_ASSERT(byteLength > 0);
    _buffer     = buffer;
    _byteOffset = byteOffset;
    _byteEndPos = byteLength + byteOffset;
    CC_ASSERT(_byteEndPos <= buffer->_byteLength);

    _data = buffer->_data + byteOffset;
}

uint8_t DataView::getUint8(index_t offset) const {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos);

    return _data[offset];
}

uint16_t DataView::getUint16(index_t offset) const {
    offset += _byteOffset;
    CC_ASSERT(offset < (_byteEndPos - 1));

    return *reinterpret_cast<uint16_t *>(_data + offset);
}

uint32_t DataView::getUint32(index_t offset) const {
    offset += _byteOffset;
    CC_ASSERT(offset < (_byteEndPos - 3));

    return *reinterpret_cast<uint32_t *>(_data + offset);
}

int8_t DataView::getInt8(index_t offset) const {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos);

    return static_cast<int8_t>(_data[offset]);
}

int16_t DataView::getInt16(index_t offset) const {
    offset += _byteOffset;
    CC_ASSERT(offset < (_byteEndPos - 1));

    return *reinterpret_cast<int16_t *>(_data + offset);
}

int32_t DataView::getInt32(index_t offset) const {
    offset += _byteOffset;
    CC_ASSERT(offset < (_byteEndPos - 3));

    return *reinterpret_cast<int32_t *>(_data + offset);
}

float DataView::getFloat32(index_t offset) const {
    offset += _byteOffset;
    CC_ASSERT(offset < (_byteEndPos - 3));

    return *reinterpret_cast<float *>(_data + offset);
}

void DataView::setUint8(index_t offset, uint8_t value) {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos);

    _data[offset] = value;
}

void DataView::setUint16(index_t offset, uint16_t value) {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos - 1);

    *reinterpret_cast<uint16_t *>(_data + offset) = value;
}

void DataView::setUint32(index_t offset, uint32_t value) {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos - 3);

    *reinterpret_cast<uint32_t *>(_data + offset) = value;
}

void DataView::setInt8(index_t offset, int8_t value) {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos);

    *reinterpret_cast<int8_t *>(_data + offset) = value;
}

void DataView::setInt16(index_t offset, int16_t value) {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos - 1);

    *reinterpret_cast<int16_t *>(_data + offset) = value;
}

void DataView::setInt32(index_t offset, int32_t value) {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos - 3);

    *reinterpret_cast<int32_t *>(_data + offset) = value;
}

void DataView::setFloat32(index_t offset, float value) {
    offset += _byteOffset;
    CC_ASSERT(offset < _byteEndPos - 3);

    *(reinterpret_cast<float *>(_data + offset)) = value;
}

} // namespace cc