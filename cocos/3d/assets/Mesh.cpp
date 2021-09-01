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

#include "3d/assets/Mesh.h"

namespace cc {

namespace {

uint32_t getOffset(const gfx::AttributeList &attributes, index_t attributeIndex) {
    uint32_t result = 0;
    for (index_t i = 0; i < attributeIndex; ++i) {
        const auto &attribute = attributes[i];
        result += gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attribute.format)].size;
    }
    return result;
}
//
//const { isLittleEndian } = sys;
//
uint32_t getComponentByteLength(gfx::Format format) {
    const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    return info.size / info.count;
}

//using DataReaderCallback = std::function<TypedArray(uint32_t)>;
//
//DataReaderCallback getReader(dataView: DataView, gfx::Format format) {
//    const info = FormatInfos[format];
//    const stride = info.size / info.count;
//
//    switch (info.type) {
//    case FormatType.UNORM: {
//        switch (stride) {
//        case 1: return (offset: number) => dataView.getUint8(offset);
//        case 2: return (offset: number) => dataView.getUint16(offset, isLittleEndian);
//        case 4: return (offset: number) => dataView.getUint32(offset, isLittleEndian);
//        default:
//        }
//        break;
//    }
//    case FormatType.SNORM: {
//        switch (stride) {
//        case 1: return (offset: number) => dataView.getInt8(offset);
//        case 2: return (offset: number) => dataView.getInt16(offset, isLittleEndian);
//        case 4: return (offset: number) => dataView.getInt32(offset, isLittleEndian);
//        default:
//        }
//        break;
//    }
//    case FormatType.INT: {
//        switch (stride) {
//        case 1: return (offset: number) => dataView.getInt8(offset);
//        case 2: return (offset: number) => dataView.getInt16(offset, isLittleEndian);
//        case 4: return (offset: number) => dataView.getInt32(offset, isLittleEndian);
//        default:
//        }
//        break;
//    }
//    case FormatType.UINT: {
//        switch (stride) {
//        case 1: return (offset: number) => dataView.getUint8(offset);
//        case 2: return (offset: number) => dataView.getUint16(offset, isLittleEndian);
//        case 4: return (offset: number) => dataView.getUint32(offset, isLittleEndian);
//        default:
//        }
//        break;
//    }
//    case FormatType.FLOAT: {
//        return (offset: number) => dataView.getFloat32(offset, isLittleEndian);
//    }
//    default:
//    }
//
//    return DataReaderCallback{};
//}
//
//function getWriter (dataView: DataView, format: Format) {
//    const info = FormatInfos[format];
//    const stride = info.size / info.count;
//
//    switch (info.type) {
//    case FormatType.UNORM: {
//        switch (stride) {
//        case 1: return (offset: number, value: number) => dataView.setUint8(offset, value);
//        case 2: return (offset: number, value: number) => dataView.setUint16(offset, value, isLittleEndian);
//        case 4: return (offset: number, value: number) => dataView.setUint32(offset, value, isLittleEndian);
//        default:
//        }
//        break;
//    }
//    case FormatType.SNORM: {
//        switch (stride) {
//        case 1: return (offset: number, value: number) => dataView.setInt8(offset, value);
//        case 2: return (offset: number, value: number) => dataView.setInt16(offset, value, isLittleEndian);
//        case 4: return (offset: number, value: number) => dataView.setInt32(offset, value, isLittleEndian);
//        default:
//        }
//        break;
//    }
//    case FormatType.INT: {
//        switch (stride) {
//        case 1: return (offset: number, value: number) => dataView.setInt8(offset, value);
//        case 2: return (offset: number, value: number) => dataView.setInt16(offset, value, isLittleEndian);
//        case 4: return (offset: number, value: number) => dataView.setInt32(offset, value, isLittleEndian);
//        default:
//        }
//        break;
//    }
//    case FormatType.UINT: {
//        switch (stride) {
//        case 1: return (offset: number, value: number) => dataView.setUint8(offset, value);
//        case 2: return (offset: number, value: number) => dataView.setUint16(offset, value, isLittleEndian);
//        case 4: return (offset: number, value: number) => dataView.setUint32(offset, value, isLittleEndian);
//        default:
//        }
//        break;
//    }
//    case FormatType.FLOAT: {
//        return (offset: number, value: number) => dataView.setFloat32(offset, value, isLittleEndian);
//    }
//    default:
//    }
//
//    return null;
//}

} // namespace

} // namespace cc
