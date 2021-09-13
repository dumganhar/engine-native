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
#include <array>

#include "core/Director.h"
#include "core/assets/Material.h"
#include "gfx-base/GFXTexture.h"
#include "renderer/pipeline/Define.h"
#include "renderer/pipeline/InstancedBuffer.h"
#include "scene/Model.h"
#include "scene/Pass.h"
#include "scene/RenderScene.h"
#include "scene/SubModel.h"

namespace {
const uint32_t LIGHTMAP_SAMPLER_HASH = cc::pipeline::SamplerLib::genSamplerHash({
    cc::gfx::Filter::LINEAR,
    cc::gfx::Filter::LINEAR,
    cc::gfx::Filter::NONE,
    cc::gfx::Address::CLAMP,
    cc::gfx::Address::CLAMP,
    cc::gfx::Address::CLAMP,
});

const uint32_t LIGHTMAP_SAMPLER_WITH_MIP_HASH = cc::pipeline::SamplerLib::genSamplerHash({
    cc::gfx::Filter::LINEAR,
    cc::gfx::Filter::LINEAR,
    cc::gfx::Filter::LINEAR,
    cc::gfx::Address::CLAMP,
    cc::gfx::Address::CLAMP,
    cc::gfx::Address::CLAMP,
});

const std::vector<cc::scene::IMacroPatch> SHADOW_MAP_PATCHES{{"CC_RECEIVE_SHADOW", true}};
const std::string                         INST_MAT_WORLD = "a_matWorld0";
} // namespace

namespace cc {
namespace scene {

Model::Model() {
    _device = Root::getInstance()->getDevice();
}

void Model::initialize() {
    if (_inited) return;
    _receiveShadow = true;
    _castShadow    = false;
    _enabled       = true;
    _visFlags      = static_cast<uint32_t>(Layers::Enum::NONE);
    _inited        = true;
}

void Model::destroy() {
    for (SubModel *subModel : _subModels) {
        CC_SAFE_DESTROY(subModel);
    }
    CC_SAFE_DESTROY(_localBuffer);
    CC_SAFE_DELETE(_worldBounds);
    CC_SAFE_DELETE(_modelBounds);
    _subModels.clear();
    _inited           = false;
    _transformUpdated = true;
    CC_SAFE_DELETE(_transform); //cjh TODO: should not delete
    CC_SAFE_DELETE(_node);      //cjh TODO: should not delete
    _isDynamicBatching = false;
}

void Model::uploadMat4AsVec4x3(const Mat4 &mat, Float32Array &v1, Float32Array &v2, Float32Array &v3) {
    v1[0] = mat.m[0];
    v1[1] = mat.m[1];
    v1[2] = mat.m[2];
    v1[3] = mat.m[12];
    v2[0] = mat.m[4];
    v2[1] = mat.m[5];
    v2[2] = mat.m[6];
    v2[3] = mat.m[13];
    v3[0] = mat.m[8];
    v3[1] = mat.m[9];
    v3[2] = mat.m[10];
    v3[3] = mat.m[14];
}

void Model::updateTransform(uint32_t /*stamp*/) {
    Node *node = _transform;
    if (node->getFlagsChanged() || node->getDirtyFlag()) {
        node->updateWorldTransform();
        _transformUpdated = true;
        if (_modelBounds->isValid() && _worldBounds) {
            _modelBounds->transform(node->getWorldMatrix(), _worldBounds);
        }
    }
}

void Model::updateWorldBound() {
    Node *node = _transform;
    if (node) {
        node->updateWorldTransform();
        _transformUpdated = true;
        if (_modelBounds->isValid() && _worldBounds) {
            _modelBounds->transform(node->getWorldMatrix(), _worldBounds);
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
    Mat4                                         mat4;
    int                                          idx = _instMatWorldIdx;
    std::array<float, pipeline::UBOLocal::COUNT> bufferView;
    if (idx >= 0) {
        std::vector<TypedArray> &attrs = getInstancedAttributeBlock()->views;
        uploadMat4AsVec4x3(worldMatrix, std::get<Float32Array>(attrs[idx]), std::get<Float32Array>(attrs[idx + 1]), std::get<Float32Array>(attrs[idx + 2]));
    } else if (_localBuffer) {
        memcpy(bufferView.data() + pipeline::UBOLocal::MAT_WORLD_OFFSET, worldMatrix.m, sizeof(Mat4));
        Mat4::inverseTranspose(worldMatrix, &mat4);
        memcpy(bufferView.data() + pipeline::UBOLocal::MAT_WORLD_IT_OFFSET, mat4.m, sizeof(Mat4));
        _localBuffer->update(bufferView.data(), pipeline::UBOLocal::SIZE);
    }
}

void Model::createBoundingShape(const std::optional<Vec3> &minPos, const std::optional<Vec3> &maxPos) {
    if (!minPos.has_value() || !maxPos.has_value()) {
        return;
    }
    _modelBounds = geometry::AABB::fromPoints(minPos.value(), maxPos.value(), new geometry::AABB());
    _worldBounds = geometry::AABB::fromPoints(minPos.value(), maxPos.value(), new geometry::AABB()); // AABB.clone(this._modelBounds) in ts
}

SubModel *Model::createSubModel() const {
    return new SubModel(); //cjh how to delete?
}

void Model::initSubModel(index_t idx, cc::RenderingSubMesh *subMeshData, Material *mat) {
    initialize();
    bool isNewSubModel = false;
    if (_subModels[idx] == nullptr) {
        _subModels[idx] = createSubModel();
        isNewSubModel   = true;
    } else {
        CC_SAFE_DESTROY(_subModels[idx]);
    }
    _subModels[idx]->initialize(subMeshData, mat->getPasses(), getMacroPatches(idx));
    _subModels[idx]->initPlanarShadowShader();
    _subModels[idx]->initPlanarShadowInstanceShader();
    updateAttributesAndBinding(idx);
}

void Model::setSubModelMesh(index_t idx, cc::RenderingSubMesh *subMesh) const {
    if (idx < _subModels.size()) {
        _subModels[idx]->setSubMesh(subMesh);
    }
}

void Model::setSubModelMaterial(index_t idx, Material *mat) {
    if (idx < _subModels.size()) {
        _subModels[idx]->setPasses(mat->getPasses());
        updateAttributesAndBinding(idx);
    }
}

void Model::onGlobalPipelineStateChanged() const {
    for (SubModel *subModel : _subModels) {
        subModel->onPipelineStateChanged();
    }
}

void Model::onMacroPatchesStateChanged() const {
    for (uint32_t i = 0; i < _subModels.size(); ++i) {
        _subModels[i]->onMacroPatchesStateChanged(getMacroPatches(i));
    }
}

void Model::updateLightingmap(Texture2D *texture, const Vec4 &uvParam) {
    // uvParam.toArray(_localData, pipeline::UBOLocal::LIGHTINGMAP_UVPARAM); // toArray not implemented in Math
    _lightmap        = texture;
    _lightmapUVParam = uvParam;

    if (texture == nullptr) {
        texture = BuiltinResMgr::getInstance()->get<Texture2D>(std::string("empty-texture"));
    }
    gfx::Texture *gfxTexture = texture->getGFXTexture();
    if (gfxTexture) {
        auto *sampler = pipeline::SamplerLib::getSampler(texture->getMipmaps().size() > 1 ? LIGHTMAP_SAMPLER_WITH_MIP_HASH : LIGHTMAP_SAMPLER_HASH);
        for (SubModel *subModel : _subModels) {
            gfx::DescriptorSet *descriptorSet = subModel->getDescriptorSet();
            // // TODO(Yun Hsiao Wu): should manage lightmap macro switches automatically
            // // USE_LIGHTMAP -> CC_USE_LIGHTMAP
            descriptorSet->bindTexture(pipeline::LIGHTMAPTEXTURE::BINDING, gfxTexture);
            descriptorSet->bindSampler(pipeline::LIGHTMAPTEXTURE::BINDING, sampler);
            descriptorSet->update();
        }
    }
}

std::vector<IMacroPatch> Model::getMacroPatches(index_t /*subModelIndex*/) const {
    return _receiveShadow ? SHADOW_MAP_PATCHES : std::vector<IMacroPatch>();
}

void Model::updateAttributesAndBinding(index_t subModelIndex) {
    if (subModelIndex >= _subModels.size()) return;
    SubModel *subModel = _subModels[subModelIndex];
    initLocalDescriptors(subModelIndex);
    updateLocalDescriptors(subModelIndex, subModel->getDescriptorSet());
    gfx::Shader *shader = subModel->getPasses()[0]->getShaderVariant(subModel->getPatches());
    updateInstancedAttributes(shader->getAttributes(), subModel->getPasses()[0]);
}

index_t Model::getInstancedAttributeIndex(const std::string &name) const {
    auto attributes = _instanceAttributeBlock.attributes;
    for (index_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i].name == name) {
            return i;
        }
    }
    return CC_INVALID_INDEX;
}

void Model::updateInstancedAttributes(const std::vector<gfx::Attribute> &attributes, Pass *pass) {
    if (!pass->getDevice()->hasFeature(gfx::Feature::INSTANCED_ARRAYS)) return;
    // free old data

    uint32_t size = 0;
    for (const gfx::Attribute &attribute : attributes) {
        if (!attribute.isInstanced) continue;
        size += gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attribute.format)].size;
    }
    auto attrs = _instanceAttributeBlock;
    attrs.buffer.clear();
    attrs.buffer.resize(size);
    attrs.views.clear();
    attrs.attributes.clear();
    uint32_t offset = 0;

