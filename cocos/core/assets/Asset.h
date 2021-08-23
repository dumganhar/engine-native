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
#include <functional>

#include "base/Value.h"
#include "core/Types.h"
#include "core/data/Object.h"

#include <any>
#include <functional>

namespace cc {

class Node;

class Asset : public CCObject {
public:
    virtual ~Asset() = default;

    const std::string& getNativeUrl() const;

    using NativeDep = std::unordered_map<std::string, Value>;
    NativeDep getNativeDep() const;

    /**
     * @param error - null or the error info
     * @param node - the created node or null
     */
    using CreateNodeCallback = std::function<void(Error, Node*)>;
    /**
     * @en
     * Create a new node using this asset in the scene.<br/>
     * If this type of asset don't have its corresponding node type, this method should be null.
     * @zh
     * 使用该资源在场景中创建一个新节点。<br/>
     * 如果这类资源没有相应的节点类型，该方法应该是空的。
     */
    virtual void createNode(const CreateNodeCallback& cb) {}

    void            addRef();
    void            decRef();
    inline uint32_t getRefCount() const { return _ref; }

    virtual void onLoaded() {}

    virtual std::any getNativeAsset() const;
    virtual void     setNativeAsset(const std::any& obj);

    virtual void initDefault(const std::string& uuid);
    virtual bool validate() const { return true; }

    virtual bool destroy() override;

    // SERIALIZATION

    /**
     * @return
     */
    virtual std::any _serialize(std::any ctxForExporting) { return std::any(); };

    /**
     *
     * @param data
     */
    virtual void _deserialize(std::any serializedData, std::any handle){};

protected:
    Asset() = default;

    void _setRawAsset(const std::string& filename, bool inLibrary /* = true*/);

private:
    std::string _native;
    std::string _nativeUrl;

    std::string _uuid;

    uint32_t _ref{0};

    bool _loaded{true};
    bool _isDefault{false};
};

} // namespace cc
