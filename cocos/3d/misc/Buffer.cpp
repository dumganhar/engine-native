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

#include "3d/misc/Buffer.h"

namespace cc {

namespace {
Record<gfx::FormatType, std::string> _typeMap{
    {gfx::FormatType::UNORM, "Uint"},
    {gfx::FormatType::SNORM, "Int"},
    {gfx::FormatType::UINT, "Uint"},
    {gfx::FormatType::INT, "Int"},
    {gfx::FormatType::UFLOAT, "Float"},
    {gfx::FormatType::FLOAT, "Float"},
};

std::string _getDataViewType(const gfx::FormatInfo& info) {
    std::string type;
    auto        iter = _typeMap.find(info.type);
    if (iter != _typeMap.end()) {
        type = iter->second;
    } else {
        type = "Uint";
    }

    const uint32_t bytes = info.size / info.count * 8;
    return type + std::to_string(bytes);
}

} // namespace

using DataVariant       = std::variant<int32_t, float>;
using MapBufferCallback = std::function<DataVariant(const DataVariant& cur, uint32_t idx, const DataView& view)>;

DataView mapBuffer(DataView&                  target,
                   const MapBufferCallback&   callback,
                   std::optional<gfx::Format> aFormat,
                   std::optional<uint32_t>    aOffset,
                   std::optional<uint32_t>    aLength,
                   std::optional<uint32_t>    aStride,
                   DataView*                  out) {
    gfx::Format format = aFormat.has_value() ? aFormat.value() : gfx::Format::R32F;
    uint32_t    offset = aOffset.has_value() ? aOffset.value() : 0;
    uint32_t    length = aLength.has_value() ? aLength.value() : target.byteLength() - offset;
    uint32_t    stride = aStride.has_value() ? aStride.value() : 0;

    DataView dataView;
    if (out == nullptr) {
        out = &dataView;
        dataView.assign(target.buffer()->slice(target.byteOffset(), target.byteOffset() + target.byteLength()));
    }

    const auto& info = gfx::GFX_FORMAT_INFOS[static_cast<int32_t>(format)];
    if (stride == 0) {
        stride = info.size;
    }

    static const std::string setPrefix{"set"};
    static const std::string getPrefix{"get"};

    bool                 isFloat    = info.type == gfx::FormatType::FLOAT || info.type == gfx::FormatType::UFLOAT;
    DataView::IntWritter intWritter = nullptr;
    if (!isFloat) {
        intWritter = DataView::intWritterMap[setPrefix + _getDataViewType(info)];
    }

    DataView::ReaderVariant intReader;
    if (!isFloat) {
        intReader = DataView::intReaderMap[getPrefix + _getDataViewType(info)];
    }

    const uint32_t componentBytesLength = info.size / info.count;
    const uint32_t nSeg                 = std::floor(length / stride);

    for (uint32_t iSeg = 0; iSeg < nSeg; ++iSeg) {
        const uint32_t x = offset + stride * iSeg;
        for (uint32_t iComponent = 0; iComponent < info.count; ++iComponent) {
            const uint32_t y = x + componentBytesLength * iComponent;
            if (isFloat) {
                float cur = target.getFloat32(y);
                out->setFloat32(y, std::get<1>(callback(cur, iComponent, target)));
            } else {
                int32_t cur = target.readInt(intReader, y);
                // iComponent is usually more useful than y
                (target.*intWritter)(y, std::get<0>(callback(cur, iComponent, target)));
            }
        }
    }
    return dataView;
}

} // namespace cc