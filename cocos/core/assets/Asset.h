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

#include "base/Value.h"
#include "core/data/Object.h"

#include "core/Any.h"

#include <string>
#include <unordered_map>

namespace cc {

class Asset : public CCObject {
public:
    virtual ~Asset() = default;

    const std::string& getNativeUrl();

    using NativeDep = std::unordered_map<std::string, Value>;
    NativeDep getNativeDep();


    void addRef();
    void decRef();
    inline uint32_t getRefCount() const { return _ref; }

    virtual void onLoaded() {}

    virtual Any getNativeAsset();
    virtual void setNativeAsset(Any obj);

    virtual void initDefault(const std::string& uuid);
    virtual bool validate() { return true; }

    virtual bool destroy() override;

protected:
    Asset() = default;

    void _setRawAsset (const std::string& filename, bool inLibrary/* = true*/);


private:
    std::string _native;
    std::string _nativeUrl;

    std::string _uuid;

    uint32_t _ref = 0;

    bool _loaded = true;
    bool _isDefault = false;

};

} // namespace cc {
