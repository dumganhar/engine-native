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
#include "terrain/Terrain.h"
#include "core/Root.h"
#include "core/assets/RenderingSubMesh.h"
#include "core/assets/Texture2D.h"
#include "core/builtin/BuiltinResMgr.h"
#include "core/scene-graph/Node.h"
#include "renderer/gfx-base/GFXDevice.h"
#include "scene/Model.h"
#include "terrain/HeightField.h"

namespace cc {

//
/**
 * @en Terrain renderable
 * @zh 地形渲染组件
 */
class TerrainRenderable final : public RenderableComponent {
public:
    using Super = RenderableComponent;

    TerrainRenderable() = default;
    ~TerrainRenderable();

    bool destroy() override;
    void destroyModel();
    void invalidMaterial();
    void updateMaterial(TerrainBlock *block, bool init);

    void onMaterialModified(index_t idx, Material *mtl) override {
        if (_model == nullptr) {
            return;
        }
        onRebuildPSO(idx, mtl != nullptr ? mtl : getBuiltinMaterial());
    }

    void onRebuildPSO(index_t idx, Material *material) override {
        if (_model) {
            _model->setSubModelMaterial(idx, material);
        }
    }

protected:
    void clearMaterials() override {
        if (_model == nullptr) {
            return;
        }

        onMaterialModified(0, nullptr);
    }

private:
    Material *getBuiltinMaterial() {
        BuiltinResMgr::getInstance()->get<Material>("missing-material");
    }

private:
    scene::Model *    _model{nullptr};
    RenderingSubMesh *_meshData{nullptr};

    Material *_brushMaterial{nullptr};
    Material *_currentMaterial{nullptr};
    int32_t   _currentMaterialLayers{0};

