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
#include "3d/skeletal-animation/SkeletalAnimationUtils.h"
#include "scene/Model.h"
#include "scene/SubModel.h"

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

BakedSkinningModel::BakedSkinningModel()
: Super(), _dataPoolManager(Root::getInstance()->getDataPoolManager()) {
    _type        = Model::Type::BAKED_SKINNING;
    _jointMedium = {BakedJointInfo{.jointTextureInfo = Float32Array(4), .animInfo = _dataPoolManager->jointAnimationInfo->getData()}};
}

void BakedSkinningModel::destroy() {
    // CC_SAFE_DELETE(uploadedAnim);
    for (geometry::AABB *boundInfo : _jointMedium.boundsInfo) {
        CC_SAFE_DELETE(boundInfo);
    }
    _jointMedium.boundsInfo.clear();
    if (_jointMedium.buffer != nullptr) {
        CC_SAFE_DESTROY(_jointMedium.buffer);
    }
    applyJointTexture(std::nullopt);
    Super::destroy();
}

void BakedSkinningModel::bindSkeleton(Skeleton *skeleton, Node *skinningRoot, Mesh *mesh) {
    _skeleton = skeleton;
    _mesh     = mesh;
    if (skeleton == nullptr || skinningRoot == nullptr || mesh == nullptr) return;
    setTransform(skinningRoot);
    _jointMedium.animInfo = _dataPoolManager->jointAnimationInfo->getData(skinningRoot->getUUid());
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
    IAnimInfo &     animInfo  = _jointMedium.animInfo;
    geometry::AABB *skelBound = !_jointMedium.boundsInfo.empty() ? _jointMedium.boundsInfo[animInfo.data[0]] : nullptr;
    if (_worldBounds && skelBound) {
        Node *node = getTransform();
        skelBound->transform(node->getWorldMatrix(), _worldBounds);
    }
}

void BakedSkinningModel::updateUBOs(uint32_t stamp) {
    Model::updateUBOs(stamp);
    IAnimInfo &info = _jointMedium.animInfo;
    int        idx  = _instAnimInfoIdx;
    if (idx >= 0) {
        auto &views = getInstancedAttributeBlock()->views;
        views[0]    = static_cast<Float32Array>(info.data[0]);
    } else if (info.dirty) {
        // info.buffer->update(info.data, info.buffer->getSize()); //TODO(xwx): need Refactor TypedArray define in cpp
        info.dirty = false;
    }
}

void BakedSkinningModel::applyJointTexture(const std::optional<IJointTextureHandle> &texture) {
    auto oldTex = _jointMedium.texture;
    if (oldTex.has_value() && &oldTex.value() != &texture.value()) {
        _dataPoolManager->jointTexturePool->releaseHandle(oldTex.value());
    }
    _jointMedium.texture = texture;
    if (!texture.has_value()) {
        return;
    }
    auto *buffer           = _jointMedium.buffer;
    auto  jointTextureInfo = _jointMedium.jointTextureInfo;
    jointTextureInfo[0]    = texture->handle.texture->getWidth();
    jointTextureInfo[1]    = _skeleton->getJoints().size();
    jointTextureInfo[2]    = texture->pixelOffset + 0.1; // guard against floor() underflow
    jointTextureInfo[3]    = 1 / jointTextureInfo[0];
    updateInstancedJointTextureInfo();
    if (buffer != nullptr) {
        // buffer->update(jointTextureInfo);  //TODO(xwx): need Refactor TypedArray define in cpp
    }
    auto *tex = texture->handle.texture;

    for (auto *subModel : _subModels) {
        auto *descriptorSet = subModel->getDescriptorSet();
        descriptorSet->bindTexture(pipeline::JOINTTEXTURE::BINDING, tex);
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
    gfx::Buffer *    buffer   = _jointMedium.buffer;
    auto             texture  = _jointMedium.texture;
    const IAnimInfo &animInfo = _jointMedium.animInfo;
    descriptorSet->bindBuffer(pipeline::UBOSkinningTexture::BINDING, buffer);
    descriptorSet->bindBuffer(pipeline::UBOSkinningAnimation::BINDING, animInfo.buffer);
    if (texture.has_value()) {
        auto *sampler = pipeline::SamplerLib::getSampler(JOINT_TEXTURE_SAMPLER_HASH);
        descriptorSet->bindTexture(pipeline::JOINTTEXTURE::BINDING, texture->handle.texture);
        descriptorSet->bindSampler(pipeline::JOINTTEXTURE::BINDING, sampler);
    }
}

void BakedSkinningModel::updateInstancedAttributes(const std::vector<gfx::Attribute> &attributes, Pass *pass) {
    Super::updateInstancedAttributes(attributes, pass);
    _instAnimInfoIdx = getInstancedAttributeIndex(INST_JOINT_ANIM_INFO);
    updateInstancedJointTextureInfo();
}

void BakedSkinningModel::updateInstancedJointTextureInfo() {
    auto             jointTextureInfo = _jointMedium.jointTextureInfo;
    const IAnimInfo &animInfo         = _jointMedium.animInfo;
    index_t          idx              = _instAnimInfoIdx;
    if (idx >= 0) {
        Float32Array view = std::get<Float32Array>(getInstancedAttributeBlock()->views[idx]); // TODO(xwx): not sure can get Float32Array or Uint8Array
        view[0]           = animInfo.data[0];
        view[1]           = jointTextureInfo[1];
        view[2]           = jointTextureInfo[2];
    }
}

} // namespace scene
} // namespace cc
