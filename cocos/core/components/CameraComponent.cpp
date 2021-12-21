#include "core/components/CameraComponent.h"
#include "2d/framework/UITransform.h"
#include "core/Root.h"
#include "core/assets/RenderTexture.h"
#include "core/platform/View.h"
#include "core/scene-graph/Node.h"
#include "scene/Camera.h"

namespace cc {

void Camera::setInEditorMode(bool value) {
    _inEditorMode = value;
    if (_camera != nullptr) {
        _camera->changeTargetWindow(value ? Root::getInstance()->getMainWindow() : Root::getInstance()->getTempWindow());
    }
}

void Camera::onLoad() {
    createCamera();
}

void Camera::onEnable() {
    _node->setChangedFlags(_node->getChangedFlags() | static_cast<uint32_t>(TransformBit::POSITION)); // trigger camera matrix update
    if (_camera != nullptr) {
        attachToScene();
    }
}

void Camera::onDisable() {
    if (_camera != nullptr) {
        detachFromScene();
    }
}

void Camera::onDestroy() {
    if (_camera != nullptr) {
        _camera->destroy();
        _camera = nullptr;
    }

    if (_targetTexture != nullptr) {
        //cjh TODO:        _targetTexture.off('resize');
    }
}

geometry::Ray *Camera::screenPointToRay(geometry::Ray *out, float x, float y) {
    if (_camera != nullptr) {
        _camera->screenPointToRay(out, x, y);
    }

    return out;
}

const Vec3 &Camera::worldToScreen(Vec3 &out, const Vec3 &worldPos) {
    if (_camera != nullptr) {
        _camera->worldToScreen(out, worldPos);
    }
    return out;
}

const Vec3 &Camera::screenToWorld(Vec3 &out, const Vec3 &screenPos) {
    if (_camera != nullptr) {
        _camera->screenToWorld(out, screenPos);
    }
    return out;
}

Vec3 Camera::convertToUINode(const Vec3 &wpos, Node *uiNode) {
    Vec3 out;
    if (!_camera) {
        return out;
    }

    Vec3 tempVec3;
    worldToScreen(tempVec3, wpos);
    auto *cmp        = uiNode->getComponent<UITransform>();
    auto &view       = View::getInstance(); //cjh TODO: Is view implemented?
    auto  designSize = view.getVisibleSize();
    float xoffset    = tempVec3.x - static_cast<float>(_camera->getWidth()) * 0.5F;
    float yoffset    = tempVec3.y - static_cast<float>(_camera->getHeight()) * 0.5F;
    tempVec3.x       = xoffset / view.getScaleX() + designSize.width * 0.5F;
    tempVec3.y       = yoffset / view.getScaleY() + designSize.height * 0.5F;

    if (cmp) {
        //cjh TODO:        cmp->convertToNodeSpaceAR(out, tempVec3);
    }

    return out;
}

void Camera::createCamera() {
    if (nullptr == _camera) {
        _camera = Root::getInstance()->createCamera();

        scene::ICameraInfo info;
        info.name       = _node->getName();
        info.node       = getNode();
        info.projection = _projection;
        info.window     = _inEditorMode ? Root::getInstance()->getMainWindow() : Root::getInstance()->getTempWindow();
        info.priority   = _priority,

        _camera->initialize(info);

        _camera->setViewport(Vec4{_rect.origin.x, _rect.origin.y, _rect.size.width, _rect.size.height});
        _camera->setFovAxis(_fovAxis);
        _camera->setFov(static_cast<float>(mathutils::toRadian(_fov)));
        _camera->setOrthoHeight(_orthoHeight);
        _camera->setNearClip(_near);
        _camera->setFarClip(_far);
        _camera->setClearColor(gfx::Color{static_cast<float>(_color.r) / 255.F, static_cast<float>(_color.g) / 255.F, static_cast<float>(_color.b) / 255.F, static_cast<float>(_color.a) / 255.F});
        _camera->setClearDepth(_depth);
        _camera->setClearStencil(_stencil);
        _camera->setClearFlag(static_cast<gfx::ClearFlags>(_clearFlags));
        _camera->setVisibility(_visibility);
        _camera->setAperture(_aperture);
        _camera->setShutter(_shutter);
        _camera->setIso(_iso);
    }

    updateTargetTexture();
}

void Camera::attachToScene() {
    if (!_node->getScene() || !_camera) {
        return;
    }
    if (_camera && _camera->getScene()) {
        _camera->getScene()->removeCamera(_camera);
    }
    auto *rs = getRenderScene();
    rs->addCamera(_camera);
}

void Camera::detachFromScene() {
    if (_camera && _camera->getScene()) {
        _camera->getScene()->removeCamera(_camera);
    }
}

void Camera::checkTargetTextureEvent(RenderTexture *old) {
    //    const resizeFunc = (window: RenderWindow) => {
    //        if (_camera) {
    //            _camera.setFixedSize(window.width, window.height);
    //        }
    //    };
    //
    //cjh TODO:    if (old) {
    //        old.off('resize');
    //    }
    //
    //    if (_targetTexture) {
    //        _targetTexture.on('resize', resizeFunc, this);
    //    }
}

void Camera::updateTargetTexture() {
    if (!_camera) {
        return;
    }

    if (_targetTexture) {
        auto *window = _targetTexture->getWindow();
        _camera->changeTargetWindow(window);
        _camera->setFixedSize(window->getWidth(), window->getHeight());
    }
}

} // namespace cc
