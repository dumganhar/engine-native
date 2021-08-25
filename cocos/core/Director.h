/*
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2020 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
#pragma once

/* spell-checker:words COORD, Quesada, INITED, Renerer */

/**
 * @packageDocumentation
 * @module core
 */

#include <any>
#include <iostream>
#include <variant>
#include <vector>

#include "base/Macros.h"
#include "core/Game.h"
#include "core/Root.h"
#include "core/Scheduler.h"
#include "core/asset-manager/AssetManager.h"
#include "core/assets/SceneAsset.h"
#include "core/event/EventEmitter.h"
#include "core/scene-graph/BaseNode.h"
#include "core/scene-graph/ComponentScheduler.h"
#include "core/scene-graph/NodeActivator.h"
#include "core/scene-graph/Scene.h"
#include "math/Vec2.h"
// ----------------------------------------------------------------------------------------------------------------------

/**
 * @en
 * ATTENTION: USE `director` INSTEAD OF `Director`.
 * `director` is a singleton object which manage your game's logic flow.
 * Since the `director` is a singleton, you don't need to call any constructor or create functions,
 * the standard way to use it is by calling:
 * `director.methodName();`
 * It creates and handle the main Window and manages how and when to execute the Scenes.
 *
 * @zh
 * 注意：用 `director` 代替 `Director`。
 * `director` 一个管理你的游戏的逻辑流程的单例对象。
 * 由于 `director` 是一个单例，你不需要调用任何构造函数或创建函数，
 * 使用它的标准方法是通过调用：
 * `director.methodName();`
 * 它创建和处理主窗口并且管理什么时候执行场景。
 */
namespace cc {

/**
 * typedef std::function<void*()> OnBeforeLoadScene;
 * typedef std::function<void*()> OnUnload;
 * typedef std::function<void*(_exception, SceneAsset*)> OnSceneLoaded;
 * typedef std::function<void*(_exception, SceneAsset*)> OnSceneLaunched;
 * typedef std::function<void*(uint32_t, uint32_t，std::any)> OnLoadSceneProgress;
 * @param completedCount - The number of the items that are already completed.
 * @param totalCount - The total number of the items.
 * @param item - The latest item which flow out the pipeline.
 */

class Director : EventEmitter {
public:
    /**
     * @en The event which will be triggered when the singleton of Director initialized.
     * @zh Director 单例初始化时触发的事件 
    */

    static std::string EVENT_INIT;

    /**
     * @en The event which will be triggered when the singleton of Director reset.
     * @zh Director 单例重置时触发的事件
     * @event Director.EVENT_RESET
     */
    static std::string EVENT_RESET;

    /**
     * @en The event which will be triggered before loading a new scene.
     * @zh 加载新场景之前所触发的事件。
     * @event Director.EVENT_BEFORE_SCENE_LOADING
     * @param {String} sceneName - The loading scene name
     */
    static std::string EVENT_BEFORE_SCENE_LOADING;

    /**
     * @en The event which will be triggered before launching a new scene.
     * @zh 运行新场景之前所触发的事件。
     * @event Director.EVENT_BEFORE_SCENE_LAUNCH
     * @param {String} sceneName - New scene which will be launched
     */
    static std::string EVENT_BEFORE_SCENE_LAUNCH;

    /**
     * @en The event which will be triggered after launching a new scene.
     * @zh 运行新场景之后所触发的事件。
     * @event Director.EVENT_AFTER_SCENE_LAUNCH
     * @param {String} sceneName - New scene which is launched
     */
    static std::string EVENT_AFTER_SCENE_LAUNCH;

    /**
     * @en The event which will be triggered at the beginning of every frame.
     * @zh 每个帧的开始时所触发的事件。
     * @event Director.EVENT_BEFORE_UPDATE
     */
    static std::string EVENT_BEFORE_UPDATE;

    /**
     * @en The event which will be triggered after engine and components update logic.
     * @zh 将在引擎和组件 “update” 逻辑之后所触发的事件。
     * @event Director.EVENT_AFTER_UPDATE
     */
    static std::string EVENT_AFTER_UPDATE;

    /**
     * @en The event which will be triggered before the rendering process.
     * @zh 渲染过程之前所触发的事件。
     * @event Director.EVENT_BEFORE_DRAW
     */
    static std::string EVENT_BEFORE_DRAW;

    /**
     * @en The event which will be triggered after the rendering process.
     * @zh 渲染过程之后所触发的事件。
     * @event Director.EVENT_AFTER_DRAW
     */
    static std::string EVENT_AFTER_DRAW;

