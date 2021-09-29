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

#include <array>
#include "stdint.h"

#include "math/Geometry.h"

#include "core/PassUtils.h"
#include "core/components/RenderableComponent.h"
#include "terrain/TerrainAsset.h"

namespace cc {

namespace scene {
class Model;
}

namespace gfx {
class Buffer;
}

class RenderingSubMesh;
class Terrain;
class Node;
class TerrainRenderable;
class EffectAsset;
class HeightField;

/**
 * @en Terrain info
 * @zh 地形信息
 */
struct TerrainInfo {
    /**
     * @en tile size
     * @zh 栅格大小
     */
    float tileSize{1.F};

    /**
     * @en block count
     * @zh 地形块的数量
     */
    std::array<int32_t, 2> blockCount{1, 1};

    /**
     * @en weight map size
     * @zh 权重图大小
     */
    int32_t weightMapSize = 128;

    /**
     * @en light map size
     * @zh 光照图大小
     */
    int32_t lightMapSize = 128;

    /**
     * @en terrain size
     * @zh 地形大小
     */
    Size getSize() const {
        Size sz;
        sz.width  = blockCount[0] * TERRAIN_BLOCK_TILE_COMPLEXITY * tileSize;
        sz.height = blockCount[1] * TERRAIN_BLOCK_TILE_COMPLEXITY * tileSize;

        return sz;
    }

    /**
     * @en tile count
     * @zh 栅格数量
     */
    std::array<int32_t, 2> getTileCount() const {
        std::array<int32_t, 2> _tileCount{
            blockCount[0] * TERRAIN_BLOCK_TILE_COMPLEXITY,
            blockCount[1] * TERRAIN_BLOCK_TILE_COMPLEXITY};
        return _tileCount;
    }

    /**
     * @en vertex count
     * @zh 顶点数量
     */
    std::array<int32_t, 2> getVertexCount() const {
        std::array<int32_t, 2> _vertexCount = getTileCount();
        _vertexCount[0] += 1;
        _vertexCount[1] += 1;

        return _vertexCount;
    }
};

/**
 * @en Terrain layer
 * @zh 地形纹理层
 */
struct TerrainLayer {
    using Ptr = std::shared_ptr<TerrainLayer>;
    /**
     * @en detail texture
     * @zh 细节纹理
     */
    Texture2D *detailMap{nullptr};

    /**
     * @en normal texture
     * @zh 法线纹理
     */
    Texture2D *normalMap{nullptr};

    /**
     * @en tile size
     * @zh 平铺大小
     */
    float tileSize{1.F};

    /**
     * @en metallic
     * @zh 金属性
     */
    float metallic{0.F}; /* [0, 1] */

    /**
     * @en roughness
     * @zh 粗糙度
     */
    float roughness{1.F}; /* [0, 1] */
};

/**
 * @en Terrain block light map info
 * @zh 地形块光照图信息
 */
struct TerrainBlockLightmapInfo {
    Texture2D *texture{nullptr};
    float      UOff{0.F};
    float      VOff{0.F};
    float      UScale{0.F};
    float      VScale{0.F};
};

/**
 * @en Terrain block
 * @zh 地形块
 */
class TerrainBlock final {
public:
    TerrainBlock(Terrain *t, int32_t i, int32_t j);
    ~TerrainBlock();

    void build();
    void rebuild();
    void destroy();
    void update();
    void setBrushMaterial(Material *mtl);
    /**
     * @en valid
     * @zh 是否有效
     */
    bool isValid() const;

    using LayerIndics = std::array<int16_t, 4>;
    /**
     * @en get layers
     * @zh 获得纹理层索引
     */
    LayerIndics getLayers() const;
    /**
     * @en get light map
     * @zh 获得光照图
     */
    Texture2D *getLightmap() const;
    /**
      * @en get light map uv parameter
      * @zh 获得光照图纹理坐标参数
      */
    Vec4 getLightmapUVParam() const;

    /**
     * @en get terrain owner
     * @zh 获得地形对象
     */
    inline Terrain *getTerrain() {
        return _terrain;
    }

    /**
     * @en get index
     * @zh 获得地形索引
     */
    const std::array<int32_t, 2> &getIndex() const {
        return _index;
    }

    /**
     * @en get rect bound
     * @zh 获得地形矩形包围体
     */
    Rect getRect() const;

    /**
     * @en set layer
     * @zh 设置纹理层
     */
    void setLayer(int32_t index, int32_t layerId);

    /**
     * @en get layer
     * @zh 获得纹理层
     */
    inline int32_t getLayer(int32_t index) const {
        return getLayers()[index];
    }

    /**
     * @en get max layer index
     * @zh 获得最大纹理索引
     */
    inline int32_t getMaxLayer() const {
        if (getLayers()[3] >= 0) {
            return 3;
        }
        if (getLayers()[2] >= 0) {
            return 2;
        }
        if (getLayers()[1] >= 0) {
            return 1;
        }

        return 0;
    }

