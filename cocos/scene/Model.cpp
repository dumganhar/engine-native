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
#include "scene/Model.h"
#include <array>
#include "../renderer/pipeline/InstancedBuffer.h"
#include "core/Director.h"
#include "core/assets/Material.h"
#include "renderer/pipeline/Define.h"
#include "scene/Pass.h"
#include "scene/RenderScene.h"
#include "scene/SubModel.h"

namespace cc {
namespace scene {
Model::Model() {
    _device = Director::getInstance().getRoot()->getDevice();
}

void Model::initialize() {
    if (_inited) return;
    _receiveShadow = true;
    _castShadow    = false;
    _enabled       = true;
    _visFlags      = static_cast<uint32_t>(scenegraph::LayerList::NONE);
    _inited        = true;
}

void Model::destroy() {
    for (SubModel *subModel : _subModels) {
        // subModel->destroy(); // destroy() not implemented
    }
    if (_localBuffer) {
        _localBuffer->destroy();
        _localBuffer = nullptr;
    }
    _worldBounds = nullptr;
    // _modelBounds = null; // not sure how to destroy
    _subModels.clear();
    _inited           = false;
    _transformUpdated = true;
    _transform        = nullptr;
    _node             = nullptr;
    isDynamicBatching = false;
}

void Model::uploadMat4AsVec4x3(const Mat4 &mat, float *v1, float *v2, float *v3) {
    uint size = sizeof(float) * 4;
    memcpy(v1, mat.m, size);
    memcpy(v2, mat.m + 4, size);
    memcpy(v3, mat.m + 8, size);
    v1[3] = mat.m[12];
    v2[3] = mat.m[13];
    v3[3] = mat.m[14];
}

void Model::updateTransform(uint32_t /*stamp*/) {
    scenegraph::Node *node = _transform;
    if (node->getFlagsChanged() || node->getDirtyFlag()) {
        node->updateWorldTransform();
        _transformUpdated = true;
        if (_modelBounds.getValid() && _worldBounds) {
            _modelBounds.transform(node->getWorldMatrix(), _worldBounds);
        }
    }
}

void Model::updateWorldBound() {
    scenegraph::Node *node = _transform;
    if (node) {
        node->updateWorldTransform();
        _transformUpdated = true;
        if (_modelBounds.getValid() && _worldBounds) {
            _modelBounds.transform(node->getWorldMatrix(), _worldBounds);
        }
    }
}

void Model::updateUBOs(uint32_t stamp) {
    for (SubModel *subModel : _subModels) {
        subModel->update();
    }
    _updateStamp = stamp;
    if (!_transformUpdated) {
        return;
    }
    _transformUpdated = false;
    getTransform()->updateWorldTransform();
    const auto &                                 worldMatrix = getTransform()->getWorldMatrix();
    int                                          idx         = _instMatWorldIdx;
    Mat4                                         mat4;
    std::array<float, pipeline::UBOLocal::COUNT> bufferView;
    if (idx >= 0) {
        const std::vector<uint8_t *> &attrs = getInstancedAttributeBlock()->views;
        uploadMat4AsVec4x3(worldMatrix,
                           reinterpret_cast<float *>(attrs[idx]),
                           reinterpret_cast<float *>(attrs[idx + 1]),
                           reinterpret_cast<float *>(attrs[idx + 2]));
    } else if (_localBuffer) {
        memcpy(bufferView.data() + pipeline::UBOLocal::MAT_WORLD_OFFSET, worldMatrix.m, sizeof(Mat4));
        Mat4::inverseTranspose(worldMatrix, &mat4);
        memcpy(bufferView.data() + pipeline::UBOLocal::MAT_WORLD_IT_OFFSET, mat4.m, sizeof(Mat4));
        _localBuffer->update(bufferView.data(), pipeline::UBOLocal::SIZE);
    }
}

void Model::createBoundingShape(const Vec3 &minPos, const Vec3 &maxPos) {
    // _modelBounds = geometry::AABB::fromPoints(minPos, maxPos, new geometry::AABB()); // not sure use new
    // _worldBounds = geometry::AABB(_modelBounds); need override operator= in AABB
}

SubModel Model::createSubModel() const {
    return SubModel();
}

void Model::initSubModel(index_t idx, const cc::RenderingSubMesh &subMeshData, Material mat) {
    initialize();
    bool isNewSubModel = false;
    if (_subModels[idx] == nullptr) {
        // _subModels[idx] = createSubModel(); // need override operator= in submodel
        isNewSubModel = true;
    } else {
        // _subModels[idx]->destroy(); // destroy() not implemented
    }
    // _subModels[idx]->initialize(subMeshData, mat.getPasses(), getMacroPatches(idx)); //initialize() not implemented
    // _subModels[idx]->initPlanarShadowShader();
    // _subModels[idx]->initPlanarShadowInstanceShader();
    updateAttributesAndBinding(idx);
}

void Model::setSubModelMesh(index_t idx, const cc::RenderingSubMesh &subMesh) const {
    if (idx < _subModels.size()) {
        // _subModels[idx]->setSubMesh(subMesh); // setSubMesh not implemented
    }
}

void Model::setSubModelMaterial(int idx, Material &mat) {
    if (idx < _subModels.size()) {
        _subModels[idx]->setPasses(mat.getPasses());
        updateAttributesAndBinding(idx);
    }
}

void Model::onGlobalPipelineStateChanged() const {
    for (SubModel *subModel : _subModels) {
        // subModel->onPiplineStateChanged(); // onPiplineStateChanged not implement
    }
}

void Model::onMacroPatchesStateChanged() const {
    for (SubModel *subModel : _subModels) {
        // subModel->onMacroPatchesStateChanged(); // onMacroPatchesStateChanged not implement
    }
}

void Model::updateLightingmap(Texture2D *texture, const Vec4 &uvParam) {
    // uvParam.toArray(_localData, pipeline::UBOLocal::LIGHTINGMAP_UVPARAM); // toArray not implemented in Math
    _lightmap        = texture;
    _lightmapUVParam = uvParam;

    if (texture == nullptr) {
        // texture = builtinResMgr.get<Texture2D>('empty-texture');
    }
    if (texture->getGFXTexture()) {
        // const sampler = samplerLib.getSampler(this._device, texture.mipmaps.length > 1 ? lightmapSamplerWithMipHash : lightmapSamplerHash);
        for (SubModel *subModel : _subModels) {
            // const { descriptorSet } = subModels[i];
            // // TODO: should manage lightmap macro switches automatically
            // // USE_LIGHTMAP -> CC_USE_LIGHTMAP
            // descriptorSet.bindTexture(UNIFORM_LIGHTMAP_TEXTURE_BINDING, gfxTexture);
            // descriptorSet.bindSampler(UNIFORM_LIGHTMAP_TEXTURE_BINDING, sampler);
            // descriptorSet.update();
        }
    }
}

std::vector<IMacroPatch> Model::getMacroPatches(index_t /*subModelIndex*/) const {
    if (_receiveShadow) {
        IMacroPatch patch = IMacroPatch();
        patch.name        = "CC_RECEIVE_SHADOW";
        patch.value       = true;
        std::vector<IMacroPatch> shadowMapPatches{patch};
        return shadowMapPatches;
    }
    return std::vector<IMacroPatch>();
}

void Model::updateAttributesAndBinding(index_t subModelIndex) {
    if (subModelIndex >= _subModels.size()) return;
    SubModel *subModel = _subModels[subModelIndex];
    initLocalDescriptors(subModelIndex);
    updateLocalDescriptors(subModelIndex, *subModel->getDescriptorSet());
    // gfx::Shader shader = subModel->getPasses()[0]->getShaderVariant(subModel->getPatches()); // getPatches not implemented
    // updateInstanceAttribute(shader.attributes, subModel->getPasses()[0])
}

int32_t Model::getInstancedAttributeIndex(const std::string &name) const {
    auto attributes = _instanceAttributeBlock.attributes;
    for (int32_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i].name == name) {
            return i;
        }
    }
    return CC_INVALID_INDEX;
}

