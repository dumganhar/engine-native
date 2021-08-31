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

#pragma once

#include <utility>

#include "3d/assets/Skeleton.h"
#include "gfx-base/GFXDef-common.h"
#include "scene/Model.h"
#include "scene/MorphModel.h"

namespace cc {
namespace scene {
struct BakedAnimInfo {
    gfx::Buffer *buffer{nullptr};
    uint8_t *    data{nullptr};
    uint8_t *    dirty{nullptr};
    inline bool  getDirty() const {
        return static_cast<bool>(*reinterpret_cast<int32_t *>(dirty));
    }
};
struct BakedJointInfo {
    std::vector<geometry::AABB *> boundsInfo;
    uint8_t *                     jointTextureInfo{nullptr};
    BakedAnimInfo                 animInfo;
    gfx::Buffer *                 buffer{nullptr};
};
class BakedSkinningModel : public MorphModel {
public:
    BakedSkinningModel()                           = default;
    BakedSkinningModel(const BakedSkinningModel &) = delete;
    BakedSkinningModel(BakedSkinningModel &&)      = delete;
    ~BakedSkinningModel() override                 = default;
    BakedSkinningModel &operator=(const BakedSkinningModel &) = delete;
    BakedSkinningModel &operator=(BakedSkinningModel &&) = delete;

    void                     destroy() override;
    void                     bindSkeleton(Skeleton *skeleton, Node *skinningRoot, Mesh *mesh) const;
    void                     initSubModel(index_t idx, RenderingSubMesh *subMeshData, Material mat) override;
    void                     initLocalDescriptors(index_t subModelIndex);
    std::vector<IMacroPatch> getMacroPatches(index_t subModelIndex) const override;
    void                     updateLocalDescriptors(index_t submodelIdx, gfx::DescriptorSet *descriptorset) const override;
    void                     updateTransform(uint32_t stamp) override;
    void                     updateUBOs(uint32_t stamp) override;
    void                     updateInstancedAttributes(const std::vector<gfx::Attribute> &attributes, Pass *pass);
    void                     updateInstancedJointTextureInfo() const;
    // void                     uploadAnimation(AnimationClip *anim); // TODO(xwx)
    inline void updateModelBounds(geometry::AABB *modelBounds) {
        if (modelBounds == nullptr) {
            return;
        }
        _modelBounds->setValid(true);
        _modelBounds->set(modelBounds->getCenter(), modelBounds->getHalfExtents());
    }

    inline void setJointMedium(bool isUploadAnim, BakedJointInfo &&jointMedium) {
        _isUploadAnim = isUploadAnim;
        _jointMedium  = std::move(jointMedium);
    }
    inline void setAnimInfoIdx(index_t idx) {
        _instAnimInfoIdx = idx;
    }

protected:
    // TODO(xwx)
    // applyJointTexture(IJointTextureHandle *texture) const;

private:
    ModelType      _type{ModelType::BAKED_SKINNING};
    BakedJointInfo _jointMedium;
    bool           _isUploadAnim{false};
    index_t        _instAnimInfoIdx{CC_INVALID_INDEX};
    // TODO(xwx)
    // DataPoolManager _dataPoolManager;
    Skeleton *_skeleton{nullptr};
    // AnimationClip uploadedAnim;
};

} // namespace scene
} // namespace cc
