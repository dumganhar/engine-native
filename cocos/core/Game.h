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

#include <cmath>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "core/asset-manager/AssetManager.h"
#include "core/event/CallbacksInvoker.h"
#include "core/platform/event-manager/InputManager.h"
#include "core/platform/native/SystemInfo.h"
#include "platform/Application.h"
#include "renderer/pipeline/RenderPipeline.h"

namespace cc {

namespace gfx {
class Device;
}

class Node;

struct ISceneInfo {
    std::string url;
    std::string uuid;
};

struct LayerItem {
    std::string name;
    int32_t     value{0};
};

struct IGameConfig {
    /**
     * @zh
     * 设置 debug 模式，在浏览器中这个选项会被忽略。
     * @en
     * Set debug mode, only valid in non-browser environment.
     */
    // debugMode?: debug.DebugMode;

    /**
     * @zh
     * 当 showFPS 为 true 的时候界面的左下角将显示 fps 的信息，否则被隐藏。
     * @en
     * Left bottom corner fps information will show when "showFPS" equals true, otherwise it will be hide.
     */
    bool showFPS{false};

    /**
     * @zh
     * 暴露类名让 Chrome DevTools 可以识别，如果开启会稍稍降低类的创建过程的性能，但对对象构造没有影响。
     * @en
     * Expose class name to chrome debug tools, the class intantiate performance is a little bit slower when exposed.
     */
    bool exposeClassName{false};

    /**
     * @zh
     * 设置想要的帧率你的游戏，但真正的FPS取决于你的游戏实现和运行环境。
     * @en
     * Set the wanted frame rate for your game, but the real fps depends on your game implementation and the running environment.
     */
    uint32_t frameRate{60};

    /**
     * @zh
     * Web 页面上的 Canvas Element ID，仅适用于 web 端。
     * @en
     * Sets the id of your canvas element on the web page, it's useful only on web.
     */
    // id?: string | HTMLElement;

    /**
     * @zh
     * 渲染模式。
     * 设置渲染器类型，仅适用于 web 端：
     * - 0 - 通过引擎自动选择。
     * - 1 - 强制使用 canvas 渲染。
     * - 2 - 强制使用 WebGL 渲染，但是在部分 Android 浏览器中这个选项会被忽略。
     * @en
     * Sets the renderer type, only useful on web:
     * - 0 - Automatically chosen by engine.
     * - 1 - Forced to use canvas renderer.
     * - 2 - Forced to use WebGL renderer, but this will be ignored on mobile browsers.
     */
    // renderMode?: 0 | 1 | 2;
    enum class RenderMode {
        AUTO   = 0,
        CANVAS = 1,
        WEB_GL = 2,
    };

    RenderMode renderMode{RenderMode::AUTO};

    /**
     * @zh
     * 当前包中可用场景。
     * @en
     * Include available scenes in the current bundle.
     */
    std::vector<ISceneInfo *> scenes;

    /**
     * For internal use.
     */
    std::vector<std::string> jsList;

    /**
     * Render pipeline resources
     */
    std::string renderPipeline;

    /**
     * Asset Manager initialization options
     */

    IAssetManagerOptions *assetOptions{nullptr};

    /**
     * GPU instancing options
     */
    // customJointTextureLayouts?: ICustomJointTextureLayout[];

    /**
     * Physics system config
     */
    // IPhysicsConfig physics;

    /**
     * User layers config
     */
    std::vector<LayerItem *> layers;

    struct Adapter {
        // HTMLCanvasElement canvas;
        // HTMLDivElement frame;
        // HTMLDivElement containter;
        // [x: string]: any,
    };
};

class Game final : public EventTarget {
public:
    /**
    * @en
    * This is a Game instance.
    * @zh
    * 这是一个 Game 类的实例，包含游戏主体信息并负责驱动游戏的游戏对象。
    */
    static Game &getInstance() {
        static Game instance;
        return instance;
    }

    /**
     * @en Event triggered when game hide to background.<br>
     * Please note that this event is not 100% guaranteed to be fired on Web platform,<br>
     * on native platforms, it corresponds to enter background event, os status bar or notification center may not trigger this event.
     * @zh 游戏进入后台时触发的事件。<br>
     * 请注意，在 WEB 平台，这个事件不一定会 100% 触发，这完全取决于浏览器的回调行为。<br>
     * 在原生平台，它对应的是应用被切换到后台事件，下拉菜单和上拉状态栏等不一定会触发这个事件，这取决于系统行为。
     * @example
     * ```ts
     * import { game, audioEngine } from 'cc';
     * game.on(Game.EVENT_HIDE, function () {
     *     audioEngine.pauseMusic();
     *     audioEngine.pauseAllEffects();
     * });
     * ```
     */
    static const CallbacksInvoker::KeyType EVENT_HIDE;

