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
#include "terrain/HeightField.h"

#include <algorithm>
#include "cocos/math/Utils.h"

namespace cc {

HeightField::HeightField(int32_t w, int32_t h)
: _w{w}, _h{h} {
    _data.reset(w * h);

    for (int32_t i = 0; i < w * h; ++i) {
        _data[i] = 0; //cjh FIXME: it seems this for loop is not needed since ArrayBuffer will set the value of all elements to zero.
    }
}

uint16_t HeightField::getClamp(int32_t i, int32_t j) const {
    i = cc::mathutils::clamp(i, 0, _w - 1);
    j = cc::mathutils::clamp(j, 0, _h - 1);

    return get(i, j);
}

uint16_t HeightField::getAt(float x, float y) {
    float fx = x;
    float fy = y;

    int32_t ix0 = static_cast<int32_t>(std::floor(fx));
    int32_t iz0 = static_cast<int32_t>(std::floor(fy));
    int32_t ix1 = ix0 + 1;
    int32_t iz1 = iz0 + 1;

    const float dx = fx - static_cast<float>(ix0);
    const float dz = fy - static_cast<float>(iz0);

    ix0 = cc::mathutils::clamp(ix0, 0, _w - 1);
    iz0 = cc::mathutils::clamp(iz0, 0, _h - 1);
    ix1 = cc::mathutils::clamp(ix1, 0, _w - 1);
    iz1 = cc::mathutils::clamp(iz1, 0, _h - 1);

    uint16_t       a = get(ix0, iz0);
    const uint16_t b = get(ix1, iz0);
    const uint16_t c = get(ix0, iz1);
    uint16_t       d = get(ix1, iz1);
    const float    m = (b + c) * 0.5F;

    if (dx + dz <= 1.0F) { //cjh TODO: float value compare
        d = m + (m - a);
    } else {
        a = m + (m - d);
    }

    const float h1 = a * (1.0F - dx) + b * dx;
    const float h2 = c * (1.0F - dx) + d * dx;

    const float h = h1 * (1.0F - dz) + h2 * dz;

    return static_cast<uint16_t>(h);
}

} // namespace cc
