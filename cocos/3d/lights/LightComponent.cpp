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
#include "3d/lights/LightComponent.h"
#include "scene/DirectionalLight.h"
#include "scene/SphereLight.h"
#include "scene/SpotLight.h"

namespace cc {
Light::Light() : Super() {
}
void Light::createLight() {
    if (_light == nullptr) {
        _light = Root::getInstance()->createLight<scene::Light>();
    }
    initializeLight();
}

void Light::initializeLight() {
    setColor(_color);
    setUseColorTemperature(_useColorTemperature);
    setColorTemperature(_colorTemperature);
    _light->setNode(_node);
    _light->setBaked(isBaked());
}

void Light::setColor(const Color &val) {
    _color = val;
    if (_light != nullptr) {
        _light->setColor(Vec3(static_cast<float>(val.r) / 255.F, static_cast<float>(val.g) / 255.F, static_cast<float>(val.b) / 255.F));
    }
}
void Light::destroyLight() {
    if (_light != nullptr) {
        Root::getInstance()->destroyLight(_light);
        _light = nullptr;
    }
}

void Light::attachToScene() {
    detachFromScene();
    if (_light != nullptr && _light->getScene() == nullptr && _node->getScene() != nullptr) {
        scene::RenderScene *renderScene = getRenderScene();
        switch (_type) {
            case scene::LightType::DIRECTIONAL:
                renderScene->addDirectionalLight(static_cast<scene::DirectionalLight *>(_light));
                renderScene->setMainLight(static_cast<scene::DirectionalLight *>(_light));
                break;
            case scene::LightType::SPHERE:
                renderScene->addSphereLight(static_cast<scene::SphereLight *>(_light));
                break;
            case scene::LightType::SPOT:
                renderScene->addSpotLight(static_cast<scene::SpotLight *>(_light));
                break;
            default:
                break;
        }
    }
}

void Light::detachFromScene() {
    if (_light != nullptr && _light->getScene() != nullptr) {
        scene::RenderScene *renderScene = _light->getScene();
        switch (_type) {
            case scene::LightType::DIRECTIONAL:
                renderScene->removeDirectionalLight(dynamic_cast<scene::DirectionalLight *>(_light));
                renderScene->unsetMainLight(dynamic_cast<scene::DirectionalLight *>(_light));
                break;
            case scene::LightType::SPHERE:
                renderScene->removeSphereLight(dynamic_cast<scene::SphereLight *>(_light));
                break;
            case scene::LightType::SPOT:
                renderScene->removeSpotLight(dynamic_cast<scene::SpotLight *>(_light));
                break;
            default:
                break;
        }
    }
}

} // namespace cc
