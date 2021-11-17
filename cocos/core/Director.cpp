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

#include "core/Director.h"
#include "core/Scheduler.h"
#include "core/scene-graph/ComponentScheduler.h"
#include "core/scene-graph/NodeActivator.h"

namespace cc {

Director *Director::instance{nullptr};
// Internal NodeEventType : 0~99
// Internal EventTypesToJS : 100~199
// Internal Game event : 200~299
// Internal Director Event Type: 300~399
const CallbacksInvoker::KeyType Director::EVENT_INIT{300};                 //{"director_init"};
const CallbacksInvoker::KeyType Director::EVENT_RESET{301};                //{"director_reset"};
const CallbacksInvoker::KeyType Director::EVENT_BEFORE_SCENE_LOADING{302}; //{"director_before_scene_loading"};
const CallbacksInvoker::KeyType Director::EVENT_BEFORE_SCENE_LAUNCH{303};  //{"director_before_scene_launch"};
const CallbacksInvoker::KeyType Director::EVENT_AFTER_SCENE_LAUNCH{304};   //{"director_after_scene_launch"};
const CallbacksInvoker::KeyType Director::EVENT_BEFORE_UPDATE{305};        //{"director_before_update"};
const CallbacksInvoker::KeyType Director::EVENT_AFTER_UPDATE{306};         //{"director_after_update"};
const CallbacksInvoker::KeyType Director::EVENT_BEFORE_DRAW{307};          //{"director_before_draw"};
const CallbacksInvoker::KeyType Director::EVENT_AFTER_DRAW{308};           //{"director_after_draw"};
const CallbacksInvoker::KeyType Director::EVENT_BEFORE_COMMIT{309};        //{"director_before_commit"};
const CallbacksInvoker::KeyType Director::EVENT_BEFORE_PHYSICS{310};       //{"director_before_physics"};
const CallbacksInvoker::KeyType Director::EVENT_AFTER_PHYSICS{311};        //{"director_after_physics"};
const CallbacksInvoker::KeyType Director::EVENT_BEGIN_FRAME{312};          //{"director_begin_frame"};
const CallbacksInvoker::KeyType Director::EVENT_END_FRAME{313};            //{"director_end_frame"};

Director::Director()
: _compScheduler{new ComponentScheduler()}, _nodeActivator{new NodeActivator()}, _scheduler{new core::Scheduler()} {
    instance = this;
}

Director::~Director() {
    CC_SAFE_DELETE(_compScheduler);
    CC_SAFE_DELETE(_nodeActivator);
    CC_SAFE_DELETE(_scheduler);
    CC_SAFE_DESTROY(_root);

    instance = nullptr;
}

void Director::init() {
#if CC_RUN_IN_CPP_MODE
    _root = new Root(gfx::Device::getInstance());
    _root->initialize();
#endif
}

void Director::runSceneImmediate(Scene *scene, const OnBeforeLoadScene &onBeforeLoadScene, const OnSceneLaunched &onLaunched) {
    //cjh    if (BUILD && DEBUG) {
    //        console.time('InitScene');
    //    }

    scene->load(); // ensure scene initialized
                   //cjh    if (BUILD && DEBUG) {
                   //        console.timeEnd('InitScene');
                   //    }
                   //    // Re-attach or replace persist nodes
                   //    if (BUILD && DEBUG) {
                   //        console.time('AttachPersist');
                   //    }

    //cjh TODO:    const persistNodeList = Object.keys(game._persistRootNodes).map((x) => game._persistRootNodes[x] as Node);
    //    for (let i = 0; i < persistNodeList.length; i++) {
    //        const node = persistNodeList[i];
    //        node.emit(legacyCC.Node.SCENE_CHANGED_FOR_PERSISTS, scene.renderScene);
    //        const existNode = scene.uuid === node._originalSceneId && scene.getChildByUuid(node.uuid);
    //        if (existNode) {
    //            // scene also contains the persist node, select the old one
    //            const index = existNode.getSiblingIndex();
    //            existNode._destroyImmediate();
    //            scene.insertChild(node, index);
    //        } else {
    //            // @ts-expect-error insert to new scene
    //            node.parent = scene;
    //        }
    //    }

    //    if (BUILD && DEBUG) {
    //        console.timeEnd('AttachPersist');
    //    }
    auto *oldScene = _scene;

    // unload scene
    //    if (BUILD && DEBUG) {
    //        console.time('Destroy');
    //    }
    if (isObjectValid(oldScene)) {
        oldScene->destroy();
    }
    //cjh    if (!EDITOR) {
    //        // auto release assets
    //        if (BUILD && DEBUG) {
    //            console.time('AutoRelease');
    //        }
    //        legacyCC.assetManager._releaseManager._autoRelease(oldScene, scene, game._persistRootNodes);
    //        if (BUILD && DEBUG) {
    //            console.timeEnd('AutoRelease');
    //        }
    //    }

    _scene = nullptr;

    // purge destroyed nodes belongs to old scene
    CCObject::deferredDestroy();
    //cjh    if (BUILD && DEBUG) { console.timeEnd('Destroy'); }

    if (onBeforeLoadScene != nullptr) {
        onBeforeLoadScene();
    }
    emit(Director::EVENT_BEFORE_SCENE_LAUNCH, scene);

    // Run an Entity Scene
    _scene = scene;

    //    if (BUILD && DEBUG) {
    //        console.time('Activate');
    //    }

    scene->activate();
    //    if (BUILD && DEBUG) {
    //        console.timeEnd('Activate');
    //    }
    // start scene
    if (_root != nullptr) {
        _root->resetCumulativeTime();
    }

    startAnimation();
    if (onLaunched != nullptr) {
        onLaunched(nullptr, scene);
    }
    emit(Director::EVENT_AFTER_SCENE_LAUNCH, scene);
}

void Director::runSceneImmediate(SceneAsset *sceneAsset, const OnBeforeLoadScene &onBeforeLoadScene, const OnSceneLaunched &onLaunched) {
    runSceneImmediate(sceneAsset->getScene(), onBeforeLoadScene, onLaunched);
}

void Director::runScene(Scene *scene, const OnBeforeLoadScene &onBeforeLoadScene, const OnSceneLaunched &onLaunched) {
}

void Director::runScene(SceneAsset *sceneAsset, const OnBeforeLoadScene &onBeforeLoadScene, const OnSceneLaunched &onLaunched) {
}

void Director::mainLoop(float now) {
}

void Director::tick(float dt) {
    if (!_invalid) {
        emit(Director::EVENT_BEGIN_FRAME);
        //cjh        if (!EDITOR) {
        //            inputManager.frameDispatchEvents();
        //        }
        // Update
        if (!_paused) {
            emit(Director::EVENT_BEFORE_UPDATE);
            // Call start for new added components
            _compScheduler->startPhase();
            // Update for components
            _compScheduler->updatePhase(dt);
            // Update systems
            for (auto &&system : _systems) {
                system->update(dt);
            }
            // Late update for components
            _compScheduler->lateUpdatePhase(dt);
            // User can use this event to do things after update
            emit(Director::EVENT_AFTER_UPDATE);
            // Destroy entities that have been removed recently
            CCObject::deferredDestroy();

            // Post update systems
            for (auto &&system : _systems) {
                system->postUpdate(dt);
            }
        }

        emit(Director::EVENT_BEFORE_DRAW);
        // The test environment does not currently support the renderer
        if (true) { //cjh }!TEST) {
            _root->frameMove(dt, _totalFrames);
        }

        emit(Director::EVENT_AFTER_DRAW);

        //cjh TODO:        eventManager.frameUpdateListeners();
        Node::resetChangedFlags();
        Node::clearNodeArray();
        emit(Director::EVENT_END_FRAME);
        _totalFrames++;
    }
}

} // namespace cc
