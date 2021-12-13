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

#include <variant>

#include "3d/assets/Mesh.h"
#include "3d/misc/CreateMesh.h"
#include "core/Director.h"
#include "core/builtin/BuiltinResMgr.h"
#include "core/scene-graph/SceneGlobals.h"
#include "primitive/Primitive.h"
#include "renderer/core/MaterialInstance.h"
#include "renderer/core/PassUtils.h"
#include "scene/Model.h"
#include "scene/Skybox.h"

namespace {
cc::Mesh *    skyboxMesh{nullptr};
cc::Material *skyboxMaterial{nullptr};
} // namespace
namespace cc {
namespace scene {

void SkyboxInfo::setEnabled(bool val) {
    _enabled = val;
    if (_resource != nullptr) {
        _resource->setEnabled(_enabled);
    }
}

void SkyboxInfo::setUseIBL(bool val) {
    _useIBL = val;
    if (_resource != nullptr) {
        _resource->setUseIBL(_useIBL);
    }
}

void SkyboxInfo::setRGBE(bool val) {
    _isRGBE = val;
    if (_resource != nullptr) {
        _resource->setIsRGBE(_isRGBE);
    }
}

void SkyboxInfo::setEnvmap(TextureCube *val) {
    _envmap = val;
    if (_resource) {
        _resource->setEnvmap(_envmap);
    }
}

void SkyboxInfo::activate(Skybox *resource) {
    _resource = resource; //cjh shared_ptr?
    if (_resource != nullptr) {
        _resource->initialize(*this);
        _resource->activate(); // update global DS first
    }
}

//
void Skybox::setIsRGBE(bool val) {
    if (val) {
        if (skyboxMaterial != nullptr) {
            skyboxMaterial->recompileShaders({{"USE_RGBE_CUBEMAP", val}}, CC_INVALID_INDEX);
        }
        if (_model != nullptr) {
            _model->setSubModelMaterial(0, skyboxMaterial);
        }
    }
    _isRGBE = val;
    updatePipeline();
}

void Skybox::setEnvmap(TextureCube *val) {
    _envmap = val ? val : _default.get();
    if (_envmap != nullptr) {
        Root::getInstance()->getPipeline()->getPipelineSceneData()->getAmbient()->_albedoArray[3] = static_cast<float>(_envmap->getMipmaps().size());
        updateGlobalBinding();
    }
}

void Skybox::initialize(const SkyboxInfo &skyboxInfo) {
    _enabled = skyboxInfo.isEnabled();
    _useIBL  = skyboxInfo.isUseIBL();
    _isRGBE  = skyboxInfo.isRGBE();
    _envmap  = skyboxInfo.getEnvamp();
}

void Skybox::activate() {
    auto *pipeline   = Root::getInstance()->getPipeline();
    auto *ambient    = pipeline->getPipelineSceneData()->getAmbient();
    _globalDSManager = pipeline->getGlobalDSManager();
    _default         = BuiltinResMgr::getInstance()->get<TextureCube>("default-cube-texture");

    if (_model == nullptr) {
        _model = Root::getInstance()->createModel<scene::Model>();
        _model->initLocalDescriptors(CC_INVALID_INDEX);
    }
    if (_envmap == nullptr) {
        _envmap = _default;
    }
    ambient->_albedoArray[3] = static_cast<float>(_envmap->getMipmaps().size());

    if (skyboxMaterial == nullptr) {
        auto *        mat = new Material();
        MacroRecord   defines{{"USE_RGBE_CUBEMAP", _isRGBE}};
        IMaterialInfo matInfo{
            .effectName = "skybox",
            .defines    = defines};
        mat->initialize({matInfo});
        IMaterialInstanceInfo matInstInfo{
            .parent = mat};
        skyboxMaterial = new MaterialInstance(matInstInfo);
    } else {
        MacroRecord defines{{"USE_RGBE_CUBEMAP", _isRGBE}};
        skyboxMaterial->recompileShaders(defines, CC_INVALID_INDEX);
    }

    if (_enabled) {
        if (skyboxMesh == nullptr) {
            skyboxMesh = createMesh(createGeometry(PrimitiveType::BOX, IBoxOptions({.width = 2, .height = 2, .length = 2})), skyboxMesh);
            _model->initSubModel(0, skyboxMesh->getRenderingSubMeshes()[0], skyboxMaterial);
        }
    }
    updateGlobalBinding();
    updatePipeline();
}

void Skybox::updatePipeline() const {
    int32_t                   value    = _useIBL ? (_isRGBE ? 2 : 1) : 0;
    Root *                    root     = Root::getInstance();
    pipeline::RenderPipeline *pipeline = root->getPipeline();

    if (auto iter = pipeline->getMacros().find("CC_USE_IBL"); iter != pipeline->getMacros().end()) {
        const MacroValue &macro    = iter->second;
        if (macro.type() == typeid(int32_t)) {
            const int32_t *macroPtr = boost::get<int32_t>(&macro);
            if (macroPtr != nullptr && (*macroPtr == value)) {
                return;
            }
        }
    }

    pipeline->setValue("CC_USE_IBL", value);
    root->onGlobalPipelineStateChanged();
}

void Skybox::updateGlobalBinding() {
    auto *texture = _envmap->getGFXTexture();
    auto *sampler = pipeline::SamplerLib::getSampler(_envmap->getSamplerHash());
    _globalDSManager->bindSampler(pipeline::ENVIRONMENT::BINDING, sampler);
    _globalDSManager->bindTexture(pipeline::ENVIRONMENT::BINDING, texture);
    _globalDSManager->update();
}

} // namespace scene
} // namespace cc
