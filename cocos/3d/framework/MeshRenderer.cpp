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

#include "3d/framework/MeshRenderer.h"
#include "3d/assets/Mesh.h"
#include "3d/assets/MorphRendering.h"
#include "core/Root.h"
#include "core/builtin/BuiltinResMgr.h"
#include "core/scene-graph/Node.h"
#include "scene/BakedSkinningModel.h"
#include "scene/MorphModel.h"
#include "scene/Pass.h"
#include "scene/RenderScene.h"
#include "scene/SkinningModel.h"

namespace cc {

void MeshRenderer::setMesh(Mesh *val) {
    Mesh *old  = _mesh;
    Mesh *mesh = _mesh = val;
    if (mesh != nullptr) {
        mesh->initialize();
    }

    initSubMeshShapesWeights();
    watchMorphInMesh();
    onMeshChanged(old);
    updateModels();
    if (isEnabledInHierarchy()) {
        attachToScene();
    }
    updateCastShadow();
    updateReceiveShadow();
}

void MeshRenderer::onLoad() {
    if (_mesh) {
        _mesh->initialize();
    }
    if (!validateShapeWeights()) {
        initSubMeshShapesWeights();
    }
    watchMorphInMesh();
    updateModels();
    updateCastShadow();
    updateReceiveShadow();
}

void MeshRenderer::onRestore() {
    updateModels();
    updateCastShadow();
    updateReceiveShadow();
}

void MeshRenderer::onEnable() {
    if (!_model) {
        updateModels();
    }
    attachToScene();
}

void MeshRenderer::onDisable() {
    if (_model) {
        detachFromScene();
    }
}

void MeshRenderer::onDestroy() {
    if (_model) {
        Root::getInstance()->destroyModel(_model);
        _model = nullptr;
        _models.clear();
    }

    CC_SAFE_DESTROY(_morphInstance);
}

float MeshRenderer::getWeight(index_t subMeshIndex, index_t shapeIndex) const {
    CC_ASSERT(subMeshIndex < _subMeshShapesWeights.size());
    const auto &shapeWeights = _subMeshShapesWeights[subMeshIndex];
    CC_ASSERT(shapeIndex < shapeWeights.size());
    return shapeWeights[shapeIndex];
}

void MeshRenderer::setWeights(const std::vector<float> &weights, index_t subMeshIndex) {
    if (subMeshIndex >= _subMeshShapesWeights.size()) {
        return;
    }
    const auto &shapeWeights = _subMeshShapesWeights[subMeshIndex];
    if (shapeWeights.size() != weights.size()) {
        return;
    }
    _subMeshShapesWeights[subMeshIndex] = weights;
    uploadSubMeshShapesWeights(subMeshIndex);
}

void MeshRenderer::setWeight(float weight, index_t subMeshIndex, index_t shapeIndex) {
    if (subMeshIndex >= _subMeshShapesWeights.size()) {
        return;
    }
    auto &shapeWeights = _subMeshShapesWeights[subMeshIndex];
    if (shapeIndex >= shapeWeights.size()) {
        return;
    }
    shapeWeights[shapeIndex] = weight;
    uploadSubMeshShapesWeights(subMeshIndex);
}

void MeshRenderer::setInstancedAttribute(const std::string &name, const TypedArray &value) {
    if (_model == nullptr) return;
    const auto &             attributes = _model->getInstanceAttributes();
    std::vector<TypedArray> &views      = _model->getInstancedAttributeBlock()->views;
    for (uint32_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i].name == name) {
            views[i] = value;
            break;
        }
    }
}

void MeshRenderer::updateLightmap(Texture2D *lightmap, float uOff, float vOff, float uScale, float vScale) {
    lightmapSettings.texture   = lightmap;
    lightmapSettings.uvParam.x = uOff;
    lightmapSettings.uvParam.y = vOff;
    lightmapSettings.uvParam.z = uScale;
    lightmapSettings.uvParam.w = vScale;

    onUpdateLightingmap();
}

void MeshRenderer::updateModels() {
    if (!isEnabledInHierarchy() || !_mesh) {
        return;
    }

    scene::Model *model = _model;
    if (model != nullptr) {
        model->destroy();
        model->initialize();
        model->setTransform(static_cast<Node *>(_node)); //cjh TODO: remove BaseNode
        model->setNode(static_cast<Node *>(_node));      //cjh TODO: remove BaseNode
    } else {
        createModel();
    }

    if (_model) {
        _model->createBoundingShape(_mesh->getStruct().minPosition, _mesh->getStruct().maxPosition);
        updateModelParams();
        onUpdateLightingmap();
    }
}

