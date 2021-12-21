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

#include "cocos/base/Any.h"
#include <functional>
#include <string>
#include <vector>

#include "core/Game.h"
#include "math/Geometry.h"
#include "math/Vec2.h"

namespace cc {

class View;

/**
 * ContentStrategy class is the root strategy class of content's scale strategy,
 * it controls the behavior of how to scale the scene and setup the viewport for the game
 *
 * @class ContentStrategy
 */
struct AdaptResult {
    std::vector<float> scale;
    Rect *             viewport{nullptr};
};

class ContentStrategy {
public:
    ContentStrategy();
    virtual ~ContentStrategy() = default;
    static cc::any EXACT_FIT;
    static cc::any SHOW_ALL;
    static cc::any NO_BORDER;
    static cc::any FIXED_HEIGHT;
    static cc::any FIXED_WIDTH;
    std::string     name{"ContainerStrategy"};

    /**
     * @en Manipulation before appling the strategy
     * @zh 在应用策略之前的操作
     * @param view - The target view
     */

    void preApply(const View &view) const;

    /**
     * @en Function to apply this strategy
     * @zh 策略应用方法
     * @param view
     * @param designedResolution
     */
    void apply(const View &view, const Size &designResolution) const;

    /**
     * @en
     * Manipulation after applying the strategy
     * @zh 策略调用之后的操作
     * @param view  The target view
     */
    void postApply(const View &view);

    const AdaptResult &buildResult(float containerW, float containerH, float contentW, float contentH, float scaleX, float scaleY) const;

private:
    AdaptResult _result;
};

/**
 * ContainerStrategy class is the root strategy class of container's scale strategy,
 * it controls the behavior of how to scale the cc.game.container and cc.game.canvas object
 */
class ContainerStrategy {
public:
    ContainerStrategy()          = default;
    virtual ~ContainerStrategy() = default;

    static cc::any EQUAL_TO_FRAME;
    static cc::any PROPORTION_TO_FRAME;
    std::string     name{"ContainerStrategy"};

    /**
     * @en Manipulation before appling the strategy
     * @zh 在应用策略之前的操作
     * @param view - The target view
     */

    void preApply(const View &view) const;

    /**
     * @en Function to apply this strategy
     * @zh 策略应用方法
     * @param view
     * @param designedResolution
     */
    void apply(const View &view, const Size &designResolution) const;

    /**
     * @en
     * Manipulation after applying the strategy
     * @zh 策略调用之后的操作
     * @param view  The target view
     */
    void postApply(const View &view);

protected:
    void setupContainter(const View &view, float w, float h);
    void fixContainter() const;
};

// Container scale strategys
/**
     * @class EqualToFrame
     * @extends ContainerStrategy
     */
class EqualToFrame final : public ContainerStrategy {
public:
    std::string name{"EqualToFrame"};
    void        apply(const View &view) const;
};
/**
     * @class ProportionalToFrame
     * @extends ContainerStrategy
     */
class ProportionalToFrame final : public ContainerStrategy {
public:
    std::string name{"ProportionalToFrame"};
    void        apply(const View &view, const Size &designResolution) const;
};

// // need to adapt prototype before instantiating
// const _global = typeof window === 'undefined' ? global : window;
// const globalAdapter = _global.__globalAdapter;
// if (globalAdapter) {
//     if (globalAdapter.adaptContainerStrategy) {
//         globalAdapter.adaptContainerStrategy(ContainerStrategy.prototype);
//     }
//     if (globalAdapter.adaptView) {
//         globalAdapter.adaptView(View.prototype);
//     }
// }

// // Alias: Strategy that makes the container's size equals to the frame's size
// ContainerStrategy.EQUAL_TO_FRAME = new EqualToFrame();
// // Alias: Strategy that scale proportionally the container's size to frame's size
// ContainerStrategy.PROPORTION_TO_FRAME = new ProportionalToFrame();

class ExactFit final : public ContentStrategy {
public:
    std::string name{"ExactFit"};
    void        apply(const View &view, const Size &designResolution) const;
};

class NoBorder final : public ContentStrategy {
public:
    std::string name{"NoBorder"};
    void        apply(const View &view, const Size &designResolution) const;
};

class FixedHeight final : public ContentStrategy {
public:
    std::string name{"FixedHeight"};
    void        apply(const View &view, const Size &designResolution) const;
};

class FixedWidth final : public ContentStrategy {
public:
    std::string name{"FixedWidth"};
    void        apply(const View &view, const Size &designResolution) const;
};

// // Alias: Strategy to scale the content's size to container's size, non proportional
// ContentStrategy.EXACT_FIT = new ExactFit();
// // Alias: Strategy to scale the content's size proportionally to maximum size and keeps the whole content area to be visible
// ContentStrategy.SHOW_ALL = new ShowAll();
// // Alias: Strategy to scale the content's size proportionally to fill the whole container area
// ContentStrategy.NO_BORDER = new NoBorder();
// // Alias: Strategy to scale the content's height to container's height and proportionally scale its width
// ContentStrategy.FIXED_HEIGHT = new FixedHeight();˝
// // Alias: Strategy to scale the content's width to container's width and proportionally scale its height
// ContentStrategy.FIXED_WIDTH = new FixedWidth();

/**
 * ResolutionPolicy class is the root strategy class of scale strategy,
 * its main task is to maintain the compatibility with Cocos2d-x</p>
 */
class ResolutionPolicy final {
public:
    /**
     * Constructor of ResolutionPolicy
     * @param containerStg
     * @param contentStg
     */
    ResolutionPolicy() = default;
    ResolutionPolicy(ContainerStrategy *containerStg, ContentStrategy *contentStg);
    ~ResolutionPolicy() = default;