    for (const gfx::Attribute &attribute : attributes) {
        if (!attribute.isInstanced) continue;
        gfx::Attribute attr = gfx::Attribute();
        attr.format         = attribute.format;
        attr.name           = attribute.name;
        attr.isNormalized   = attribute.isNormalized;
        attr.location       = attribute.location;
        attrs.attributes.emplace_back(attr);
        const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attribute.format)];
        // const typeViewArray = new (getTypedArrayConstructor(info))(attrs.buffer.buffer, offset, info.count); // TODO(xwx): need refactor TypedArray related function
        attrs.views.emplace_back(/*typeViewArray*/);
        offset += info.size;
    }
    if (pass->getBatchingScheme() == BatchingSchemes::INSTANCING) {
        pipeline::InstancedBuffer *instanceBuffer = pipeline::InstancedBuffer::get(pass);
        CC_SAFE_DESTROY(instanceBuffer); // instancing IA changed
        setInstMatWorldIdx(getInstancedAttributeIndex(INST_MAT_WORLD));
        _transformUpdated = true;
    }
}

void Model::initLocalDescriptors(index_t /*subModelIndex*/) {
    if (!_localBuffer) {
        _localBuffer = _device->createBuffer({
            gfx::BufferUsageBit::UNIFORM | gfx::BufferUsageBit::TRANSFER_DST,
            gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
            pipeline::UBOLocal::SIZE,
            pipeline::UBOLocal::SIZE,
        });
    }
}

void Model::updateLocalDescriptors(index_t /*subModelIndex*/, gfx::DescriptorSet *descriptorSet) {
    if (_localBuffer) {
        descriptorSet->bindBuffer(pipeline::UBOLocal::BINDING, _localBuffer);
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
