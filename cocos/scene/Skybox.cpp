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

#include "scene/Skybox.h"
#include "3d/assets/Mesh.h"
#include "3d/misc/CreateMesh.h"
#include "core/Director.h"
#include "core/builtin/BuiltinResMgr.h"
#include "core/scene-graph/SceneGlobals.h"
#include "primitive/Primitive.h"
#include "renderer/core/MaterialInstance.h"
#include "renderer/core/PassUtils.h"
#include "scene/Model.h"

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

void SkyboxInfo::setApplyDiffuseMap(bool val) {
    _applyDiffuseMap = val;
    if (_resource != nullptr) {
        _resource->setUseDiffuseMap(val);
    }
}

void SkyboxInfo::setEnvmap(TextureCube *val) {
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        _envmapHDR = val;
    } else {
        _envmapLDR = val;
    }

    if (_envmapHDR == nullptr) {
        _diffuseMapHDR   = nullptr;
        _applyDiffuseMap = false;
        setUseIBL(false);
    }

    if (_resource) {
        _resource->setEnvMaps(_envmapHDR, _envmapLDR);
        _resource->setDiffuseMaps(_diffuseMapHDR, _diffuseMapLDR);
        _resource->setUseDiffuseMap(_applyDiffuseMap);
        _resource->setEnvmap(val);
    }
}

void SkyboxInfo::setDiffuseMap(TextureCube *val) {
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        _diffuseMapHDR = val;
    } else {
        _diffuseMapHDR = val;
    }

    if (_resource) {
        _resource->setDiffuseMaps(_diffuseMapHDR, _diffuseMapLDR);
    }
}

void SkyboxInfo::activate(Skybox *resource) {
    _resource = resource; //cjh shared_ptr?
    if (_resource != nullptr) {
        _resource->initialize(*this);
        _resource->setEnvMaps(_envmapHDR, _envmapLDR);
        _resource->setDiffuseMaps(_diffuseMapHDR, _diffuseMapLDR);
        _resource->activate(); // update global DS first
    }
}

void Skybox::setEnvmap(TextureCube *val) {
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        setEnvMaps(val, _envmapLDR);
    } else {
        setEnvMaps(_envmapHDR, val);
    }
}

void Skybox::initialize(const SkyboxInfo &skyboxInfo) {
    _enabled       = skyboxInfo.isEnabled();
    _useIBL        = skyboxInfo.isUseIBL();
    _useDiffuseMap = skyboxInfo.isApplyDiffuseMap();
    _useHDR        = skyboxInfo.isUseHDR();
}

void Skybox::setEnvMaps(TextureCube *envmapHDR, TextureCube *envmapLDR) {
    _envmapHDR       = envmapHDR;
    _envmapLDR       = envmapLDR;
    const bool isHDR = true;
    // TODO(xwx): use below after implement
    // legacyCC.director.root as Root).pipeline.pipelineSceneData.isHDR
    if (isHDR) {
        if (envmapHDR) {
            Root::getInstance()->getPipeline()->getPipelineSceneData()->getAmbient()->getGroundAlbedo().w = static_cast<float>(envmapHDR->mipmapLevel());
        }
    } else if (envmapLDR) {
        Root::getInstance()->getPipeline()->getPipelineSceneData()->getAmbient()->getGroundAlbedo().w = static_cast<float>(envmapLDR->mipmapLevel());
    }

    updateGlobalBinding();
    updatePipeline();
}

void Skybox::setDiffuseMaps(TextureCube *diffuseMapHDR, TextureCube *diffuseMapLDR) {
    _diffuseMapHDR = diffuseMapHDR;
    _diffuseMapLDR = diffuseMapLDR;
    updateGlobalBinding();
    updatePipeline();
}

void Skybox::activate() {
    auto *pipeline   = Root::getInstance()->getPipeline();
    _globalDSManager = pipeline->getGlobalDSManager();
    _default         = BuiltinResMgr::getInstance()->get<TextureCube>("default-cube-texture");

    if (_model == nullptr) {
        _model = Root::getInstance()->createModel<scene::Model>();
        _model->initLocalDescriptors(CC_INVALID_INDEX);
        // _model->initWorldBoundDescriptors(CC_INVALID_INDEX); // TODO(xwx): initWorldBoundDescriptors not implement yet
    }
    auto *envmap = getEnvmap();
    bool  isRGBE = envmap != nullptr ? envmap->isRGBE : _default->isRGBE;

    if (skyboxMaterial == nullptr) {
        auto *        mat = new Material();
        MacroRecord   defines{{"USE_RGBE_CUBEMAP", isRGBE}};
        IMaterialInfo matInfo{
            .effectName = "skybox",
            .defines    = defines};
        mat->initialize({matInfo});
        IMaterialInstanceInfo matInstInfo{
            .parent = mat};
        skyboxMaterial = new MaterialInstance(matInstInfo);
    }

    if (_enabled) {
        if (skyboxMesh == nullptr) {
            skyboxMesh = createMesh(createGeometry(PrimitiveType::BOX, IBoxOptions({.width = 2, .height = 2, .length = 2})), skyboxMesh);
            _model->initSubModel(0, skyboxMesh->getRenderingSubMeshes()[0], skyboxMaterial);
        }
    }

    if (getEnvmap() == nullptr) {
        setEnvmap(_default.get());
    }

    if (getDiffuseMap() == nullptr) {
        setDiffuseMap(_default.get());
    }

    updateGlobalBinding();
    updatePipeline();
}

