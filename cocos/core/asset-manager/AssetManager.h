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
#include "core/asset-manager/Cache.h"
#include "core/asset-manager/DependUtil.h"
#include "core/asset-manager/Shared.h"
#include "core/asset-manager/Pipeline.h"

namespace cc {

/**
 * @zh
 * AssetManager 配置。
 * @en
 * AssetManager configuration.
 */
struct IAssetManagerOptions final {
    /* Only valid on Editor */
    std::string importBase;
    /* Only valid on Editor */
    std::string nativeBase;
    /* Only valid on native */
    uint32_t jsbDownloaderMaxTasks;
    /* Only valid on native */
    uint32_t jsbDownloaderTimeout;

    /**
     * @zh
     * 所有 bundle 的版本信息
     * @en
     * Version for all bundles
     */
    Record<std::string, std::string> bundleVers;

    /**
     * @zh
     * 远程服务器地址
     * @en
     * Remote server address
     */
    std::string server;

    /**
     * @zh
     * 配置为子包的 bundle
     * @en
     * All subpackages
     */
    std::vector<std::string> subpackages;

    /**
     * @zh
     * 配置为远程包的 bundle
     * @en
     * All remote bundles
     */
    std::vector<std::string> remoteBundles;

};

class Pipeline;
class Bundle;
class Asset;
class Downloader;
class PackManager;
class CacheManager;
/**
 * @en
 * This module controls asset's behaviors and information, include loading, releasing etc. it is a singleton
 * All member can be accessed with `cc.assetManager`.
 *
 * @zh
 * 此模块管理资源的行为和信息，包括加载，释放等，这是一个单例，所有成员能够通过 `cc.assetManager` 调用
 *
 */
class AssetManager final {
public:
    static AssetManager* getInstance();

    /**
     * @en
     * Normal loading pipeline
     *
     * @zh
     * 正常加载管线
     *
     */
    Pipeline* pipeline{nullptr};

    /**
     * @en
     * Fetching pipeline
     *
     * @zh
     * 下载管线
     *
     */
    Pipeline* fetchPipeline{nullptr};

    /**
     * @en
     * Url transformer
     *
     * @zh
     * Url 转换器
     *
     */
    Pipeline* transformPipeline{nullptr};

    /**
     * @en
     * The collection of bundle which is already loaded, you can remove cache with {{#crossLink "AssetManager/removeBundle:method"}}{{/crossLink}}
     *
     * @zh
     * 已加载 bundle 的集合， 你能通过 {{#crossLink "AssetManager/removeBundle:method"}}{{/crossLink}} 来移除缓存
     *
     */
    Cache<Bundle*> bundles;

    /**
     * @en
     * The collection of asset which is already loaded, you can remove cache with {{#crossLink "AssetManager/releaseAsset:method"}}{{/crossLink}}
     *
     * @zh
     * 已加载资源的集合， 你能通过 {{#crossLink "AssetManager/releaseAsset:method"}}{{/crossLink}} 来移除缓存
     */
    Cache<Asset> assets;

    std::string generalImportBase;
    std::string generalNativeBase;

    /**
     * @en
     * Manage relationship between asset and its dependencies
     *
     * @zh
     * 管理资源依赖关系
     */
    DependUtil* dependUtil{nullptr};

    /**
     * @en
     * Whether or not load asset forcibly, if it is true, asset will be loaded regardless of error
     *
     * @zh
     * 是否强制加载资源, 如果为 true ，加载资源将会忽略报错
     *
     */
    bool force = false;//cjh EDITOR || PREVIEW;

    /**
     * @en
     * Whether to use image bitmap to load image first. If enabled, images loading will become faster but memory usage will increase.
     *
     * @zh
     * 是否优先使用 image bitmap 来加载图片，启用之后，图片加载速度会更快, 但内存占用会变高，
     *
     */
    bool allowImageBitmap = false;//cjh !sys.isMobile;

    /**
     * @en
     * Some useful function
     *
     * @zh
     * 一些有用的方法
     *
     */
//cjh    public utils = helper;

    /**
     * @en
     * Manage all downloading task
     *
     * @zh
     * 管理所有下载任务
     *
     */
    Downloader* downloader{nullptr};

    /**
     * @en
     * Manage all parsing task
     *
     * @zh
     * 管理所有解析任务
     *
     */
    Downloader* parser{nullptr};

    /**
     * @en
     * Manage all packed asset
     *
     * @zh
     * 管理所有合并后的资源
     *
     */
    PackManager* packManager{nullptr};

    /**
     * @en
     * Whether or not cache the loaded asset
     *
     * @zh
     * 是否缓存已加载的资源
     *
     */
    bool cacheAsset{true};

