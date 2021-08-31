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

#include <vector>
#include <array>
#include "math/Vec3.h"
#include "math/Vec2.h"
#include "math/Mat4.h"
#include "math/Color.h"
#include "renderer/gfx-base/GFXShader.h"
#include "core/assets/Material.h"
#include "core/scene-graph/SceneGlobal.h"
#include "scene/Define.h"
#include "core/geometry/Sphere.h"

namespace cc {
namespace scene {

/**
 * @zh 阴影贴图分辨率。
 * @en The shadow map size.
 * @static
 * @enum Shadows.ShadowSize
 */
enum class ShadowSize {
    /**
     * @zh 分辨率 256 * 256。
     * @en shadow resolution 256 * 256.
     * @readonly
     */
    LOW_256x256 = 256,

    /**
     * @zh 分辨率 512 * 512。
     * @en shadow resolution 512 * 512.
     * @readonly
     */
    MEDIUM_512x512 = 512,

    /**
     * @zh 分辨率 1024 * 1024。
     * @en shadow resolution 1024 * 1024.
     * @readonly
     */
    HIGH_1024x1024 = 1024,

    /**
     * @zh 分辨率 2048 * 2048。
     * @en shadow resolution 2048 * 2048.
     * @readonly
     */
    ULTRA_2048x2048 = 2048
};

/**
 * @zh 阴影类型。
 * @en The shadow type
 * @enum Shadows.ShadowType
 */
enum class ShadowType {
    /**
     * @zh 平面阴影。
     * @en Planar shadow
     * @property Planar
     * @readonly
     */
    PLANAR = 0,

    /**
     * @zh 阴影贴图。
     * @en Shadow type
     * @property ShadowMap
     * @readonly
     */
    SHADOW_MAP = 1,
    NONE
};

/**
 * @zh pcf阴影等级。
 * @en The pcf type
 * @static
 * @enum Shadows.PCFType
 */
enum class PCFType {
    /**
     * @zh x1 次采样
     * @en x1 times
     * @readonly
     */
    HARD = 0,

    /**
     * @zh 软阴影
     * @en soft shadow
     * @readonly
     */
    SOFT = 1,

    /**
     * @zh 软阴影
     * @en soft shadow
     * @readonly
     */
    SOFT_2X = 2
};

class Shadow final {
public:
    /**
     * @en MAX_FAR. This is shadow camera max far.
     * @zh 阴影相机的最远视距。
     */
    static constexpr float MAX_FAR{2000.0f};

    /**
     * @en EXPANSION_RATIO. This is shadow boundingBox Coefficient of expansion.
     * @zh 阴影包围盒扩大系数。
     */
    static const float COEFFICIENT_OF_EXPANSION;

    Shadow()  = default;
    ~Shadow() = default;

    void         initialize(const scenegraph::ShadowInfo &shadowsInfo);
    void         destroy();
    gfx::Shader *getPlanarShader(const std::vector<IMacroPatch> &patches);
    gfx::Shader *getPlanarInstanceShader(const std::vector<IMacroPatch> &patches);
    void         activate();

    /**
     * @en Whether activate planar shadow.
     * @zh 是否启用平面阴影？
     */
    inline bool isEnabled() const { return _enabled; }
    inline void setEnabled(bool val) {
        _enabled = val;
        activate();
    }

    /**
     * @en The normal of the plane which receives shadow.
     * @zh 阴影接收平面的法线。
     */
    inline const Vec3 &getNormal() const { return _normal; }
    inline void        setNormal(const Vec3 &val) { _normal.set(val); }

    /**
     * @en The distance from coordinate origin to the receiving plane.
     * @zh 阴影接收平面与原点的距离。
     */
    inline float getDistance() const { return _distance; }
    inline void  setDistance(float val) { _distance = val; }

    /**
     * @en Shadow color.
     * @zh 阴影颜色。
     */
    inline const Color &getShadowColor() const { return _shadowColor; }
    inline void         setShadowColor(const Color &color) {
        _shadowColor.set(color);
        _shadowColor4f[0] = color.r / 255;
        _shadowColor4f[1] = color.g / 255;
        _shadowColor4f[2] = color.b / 255;
        _shadowColor4f[3] = color.a / 255;
    }
    inline const std::array<float, 4> &getShadowColor4f() const { return _shadowColor4f; }