    friend class TerrainBlock;
    CC_DISALLOW_COPY_MOVE_ASSIGN(TerrainRenderable);
};

TerrainRenderable::~TerrainRenderable() {
    CC_SAFE_DELETE(_meshData);
    CC_SAFE_DELETE(_brushMaterial);
    CC_SAFE_DELETE(_currentMaterial);
}

bool TerrainRenderable::destroy() {
    destroyModel();
    return Super::destroy();
}

void TerrainRenderable::destroyModel() {
    // _invalidMaterial();
    if (_model != nullptr) {
        Root::getInstance()->destroyModel(_model);
        _model = nullptr;
    }
}

void TerrainRenderable::invalidMaterial() {
    if (_currentMaterial == nullptr) {
        return;
    }

    if (_brushMaterial != nullptr && !_brushMaterial->getPasses().empty()) {
        auto &passes = _currentMaterial->getPasses();
        for (size_t i = 0; i < passes.size(); ++i) {
            if (passes[i] == _brushMaterial->getPasses()[0]) {
                passes.pop_back();
                break;
            }
        }
    }

    clearMaterials();

    _currentMaterial = nullptr;
    if (_model != nullptr) {
        _model->setEnabled(false);
    }
}

void TerrainRenderable::updateMaterial(TerrainBlock *block, bool init) {
    if (_meshData == nullptr || _model == nullptr) {
        return;
    }

    const int32_t nLayers = block->getMaxLayer();
    if (_currentMaterial == nullptr || nLayers != _currentMaterialLayers) {
        _currentMaterial = new Material();

        IMaterialInfo info;
        info.effectAsset = block->getTerrain()->getEffectAsset();
        info.defines     = block->getMaterialDefines(nLayers);
        _currentMaterial->initialize(info);

        if (_brushMaterial != nullptr && !_brushMaterial->getPasses().empty()) {
            auto &passes = _currentMaterial->getPasses();
            passes.emplace_back(_brushMaterial->getPasses()[0]);
        }

        if (init) {
            _model->initSubModel(0, _meshData, _currentMaterial);
        }

        setMaterial(_currentMaterial, 0);

        _currentMaterialLayers = nLayers;
        _model->setEnabled(true);
        _model->setReceiveShadow(block->getTerrain()->isReceiveShadow());
    }
}

//

TerrainBlock::TerrainBlock(Terrain *t, int32_t i, int32_t j) {
    _terrain      = t;
    _index[0]     = i;
    _index[1]     = j;
    _lightmapInfo = t->getLightmapInfo(i, j);

    _node = new Node();
    _node->setParent(_terrain->getNode());
    _node->setHideFlags(_node->getHideFlags() | CCObject::Flags::DONT_SAVE | CCObject::Flags::HIDE_IN_HIERARCHY);

    _node->setLayer(_terrain->getNode()->getLayer());

    _renderable = _node->addComponent<TerrainRenderable>();
}

TerrainBlock::~TerrainBlock() {
    CC_SAFE_DELETE(_weightMap);
}

void TerrainBlock::build() {
    gfx::Device *gfxDevice = gfx::Device::getInstance();

    // vertex buffer
    Float32Array vertexData{TERRAIN_BLOCK_VERTEX_SIZE * TERRAIN_BLOCK_VERTEX_COMPLEXITY * TERRAIN_BLOCK_VERTEX_COMPLEXITY};

    int32_t index = 0;
    Vec3    bbMin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    Vec3    bbMax(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

    for (int32_t j = 0; j < TERRAIN_BLOCK_VERTEX_COMPLEXITY; ++j) {
        for (int32_t i = 0; i < TERRAIN_BLOCK_VERTEX_COMPLEXITY; ++i) {
            const int32_t x        = _index[0] * TERRAIN_BLOCK_TILE_COMPLEXITY + i;
            const int32_t y        = _index[1] * TERRAIN_BLOCK_TILE_COMPLEXITY + j;
            const auto &  position = _terrain->getPosition(x, y);
            const auto &  normal   = _terrain->getNormal(x, y);
            Vec2          uv{static_cast<float>(i) / TERRAIN_BLOCK_TILE_COMPLEXITY, static_cast<float>(j) / TERRAIN_BLOCK_TILE_COMPLEXITY};
            vertexData[index++] = position.x;
            vertexData[index++] = position.y;
            vertexData[index++] = position.z;
            vertexData[index++] = normal.x;
            vertexData[index++] = normal.y;
            vertexData[index++] = normal.z;
            vertexData[index++] = uv.x;
            vertexData[index++] = uv.y;

            Vec3::min(bbMin, position, &bbMin);
            Vec3::max(bbMax, position, &bbMax);
        }
    }

    auto *vertexBuffer = gfxDevice->createBuffer(gfx::BufferInfo{
        gfx::BufferUsageBit::VERTEX | gfx::BufferUsageBit::TRANSFER_DST,
        gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
        TERRAIN_BLOCK_VERTEX_SIZE * Float32Array::BYTES_PER_ELEMENT * TERRAIN_BLOCK_VERTEX_COMPLEXITY * TERRAIN_BLOCK_VERTEX_COMPLEXITY,
        TERRAIN_BLOCK_VERTEX_SIZE * Float32Array::BYTES_PER_ELEMENT,
    });
    vertexBuffer->update(vertexData.buffer()->getData());

    // initialize renderable
    const gfx::AttributeList gfxAttributes{
        {gfx::ATTR_NAME_POSITION, gfx::Format::RGB32F},
        {gfx::ATTR_NAME_NORMAL, gfx::Format::RGB32F},
        {gfx::ATTR_NAME_TEX_COORD, gfx::Format::RG32F},
    };

    _renderable->_meshData = new RenderingSubMesh({vertexBuffer}, gfxAttributes,
                                                  gfx::PrimitiveMode::TRIANGLE_LIST, _terrain->getSharedIndexBuffer());

    auto *model = _renderable->_model = Root::getInstance()->createModel<scene::Model>();
    model->createBoundingShape(bbMin, bbMax);
    model->setNode(_node);
    model->setTransform(_node);
    _renderable->getRenderScene()->addModel(model);

    // reset weightmap
    updateWeightMap();

    // reset material
    updateMaterial(true);
}

void TerrainBlock::rebuild() {
    updateHeight();
    updateWeightMap();

    _renderable->invalidMaterial();
    updateMaterial(false);
}

void TerrainBlock::destroy() {
    _renderable->destroyModel();

    if (_node != nullptr) {
        _node->destroy();
    }
    if (_weightMap != nullptr) {
        _weightMap->destroy();
    }
}

void TerrainBlock::update() {
    updateMaterial(false);

    const bool useNormalMap = _terrain->isUseNormalMap();
    const bool usePBR       = _terrain->isUsePBR();

    auto getDetailTex = [](TerrainLayer::Ptr layer) -> Texture2D * {
        return layer != nullptr ? layer->detailMap : nullptr;
    };

    auto getNormalTex = [](TerrainLayer::Ptr layer) -> Texture2D * {
        auto *normalTex = layer != nullptr ? layer->normalMap : nullptr;
        if (normalTex == nullptr) {
            normalTex = BuiltinResMgr::getInstance()->get<Texture2D>("normal-texture");
        }

        return normalTex;
    };

    Material *mtl = _renderable->_currentMaterial;
    if (mtl != nullptr) {
        const int32_t nlayers = getMaxLayer();
        Vec4          uvScale{1.F, 1.F, 1.F, 1.F};
        Vec4          roughness{1.F, 1.F, 1.F, 1.F};
        Vec4          metallic{0.F, 0.F, 0.F, 0.F};

        if (nlayers == 0) {
            if (getLayers()[0] != -1) {
                TerrainLayer::Ptr l0 = _terrain->getLayer(getLayers()[0]);

                if (l0 != nullptr) {
                    uvScale.x   = 1.0 / l0->tileSize;
                    roughness.x = l0->roughness;
                    metallic.x  = l0->metallic;
                }

                mtl->setProperty("detailMap0", getDetailTex(l0));
                if (useNormalMap) {
                    mtl->setProperty("normalMap0", getNormalTex(l0));
                }
            } else {
                mtl->setProperty("detailMap0", BuiltinResMgr::getInstance()->get<Texture2D>("default-texture"));
                if (useNormalMap) {
                    mtl->setProperty("normalMap0", BuiltinResMgr::getInstance()->get<Texture2D>("normal-texture"));
                }
            }
        } else if (nlayers == 1) {
            TerrainLayer::Ptr l0 = _terrain->getLayer(getLayers()[0]);
            TerrainLayer::Ptr l1 = _terrain->getLayer(getLayers()[1]);

            if (l0 != nullptr) {
                uvScale.x   = 1.0 / l0->tileSize;
                roughness.x = l0->roughness;
                metallic.x  = l0->metallic;
            }
            if (l1 != nullptr) {
                uvScale.y   = 1.0 / l1->tileSize;
                roughness.y = l1->roughness;
                metallic.y  = l1->metallic;
            }

            mtl->setProperty("weightMap", _weightMap);
            mtl->setProperty("detailMap0", getDetailTex(l0));
            mtl->setProperty("detailMap1", getDetailTex(l1));
            if (useNormalMap) {
                mtl->setProperty("normalMap0", getNormalTex(l0));
                mtl->setProperty("normalMap1", getNormalTex(l1));
            }
        } else if (nlayers == 2) {
            TerrainLayer::Ptr l0 = _terrain->getLayer(getLayers()[0]);
            TerrainLayer::Ptr l1 = _terrain->getLayer(getLayers()[1]);
            TerrainLayer::Ptr l2 = _terrain->getLayer(getLayers()[2]);

            if (l0 != nullptr) {
                uvScale.x   = 1.0 / l0->tileSize;
                roughness.x = l0->roughness;
                metallic.x  = l0->metallic;
            }
            if (l1 != nullptr) {
                uvScale.y   = 1.0 / l1->tileSize;
                roughness.y = l1->roughness;
                metallic.y  = l1->metallic;
            }
            if (l2 != nullptr) {
                uvScale.z   = 1.0 / l2->tileSize;
                roughness.z = l2->roughness;
                metallic.z  = l2->metallic;
            }

            mtl->setProperty("weightMap", _weightMap);
            mtl->setProperty("detailMap0", getDetailTex(l0));
            mtl->setProperty("detailMap1", getDetailTex(l1));
            mtl->setProperty("detailMap2", getDetailTex(l2));
            if (useNormalMap) {
                mtl->setProperty("normalMap0", getNormalTex(l0));
                mtl->setProperty("normalMap1", getNormalTex(l1));
                mtl->setProperty("normalMap2", getNormalTex(l2));
            }
        } else if (nlayers == 3) {
            TerrainLayer::Ptr l0 = _terrain->getLayer(getLayers()[0]);
            TerrainLayer::Ptr l1 = _terrain->getLayer(getLayers()[1]);
            TerrainLayer::Ptr l2 = _terrain->getLayer(getLayers()[2]);
            TerrainLayer::Ptr l3 = _terrain->getLayer(getLayers()[3]);

            if (l0 != nullptr) {
                uvScale.x   = 1.0 / l0->tileSize;
                roughness.x = l0->roughness;
                metallic.x  = l0->metallic;
            }
            if (l1 != nullptr) {
                uvScale.y   = 1.0 / l1->tileSize;
                roughness.y = l1->roughness;
                metallic.y  = l1->metallic;
            }
            if (l2 != nullptr) {
                uvScale.z   = 1.0 / l2->tileSize;
                roughness.z = l2->roughness;
                metallic.z  = l2->metallic;
            }
            if (l3 != nullptr) {
                uvScale.w   = 1.0 / l3->tileSize;
                roughness.w = l3->roughness;
                metallic.w  = l3->metallic;
            }

            mtl->setProperty("weightMap", _weightMap);
            mtl->setProperty("detailMap0", getDetailTex(l0));
            mtl->setProperty("detailMap1", getDetailTex(l1));
            mtl->setProperty("detailMap2", getDetailTex(l2));
            mtl->setProperty("detailMap3", getDetailTex(l3));
            if (useNormalMap) {
                mtl->setProperty("normalMap0", getNormalTex(l0));
                mtl->setProperty("normalMap1", getNormalTex(l1));
                mtl->setProperty("normalMap2", getNormalTex(l2));
                mtl->setProperty("normalMap3", getNormalTex(l3));
            }
        }

        mtl->setProperty("UVScale", uvScale);
        if (usePBR) {
            mtl->setProperty("roughness", roughness);
            mtl->setProperty("metallic", metallic);
        }

        if (getLightmap() != nullptr) {
            mtl->setProperty("lightMap", getLightmap());
            mtl->setProperty("lightMapUVParam", getLightmapUVParam());
        }
    }
}

void TerrainBlock::setBrushMaterial(Material *mtl) {
    if (_renderable->_brushMaterial != mtl) {
        _renderable->invalidMaterial();
        _renderable->_brushMaterial = mtl;
    }
}

bool TerrainBlock::isValid() const {
    if (_terrain == nullptr) {
        return false;
    }

    const auto &blocks = _terrain->getBlocks();
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i] == this) {
            return true;
        }
    }

    return false;
}