    /**
     * @en Event triggered when game back to foreground<br>
     * Please note that this event is not 100% guaranteed to be fired on Web platform,<br>
     * on native platforms, it corresponds to enter foreground event.
     * @zh 游戏进入前台运行时触发的事件。<br>
     * 请注意，在 WEB 平台，这个事件不一定会 100% 触发，这完全取决于浏览器的回调行为。<br>
     * 在原生平台，它对应的是应用被切换到前台事件。
     */
    static const CallbacksInvoker::KeyType EVENT_SHOW;

    /**
     * @en Event triggered when system in low memory status.<br>
     * This event is only triggered on native iOS/Android platform.
     * @zh 程序在内存不足时触发的事件。<br>
     * 该事件只会在 iOS/Android 平台触发。
     */
    static const CallbacksInvoker::KeyType EVENT_LOW_MEMORY;

    /**
     * @en Event triggered after game inited, at this point all engine objects and game scripts are loaded
     * @zh 游戏启动后的触发事件，此时加载所有的引擎对象和游戏脚本。
     */
    static const CallbacksInvoker::KeyType EVENT_GAME_INITED;

    /**
     * @en Event triggered after engine inited, at this point you will be able to use all engine classes.<br>
     * It was defined as EVENT_RENDERER_INITED in cocos creator v1.x and renamed in v2.0.
     * Since Cocos Creator v3.0, EVENT_RENDERER_INITED is a new event, look up define for details.
     * @zh 在引擎初始化之后触发的事件，此时您能够使用引擎所有的类。<br>
     * 它在 Cocos Creator v1.x 版本中名字为 EVENT_RENDERER_INITED，在 v2.0 更名为 EVENT_ENGINE_INITED
     * 并在 Cocos Creator v3.0 中将 EVENT_RENDERER_INITED 用作为渲染器初始化的事件。
     */
    static const CallbacksInvoker::KeyType EVENT_ENGINE_INITED;

    /**
     * @en Event triggered after renderer inited, at this point you will be able to use all gfx renderer feature.<br>
     * @zh 在渲染器初始化之后触发的事件，此事件在 EVENT_ENGINE_INITED 之前触发，此时开始可使用 gfx 渲染框架。
     */
    static const CallbacksInvoker::KeyType EVENT_RENDERER_INITED;

    /**
     * @en Event triggered when game restart
     * @zh 调用restart后，触发事件
     */
    static const CallbacksInvoker::KeyType EVENT_RESTART;

    /**
     * @en Web Canvas 2d API as renderer backend.
     * @zh 使用 Web Canvas 2d API 作为渲染器后端。
     */
    static const uint32_t RENDER_TYPE_CANVAS{0};
    /**
     * @en WebGL API as renderer backend.
     * @zh 使用 WebGL API 作为渲染器后端。
     */
    static const uint32_t RENDER_TYPE_WEBGL{1};
    /**
     * @en OpenGL API as renderer backend.
     * @zh 使用 OpenGL API 作为渲染器后端。
     */
    static const uint32_t RENDER_TYPE_OPENGL{2};

    /**
     * @en If delta time since last frame is more than this threshold in seconds,
     * the game timer will consider user is debugging and adjust the delta time to [[frameTime]].
     * @zh 如果距离上一帧的帧间隔超过了这个阈值（单位是 s），那么就会被认为正在调试，帧间隔会被自动调节为 [[frameTime]].
     */
    static const uint32_t DEBUG_DT_THRESHOLD{1};

    // /**
    //  * @en The outer frame of the game canvas; parent of game container.
    //  * @zh 游戏画布的外框，container 的父容器。
    //  */
    // HTMLDivElement *frame{nullptr};
    // /**
    //  * @en The container of game canvas.
    //  * @zh 游戏画布的容器。
    //  */
    // HTMLDivElement *container{nullptr};
    // /**
    //  * @en The canvas of the game.
    //  * @zh 游戏的画布。
    //  */
    // HTMLDivElement *canvas{nullptr};

    /**
     * @en The renderer backend of the game.
     * @zh 游戏的渲染器类型。
     */
    int32_t renderType{-1};

