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

#include "math/Geometry.h"

namespace cc {
/**
 * @en The screen API provides an easy way to do some screen managing stuff.
 * @zh screen 单例对象提供简单的方法来做屏幕管理相关的工作。
 */
class Screen {
    // TODO(PP): windowSize should be physical size, and deprecate sys.windowPixelResolution
    // /**
    //  * @en Get the size of current window.
    //  * On Web platform, this should be the size of game frame.
    //  * @zh 获取当前窗口尺寸。
    //  * 在 Web 平台，这里应该是 game frame 的尺寸
    //  * @returns {Size}
    //  */
    const Size& getWindowSize() const;

    const Size& screenSize() const;

    /**
     * @en Whether it supports full screen？
     * @zh 是否支持全屏？
     * @returns {Boolean}
     */
    bool isSupportsFullScreen() const;

    /**
     * @en Return true if it's in full screen state now.
     * @zh 当前是否处在全屏状态下
     * @returns {boolean}
     */

    bool isFullScreen() const;

    /**
     * @en Request to enter full screen mode.
     * Many browsers forbid to enter full screen mode without an user intended interaction.
     * If failed to request fullscreen, another attempt will be made to request fullscreen the next time a user interaction occurs.
     * @zh 尝试使当前屏幕进入全屏模式，很多浏览器不允许程序触发这样的行为，必须在一个用户交互回调中才会生效。
     * 如果进入全屏失败，会在下一次用户发生交互时，再次尝试进入全屏。
     * @return {Promise}
     */
    // public requestFullScreen (): Promise<void>;

    /**
     * @en Exit the full mode.
     * @zh 退出全屏模式
     * @return {Promise}
     */
    // public exitFullScreen (): Promise<any> {
    //     return screenAdapter.exitFullScreen();
    // }

    // TODO(PP): to support registering fullscreen change
    // TODO(PP): to support screen resize
};

} // namespace cc
