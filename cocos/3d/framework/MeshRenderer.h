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

#include "core/components/RenderableComponent.h"
#include "scene/Model.h"

namespace cc {

class Mesh;
class MorphRenderingInstance;

/**
 * @en Shadow projection mode.
 * @zh 阴影投射方式。
 */
enum class ModelShadowCastingMode {
    /**
     * @en Disable shadow projection.
     * @zh 不投射阴影。
     */
    OFF = 0,
    /**
     * @en Enable shadow projection.
     * @zh 开启阴影投射。
     */
    ON = 1
};

/**
 * @en Shadow receive mode.
 * @zh 阴影接收方式。
 */
enum class ModelShadowReceivingMode {
    /**
     * @en Disable shadow projection.
     * @zh 不接收阴影。
     */
    OFF = 0,
    /**
     * @en Enable shadow projection.
     * @zh 开启阴影投射。
     */
    ON = 1
};

/**
 * @en model light map settings.
 * @zh 模型光照图设置
 */
class ModelLightmapSettings {
public:
    // @serializable
    Texture2D *texture{nullptr};
    // @serializable
    Vec4 uvParam;

protected:
    // @serializable
    bool _bakeable{false};
    // @serializable
    bool _castShadow{false};
    // @formerlySerializedAs('_receiveShadow')
    bool _receiveShadow{false};
    // @serializable
    float _lightmapSize{64.F};

    /**
     * @en bakeable.
     * @zh 是否可烘培。
     */
    // @editable
    inline bool isBakeable() const {
        return _bakeable;
    }

    inline void setBakeable(bool val) {
        _bakeable = val;
    }

    /**
     * @en cast shadow.
     * @zh 是否投射阴影。
     */
    // @editable
    inline bool isCastShadow() const { return _castShadow; }

    inline void setCastShadow(bool val) { _castShadow = val; }

    /**
     * @en receive shadow.
     * @zh 是否接受阴影。
     */
    // @editable
    inline bool isReceiveShadow() const {
        return _receiveShadow;
    }

    inline void setReceiveShadow(bool val) {
        _receiveShadow = val;
    }

    /**
     * @en lightmap size.
     * @zh 光照图大小
     */
    // @editable
    inline float getLightmapSize() const {
        return _lightmapSize;
    }

    void setLightmapSize(float val) {
        _lightmapSize = val;
    }
};

/**
 * @en Mesh renderer component
 * @zh 网格渲染器组件。
 */

class MeshRenderer : public RenderableComponent {
public:
    COMPONENT_EXECUTION_ORDER(MeshRenderer, 100)

    MeshRenderer()           = default;
    ~MeshRenderer() override = default;

    /**
     * @en Shadow projection mode.
     * @zh 阴影投射方式。
     */
    // @type(ModelShadowCastingMode)
    // @tooltip('i18n:model.shadow_casting_model')
    // @disallowAnimation
    inline ModelShadowCastingMode getshadowCastingMode() const { return _shadowCastingMode; }
    inline void                   setShadowCastingMode(ModelShadowCastingMode val) {
        _shadowCastingMode = val;
        // updateCastShadow();
    }

    /**
     * @en receive shadow.
     * @zh 是否接受阴影。
     */
    // @type(ModelShadowReceivingMode)
    // @tooltip('i18n:model.shadow_receiving_model')
    // @disallowAnimation
    inline ModelShadowReceivingMode getReceiveShadow() const { return _shadowReceivingMode; }
    inline void                     setReceiveShadow(ModelShadowReceivingMode val) {
        _shadowReceivingMode = val;
        // updateReceiveShadow();
    }

    /**
     * @en Gets or sets the mesh of the model.
     * Note, when set, all shape's weights would be reset to zero.
     * @zh 获取或设置模型的网格数据。
     * 注意，设置时，所有形状的权重都将归零。
     */
    //cjh    @type(Mesh)
    //    @tooltip('i18n:model.mesh')
    inline Mesh *getMesh() const {
        return _mesh;
    }