void MeshRenderer::createModel() {
    bool preferMorphOverPlain = !!_morphInstance;
    // Note we only change to use `MorphModel` if
    // we are required to render morph and the `_modelType` is exactly the basic `Model`.
    // We do this since the `_modelType` might be changed in classes derived from `Model`.
    // We shall not overwrite it.
    // Please notice that we do not enforce that
    // derived classes should use a morph-able model type(i.e. model type derived from `MorphModel`).
    // So we should take care of the edge case.
    if (preferMorphOverPlain && _modelType == scene::Model::Type::DEFAULT) {
        _model = Root::getInstance()->createModel<scene::MorphModel>();
    } else {
        switch (_modelType) {
            case scene::Model::Type::DEFAULT:
                _model = Root::getInstance()->createModel<scene::Model>();
                break;
            case scene::Model::Type::SKINNING:
                _model = Root::getInstance()->createModel<scene::SkinningModel>();
                break;
            case scene::Model::Type::BAKED_SKINNING:
                _model = Root::getInstance()->createModel<scene::BakedSkinningModel>();
                break;
            case scene::Model::Type::PARTICLE_BATCH:
                //cjh todo:
                break;
            case scene::Model::Type::LINE:
                //cjh todo:
                break;
            default:
                _model = Root::getInstance()->createModel<scene::Model>();
                break;
        }
    }

    _model->setVisFlags(static_cast<uint32_t>(getVisibility())); //cjh TODO: remove static_cast
    _model->setNode(static_cast<Node *>(_node));                 //cjh TODO: remove BaseNode
    _model->setTransform(static_cast<Node *>(_node));

    _models.clear();
    _models.emplace_back(_model);
    if (_morphInstance != nullptr) {
        auto *morphModel = dynamic_cast<scene::MorphModel *>(_model);
        if (morphModel != nullptr) {
            morphModel->setMorphRendering(_morphInstance);
        }
    }
}

void MeshRenderer::attachToScene() {
    if (_node->getScene() == nullptr || _model == nullptr) {
        return;
    }
    auto *renderScene = getRenderScene();
    if (_model->getScene() != nullptr) {
        detachFromScene();
    }
    renderScene->addModel(_model);
}

void MeshRenderer::detachFromScene() {
    if (_model != nullptr && _model->getScene() != nullptr) {
        _model->getScene()->removeModel(_model);
    }
}

void MeshRenderer::onUpdateLightingmap() {
    if (_model != nullptr) {
        _model->updateLightingmap(lightmapSettings.texture, lightmapSettings.uvParam);
    }

    Float32Array attr(4);
    attr[0] = lightmapSettings.uvParam.x;
    attr[1] = lightmapSettings.uvParam.y;
    attr[2] = lightmapSettings.uvParam.z;
    attr[3] = lightmapSettings.uvParam.w;

    setInstancedAttribute("a_lightingMapUVParam", attr);
}

void MeshRenderer::onMaterialModified(index_t index, Material *material) {
    if (!_model || !_model->isInited()) {
        return;
    }

    onRebuildPSO(index, (material != nullptr ? material : getBuiltinMaterial()));
}

void MeshRenderer::onRebuildPSO(index_t index, Material *material) {
    if (!_model || !_model->isInited()) {
        return;
    }

    _model->setDynamicBatching(isBatchingEnabled());
    _model->setSubModelMaterial(index, material);
    onUpdateLightingmap();
}

void MeshRenderer::clearMaterials() {
    if (!_model) {
        return;
    }

    const auto &subModels = _model->getSubModels();
    for (index_t i = 0; i < subModels.size(); ++i) {
        onMaterialModified(i, nullptr);
    }
}

void MeshRenderer::onVisibilityChange(Layers::Enum val) {
    if (!_model) {
        return;
    }

    _model->setVisFlags(static_cast<uint32_t>(val)); //cjh todo: remove static_cast
}

void MeshRenderer::updateCastShadow() {
    if (_model == nullptr) return;
    if (_shadowCastingMode == ModelShadowCastingMode::OFF) {
        _model->setCastShadow(false);
    } else {
        CC_ASSERT(_shadowCastingMode == ModelShadowCastingMode::ON);
        _model->setCastShadow(true);
    }
}

