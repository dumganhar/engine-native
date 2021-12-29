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

#include "core/components/RenderableComponent.h"
#include "base/Log.h"
#include "renderer/core/MaterialInstance.h"
#include "scene/Model.h"

namespace cc {

void RenderableComponent::setSharedMaterials(const std::vector<Material *> &val) {
    for (size_t i = 0; i < val.size(); ++i) {
        if (val[i] != _materials[i]) {
            setMaterial(val[i], i);
        }
    }
    if (val.size() < _materials.size()) {
        for (size_t i = val.size(); i < _materials.size(); i++) {
            setMaterial(nullptr, i);
        }
        _materials.resize(val.size());
    }
}

std::vector<MaterialInstance *> &RenderableComponent::getMaterials() {
    for (size_t i = 0; i < _materials.size(); i++) {
        _materialInstances[i] = static_cast<MaterialInstance *>(getMaterialInstance(i));
    }
    return _materialInstances;
}

void RenderableComponent::setMaterials(const std::vector<Material *> &val) {
    const size_t dLen = val.size() - _materials.size();
    if (dLen > 0) {
        _materials.resize(val.size());
        _materialInstances.resize(val.size());
    } else if (dLen < 0) {
        for (size_t i = _materials.size() - dLen; i < _materials.size(); ++i) {
            setMaterialInstance(nullptr, i);
        }
    }

    for (size_t i = 0; i < _materialInstances.size(); i++) {
        // they could be either undefined or null
        // eslint-disable-next-line eqeqeq
        if (_materialInstances[i] != val[i]) {
            setMaterialInstance(val[i], i);
        }
    }
}

void RenderableComponent::setMaterial(Material *material, index_t index) {
    if (material != nullptr && dynamic_cast<MaterialInstance *>(material) != nullptr) { //cjh remove dynamic_cast, use a type flag to decide whether it's an instance.
        CC_LOG_ERROR("Can\'t set a material instance to a sharedMaterial slot");
        //cjh Do we need return directly?
    }

    _materials.resize(index + 1, nullptr);
    _materials[index] = material;

    if (index < _materialInstances.size()) {
        auto *inst = _materialInstances[index];
        if (inst != nullptr) {
            inst->destroy();
            _materialInstances[index] = nullptr;
        }
    }

    onMaterialModified(index, _materials[index]);
}

MaterialInstance *RenderableComponent::getMaterialInstance(index_t idx) {
    Material *mat = _materials[idx];
    if (!mat) {
        return nullptr;
    }

    if (idx >= _materialInstances.size() || !_materialInstances[idx]) {
        IMaterialInstanceInfo matInsInfo;
        matInsInfo.parent              = _materials[idx];
        matInsInfo.owner               = this;
        matInsInfo.subModelIdx         = idx;
        MaterialInstance *instantiated = new MaterialInstance(matInsInfo); //cjh how to delete?
        matInsInfo.parent              = nullptr;
        matInsInfo.owner               = nullptr;
        matInsInfo.subModelIdx         = 0;
        setMaterialInstance(instantiated, idx);
    }
    return _materialInstances[idx];
}

void RenderableComponent::setMaterialInstance(Material *matInst, index_t index) {
    MaterialInstance *curInst = nullptr;
    if (index < _materialInstances.size()) {
        curInst = _materialInstances[index];
    }

    // If the new material is an MaterialInstance
    if (matInst && matInst->getParent()) {
        if (matInst != curInst) {
            _materialInstances.resize(index + 1, nullptr);
            _materialInstances[index] = static_cast<MaterialInstance *>(matInst);
            onMaterialModified(index, matInst);
        }
        return;
    }

    // Or else it's a Material proper
    // Should skip identity check if there is any MaterialInstance
    if (index >= _materials.size() || matInst != _materials[index] || curInst) {
        setMaterial(matInst, index);
    }
}

Material *RenderableComponent::getRenderMaterial(index_t index) {
    if (index < 0) {
        return nullptr;
    }

    if (index < _materialInstances.size()) {
        return _materialInstances[index];
    }

    if (index < _materials.size()) {
        return _materials[index];
    }

    return nullptr;
}

} // namespace cc
