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

#include "core/Root.h"
#include "core/components/Component.h"
#include "math/Color.h"
#include "scene/Light.h"

namespace cc {

class StaticLightSettings {
public:
    /**
     * @en editor only.
     * @zh 是否只在编辑器里生效。
     */
    // @editable
    inline bool isEditorOnly() const { return _editorOnly; }
    inline void setEditorOnly(bool val) { _editorOnly = val; }

    /**
     * bake state
     */
    inline bool isBaked() const { return _baked; }
    inline void setBaked(bool val) { _baked = val; }

    /**
     * @en bakeable.
     * @zh 是否可烘培。
     */
    // @editable
    inline bool isBakeable() const { return _bakeable; }
    inline void setBakeable(bool val) { _bakeable = val; }

    /**
     * @en cast shadow.
     * @zh 是否投射阴影。
     */
    // @editable
    inline bool isCastShadow() const { return _castShadow; }

    inline void setCastShadow(bool val) { _castShadow = val; }

protected:
    // TODO(xwx): @serializable
    bool _baked{false};
    // TODO(xwx): @serializable
    bool _editorOnly{false};
    // TODO(xwx): @serializable
    bool _bakeable{false};
    // TODO(xwx): @serializable
    bool _castShadow{false};
};

enum class PhotometricTerm {
    LUMINOUS_FLUX = 0,
    LUMINANCE     = 1,
};

/**
 * @en static light settings.
 * @zh 静态灯光设置
 */
class Light : public Component {
public:
    using Super = Component;

    Light();
    ~Light() override;

    /**
     * @en
     * Color of the light.
     * @zh
     * 光源颜色。
     */
    // @tooltip('i18n:lights.color')
    inline Color getColor() const { return _color; }

    void setColor(const Color &val);

    /**
     * @en
     * Whether to enable light color temperature.
     * @zh
     * 是否启用光源色温。
     */
    // @tooltip('i18n:lights.use_color_temperature')
    inline bool isUseColorTemperature() const { return _useColorTemperature; }

    inline void setUseColorTemperature(bool val) {
        _useColorTemperature = val;
        if (_light != nullptr) _light->setUseColorTemperature(val);
    };

    /**
     * @en
     * The light color temperature.
     * @zh
     * 光源色温。
     */
    // @slide
    // @range([ 1000, 15000, 1 ])
    // @tooltip('i18n:lights.color_temperature')
    inline float getColorTemperature() const { return _colorTemperature; }

    inline void setColorTemperature(float val) {
        _colorTemperature = val;
        if (_light != nullptr) _light->setColorTemperature(val);
    }

    /**
     * @en
     * static light settings.
     * @zh
     * 静态灯光设置。
     */
    // @type(StaticLightSettings)
    inline const StaticLightSettings &getStaticSettings() const { return _staticSettings; }

    inline void setStaticSettings(const StaticLightSettings &val) { _staticSettings = val; }

    /**
     * @en
     * The light type.
     * @zh
     * 光源类型。
     */
    const scene::LightType &getType() const { return _type; }

    /**
     * bake state
     */
    inline bool isBaked() const { return _staticSettings.isBaked(); }

    inline void setBaked(bool val) {
        _staticSettings.setBaked(val);
        if (_light != nullptr) _light->setBaked(val);
    }

    inline void onLoad() override {
        createLight();
    }

    inline void onEnable() override {
        attachToScene();
    }

    inline void onDisable() override {
        detachFromScene();
    }

    inline void onDestroy() override {
        destroyLight();
    }

protected:
    // TODO(xwx): @serializable
    Color _color{255, 255, 255, 255}; // default white color
    // TODO(xwx): @serializable
    bool _useColorTemperature{false};
    // TODO(xwx): @serializable
    float _colorTemperature{6550};
    // TODO(xwx): @serializable
    StaticLightSettings _staticSettings;

    scene::LightType _type{scene::LightType::UNKNOWN};

    scene::Light *_light{nullptr};

    void initializeLight();
    void createLight();
    void destroyLight();
    void attachToScene();
    void detachFromScene();

private:
    CC_DISALLOW_COPY_MOVE_ASSIGN(Light);
};

} // namespace cc
