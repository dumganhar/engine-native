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

class MeshRenderer : public RenderableComponent {
public:
    MeshRenderer()           = default;
    ~MeshRenderer() override = default;

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

    void onLoad() override;

    // Redo, Undo, Prefab restore, etc.
    void onRestore() override;

    void onEnable() override;

    void onDisable() override;

    void onDestroy() override;

protected:
    void updateModels();
    void createModel();

    void attachToScene() override;
    void detachFromScene() override;

    void onMaterialModified(index_t index, Material *material) override;
    void onRebuildPSO(index_t index, Material *material) override;
    void clearMaterials() override;

    void onVisibilityChange(Layers::Enum val) override;

    virtual void updateModelParams();
    virtual void onMeshChanged(Mesh *old) {}

    static Material *getBuiltinMaterial();
    bool             isBatchingEnabled();

    //    @serializable
    Mesh *_mesh{nullptr};

    scene::Model *_model{nullptr};

private:
    MorphRenderingInstance *_morphInstance{nullptr};

    scene::Model::Type _modelType{scene::Model::Type::DEFAULT};
    //cjh    @serializable
    bool _enableMorph{true};
};

} // namespace cc
