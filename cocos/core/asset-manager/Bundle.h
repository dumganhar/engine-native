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

#include "core/Types.h"
#include "core/asset-manager/AssetManagerConfig.h"

#include <any>
#include <functional>

namespace cc {

/**
 * @en
 * A bundle contains an amount of assets(includes scene), you can load, preload, release asset which is in this bundle
 *
 * @zh
 * 一个包含一定数量资源（包括场景）的包，你可以加载，预加载，释放此包内的资源
 *
 */
class Bundle final {
public:
    /**
     * for internal use
     * @private
     */
    const Config& getConfig()  {
        return _config;
    }

    /**
     * @en
     * The name of this bundle
     *
     * @zh
     * 此 bundle 的名称
     *
     */
    const std::string& getName() {
        return _config.name;
    }

    /**
     * @en
     * The dependency of this bundle
     *
     * @zh
     * 此 bundle 的依赖
     *
     */
    const std::vector<std::string>& getDeps() {
        return _config.deps;
    }

    /**
     * @en
     * The root path of this bundle, such like 'http://example.com/bundle1'
     *
     * @zh
     * 此 bundle 的根路径, 例如 'http://example.com/bundle1'
     *
     */
    const std::string& getBase() {
        return _config.base;
    }

    /**
     * @en
     * Get asset's info using path, only valid when asset is in bundle folder.
     *
     * @zh
     * 使用 path 获取资源的配置信息
     *
     * @param path - The relative path of asset, such as 'images/a'
     * @param type - The constructor of asset, such as  `cc.Texture2D`
     * @returns The asset info
     *
     * @example
     * var info = bundle.getInfoWithPath('image/a', cc.Texture2D);
     *
     */
    IAddressableInfo* getInfoWithPath(const std::string& path, AssetType type) {
        return _config.getInfoWithPath(path, type);
    }

    /**
     * @en
     * Get all asset's info within specific folder
     *
     * @zh
     * 获取在某个指定文件夹下的所有资源信息
     *
     * @param path - The relative path of folder, such as 'images'
     * @param type - The constructor should be used to filter paths
     * @param out - The output array
     * @returns Infos
     *
     * @example
     * var infos = [];
     * bundle.getDirWithPath('images', cc.Texture2D, infos);
     */
    std::vector<IAddressableInfo*> getDirWithPath (const std::string& path, AssetType type) {
        return _config.getDirWithPath(path, type);
    }

    /**
     * @en
     * Get asset's info with uuid
     *
     * @zh
     * 通过 uuid 获取资源信息
     *
     * @method getAssetInfo
     * @param  uuid - The asset's uuid
     * @returns info
     *
     * @example
     * var info = bundle.getAssetInfo('fcmR3XADNLgJ1ByKhqcC5Z');
     *
     */
    IAssetInfo* getAssetInfo (const std::string& uuid) {
        return _config.getAssetInfo(uuid);
    }

    /**
     * @en
     * Get scene'info with name
     *
     * @zh
     * 通过场景名获取场景信息
     *
     * @method getSceneInfo
     * @param name - The name of scene
     * @return info
     *
     * @example
     * var info = bundle.getSceneInfo('first.fire');
     *
     */
    ISceneInfo* getSceneInfo (const std::string& name) {
        return _config.getSceneInfo(name);
    }

    /**
     * @en
     * Initialize this bundle with options
     *
     * @zh
     * 初始化此 bundle
     *
     * @param options
     *
     */
    void init(const IConfigOption& options);

private:
    Config _config;
};

} // namespace cc {
