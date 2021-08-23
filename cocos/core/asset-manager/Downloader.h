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

#include <any>

#include "core/Types.h"
#include "core/asset-manager/Shared.h"

namespace cc {

using DownloadHandler = std::function<void(const std::string &url, const IDownloadParseOptions &options, const CompleteCallback &onComplete)>;

struct IDownloadRequest {
    std::string           id;
    int32_t               priority{0};
    std::string           url;
    IDownloadParseOptions options;
    CompleteCallback      done{nullptr};
    DownloadHandler       handler{nullptr};
};

/**
 * @en
 * Control all download process, it is a singleton. All member can be accessed with `cc.assetManager.downloader` , it can download several types of files:
 * 1. Text
 * 2. Image
 * 3. Audio
 * 4. Assets
 * 5. Scripts
 *
 * @zh
 * 管理所有下载过程，downloader 是个单例，所有成员能通过 `cc.assetManager.downloader` 访问，它能下载以下几种类型的文件：
 * 1. 文本
 * 2. 图片
 * 3. 音频
 * 4. 资源
 * 5. 脚本
 *
 */
class Downloader final {
public:
    static Downloader *getInstance();
    /**
     * @en
     * The maximum number of concurrent when downloading
     *
     * @zh
     * 下载时的最大并发数
     */
    uint32_t maxConcurrency{6};

    /**
     * @en
     * The maximum number of request can be launched per frame when downloading
     *
     * @zh
     * 下载时每帧可以启动的最大请求数
     *
     */
    uint32_t maxRequestsPerFrame{6};

    /**
     * @en
     * The address of remote server
     *
     * @zh
     * 远程服务器地址
     *
     */
    const std::string &getRemoteServerAddress() const {
        return _remoteServerAddress;
    }

    /**
     * @en
     * The max number of retries when fail
     *
     * @zh
     * 失败重试次数
     *
     * @property maxRetryCount
     * @type {Number}
     */
    uint32_t maxRetryCount{3}; //cjh = BUILD ? 3 : 0;

    bool appendTimeStamp{false}; //cjh = !!EDITOR;

    bool limited{true}; //cjh !EDITOR;

    /**
     * @en
     * Wait for while before another retry, unit: ms
     *
     * @zh
     * 重试的间隔时间
     *
     */
    uint32_t retryInterval{2000};

    Record<std::string, std::string> bundleVers;

    std::vector<std::string> remoteBundles;

private:
    Record<std::string, DownloadHandler> _downloaders;

    Cache<std::vector<CompleteCallback>> _downloading;
    std::vector<IDownloadRequest>        _queue;
    bool                                 _queueDirty{false};
    // the number of loading thread
    uint32_t _totalNum{0};
    // the number of request that launched in this period
    uint32_t _totalNumThisPeriod{0};
    // last time, if now - lastTime > period, refresh _totalNumThisPeriod.
    int64_t _lastDate{-1};
    // if _totalNumThisPeriod equals max, move request to next period using setTimeOut.
    bool        _checkNextPeriod{false};
    std::string _remoteServerAddress;
    float       _maxInterval{1.0f / 30.0f};
};

} // namespace cc
