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
#include "core/assets/TextureBase.h"
#include "core/ArrayBuffer.h"

namespace cc {

uint32_t getMipLevel (uint32_t width, uint32_t height);
bool isPOT (uint32_t n);
bool canGenerateMipmap (uint32_t w, uint32_t h);

class ImageAsset;

/**
 * @en The simple texture base class.
 * It create the GFX Texture and can set mipmap levels.
 * @zh 简单贴图基类。
 * 简单贴图内部创建了 GFX 贴图和该贴图上的 GFX 贴图视图。
 * 简单贴图允许指定不同的 Mipmap 层级。
 */
class SimpleTexture : public TextureBase {
public:
    /**
     * @en The mipmap level of the texture
     * @zh 贴图中的 Mipmap 层级数量
     */
    uint32_t mipmapLevel ();

    /**
     * @en The GFX Texture resource
     * @zh 获取此贴图底层的 GFX 贴图对象。
     */
    gfx::Texture* getGFXTexture ();

    virtual bool destroy () override;

    /**
     * @en Update the level 0 mipmap image.
     * @zh 更新 0 级 Mipmap。
     */
    void updateImage ();

    /**
     * @en Update the given level mipmap image.
     * @zh 更新指定层级范围内的 Mipmap。当 Mipmap 数据发生了改变时应调用此方法提交更改。
     * 若指定的层级范围超出了实际已有的层级范围，只有覆盖的那些层级范围会被更新。
     * @param firstLevel First level to be updated
     * @param count Mipmap level count to be updated
     */
    virtual void updateMipmaps (uint32_t firstLevel = 0, uint32_t count = 0) = 0;


    /**
     * @en Upload data to the given mipmap level.
     * The size of the image will affect how the mipmap is updated.
     * - When the image is an ArrayBuffer, the size of the image must match the mipmap size.
     * - If the image size matches the mipmap size, the mipmap data will be updated entirely.
     * - If the image size is smaller than the mipmap size, the mipmap will be updated from top left corner.
     * - If the image size is larger, an error will be raised
     * @zh 上传图像数据到指定层级的 Mipmap 中。
     * 图像的尺寸影响 Mipmap 的更新范围：
     * - 当图像是 `ArrayBuffer` 时，图像的尺寸必须和 Mipmap 的尺寸一致；否则，
     * - 若图像的尺寸与 Mipmap 的尺寸相同，上传后整个 Mipmap 的数据将与图像数据一致；
     * - 若图像的尺寸小于指定层级 Mipmap 的尺寸（不管是长或宽），则从贴图左上角开始，图像尺寸范围内的 Mipmap 会被更新；
     * - 若图像的尺寸超出了指定层级 Mipmap 的尺寸（不管是长或宽），都将引起错误。
     * @param source The source image or image data
     * @param level Mipmap level to upload the image to
     * @param arrayIndex The array index
     */
    void uploadData (const ArrayBuffer& source, uint32_t level = 0, uint32_t arrayIndex = 0);

    void _assignImage (ImageAsset* image, uint32_t level, uint32_t arrayIndex);


    void _checkTextureLoaded ();

protected:
    void _textureReady ();

    /**
     * Set mipmap level of this texture.
     * The value is passes as presumed info to `this._getGfxTextureCreateInfo()`.
     * @param value The mipmap level.
     */
    void _setMipmapLevel (uint32_t value);

    /**
     * @en This method is overrided by derived classes to provide GFX texture info.
     * @zh 这个方法被派生类重写以提供 GFX 纹理信息。
     * @param presumed The presumed GFX texture info.
     */
    virtual gfx::TextureInfo _getGfxTextureCreateInfo (gfx::TextureUsageBit usage, gfx::Format format, uint32_t levelCount, gfx::TextureFlagBit flags) = 0;

    void _tryReset ();

    void _createTexture (gfx::Device* device);

    void _tryDestroyTexture ();

protected:
    gfx::Texture* _gfxTexture {nullptr};
private:

    uint32_t _mipmapLevel {1};
    // Cache these data to reduce JSB invoking.
    uint32_t _textureWidth {0};
    uint32_t _textureHeight {0};
};

} // namespace cc {