    /**
     * @en Shadow type.
     * @zh 阴影类型。
     */
    inline ShadowType getType() const { return _type; }
    inline void       setType(ShadowType val) {
        _type = _enabled ? val : ShadowType::NONE;
        activate();
    }

    /**
     * @en get or set shadow camera near.
     * @zh 获取或者设置阴影相机近裁剪面。
     */
    inline float getNear() const { return _near; }
    inline void  setNear(float val) { _near = val; }

    /**
     * @en get or set shadow camera far.
     * @zh 获取或者设置阴影相机远裁剪面。
     */
    inline float getFar() const { return _far; }
    inline void  setFar(float val) { _far = val; }

    /**
     * @en get or set shadow camera orthoSize.
     * @zh 获取或者设置阴影相机正交大小。
     */
    inline float getOrthoSize() const { return _orthoSize; }
    inline void  setOrthoSize(float val) { _orthoSize = val; }

    /**
     * @en get or set shadow camera orthoSize.
     * @zh 获取或者设置阴影纹理大小。
     */
    inline const Vec2 &getSize() const { return _size; }
    inline void        setSize(const Vec2 &val) { _size.set(val); }

    /**
     * @en get or set shadow pcf.
     * @zh 获取或者设置阴影pcf等级。
     */
    inline PCFType getPcf() const { return _pcf; }
    inline void    setPcf(PCFType val) { _pcf = val; }

    /**
     * @en shadow Map size has been modified.
     * @zh 阴影贴图大小是否被修改。
     */
    inline bool isShadowMapDirty() const { return _shadowMapDirty; }
    inline void setShadowMapDirty(bool val) { _shadowMapDirty = val; }

    /**
     * @en get or set shadow bias.
     * @zh 获取或者设置阴影偏移量。
     */
    inline float getBias() const { return _bias; }
    inline void  setBias(float val) { _bias = val; }

    /**
     * @en get or set normal bias.
     * @zh 设置或者获取法线偏移。
     */
    inline float getNormalBias() const { return _normalBias; }
    inline void  setNormalBias(float val) { _normalBias = val; }

    /**
     * @en get or set shadow saturation.
     * @zh 设置或者获取阴影饱和度。
     */
    inline float getSaturation() const { return _saturation; }
    inline void  setSaturation(float val) { _saturation = val; }

    /**
     * @en get or set shadow auto control.
     * @zh 获取或者设置阴影是否自动控制。
     */
    inline bool isAutoAdapt() const { return _autoAdapt; }
    inline void setAutoAdapt(bool val) { _autoAdapt = val; }

    inline const Mat4 &getMatLight() const { return _matLight; }
    inline Material *  getMaterial() const { return _material; }
    inline Material *  getInstancingMaterial() const { return _instancingMaterial; }

private:
    void updatePlanarInfo();
    void updatePipeline();

    /**
     * @en The bounding sphere of the shadow map.
     * @zh 用于计算阴影 Shadow map 的场景包围球.
     */
    geometry::Sphere sphere{0.0F, 0.0F, 0.0F, 0.01F};

    /**
     * @en get or set shadow max received.
     * @zh 阴影接收的最大灯光数量。
     */
    uint32_t maxReceived{4};

    Vec3                _normal{0.F, 1.F, 0.F};
    Color               _shadowColor{0.F, 0.F, 0.F, 76.F};
    std::array<float, 4> _shadowColor4f;
    Mat4                _matLight;
    Material *          _material{nullptr};
    Material *          _instancingMaterial{nullptr};
    Vec2                _size{512.F, 512.F};
    bool                _enabled{false};
    float               _distance{0.F};
    ShadowType          _type{ShadowType::NONE};
    float               _near{0.F};
    float               _far{0.F};
    float               _orthoSize{1.F};
    PCFType             _pcf{PCFType::HARD};
    bool                _shadowMapDirty{false};
    float               _bias{0.F};
    float               _normalBias{0.F};
    bool                _autoAdapt{true};
    float               _saturation{0.75F};
};

} // namespace scene
} // namespace cc
