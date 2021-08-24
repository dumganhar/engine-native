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

#include "core/platform/VisibleRect.h"

namespace cc {

float VisibleRect::width  = 0.F;
float VisibleRect::height = 0.F;

void VisibleRect::init(const Rect &visibleRect) {
    const float w = VisibleRect::width = visibleRect.size.width;
    const float h = VisibleRect::height = visibleRect.size.height;
    const float l                       = visibleRect.origin.x;
    const float b                       = visibleRect.origin.y;
    const float t                       = b + h;
    const float r                       = l + w;

    // top
    topLeft.x  = l;
    topLeft.y  = t;
    topRight.x = r;
    topRight.y = t;
    top.x      = l + w / 2;
    top.y      = t;

    // bottom
    bottomLeft.x  = l;
    bottomLeft.y  = b;
    bottomRight.x = r;
    bottomRight.y = b;
    bottom.x      = l + w / 2;
    bottom.y      = b;

    // center
    center.x = l + w / 2;
    center.y = b + h / 2;

    // left
    left.x = l;
    left.y = b + h / 2;

    // right
    right.x = r;
    right.y = b + h / 2;
}

} // namespace cc