    void setMesh(Mesh *val);

    scene::Model *getModel() const { return _model; }

    // TODO(xwx): cannot understand
    // eslint-disable-next-line func-names
    // @visible(function (this: MeshRenderer) {
    //     return !!(
    //         this.mesh
    //         && this.mesh.struct.morph
    //         && this.mesh.struct.morph.subMeshMorphs.some((subMeshMorph) => !!subMeshMorph)
    //     );
    // })
    // @disallowAnimation
    inline bool isEnableMorph() const {
        return _enableMorph;
    }

    inline void setEnableMorph(bool value) {
        _enableMorph = value;
    }

    void onLoad() override;

    // Redo, Undo, Prefab restore, etc.
    void onRestore() override;

    void onEnable() override;

    void onDisable() override;

    void onDestroy() override;

    /**
     * @zh 获取子网格指定外形的权重。
     * @en Gets the weight at specified shape of specified sub mesh.
     * @param subMeshIndex Index to the sub mesh.
     * @param shapeIndex Index to the shape of the sub mesh.
     * @returns The weight.
     */
    float getWeight(index_t subMeshIndex, index_t shapeIndex);

    /**
     * @zh
     * 设置子网格所有外形的权重。
     * `subMeshIndex` 是无效索引或 `weights` 的长度不匹配子网格的外形数量时，此方法不会生效。
     * @en
     * Sets weights of each shape of specified sub mesh.
     * If takes no effect if
     * `subMeshIndex` out of bounds or
     * `weights` has a different length with shapes count of the sub mesh.
     * @param weights The weights.
     * @param subMeshIndex Index to the sub mesh.
     */
    void setWeights(const std::vector<float> &weights, index_t subMeshIndex);

    /**
     * @zh
     * 设置子网格指定外形的权重。
     * `subMeshIndex` 或 `shapeIndex` 是无效索引时，此方法不会生效。
     * @en
     * Sets the weight at specified shape of specified sub mesh.
     * If takes no effect if
     * `subMeshIndex` or `shapeIndex` out of bounds.
     * @param weight The weight.
     * @param subMeshIndex Index to the sub mesh.
     * @param shapeIndex Index to the shape of the sub mesh.
     */
    void setWeight(float weight, index_t subMeshIndex, index_t shapeIndex);

    void setInstancedAttribute(const std::string &name, std::vector<float> value);

    void updateLightmap(Texture2D *lightmap, float uOff, float vOff, float uScale, float vScale);

    // @serializable
    // @editable
    // @disallowAnimation
    ModelLightmapSettings lightmapSettings;

protected:
    void updateModels();
    void createModel();

    void attachToScene() override;
    void detachFromScene() override;

    void onUpdateLightingmap();
    void onMaterialModified(index_t index, Material *material) override;
    void onRebuildPSO(index_t index, Material *material) override;
    void clearMaterials() override;

    void onVisibilityChange(Layers::Enum val) override;
    void updateCastShadow();
    void updateReceiveShadow();

    virtual void updateModelParams();

    virtual void onMeshChanged(Mesh *old) {}

    static Material *getBuiltinMaterial();
    bool             isBatchingEnabled();

    //    @serializable
    Mesh *_mesh{nullptr};
    // @serializable
    ModelShadowCastingMode _shadowCastingMode{ModelShadowCastingMode::OFF};

    // @serializable
    ModelShadowReceivingMode _shadowReceivingMode{ModelShadowReceivingMode::ON};

    scene::Model::Type _modelType{scene::Model::Type::DEFAULT};

    scene::Model *_model{nullptr};

private:
    void watchMorphInMesh();
    void initSubMeshShapesWeights();
    void validateShapeWeights();
    void uploadSubMeshShapesWeights(index_t subMeshIndex);

    std::vector<std::vector<float>> _subMeshShapesWeights;

    MorphRenderingInstance *_morphInstance{nullptr};

    //cjh    @serializable
    bool _enableMorph{true};
};

} // namespace cc
