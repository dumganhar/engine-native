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

#include "core/Root.h"
#include "core/Director.h"
#include "core/event/CallbacksInvoker.h"
#include "core/event/EventTypesToJS.h"
#include "renderer/gfx-base/GFXDef.h"
#include "renderer/pipeline/deferred/DeferredPipeline.h"
#include "renderer/pipeline/forward/ForwardPipeline.h"

namespace cc {

namespace {
Root *instance = nullptr;
}

Root *Root::getInstance() {
    return instance;
}

Root::Root(gfx::Device *device)
: _device(device) {
    instance        = this;
    _eventProcessor = new CallbacksInvoker();
    //TODO: minggo
    //    this._dataPoolMgr = legacyCC.internal.DataPoolManager && new legacyCC.internal.DataPoolManager(device) as DataPoolManager;
    _cameraPool = new memop::Pool<scene::Camera>([this]() { return new scene::Camera(_device); },
                                                 4);
}

Root::~Root() {
    instance = nullptr;
    delete _cameraPool;
    CC_SAFE_DELETE(_eventProcessor);
}

void Root::initialize() {
    gfx::ColorAttachment colorAttachment;

    gfx::DepthStencilAttachment depthStencilAttachment;
    gfx::RenderPassInfo         renderPassInfo;
    renderPassInfo.colorAttachments.emplace_back(colorAttachment);
    renderPassInfo.depthStencilAttachment.depthStoreOp   = gfx::StoreOp::DISCARD;
    renderPassInfo.depthStencilAttachment.stencilStoreOp = gfx::StoreOp::DISCARD;

    scene::IRenderWindowInfo info{"rootMainWindow",
                                  _device->getWidth(),
                                  _device->getHeight(),
                                  renderPassInfo,
                                  -1, // always on screen
                                  false};
    _mainWindow = createWindow(info);

    _curWindow = _mainWindow;

    //TODO: minggo
    //    return Promise.resolve(builtinResMgr.initBuiltinRes(this._device)).then(() => {
    //        legacyCC.view.on('design-resolution-changed', () => {
    //            const width = legacyCC.game.canvas.width;
    //            const height = legacyCC.game.canvas.height;
    //            this.resize(width, height);
    //        }, this);
    //    });
}

void Root::destroy() {
    destroyScenes();

    CC_SAFE_DESTROY(_pipeline);
    //TODO: minggo
    //    CC_SAFE_DESTROY(_batcher2D);
    if (_mainWindow != _curWindow) {
        CC_SAFE_DELETE(_mainWindow);
    }
    CC_SAFE_DELETE(_curWindow);

    //TODO: minggo
    //    this.dataPoolManager.clear();
}

void Root::resize(uint32_t width, uint32_t height) {
    _device->resize(width, height);
    _mainWindow->resize(width, height);
    for (auto *window : _windows) {
        if (window->shouldSyncSizeWithSwapchain()) {
            window->resize(width, height);
        }
    }
    if (_pipeline) {
        _pipeline->resize(width, height);
    }
}

bool Root::setRenderPipeline(pipeline::RenderPipeline *rppl /* = nullptr*/) {
    if (rppl != nullptr && dynamic_cast<pipeline::DeferredPipeline *>(rppl) != nullptr) {
        _useDeferredPipeline = true;
    }

    if (!rppl) {
        rppl = new pipeline::ForwardPipeline();
        rppl->initialize({});
    }

    _pipeline = rppl;
    if (!_pipeline->activate()) {
        CC_SAFE_DESTROY(_pipeline);
        return false;
    }

    // TODO: minggo
    auto *scene = Director::getInstance()->getScene();
    if (scene) {
        scene->getSceneGlobals()->activate();
    }

    onGlobalPipelineStateChanged();

    _eventProcessor->emit(EventTypesToJS::ROOT_BATCH2D_INIT, this);
    //TODO: minggo
    //    if (!_batcher) {
    //        _batcher = new Batcher2D(this);
    //        if (!this._batcher.initialize()) {
    //            this.destroy();
    //            return false;
    //        }
    //    }

    return true;
}

void Root::onGlobalPipelineStateChanged() {
    for (auto *scene : _scenes) {
        scene->onGlobalPipelineStateChanged();
    }

    _pipeline->getPipelineSceneData()->onGlobalPipelineStateChanged();
}

void Root::activeWindow(scene::RenderWindow *window) {
    _curWindow = window;
}

void Root::resetCumulativeTime() {
    _cumulativeTime = 0;
}

void Root::frameMove(float deltaTime, int32_t totalFrames) {

    _frameTime = deltaTime;

    ++_frameCount;
    _cumulativeTime += deltaTime;
    _fpsTime += deltaTime;
    if (_fpsTime > 1.0F) {
        _fps        = _frameCount;
        _frameCount = 0;
        _fpsTime    = 0.0;
    }

    for (auto *scene : _scenes) {
        scene->removeBatches();
    }

    _eventProcessor->emit(EventTypesToJS::ROOT_BATCH2D_UPDATE, this); //cjh added for sync logic in ts.

    //TODO: minggo
    //    if (_batcher) {
    //        _batcher.update();
    //    }

    //
    std::vector<scene::Camera *> cameraList;
    for (auto *window : _windows) {
        window->extractRenderCameras(cameraList);
    }

    if (_pipeline != nullptr && !cameraList.empty()) {
        _device->acquire();
        //cjh TODO:        const stamp = legacyCC.director.getTotalFrames();
        uint32_t stamp = totalFrames;

        _eventProcessor->emit(EventTypesToJS::ROOT_BATCH2D_UPLOAD_BUFFERS, this);
        //                if (_batcher != nullptr) {
        //                    _batcher->uploadBuffers();
        //                }

        for (auto *scene : _scenes) {
            scene->update(stamp);
        }

        _eventProcessor->emit(EventTypesToJS::DIRECTOR_BEFORE_COMMIT, this);

        std::stable_sort(cameraList.begin(), cameraList.end(), [](const auto *a, const auto *b) {
            return a->getPriority() < b->getPriority();
        });
        _pipeline->render(cameraList);
        _device->present();
    }

    _eventProcessor->emit(EventTypesToJS::ROOT_BATCH2D_RESET, this);
    //cjh TODO:    if (this._batcher) this._batcher.reset();
}

scene::RenderWindow *Root::createWindow(scene::IRenderWindowInfo &info) {
    auto *window = new scene::RenderWindow();

    window->initialize(_device, info);
    _windows.emplace_back(window);
    return window;
}

void Root::destroyWindow(scene::RenderWindow *window) {
    auto it = std::find(_windows.begin(), _windows.end(), window);
    if (it != _windows.end()) {
        CC_SAFE_DESTROY(*it);
        _windows.erase(it);
    }
}

void Root::destroyWindows() {
    for (auto *window : _windows) {
        CC_SAFE_DESTROY(window);
    }
    _windows.clear();
}

scene::RenderScene *Root::createScene(const scene::IRenderSceneInfo &info) {
    auto *scene = new scene::RenderScene();
    scene->initialize(info);
    _scenes.emplace_back(scene);
    return scene;
}

void Root::destroyScene(scene::RenderScene *scene) {
    auto it = std::find(_scenes.begin(), _scenes.end(), scene);
    if (it != _scenes.end()) {
        CC_SAFE_DESTROY(*it);
        _scenes.erase(it);
    }
}

void Root::destroyScenes() {
    for (auto *scene : _scenes) {
        CC_SAFE_DESTROY(scene);
    }
    _scenes.clear();
}

} // namespace cc
