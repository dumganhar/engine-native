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
#include <string>
#include "core/Root.h"
#include "core/scene-graph/Node.h"
#include "scene/BakedSkinningModel.h"
#include "scene/DirectionalLight.h"
#include "scene/DrawBatch2D.h"
#include "scene/Model.h"
#include "scene/SkinningModel.h"
#include "scene/SphereLight.h"
#include "scene/SpotLight.h"
#include "scene/Camera.h"

namespace cc {
namespace scene {

struct IRenderSceneInfo {
    std::string name;
};

struct IRaycastResult {
    Node *node{nullptr};
    float distance{0.F};
};

class RenderScene final {
public:
    explicit RenderScene(Root *root);
    RenderScene(const RenderScene &) = delete;
    RenderScene(RenderScene &&)      = delete;
    ~RenderScene()                   = default;
    RenderScene &operator=(const RenderScene &) = delete;
    RenderScene &operator=(RenderScene &&) = delete;

    bool initialize(const IRenderSceneInfo &info);
    void update(uint32_t stamp);
    void destroy();

    void addCamera(Camera *camera);
    void removeCamera(Camera *camera);
    void removeCameras();

    void unsetMainLight(DirectionalLight *dl);
    void addDirectionalLight(DirectionalLight *dl);
    void removeDirectionalLight(DirectionalLight *dl);

    void addSphereLight(SphereLight *);
    void removeSphereLight(SphereLight *);
    void removeSphereLights();

    void addSpotLight(SpotLight *);
    void removeSpotLight(SpotLight *);
    void removeSpotLights();

    void addModel(Model *);
    void addSkinningModel(SkinningModel *);
    void addBakedSkinningModel(BakedSkinningModel *);
    void removeModel(uint32_t);
    void removeModels();

    void updateBatches(std::vector<DrawBatch2D *> &&);
    void addBatch(DrawBatch2D *);
    void removeBatch(DrawBatch2D *);
    void removeBatch(uint32_t index);
    void removeBatches();

    void onGlobalPipelineStateChanged();

    inline DirectionalLight *getMainLight() const { return _mainLight; }
    inline void              setMainLight(DirectionalLight *dl) { _mainLight = dl; }

    inline uint64_t                          generateModelId() { return _modelId++; }
    inline Root *                            getRoot() const { return _root; }
    inline const std::string &               getName() const { return _name; }
    inline const std::vector<Camera *> &     getCameras() const { return _cameras; }
    inline const std::vector<SphereLight *> &getSphereLights() const { return _sphereLights; }
    inline const std::vector<SpotLight *> &  getSpotLight() const { return _spotLights; }
    inline const std::vector<Model *> &      getModels() const { return _models; }
    inline const std::vector<DrawBatch2D *> &getBatches() const { return _batches; }

private:
    std::string                _name;
    Root *                     _root{nullptr};
    uint64_t                   _modelId{0};
    DirectionalLight *         _mainLight{nullptr};
    std::vector<Model *>       _models;
    std::vector<Camera *>      _cameras;
    std::vector<SphereLight *> _sphereLights;
    std::vector<SpotLight *>   _spotLights;
    std::vector<DrawBatch2D *> _batches;
};

} // namespace scene
} // namespace cc