    /**
     * @en The event which will be triggered before the pipeline render commit.
     * @zh 当前渲染帧提交前所触发的事件。
     * @event Director.EVENT_BEFORE_COMMIT
     */
    static std::string EVENT_BEFORE_COMMIT;

    /**
     * The event which will be triggered before the physics process.<br/>
     * 物理过程之前所触发的事件。
     * @event Director.EVENT_BEFORE_PHYSICS
     */
    static std::string EVENT_BEFORE_PHYSICS;

    /**
     * The event which will be triggered after the physics process.<br/>
     * 物理过程之后所触发的事件。
     * @event Director.EVENT_AFTER_PHYSICS
     */
    static std::string EVENT_AFTER_PHYSICS;

    /**
     * The event which will be triggered at the frame begin.<br/>
     * 一帧开始时所触发的事件。
     * @event Director.EVENT_BEGIN_FRAME
     */
    static std::string EVENT_BEGIN_FRAME;

    /**
     * The event which will be triggered at the frame end.<br/>
     * 一帧结束之后所触发的事件。
     * @event Director.EVENT_END_FRAME
     */
    static std::string EVENT_END_FRAME;

    static Director &getInstance() {
        static Director instance;
        return instance;
    }

    scenegraph::ComponentScheduler *_compScheduler{nullptr};
    scenegraph::NodeActivator *     _nodeActivator{nullptr};

    /**
     * @en End the life of director in the next frame
     * @zh 执行完当前帧后停止 director 的执行
     */
    void end();

    /**
     * @en Pause the director's ticker, only involve the game logic execution.<br>
     * It won't pause the rendering process nor the event manager.<br>
     * If you want to pause the entire game including rendering, audio and event,<br>
     * please use `game.pause`.
     * @zh 暂停正在运行的场景，该暂停只会停止游戏逻辑执行，但是不会停止渲染和 UI 响应。<br>
     * 如果想要更彻底得暂停游戏，包含渲染，音频和事件，请使用 `game.pause` 。
     */
    void pause();

    /**
     * @en Purge the `director` itself, including unschedule all schedule,<br>
     * remove all event listeners, clean up and exit the running scene, stops all animations, clear cached data.
     * @zh 清除 `director` 本身，包括停止所有的计时器，<br>
     * 移除所有的事件监听器，清理并退出当前运行的场景，停止所有动画，清理缓存数据。
     */
    void purgeDirector();

    /**
     * @en Reset the director, can be used to restart the director after purge
     * @zh 重置此 Director，可用于在清除后重启 Director。
     */
    void reset();

    /**
     * @en
     * Run a scene. Replaces the running scene with a new one or enter the first scene.<br>
     * The new scene will be launched immediately.
     * @zh 运行指定场景。将正在运行的场景替换为（或重入为）新场景。新场景将立即启动。
     * @param scene - The need run scene.
     * @param onBeforeLoadScene - The function invoked at the scene before loading.
     * @param onLaunched - The function invoked at the scene after launch.
     */
    void runSceneImmediate(const std::variant<Scene, SceneAsset> &, const std::function<void *()> &onBeforeLoadScene, const std::function<void *()> &onLaunched);
    /**
     * @en
     * Run a scene. Replaces the running scene with a new one or enter the first scene.<br>
     * The new scene will be launched at the end of the current frame.<br>
     * @zh 运行指定场景。
     * @param scene - The need run scene.
     * @param onBeforeLoadScene - The function invoked at the scene before loading.
     * @param onLaunched - The function invoked at the scene after launch.
     * @private
     */
    void runScene(const std::variant<Scene *, SceneAsset *> &scene, const std::function<void *()> &onBeforeLoadScene, const std::function<void *()> &onLaunched);

    /**
     * @en Loads the scene by its name.
     * @zh 通过场景名称进行加载场景。
     *
     * @param sceneName - The name of the scene to load.
     * @param onLaunched - callback, will be called after scene launched.
     * @return if error, return false
     */
    bool loadScene(const std::string &sceneName, const std::function<void *()> &onLaunched, const std::function<void *()> &onUnloaded);
    /**
     * @en
     * Pre-loads the scene to reduces loading time. You can call this method at any time you want.<br>
     * After calling this method, you still need to launch the scene by `director.loadScene`.<br>
     * It will be totally fine to call `director.loadScene` at any time even if the preloading is not<br>
     * yet finished, the scene will be launched after loaded automatically.
     * @zh 预加载场景，你可以在任何时候调用这个方法。
     * 调用完后，你仍然需要通过 `director.loadScene` 来启动场景，因为这个方法不会执行场景加载操作。<br>
     * 就算预加载还没完成，你也可以直接调用 `director.loadScene`，加载完成后场景就会启动。
     * @param sceneName 场景名称。
     * @param onLoaded 加载回调。
     */
    void preloadScene(const std::string &sceneName, const std::function<void *()> &onLoaded);

