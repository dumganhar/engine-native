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
#include "core/components/Component.h"
#include "core/scene-graph/Node.h"
#include "core/utils/IDGenerator.h"

namespace cc {

namespace {
IDGenerator idGenerator("Comp");
}

Component::Component() {
    _id = idGenerator.getNewId();
}

scene::RenderScene *Component::getRenderScene() const {
    //cjh TODO:    if (this._sceneGetter) {
    //        return this._sceneGetter();
    //    }
    return _node->getScene()->getRenderScene();
}

bool Component::isEnabledInHierarchy() const {
    return _enabled && _node != nullptr && _node->isActiveInHierarchy();
}

void Component::setEnabled(bool value) {
    if (_enabled != value) {
        _enabled = value;
        if (_node->isActiveInHierarchy()) {
            // ComponentScheduler *compScheduler = Director::getInstance()._compScheduler; // TODO(xwx): not sure use Director
            if (value) {
                // compScheduler->enableComp(this);
            } else {
                // compScheduler->disableComp(this);
            }
        }
    }
}

bool Component::destroy() {
    // TODO(xwx): EDITOR & js related logic not define
    // if (EDITOR) {
    //     // @ts-expect-error private function access
        // const depend = _node->_getDependComponent(this);
    //     if (depend) {
    //         errorID(3626,
    //                 getClassName(this), getClassName(depend));
    //         return false;
    //     }
    // }
    if (Super::destroy()) {
        if (_enabled && _node->isActiveInHierarchy()) {
            // Director::getInstance()._compScheduler->disableComp(this); // TODO(xwx): not sure Director will be used
        }
        return true;
    }
    return false;
}

void Component::_onPreDestroy() {
    // Schedules
    unscheduleAllCallbacks();

    // TODO(xwx): EDITOR not define
    // if (EDITOR && !TEST) {
    //     // @ts-expect-error expected
    //     _Scene.AssetsWatcher.stop(this);
    // }

    // onDestroy
    // Director::getInstance()._nodeActivator->destroyComp(this); // TODO(xwx): not sure Director will be used

    // do remove component
    _node->removeComponent(this);
}

Node *Component::getNode() const {
    return static_cast<Node *>(_node);
}

} // namespace cc
