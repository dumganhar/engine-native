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

#include <any>
#include <functional>

#include "math/Geometry.h"
#include "math/Vec2.h"

namespace cc {

class ResolutionPolicy {
};
class View {
public:
    static View& getInstance() {
        static View instance;
        return instance;
    }

    void init();

    /**
     * @en
     * Sets whether resize canvas automatically when browser's size changed.<br/>
     * Useful only on web.
     * @zh 设置当发现浏览器的尺寸改变时，是否自动调整 canvas 尺寸大小。
     * 仅在 Web 模式下有效。
     * @param enabled - Whether enable automatic resize with browser's resize event
     */
    void resizeWithBrowserSize(bool enabled) const;

    /**
     * @en
     * Sets the callback function for `view`'s resize action,<br/>
     * this callback will be invoked before applying resolution policy, <br/>
     * so you can do any additional modifications within the callback.<br/>
     * Useful only on web.
     * @zh 设置 `view` 调整视窗尺寸行为的回调函数，
     * 这个回调函数会在应用适配模式之前被调用，
     * 因此你可以在这个回调函数内添加任意附加改变，
     * 仅在 Web 平台下有效。
     * @param callback - The callback function
     */
    void setResizeCallback(std::function<void()> callback);

    /**
     * @en
     * Sets the orientation of the game, it can be landscape, portrait or auto.
     * When set it to landscape or portrait, and screen w/h ratio doesn't fit,
     * `view` will automatically rotate the game canvas using CSS.
     * Note that this function doesn't have any effect in native,
     * in native, you need to set the application orientation in native project settings
     * @zh 设置游戏屏幕朝向，它能够是横版，竖版或自动。
     * 当设置为横版或竖版，并且屏幕的宽高比例不匹配时，
     * `view` 会自动用 CSS 旋转游戏场景的 canvas，
     * 这个方法不会对 native 部分产生任何影响，对于 native 而言，你需要在应用设置中的设置排版。
     * @param orientation - Possible values: macro.ORIENTATION_LANDSCAPE | macro.ORIENTATION_PORTRAIT | macro.ORIENTATION_AUTO
     */
    void setOrientation(int32_t orientation);

    /**
     * @en
     * Sets whether the engine modify the "viewport" meta in your web page.<br/>
     * It's enabled by default, we strongly suggest you not to disable it.<br/>
     * And even when it's enabled, you can still set your own "viewport" meta, it won't be overridden<br/>
     * Only useful on web
     * @zh 设置引擎是否调整 viewport meta 来配合屏幕适配。
     * 默认设置为启动，我们强烈建议你不要将它设置为关闭。
     * 即使当它启动时，你仍然能够设置你的 viewport meta，它不会被覆盖。
     * 仅在 Web 模式下有效
     * @param enabled - Enable automatic modification to "viewport" meta
     * @deprecated since v3.3
     */
    void adjustViewPortMeta(bool enabled) const {
        // DO NOTHING
    }

    /**
     * @en
     * Retina support is enabled by default for Apple device but disabled for other devices,<br/>
     * it takes effect only when you called setDesignResolutionPolicy<br/>
     * Only useful on web
     * @zh 对于 Apple 这种支持 Retina 显示的设备上默认进行优化而其他类型设备默认不进行优化，
     * 它仅会在你调用 setDesignResolutionPolicy 方法时有影响。
     * 仅在 Web 模式下有效。
     * @param enabled - Enable or disable retina display
     */
    inline void enableRetina(bool enabled) {
        _retinaEnabled = enabled;
    }

    /**
     * @en
     * Check whether retina display is enabled.<br/>
     * Only useful on web
     * @zh 检查是否对 Retina 显示设备进行优化。
     * 仅在 Web 模式下有效。
     */
    inline bool isRetinaEnabled() const {
        return _retinaEnabled;
    }

