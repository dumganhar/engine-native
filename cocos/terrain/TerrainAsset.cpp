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
#include "terrain/TerrainAsset.h"
#include "core/assets/Texture2D.h"

namespace cc {

class TerrainBuffer final {
public:
    TerrainBuffer();
    ~TerrainBuffer();

    void reserve(int32_t size);
    void assign(const Uint8Array &buff);

    void writeInt8(int8_t value);
    void writeInt16(int16_t value);
    void writeInt32(int32_t value);
    void writeInt32Array(const int32_t *value, int32_t count);

    void writeFloat32(float value);
    void writeFloat32Array(const float *value, int32_t count);
    void writeString(const std::string &value);

    int8_t  readInt8();
    int16_t readInt16();
    int32_t readInt32();
    void    readInt32Array(int32_t *value, int32_t count);

    float readFloat32();
    void  readFloat32Array(float *value, int32_t count);

    std::string readString();

    inline const Uint8Array &getBuffer() const { return _buffer; }
    inline int32_t           getLength() const { return _length; }

private:
    int32_t    _length{0};
    Uint8Array _buffer{2048};
    DataView   _buffView;
    int32_t    _seekPos{0};
};

TerrainBuffer::TerrainBuffer() {
    _buffView.assign(_buffer.buffer());
}

TerrainBuffer::~TerrainBuffer() {
}

void TerrainBuffer::reserve(int32_t size) {
    if (_buffer.byteLength() > size) {
        return;
    }

    uint32_t capacity = _buffer.byteLength();
    while (capacity < size) {
        capacity += capacity;
    }

    Uint8Array temp(capacity);
    for (int32_t i = 0; i < _length; ++i) {
        temp[i] = _buffer[i];
    }

    _buffer = temp;
    _buffView.assign(_buffer.buffer());
}

void TerrainBuffer::assign(const Uint8Array &buff) {
    _buffer  = buff;
    _length  = buff.length();
    _seekPos = buff.byteOffset();
    _buffView.assign(_buffer.buffer());
}

void TerrainBuffer::writeInt8(int8_t value) {
    reserve(_length + 1);

    _buffView.setInt8(_length, value);
    _length += 1;
}

void TerrainBuffer::writeInt16(int16_t value) {
    reserve(_length + 2);

    _buffView.setInt16(_length, value);
    _length += 2;
}

void TerrainBuffer::writeInt32(int32_t value) {
    reserve(_length + 4);

    _buffView.setInt32(_length, value);
    _length += 4;
}

void TerrainBuffer::writeInt32Array(const int32_t *value, int32_t count) {
    reserve(_length + 4 * count);

    for (int32_t i = 0; i < count; ++i) {
        _buffView.setInt32(_length + i * 4, value[i]);
    }
    _length += 4 * count;
}

void TerrainBuffer::writeFloat32(float value) {
    reserve(_length + 4);

    _buffView.setFloat32(_length, value);
    _length += 4;
}

void TerrainBuffer::writeFloat32Array(const float *value, int32_t count) {
    reserve(_length + 4 * count);

    for (int32_t i = 0; i < count; ++i) {
        _buffView.setFloat32(_length + i * 4, value[i]);
    }
    _length += 4 * count;
}

void TerrainBuffer::writeString(const std::string &value) {
    reserve(_length + value.length() + 4);

    _buffView.setInt32(_length, value.length());
    for (int32_t i = 0; i < value.length(); ++i) {
        _buffView.setInt8(_length + 4 + i, value[i]);
    }
    _length += value.length() + 4;
}

int8_t TerrainBuffer::readInt8() {
    const int8_t value = _buffView.getInt8(_seekPos);
    _seekPos += 1;
    return value;
}

int16_t TerrainBuffer::readInt16() {
    const int16_t value = _buffView.getInt16(_seekPos);
    _seekPos += 2;
    return value;
}

int32_t TerrainBuffer::readInt32() {
    const int32_t value = _buffView.getInt32(_seekPos);
    _seekPos += 4;
    return value;
}

void TerrainBuffer::readInt32Array(int32_t *value, int32_t count) {
    for (int32_t i = 0; i < count; ++i) {
        value[i] = _buffView.getInt32(_seekPos + i * 4);
    }
    _seekPos += 4 * count;
}

float TerrainBuffer::readFloat32() {
    const float value = _buffView.getFloat32(_seekPos);
    _seekPos += 4;
    return value;
}

void TerrainBuffer::readFloat32Array(float *value, int32_t count) {
    for (int32_t i = 0; i < count; ++i) {
        value[i] = _buffView.getFloat32(_seekPos + i * 4);
    }
    _seekPos += 4 * count;
}

std::string TerrainBuffer::readString() {
    const int32_t length = readInt32();

    std::string value;
    for (int32_t i = 0; i < length; ++i) {
        value += static_cast<char>(readInt8());
    }

    return value;
}

//

std::any TerrainAsset::getNativeAsset() const {
    return _data.buffer();
}

void TerrainAsset::setNativeAsset(const std::any &obj) {
    auto value = std::any_cast<ArrayBuffer::Ptr>(obj);
    if (!_data.empty() && _data.byteLength() == value->byteLength()) {
        _data.set(Uint8Array{value});
    } else {
        _data = Uint8Array{value};
    }

    loadNativeData(_data);
}

int32_t TerrainAsset::getLayer(int32_t xBlock, int32_t yBlock, int32_t layerId) const {
    const int32_t blockId = yBlock * _blockCount[0] + xBlock;
    const int32_t index   = blockId * 4 + layerId;

    if (xBlock < _blockCount[0] && yBlock < _blockCount[1] && index < _layerBuffer.size()) {
        return _layerBuffer[index];
    }

    return -1;
}

float TerrainAsset::getHeight(int32_t i, int32_t j) const {
    const int32_t vertexCountX = _blockCount[0] * TERRAIN_BLOCK_TILE_COMPLEXITY + 1;
    return (_heights[j * vertexCountX + i] - TERRAIN_HEIGHT_BASE) * TERRAIN_HEIGHT_FACTORY;
}

int32_t TerrainAsset::getVertexCountI() const {
    if (_blockCount.size() < 1) {
        return 0;
    }
    return _blockCount[0] * TERRAIN_BLOCK_TILE_COMPLEXITY + 1;
}

int32_t TerrainAsset::getVertexCountJ() const {
    if (_blockCount.size() < 2) {
        return 0;
    }
    return _blockCount[1] * TERRAIN_BLOCK_TILE_COMPLEXITY + 1;
}

bool TerrainAsset::loadNativeData(const Uint8Array &_nativeData) {
    if (_nativeData.length() == 0) {
        return false;
    }

    TerrainBuffer stream;
    stream.assign(_nativeData);

    // version
    _version = stream.readInt32();
    if (_version == TERRAIN_DATA_VERSION_DEFAULT) {
        return true;
    }

    if (_version != TERRAIN_DATA_VERSION && _version != TERRAIN_DATA_VERSION2 && _version != TERRAIN_DATA_VERSION3 && _version != TERRAIN_DATA_VERSION4 && _version != TERRAIN_DATA_VERSION5) {
        return false;
    }

    // geometry info
    _tileSize = stream.readFloat32();
    stream.readInt32Array(_blockCount.data(), _blockCount.size());
    _weightMapSize = stream.readInt16();
    _lightMapSize  = stream.readInt16();

    // heights
    const int32_t heightBufferSize = stream.readInt32();
    _heights.reset(heightBufferSize);
    for (uint32_t i = 0; i < _heights.length(); ++i) {
        _heights[i] = stream.readInt16();
    }

    // weights
    const int32_t WeightBufferSize = stream.readInt32();
    _weights.reset(WeightBufferSize);
    for (uint32_t i = 0; i < _weights.length(); ++i) {
        _weights[i] = stream.readInt8();
    }

    // layer buffer
    if (_version >= TERRAIN_DATA_VERSION2) {
        const int32_t layerBufferSize = stream.readInt32();
        _layerBuffer.resize(layerBufferSize);
        for (size_t i = 0; i < _layerBuffer.size(); ++i) {
            _layerBuffer[i] = stream.readInt16();
        }
    }

    // layer infos
    if (_version >= TERRAIN_DATA_VERSION3) {
        const int32_t layerInfoSize = stream.readInt32();
        _layerBinaryInfos.resize(layerInfoSize);
        for (size_t i = 0; i < _layerBinaryInfos.size(); ++i) {
            _layerBinaryInfos[i].slot     = stream.readInt32();
            _layerBinaryInfos[i].tileSize = stream.readFloat32();

            _layerBinaryInfos[i].detailMapId = stream.readString();
            if (_version >= TERRAIN_DATA_VERSION4) {
                _layerBinaryInfos[i].normalMapId = stream.readString();
                _layerBinaryInfos[i].roughness   = stream.readFloat32();
                _layerBinaryInfos[i].metallic    = stream.readFloat32();
            }
        }
    }

    return true;
}

Uint8Array TerrainAsset::exportNativeData() const {
    TerrainBuffer stream;

    // version
    stream.writeInt32(TERRAIN_DATA_VERSION5);

    // geometry info
    stream.writeFloat32(_tileSize);
    stream.writeInt32Array(_blockCount.data(), _blockCount.size());
    stream.writeInt16(_weightMapSize);
    stream.writeInt16(_lightMapSize);

    // heights
    stream.writeInt32(_heights.length());
    for (uint32_t i = 0; i < _heights.length(); ++i) {
        stream.writeInt16(_heights[i]);
    }

    // weights
    stream.writeInt32(_weights.length());
    for (uint32_t i = 0; i < _weights.length(); ++i) {
        stream.writeInt8(_weights[i]);
    }

    // layer buffer
    stream.writeInt32(_layerBuffer.size());
    for (size_t i = 0; i < _layerBuffer.size(); ++i) {
        stream.writeInt16(_layerBuffer[i]);
    }

    // layer infos
    std::vector<TerrainLayerBinaryInfo> layerBinaryInfos(_layerInfos.size());
    for (size_t i = 0; i < layerBinaryInfos.size(); ++i) {
        TerrainLayerBinaryInfo &binaryLayer = layerBinaryInfos[i];
        const TerrainLayerInfo &layer       = _layerInfos[i];

        binaryLayer.slot        = i;
        binaryLayer.tileSize    = layer.tileSize;
        binaryLayer.detailMapId = layer.detailMap != nullptr ? layer.detailMap->getUuid() : "";
        binaryLayer.normalMapId = layer.normalMap != nullptr ? layer.normalMap->getUuid() : "";
        binaryLayer.metallic    = layer.metallic;
        binaryLayer.roughness   = layer.roughness;
    }

    stream.writeInt32(layerBinaryInfos.size());
    for (size_t i = 0; i < layerBinaryInfos.size(); ++i) {
        stream.writeInt32(layerBinaryInfos[i].slot);
        stream.writeFloat32(layerBinaryInfos[i].tileSize);
        stream.writeString(layerBinaryInfos[i].detailMapId);
        stream.writeString(layerBinaryInfos[i].normalMapId);
        stream.writeFloat32(layerBinaryInfos[i].roughness);
        stream.writeFloat32(layerBinaryInfos[i].metallic);
    }

    return stream.getBuffer();
}

Uint8Array TerrainAsset::exportDefaultNativeData() const {
    TerrainBuffer stream;
    stream.writeInt32(TERRAIN_DATA_VERSION_DEFAULT);
    return stream.getBuffer();
}

} // namespace cc
