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

#include "base/Macros.h"
#include "base/RefCounted.h"
#include "core/assets/TextureCube.h"
#include "pipeline/GlobalDescriptorSetManager.h"
#include "renderer/gfx-base/GFXTexture.h"
#include "scene/Model.h"

namespace cc {
namespace scene {

class Skybox;

class SkyboxInfo : public RefCounted {
public:
    SkyboxInfo(/* args */) = default;
    ~SkyboxInfo() override = default;

    /**
     * @en Whether activate skybox in the scene
     * @zh 是否启用天空盒？
     */
    void        setEnabled(bool val);
    inline bool isEnabled() const { return _enabled; }

    /**
      * @en Whether use environment lighting
      * @zh 是否启用环境光照？
      */
    void        setUseIBL(bool val);
    inline bool isUseIBL() const { return _useIBL; }

    void                setEnvmap(TextureCube *val);
    inline TextureCube *getEnvamp() const { return _envmap; }

    /**
     * @en Whether enable RGBE data support in skybox shader
     * @zh 是否需要开启 shader 内的 RGBE 数据支持？
     */
    void        setRGBE(bool val);
    inline bool isRGBE() const { return _isRGBE; }

    void activate(Skybox *resource);

    //cjh JSB need to bind the property, so need to make it public
    //private:
    TextureCube *_envmap{nullptr};
    bool         _isRGBE{false};
    bool         _enabled{false};
    bool         _useIBL{false};
    Skybox *     _resource{nullptr};
};

class Skybox final {
public:
    Skybox()  = default;
    ~Skybox() = default;

    void initialize(const SkyboxInfo &skyboxInfo);
    void activate();

    inline Model *getModel() const { return _model.get(); }

    /**
     * @en Whether activate skybox in the scene
     * @zh 是否启用天空盒？
     */
    inline bool isEnabled() const { return _enabled; }
    inline void setEnabled(bool val) {
        _enabled = val;
        if (val) {
            activate();
        } else {
            updatePipeline();
        }
    }
    /**
     * @en Whether use environment lighting
     * @zh 是否启用环境光照？
     */
    inline bool isUseIBL() const { return _useIBL; }
    inline void setUseIBL(bool val) {
        _useIBL = val;
        updatePipeline();
    }

    /**
     * @en Whether enable RGBE data support in skybox shader
     * @zh 是否需要开启 shader 内的 RGBE 数据支持？
     */
    inline bool isRGBE() const { return _isRGBE; }
    void        setIsRGBE(bool val);

    /**
     * @en The texture cube used for the skybox
     * @zh 使用的立方体贴图
     */
    inline TextureCube *getEnvmap() const { return _envmap.get(); }
    void                setEnvmap(TextureCube *val);

private:
    void updatePipeline() const;
    void updateGlobalBinding();

    SharedPtr<TextureCube>     _envmap;
    pipeline::GlobalDSManager *_globalDSManager{nullptr};
    SharedPtr<Model>           _model;
    SharedPtr<TextureCube>     _default;
    bool                       _enabled{false};
    bool                       _useIBL{false};
    bool                       _isRGBE{false};

    CC_DISALLOW_COPY_MOVE_ASSIGN(Skybox);
};

} // namespace scene
} // namespace cc
