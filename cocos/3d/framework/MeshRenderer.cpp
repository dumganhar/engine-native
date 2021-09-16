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

    //cjh    _initSubMeshShapesWeights();
    //    _watchMorphInMesh();
    onMeshChanged(old);
    updateModels();
    if (isEnabledInHierarchy()) {
        attachToScene();
    }
    //cjh    updateCastShadow();
    //    updateReceiveShadow();
}

void MeshRenderer::onLoad() {
    if (_mesh) {
        _mesh->initialize();
    }
    //cjh    if (!_validateShapeWeights()) {
    //        _initSubMeshShapesWeights();
    //    }
    //    _watchMorphInMesh();
    updateModels();
    //cjh    _updateCastShadow();
    //    _updateReceiveShadow();
}

void MeshRenderer::onRestore() {
    updateModels();
    //cjh    _updateCastShadow();
    //    _updateReceiveShadow();
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
        //cjh        onUpdateLightingmap();
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
    //cjh    onUpdateLightingmap();
}

void MeshRenderer::clearMaterials() {
    if (!_model) {
        return;
    }

    const auto &subModels = _model->getSubModels();
    for (size_t i = 0; i < subModels.size(); ++i) {
        onMaterialModified(i, nullptr);
    }
}

void MeshRenderer::onVisibilityChange(Layers::Enum val) {
    if (!_model) {
        return;
    }

    _model->setVisFlags(static_cast<uint32_t>(val)); //cjh todo: remove static_cast
}

void MeshRenderer::updateModelParams() {
    if (!_mesh || !_model) {
        return;
    }
    _node->setChangedFlags(_node->getChangedFlags() | static_cast<uint32_t>(TransformBit::POSITION));
    _model->getTransform()->setChangedFlags(_model->getTransform()->getChangedFlags() | static_cast<uint32_t>(TransformBit::POSITION));
    _model->setDynamicBatching(isBatchingEnabled());
    const size_t meshCount     = _mesh ? _mesh->getRenderingSubMeshes().size() : 0;
    const auto & renderingMesh = _mesh->getRenderingSubMeshes();
    if (!renderingMesh.empty()) {
        for (size_t i = 0; i < meshCount; ++i) {
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

} // namespace cc
