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

#include <optional>
#include "core/ArrayBuffer.h"
#include "gfx-base/GFXTexture.h"
#include "renderer/gfx-base/GFXDef.h"
#include "renderer/gfx-base/GFXDevice.h"

namespace cc {
struct ITextureBuffer {
    gfx::Texture *texture{nullptr};
    uint32_t      size{0};
    uint32_t      start{0};
    uint32_t      end{0};
};

struct ITextureBufferHandle {
    index_t  chunkIndex{0};
    uint32_t size{0};
    uint32_t start{0};
    uint32_t end{0};
};
struct ITextureBufferPoolInfo {
    gfx::Format         format{gfx::Format::UNKNOWN};
    std::optional<bool> inOrderFree{std::nullopt};
};

class TextureBufferPool {
public:
    TextureBufferPool()  = default;
    ~TextureBufferPool() = default;

    void initialize(const ITextureBufferPoolInfo &info);
    void destroy();
    void alloc(uint32_t size, std::optional<index_t> chunkIdx);
    void free(const ITextureBufferHandle &handle);
    void createChunk(uint32_t length);
    void update(const ITextureBufferHandle &handle, const ArrayBuffer &buffer);

private:
    void findAvailableSpace(uint32_t size, index_t chunkIdx) const;

    // [McDonald 12] Efficient Buffer Management
    ITextureBufferHandle mcDonaldAlloc(uint32_t size);

    gfx::Device *                     _device{nullptr};
    gfx::Format                       _format{gfx::Format::UNKNOWN};
    uint32_t                          _formatSize{0};
    std::vector<ITextureBuffer>       _chunks;
    uint32_t                          _chunkCount{0};
    std::vector<ITextureBufferHandle> _handles;
    gfx::BufferTextureCopy            _region0;
    gfx::BufferTextureCopy            _region1;
    gfx::BufferTextureCopy            _region2;
    // private _roundUpFn: ((targetSize: number, formatSize: number) => number) | null = null; // TODO(xwx)
    // private _bufferViewCtor: TypedArrayConstructor = Uint8Array; // TODO(xwx)
    uint32_t _channels{4};
    uint32_t _alignment{1};

    CC_DISALLOW_COPY_MOVE_ASSIGN(TextureBufferPool);
};
} // namespace cc