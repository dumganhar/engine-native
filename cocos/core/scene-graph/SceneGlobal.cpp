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

#include "core/scene-graph/SceneGlobal.h"
#include "core/Root.h"
#include "scene/Ambient.h"
#include "scene/Fog.h"
#include "scene/Shadow.h"
#include "scene/Skybox.h"

namespace cc {

SceneGlobal::SceneGlobal() {
    _ambientInfo = new scene::AmbientInfo();
    _shadowInfo  = new scene::ShadowInfo();
    _skyboxInfo  = new scene::SkyboxInfo();
    _fogInfo     = new scene::FogInfo();
}

SceneGlobal::~SceneGlobal() {
    CC_SAFE_DELETE(_ambientInfo);
    CC_SAFE_DELETE(_shadowInfo);
    CC_SAFE_DELETE(_skyboxInfo);
    CC_SAFE_DELETE(_fogInfo);
}

void SceneGlobal::activate() {
    auto *sceneData = Root::getInstance()->getPipeline()->getPipelineSceneData();
    _ambientInfo->activate(sceneData->getAmbient());
    _skyboxInfo->activate(sceneData->getSkybox());
    _shadowInfo->activate(sceneData->getShadow());
    _fogInfo->activate(sceneData->getFog());
}

} // namespace cc
