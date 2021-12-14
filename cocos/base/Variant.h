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

#include "cocos/base/TypeDef.h"

#if USE_STD_C_PLUS_PLUS_17 > 0
    #include <variant>

    #define CC_HOLDS_ALTERNATIVE std::holds_alternative
    #define CC_GET_IF            std::get_if
    #define CC_GET               std::get
    #define CC_VISIT             std::visit

namespace cc {
template <class... T>
using variant = std::variant<T...>;

using monostate = std::monostate;
}; // namespace cc
#else
    #include "boost/variant2/variant.hpp"

    #define CC_HOLDS_ALTERNATIVE boost::variant2::holds_alternative
    #define CC_GET_IF            boost::variant2::get_if
    #define CC_GET               boost::variant2::get
    #define CC_VISIT             boost::variant2::visit

namespace cc {
template <class... T>
using variant = boost::variant2::variant<T...>;

using monostate = boost::variant2::monostate;
}; // namespace cc
#endif
