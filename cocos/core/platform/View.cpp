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

#include "core/platform/View.h"

namespace cc {
//ContainerStrategy
std::any ContainerStrategy::EQUAL_TO_FRAME{nullptr};
std::any ContainerStrategy::PROPORTION_TO_FRAME{nullptr};

//ContentStrategy
ContentStrategy::ContentStrategy() {
    _result.scale    = {1, 1};
    _result.viewport = nullptr;
}

std::any ContentStrategy::EXACT_FIT{nullptr};
std::any ContentStrategy::SHOW_ALL{nullptr};
std::any ContentStrategy::NO_BORDER{nullptr};
std::any ContentStrategy::FIXED_HEIGHT{nullptr};
std::any ContentStrategy::FIXED_WIDTH{nullptr};

//ResolutionPolicy
ResolutionPolicy::ResolutionPolicy(ContainerStrategy *containerStg, ContentStrategy *contentStg) {
    _containerStrategy = nullptr;
    _contentStrategy   = nullptr;
    setContainerStrategy(containerStg);
    setContentStrategy(contentStg);
}

// View
void View::convertPointWithScale(Vec2& point) {
    point.x = (point.x - _viewportRect.getMinX()) / _scaleX;
    point.y = (point.y - _viewportRect.getMinY()) / _scaleY;
}

} // namespace cc
