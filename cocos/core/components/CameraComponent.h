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

#include "core/components/Component.h"
#include "math/Color.h"
#include "math/Geometry.h"
#include "math/Utils.h"
#include "renderer/pipeline/Define.h"
#include "scene/Camera.h"

namespace cc {

class RenderTexture;

namespace geometry {
class Ray;
}

namespace scene {
class Camera;
}

class Camera : public Component {
public:
    enum class ClearFlag {
        SKYBOX      = scene::Camera::SKYBOX_FLAG | static_cast<int32_t>(gfx::ClearFlagBit::DEPTH_STENCIL),
        SOLID_COLOR = static_cast<int32_t>(gfx::ClearFlagBit::ALL),
        DEPTH_ONLY  = static_cast<int32_t>(gfx::ClearFlagBit::DEPTH_STENCIL),
        DONT_CLEAR  = static_cast<int32_t>(gfx::ClearFlagBit::NONE)
    };

    using ProjectionType = scene::CameraProjection;
    using FOVAxis        = scene::CameraFOVAxis;
    using Aperture       = scene::CameraAperture;
    using Shutter        = scene::CameraShutter;
    using ISO            = scene::CameraISO;

    static constexpr const char *TARGET_TEXTURE_CHANGE{"tex-change"};

    Camera()           = default;
    ~Camera() override = default;

    inline scene::Camera *getCamera() const {
        return _camera;
    }

    /**
     * @en Render priority of the camera. Cameras with higher depth are rendered after cameras with lower depth.
     * @zh 相机的渲染优先级，值越小越优先渲染。
     */
    inline uint32_t getPriority() const {
        return _priority;
    }

    inline void setPriority(uint32_t val) {
        _priority = val;
        if (_camera != nullptr) {
            _camera->setPriority(val);
        }
    }
    /**
     * @en Visibility mask, declaring a set of node layers that will be visible to this camera.
     * @zh 可见性掩码，声明在当前相机中可见的节点层级集合。
     */
    inline uint32_t getVisibility() const {
        return _visibility;
    }

    inline void setVisibility(uint32_t val) {
        _visibility = val;
        if (_camera != nullptr) {
            _camera->setVisibility(val);
        }
    }

    /**
     * @en Clearing flags of the camera, specifies which part of the framebuffer will be actually cleared every frame.
     * @zh 相机的缓冲清除标志位，指定帧缓冲的哪部分要每帧清除。
     */
    inline ClearFlag getClearFlags() const {
        return _clearFlags;
    }

    inline void setClearFlags(ClearFlag val) {
        _clearFlags = val;
        if (_camera != nullptr) {
            //cjh TODO:            _camera->setClearFlag(val);
        }
    }

    /**
     * @en Clearing color of the camera.
     * @zh 相机的颜色缓冲默认值。
     */
    inline const Color &getClearColor() const {
        return _color;
    }

    inline void setClearColor(const Color &val) {
        _color.set(val);
        if (_camera != nullptr) {
            _camera->setClearColor(gfx::Color{val.r / 255.F, val.g / 255.F, val.b / 255.F, val.a / 255.F});
        }
    }

    /**
     * @en Clearing depth of the camera.
     * @zh 相机的深度缓冲默认值。
     */
    inline float getClearDepth() const {
        return _depth;
    }

    inline void setClearDepth(float val) {
        _depth = val;
        if (_camera != nullptr) {
            _camera->setClearDepth(val);
        }
    }

    /**
     * @en Clearing stencil of the camera.
     * @zh 相机的模板缓冲默认值。
     */
    inline float getClearStencil() const {
        return _stencil;
    }

    inline void setClearStencil(float val) {
        _stencil = val;
        if (_camera != nullptr) {
            _camera->setClearStencil(val);
        }
    }

    /**
     * @en Projection type of the camera.
     * @zh 相机的投影类型。
     */
    inline ProjectionType getProjection() const {
        return _projection;
    }

    inline void setProjection(ProjectionType val) {
        _projection = val;
        if (_camera != nullptr) {
            _camera->setProjectionType(val);
        }
    }

    /**
     * @en The axis on which the FOV would be fixed regardless of screen aspect changes.
     * @zh 指定视角的固定轴向，在此轴上不会跟随屏幕长宽比例变化。
     */
    inline FOVAxis getFovAxis() const {
        return _fovAxis;
    }

    inline void setFovAxis(FOVAxis val) {
        if (val == _fovAxis) {
            return;
        }

        _fovAxis = val;
        if (_camera != nullptr) {
            _camera->setFovAxis(val);
            if (val == scene::CameraFOVAxis::VERTICAL) {
                _fov = _fov * _camera->getAspect();
            } else {
                _fov = _fov / _camera->getAspect();
            }
        }
    }

    /**
     * @en Field of view of the camera.
     * @zh 相机的视角大小。
     */
    inline float getFov() const {
        return _fov;
    }

    inline void setFov(float val) {
        _fov = val;
        if (_camera != nullptr) {
            _camera->setFov(mathutils::toRadian(val));
        }
    }

    /**
     * @en Viewport height in orthographic mode.
     * @zh 正交模式下的相机视角高度。
     */
    inline float getOrthoHeight() const {
        return _orthoHeight;
    }

    inline void setOrthoHeight(float val) {
        _orthoHeight = val;
        if (_camera != nullptr) {
            _camera->setOrthoHeight(val);
        }
    }

    /**
     * @en Near clipping distance of the camera, should be as large as possible within acceptable range.
     * @zh 相机的近裁剪距离，应在可接受范围内尽量取最大。
     */
    inline float getNear() const {
        return _near;
    }

    inline void setNear(float val) {
        _near = val;
        if (_camera != nullptr) {
            _camera->setNearClip(val);
        }
    }