void Model::updateInstancedAttributes(const std::vector<gfx::Attribute> &attributes, Pass *pass) {
    if (!pass->getDevice()->hasFeature(gfx::Feature::INSTANCED_ARRAYS)) return;
    // free old data

    int32_t size = 0;
    for (const gfx::Attribute &attribute : attributes) {
        if (!attribute.isInstanced) continue;
        // size += FormatInfos[attribute.format].size(); FormatInfos not define
    }
    auto attrs = _instanceAttributeBlock;
    attrs.buffer.clear();
    attrs.buffer.resize(size);
    attrs.views.clear();
    attrs.attributes.clear();
    int32_t offset = 0;

    for (const gfx::Attribute &attribute : attributes) {
        if (!attribute.isInstanced) continue;
        gfx::Attribute attr = gfx::Attribute();
        attr.format         = attribute.format;
        attr.name           = attribute.name;
        attr.isNormalized   = attribute.isNormalized;
        attr.location       = attribute.location;
        attrs.attributes.emplace_back(attr);

        // auto info = FormatInfos[attribute.format];
        // const typeViewArray = new (getTypedArrayConstructor(info))(attrs.buffer.buffer, offset, info.count);
        attrs.views.emplace_back(/*typeViewArray*/);
        // offset += info.size();
    }
    if (pass->getBatchingScheme() == BatchingSchemes::INSTANCING) {
        pipeline::InstancedBuffer::get(pass)->destroy(); // instancing IA changed
        // setInstMatWorldIdx(getInstancedAttributeIndex(INST_MAT_WORLD)); // INST_MAT_WORLD not define
        _transformUpdated = true;
    }
}

void Model::initLocalDescriptors(index_t /*subModelIndex*/) {
    if (!_localBuffer) {
        gfx::BufferInfo bufferInfo = gfx::BufferInfo();
        bufferInfo.usage           = gfx::BufferUsageBit::UNIFORM | gfx::BufferUsageBit::TRANSFER_DST; // not sure ts operator| is same in cpp
        bufferInfo.memUsage        = gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE;
        bufferInfo.size            = pipeline::UBOLocal::SIZE;
        bufferInfo.stride          = pipeline::UBOLocal::SIZE;
        _localBuffer               = _device->createBuffer(bufferInfo);
    }
}

void Model::updateLocalDescriptors(index_t /*subModelIndex*/, gfx::DescriptorSet &descriptorSet) const {
    if (_localBuffer) {
        descriptorSet.bindBuffer(pipeline::UBOLocal::BINDING, _localBuffer);
    }
}

void Model::setSubModel(uint32_t idx, SubModel *subModel) {
    if (idx >= static_cast<uint32_t>(_subModels.size())) {
        _subModels.emplace_back(subModel);
        return;
    }
    _subModels[idx] = subModel;
}

} // namespace scene
} // namespace cc
