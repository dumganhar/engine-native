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

#include <vector>

#include "base/TypeDef.h"

#include "core/components/Component.h"
#include "core/scene-graph/Layers.h"

namespace cc {

class Material;
class MaterialInstance;

namespace scene {
class Model;
}

class RenderableComponent : public components::Component {
public:
    RenderableComponent()           = default;
    ~RenderableComponent() override = default;

    inline scenegraph::Layers::Enum getVisibility() const {
        return _visFlags;
    }

    inline void setVisibility(scenegraph::Layers::Enum val) {
        _visFlags = val;
        onVisibilityChange(val);
    }

    //cjh    @type(Material)
    //    @displayOrder(0)
    //    @displayName('Materials')
    const std::vector<Material *> &getSharedMaterials() const {
        // if we don't create an array copy, the editor will modify the original array directly.
        return /*cjh (EDITOR && this._materials.slice()) || */ _materials;
    }

    void setSharedMaterials(const std::vector<Material *> &val);

    /**
     * @en The materials of the model.
     * @zh 模型材质。
     */
    std::vector<MaterialInstance *> &getMaterials();
    void                             setMaterials(const std::vector<Material *> &val);

    inline Material *getSharedMaterial() {
        return getMaterial(0);
    }

    /**
     * @en Get the shared material asset of the specified sub-model.
     * @zh 获取指定子模型的共享材质资源。
     */
    inline Material *getMaterial(index_t idx) {
        if (idx < 0 || idx >= _materials.size()) {
            return nullptr;
        }
        return _materials[idx];
    }

    /**
     * @en Set the shared material asset of the specified sub-model,
     * new material instance will be created automatically if the sub-model is already using one.
     * @zh 设置指定子模型的 sharedMaterial，如果对应位置有材质实例则会创建一个对应的材质实例。
     */
    void setMaterial(Material *material, index_t index);

    inline MaterialInstance *getMaterial() {
        return getMaterialInstance(0);
    }

    inline void setMaterial(Material *val) {
        if (_materials.size() == 1 && !_materialInstances[0] && _materials[0] == val) {
            return;
        }
        setMaterialInstance(val, 0);
    }

    /**
     * @en Get the material instance of the specified sub-model.
     * @zh 获取指定子模型的材质实例。
     */
    MaterialInstance *getMaterialInstance(index_t idx);

    /**
     * @en Set the material instance of the specified sub-model.
     * @zh 获取指定子模型的材质实例。
     */
    void setMaterialInstance(Material *matInst, index_t index);

    /**
     * @en Get the actual rendering material of the specified sub-model.
     * (material instance if there is one, or the shared material asset)
     * @zh 获取指定位置可供渲染的材质，如果有材质实例则使用材质实例，如果没有则使用材质资源
     */
    Material *getRenderMaterial(index_t index);

    const std::vector<scene::Model *> &collectModels() { return _models; }

    // OVERRIDE FUNCTIONS
    virtual void attachToScene() {}
    virtual void detachFromScene() {}
    virtual void onMaterialModified(index_t index, Material *material) {}
    virtual void onRebuildPSO(index_t index, Material *material) {}
    virtual void clearMaterials() {}
    virtual void onVisibilityChange(scenegraph::Layers::Enum val) {}
    //

protected:
    //cjh @type([Material])
    std::vector<Material *> _materials;

    std::vector<MaterialInstance *> _materialInstances;

    std::vector<scene::Model *> _models;

    //cjh @serializable
    scenegraph::Layers::Enum _visFlags{scenegraph::Layers::Enum::NONE};
};

} // namespace cc