    /**
     * @en
     * Cache manager is a module which controls all caches downloaded from server in non-web platform.
     *
     * @zh
     * 缓存管理器是一个模块，在非 WEB 平台上，用于管理所有从服务器上下载下来的缓存
     *
     */
    CacheManager* cacheManager{nullptr};

    /**
     * @en
     * The preset of options
     *
     * @zh
     * 可选参数的预设集
     *
     */
//cjh    public presets = presets;
//
//    public factory = factory;

    IPipe preprocessPipe;

    IPipe fetchPipe;

    IPipe loadPipe;

//cjh    public references = references;
//
//    private _releaseManager = releaseManager;

//    private _files = files;

//    private _parsed = parsed;
//    private _parsePipeline = BUILD ? null : new Pipeline('parse existing json', [this.loadPipe]);

    /**
     * @en
     * The builtin 'main' bundle
     *
     * @zh
     * 内置 main 包
     */
    Bundle* getMain();

    /**
     * @en
     * The builtin 'resources' bundle
     *
     * @zh
     * 内置 resources 包
     *
     */
    Bundle* getResources();

    /**
     * @en
     * Initialize assetManager with options
     *
     * @zh
     * 初始化资源管理器
     *
     * @param options - the configuration
     *
     */
    void init(const IAssetManagerOptions& options);

    /**
     * @en
     * Get the bundle which has been loaded
     *
     * @zh
     * 获取已加载的分包
     *
     * @param name - The name of bundle
     * @return - The loaded bundle
     *
     * @example
     * // ${project}/assets/test1
     * cc.assetManager.getBundle('test1');
     *
     * cc.assetManager.getBundle('resources');
     *
     */
    Bundle* getBundle(const std::string& name);

    /**
     * @en
     * Remove this bundle. NOTE: The asset within this bundle will not be released automatically,
     * you can call {{#crossLink "Bundle/releaseAll:method"}}{{/crossLink}} manually before remove it if you need
     *
     * @zh
     * 移除此包, 注意：这个包内的资源不会自动释放, 如果需要的话你可以在摧毁之前手动调用 {{#crossLink "Bundle/releaseAll:method"}}{{/crossLink}} 进行释放
     *
     * @param bundle - The bundle to be removed
     *
     * @typescript
     * removeBundle(bundle: cc.AssetManager.Bundle): void
     */
    void removeBundle(Bundle* bundle);

    /**
     * @en
     * General interface used to load assets with a progression callback and a complete callback. You can achieve almost all
     * effect you want with combination of `requests` and `options`.It is highly recommended that you use more simple API,
     * such as `load`, `loadDir` etc. Every custom parameter in `options` will be distribute to each of `requests`. if request
     * already has same one, the parameter in request will be given priority. Besides, if request has dependencies, `options`
     * will distribute to dependencies too. Every custom parameter in `requests` will be transferred to handler of `downloader`
     * and `parser` as `options`. You can register you own handler downloader or parser to collect these custom parameters for some effect.
     *
     * Reserved Keyword: `uuid`, `url`, `path`, `dir`, `scene`, `type`, `priority`, `preset`, `audioLoadMode`, `ext`,
     * `bundle`, `onFileProgress`, `maxConcurrency`, `maxRequestsPerFrame`, `maxRetryCount`, `version`, `xhrResponseType`,
     * `xhrWithCredentials`, `xhrMimeType`, `xhrTimeout`, `xhrHeader`, `reloadAsset`, `cacheAsset`, `cacheEnabled`,
     * Please DO NOT use these words as custom options!
     *
     * @zh
     * 通用加载资源接口，可传入进度回调以及完成回调，通过组合 `request` 和 `options` 参数，几乎可以实现和扩展所有想要的加载效果。非常建议
     * 你使用更简单的API，例如 `load`、`loadDir` 等。`options` 中的自定义参数将会分发到 `requests` 的每一项中，如果request中已存在同名的
     * 参数则以 `requests` 中为准，同时如果有其他依赖资源，则 `options` 中的参数会继续向依赖项中分发。request中的自定义参数都会以 `options`
     * 形式传入加载流程中的 `downloader`, `parser` 的方法中, 你可以扩展 `downloader`, `parser` 收集参数完成想实现的效果。
     *
     * 保留关键字: `uuid`, `url`, `path`, `dir`, `scene`, `type`, `priority`, `preset`, `audioLoadMode`, `ext`, `bundle`, `onFileProgress`,
     *  `maxConcurrency`, `maxRequestsPerFrame`, `maxRetryCount`, `version`, `xhrResponseType`, `xhrWithCredentials`, `xhrMimeType`, `xhrTimeout`, `xhrHeader`,
     *  `reloadAsset`, `cacheAsset`, `cacheEnabled`, 请不要使用这些字段为自定义参数!
     *
     * @param requests - The request you want to load
     * @param options - Optional parameters
     * @param onProgress - Callback invoked when progression change
     * @param onProgress.finished - The number of the items that are already completed
     * @param onProgress.total - The total number of the items
     * @param onProgress.item - The current request item
     * @param onComplete - Callback invoked when finish loading
     * @param onComplete.err - The error occurred in loading process.
     * @param onComplete.data - The loaded content
     *
     * @example
     * cc.assetManager.loadAny({url: 'http://example.com/a.png'}, (err, img) => cc.log(img));
     * cc.assetManager.loadAny(['60sVXiTH1D/6Aft4MRt9VC'], (err, assets) => cc.log(assets));
     * cc.assetManager.loadAny([{ uuid: '0cbZa5Y71CTZAccaIFluuZ'}, {url: 'http://example.com/a.png'}], (err, assets) => cc.log(assets));
     * cc.assetManager.downloader.register('.asset', (url, options, onComplete) => {
     *      url += '?userName=' + options.userName + "&password=" + options.password;
     *      cc.assetManager.downloader.downloadFile(url, null, onComplete);
     * });
     * cc.assetManager.parser.register('.asset', (file, options, onComplete) => {
     *      var json = JSON.parse(file);
     *      var skin = json[options.skin];
     *      var model = json[options.model];
     *      onComplete(null, {skin, model});
     * });
     * cc.assetManager.loadAny({ url: 'http://example.com/my.asset', skin: 'xxx', model: 'xxx', userName: 'xxx', password: 'xxx' });
     *
     */
    void loadAny(const Request& requests, const IOptions& options, const ProgressCallback& onProgress, const CompleteCallbackWithData<std::any>& onComplete);
    void loadAny(const Request& requests, const IOptions& options, const CompleteCallbackWithData<std::any>& onComplete);
    void loadAny(const Request& requests, const ProgressCallback& onProgress, const CompleteCallbackWithData<std::any>& onComplete);
    void loadAny(const Request& requests, const CompleteCallbackWithData<std::any>& onComplete);

