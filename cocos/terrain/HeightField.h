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

#include "core/TypedArray.h"

namespace cc {

class HeightField final {
public:
    HeightField(int32_t w, int32_t h);
    ~HeightField() = default;

    inline int32_t getWidth() const { return _w; }
    inline int32_t getHeight() const { return _h; }

    inline void set(int32_t i, int32_t j, uint16_t value) {
        _data[j * _w + i] = value;
    }

    inline uint16_t get(int32_t i, int32_t j) const {
        return _data[j * _w + i];
    }

    uint16_t getClamp(int32_t i, int32_t j) const;

    uint16_t getAt(float x, float y);

private:
    Uint16Array _data;
    int32_t     _w{0};
    int32_t     _h{0};

    friend class Terrain;
};

} // namespace cc
