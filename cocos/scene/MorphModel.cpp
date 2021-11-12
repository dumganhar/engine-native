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

#include "scene/MorphModel.h"
namespace cc {
namespace scene {
std::vector<IMacroPatch> MorphModel::getMacroPatches(index_t subModelIndex) {
    if (_morphRenderingInstance != nullptr) {
        return _morphRenderingInstance->requiredPatches(subModelIndex);
    }
    return std::vector<IMacroPatch>();
}

void MorphModel::initSubModel(index_t idx, RenderingSubMesh *subMeshData, Material *mat) {
    Super::initSubModel(idx, subMeshData, launderMaterial(mat));
}

void MorphModel::destroy() {
    Super::destroy();
    CC_SAFE_DELETE(_morphRenderingInstance);
}

void MorphModel::setSubModelMaterial(index_t idx, Material *mat) {
    Super::setSubModelMaterial(idx, mat);
}

void MorphModel::updateLocalDescriptors(index_t subModelIndex, gfx::DescriptorSet *descriptorSet) {
    Super::updateLocalDescriptors(subModelIndex, descriptorSet);
    if (_morphRenderingInstance != nullptr) {
        _morphRenderingInstance->adaptPipelineState(subModelIndex, descriptorSet);
    }
}

Material *MorphModel::launderMaterial(Material *material) const {
    return material;
    // // Commented in ts
    // if (this._usedMaterials.has(material)) {
    //     return new MaterialInstance({
    //         parent: material,
    //     });
    // } else {
    //     this._usedMaterials.add(material);
    //     return material;
    // }
}

} // namespace scene
} // namespace cc