    template <typename T, typename Enable = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    void loadAny(const std::string& request, const CompleteCallbackWithData<T>& onComplete);

    template <typename T, typename Enable = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    void loadAny(const std::vector<std::string>& requests, const CompleteCallbackWithData<T>& onComplete);


    /**
     * @en
     * General interface used to preload assets with a progression callback and a complete callback.It is highly recommended that you use
     * more simple API, such as `preloadRes`, `preloadResDir` etc. Everything about preload is just likes `cc.assetManager.loadAny`, the
     * difference is `cc.assetManager.preloadAny` will only download asset but not parse asset. You need to invoke `cc.assetManager.loadAny(preloadTask)`
     * to finish loading asset
     *
     * @zh
     * 通用预加载资源接口，可传入进度回调以及完成回调，非常建议你使用更简单的 API ，例如 `preloadRes`, `preloadResDir` 等。`preloadAny` 和 `loadAny`
     * 几乎一样，区别在于 `preloadAny` 只会下载资源，不会去解析资源，你需要调用 `cc.assetManager.loadAny(preloadTask)` 来完成资源加载。
     *
     * @param requests - The request you want to preload
     * @param options - Optional parameters
     * @param onProgress - Callback invoked when progression change
     * @param onProgress.finished - The number of the items that are already completed
     * @param onProgress.total - The total number of the items
     * @param onProgress.item - The current request item
     * @param onComplete - Callback invoked when finish preloading
     * @param onComplete.err - The error occurred in preloading process.
     * @param onComplete.items - The preloaded content
     *
     * @example
     * cc.assetManager.preloadAny('0cbZa5Y71CTZAccaIFluuZ', (err) => cc.assetManager.loadAny('0cbZa5Y71CTZAccaIFluuZ'));
     *
     */
    void preloadAny(const Request& requests, const IOptions& options, const ProgressCallback& onProgress, const CompleteCallbackWithData<std::vector<RequestItem>>& onComplete);
    void preloadAny(const Request& requests, const ProgressCallback& onProgress, const CompleteCallbackWithData<std::vector<RequestItem>>& onComplete);

    void preloadAny(const Request& requests, const IOptions& options, const CompleteCallbackWithData<std::vector<RequestItem>>& onComplete);
    void preloadAny(const Request& requests, const CompleteCallbackWithData<std::vector<RequestItem>>& onComplete);