    /**
     * @en Far clipping distance of the camera, should be as small as possible within acceptable range.
     * @zh 相机的远裁剪距离，应在可接受范围内尽量取最小。
     */
    inline float getFar() const {
        return _far;
    }

    inline void setFar(float val) {
        _far = val;
        if (_camera != nullptr) {
            _camera->setFarClip(val);
        }
    }

    /**
     * @en Camera aperture, controls the exposure parameter.
     * @zh 相机光圈，影响相机的曝光参数。
     */
    inline Aperture getAperture() const {
        return _aperture;
    }

    inline void setAperture(Aperture val) {
        _aperture = val;
        if (_camera != nullptr) {
            _camera->setAperture(val);
        }
    }

    /**
     * @en Camera shutter, controls the exposure parameter.
     * @zh 相机快门，影响相机的曝光参数。
     */
    inline Shutter getShutter() const {
        return _shutter;
    }

    inline void setShutter(Shutter val) {
        _shutter = val;
        if (_camera != nullptr) {
            _camera->setShutter(val);
        }
    }

    /**
     * @en Camera ISO, controls the exposure parameter.
     * @zh 相机感光度，影响相机的曝光参数。
     */
    inline ISO getIso() const {
        return _iso;
    }

    inline void setIso(ISO val) {
        _iso = val;
        if (_camera != nullptr) {
            _camera->setIso(val);
        }
    }

    /**
     * @en Screen viewport of the camera wrt. the sceen size.
     * @zh 此相机最终渲染到屏幕上的视口位置和大小。
     */
    inline const cc::Rect &getRect() const {
        return _rect;
    }

    inline void setRect(const cc::Rect &val) {
        _rect = val;
        if (_camera != nullptr) {
            _camera->setViewport({_rect.origin.x, _rect.origin.y, _rect.size.width, _rect.size.height});
        }
    }

    /**
     * @en Output render texture of the camera. Default to null, which outputs directly to screen.
     * @zh 指定此相机的渲染输出目标贴图，默认为空，直接渲染到屏幕。
     */
    inline RenderTexture *getTargetTexture() const {
        return _targetTexture;
    }

    inline void setTargetTexture(RenderTexture *value) {
        if (_targetTexture == value) {
            return;
        }

        auto *old      = _targetTexture;
        _targetTexture = value;
        checkTargetTextureEvent(old);
        updateTargetTexture();

        if (!value && _camera != nullptr) {
            _camera->changeTargetWindow(/*EDITOR ? legacyCC.director.root.tempWindow : */ nullptr);
            _camera->setWindowSize(true);
        }
        //cjh TODO:        node.emit(Camera.TARGET_TEXTURE_CHANGE, this);
    }

    /**
     * @en Scale of the internal buffer size,
     * set to 1 to keep the same with the canvas size.
     * @zh 相机内部缓冲尺寸的缩放值, 1 为与 canvas 尺寸相同。
     */
    inline float getScreenScale() const {
        return _screenScale;
    }

    inline void setScreenScale(float val) {
        _screenScale = val;
        if (_camera != nullptr) {
            _camera->setScreenScale(val);
        }
    }

    bool isInEditorMode() const {
        return _inEditorMode;
    }

    void setInEditorMode(bool value);

    void onLoad() override;
    void onEnable() override;
    void onDisable() override;
    void onDestroy() override;

    geometry::Ray *screenPointToRay(geometry::Ray *out, float x, float y);

    const Vec3 &worldToScreen(Vec3 &out, const Vec3 &worldPos);
    const Vec3 &screenToWorld(Vec3 &out, const Vec3 &screenPos);

    /**
     * @en 3D node to UI local node coordinates. The converted value is the offset under the UI node.
     *
     * @zh 3D 节点转 UI 本地节点坐标。转换后的值是该 UI 节点下的偏移。
     * @param wpos 3D 节点世界坐标
     * @param uiNode UI 节点
     * @param out 返回在当前传入的 UI 节点下的偏移量
     *
     * @example
     * ```ts
     * this.convertToUINode(target.worldPosition, uiNode.parent, out);
     * uiNode.position = out;
     * ```
     */
    Vec3 convertToUINode(const Vec3 &wpos, Node *uiNode);

protected:
    void createCamera();
    void attachToScene();
    void detachFromScene();

    void checkTargetTextureEvent(RenderTexture *old);
    void updateTargetTexture();

protected:
    // @serializable
    ProjectionType _projection{ProjectionType::PERSPECTIVE};
    // @serializable
    uint32_t _priority{0}; //cjh Why it's uint32_t in scene::Camera?
    // @serializable
    float _fov = 45.F;
    // @serializable
    FOVAxis _fovAxis{FOVAxis::VERTICAL};
    // @serializable
    float _orthoHeight{10.F};
    // @serializable
    float _near{1.F};
    // @serializable
    float _far{1000.F};
    // @serializable
    Color _color{0x33, 0x33, 0x33, 0xFF};
    // @serializable
    float _depth{1.F};
    // @serializable
    float _stencil{0.F};
    // @serializable
    ClearFlag _clearFlags{ClearFlag::SOLID_COLOR};
    // @serializable
    Rect _rect{0, 0, 1, 1};
    // @serializable
    Aperture _aperture = Aperture::F16_0;
    // @serializable
    Shutter _shutter = Shutter::D125;
    // @serializable
    ISO _iso = ISO::ISO100;
    // @serializable
    float _screenScale = 1.F;
    // @serializable
    uint32_t _visibility{pipeline::CAMERA_DEFAULT_MASK};
    // @serializable
    RenderTexture *_targetTexture{nullptr};

    scene::Camera *          _camera{nullptr};
    bool                     _inEditorMode{false};
    std::vector<std::string> _flows;
};

} // namespace cc
