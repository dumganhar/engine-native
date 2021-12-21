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
#include "core/asset-manager/Shared.h"

namespace cc {

struct IUnpackRequest {
    CompleteCallback onComplete{nullptr};
    std::string      id;
};

using Unpacker = std::function<void(const std::string &packUuid, const cc::any &data, const IDownloadParseOptions &options, const CompleteCallback &onComplete)>;

/**
 * @en
 * Handle the packed asset, include unpacking, loading, cache and so on. It is a singleton. All member can be accessed with `cc.assetManager.packManager`
 *
 * @zh
 * 处理打包资源，包括拆包，加载，缓存等等，这是一个单例, 所有成员能通过 `cc.assetManager.packManager` 访问
 *
 */
class PackManager {
public:
    static PackManager *getInstance();

    /**
     * @en
     * Unpack the json, revert to what it was before packing
     *
     * @zh
     * 拆解 json 包，恢复为打包之前的内容
     *
     * @param pack - The pack
     * @param json - The content of pack
     * @param options - Some optional parameters
     * @param onComplete - Callback when finish unpacking
     * @param onComplete.err - The occurred error, null indicates success
     * @param onComplete.content - The unpacked assets
     *
     * @example
     * downloader.downloadFile('pack.json', { xhrResponseType: 'json'}, null, (err, file) => {
     *      packManager.unpackJson(['a', 'b'], file, null, (err, data) => console.log(err));
     * });
     *
     */
    void unpackJson(const std::vector<std::string> &pack,
                    const cc::any &                json,
                    const IDownloadParseOptions &   options,
                    const CompleteCallback &        onComplete);

    void init();

    /**
     * @en
     * Register custom handler if you want to change default behavior or extend packManager to unpack other format pack
     *
     * @zh
     * 当你想修改默认行为或者拓展 packManager 来拆分其他格式的包时可以注册自定义的 handler
     *
     * @param type - Extension likes '.bin' or map likes {'.bin': binHandler, '.ab': abHandler}
     * @param handler - handler
     * @param handler.packUuid - The uuid of pack
     * @param handler.data - The content of pack
     * @param handler.options - Some optional parameters
     * @param handler.onComplete - Callback when finishing unpacking
     *
     * @example
     * packManager.register('.bin', (packUuid, file, options, onComplete) => onComplete(null, null));
     * packManager.register({
     *  '.bin': (packUuid, file, options, onComplete) => onComplete(null, null),
     *  '.ab': (packUuid, file, options, onComplete) => onComplete(null, null),
     * });
     */
    void registerCustomHandlerWithType(const std::string &type, const Unpacker &handler);
    void registerCustomHandlerWithMap(const Record<std::string, Unpacker> &map);

    /**
     * @en
     * Use corresponding handler to unpack package
     *
     * @zh
     * 用对应的 handler 来进行解包
     *
     * @method unpack
     * @param pack - The uuid of packed assets
     * @param data - The packed data
     * @param type - The type indicates that which handler should be used to download, such as '.jpg'
     * @param options - Some optional parameter
     * @param onComplete - callback when finishing unpacking
     * @param onComplete.err -  The occurred error, null indicates success
     * @param onComplete.data - Original assets
     *
     * @example
     * downloader.downloadFile('pack.json', {xhrResponseType: 'json'}, null, (err, file) => {
     *      packManager.unpack(['2fawq123d', '1zsweq23f'], file, '.json', null, (err, data) => console.log(err));
     * });
     *
     */
    void unpack(const std::vector<std::string> &pack,
                const cc::any &                data,
                const std::string &             type,
                const IDownloadParseOptions &   options,
                const CompleteCallback &        onComplete);

    /**
     * @en
     * Download request item, If item is not in any package, download as usual. Otherwise, download the corresponding package and unpack it.
     * And then retrieve the corresponding content form it.
     *
     * @zh
     * 下载请求对象，如果请求对象不在任何包内，则正常下载，否则下载对应的 package 并进行拆解，并取回包内对应的内容
     *
     * @param item - Some item you want to download
     * @param options - Some optional parameters
     * @param onComplete - Callback when finished
     * @param onComplete.err - The occurred error, null indicates success
     * @param onComplete.data - The unpacked data retrieved from package
     *
     * @example
     * var requestItem = cc.AssetManager.RequestItem.create();
     * requestItem.uuid = 'fcmR3XADNLgJ1ByKhqcC5Z';
     * requestItem.info = config.getAssetInfo('fcmR3XADNLgJ1ByKhqcC5Z');
     * packManager.load(requestItem, null, (err, data) => console.log(err));
     *
     */
    void load(const RequestItem &item, const IDownloadParseOptions &options, const CompleteCallback &onComplete);

private:
    Cache<std::vector<IUnpackRequest>> _loading;
    Record<std::string, Unpacker>      _unpackers;
};

} // namespace cc
