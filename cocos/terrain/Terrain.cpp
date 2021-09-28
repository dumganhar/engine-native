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
    vertexBuffer->update(vertexData.buffer().get());

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
    return _lightmapInfo.has_value() ? _lightmapInfo.value().texture : nullptr;
}

Vec4 TerrainBlock::getLightmapUVParam() const {
    if (_lightmapInfo.has_value()) {
        return {
            _lightmapInfo.value().UOff,
            _lightmapInfo.value().VOff,
            _lightmapInfo.value().UScale,
            _lightmapInfo.value().VScale};
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

    _renderable->_meshData->getVertexBuffers()[0]->update(vertexData.buffer().get());
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
    _weightMap->uploadData(weightData.buffer().get()->getData());
}

void TerrainBlock::updateLightmap(const TerrainBlockLightmapInfo &info) {
    _lightmapInfo = info;
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

const TerrainBlockLightmapInfo &Terrain::getLightmapInfo(int32_t i, int32_t j) const {
}

std::array<int32_t, 4> Terrain::getBlockLayers(int32_t i, int32_t j) const {
}

int32_t Terrain::getBlockLayer(int32_t i, int32_t j, int32_t index) const {
}

Vec3 Terrain::getPosition(int32_t i, int32_t j) {
}

void Terrain::setHeight(int32_t i, int32_t j, float h) {
}

float Terrain::getHeight(int32_t i, int32_t j) const {
}

float Terrain::getHeightClamp(int32_t i, int32_t j) const {
}

std::optional<float> Terrain::getHeightAt(float x, float y) const {
}

void Terrain::setNormal(int32_t i, int32_t j, const Vec3 &n) {
}

Vec3 Terrain::getNormal(int32_t i, int32_t j) const {
}

Vec3 Terrain::getNormalAt(float x, float y) const {
}

void Terrain::setWeight(int32_t i, int32_t j, const Vec4 &w) {
}

Vec4 Terrain::getWeight(int32_t i, int32_t j) const {
}

Vec4 Terrain::getWeightAt(float x, float y) const {
}

TerrainLayer::Ptr Terrain::getMaxWeightLayerAt(float x, float y) {
}

Vec3 Terrain::rayCheck(const Vec3 &start, const Vec3 &dir, float step, bool worldSpace /* = true*/) {
}

void Terrain::resetLightmap(bool enable) {
}

void Terrain::updateLightmap(int32_t blockId, Texture2D *tex, float uOff, float vOff, float uScale, float vScale) {
}

Vec3 Terrain::calcNormal(float x, float z) {
}

void Terrain::buildNormals() {
}

// Override functions
void Terrain::onLoad() {
}

void Terrain::onEnable() {
}

void Terrain::onDisable() {
}

void Terrain::onDestroy() {
}

void Terrain::onRestore() {
}

void Terrain::update(float deltaTime) {
}

} // namespace cc
