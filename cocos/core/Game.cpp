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

#include "core/Game.h"
#include "core/Director.h"

namespace cc {

const std::string Game::EVENT_HIDE{"game_on_hide"};
const std::string Game::EVENT_LOW_MEMORY{"game_on_low_memory"};
const std::string Game::EVENT_SHOW{"game_on_show"};
const std::string Game::EVENT_ENGINE_INITED{"engine_inited"};
const std::string Game::EVENT_RENDERER_INITED{"renderer_inited"};
const std::string Game::EVENT_GAME_INITED{"game_inited"};
const std::string Game::EVENT_RESTART{"game_on_restart"};

void Game::step() const {
    Director::getInstance().tick(frameTime / 1000);
}

void Game::pause() {
    if (_paused) return;
    _paused = true;
    if (_intervalId) {
        // window.cAF(this._intervalId);
        _intervalId = 0;
    }
}

void Game::resume() {
    if (_paused) return;
    InputManager::getInstance().clearEvents();
    if (_intervalId) {
        // window.cAF(this._intervalId);
        _intervalId = 0;
    }
    _paused = false;
    updateCallback();
    // _intervalId = window.rAF(this._frameCB);
}

void Game::restart() {
}
//
void Game::end() const {
    SystemInfo::getInstance().close();
}

void Game::init(IGameConfig *config) {
    initConfig(config);
    // Init assetManager
    if (config->assetOptions) {
        AssetManager::getInstance()->init(*config->assetOptions);
    }

    if (!config->layers.empty()) {
        for (const auto &layer : config->layers) {
            auto bimNum = static_cast<uint32_t>(log2(layer->value));
            // Layers::getInstance()->addLayer(layer->name, bimNum);
        }
    }

    // return this._initEngine().then(() => {}
}
void Game::addPersistRootNode(scenegraph::Node *node) {
    if (!node || !scenegraph::Node::isNode(node) || !node->getUUid().empty()) {
        // debug.warnID(3800);
        return;
    }
    std::string id = node->getUUid();
    if (_persistRootNodes.find(id) == _persistRootNodes.end()) {
        scenegraph::Scene *scene = Director::getInstance().getScene();
        if (scene->isValid()) {
            auto *nodeParent = node->getParent();
            if (!nodeParent) {
                // node->setParent(scene);
            } else if (typeid(nodeParent) != typeid(scenegraph::Scene)) {
                // debug.warnID(3801);
                return;
            } else if (nodeParent != scene) {
                // debug.warnID(3802);
                return;
            } else {
                // node->_originalSceneId = scene->getUUid();
            }
        }
        _persistRootNodes[id] = node;
        // node->_presistNode = true;
        // AssetManager::getInstance()->_releaseManager->addPersistNodeRef(node);
    }
}

void Game::removePersistRootNode(scenegraph::Node *node) {
    std::string id = node ? node->getUUid() : "";
    if (node == _persistRootNodes[id]) {
        _persistRootNodes.erase(id);
        // node->_persistNode = false;
        // node->originalSceneId = "";
        // AssetManager::getInstance()->_releaseManager->_removePersistNodeRef(node);
    }
}

// TODO(xwx): _persistNode not implemented
// bool Game::isPersistRootNode(scenegraph::Node *node) const {
//     return node->_persistNode;
// }

//  @Engine loading
void Game::initEngine() {
    initDevice();
    // return Promise.resolve(legacyCC.director._init()).then(() => {}
}

//  @Time ticker section
void Game::setAnimFrame() {
    uint32_t frameRate = _frameRate;
    Application::getInstance()->setPreferredFramesPerSecond(frameRate);
    // window.rAF = window.requestAnimationFrame;
    // window.cAF = window.cancelAnimationFrame;
}

float Game::calculateDT(float now) {
    _deltaTime = now > _startTime ? (now - _startTime) / 1000.0F : 0.0F;
    if (_deltaTime > Game::DEBUG_DT_THRESHOLD) {
        _deltaTime = frameTime / 1000.0F;
    }
    _startTime = now;
    return _deltaTime;
}

void Game::runMainLoop() {
    if (!_inited /*|| (EDITOR && !GAME_VIEW)*/) {
        return;
    }
    // auto config = config();
    // debug.setDisplayStats(!!config.showFPS);
    Director::getInstance().startAnimation();
    resume();
}

// @Game loading section
void Game::initConfig(IGameConfig *config) {
    // if (typeof config.debugMode !== 'number') {
    //     config.debugMode = debug.DebugMode.NONE;
    // }
    // debug._resetDebugSetting(config.debugMode);
    this->config  = config;
    _configLoaded = true;
    _frameRate    = config->frameRate;
}

void Game::determineRenderType() {
    auto *config       = this->config;
    renderType         = Game::RENDER_TYPE_CANVAS;
    bool supportRender = false;

    auto userRenderMode = config->renderMode;
    if (userRenderMode == IGameConfig::RenderMode::AUTO) {
        // if (sys.capabilities.opengl) {
        //     renderType    = Game::RENDER_TYPE_OPENGL;
        //     supportRender = true;
        // } else if (sys.capabilities.canvas) {
        //     renderType    = Game::RENDER_TYPE_CANVAS;
        //     supportRender = true;
        // }
    } else if (userRenderMode == IGameConfig::RenderMode::CANVAS /* && sys.capabilities.canvas */) {
        supportRender = true;
    } else if (userRenderMode == IGameConfig::RenderMode::WEB_GL /* && sys.capabilities.opengl */) {
        supportRender = true;
    }

    if (!supportRender) {
        // throw new Error(debug.getError(3820, userRenderMode));
    }
}

void Game::onHide() {
    emit(Game::EVENT_HIDE);
    pause();
}

void Game::onShow() {
    emit(Game::EVENT_SHOW);
    resume();
}

void Game::setRenderPipeline(pipeline::RenderPipeline *pipeline) {
    if (!Director::getInstance().getRoot()->setRenderPipline(pipeline)) {
        setRenderPipeline(nullptr);
    }
    _rendererInitialized = true;
    safeEmit(Game::EVENT_RENDERER_INITED);
}

void Game::safeEmit(const std::string &event) {
    // TODO(xwx):
    // if (EDITOR){}
    // else
    emit(event);
}

} // namespace cc