    /**
     * @en
     * Pre-loads the scene to reduces loading time. You can call this method at any time you want.<br>
     * After calling this method, you still need to launch the scene by `director.loadScene`.<br>
     * It will be totally fine to call `director.loadScene` at any time even if the preloading is not<br>
     * yet finished, the scene will be launched after loaded automatically.
     * @zh 预加载场景，你可以在任何时候调用这个方法。
     * 调用完后，你仍然需要通过 `director.loadScene` 来启动场景，因为这个方法不会执行场景加载操作。<br>
     * 就算预加载还没完成，你也可以直接调用 `director.loadScene`，加载完成后场景就会启动。
     * @param sceneName 场景名称。
     * @param onProgress 加载进度回调。
     * @param onLoaded 加载回调。
     */
    template <typename... A, typename... B>
    void preloadScene(const std::string &sceneName, const std::function<void *(A...)> &onProgress, const std::function<void *(B...)> &onLoaded);

    /**
     * @en Resume game logic execution after pause, if the current scene is not paused, nothing will happen.
     * @zh 恢复暂停场景的游戏逻辑，如果当前场景没有暂停将没任何事情发生。
     */
    inline void resume() { _paused = false; }

    Root *getRoot() const { return _root; }

    /**
     * @en Returns current logic Scene.
     * @zh 获取当前逻辑场景。
     */
    scenegraph::Scene *getScene() const { return _scene; }

    /**
     * @en Returns the delta time since last frame.
     * @zh 获取上一帧的增量时间。
     * @deprecated since v3.3.0, please use game.deltaTime instead
     */
    float getDeltaTime() const;

    /**
     * @en Returns the total passed time since game start, unit: ms
     * @zh 获取从游戏开始到现在总共经过的时间，单位为 ms
     * @deprecated since v3.3.0, please use game.totalTime instead
     */
    float getTotalTime() const;
    /**
     * @en Returns the current time.
     * @zh 获取当前帧的时间。
     * @deprecated since v3.3.0, please use game.frameStartTime instead
     */
    float getCurrentTime() const;

    /**
     * @en Returns how many frames were called since the director started.
     * @zh 获取 director 启动以来游戏运行的总帧数。
     */
    inline uint32_t getTotalFrames() const { return _totalFrames; }

    /**
     * @en Returns whether or not the Director is paused.
     * @zh 是否处于暂停状态。
     */
    inline bool isPaused() const { return _paused; }

    /**
     * @en Returns the scheduler associated with this director.
     * @zh 获取和 director 相关联的调度器。
     */
    inline core::Scheduler *getScheduler() { return _scheduler; }

    /**
     * @en Sets the scheduler associated with this director.
     * @zh 设置和 director 相关联的调度器。
     */
    void setScheduler(core::Scheduler *scheduler);
    /**
     * @en Register a system.
     * @zh 注册一个系统。
     */
    void registerSystem(const std::string &name, core::System *sys, uint32_t priority);
    void unregisterSystem(core::System *sys);

    /**
     * @en get a system.
     * @zh 获取一个 system。
     */
    core::System *getSystem(const std::string &name) const;

    /**
     * @en Returns the `AnimationManager` associated with this director. Please use getSystem(AnimationManager.ID)
     * @zh 获取和 director 相关联的 `AnimationManager`（动画管理器）。请使用 getSystem(AnimationManager.ID) 来替代
     * @deprecated since 3.0.0
     */
    std::string getAnimationManager() const;

    // Loop management
    /**
     * @en Starts the director
     * @zh 开始执行游戏逻辑
     */
    inline void startAnimation() {
        _invalid = false;
    }

    /**
     * @en Stops the director
     * @zh 停止执行游戏逻辑，每帧渲染会继续执行
     */
    inline void stopAnimation() {
        _invalid = true;
    }

    /**
     * @en Run main loop of director
     * @zh 运行主循环
     * @deprecated please use [tick] instead
     */
    void mainLoop(float now);

    /**
     * @en Run main loop of director
     * @zh 运行主循环
     */
    void tick(float dt);

    Director();
    ~Director();

private:
    bool                        _invalid{false};
    bool                        _paused{false};
    Root *                      _root{nullptr};
    std::string                 _loadingScene;
    uint32_t                    _totalFrames{0};
    core::Scheduler *           _scheduler{nullptr};
    std::vector<core::System *> _systems;

    scenegraph::Scene *_scene{nullptr};
    void               _initOnRendererInitialized();
    //TODO: return Promise in js, c++ need adaption
    void _init();
};

} // namespace cc
