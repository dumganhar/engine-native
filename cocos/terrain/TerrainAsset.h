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

#include <stdint.h>

#include "core/DataView.h"
#include "core/TypedArray.h"
#include "core/assets/Asset.h"

namespace cc {

constexpr uint32_t TERRAIN_MAX_LEVELS              = 4;
constexpr uint32_t TERRAIN_MAX_BLEND_LAYERS        = 4;
constexpr uint32_t TERRAIN_MAX_LAYER_COUNT         = 256;
constexpr uint32_t TERRAIN_BLOCK_TILE_COMPLEXITY   = 32;
constexpr uint32_t TERRAIN_BLOCK_VERTEX_COMPLEXITY = 33;
constexpr uint32_t TERRAIN_BLOCK_VERTEX_SIZE       = 8; // position + normal + uv
constexpr uint32_t TERRAIN_HEIGHT_BASE             = 32768;

constexpr float TERRAIN_HEIGHT_FACTORY = 1.0F / 512.0F;
constexpr float TERRAIN_HEIGHT_FMIN    = (-TERRAIN_HEIGHT_BASE) * TERRAIN_HEIGHT_FACTORY;
constexpr float TERRAIN_HEIGHT_FMAX    = (65535 - TERRAIN_HEIGHT_BASE) * TERRAIN_HEIGHT_FACTORY;

constexpr uint32_t TERRAIN_NORTH_INDEX = 0;
constexpr uint32_t TERRAIN_SOUTH_INDEX = 1;
constexpr uint32_t TERRAIN_WEST_INDEX  = 2;
constexpr uint32_t TERRAIN_EAST_INDEX  = 3;

constexpr uint32_t TERRAIN_DATA_VERSION         = 0x01010001;
constexpr uint32_t TERRAIN_DATA_VERSION2        = 0x01010002;
constexpr uint32_t TERRAIN_DATA_VERSION3        = 0x01010003;
constexpr uint32_t TERRAIN_DATA_VERSION4        = 0x01010004;
constexpr uint32_t TERRAIN_DATA_VERSION5        = 0x01010005;
constexpr uint32_t TERRAIN_DATA_VERSION_DEFAULT = 0x01010111;

class Texture2D;

/**
 * @en terrain layer info
 * @zh 地形纹理信息
 */
struct TerrainLayerInfo {
    //    @serializable
    int32_t slot{0};
    //    @serializable
    int32_t tileSize{1};
    //    @serializable
    Texture2D *detailMap{nullptr};
    //    @serializable
    Texture2D *normalMap{nullptr};
    //    @serializable
    float roughness{1.F};
    //    @serializable
    float metallic{0.F};
};

/**
 * @en terrain layer binary info
 * @zh 地形纹理二进制信息
 */
struct TerrainLayerBinaryInfo {
    int32_t     slot      = 0;
    int32_t     tileSize  = 1;
    float       roughness = 1;
    float       metallic  = 0;
    std::string detailMapId;
    std::string normalMapId;
};

/**
 * @en terrain asset
 * @zh 地形资源
 */
class TerrainAsset final : public Asset {
public:
    TerrainAsset()  = default;
    ~TerrainAsset() = default;

    std::any getNativeAsset() const override;
    void     setNativeAsset(const std::any &obj) override;

    /**
     * @en version
     * @zh 版本
     */
    inline int32_t getVersion() const {
        return _version;
    }

    /**
     * @en tile size
     * @zh 栅格大小
     */
    inline void setTileSize(float value) {
        _tileSize = value;
    }

    inline float getTileSize() const {
        return _tileSize;
    }

    /**
     * @en block count
     * @zh 块数量
     */
    inline void setBlockCount(const std::vector<int32_t> &value) {
        _blockCount = value;
    }

    inline const std::vector<int32_t> &getBlockCount() const {
        return _blockCount;
    }

    /**
     * @en light map size
     * @zh 光照图大小
     */
    inline void setLightMapSize(int16_t value) {
        _lightMapSize = value;
    }

    inline int16_t getLightMapSize() const {
        return _lightMapSize;
    }

    /**
     * @en weight map size
     * @zh 权重图大小
     */
    inline void setWeightMapSize(int16_t value) {
        _weightMapSize = value;
    }

    inline int16_t getWeightMapSize() const {
        return _weightMapSize;
    }

    /**
     * @en height buffer
     * @zh 高度缓存
     */
    inline void setHeights(const Uint16Array &value) {
        _heights = value;
    }

    inline const Uint16Array &getHeights() const {
        return _heights;
    }

    /**
     * @en weight buffer
     * @zh 权重缓存
     */
    inline void setWeights(const Uint8Array &value) {
        _weights = value;
    }

    inline const Uint8Array &getWeights() {
        return _weights;
    }

    /**
     * @en layer buffer
     * @zh 纹理索引缓存
     */
    inline void setLayerBuffer(const std::vector<int16_t> &value) {
        _layerBuffer = value;
    }

    inline const std::vector<int16_t> &getLayerBuffer() const {
        return _layerBuffer;
    }

    /**
     * @en layer info
     * @zh 纹理信息
     */
    inline void setLayerInfos(const std::vector<TerrainLayerInfo> &value) {
        _layerInfos = value;
    }

    inline const std::vector<TerrainLayerInfo> &getLayerInfos() const {
        return _layerInfos;
    }

    inline const std::vector<TerrainLayerBinaryInfo> &getLayerBinaryInfos() const {
        return _layerBinaryInfos;
    }

    /**
     * @en get layer
     * @zh 获得纹理索引
     * @param xBlock block index x
     * @param yBlock block index y
     * @param layerId layer id
     */
    int32_t getLayer(int32_t xBlock, int32_t yBlock, int32_t layerId) const;

    float   getHeight(int32_t i, int32_t j) const;
    int32_t getVertexCountI() const;
    int32_t getVertexCountJ() const;

    inline void setNativeData(const Uint8Array &_nativeData) {
        _data = _nativeData;
    }

    bool loadNativeData(const Uint8Array &_nativeData);

    Uint8Array exportNativeData() const;
    Uint8Array exportDefaultNativeData() const;

protected:
    int32_t                             _version{0};
    Uint8Array                          _data;
    float                               _tileSize{1.F};
    std::vector<int32_t>                _blockCount{1, 1};
    int16_t                             _weightMapSize{128};
    int16_t                             _lightMapSize{128};
    Uint16Array                         _heights;
    Uint8Array                          _weights;
    std::vector<int16_t>                _layerBuffer{-1, -1, -1, -1};
    std::vector<TerrainLayerBinaryInfo> _layerBinaryInfos;
    //    @serializable
    std::vector<TerrainLayerInfo> _layerInfos;
};

} // namespace cc