TerrainBlock::LayerIndics TerrainBlock::getLayers() const {
    return _terrain->getBlockLayers(_index[0], _index[1]);
}

Texture2D *TerrainBlock::getLightmap() const {
    return _lightmapInfo != nullptr ? _lightmapInfo->texture : nullptr;
}

Vec4 TerrainBlock::getLightmapUVParam() const {
    if (_lightmapInfo != nullptr) {
        return {
            _lightmapInfo->UOff,
            _lightmapInfo->VOff,
            _lightmapInfo->UScale,
            _lightmapInfo->VScale};
    }

    return Vec4::ZERO;
}

Rect TerrainBlock::getRect() const {
    Rect rect;
    rect.origin.x    = _index[0] * TERRAIN_BLOCK_TILE_COMPLEXITY;
    rect.origin.y    = _index[1] * TERRAIN_BLOCK_TILE_COMPLEXITY;
    rect.size.width  = TERRAIN_BLOCK_TILE_COMPLEXITY;
    rect.size.height = TERRAIN_BLOCK_TILE_COMPLEXITY;
    return rect;
}

void TerrainBlock::setLayer(int32_t index, int32_t layerId) {
    if (getLayers()[index] != layerId) {
        _terrain->setBlockLayer(_index[0], _index[1], index, layerId);
        _renderable->invalidMaterial();
        updateMaterial(false);
    }
}

MacroRecord TerrainBlock::getMaterialDefines(int32_t nlayers) {
    return MacroRecord{
        {"LAYERS", nlayers + 1},
        {"USE_LIGHTMAP", getLightmap() != nullptr ? 1 : 0},
        {"USE_NORMALMAP", _terrain->isUseNormalMap() ? 1 : 0},
        {"USE_PBR", _terrain->isUsePBR() ? 1 : 0},
        //{ "CC_RECEIVE_SHADOW", _terrain->isReceiveShadow() ? 1 : 0 },
    };
}

void TerrainBlock::invalidMaterial() {
    _renderable->invalidMaterial();
}

void TerrainBlock::updateMaterial(bool init) {
    _renderable->updateMaterial(this, init);
}

