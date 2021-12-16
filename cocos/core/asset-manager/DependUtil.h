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

#include "cocos/base/Any.h"

#include "core/Types.h"
#include "core/asset-manager/Cache.h"

namespace cc {

struct IDependencies {
    Record<std::string, cc::any> nativeDep;
    std::vector<std::string>      deps;
    bool                          parsedFromExistAsset{false};
    std::vector<std::string>      persistDeps;
};

class Asset;

/**
 * @en
 * Control asset's dependency list, it is a singleton. All member can be accessed with `cc.assetManager.dependUtil`
 *
 * @zh
 * 控制资源的依赖列表，这是一个单例, 所有成员能通过 `cc.assetManager.dependUtil` 访问
 *
 */
class DependUtil final {
public:
    static DependUtil *getInstance();

    Cache<IDependencies> _depends;

    void init();

    /**
     * @en
     * Get asset's native dependency. For example, Texture's native dependency is image.
     *
     * @zh
     * 获取资源的原生依赖，例如 Texture 的原生依赖是图片
     *
     * @param uuid - asset's uuid
     * @returns native dependency
     *
     * @example
     * var dep = dependUtil.getNativeDep('fcmR3XADNLgJ1ByKhqcC5Z');
     */
    Record<std::string, cc::any> getNativeDep(const std::string &uuid);

    /**
     * @en
     * Get asset's direct referencing non-native dependency list. For example, Material's non-native dependencies are Texture.
     *
     * @zh
     * 获取资源直接引用的非原生依赖列表，例如，材质的非原生依赖是 Texture
     *
     * @param uuid - asset's uuid
     * @returns direct referencing non-native dependency list
     *
     * @example
     * var deps = dependUtil.getDeps('fcmR3XADNLgJ1ByKhqcC5Z');
     *
     */
    std::vector<std::string> getDeps(const std::string &uuid);

    /**
     * @en
     * Get non-native dependency list of the loaded asset, include indirect reference.
     * The returned array stores the dependencies with their uuid, after retrieve dependencies,
     *
     * @zh
     * 获取某个已经加载好的资源的所有非原生依赖资源列表，包括间接引用的资源，并保存在数组中返回。
     * 返回的数组将仅保存依赖资源的 uuid。
     *
     * @param uuid - The asset's uuid
     * @returns non-native dependency list
     *
     * @example
     * var deps = dependUtil.getDepsRecursively('fcmR3XADNLgJ1ByKhqcC5Z');
     *
     */
    std::vector<std::string> getDepsRecursively(const std::string &uuid);

    void remove(const std::string &uuid);

    /**
     * @en
     * Extract dependency list from serialized data or asset and then store in cache.
     *
     * @zh
     * 从序列化数据或资源中提取出依赖列表，并且存储在缓存中。
     *
     * @param uuid - The uuid of serialized data or asset
     * @param json - Serialized data or asset
     * @returns dependency list, include non-native and native dependency
     *
     * @example
     * downloader.downloadFile('test.json', { xhrResponseType: 'json'}, null, (err, file) => {
     *     var dependencies = parse('fcmR3XADNLgJ1ByKhqcC5Z', file);
     * });
     *
     */
    IDependencies *parse(const std::string &uuid, const cc::any &json);

private:
    IDependencies parseDepsFromAsset(const Asset *asset);

    std::vector<std::string> parseDepsFromJson(const std::vector<cc::any> &json);

    void descend(const std::string &uuid, const Record<std::string, cc::any> &exclude, const std::vector<std::string> &depends);
};

} // namespace cc
