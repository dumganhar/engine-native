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
#include "base/TypeDef.h"
#include "core/assets/Asset.h"

namespace cc {

namespace gfx {
class Device;
}

class Material;

class BuiltinResMgr final {
public:
    static BuiltinResMgr *getInstance();

    explicit BuiltinResMgr() = default;
    ~BuiltinResMgr()         = default;

    bool initBuiltinRes(gfx::Device *device);

    template <typename T, typename Enabled = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    T *get(const std::string &uuid) {
        if (auto iter = _resources.find(uuid); iter != _resources.end()) {
            return static_cast<T *>(iter->second);
        }

        return nullptr;
    }

    void tryCompileAllPasses();

private:
    void initMaterials();
    void initTexture2DWithUuid(const std::string &uuid, const uint8_t *data, size_t dataBytes, uint32_t width, uint32_t height, uint32_t bytesPerPixel);
    void initTextureCubeWithUuid(const std::string &uuid, const uint8_t *data, size_t dataBytes, uint32_t width, uint32_t height, uint32_t bytesPerPixel);

private:
    gfx::Device *                _device{nullptr};
    Record<std::string, Asset *> _resources;
    std::vector<Material *>      _materialsToBeCompiled;

    CC_DISALLOW_COPY_MOVE_ASSIGN(BuiltinResMgr);
};

} // namespace cc