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

#include "cocos/base/Any.h"
#include "cocos/base/Variant.h"

namespace cc {

class RequestItem;
class Asset;
class Bundle;
class Pipeline;

struct IXHROptions { //cjh why to inherit from map? } : public Record<std::string, cc::any> {
    std::string                      xhrResponseType;
    bool                             xhrWithCredentials{false};
    uint32_t                         xhrTimeout;
    Record<std::string, std::string> xhrHeader;
    std::string                      xhrMimeType;
};

struct IDownloadParseOptions : public IXHROptions {
    int32_t                                              priority{0};
    int32_t                                              audioLoadMode{0};
    std::function<void(uint32_t loaded, uint32_t total)> onFileProgress{nullptr};
    uint32_t                                             maxConcurrency{0};
    uint32_t                                             maxRequestsPerFrame{0};
    uint32_t                                             maxRetryCount{0};
    bool                                                 cacheEnabled{false};
};

struct INativeAssetOptions : public IDownloadParseOptions {
    std::string preset;
};

struct IBundleOptions : public INativeAssetOptions {
    std::string version;
    bool        scriptAsyncLoading{false};
};

struct IAssetOptions : public INativeAssetOptions {
    bool reloadAsset{false};
    bool cacheAsset{false};
};

struct IJsonAssetOptions : public IAssetOptions {
    std::string assetId;
};

struct IRemoteOptions : public IAssetOptions {
    std::string ext;
};

struct IOptions : public IBundleOptions, IRemoteOptions {
    std::string type; //cjh ?: typeof Asset;
    std::string bundle;
};

struct IRequest : public IOptions {
    std::string uuid;
    std::string url;
    std::string path;
    std::string dir;
    std::string scene;
};

using CompleteCallback       = std::function<void(const Error *err, const cc::any &data)>;
using CompleteCallbackNoData = std::function<void(const Error *err)>;

template <typename T>
using CompleteCallbackWithData = std::function<void(const Error *err, const T &data)>;

using ProgressCallback = std::function<void(uint32_t finished, uint32_t total, RequestItem *item)>;
using Request          = cc::variant<std::string, std::vector<std::string>, IRequest, std::vector<IRequest>>;

//cjh TODO: how to implement constructor in C++?     export type AssetType<T = Asset> = Constructor<T>;
using AssetType = std::function<void()>;

namespace shared {

extern Cache<Asset *>               assets; //cjh EDITOR ? new WeakCache<Asset>() : new Cache<Asset>();
extern Cache<cc::any>              files;
extern Cache<cc::any>              parsed;
extern Cache<Bundle *>              bundles;
extern Pipeline *                   pipeline;          //cjh implement in cpp = new ('normal load', []);
extern Pipeline *                   fetchPipeline;     //cjh = new Pipeline('fetch', []);
extern Pipeline *                   transformPipeline; //cjh = new Pipeline('transform url', []);
extern Cache<std::vector<cc::any>> references;        //cjh = EDITOR ? new Cache<any[]>() : null;

extern const std::string RequestType_UUID;

extern const std::string RequestType_PATH;

extern const std::string RequestType_DIR;

extern const std::string RequestType_URL;

extern const std::string RequestType_SCENE;

extern Record<std::string, Record<std::string, cc::any>> presets;

/**
 * @en
 * The builtin bundle corresponds to 'assets/resources'.
 *
 * @zh
 * 内置 bundle, 对应 'assets/resources' 目录
 *
 */
static const char *BuiltinBundleName_RESOURCES = "resources";
/**
 * @en
 * The builtin bundle
 *
 * @zh
 * 内置 bundle
 *
 */
static const char *BuiltinBundleName_MAIN = "main";

/**
 * @en
 * The builtin bundle, exists when Start Scene asset bundle is checked on the project building panel
 *
 * @zh
 * 内置 bundle, 如果构建面板开启了首场景分包，则会有 START_SCENE bundle
 *
 */
static const char *BuiltinBundleName_START_SCENE = "start-scene";

} // namespace shared

} // namespace cc
