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

#include "core/scene-graph/Scene.h"
#include "core/Root.h"

namespace cc {

Scene::Scene(const std::string &name)
: BaseNode(name) {
    _activeInHierarchy = false;
    _renderScene       = Root::getInstance()->createScene({});
    _globals           = new SceneGlobal();
}

Scene::~Scene() {
    CC_SAFE_DELETE(_globals);
}

void Scene::load() {
    if (!_inited) {
        //cjh        if (TEST) {
        //            assert(!_activeInHierarchy, 'Should deactivate ActionManager and EventManager by default');
        //        }
        onBatchCreated(false); //cjh EDITOR && _prefabSyncedInLiveReload);
        _inited = true;
    }
    _scene = this;
    // static methode can't use this as parameter type
    walk(BaseNode::setScene);
}

void Scene::activate(bool active /* = true */) {
    //cjh    if (EDITOR) {
    //        // register all nodes to editor
    //        _registerIfAttached!(active);
    //    }
    //cjh    legacyCC.director._nodeActivator.activateNode(this, active);
    //     The test environment does not currently support the renderer
    //        if (!TEST) {
    _globals->activate();
    //        }
}

void Scene::onBatchCreated(bool dontSyncChildPrefab) {
    Super::onBatchCreated(dontSyncChildPrefab);

    int32_t len = static_cast<int32_t>(_children.size());
    for (int32_t i = 0; i < len; ++i) {
        _children[i]->setSiblingIndex(i);
        _children[i]->onBatchCreated(dontSyncChildPrefab);
    }

    //cjh    applyTargetOverrides(this);
}

bool Scene::destroy() {
    bool success = Super::destroy();
    if (success) {
        for (auto &child : _children) {
            child->setActive(false);
        }
    }

    if (_renderScene != nullptr) {
        //cjh TODO: legacyCC.director.root.destroyScene(this._renderScene);
    }

    _active            = false;
    _activeInHierarchy = false;
    return success;
}

} // namespace cc
