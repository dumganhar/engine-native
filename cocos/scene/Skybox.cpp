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
#include "core/scene-graph/SceneGlobal.h"
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
void Skybox::initialize(const scenegraph::SkyboxInfo &skyboxInfo) {
    _enabled = skyboxInfo.getEnabled();
    _useIBL  = skyboxInfo.getIBL();
    _isRGBE  = skyboxInfo.getRGBE();
    _envmap  = skyboxInfo.getEnvamp();
}

void Skybox::activate() {
    auto *pipeline   = Director::getInstance().getRoot()->getPipeline();
    auto *ambient    = pipeline->getPipelineSceneData()->getAmbient();
    _globalDSManager = pipeline->getGlobalDSManager();
    _default         = BuiltinResMgr::getInstance()->get<TextureCube>(std::string("default-cube-texture"));

    if (_model == nullptr) {
        // _model = Director::getInstance().getRoot()->createModel(); // TODO(xwx): need to figure out usage
        // this._model._initLocalDescriptors = () => {}; // TODO(xwx): need to figure out usage
    }
    if (_envmap == nullptr) {
        _envmap = _default;
    }
    // ambient.albedoArray[3] = this._envmap.mipmapLevel;
    // ambient->getAlbedoArray()[3] = _envmap->getMipmaps().size(); // const array cannot be assignment

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
            // skybox_mesh = legacyCC.utils.createMesh(legacyCC.primitives.box({ width: 2, height: 2, length: 2 })) as Mesh;
            // skyboxMesh = createMesh(primitives) // TODO(xwx): need to figure out usage above
            _model->initSubModel(0, skyboxMesh->getRenderingSubMeshes()[0], skyboxMaterial);
        }
    }
    updateGlobalBinding();
    updatePipeline();
}

void Skybox::updatePipeline() const {
    uint32_t                  value    = _useIBL ? (_isRGBE ? 2 : 1) : 0;
    Root *                    root     = Director::getInstance().getRoot();
    pipeline::RenderPipeline *pipeline = root->getPipeline();

    const std::variant<float, bool, std::string> &macro    = pipeline->getMacros().at("CC_USE_IBL");
    const float *                                 macroPtr = std::get_if<float>(&macro);
    if (macroPtr && static_cast<int>(*macroPtr) == static_cast<int>(value)) {
        return;
    }

    pipeline->setValue("CC_USE_IBL", static_cast<float>(value));
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