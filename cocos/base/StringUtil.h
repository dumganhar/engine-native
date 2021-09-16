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

#include <cstddef>
#include "Macros.h"
#include "TypeDef.h"
#include "base/base64.h"
#include "memory/Memory.h"

#include "base/ZipUtils.h"
namespace cc {

class CC_DLL StringUtil {
public:
    static int         vprintf(char *buf, const char *last, const char *fmt, va_list args);
    static int         printf(char *buf, const char *last, const char *fmt, ...);
    static String      format(const char *fmt, ...);
    static StringArray split(const String &str, const String &delims, uint maxSplits = 0);
};

class CC_DLL GzipedString {
public:
    explicit GzipedString(std::string &&dat) : _str(dat) {}
    explicit GzipedString(const char *dat) : _str(dat) {}

    GzipedString(const GzipedString &o) = default;
    GzipedString &operator=(const GzipedString &d) = default;

    GzipedString(GzipedString &&o) noexcept {
        _str = std::move(o._str);
    }

    GzipedString &operator=(std::string &&d) {
        _str = std::move(d);
        return *this;
    }

    GzipedString &operator=(GzipedString &&d) noexcept {
        _str = std::move(d._str);
        return *this;
    }

    std::string value() const {
        uint8_t *   outGzip   = nullptr;
        uint8_t *   outBase64 = nullptr;
        auto *      inc       = const_cast<char *>(_str.c_str());
        auto *      inu       = reinterpret_cast<unsigned char *>(inc);
        auto        lenB64    = base64Decode(inu, static_cast<unsigned int>(_str.size()), &outBase64);
        auto        len       = ZipUtils::inflateMemory(outBase64, static_cast<ssize_t>(lenB64), &outGzip);
        std::string ret(outGzip, outGzip + len);
        free(outGzip);
        free(outBase64);
        return ret;
    }

private:
    std::string _str{};
};

} // namespace cc
