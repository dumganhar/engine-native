/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

 http =//www.cocos.com

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

#include "core/event/EventEmitter.h"

namespace cc {
class SystemInfo final : public EventEmitter {
public:
    static SystemInfo& getInstance() {
        static SystemInfo instance;
        return instance;
    }

    const bool isNative{true};
    const bool isBrowser{false};
    const bool isMobile{true};
    const bool isLittleEndian{true};
    // const Platform platform;
    // const Language language;
    const std::string nativeLanguage;
    // const OS os;
    const std::string osVersion;
    const uint32_t osMainVersion{0};
    // const BrowserType browserTpe;
    const std::string browserVersion;
    const float pixelRatio{1};
    // const SupportCapability supportCapability;

    // TODO(PP): need to wrap the function __isObjectValid()

    uint32_t getBatterLevel() const;

    void triggerGC() const;

    void openURL() const;

    int32_t now() const;

    void restartJSVM() const;

    void close() const;

private:
    SystemInfo() = default;
    ~SystemInfo() = default;
    void registerEvent() const;

};

} // namespace cc 