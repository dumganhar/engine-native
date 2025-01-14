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
#include "core/asset-manager/Task.h"

namespace cc {

class Config;

void setDefaultProgressCallback(const ProgressCallback &onProgress);

void clear(const Task &task, bool clearRef);

std::string urlAppendTimestamp(const std::string &url, bool append);

using RetryFunction = std::function<void(uint32_t times, const CompleteCallback &done)>;

void retry(const RetryFunction &process, uint32_t times, uint32_t wait, const CompleteCallback &onComplete, uint32_t index = 0);

void getDepends(const std::string &uuid, Asset *data, const Record<std::string, cc::any> &exclude, std::vector<Record<std::string, cc::any>> &depends, Config *config);
void getDepends(const std::string &uuid, const Record<std::string, cc::any> &data, const Record<std::string, cc::any> &exclude, std::vector<Record<std::string, cc::any>> &depends, Config *config);

void cache(const std::string &id, Asset *asset, bool cacheAsset = false);

void setProperties(const std::string &uuid, Asset *asset, const Record<std::string, cc::any> &assetsMap);

void gatherAsset(Task &task);

template <typename T>
using ForEachFunction = std::function<void(T item, const CompleteCallbackNoData &done)>;

template <typename T>
void forEach(const std::vector<T> array, const ForEachFunction<T> &process, const std::function<void(const std::vector<Error *> &errs)> &onComplete);

template <typename T>
struct IParameters {
    IOptions         options;
    ProgressCallback onProgress{nullptr};
    T                onComplete{nullptr};
};

template <typename T>
struct ILoadResArgs {
    AssetType        type{nullptr};
    ProgressCallback onProgress{nullptr};
    T                onComplete{nullptr};
};

template <typename T>
IParameters<T> parseParameters(const cc::variant<IOptions, ProgressCallback, T> &options,
                               const cc::variant<ProgressCallback, T> &          onProgress,
                               const T &                                          onComplete);

template <typename T>
ILoadResArgs<T> parseLoadResArgs(const cc::variant<AssetType, ProgressCallback, T> &type,
                                 const cc::variant<ProgressCallback, T> &           onProgress,
                                 const T &                                           onComplete);

bool checkCircleReference(const std::string &owner, const std::string &uuid, const Record<std::string, cc::any> &map, const Record<std::string, bool> &checked = {});

using AsyncifyFunction = std::function<void(const cc::any &p1, const cc::any &p2)>;
AsyncifyFunction asyncify(const AsyncifyFunction &cb);

} // namespace cc