    MacroRecord getMaterialDefines(int32_t nlayers);
    void        invalidMaterial();
    void        updateMaterial(bool init);
    void        updateHeight();
    void        updateWeightMap();
    void        updateLightmap(TerrainBlockLightmapInfo *info);

private:
    Terrain *              _terrain{nullptr};
    Node *                 _node{nullptr};
    TerrainRenderable *    _renderable{nullptr};
    std::array<int32_t, 2> _index{1, 1};
    // private _neighbor: TerrainBlock|null[] = [null, null, null, null];
    Texture2D *               _weightMap{nullptr};
    TerrainBlockLightmapInfo *_lightmapInfo{nullptr};
};

/**
 * @en Terrain
 * @zh 地形组件
 */
class Terrain final : public Component {
public:
    using Super = Component;

    Terrain();
    ~Terrain();

    void          setAsset(TerrainAsset *asset);
    TerrainAsset *getAsset() const;

    void         setEffectAsset(EffectAsset *value);
    EffectAsset *getEffectAssetOrNull() const;
    EffectAsset *getEffectAsset() const;

    void        setReceiveShadow(bool val);
    inline bool isReceiveShadow() const { return _receiveShadow; }

    /**
     * @en Use normal map
     * @zh 是否使用法线贴图
     */
    inline bool isUseNormalMap() const {
        return _useNormalmap;
    }

    void setUseNormalMap(bool val);

    /**
     * @en Use pbr material
     * @zh 是否使用物理材质
     */
    inline bool isUsePBR() const {
        return _usePBR;
    }

    void setUsePBR(bool val);

    /**
     * @en get terrain size
     * @zh 获得地形大小
     */
    Size getSize() const;

    /**
     * @en get tile size
     * @zh 获得栅格大小
     */
    inline float getTileSize() const {
        return _tileSize;
    }

    /**
     * @en get tile count
     * @zh 获得栅格数量
     */
    std::array<int32_t, 2> getTileCount() const {
        return {_blockCount[0] * TERRAIN_BLOCK_TILE_COMPLEXITY, _blockCount[1] * TERRAIN_BLOCK_TILE_COMPLEXITY};
    }

    /**
     * @en get vertex count
     * @zh 获得顶点数量
     */
    std::array<int32_t, 2> getVertexCount() const {
        auto _vertexCount = getTileCount();
        _vertexCount[0] += 1;
        _vertexCount[1] += 1;

        return _vertexCount;
    }

    /**
     * @en get block count
     * @zh 获得地形块数量
     */
    inline const std::array<int32_t, 2> &getBlockCount() const {
        return _blockCount;
    }

    /**
     * @en get light map size
     * @zh 获得光照图大小
     */
    inline int16_t getLightMapSize() const {
        return _lightMapSize;
    }

    /**
     * @en get weight map size
     * @zh 获得权重图大小
     */
    inline int16_t getWeightMapSize() const {
        return _weightMapSize;
    }

    /**
     * @en get height buffer
     * @zh 获得高度缓存
     */
    inline const Uint16Array &getHeights() const {
        return _heights;
    }

    /**
     * @en get weight buffer
     * @zh 获得权重缓存
     */
    inline const Uint8Array &getWeights() const {
        return _weights;
    }

    /**
     * @en check valid
     * @zh 检测是否有效
     */
    inline bool isValid() const {
        return !_blocks.empty();
    }

    /**
     * @en get terrain info
     * @zh 获得地形信息
     */
    TerrainInfo getInfo();

    /**
     * @en build
     * @zh 构建地形
     */
    void build(const TerrainInfo &info);

    /**
     * @en rebuild
     * @zh 重建地形
     */
    void rebuild(const TerrainInfo &info);

    /**
     * @en import height field
     * @zh 导入高度图
     */
    void importHeightField(HeightField *hf, float heightScale);

    /**
     * @en export height field
     * @zh 导出高度图
     */
    void exportHeightField(HeightField *hf, float heightScale) const;

    TerrainAsset *exportAsset() const;

    TerrainBlockLightmapInfo *getLightmapInfo(int32_t i, int32_t j);

    /**
     * @en get all blocks
     * @zh 获得地形块缓存
     */
    const std::vector<TerrainBlock *> &getBlocks() const {
        return _blocks;
    }

    /**
     * @en get block layers
     * @zh 获得地形块纹理层
     */
    std::array<int16_t, 4> getBlockLayers(int32_t i, int32_t j) const;

    /**
     * @en get block layer
     * @zh 获得地形块纹理层
     */
    int16_t getBlockLayer(int32_t i, int32_t j, int32_t index) const;

    /**
     * @en set block layer
     * @zh 获得地形块层
     */
    void setBlockLayer(int32_t i, int32_t j, int32_t index, int16_t layerId) {
        int32_t layerIndex               = (j * _blockCount[0] + i) * TERRAIN_MAX_BLEND_LAYERS;
        _layerBuffer[layerIndex + index] = layerId;
    }

