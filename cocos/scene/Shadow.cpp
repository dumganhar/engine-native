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

#include "scene/Shadow.h"
#include <cmath>
#include "scene/Pass.h"

namespace cc {
namespace scene {

const float Shadow::COEFFICIENT_OF_EXPANSION{2.0F * std::sqrt(3.0F)};

void Shadow::initialize(const ShadowInfo &shadowsInfo) {
    _near        = shadowsInfo.near;
    _far         = shadowsInfo.far;
    _orthoSize   = shadowsInfo.orthoSize;
    _size        = shadowsInfo.size;
    _pcf         = shadowsInfo.pcf;
    _normal      = shadowsInfo.normal;
    _distance    = shadowsInfo.distance;
    _shadowColor = shadowsInfo.shadowColor;
    _bias        = shadowsInfo.bias;
    _normalBias  = shadowsInfo.normalBias;
    _maxReceived = shadowsInfo.maxReceived;
    _autoAdapt   = shadowsInfo.autoAdapt;
    setEnabled(shadowsInfo.enabled);
    _type       = shadowsInfo.type;
    _saturation = shadowsInfo.saturation;
}

void Shadow::destroy() {
    if (_material) {
        _material->destroy();
        _material = nullptr;
    }

    if (_instancingMaterial) {
        _instancingMaterial->destroy();
        _instancingMaterial = nullptr;
    }
}

gfx::Shader *Shadow::getPlanarShader(const std::vector<IMacroPatch> &patches) {
    if (!_material) {
        createMaterial();
    }

    return _material->getPasses()[0]->getShaderVariant(patches);
}

gfx::Shader *Shadow::getPlanarInstanceShader(const std::vector<IMacroPatch> &patches) {
    if (!_instancingMaterial) {
        createInstanceMaterial();
    }

    return _instancingMaterial->getPasses()[0]->getShaderVariant(patches);
}

void Shadow::activate() {
    if (_enabled) {
        if (_type == ShadowType::SHADOW_MAP) {
            updatePipeline();
        } else {
            updatePlanarInfo();
        }
    } else {
        auto *root     = Root::getInstance();
        auto *pipeline = root->getPipeline();
        pipeline->setValue("CC_RECEIVE_SHADOW", 0.F);
        root->onGlobalPipelineStateChanged();
    }
}

void Shadow::updatePlanarInfo() {
    if (!_material) {
        createMaterial();
    }
    if (!_instancingMaterial) {
        createInstanceMaterial();
    }

    auto *root     = Root::getInstance();
    auto *pipeline = root->getPipeline();
    pipeline->setValue("CC_RECEIVE_SHADOW", 0.F);
    root->onGlobalPipelineStateChanged();
}

void Shadow::updatePipeline() {
    auto *root     = Root::getInstance();
    auto *pipeline = root->getPipeline();
    pipeline->setValue("CC_RECEIVE_SHADOW", 1.F);
    root->onGlobalPipelineStateChanged();
}

void Shadow::createInstanceMaterial() {
    _instancingMaterial = new Material();

    IMaterialInfo materialInfo;
    materialInfo.effectName = "planar-shadow";
    MacroRecord microRecord{{"USE_INSTANCING", true}};
    materialInfo.defines = microRecord;
    _instancingMaterial->initialize(materialInfo);
}

void Shadow::createMaterial() {
    _material = new Material();

    IMaterialInfo materialInfo;
    materialInfo.effectName = "planar-shadow";
    _material->initialize(materialInfo);
}

} // namespace scene
} // namespace cc