void MeshRenderer::updateReceiveShadow() {
    if (_model == nullptr) return;
    if (_shadowReceivingMode == ModelShadowReceivingMode::OFF) {
        _model->setReceiveShadow(false);
    } else {
        _model->setReceiveShadow(true);
    }
}

void MeshRenderer::updateModelParams() {
    if (!_mesh || !_model) {
        return;
    }
    _node->setChangedFlags(_node->getChangedFlags() | static_cast<uint32_t>(TransformBit::POSITION));
    _model->getTransform()->setChangedFlags(_model->getTransform()->getChangedFlags() | static_cast<uint32_t>(TransformBit::POSITION));
    _model->setDynamicBatching(isBatchingEnabled());
    const uint32_t meshCount     = _mesh ? _mesh->getRenderingSubMeshes().size() : 0;
    const auto &   renderingMesh = _mesh->getRenderingSubMeshes();
    if (!renderingMesh.empty()) {
        for (index_t i = 0; i < meshCount; ++i) {
            Material *material = getRenderMaterial(i);
            if (material && !material->isValid()) {
                material = nullptr;
            }
            RenderingSubMesh *subMeshData = renderingMesh[i];
            if (subMeshData) {
                _model->initSubModel(i, subMeshData, (material != nullptr ? material : getBuiltinMaterial()));
            }
        }
    }
    _model->setEnabled(true);
}

Material *MeshRenderer::getBuiltinMaterial() {
    // classic ugly pink indicating missing material
    return BuiltinResMgr::getInstance()->get<Material>("missing-material");
}

bool MeshRenderer::isBatchingEnabled() {
    for (auto *mat : _materials) {
        if (!mat) {
            continue;
        }

        for (auto *pass : mat->getPasses()) {
            if (pass->getBatchingScheme() != scene::BatchingSchemes::NONE) {
                return true;
            }
        }
    }
    return false;
}

void MeshRenderer::watchMorphInMesh() {
    CC_SAFE_DESTROY(_morphInstance);

    if (!_enableMorph) return;

    if (_mesh == nullptr || !_mesh->getStruct().morph.has_value() || _mesh->morphRendering == nullptr) return;

    _morphInstance = _mesh->morphRendering->createInstance();
    for (index_t iSubMesh = 0; iSubMesh < _mesh->getStruct().primitives.size(); iSubMesh++) {
        uploadSubMeshShapesWeights(iSubMesh);
    }

    if (_model != nullptr) {
        auto *morphModel = dynamic_cast<scene::MorphModel *>(_model);
        if (morphModel != nullptr) {
            morphModel->setMorphRendering(_morphInstance);
        }
    }
}

void MeshRenderer::initSubMeshShapesWeights() {
    _subMeshShapesWeights.clear();

    if (_mesh == nullptr) return;

    const auto &morph = _mesh->getStruct().morph;
    if (!morph.has_value()) return;

    const auto &                 commonWeights = morph->weights;
    const auto &                 subMeshMorphs = morph.value().subMeshMorphs;
    std::vector<MeshWeightsType> shapesWeights;

    for (const auto &subMeshMorph : subMeshMorphs) {
        if (subMeshMorph.weights.has_value()) {
            shapesWeights.emplace_back(subMeshMorph.weights.value());
        } else if (commonWeights.has_value()) {
            CC_ASSERT(commonWeights.value().size() == subMeshMorph.targets.size());
            shapesWeights.emplace_back(morph->weights.value());
        } else {
            shapesWeights.emplace_back(MeshWeightsType(subMeshMorph.targets.size()));
        }
    }
    _subMeshShapesWeights = shapesWeights;
}

bool MeshRenderer::validateShapeWeights() {
    if (_mesh == nullptr || !_mesh->getStruct().morph.has_value()) {
        return _subMeshShapesWeights.empty();
    }

    const auto &morph = _mesh->getStruct().morph;
    if (morph->subMeshMorphs.size() != _subMeshShapesWeights.size()) {
        return false;
    }
    for (index_t subMeshIdx = 0; subMeshIdx < _subMeshShapesWeights.size(); ++subMeshIdx) {
        uint32_t shapeCount = _subMeshShapesWeights[subMeshIdx].size();
        if (morph->subMeshMorphs[subMeshIdx].targets.size() == shapeCount) continue;
        return false;
    }
    return true;
}

void MeshRenderer::uploadSubMeshShapesWeights(index_t subMeshIndex) {
    if (_morphInstance != nullptr) {
        _morphInstance->setWeights(subMeshIndex, _subMeshShapesWeights[subMeshIndex]);
    }
}

} // namespace cc