    const Vec2 &getCanvasSize() const;

    /**
     * @en Manipulation before applying the resolution policy
     * @zh 策略应用前的操作
     * @param _view The target view
     */
    void preApply(const View &view);

    /**
     * @en Function to apply this resolution policy
     * The return value is {scale: [scaleX, scaleY], viewport: {new Rect}},
     * The target view can then apply these value to itself, it's preferred not to modify directly its private variables
     * @zh 调用策略方法
     * @param _view - The target view
     * @param designedResolution - The user defined design resolution
     * @return An object contains the scale X/Y values and the viewport rect
     */
    void apply(const View &view, const Size &designedResolution) const;

    /**
     * @en Manipulation after appyling the strategy
     * @zh 策略应用之后的操作
     * @param _view - The target view
     */
    void postApply(const View &view) const;

    /**
     * @en Setup the container's scale strategy
     * @zh 设置容器的适配策略
     * @param containerStg The container strategy
     */
    void setContainerStrategy(ContainerStrategy *containerStg);

    /**
     * @en Setup the content's scale strategy
     * @zh 设置内容的适配策略
     * @param contentStg The content strategy
     */
    void setContentStrategy(ContentStrategy *contentStg);

    /**
     * The entire application is visible in the specified area without trying to preserve the original aspect ratio.<br/>
     * Distortion can occur, and the application may appear stretched or compressed.
     */
    static const int32_t EXACT_FIT{0};
    /**
     * The entire application fills the specified area, without distortion but possibly with some cropping,<br/>
     * while maintaining the original aspect ratio of the application.
     */
    static const int32_t NO_BORDER{1};
    /**
     * The entire application is visible in the specified area without distortion while maintaining the original<br/>
     * aspect ratio of the application. Borders can appear on two sides of the application.
     */
    static const int32_t SHOW_ALL{2};
    /**
     * The application takes the height of the design resolution size and modifies the width of the internal<br/>
     * canvas so that it fits the aspect ratio of the device<br/>
     * no distortion will occur however you must make sure your application works on different<br/>
     * aspect ratios
     */
    static const int32_t FIXED_HEIGHT{3};
    /**
     * The application takes the width of the design resolution size and modifies the height of the internal<br/>
     * canvas so that it fits the aspect ratio of the device<br/>
     * no distortion will occur however you must make sure your application works on different<br/>
     * aspect ratios
     */
    static const int32_t FIXED_WIDTH{4};
    /**
     * Unknown policy
     */
    static const int32_t UNKNOWN{5};

