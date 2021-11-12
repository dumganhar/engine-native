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

#include <tuple>
#include <vector>
#include "core/TypedArray.h"
#include "core/assets/RenderingSubMesh.h"
#include "core/assets/Texture2D.h"
#include "core/builtin/BuiltinResMgr.h"
#include "core/event/CallbacksInvoker.h"
#include "core/geometry/AABB.h"
#include "core/scene-graph/Layers.h"
#include "renderer/gfx-base/GFXBuffer.h"
#include "renderer/gfx-base/GFXDef-common.h"

namespace cc {

class Material;
class Node;

namespace scene {

// SubModel.h -> Define.h -> Model.h, so do not include SubModel.h here.
class SubModel;
// RenderScene.h <-> Model.h, so do not include RenderScene.h here.
class RenderScene;
class Pass;
struct IMacroPatch;
struct InstancedAttributeBlock {
    Uint8Array                  buffer;
    std::vector<TypedArray>     views;
    std::vector<gfx::Attribute> attributes;
};

class Model {
public:
    friend class Skybox;

    enum class Type {
        DEFAULT,
        SKINNING,
        BAKED_SKINNING,
        BATCH_2D,
        PARTICLE_BATCH,
        LINE,
    };

    Model();
    virtual ~Model() = default;

    void                             initialize();
    virtual void                     destroy();
    void                             updateWorldBound();
    void                             createBoundingShape(const std::optional<Vec3> &minPos, const std::optional<Vec3> &maxPos);
    virtual void                     initSubModel(index_t idx, RenderingSubMesh *subMeshData, Material *mat);
    void                             setSubModelMesh(index_t idx, RenderingSubMesh *subMesh) const;
    virtual void                     setSubModelMaterial(index_t idx, Material *mat);
    void                             onGlobalPipelineStateChanged() const;
    void                             onMacroPatchesStateChanged();
    void                             updateLightingmap(Texture2D *texture, const Vec4 &uvParam);
    virtual std::vector<IMacroPatch> getMacroPatches(index_t subModelIndex);
    virtual void                     updateInstancedAttributes(const std::vector<gfx::Attribute> &attributes, Pass *pass);

    virtual void updateTransform(uint32_t stamp);
    virtual void updateUBOs(uint32_t stamp);

    inline void attachToScene(RenderScene *scene) { _scene = scene; };
    inline void detachFromScene() { _scene = nullptr; };
    inline void setCastShadow(bool value) { _castShadow = value; }
    inline void setEnabled(bool value) { _enabled = value; }
    inline void setInstMatWorldIdx(int32_t idx) { _instMatWorldIdx = idx; }
    inline void setLocalBuffer(gfx::Buffer *buffer) { _localBuffer = buffer; }
    inline void setNode(Node *node) { _node = node; }
    inline void setReceiveShadow(bool value) {
        _receiveShadow = value;
        onMacroPatchesStateChanged();
    }
    inline void setTransform(Node *node) { _transform = node; }
    inline void setVisFlags(uint32_t flags) { _visFlags = flags; }
    inline void setBounds(geometry::AABB *world) {
        _worldBounds = world;
        _modelBounds->set(_worldBounds->getCenter(), _worldBounds->getHalfExtents());
    }
    inline void setInstancedAttributeBlock(const InstancedAttributeBlock &val) { _instanceAttributeBlock = val; }

    inline bool                               isInited() const { return _inited; };
    inline bool                               getCastShadow() const { return _castShadow; }
    inline bool                               isEnabled() const { return _enabled; }
    inline bool                               isInstancingEnabled() const { return _instMatWorldIdx >= 0; };
    inline int32_t                            getInstMatWorldIdx() const { return _instMatWorldIdx; }
    inline const std::vector<gfx::Attribute> &getInstanceAttributes() const { return _instanceAttributes; }
    inline InstancedAttributeBlock *          getInstancedAttributeBlock() { return &_instanceAttributeBlock; }
    inline uint8_t *                          getInstancedBuffer() const { return std::get<0>(_instancedBuffer); }
    inline uint32_t                           getInstancedBufferSize() const { return std::get<1>(_instancedBuffer); }
    inline gfx::Buffer *                      getLocalBuffer() const { return _localBuffer; }
    inline Float32Array                       getLocalData() const { return _localData; }
    inline geometry::AABB *                   getModelBounds() const { return _modelBounds; }
    inline Node *                             getNode() const { return _node; }
    inline bool                               getReceiveShadow() const { return _receiveShadow; }
    inline const std::vector<SubModel *> &    getSubModels() const { return _subModels; }
    inline Node *                             getTransform() const { return _transform; }
    inline bool                               getTransformUpdated() const { return _transformUpdated; }
    inline uint32_t                           getUpdateStamp() const { return _updateStamp; }
    inline uint32_t                           getVisFlags() const { return _visFlags; }
    inline geometry::AABB *                   getWorldBounds() const { return _worldBounds; }
    inline Type                               getType() const { return _type; };
    inline void                               setType(Type type) { _type = type; }

    inline RenderScene *getScene() const { return _scene; }
    inline void         setDynamicBatching(bool val) { _isDynamicBatching = val; }
    inline bool         isDynamicBatching() const { return _isDynamicBatching; }

    void         initLocalDescriptors(index_t subModelIndex);
    virtual void updateLocalDescriptors(index_t subModelIndex, gfx::DescriptorSet *descriptorSet);
    int32_t      getInstancedAttributeIndex(const std::string &name) const;

    // For JS
    inline void              setCalledFromJS(bool v) { _isCalledFromJS = v; }
    inline CallbacksInvoker &getEventProcessor() { return _eventProcessor; }
    void                     _setInstancedAttributesViewData(index_t viewIdx, index_t arrIdx, float value);
    //

protected:
    static void uploadMat4AsVec4x3(const Mat4 &mat, Float32Array &v1, Float32Array &v2, Float32Array &v3);

    void updateAttributesAndBinding(index_t subModelIndex);

    SubModel *createSubModel() const;

    Type            _type{Type::DEFAULT};
    bool            _transformUpdated{false};
    geometry::AABB *_worldBounds{nullptr};
    geometry::AABB *_modelBounds{nullptr};
    gfx::Device *   _device{nullptr};
    bool            _inited{false};
    uint32_t        _descriptorSetCount{1};

    bool _enabled{false};
    bool _castShadow{false};
    bool _receiveShadow{false};
    bool _isDynamicBatching{false};

    int32_t                         _instMatWorldIdx{-1};
    uint32_t                        _visFlags{static_cast<uint32_t>(Layers::Enum::NONE)};
    uint32_t                        _updateStamp{0};
    Node *                          _transform{nullptr};
    Node *                          _node{nullptr};
    Float32Array                    _localData;
    std::tuple<uint8_t *, uint32_t> _instancedBuffer{nullptr, 0};
    gfx::Buffer *                   _localBuffer{nullptr};
    InstancedAttributeBlock         _instanceAttributeBlock{};
    std::vector<SubModel *>         _subModels;
    std::vector<gfx::Attribute>     _instanceAttributes;

    Texture2D *_lightmap{nullptr};
    Vec4       _lightmapUVParam;

    RenderScene *_scene{nullptr};

    // For JS
    CallbacksInvoker _eventProcessor;
    bool             _isCalledFromJS{false};
    //

private:
    CC_DISALLOW_COPY_MOVE_ASSIGN(Model);
};

} // namespace scene
} // namespace cc