void TerrainBlock::updateHeight() {
    if (_renderable->_meshData == nullptr) {
        return;
    }

    Float32Array vertexData{TERRAIN_BLOCK_VERTEX_SIZE * TERRAIN_BLOCK_VERTEX_COMPLEXITY * TERRAIN_BLOCK_VERTEX_COMPLEXITY};

    int32_t index = 0;
    Vec3    bbMin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    Vec3    bbMax(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
    for (int32_t j = 0; j < TERRAIN_BLOCK_VERTEX_COMPLEXITY; ++j) {
        for (int32_t i = 0; i < TERRAIN_BLOCK_VERTEX_COMPLEXITY; ++i) {
            const int32_t x = _index[0] * TERRAIN_BLOCK_TILE_COMPLEXITY + i;
            const int32_t y = _index[1] * TERRAIN_BLOCK_TILE_COMPLEXITY + j;

            const auto &position = _terrain->getPosition(x, y);
            const auto &normal   = _terrain->getNormal(x, y);
            const Vec2  uv{
                static_cast<float>(i) / TERRAIN_BLOCK_VERTEX_COMPLEXITY,
                static_cast<float>(j) / TERRAIN_BLOCK_VERTEX_COMPLEXITY};

            vertexData[index++] = position.x;
            vertexData[index++] = position.y;
            vertexData[index++] = position.z;
            vertexData[index++] = normal.x;
            vertexData[index++] = normal.y;
            vertexData[index++] = normal.z;
            vertexData[index++] = uv.x;
            vertexData[index++] = uv.y;

            Vec3::min(bbMin, position, &bbMin);
            Vec3::max(bbMax, position, &bbMax);
        }
    }

    _renderable->_meshData->getVertexBuffers()[0]->update(vertexData.buffer()->getData());
    _renderable->_model->createBoundingShape(bbMin, bbMax);
    _renderable->_model->updateWorldBound();
}

void TerrainBlock::updateWeightMap() {
    const int32_t nlayers = getMaxLayer();

    if (nlayers == 0) {
        if (_weightMap != nullptr) {
            _weightMap->destroy();
            _weightMap = nullptr;
        }

        return;
    }

    if (_weightMap == nullptr) {
        _weightMap = new Texture2D();
        _weightMap->create(_terrain->getWeightMapSize(), _terrain->getWeightMapSize(), PixelFormat::RGBA8888);
        _weightMap->setFilters(Filter::LINEAR, Filter::LINEAR);
        _weightMap->setWrapMode(WrapMode::CLAMP_TO_EDGE, WrapMode::CLAMP_TO_EDGE);
    }

    Uint8Array weightData(_terrain->getWeightMapSize() * _terrain->getWeightMapSize() * 4);
    uint32_t   weightIndex = 0;
    for (uint32_t j = 0; j < _terrain->getWeightMapSize(); ++j) {
        for (uint32_t i = 0; i < _terrain->getWeightMapSize(); ++i) {
            const int32_t x = _index[0] * _terrain->getWeightMapSize() + i;
            const int32_t y = _index[1] * _terrain->getWeightMapSize() + j;
            const Vec4 &  w = _terrain->getWeight(x, y);

            weightData[weightIndex * 4 + 0] = static_cast<uint8_t>(std::floor(w.x * 255.F));
            weightData[weightIndex * 4 + 1] = static_cast<uint8_t>(std::floor(w.y * 255.F));
            weightData[weightIndex * 4 + 2] = static_cast<uint8_t>(std::floor(w.z * 255.F));
            weightData[weightIndex * 4 + 3] = static_cast<uint8_t>(std::floor(w.w * 255.F));

            weightIndex += 1;
        }
    }
    _weightMap->uploadData(weightData.buffer()->getData());
}

void TerrainBlock::updateLightmap(TerrainBlockLightmapInfo *info) {
    _lightmapInfo = info; //cjh TODO: weak ref?
    invalidMaterial();
}
//

//
Terrain::Terrain() {
}

Terrain::~Terrain() {
}

void Terrain::setAsset(TerrainAsset *asset) {
    if (_asset != asset) {
        _asset = asset;
        if (_asset != nullptr && isValid()) {
            // rebuild
            for (auto *block : _blocks) {
                block->destroy();
                delete block;
            }
            _blocks.clear();
            buildImp();
        }
    }
}

TerrainAsset *Terrain::getAsset() const {
    return _asset;
}

void Terrain::setEffectAsset(EffectAsset *value) {
    if (_effectAsset == value) {
        return;
    }

    _effectAsset = value;
    for (auto *block : _blocks) {
        block->invalidMaterial();
    }
}

EffectAsset *Terrain::getEffectAssetOrNull() const {
    return _effectAsset;
}

EffectAsset *Terrain::getEffectAsset() const {
    if (_effectAsset == nullptr) {
        return EffectAsset::get("terrain");
    }

    return _effectAsset;
}

void Terrain::setReceiveShadow(bool val) {
    _receiveShadow = val;
    for (auto *block : _blocks) {
        block->invalidMaterial();
    }
}

void Terrain::setUseNormalMap(bool val) {
    _useNormalmap = val;
    for (auto *block : _blocks) {
        block->invalidMaterial();
    }
}

void Terrain::setUsePBR(bool val) {
    _usePBR = val;
    for (auto *block : _blocks) {
        block->invalidMaterial();
    }
}

Size Terrain::getSize() const {
    Size sz;
    sz.width  = _blockCount[0] * TERRAIN_BLOCK_TILE_COMPLEXITY * _tileSize;
    sz.height = _blockCount[1] * TERRAIN_BLOCK_TILE_COMPLEXITY * _tileSize;
    return sz;
}

TerrainInfo Terrain::getInfo() {
    TerrainInfo ti;
    ti.tileSize      = getTileSize();
    ti.blockCount[0] = _blockCount[0];
    ti.blockCount[1] = _blockCount[1];
    ti.weightMapSize = _weightMapSize;
    ti.lightMapSize  = _lightMapSize;

    return ti;
}

void Terrain::build(const TerrainInfo &info) {
    _tileSize      = info.tileSize;
    _blockCount[0] = info.blockCount[0];
    _blockCount[1] = info.blockCount[1];
    _weightMapSize = info.weightMapSize;
    _lightMapSize  = info.lightMapSize;

    return buildImp();
}

void Terrain::rebuild(const TerrainInfo &info) {
    for (auto *block : _blocks) {
        block->destroy();
        delete block;
    }
    _blocks.clear();

    // build layer buffer
    rebuildLayerBuffer(info);

    // build heights
    rebuildHeights(info);

    // build weights
    rebuildWeights(info);

    // update info
    _tileSize      = info.tileSize;
    _blockCount[0] = info.blockCount[0];
    _blockCount[1] = info.blockCount[1];
    _weightMapSize = info.weightMapSize;
    _lightMapSize  = info.lightMapSize;

    // build blocks
    buildNormals();

    for (int32_t j = 0; j < _blockCount[1]; ++j) {
        for (int32_t i = 0; i < _blockCount[0]; ++i) {
            _blocks.emplace_back(new TerrainBlock(this, i, j));
        }
    }

    for (auto *block : _blocks) {
        block->build();
    }
}

void Terrain::importHeightField(HeightField *hf, float heightScale) {
    int32_t index       = 0;
    auto    vertexCount = getVertexCount();
    for (int32_t j = 0, jLen = vertexCount[1]; j < jLen; ++j) {
        for (int32_t i = 0, iLen = vertexCount[0]; i < iLen; ++i) {
            auto        tileCount = getTileCount();
            const float u         = static_cast<float>(i) / tileCount[0];
            const float v         = static_cast<float>(j) / tileCount[1];

            float h = hf->getAt(u * hf->getWidth(), v * hf->getHeight()) * heightScale;

            _heights[index++] = h;
        }
    }

    buildNormals();

    // rebuild all blocks
    for (auto *block : _blocks) {
        block->updateHeight();
    }
}

void Terrain::exportHeightField(HeightField *hf, float heightScale) const {
    int32_t index = 0;
    for (int32_t j = 0; j < hf->getHeight(); ++j) {
        for (int32_t i = 0; i < hf->getWidth(); ++i) {
            const float u = static_cast<float>(i) / (hf->getWidth() - 1);
            const float v = static_cast<float>(j) / (hf->getHeight() - 1);

            const float x = u * getSize().width;
            const float y = v * getSize().height;

            std::optional<float> h = getHeightAt(x, y);
            if (h.has_value()) {
                hf->_data[index++] = h.value() * heightScale;
            }
        }
    }
}

TerrainAsset *Terrain::exportAsset() const {
    TerrainAsset *asset = new TerrainAsset(); //cjh how to release? shared_ptr?

    asset->setTileSize(getTileSize());
    asset->setBlockCount(getBlockCount());
    asset->setLightMapSize(_lightMapSize);
    asset->setWeightMapSize(_weightMapSize);
    asset->setHeights(_heights);
    asset->setWeights(_weights);

    auto &layerBuffer = asset->getLayerBuffer();
    layerBuffer.resize(_blocks.size() * 4);
    for (size_t i = 0; i < _blocks.size(); ++i) {
        layerBuffer[i * 4 + 0] = _blocks[i]->getLayers()[0];
        layerBuffer[i * 4 + 1] = _blocks[i]->getLayers()[1];
        layerBuffer[i * 4 + 2] = _blocks[i]->getLayers()[2];
        layerBuffer[i * 4 + 3] = _blocks[i]->getLayers()[3];
    }

    int32_t i = 0;
    for (auto &temp : _layerList) {
        if (temp && temp->detailMap && isObjectValid(temp->detailMap)) {
            TerrainLayerInfo layer;
            layer.slot      = i;
            layer.tileSize  = temp->tileSize;
            layer.detailMap = temp->detailMap;
            layer.normalMap = temp->normalMap;
            layer.metallic  = temp->metallic;
            layer.roughness = temp->roughness;

            asset->_layerInfos.emplace_back(layer);
        }
        ++i;
    }

    return asset;
}

TerrainBlockLightmapInfo *Terrain::getLightmapInfo(int32_t i, int32_t j) {
    const int32_t             index = j * getBlockCount()[0] + i;
    TerrainBlockLightmapInfo *ret   = nullptr;
    if (index < _lightmapInfos.size()) {
        ret = &_lightmapInfos[index];
    }
    return ret;
}

std::array<int16_t, 4> Terrain::getBlockLayers(int32_t i, int32_t j) const {
    const int32_t layerIndex = (j * _blockCount[0] + i) * TERRAIN_MAX_BLEND_LAYERS;

    return {
        _layerBuffer[layerIndex],
        _layerBuffer[layerIndex + 1],
        _layerBuffer[layerIndex + 2],
        _layerBuffer[layerIndex + 3],
    };
}

int16_t Terrain::getBlockLayer(int32_t i, int32_t j, int32_t index) const {
    const int32_t layerIndex = (j * _blockCount[0] + i) * TERRAIN_MAX_BLEND_LAYERS;
    return _layerBuffer[layerIndex + index];
}

Vec3 Terrain::getPosition(int32_t i, int32_t j) {
    const float x = i * _tileSize;
    const float z = j * _tileSize;
    const float y = getHeight(i, j);

    return {x, y, z};
}

void Terrain::setHeight(int32_t i, int32_t j, float h) {
    h                                     = std::clamp(h, TERRAIN_HEIGHT_FMIN, TERRAIN_HEIGHT_FMAX);
    _heights[j * getVertexCount()[0] + i] = TERRAIN_HEIGHT_BASE + h / TERRAIN_HEIGHT_FACTORY;
}

float Terrain::getHeight(int32_t i, int32_t j) const {
    return (_heights[j * getVertexCount()[0] + i] - TERRAIN_HEIGHT_BASE) * TERRAIN_HEIGHT_FACTORY;
}

float Terrain::getHeightClamp(int32_t i, int32_t j) const {
    auto vertexCount = getVertexCount();
    i                = std::clamp(i, 0, vertexCount[0] - 1);
    j                = std::clamp(j, 0, vertexCount[1] - 1);

    return getHeight(i, j);
}

std::optional<float> Terrain::getHeightAt(float x, float y) const {
    const float fx = x / getTileSize();
    const float fy = y / getTileSize();

    int32_t     ix0 = static_cast<int32_t>(std::floor(fx));
    int32_t     iz0 = static_cast<int32_t>(std::floor(fy));
    int32_t     ix1 = ix0 + 1;
    int32_t     iz1 = iz0 + 1;
    const float dx  = fx - ix0;
    const float dz  = fy - iz0;

    auto vertexCount = getVertexCount();

    if (ix0 < 0 || ix0 > vertexCount[0] - 1 || iz0 < 0 || iz0 > vertexCount[1] - 1) {
        return std::nullopt;
    }

    ix0 = std::clamp(ix0, 0, vertexCount[0] - 1);
    iz0 = std::clamp(iz0, 0, vertexCount[1] - 1);
    ix1 = std::clamp(ix1, 0, vertexCount[0] - 1);
    iz1 = std::clamp(iz1, 0, vertexCount[1] - 1);

    float       a = getHeight(ix0, iz0);
    float       b = getHeight(ix1, iz0);
    float       c = getHeight(ix0, iz1);
    float       d = getHeight(ix1, iz1);
    const float m = (b + c) * 0.5F;

    if (dx + dz <= 1.0F) {
        d = m + (m - a);
    } else {
        a = m + (m - d);
    }

    const float h1 = a * (1.0F - dx) + b * dx;
    const float h2 = c * (1.0F - dx) + d * dx;

    const float h = h1 * (1.0F - dz) + h2 * dz;

    return h;
}

void Terrain::setNormal(int32_t i, int32_t j, const Vec3 &n) {
    const int32_t index = j * getVertexCount()[0] + i;

    _normals[index * 3 + 0] = n.x;
    _normals[index * 3 + 1] = n.y;
    _normals[index * 3 + 2] = n.z;
}

Vec3 Terrain::getNormal(int32_t i, int32_t j) const {
    const int32_t index = j * getVertexCount()[0] + i;

    Vec3 n;
    n.x = _normals[index * 3 + 0];
    n.y = _normals[index * 3 + 1];
    n.z = _normals[index * 3 + 2];

    return n;
}

std::optional<Vec3> Terrain::getNormalAt(float x, float y) const {
    const float fx = x / getTileSize();
    const float fy = y / getTileSize();

    int32_t     ix0 = static_cast<int32_t>(std::floor(fx));
    int32_t     iz0 = static_cast<int32_t>(std::floor(fy));
    int32_t     ix1 = ix0 + 1;
    int32_t     iz1 = iz0 + 1;
    const float dx  = fx - ix0;
    const float dz  = fy - iz0;

    auto vertexCount = getVertexCount();

    if (ix0 < 0 || ix0 > vertexCount[0] - 1 || iz0 < 0 || iz0 > vertexCount[1] - 1) {
        return std::nullopt;
    }

    ix0 = std::clamp(ix0, 0, vertexCount[0] - 1);
    iz0 = std::clamp(iz0, 0, vertexCount[1] - 1);
    ix1 = std::clamp(ix1, 0, vertexCount[0] - 1);
    iz1 = std::clamp(iz1, 0, vertexCount[1] - 1);

    Vec3 a = getNormal(ix0, iz0);
    Vec3 b = getNormal(ix1, iz0);
    Vec3 c = getNormal(ix0, iz1);
    Vec3 d = getNormal(ix1, iz1);
    Vec3 m;
    Vec3::add(b, c, &m);
    m.scale(0.5F);

    if (dx + dz <= 1.0F) {
        // d = m + (m - a);
        d.set(m);
        d.subtract(a);
        d.add(m);
    } else {
        // a = m + (m - d);
        a.set(m);
        a.subtract(d);
        a.add(m);
    }

    Vec3 n1 = a.lerp(b, dx);
    Vec3 n2 = c.lerp(d, dx);
    Vec3 n  = n1.lerp(n2, dz);

    return n;
}

void Terrain::setWeight(int32_t i, int32_t j, const Vec4 &w) {
    const int32_t index = j * _weightMapSize * _blockCount[0] + i;

    _weights[index * 4 + 0] = w.x * 255.F;
    _weights[index * 4 + 1] = w.y * 255.F;
    _weights[index * 4 + 2] = w.z * 255.F;
    _weights[index * 4 + 3] = w.w * 255.F;
}

Vec4 Terrain::getWeight(int32_t i, int32_t j) const {
    const int32_t index = j * _weightMapSize * _blockCount[0] + i;

    Vec4 w;
    w.x = _weights[index * 4 + 0] / 255.F;
    w.y = _weights[index * 4 + 1] / 255.F;
    w.z = _weights[index * 4 + 2] / 255.F;
    w.w = _weights[index * 4 + 3] / 255.F;

    return w;
}

std::optional<Vec4> Terrain::getWeightAt(float x, float y) const {
    const int32_t uWeigthComplexity = getWeightMapSize() * _blockCount[0];
    const int32_t vWeigthComplexity = getWeightMapSize() * _blockCount[1];
    if (uWeigthComplexity == 0 || vWeigthComplexity == 0) {
        return std::nullopt;
    }

    const float fx = x / uWeigthComplexity;
    const float fy = y / vWeigthComplexity;

    int32_t     ix0 = static_cast<int32_t>(std::floor(fx));
    int32_t     iz0 = static_cast<int32_t>(std::floor(fy));
    int32_t     ix1 = ix0 + 1;
    int32_t     iz1 = iz0 + 1;
    const float dx  = fx - ix0;
    const float dz  = fy - iz0;

    if (ix0 < 0 || ix0 > uWeigthComplexity - 1 || iz0 < 0 || iz0 > vWeigthComplexity - 1) {
        return std::nullopt;
    }

    ix0 = std::clamp(ix0, 0, uWeigthComplexity - 1);
    iz0 = std::clamp(iz0, 0, vWeigthComplexity - 1);
    ix1 = std::clamp(ix1, 0, uWeigthComplexity - 1);
    iz1 = std::clamp(iz1, 0, vWeigthComplexity - 1);

    Vec4 a = getWeight(ix0, iz0);
    Vec4 b = getWeight(ix1, iz0);
    Vec4 c = getWeight(ix0, iz1);
    Vec4 d = getWeight(ix1, iz1);
    Vec4 m;
    Vec4::add(b, c, &m);
    m.scale(0.5F);

    if (dx + dz <= 1.0F) {
        d = Vec4{};
        Vec4::subtract(m, a, &d);
        d.add(m);
    } else {
        a = Vec4{};
        Vec4::subtract(m, d, &a);
        a.add(m);
    }

    Vec4 n1;
    Vec4 n2;
    Vec4 n;
    Vec4::lerp(a, b, dx, &n1);
    Vec4::lerp(c, d, dx, &n2);
    Vec4::lerp(n1, n2, dz, &n);

    return n;
}

TerrainLayer::Ptr Terrain::getMaxWeightLayerAt(float x, float y) {
    const int32_t uWeigthComplexity = getWeightMapSize() * _blockCount[0];
    const int32_t vWeigthComplexity = getWeightMapSize() * _blockCount[1];
    if (uWeigthComplexity == 0 || vWeigthComplexity == 0) {
        return nullptr;
    }

    const float   fx  = x / uWeigthComplexity;
    const float   fy  = y / vWeigthComplexity;
    const int32_t ix0 = static_cast<int32_t>(std::floor(fx));
    const int32_t iz0 = static_cast<int32_t>(std::floor(fy));

    if (ix0 < 0 || ix0 > uWeigthComplexity - 1 || iz0 < 0 || iz0 > vWeigthComplexity - 1) {
        return nullptr;
    }

    const Vec4    w     = getWeight(ix0, iz0);
    const int32_t bx    = static_cast<int32_t>(std::floor(x / getWeightMapSize()));
    const int32_t by    = static_cast<int32_t>(std::floor(y / getWeightMapSize()));
    TerrainBlock *block = getBlock(bx, by);

    int32_t i = 0;
    //cjh TODO: what's w[i] means?   if (w.y > w[i] && block->getLayer(1) != -1) {
    //        i = 1;
    //    }
    //    if (w.y > w[i] && block->getLayer(2) != -1) {
    //        i = 2;
    //    }
    //    if (w.z > w[i] && block->getLayer(3) != -1) {
    //        i = 3;
    //    }

    i = block->getLayer(i);

    return getLayer(i);
}

std::optional<Vec3> Terrain::rayCheck(const Vec3 &start, const Vec3 &dir, float step, bool worldSpace /* = true*/) {
    constexpr int32_t MAX_COUNT = 2000;

    auto trace = start;
    if (worldSpace) {
        Vec3::subtract(start, getNode()->getWorldPosition(), &trace);
    }

    Vec3 delta;
    delta.set(dir);
    delta.scale(step);

    std::optional<Vec3> position;

    if (dir == Vec3{0, 1, 0}) {
        std::optional<float> y = getHeightAt(trace.x, trace.z);
        if (y.has_value() && trace.y <= y) {
            position = Vec3{trace.x, y.value(), trace.z};
        }
    } else if (dir == Vec3{0, -1, 0}) {
        std::optional<float> y = getHeightAt(trace.x, trace.z);
        if (y.has_value() && trace.y >= y) {
            position = Vec3{trace.x, y.value(), trace.z};
        }
    } else {
        int32_t i = 0;

        // 优先大步进查找
        while (i++ < MAX_COUNT) {
            std::optional<float> y = getHeightAt(trace.x, trace.z);
            if (y.has_value() && trace.y <= y) {
                break;
            }

            trace.add(dir);
        }

        // 穷举法
        while (i++ < MAX_COUNT) {
            std::optional<float> y = getHeightAt(trace.x, trace.z);
            if (y.has_value() && trace.y <= y) {
                position = Vec3{trace.x, y.value(), trace.z};
                break;
            }

            trace.add(delta);
        }
    }

    return position;
}

void Terrain::resetLightmap(bool enable) {
    _lightmapInfos.clear();
    if (enable) {
        for (int32_t i = 0; i < _blockCount[0] * _blockCount[1]; ++i) {
            _lightmapInfos.emplace_back(TerrainBlockLightmapInfo{});
        }
    }
}

void Terrain::updateLightmap(int32_t blockId, Texture2D *tex, float uOff, float vOff, float uScale, float vScale) {
    _lightmapInfos[blockId].texture = tex;
    _lightmapInfos[blockId].UOff    = uOff;
    _lightmapInfos[blockId].VOff    = vOff;
    _lightmapInfos[blockId].UScale  = uScale;
    _lightmapInfos[blockId].VScale  = vScale;
    _blocks[blockId]->updateLightmap(&_lightmapInfos[blockId]);
}

Vec3 Terrain::calcNormal(float x, float z) {
    float flip = 1.F;
    Vec3  here = getPosition(x, z);
    Vec3  right;
    Vec3  up;

    auto vertexCount = getVertexCount();
    if (x < vertexCount[0] - 1) {
        right = getPosition(x + 1, z);
    } else {
        flip *= -1.F;
        right = getPosition(x - 1, z);
    }

    if (z < vertexCount[1] - 1) {
        up = getPosition(x, z + 1);
    } else {
        flip *= -1.F;
        up = getPosition(x, z - 1);
    }

    right.subtract(here);
    up.subtract(here);

    Vec3 normal;
    normal.set(up);
    normal.cross(right);
    normal.scale(flip);
    normal.normalize();

    return normal;
}

void Terrain::buildNormals() {
    auto    vertexCount = getVertexCount();
    int32_t index       = 0;
    for (int32_t y = 0; y < vertexCount[1]; ++y) {
        for (int32_t x = 0; x < vertexCount[0]; ++x) {
            Vec3 n = calcNormal(x, y);

            _normals[index * 3 + 0] = n.x;
            _normals[index * 3 + 1] = n.y;
            _normals[index * 3 + 2] = n.z;
            index += 1;
        }
    }
}

void Terrain::buildImp(bool restore /* = false*/) {
    if (isValid()) {
        return;
    }

    TerrainAsset *terrainAsset = _asset;
    if (!restore && terrainAsset != nullptr) {
        _tileSize      = terrainAsset->getTileSize();
        _blockCount    = terrainAsset->getBlockCount();
        _weightMapSize = terrainAsset->getWeightMapSize();
        _lightMapSize  = terrainAsset->getLightMapSize();
        _heights       = terrainAsset->getHeights();
        _weights       = terrainAsset->getWeights();
        _layerBuffer   = terrainAsset->getLayerBuffer();

        // build layers
        for (size_t i = 0; i < _layerList.size(); ++i) {
            _layerList[i] = nullptr;
        }

        if (terrainAsset->getVersion() < TERRAIN_DATA_VERSION5) {
            for (size_t i = 0; i < terrainAsset->getLayerBinaryInfos().size(); ++i) {
                auto        layer     = std::make_shared<TerrainLayer>();
                const auto &layerInfo = terrainAsset->getLayerBinaryInfos()[i];
                layer->tileSize       = layerInfo.tileSize;
                //cjh TODO:                legacyCC.assetManager.loadAny(layerInfo.detailMapId, (err, asset) => {
                //                    layer.detailMap = asset;
                //                });
                //
                //                if (layerInfo.normalMapId !== '') {
                //                    legacyCC.assetManager.loadAny(layerInfo.normalMapId, (err, asset) => {
                //                        layer.normalMap = asset;
                //                    });
                //                }

                layer->roughness = layerInfo.roughness;
                layer->metallic  = layerInfo.metallic;

                _layerList[layerInfo.slot] = layer;
            }
        } else {
            for (size_t i = 0; i < terrainAsset->getLayerInfos().size(); ++i) {
                auto        layer     = std::make_shared<TerrainLayer>();
                const auto &layerInfo = terrainAsset->getLayerInfos()[i];
                layer->tileSize       = layerInfo.tileSize;
                layer->detailMap      = layerInfo.detailMap;
                layer->normalMap      = layerInfo.normalMap;
                layer->roughness      = layerInfo.roughness;
                layer->metallic       = layerInfo.metallic;

                _layerList[layerInfo.slot] = layer;
            }
        }
    }

    if (_blockCount[0] == 0 || _blockCount[1] == 0) {
        return;
    }

    // build heights & normals
    auto          vc          = getVertexCount();
    const int32_t vertexCount = vc[0] * vc[1];
    if (_heights.empty() || _heights.length() != vertexCount) {
        _heights.reset(vertexCount);
        _normals.resize(vertexCount * 3);

        for (int32_t i = 0; i < vertexCount; ++i) {
            _heights[i]         = TERRAIN_HEIGHT_BASE;
            _normals[i * 3 + 0] = 0;
            _normals[i * 3 + 1] = 1;
            _normals[i * 3 + 2] = 0;
        }
    } else {
        _normals.resize(vertexCount * 3);
        buildNormals();
    }

    // build layer buffer
    const int32_t layerBufferSize = _blockCount[0] * _blockCount[1] * TERRAIN_MAX_BLEND_LAYERS;
    if (_layerBuffer.empty() || _layerBuffer.size() != layerBufferSize) {
        _layerBuffer.resize(layerBufferSize);
        for (int32_t i = 0; i < layerBufferSize; ++i) {
            _layerBuffer[i] = -1;
        }
    }

    // build weights
    const int32_t weightMapComplexityU = _weightMapSize * _blockCount[0];
    const int32_t weightMapComplexityV = _weightMapSize * _blockCount[1];
    if (_weights.length() != weightMapComplexityU * weightMapComplexityV * 4) {
        _weights.reset(weightMapComplexityU * weightMapComplexityV * 4);
        for (int32_t i = 0; i < weightMapComplexityU * weightMapComplexityV; ++i) {
            _weights[i * 4 + 0] = 255;
            _weights[i * 4 + 1] = 0;
            _weights[i * 4 + 2] = 0;
            _weights[i * 4 + 3] = 0;
        }
    }

    // build blocks
    for (int32_t j = 0; j < _blockCount[1]; ++j) {
        for (int32_t i = 0; i < _blockCount[0]; ++i) {
            _blocks.emplace_back(new TerrainBlock(this, i, j));
        }
    }

    for (auto *block : _blocks) {
        block->build();
    }
}

bool Terrain::rebuildHeights(const TerrainInfo &info) {
    auto vertexCount     = getVertexCount();
    auto infoVertexCount = info.getVertexCount();
    if (vertexCount[0] == infoVertexCount[0] && vertexCount[1] == infoVertexCount[1]) {
        return false;
    }

    Uint16Array heights{static_cast<uint32_t>(infoVertexCount[0] * infoVertexCount[1])};
    for (uint32_t i = 0; i < heights.length(); ++i) {
        heights[i] = TERRAIN_HEIGHT_BASE;
    }

    const int32_t w = std::min(vertexCount[0], infoVertexCount[0]);
    const int32_t h = std::min(vertexCount[1], infoVertexCount[1]);

    for (int32_t j = 0; j < h; ++j) {
        for (int32_t i = 0; i < w; ++i) {
            const int32_t index0 = j * infoVertexCount[0] + i;
            const int32_t index1 = j * vertexCount[0] + i;

            heights[index0] = _heights[index1];
        }
    }

    _heights = heights;

    return true;
}

bool Terrain::rebuildLayerBuffer(const TerrainInfo &info) {
    if (_blockCount[0] == info.blockCount[0] && _blockCount[1] == info.blockCount[1]) {
        return false;
    }

    std::vector<int16_t> layerBuffer;
    layerBuffer.resize(info.blockCount[0] * info.blockCount[1] * TERRAIN_MAX_BLEND_LAYERS, -1);

    const int32_t w = std::min(_blockCount[0], info.blockCount[0]);
    const int32_t h = std::min(_blockCount[1], info.blockCount[1]);
    for (int32_t j = 0; j < h; ++j) {
        for (int32_t i = 0; i < w; ++i) {
            const int32_t index0 = j * info.blockCount[0] + i;
            const int32_t index1 = j * _blockCount[0] + i;

            for (int32_t l = 0; l < TERRAIN_MAX_BLEND_LAYERS; ++l) {
                layerBuffer[index0 * TERRAIN_MAX_BLEND_LAYERS + l] = _layerBuffer[index1 * TERRAIN_MAX_BLEND_LAYERS + l];
            }
        }
    }

    _layerBuffer = layerBuffer;

    return true;
}

bool Terrain::rebuildWeights(const TerrainInfo &info) {
    const int16_t oldWeightMapSize        = _weightMapSize;
    const int32_t oldWeightMapComplexityU = _weightMapSize * _blockCount[0];
    const int32_t oldWeightMapComplexityV = _weightMapSize * _blockCount[1];

    const int32_t weightMapComplexityU = info.weightMapSize * info.blockCount[0];
    const int32_t weightMapComplexityV = info.weightMapSize * info.blockCount[1];

    if (weightMapComplexityU == oldWeightMapComplexityU && weightMapComplexityV == oldWeightMapComplexityV) {
        return false;
    }

    Uint8Array weights{static_cast<uint32_t>(weightMapComplexityU * weightMapComplexityV * 4)};

    for (int32_t i = 0; i < weightMapComplexityU * weightMapComplexityV; ++i) {
        weights[i * 4 + 0] = 255;
        weights[i * 4 + 1] = 0;
        weights[i * 4 + 2] = 0;
        weights[i * 4 + 3] = 0;
    }

    const int32_t w = std::min(info.blockCount[0], _blockCount[0]);
    const int32_t h = std::min(info.blockCount[1], _blockCount[1]);

    // get weight
    auto getOldWeight = [&](int32_t _i, int32_t _j, const Uint8Array &_weights) -> Vec4 {
        const int32_t index = _j * oldWeightMapComplexityU + _i;

        Vec4 weight;
        weight.x = _weights[index * 4 + 0] / 255.0F;
        weight.y = _weights[index * 4 + 1] / 255.0F;
        weight.z = _weights[index * 4 + 2] / 255.0F;
        weight.w = _weights[index * 4 + 3] / 255.0F;

        return weight;
    };

    // sample weight
    auto sampleOldWeight = [&](float _x, float _y, float _xOff, float _yOff, const Uint8Array &_weights) {
        const int32_t ix0 = std::floor(_x);
        const int32_t iz0 = std::floor(_y);
        const int32_t ix1 = ix0 + 1;
        const int32_t iz1 = iz0 + 1;
        const float   dx  = _x - ix0;
        const float   dz  = _y - iz0;

        Vec4 a = getOldWeight(ix0 + _xOff, iz0 + _yOff, _weights);
        Vec4 b = getOldWeight(ix1 + _xOff, iz0 + _yOff, _weights);
        Vec4 c = getOldWeight(ix0 + _xOff, iz1 + _yOff, _weights);
        Vec4 d = getOldWeight(ix1 + _xOff, iz1 + _yOff, _weights);
        Vec4 m;
        Vec4::add(b, c, &m);
        m.scale(0.5F);

        if (dx + dz <= 1.0F) {
            d.set(m);
            d.subtract(a);
            d.add(m);
        } else {
            a.set(m);
            a.subtract(d);
            a.add(m);
        }

        Vec4 n1;
        Vec4 n2;
        Vec4 n;
        Vec4::lerp(a, b, dx, &n1);
        Vec4::lerp(c, d, dx, &n2);
        Vec4::lerp(n1, n2, dz, &n);

        return n;
    };

    // fill new weights
    for (int32_t j = 0; j < h; ++j) {
        for (int32_t i = 0; i < w; ++i) {
            const int32_t uOff = i * oldWeightMapSize;
            const int32_t vOff = j * oldWeightMapSize;

            for (int32_t v = 0; v < info.weightMapSize; ++v) {
                for (int32_t u = 0; u < info.weightMapSize; ++u) {
                    Vec4 w;
                    if (info.weightMapSize == oldWeightMapSize) {
                        w = getOldWeight(u + uOff, v + vOff, _weights);
                    } else {
                        const float x = static_cast<float>(u) / (info.weightMapSize - 1) * (oldWeightMapSize - 1);
                        const float y = static_cast<float>(v) / (info.weightMapSize - 1) * (oldWeightMapSize - 1);
                        w             = sampleOldWeight(x, y, uOff, vOff, _weights);
                    }

                    const int32_t du    = i * info.weightMapSize + u;
                    const int32_t dv    = j * info.weightMapSize + v;
                    const int32_t index = dv * weightMapComplexityU + du;

                    weights[index * 4 + 0] = w.x * 255;
                    weights[index * 4 + 1] = w.y * 255;
                    weights[index * 4 + 2] = w.z * 255;
                    weights[index * 4 + 3] = w.w * 255;
                }
            }
        }
    }

    _weights = weights;
}

// Override functions
void Terrain::onLoad() {
    gfx::Device *gfxDevice = gfx::Device::getInstance();

    // initialize shared index buffer
    Uint16Array indexData(TERRAIN_BLOCK_TILE_COMPLEXITY * TERRAIN_BLOCK_TILE_COMPLEXITY * 6);

    int16_t index = 0;
    for (int16_t j = 0; j < TERRAIN_BLOCK_TILE_COMPLEXITY; ++j) {
        for (int16_t i = 0; i < TERRAIN_BLOCK_TILE_COMPLEXITY; ++i) {
            const int16_t a = j * TERRAIN_BLOCK_VERTEX_COMPLEXITY + i;
            const int16_t b = j * TERRAIN_BLOCK_VERTEX_COMPLEXITY + i + 1;
            const int16_t c = (j + 1) * TERRAIN_BLOCK_VERTEX_COMPLEXITY + i;
            const int16_t d = (j + 1) * TERRAIN_BLOCK_VERTEX_COMPLEXITY + i + 1;

            // face 1
            indexData[index++] = a;
            indexData[index++] = c;
            indexData[index++] = b;

            // face 2
            indexData[index++] = b;
            indexData[index++] = c;
            indexData[index++] = d;
        }
    }

    _sharedIndexBuffer = gfxDevice->createBuffer(gfx::BufferInfo{
        gfx::BufferUsageBit::INDEX | gfx::BufferUsageBit::TRANSFER_DST,
        gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
        Uint16Array::BYTES_PER_ELEMENT * TERRAIN_BLOCK_TILE_COMPLEXITY * TERRAIN_BLOCK_TILE_COMPLEXITY * 6,
        Uint16Array::BYTES_PER_ELEMENT,
    });
    _sharedIndexBuffer->update(indexData.buffer()->getData());
}

void Terrain::onEnable() {
    if (_blocks.empty()) {
        buildImp();
    }
}

void Terrain::onDisable() {
    for (auto *block : _blocks) {
        block->destroy();
        delete block;
    }
    _blocks.clear();
}

void Terrain::onDestroy() {
    for (auto *block : _blocks) {
        block->destroy();
        delete block;
    }
    _blocks.clear();

    for (int32_t i = 0; i < _layerList.size(); ++i) {
        _layerList[i] = nullptr;
    }

    if (_sharedIndexBuffer != nullptr) {
        _sharedIndexBuffer->destroy();
        CC_SAFE_DELETE(_sharedIndexBuffer);
    }
}

void Terrain::onRestore() {
    onDisable();
    onLoad();
    buildImp(true);
}

void Terrain::update(float deltaTime) {
    for (auto *block : _blocks) {
        block->update();
    }
}

} // namespace cc
