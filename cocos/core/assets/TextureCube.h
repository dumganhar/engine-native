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

#include "core/assets/Asset.h"
#include "core/assets/SimpleTexture.h"
#include "core/assets/Texture2D.h"

namespace cc {

class ImageAsset;

using ITextureCubeCreateInfo = ITexture2DCreateInfo;

/**
 * @en The texture cube mipmap interface
 * @zh 立方体贴图的 Mipmap 接口。
 */
struct ITextureCubeMipmap {
    ImageAsset *front{nullptr};
    ImageAsset *back{nullptr};
    ImageAsset *left{nullptr};
    ImageAsset *right{nullptr};
    ImageAsset *top{nullptr};
    ImageAsset *bottom{nullptr};
};

/**
 * @en The texture cube asset.
 * Each mipmap level of a texture cube have 6 [[ImageAsset]], represents 6 faces of the cube.
 * @zh 立方体贴图资源。
 * 立方体贴图资源的每个 Mipmap 层级都为 6 张 [[ImageAsset]]，分别代表了立方体贴图的 6 个面。
 */
class TextureCube final : public SimpleTexture {
public:
    /**
     * @en The index for all faces of the cube
     * @zh 立方体每个面的约定索引。
     */
    enum class FaceIndex {
        right  = 0,
        left   = 1,
        top    = 2,
        bottom = 3,
        front  = 4,
        back   = 5,
    };

    /*@serializable*/
    bool isRGBE{false};

    /**
     * @en All levels of mipmap images, be noted, automatically generated mipmaps are not included.
     * When setup mipmap, the size of the texture and pixel format could be modified.
     * @zh 所有层级 Mipmap，注意，这里不包含自动生成的 Mipmap。
     * 当设置 Mipmap 时，贴图的尺寸以及像素格式可能会改变。
     */
    const std::vector<ITextureCubeMipmap> &getMipmaps() const {
        return _mipmaps;
    }

    void setMipmaps(std::vector<ITextureCubeMipmap> &value);

    /**
     * @en Level 0 mipmap image.
     * Be noted, `this.image = img` equals `this.mipmaps = [img]`,
     * sets image will clear all previous mipmaps.
     * @zh 0 级 Mipmap。
     * 注意，`this.image = img` 等价于 `this.mipmaps = [img]`，
     * 也就是说，通过 `this.image` 设置 0 级 Mipmap 时将隐式地清除之前的所有 Mipmap。
     */
    const ITextureCubeMipmap *getImage() const {
        return _mipmaps.empty() ? nullptr : &_mipmaps[0];
    }

    void setImage(const ITextureCubeMipmap *value) {
        _mipmaps.clear();
        _mipmaps.emplace_back(*value);
    }

    /**
     * @en Create a texture cube with an array of [[Texture2D]] which represents 6 faces of the texture cube.
     * @zh 通过二维贴图数组指定每个 Mipmap 的每个面创建立方体贴图。
     * @param textures Texture array, the texture count must be multiple of 6. Every 6 textures are 6 faces of a mipmap level.
     * The order should obey [[FaceIndex]] order.
     * @param out Output texture cube, if not given, will create a new texture cube.
     * @returns The created texture cube.
     * @example
     * ```ts
     * const textures = new Array<Texture2D>(6);
     * textures[TextureCube.FaceIndex.front] = frontImage;
     * textures[TextureCube.FaceIndex.back] = backImage;
     * textures[TextureCube.FaceIndex.left] = leftImage;
     * textures[TextureCube.FaceIndex.right] = rightImage;
     * textures[TextureCube.FaceIndex.top] = topImage;
     * textures[TextureCube.FaceIndex.bottom] = bottomImage;
     * const textureCube = TextureCube.fromTexture2DArray(textures);
     * ```
     */
    static TextureCube *fromTexture2DArray(const std::vector<Texture2D *> &textures);

    /*@serializable*/
    std::vector<ITextureCubeMipmap> _mipmaps;

    void onLoaded() override;

    /**
     * @en Reset the current texture with given size, pixel format and mipmap images.
     * After reset, the gfx resource will become invalid, you must use [[uploadData]] explicitly to upload the new mipmaps to GPU resources.
     * @zh 将当前贴图重置为指定尺寸、像素格式以及指定 mipmap 层级。重置后，贴图的像素数据将变为未定义。
     * mipmap 图像的数据不会自动更新到贴图中，你必须显式调用 [[uploadData]] 来上传贴图数据。
     * @param info The create information
     */
    void reset(const ITextureCubeCreateInfo &info);

    void updateMipmaps(uint32_t firstLevel = 0, uint32_t count = 0) override;

    /**
     * 销毁此贴图，清空所有 Mipmap 并释放占用的 GPU 资源。
     */
    bool destroy() override;

    /**
     * @en Release used GPU resources.
     * @zh 释放占用的 GPU 资源。
     * @deprecated please use [[destroy]] instead
     */
    void releaseTexture();

    std::any _serialize(std::any ctxForExporting) override;
    void     _deserialize(std::any serializedData, std::any handle) override;

    gfx::TextureInfo _getGfxTextureCreateInfo(gfx::TextureUsageBit usage, gfx::Format format, uint32_t levelCount, gfx::TextureFlagBit flags) override;

    void initDefault(const std::string &uuid) override;

    bool validate() const override;
};

} // namespace cc