    /**
     * @en
     * If enabled, the application will try automatically to enter full screen mode on mobile devices<br/>
     * You can pass true as parameter to enable it and disable it by passing false.<br/>
     * Only useful on web
     * @zh 启动时，移动端游戏会在移动端自动尝试进入全屏模式。
     * 你能够传入 true 为参数去启动它，用 false 参数来关闭它。
     * @param enabled - Enable or disable auto full screen on mobile devices
     *
     * @deprecated since v3.3
     */
    void enableAutoFullScreen(bool enabled) const;

    /**
     * @en
     * Check whether auto full screen is enabled.<br/>
     * Only useful on web
     * @zh 检查自动进入全屏模式是否启动。
     * 仅在 Web 模式下有效。
     * @return Auto full screen enabled or not
     *
     * @deprecated since v3.3
     */

    inline bool isAutoFullScreenEnable() const {
        return _autoFullScreen;
    }

    /*
     * Not support on native.<br/>
     * On web, it sets the size of the canvas.
     * @zh 这个方法并不支持 native 平台，在 Web 平台下，可以用来设置 canvas 尺寸。
     * @private
     * @param {Number} width
     * @param {Number} height
     */
    void setCanvasSize(int32_t width, int32_t height);

    /**
     * @en
     * Returns the canvas size of the view.<br/>
     * On native platforms, it returns the screen size since the view is a fullscreen view.<br/>
     * On web, it returns the size of the canvas element.
     * @zh 返回视图中 canvas 的尺寸。
     * 在 native 平台下，它返回全屏视图下屏幕的尺寸。
     * 在 Web 平台下，它返回 canvas 元素尺寸。
     */

    Size getCanvasSize() const;

    /**
     * @en
     * Returns the frame size of the view.<br/>
     * On native platforms, it returns the screen size since the view is a fullscreen view.<br/>
     * On web, it returns the size of the canvas's outer DOM element.
     * @zh 返回视图中边框尺寸。
     * 在 native 平台下，它返回全屏视图下屏幕的尺寸。
     * 在 web 平台下，它返回 canvas 元素的外层 DOM 元素尺寸。
     */
    Size getFrameSize() const;

    /**
     * @en On native, it sets the frame size of view.<br/>
     * On web, it sets the size of the canvas's outer DOM element.
     * @zh 在 native 平台下，设置视图框架尺寸。
     * 在 web 平台下，设置 canvas 外层 DOM 元素尺寸。
     * @param {Number} width
     * @param {Number} height
     */
    void setFrameSize(int32_t width, int32_t height) const;

    /**
     * @en Returns the visible area size of the view port.
     * @zh 返回视图窗口可见区域尺寸。
     */
    Size getVisibleSize() const;

    /**
     * @en Returns the visible area size of the view port.
     * @zh 返回视图窗口可见区域像素尺寸。
     */
    Size getVisibleSizeInPixel() const;

    /**
     * @en Returns the visible origin of the view port.
     * @zh 返回视图窗口可见区域原点。
     */

    const Vec2& getVisibleOrigin() const;

    /**
     * @en Returns the visible origin of the view port.
     * @zh 返回视图窗口可见区域像素原点。
     */
    const Vec2& getVisibleOriginInPixel() const;

    bool _resizeWithBrowserSize{true};
    Size _designResolutionSize;

private:
    View()  = default;
    ~View() = default;

    Size  _frameSize;
    float _scaleX{1};
    float _scaleY{1};
    Rect  _viewportRect;
    Rect  _visibleRect;
    bool  _autoFullScreen{false};
    float _devicePixelRatio{1};
    float _maxPixelRatio{2};
    bool  _retinaEnabled{false};
    using _resizeCallback = std::function<void()>;
    bool             _resizing{false};
    bool             _orientationChanging{true};
    bool             _isRotated{false};
    std::any         _orientation{0};
    ResolutionPolicy _resolutionPolicy;
    ResolutionPolicy _rpExactFit;
    ResolutionPolicy _rpShowAll;
    ResolutionPolicy _rpNoBorder;
    ResolutionPolicy _rpFixedHeight;
    ResolutionPolicy _rpFixedWidth;
};

} // namespace cc