    /**
     * @en
     * Load remote asset with url, such as audio, image, text and so on.
     *
     * @zh
     * 使用 url 加载远程资源，例如音频，图片，文本等等。
     *
     * @param url - The url of asset
     * @param options - Some optional parameters
     * @param options.audioLoadMode - Indicate which mode audio you want to load
     * @param options.ext - If the url does not have a extension name, you can specify one manually.
     * @param onComplete - Callback invoked when finish loading
     * @param onComplete.err - The error occurred in loading process.
     * @param onComplete.asset - The loaded texture
     *
     * @example
     * cc.assetManager.loadRemote('http://www.cloud.com/test1.jpg', (err, texture) => console.log(err));
     * cc.assetManager.loadRemote('http://www.cloud.com/test2.mp3', (err, audioClip) => console.log(err));
     * cc.assetManager.loadRemote('http://www.cloud.com/test3', { ext: '.png' }, (err, texture) => console.log(err));
     *
     */
    template <typename T, typename Enable = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    void loadRemote(const std::string& url, const IRemoteOptions& options, const CompleteCallbackWithData<T>& onComplete);

    template <typename T, typename Enable = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    void loadRemote(const std::string& url, const CompleteCallbackWithData<T>& onComplete);

    /**
     * @en
     * load bundle
     *
     * @zh
     * 加载资源包
     *
     * @param nameOrUrl - The name or root path of bundle
     * @param options - Some optional paramter, same like downloader.downloadFile
     * @param options.version - The version of this bundle, you can check config.json in this bundle
     * @param onComplete - Callback when bundle loaded or failed
     * @param onComplete.err - The occurred error, null indicates success
     * @param onComplete.bundle - The loaded bundle
     *
     * @example
     * loadBundle('http://localhost:8080/test', null, (err, bundle) => console.log(err));
     *
     */
    void loadBundle(const std::string& nameOrUrl, const IBundleOptions& options, const CompleteCallbackWithData<Bundle>& onComplete);
    void loadBundle(const std::string& nameOrUrl, const CompleteCallbackWithData<Bundle>& onComplete);

    /**
     * @en
     * Release asset and it's dependencies.
     * This method will not only remove the cache of the asset in assetManager, but also clean up its content.
     * For example, if you release a texture, the texture asset and its gl texture data will be freed up.
     * Notice, this method may cause the texture to be unusable, if there are still other nodes use the same texture,
     * they may turn to black and report gl errors.
     *
     * @zh
     * 释放资源以及其依赖资源, 这个方法不仅会从 assetManager 中删除资源的缓存引用，还会清理它的资源内容。
     * 比如说，当你释放一个 texture 资源，这个 texture 和它的 gl 贴图数据都会被释放。
     * 注意，这个函数可能会导致资源贴图或资源所依赖的贴图不可用，如果场景中存在节点仍然依赖同样的贴图，它们可能会变黑并报 GL 错误。
     *
     * @param asset - The asset to be released
     *
     * @example
     * // release a texture which is no longer need
     * cc.assetManager.releaseAsset(texture);
     *
     */
    void releaseAsset(Asset* asset);

    /**
     * @en
     * Release all unused assets. Refer to {{#crossLink "AssetManager/releaseAsset:method"}}{{/crossLink}} for detailed information.
     *
     * @zh
     * 释放所有没有用到的资源。详细信息请参考 {{#crossLink "AssetManager/releaseAsset:method"}}{{/crossLink}}
     *
     * @hidden
     *
     */
    void releaseUnusedAssets();

    /**
     * @en
     * Release all assets. Refer to {{#crossLink "AssetManager/releaseAsset:method"}}{{/crossLink}} for detailed information.
     *
     * @zh
     * 释放所有资源。详细信息请参考 {{#crossLink "AssetManager/releaseAsset:method"}}{{/crossLink}}
     *
     */
    void releaseAll();

private:
    /**
     * For internal usage.
     * @param json
     * @param options
     * @param onComplete
     * @private
     */
    template <typename T, typename Enable = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    void loadWithJson(const Record<std::string, std::any>& json, //cjh TODO: use Rapidjson Value?
                      const IJsonAssetOptions& options,
                      const ProgressCallback& onProgress,
                      const CompleteCallbackWithData<T>& onComplete);

    template <typename T, typename Enable = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    void loadWithJson(const Record<std::string, std::any>& json,
                      const ProgressCallback& onProgress,
                      const CompleteCallbackWithData<T>& onComplete);

    template <typename T, typename Enable = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    void loadWithJson(const Record<std::string, std::any>& json,
                      const IJsonAssetOptions& options,
                      const CompleteCallbackWithData<T>& onComplete);

    template <typename T, typename Enable = std::enable_if_t<std::is_base_of<Asset, T>::value>>
    void loadWithJson(const Record<std::string, std::any>& json, const CompleteCallbackWithData<T>& onComplete);
};

} // namespace cc {