void Skybox::updatePipeline() const {
    if (isEnabled() && skyboxMaterial != nullptr) {
        skyboxMaterial->recompileShaders({{"USE_RGBE_CUBEMAP", isRGBE()}});
    }

    if (_model != nullptr && skyboxMaterial != nullptr) {
        _model->setSubModelMaterial(0, skyboxMaterial);
    }

    Root *                    root     = Root::getInstance();
    pipeline::RenderPipeline *pipeline = root->getPipeline();

    const bool    useRGBE            = isRGBE();
    const int32_t useIBLValue        = isUseIBL() ? (useRGBE ? 2 : 1) : 0;
    const int32_t useDiffuseMapValue = (isUseIBL() && isUseDiffuseMap() && getDiffuseMap() != nullptr) ? (useRGBE ? 2 : 1) : 0;
    const bool    useHDRValue        = isUseHDR();

    if (auto iter = pipeline->getMacros().find("CC_USE_IBL"); iter != pipeline->getMacros().end()) {
        const MacroValue &macroIBL    = iter->second;
        const int32_t *   macroIBLPtr = cc::get_if<int32_t>(&macroIBL);
        if (macroIBLPtr != nullptr && (*macroIBLPtr == useIBLValue)) {
            auto iter = pipeline->getMacros().find("CC_USE_DIFFUSEMAP");
            if (iter != pipeline->getMacros().end()) {
                const MacroValue &macroDIFFUSEMAP    = iter->second;
                const int32_t *   macroDIFFUSEMAPPtr = cc::get_if<int32_t>(&macroDIFFUSEMAP);
                if (macroDIFFUSEMAPPtr != nullptr && (*macroDIFFUSEMAPPtr == useDiffuseMapValue)) {
                    if (auto iter = pipeline->getMacros().find("CC_USE_HDR"); iter != pipeline->getMacros().end()) {
                        const MacroValue &macroHDR    = iter->second;
                        const int32_t *   macroHDRPtr = cc::get_if<int32_t>(&macroHDR);
                        if (macroHDRPtr != nullptr && (*macroHDRPtr == useHDRValue)) {
                            return;
                        }
                    }
                }
            }
        }
    }
    pipeline->setValue("CC_USE_IBL", useIBLValue);
    pipeline->setValue("CC_USE_DIFFUSEMAP", useDiffuseMapValue);
    pipeline->setValue("CC_USE_HDR", useHDRValue);

    root->onGlobalPipelineStateChanged();
}

void Skybox::updateGlobalBinding() {
    if (_globalDSManager != nullptr) {
        const auto *device = Root::getInstance()->getDevice();
        auto *      envmap = getEnvmap();
        if (envmap == nullptr) {
            envmap = _default.get();
        }
        if (envmap != nullptr) {
            auto *texture = envmap->getGFXTexture();
            auto *sampler = pipeline::SamplerLib::getSampler(envmap->getSamplerHash());
            _globalDSManager->bindSampler(pipeline::ENVIRONMENT::BINDING, sampler);
            _globalDSManager->bindTexture(pipeline::ENVIRONMENT::BINDING, texture);
        }

        auto *diffuseMap = getDiffuseMap();
        if (diffuseMap == nullptr) {
            diffuseMap = _default.get();
        }
        if (diffuseMap != nullptr) {
            auto *texture = diffuseMap->getGFXTexture();
            auto *sampler = pipeline::SamplerLib::getSampler(envmap->getSamplerHash());
            // TODO(xwx): pipeline::DIFFUSEMAP::BINDING not implemented yet;
            // _globalDSManager->bindSampler(pipeline::DIFFUSEMAP::BINDING, sampler);
            // _globalDSManager->bindTexture(pipeline::DIFFUSEMAP::BINDING, texture);
        }
        _globalDSManager->update();
    }
}

} // namespace scene
} // namespace cc