    // public eventTargetOn = super.on;
    // public eventTargetOnce = super.once;

    IGameConfig *config{nullptr};

    // /**
    //  * @en Callback when the scripts of engine have been load.
    //  * @zh 当引擎完成启动后的回调函数。
    //  * @method onStart
    //  */
    using OnStart = std::function<void()>;

    /**
     * @en Indicates whether the engine and the renderer has been initialized
     * @zh 引擎和渲染器是否以完成初始化
     */
    inline bool getInited() const {
        return _inited;
    }

    /**
     * @en Set frame rate of game.
     * @zh 设置游戏帧率。
     * @deprecated since v3.3.0 please use [[game.frameRate]]
     */
    inline void setFrameRate(uint32_t frameRate) {
        _frameRate = frameRate;
    }

    inline void setFrameRate(const std::string &frameRate) {
        _frameRate = std::stoul(frameRate);
    }
    /**
     * @en Expected frame rate of the game.
     * @zh 游戏的设定帧率。
     */
    inline uint32_t getFrameRate() const {
        return _frameRate;
    }

    /**
     * @en The delta time since last frame, unit: s.
     * @zh 获取上一帧的增量时间，以秒为单位。
     */
    inline float getDeltaTime() const {
        return _deltaTime;
    }

    /**
     * @en The total passed time since game start, unit: ms
     * @zh 获取从游戏开始到现在总共经过的时间，以毫秒为单位
     */
    inline uint32_t getTotalTime() {
        auto     nowTime      = std::chrono::high_resolution_clock::now();
        uint32_t intervalInMS = (static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::microseconds>(nowTime - _initTime).count()) / 1000);
        return intervalInMS;
    }

    /**
     * @en The start time of the current frame in milliseconds.
     * @zh 获取当前帧开始的时间（以 ms 为单位）。
     */
    inline float getFrameStartTime() const {
        return _startTime;
    }

    /**
     * @en The expected delta time of each frame in milliseconds
     * @zh 期望帧率对应的每帧时间（以 ms 为单位）
     */
    float frameTime{1000.F / 60};

    std::unordered_map<std::string, Node *> _persistRootNodes;

    // states
    bool _configLoaded{false}; // whether config loaded
    bool _isCloning{false};    // deserializing or instantiating

    //  @Game play control

    /**
     * @en Run the game frame by frame with a fixed delta time correspond to frame rate.
     * @zh 以固定帧间隔执行一帧游戏循环，帧间隔与设定的帧率匹配。
     */
    void step() const;

    /**
     * @en Pause the game main loop. This will pause:<br>
     * game logic execution, rendering process, event manager, background music and all audio effects.<br>
     * This is different with `director.pause` which only pause the game logic execution.<br>
     * @zh 暂停游戏主循环。包含：游戏逻辑，渲染，事件处理，背景音乐和所有音效。这点和只暂停游戏逻辑的 `director.pause` 不同。
     */
    void pause();

    /**
     * @en Resume the game from pause. This will resume:<br>
     * game logic execution, rendering process, event manager, background music and all audio effects.<br>
     * @zh 恢复游戏主循环。包含：游戏逻辑，渲染，事件处理，背景音乐和所有音效。
     */
    void resume();

    /**
     * @en Check whether the game is paused.
     * @zh 判断游戏是否暂停。
     */
    inline bool isPaused() const {
        return _paused;
    }

    /**
     * @en Restart game.
     * @zh 重新开始游戏
     */
    void restart();

    /**
     * @en End game, it will close the game window
     * @zh 退出游戏
     */
    void end() const;

    /**
     * @en
     * Register an callback of a specific event type on the game object.<br>
     * This type of event should be triggered via `emit`.<br>
     * @zh
     * 注册 game 的特定事件类型回调。这种类型的事件应该被 `emit` 触发。<br>
     *
     * @param type - A string representing the event type to listen for.
     * @param callback - The callback that will be invoked when the event is dispatched.<br>
     *                              The callback is ignored if it is a duplicate (the callbacks are unique).
     * @param target - The target (this object) to invoke the callback, can be null
     * @param once - After the first invocation, whether the callback should be unregistered.
     * @return - Just returns the incoming callback so you can save the anonymous function easier.
     */
    // public on (type: string, callback: () => void, target?: any, once?: boolean): any {
    //     // Make sure EVENT_ENGINE_INITED callbacks to be invoked
    //     if ((this._engineInited && type === Game.EVENT_ENGINE_INITED)
    //     || (this._inited && type === Game.EVENT_GAME_INITED)
    //     || (this._rendererInitialized && type === Game.EVENT_RENDERER_INITED)) {
    //         callback.call(target);
    //     }
    //     return this.eventTargetOn(type, callback, target, once);
    // }

