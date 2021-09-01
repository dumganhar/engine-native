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
#include "scene/BakedSkinningModel.h"
#include "pipeline/Define.h"

namespace {
const uint32_t JOINT_TEXTURE_SAMPLER_HASH = cc::pipeline::SamplerLib::genSamplerHash({
    cc::gfx::Filter::POINT,
    cc::gfx::Filter::POINT,
    cc::gfx::Filter::NONE,
    cc::gfx::Address::CLAMP,
    cc::gfx::Address::CLAMP,
    cc::gfx::Address::CLAMP,
});

std::vector<cc::scene::IMacroPatch> myPatches{
    {"CC_USE_SKINNING", true},
    {"CC_USE_BAKED_ANIMATION", true}};

const std::string INST_JOINT_ANIM_INFO = "a_jointAnimInfo";
} // namespace
namespace cc {
namespace scene {
void BakedSkinningModel::destroy() {
    // CC_SAFE_DELETE(uploadedAnim);
    for (geometry::AABB *boundInfo : _jointMedium.boundsInfo) {
        CC_SAFE_DELETE(boundInfo);
    }
    _jointMedium.boundsInfo.clear();
    if (_jointMedium.buffer != nullptr) {
        CC_SAFE_DESTROY(_jointMedium.buffer);
    }
    // applyJointTexture(nullptr);
    Super::destroy();
}

void BakedSkinningModel::bindSkeleton(Skeleton *skeleton, scenegraph::Node *skinningRoot, Mesh *mesh) {
    _skeleton = skeleton;
    _mesh     = mesh;
    if (skeleton == nullptr || skinningRoot == nullptr || mesh == nullptr) return;
    setTransform(skinningRoot);
    // _jointMedium.animInfo = _dataPoolManager.getData(skinningRoot->getUUid()); // _dataPoolManager not define
    if (_jointMedium.buffer == nullptr) {
        _jointMedium.buffer = _device->createBuffer({
            gfx::BufferUsageBit::UNIFORM | gfx::BufferUsageBit::TRANSFER_DST,
            gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
            pipeline::UBOSkinning::SIZE,
            pipeline::UBOSkinning::SIZE,
        });
    }
}

void BakedSkinningModel::updateTransform(uint32_t stamp) {
    Model::updateTransform(stamp);
    if (!_isUploadAnim) {
        return;
    }
    BakedAnimInfo & animInfo  = _jointMedium.animInfo;
    geometry::AABB *skelBound = !_jointMedium.boundsInfo.empty() ? _jointMedium.boundsInfo[*animInfo.data] : nullptr;
    if (_worldBounds && skelBound) {
        scenegraph::Node *node = getTransform();
        skelBound->transform(node->getWorldMatrix(), _worldBounds);
    }
}

void BakedSkinningModel::updateUBOs(uint32_t stamp) {
    Model::updateUBOs(stamp);
    BakedAnimInfo &info = _jointMedium.animInfo;
    int            idx  = _instAnimInfoIdx;
    if (idx >= 0) {
        std::vector<uint8_t *> &views        = getInstancedAttributeBlock()->views;
        *reinterpret_cast<float *>(views[0]) = *reinterpret_cast<float *>(info.data);
    } else if (info.getDirty()) {
        info.buffer->update(info.data, info.buffer->getSize());
        *info.dirty = 0;
    }
}

std::vector<IMacroPatch> BakedSkinningModel::getMacroPatches(index_t subModelIndex) const {
    auto patches = Super::getMacroPatches(subModelIndex);
    if (!patches.empty()) {
        patches.reserve(patches.size() + myPatches.size());
        patches.insert(std::end(patches), std::begin(myPatches), std::end(myPatches));
    }
    return patches;
}

void BakedSkinningModel::updateLocalDescriptors(index_t subModelIndex, gfx::DescriptorSet *descriptorSet) {
    Super::updateLocalDescriptors(subModelIndex, descriptorSet);
    gfx::Buffer * buffer   = _jointMedium.buffer;
    auto *        texture  = _jointMedium.jointTextureInfo;
    BakedAnimInfo animInfo = _jointMedium.animInfo;
    descriptorSet->bindBuffer(pipeline::UBOSkinningTexture::BINDING, buffer);
    descriptorSet->bindBuffer(pipeline::UBOSkinningAnimation::BINDING, animInfo.buffer);
    if (texture != nullptr) {
        auto *sampler = pipeline::SamplerLib::getSampler(JOINT_TEXTURE_SAMPLER_HASH);
        // descriptorSet->bindTexture(UNIFORM_JOINT_TEXTURE_BINDING, texture.handle.texure); //TODO(xwx):UNIFORM_JOINT_TEXTURE_BINDING not define
        // descriptorSet->bindSampler(UNIFORM_JOINT_TEXTURE_BINDING, sampler); //TODO(xwx):UNIFORM_JOINT_TEXTURE_BINDING not define
    }
}

void BakedSkinningModel::updateInstancedAttributes(const std::vector<gfx::Attribute> &attributes, Pass *pass) {
    Super::updateInstancedAttributes(attributes, pass);
    _instAnimInfoIdx = getInstancedAttributeIndex(INST_JOINT_ANIM_INFO);
    updateInstancedJointTextureInfo();
}

void BakedSkinningModel::updateInstancedJointTextureInfo() {
    auto *        jointTextureInfo = _jointMedium.jointTextureInfo;
    BakedAnimInfo animInfo         = _jointMedium.animInfo;
    index_t       idx              = _instAnimInfoIdx;
    if (idx >= 0) {
        auto *view = getInstancedAttributeBlock()->views[idx];
        view[0]    = animInfo.data[0];
        view[1]    = jointTextureInfo[1];
        view[2]    = jointTextureInfo[2];
    }
}

} // namespace scene
} // namespace cc
