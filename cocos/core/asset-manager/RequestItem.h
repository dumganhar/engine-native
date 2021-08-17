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

#include "core/asset-manager/AssetManagerConfig.h"

namespace cc {

/**
 * @en
 * A collection of information about a request
 *
 * @zh
 * 请求的相关信息集合
 *
 */
class RequestItem final {
public:
    /**
     * @en
     * The id of request, combined from uuid and isNative
     *
     * @zh
     * 请求的 id, 由 uuid 和 isNative 组合而成
     */
    std::string getId () const;

    static const uint32_t MAX_DEAD_NUM = 500;

    /**
     * @en
     * Create a new request item from pool
     *
     * @zh
     * 从对象池中创建 requestItem
     *
     * @returns requestItem
     *
     */
    static RequestItem* create ();

    static std::vector<RequestItem*> s_deadPool;

    /**
     * @en
     * The uuid of request
     *
     * @zh
     * 请求资源的uuid
     *
     */
    std::string uuid;

    /**
     * @en
     * The final url of request
     *
     * @zh
     * 请求的最终url
     *
     */
    std::string url;

    /**
     * @en
     * The extension name of asset
     *
     * @zh
     * 资源的扩展名
     *
     */
    std::string ext { ".json" };

    /**
     * @en
     * The content of asset
     *
     * @zh
     * 资源的内容
     *
     */
    std::any content;

    /**
     * @en
     * The file of asset
     *
     * @zh
     * 资源的文件
     *
     */
    std::any file;

    /**
     * @en
     * The information of asset
     *
     * @zh
     * 资源的相关信息
     *
     */
    IAssetInfo info;

    Config config;

    /**
     * @en
     * Whether or not it is native asset
     *
     * @zh
     * 资源是否是原生资源
     *
     */
    bool isNative {false};

    /**
     * @en
     * Custom options
     *
     * @zh
     * 自定义参数
     *
     */
    Record<std::string, std::any> options;

    /**
     * @en
     * Recycle this for reuse
     *
     * @zh
     * 回收 requestItem 用于复用
     *
     */
    void recycle();

private:
    std::string _id;
};

} // namespace cc {