    /**
     * @en
     * Register an callback of a specific event type on the game object,<br>
     * the callback will remove itself after the first time it is triggered.<br>
     * @zh
     * 注册 game 的特定事件类型回调，回调会在第一时间被触发后删除自身。
     *
     * @param type - A string representing the event type to listen for.
     * @param callback - The callback that will be invoked when the event is dispatched.<br>
     *                              The callback is ignored if it is a duplicate (the callbacks are unique).
     * @param target - The target (this object) to invoke the callback, can be null
     */
    // public once (type: string, callback: () => void, target?: any): any {
    //     // Make sure EVENT_ENGINE_INITED callbacks to be invoked
    //     if (this._engineInited && type === Game.EVENT_ENGINE_INITED) {
    //         return callback.call(target);
    //     }
    //     return this.eventTargetOnce(type, callback, target);
    // }

    /**
     * @en Init game with configuration object.
     * @zh 使用指定的配置初始化引擎。
     * @param config - Pass configuration object
     */
    void init(IGameConfig *config);

    /**
     * @en Run game with configuration object and onStart function.
     * @zh 运行游戏，并且指定引擎配置和 onStart 的回调。
     * @param onStart - function to be executed after game initialized
     */
    // public run(onStart?: Game.OnStart): Promise<void>;

    //     public run (configOrCallback?: Game.OnStart | IGameConfig, onStart?: Game.OnStart) {
    //     // To compatible with older version,
    //     // we allow the `run(config, onstart?)` form. But it's deprecated.
    //     let initPromise: Promise<boolean> | undefined;
    //     if (typeof configOrCallback !== 'function' && configOrCallback) {
    //         initPromise = this.init(configOrCallback);
    //         this.onStart = onStart ?? null;
    //     } else {
    //         this.onStart = configOrCallback ?? null;
    //     }
    //     garbageCollectionManager.init();

    //     return Promise.resolve(initPromise).then(() => this._setRenderPipelineNShowSplash());
    // }

    //  @ Persist root node section
    /**
     * @en
     * Add a persistent root node to the game, the persistent node won't be destroyed during scene transition.<br>
     * The target node must be placed in the root level of hierarchy, otherwise this API won't have any effect.
     * @zh
     * 声明常驻根节点，该节点不会在场景切换中被销毁。<br>
     * 目标节点必须位于为层级的根节点，否则无效。
     * @param node - The node to be made persistent
     */
    void addPersistRootNode(Node *node);

    /**
     * @en Remove a persistent root node.
     * @zh 取消常驻根节点。
     * @param node - The node to be removed from persistent node list
     */
    void removePersistRootNode(Node *node);

    /**
     * @en Check whether the node is a persistent root node.
     * @zh 检查节点是否是常驻根节点。
     * @param node - The node to be checked
     */
    bool isPersistRootNode(Node *node) const;

private:
    Game() = default;

    ~Game() = default;

    //  @Engine loading
    void initEngine();

    //  @Time ticker section
    void setAnimFrame();

    int stTime(void *cb);

    void ctTime();

    void ctTime(uint32_t);

    float calculateDT(float now);

    void updateCallback();

    // Run game.
    void runMainLoop();

    // @Game loading section
    void initConfig(IGameConfig *config);

    void determineRenderType();

    void initDevice();

    void initEvents();

    void onHide();

    void onShow();

    void setRenderPipelineNShowSplash();

    void setupRenderPipeline();

    void showSplashScreen();

    void setRenderPipeline(pipeline::RenderPipeline *pipeline);

    void safeEmit(const CallbacksInvoker::KeyType &event);

    gfx::Device *_gfxDevice = nullptr;

    // states
    bool _inited{false};
    bool _engineInited{false}; // whether the engine has inited
    bool _rendererInitialized{false};
    bool _paused{true};

    // frame control
    uint32_t                                                    _frameRate{60};
    int                                                         _intervalId{0}; // interval target of main
    std::chrono::time_point<std::chrono::high_resolution_clock> _initTime;
    float                                                       _startTime{0};
    float                                                       _deltaTime{0};

    using frameCB = std::function<void(uint32_t)>;
};

} // namespace cc