    /**
     * @en get block
     * @zh 获得地形块对象
     */
    TerrainBlock *getBlock(int32_t i, int32_t j) const {
        return _blocks[j * _blockCount[0] + i];
    }

    /**
     * @en add layer
     * @zh 添加纹理层
     */
    int32_t addLayer(TerrainLayer::Ptr layer) {
        for (size_t i = 0; i < _layerList.size(); ++i) {
            if (_layerList[i] == nullptr || (_layerList[i] != nullptr && _layerList[i]->detailMap == nullptr)) {
                _layerList[i] = layer;
                return i;
            }
        }

        return -1;
    }

    /**
     * @en set layer
     * @zh 设置纹理层
     */
    void setLayer(int32_t i, TerrainLayer::Ptr layer) {
        _layerList[i] = layer;
    }

    /**
     * @en remove layer
     * @zh 移除纹理层
     */
    void removeLayer(int32_t id) {
        _layerList[id] = nullptr;
    }

    /**
     * @en get layer
     * @zh 获得纹理层
     */
    inline TerrainLayer::Ptr getLayer(int32_t id) const {
        if (id == -1) {
            return nullptr;
        }

        return _layerList[id];
    }
    /**
    * @en get position
    * @zh 获得地形上的位置
    */
    Vec3 getPosition(int32_t i, int32_t j);

    inline const Uint16Array &getHeightField() const {
        return _heights;
    }

    /**
     * @en set height
     * @zh 设置地形上的高度
     */
    void setHeight(int32_t i, int32_t j, float h);

    /**
     * @en get height
     * @zh 获得地形上的高度
     */
    float getHeight(int32_t i, int32_t j) const;

    /**
     * @en set height
     * @zh 设置高度
     */
    float getHeightClamp(int32_t i, int32_t j) const;

    /**
     * @en get height by point
     * @zh 根据点的坐标获得高度
     */
    std::optional<float> getHeightAt(float x, float y) const;

    void setNormal(int32_t i, int32_t j, const Vec3 &n);
    /**
     * @en get normal
     * @zh 获得法线
     */
    Vec3 getNormal(int32_t i, int32_t j) const;

    /**
     * @en get normal by point
     * @zh 根据点的坐标获得法线
     */
    std::optional<Vec3> getNormalAt(float x, float y) const;

    /**
     * @en set weight
     * @zh 设置权重
     */
    void setWeight(int32_t i, int32_t j, const Vec4 &w);

    /**
     * @en get weight
     * @zh 获得权重
     */
    Vec4 getWeight(int32_t i, int32_t j) const;

    /**
     * @en get normal by point
     * @zh 根据点的坐标获得权重
     */
    std::optional<Vec4> getWeightAt(float x, float y) const;

    /**
     * @en get max weight layer by point
     * @zh 根据点的坐标获得权重最大的纹理层
     */
    TerrainLayer::Ptr getMaxWeightLayerAt(float x, float y);

    /**
     * @en ray check
     * @zh 射线检测
     * @param start ray start
     * @param dir ray direction
     * @param step ray step
     * @param worldSpace is world space
     */
    std::optional<Vec3> rayCheck(const Vec3 &start, const Vec3 &dir, float step, bool worldSpace = true);

    inline gfx::Buffer *getSharedIndexBuffer() const { return _sharedIndexBuffer; }

    void resetLightmap(bool enable);
    void updateLightmap(int32_t blockId, Texture2D *tex, float uOff, float vOff, float uScale, float vScale);

    Vec3 calcNormal(float x, float z);
    void buildNormals();

    // Override functions
    void onLoad() override;
    void onEnable() override;
    void onDisable() override;
    void onDestroy() override;
    void onRestore() override;
    void update(float deltaTime) override;
    //

private:
    void buildImp(bool restore = false);
    bool rebuildHeights(const TerrainInfo &info);
    bool rebuildLayerBuffer(const TerrainInfo &info);
    bool rebuildWeights(const TerrainInfo &info);

private:
    TerrainAsset *                        _asset{nullptr};
    EffectAsset *                         _effectAsset{nullptr};
    std::vector<TerrainBlockLightmapInfo> _lightmapInfos;
    bool                                  _receiveShadow{false};
    bool                                  _useNormalmap{false};
    bool                                  _usePBR{false};

    float                                                  _tileSize{1.F};
    std::array<int32_t, 2>                                 _blockCount{1, 1};
    int16_t                                                _weightMapSize{128};
    int16_t                                                _lightMapSize{128};
    Uint16Array                                            _heights;
    Uint8Array                                             _weights;
    std::vector<float>                                     _normals;
    std::array<TerrainLayer::Ptr, TERRAIN_MAX_LAYER_COUNT> _layerList;
    std::vector<int16_t>                                   _layerBuffer;
    std::vector<TerrainBlock *>                            _blocks;
    gfx::Buffer *                                          _sharedIndexBuffer{nullptr};

    CC_DISALLOW_COPY_MOVE_ASSIGN(Terrain);
};

} // namespace cc
