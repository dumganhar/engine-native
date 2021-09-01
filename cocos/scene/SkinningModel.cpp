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
#include <utility>

#include "scene/RenderScene.h"
#include "scene/SkinningModel.h"

namespace {

void getRelevantBuffers(std::vector<index_t> &outIndices, std::vector<int32_t> &outBuffers, const std::vector<std::vector<int32_t>> &jointMaps, int32_t targetJoint) {
    for (int32_t i = 0; i < jointMaps.size(); i++) {
        index_t index = CC_INVALID_INDEX;
        for (int32_t j = 0; j < jointMaps[i].size(); j++) {
            if (jointMaps[i][j] == targetJoint) {
                index = j;
                break;
            }
        }
        if (index >= 0) {
            outBuffers.emplace_back(i);
            outIndices.emplace_back(index);
        }
    }
}

std::vector<cc::scene::IMacroPatch> myPatches{{"CC_USE_SKINNING", true}};

} // namespace
namespace cc {
namespace scene {

void SkinningModel::destroy() {
    bindSkeleton(nullptr, nullptr, nullptr);
    if (!_buffers.empty()) {
        for (gfx::Buffer *buffer : _buffers) {
            CC_SAFE_DESTROY(buffer);
        }
        _buffers.clear();
    }
    Super::destroy();
}

void SkinningModel::bindSkeleton(Skeleton *skeleton, scenegraph::Node *skinningRoot, Mesh *mesh) {
    for (const JointInfo &joint : _joints) {
        // deleteTransform(joint.target); // deleteTransform not implementation
    }
    _bufferIndices.clear();
    _joints.clear();

    if (!skeleton || !skinningRoot || !mesh) return;
    setTransform(skinningRoot);
    // std::vector<geometry::AABB> boneSpaceBounds = mesh->getBoneSpaceBounds(skeleton); // 'AABB' has been explicitly marked deleted here
    auto jointMaps = mesh->getStruct().jointMaps;
    ensureEnoughBuffers(jointMaps != std::nullopt && !jointMaps->empty() || 1);
    _bufferIndices = mesh->getJointBufferIndices();

    for (index_t index = 0; index < skeleton->getJoints().size(); ++index) {
        // geometry::AABB bound  = boneSpaceBounds[index]; // 'AABB' has been explicitly marked deleted here
        auto *target = skinningRoot->getChildByPath(skeleton->getJoints()[index]);
        // if (!bound || !target) continue;
        // auto transform = getTransform(target, skiinningRoot); // getTransform not implementation
        Mat4                 bindPose = skeleton->getBindposes()[index];
        std::vector<index_t> indices;
        std::vector<index_t> buffers;
        if (!jointMaps.has_value()) {
            indices.emplace_back(index);
            buffers.emplace_back(0);
        } else {
            getRelevantBuffers(indices, buffers, jointMaps.value(), index);
        }
        // _joints.emplace_back({indices, buffers, bound, target, bindPose, transform}); // transform not define
    }
}

void SkinningModel::updateWorldMatrix(JointInfo *info, uint32_t stamp) {
    int i = -1;
    _worldMatrix.setIdentity();
    auto *                        currTransform = &info->transform;
    auto                          parentSize    = static_cast<int>(info->parents.size());
    std::vector<JointTransform *> transStacks;
    while (currTransform->node) {
        if ((currTransform->stamp == stamp || currTransform->stamp + 1 == stamp) && !currTransform->node->getFlagsChanged()) {
            _worldMatrix.set(currTransform->world);
            currTransform->stamp = stamp;
            break;
        }
        currTransform->stamp = stamp;
        transStacks.push_back(currTransform);
        i++;
        if (i >= parentSize) {
            break;
        }
        currTransform = &info->parents[i];
    }
    while (i > -1) {
        currTransform = transStacks[i--];
        auto *node    = currTransform->node;
        Mat4::fromRTS(node->getRotation(), node->getPosition(), node->getScale(), &currTransform->local);
        Mat4::multiply(_worldMatrix, currTransform->local, &currTransform->world);
        _worldMatrix.set(currTransform->world);
    }
}

void SkinningModel::updateUBOs(uint32_t stamp) {
    Super::updateUBOs(stamp);
    uint32_t bIdx = 0;
    Mat4     mat4;
    for (const JointInfo &jointInfo : _joints) {
        Mat4::multiply(jointInfo.transform.world, jointInfo.bindpose, &mat4);
        for (uint32_t buffer : jointInfo.buffers) {
            uploadJointData(jointInfo.indices[bIdx] * 12, mat4, _dataArray[buffer]->data());
            bIdx++;
        }
        bIdx = 0;
    }
    bIdx = 0;
    for (gfx::Buffer *buffer : _buffers) {
        buffer->update(_dataArray[bIdx]->data(), buffer->getSize());
        bIdx++;
    }
}

void SkinningModel::initSubModel(index_t idx, RenderingSubMesh *subMeshData, Material *mat) {
    // auto original = subMeshData->getVertexBuffers(); //TODO(xwx): getVertexBuffers not implement
    auto iaInfo = subMeshData->getIaInfo();
    // inInfo.vertexBuffers = subMeshData->getjointMappedBuffers();
    Super::initSubModel(idx, subMeshData, mat);
    // iaInfo.vertexBuffers = original;
}

std::vector<IMacroPatch> SkinningModel::getMacroPatches(index_t subModelIndex) const {
    auto superMacroPatches = Super::getMacroPatches(subModelIndex);
    if (!superMacroPatches.empty()) {
        myPatches.reserve(myPatches.size() + superMacroPatches.size());
        myPatches.insert(std::end(myPatches), std::begin(superMacroPatches), std::end(superMacroPatches));
    }
    return myPatches;
}
void SkinningModel::uploadJointData(uint32_t base, const Mat4 &mat, float *dst) {
    memcpy(reinterpret_cast<void *>(dst + base), mat.m, sizeof(float) * 12);
    dst[base + 3]  = mat.m[12];
    dst[base + 7]  = mat.m[13];
    dst[base + 11] = mat.m[14];
}

SkinningModel::~SkinningModel() {
    for (auto *curr : _dataArray) {
        delete curr;
    }
}

void SkinningModel::setBuffers(const std::vector<gfx::Buffer *> &buffers) {
    _buffers = buffers;
    for (auto *buffer : _buffers) {
        auto *data = new std::array<float, pipeline::UBOSkinning::COUNT>();
        _dataArray.push_back(data);
    }
}

void SkinningModel::updateLocalDescriptors(index_t submodelIdx, gfx::DescriptorSet *descriptorset) {
    Super::updateLocalDescriptors(submodelIdx, descriptorset);
    gfx::Buffer *buffer = _buffers[_bufferIndices[submodelIdx]];
    if (buffer) {
        descriptorset->bindBuffer(pipeline::UBOSkinning::BINDING, buffer);
    }
}

void SkinningModel::updateTransform(uint32_t stamp) {
    auto *root = getTransform();
    if (root->getFlagsChanged() || root->getDirtyFlag()) {
        root->updateWorldTransform();
        _transformUpdated = true;
    }
    Vec3           v3Min{INFINITY, INFINITY, INFINITY};
    Vec3           v3Max{-INFINITY, -INFINITY, -INFINITY};
    geometry::AABB ab1;
    Vec3           v31;
    Vec3           v32;
    for (JointInfo &jointInfo : _joints) {
        updateWorldMatrix(&jointInfo, stamp);
        jointInfo.bound->transform(_worldMatrix, &ab1);
        ab1.getBoundary(&v31, &v32);
        Vec3::min(v3Min, v31, &v3Min);
        Vec3::max(v3Max, v32, &v3Max);
    }
    if (_modelBounds->isValid() && _worldBounds) {
        geometry::AABB::fromPoints(v3Min, v3Max, _modelBounds);
        _modelBounds->transform(root->getWorldMatrix(), _worldBounds);
    }
}

void SkinningModel::ensureEnoughBuffers(index_t count) {
    for (index_t i = 0; i < count; i++) {
        if (!_buffers[i]) {
            _device->createBuffer({
                gfx::BufferUsageBit::UNIFORM | gfx::BufferUsageBit::TRANSFER_DST,
                gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
                pipeline::UBOSkinning::SIZE,
                pipeline::UBOSkinning::SIZE,
            });
        }
        if (!_dataArray[i]) {
            _dataArray[i] = new std::array<float, pipeline::UBOSkinning::COUNT>;
        }
    }
}
} // namespace scene
} // namespace cc
