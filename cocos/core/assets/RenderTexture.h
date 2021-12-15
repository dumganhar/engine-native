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

#include "core/assets/TextureBase.h"
#include "renderer/gfx-base/GFXDef.h"
#include "scene/RenderWindow.h"

namespace cc {

struct IRenderTextureCreateInfo {
    cc::optional<std::string>         name;
    uint32_t                           width;
    uint32_t                           height;
    cc::optional<gfx::RenderPassInfo> passInfo;
};
namespace scene {
class RenderWindow;
}

namespace gfx {
class Texture;
class Sampler;
} // namespace gfx

/**
 * @en Render texture is a render target for [[Camera]] or [[Canvas]] component,
 * the render pipeline will use its [[RenderWindow]] as the target of the rendering process.
 * @zh 渲染贴图是 [[Camera]] 或 [[Canvas]] 组件的渲染目标对象，渲染管线会使用它的 [[RenderWindow]] 作为渲染的目标窗口。
 */
class RenderTexture final : public TextureBase {
public:
    using Super = TextureBase;

    explicit RenderTexture()  = default;
    ~RenderTexture() override = default;
    /**
     * @en The pixel width of the render texture
     * @zh 渲染贴图的像素宽度
     */
    inline uint32_t getWidth() const { return _width; }

    /**
     * @en The pixel height of the render texture
     * @zh 渲染贴图的像素高度
     */
    inline uint32_t getHeight() const { return _height; }

    /**
     * @en The render window for the render pipeline, it's created internally and cannot be modified.
     * @zh 渲染管线所使用的渲染窗口，内部逻辑创建，无法被修改。
     */
    inline scene::RenderWindow *getWindow() const { return _window; }

    void initialize(const IRenderTextureCreateInfo &info);
    void reset(const IRenderTextureCreateInfo &info); // to be consistent with other assets

    bool destroy() override;

    /**
     * @en Resize the render texture
     * @zh 修改渲染贴图的尺寸
     * @param width The pixel width
     * @param height The pixel height
     */
    void resize(uint32_t width, uint32_t height);

    // TODO: migration with TextureBase data
    // @ts-expect-error Hack
    //    get _serialize () { return null; }
    // @ts-expect-error Hack
    //    get _deserialize () { return null; }

    // To be compatible with material property interface
    /**
     * @en Gets the related [[Texture]] resource, it's also the color attachment for the render window
     * @zh 获取渲染贴图的 GFX 资源，同时也是渲染窗口所指向的颜色缓冲贴图资源
     */
    gfx::Texture *getGFXTexture() const override;

    /**
     * @en Gets the sampler resource for the render texture
     * @zh 获取渲染贴图的采样器
     */
    gfx::Sampler *getGFXSampler() const override;

    /**
     * @en Gets the sampler hash for the render texture
     * @zh 获取渲染贴图的采样器哈希值
     */
    uint64_t getSamplerHash() const override;

    void onLoaded() override;

    void initWindow();
    void initWindow(const IRenderTextureCreateInfo &info);

    void initDefault(const cc::optional<std::string> &uuid) override;

    bool validate() const override;

    // Functions for TS deserialization.
    inline void setWidth(uint32_t width) { _width = width; }
    inline void setHeight(uint32_t height) { _height = height; }

private:
    /*    @serializable
    @rangeMin(1)
    @rangeMax(2048)*/
    uint32_t _width{1};

    /*    @serializable
    @rangeMin(1)
    @rangeMax(2048)*/
    uint32_t _height{1};

    scene::RenderWindow *_window{nullptr};

    CC_DISALLOW_COPY_MOVE_ASSIGN(RenderTexture);
};

} // namespace cc