    std::string name{"ResolutionPolicy"};

private:
    ContainerStrategy *_containerStrategy{nullptr};
    ContentStrategy *  _contentStrategy{nullptr};
};
class View final {
public:
    static View &getInstance() {
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
    inline Size getVisibleSize() const {
        return Size(_visibleRect.size.width, _visibleRect.size.height);
    }

    /**
     * @en Returns the visible area size of the view port.
     * @zh 返回视图窗口可见区域像素尺寸。
     */
    Size getVisibleSizeInPixel() const;

    /**
     * @en Returns the visible origin of the view port.
     * @zh 返回视图窗口可见区域原点。
     */

    const Vec2 &getVisibleOrigin() const;

    /**
     * @en Returns the visible origin of the view port.
     * @zh 返回视图窗口可见区域像素原点。
     */
    const Vec2 &getVisibleOriginInPixel() const;

    /**
     * @en Returns the current resolution policy
     * @zh 返回当前分辨率方案
     * @see {{ResolutionPolicy}}
     */
    inline ResolutionPolicy getResolutionPolicy() const {
        return _resolutionPolicy;
    }

    /**
     * @en Sets the current resolution policy
     * @zh 设置当前分辨率模式
     * @see {{ResolutionPolicy}}
     */

    void setResolutionPolicy(const ResolutionPolicy &resolutionPolicy) const;

    void setResolutionPolicy(int32_t resolutionPolicy) const;

    /**
     * @en Sets the resolution policy with designed view size in points.<br/>
     * The resolution policy include: <br/>
     * [1] ResolutionExactFit       Fill screen by stretch-to-fit: if the design resolution ratio of width to height is different from the screen resolution ratio, your game view will be stretched.<br/>
     * [2] ResolutionNoBorder       Full screen without black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two areas of your game view will be cut.<br/>
     * [3] ResolutionShowAll        Full screen with black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two black borders will be shown.<br/>
     * [4] ResolutionFixedHeight    Scale the content's height to screen's height and proportionally scale its width<br/>
     * [5] ResolutionFixedWidth     Scale the content's width to screen's width and proportionally scale its height<br/>
     * [ResolutionPolicy]        [Web only feature] Custom resolution policy, constructed by ResolutionPolicy<br/>
     * @zh 通过设置设计分辨率和匹配模式来进行游戏画面的屏幕适配。
     * @param width Design resolution width.
     * @param height Design resolution height.
     * @param resolutionPolicy The resolution policy desired
     */
    void setDesignResolutionSize(float width, float height, const ResolutionPolicy &resolutionPolicy);

    void setDesignResolutionSize(float width, float height, int32_t resolutionPolicy);

    /**
     * @en Returns the designed size for the view.
     * Default resolution size is the same as 'getFrameSize'.
     * @zh 返回视图的设计分辨率。
     * 默认下分辨率尺寸同 `getFrameSize` 方法相同
     */
    const Size &getDesignResolutionSize() const;

    /**
     * @en Sets the container to desired pixel resolution and fit the game content to it.
     * This function is very useful for adaptation in mobile browsers.
     * In some HD android devices, the resolution is very high, but its browser performance may not be very good.
     * In this case, enabling retina display is very costy and not suggested, and if retina is disabled, the image may be blurry.
     * But this API can be helpful to set a desired pixel resolution which is in between.
     * This API will do the following:
     *     1. Set viewport's width to the desired width in pixel
     *     2. Set body width to the exact pixel resolution
     *     3. The resolution policy will be reset with designed view size in points.
     * @zh 设置容器（container）需要的像素分辨率并且适配相应分辨率的游戏内容。
     * @param width Design resolution width.
     * @param height Design resolution height.
     * @param resolutionPolicy The resolution policy desired
     */
    void setRealPixelResolution(float width, float height, const ResolutionPolicy &resolutionPolicy);

    /**
     * @en Returns the view port rectangle.
     * @zh 返回视窗剪裁区域。
     */
    const Rect &getViewportRect() const;

    /**
     * @en Returns scale factor of the horizontal direction (X axis).
     * @zh 返回横轴的缩放比，这个缩放比是将画布像素分辨率放到设计分辨率的比例。
     */
    inline float getScaleX() const {
        return _scaleX;
    }

    /**
     * @en Returns scale factor of the vertical direction (Y axis).
     * @zh 返回纵轴的缩放比，这个缩放比是将画布像素分辨率缩放到设计分辨率的比例。
     */
    inline float getScaleY() const {
        return _scaleY;
    }

    /**
     * @en Returns device pixel ratio for retina display.
     * @zh 返回设备或浏览器像素比例。
     */
    inline float getDevicePixelRatio() const {
        return _devicePixelRatio;
    }

    /**
     * @en Returns the real location in view for a translation based on a related position
     * @zh 将屏幕坐标转换为游戏视图下的坐标。
     * @param tx - The X axis translation
     * @param ty - The Y axis translation
     * @param relatedPos - The related position object including "left", "top", "width", "height" informations
     * @param out - The out object to save the conversion result
     */

    const Vec2 &convertToLocationInView(float tx, float ty, const cc::any &relatedPos, const Vec2 &out) const;

    void convertPointWithScale(Vec2 &point);

    bool _resizeWithBrowserSize{true};
    Size _designResolutionSize;

private:
    View()  = default;
    ~View() = default;

    void resizeEvent() const;
    void initFrameSize() const;

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
    cc::any         _orientation{0};
    ResolutionPolicy _resolutionPolicy;
    ResolutionPolicy _rpExactFit;
    ResolutionPolicy _rpShowAll;
    ResolutionPolicy _rpNoBorder;
    ResolutionPolicy _rpFixedHeight;
    ResolutionPolicy _rpFixedWidth;
};

} // namespace cc
