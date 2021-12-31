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

#include "core/builtin/Effects.h"
#include "base/StringUtil.h"
namespace cc {

// absolute essential effects
const GzipedString builtinEffects{
    "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"};
} // namespace cc
