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
#include "core/scene-graph/Node.h"
#include "scene/Pass.h"
#include "core/Root.h"

namespace cc {
namespace scene {

// ShadowInfo

void ShadowsInfo::setEnabled(bool val) {
    if (_enabled == val) {
        return;
    }

    _enabled = val;
    if (_resource != nullptr) {
        _resource->setEnabled(val);
        if (val) {
            _resource->setType(_type);
        }
    }
}

void ShadowsInfo::setType(ShadowType val) {
    _type = val;
    if (_resource != nullptr) {
        _resource->setType(val);
    }
}

void ShadowsInfo::setShadowColor(const Color &val) {
    _shadowColor.set(val);
    if (_resource != nullptr) {
        _resource->setShadowColor(val);
    }
}

void ShadowsInfo::setNormal(const Vec3 &val) {
    _normal = val;
    if (_resource != nullptr) {
        _resource->setNormal(val);
    }
}

void ShadowsInfo::setDistance(float val) {
    _distance = val;
    if (_resource != nullptr) {
        _resource->setDistance(val);
    }
}

void ShadowsInfo::setSaturation(float val) {
    if (val > 1.0) {
        _saturation = val / val;
        if (_resource != nullptr) {
            _resource->setSaturation(val / val);
        }
    } else {
        _saturation = val;
        if (_resource != nullptr) {
            _resource->setSaturation(val);
        }
    }
}

void ShadowsInfo::setPcf(PCFType val) {
    _pcf = val;
    if (_resource != nullptr) {
        _resource->setPcf(val);
    }
}

void ShadowsInfo::setMaxReceived(uint32_t val) {
    _maxReceived = val;
    if (_resource != nullptr) {
        _resource->setMaxReceived(val);
    }
}

void ShadowsInfo::setBias(float val) {
    _bias = val;
    if (_resource != nullptr) {
        _resource->setBias(val);
    }
}

void ShadowsInfo::setNormalBias(float val) {
    _normalBias = val;
    if (_resource != nullptr) {
        _resource->setNormalBias(val);
    }
}

void ShadowsInfo::setShadowMapSize(float value) {
    _size.set(value, value);
    if (_resource != nullptr) {
        _resource->setShadowMapSize(value);
        _resource->setShadowMapDirty(true);
    }
}

void ShadowsInfo::setAutoAdapt(bool val) {
    _autoAdapt = val;
    if (_resource != nullptr) {
        _resource->setAutoAdapt(val);
    }
}

void ShadowsInfo::setNear(float val) {
    _near = val;
    if (_resource != nullptr) {
        _resource->setNear(val);
    }
}

void ShadowsInfo::setFar(float val) {
    _far = val;
    if (_resource != nullptr) {
        _resource->setFar(val);
    }
}

void ShadowsInfo::setOrthoSize(float val) {
    _orthoSize = val;
    if (_resource != nullptr) {
        _resource->setOrthoSize(val);
    }
}

void ShadowsInfo::setPlaneFromNode(Node *node) {
    const auto &qt = node->getWorldRotation();
    _normal        = Vec3::UNIT_Y;
    _normal.transformQuat(qt);
    _distance = _normal.dot(node->getWorldPosition());
}

void ShadowsInfo::activate(Shadow *resource) {
    _resource = resource; //cjh shared_ptr
    _resource->initialize(*this);
    _resource->activate();
}

//
const float Shadow::COEFFICIENT_OF_EXPANSION{2.0F * std::sqrt(3.0F)};

void Shadow::initialize(const ShadowsInfo &shadowsInfo) {
    _near      = shadowsInfo.getNear();
    _far       = shadowsInfo.getFar();
    _orthoSize = shadowsInfo.getOrthoSize();
    _size      = shadowsInfo.getSize();
    _pcf       = shadowsInfo.getPcf();
    _normal    = shadowsInfo.getNormal();
    _distance  = shadowsInfo.getDistance();
    setShadowColor(shadowsInfo.getShadowColor());
    _bias        = shadowsInfo.getBias();
    _normalBias  = shadowsInfo.getNormalBias();
    _maxReceived = shadowsInfo.getMaxReceived();
    _autoAdapt   = shadowsInfo.isAutoAdapt();
    setEnabled(shadowsInfo.isEnabled());
    _type       = shadowsInfo.getType();
    _saturation = shadowsInfo.getSaturation();
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
