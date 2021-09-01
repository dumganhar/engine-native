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

#include "math/Color.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "scene/Fog.h"

namespace cc {

namespace scene {
enum class FogType;
}

namespace scenegraph {

class Ambient;
class AmbientInfo {
protected:
    Color    _skyColor{51, 128, 204, 1.0F};
    float    _skyIllum{2000.0F};
    Color    _groundAlbedo{51, 51, 51, 255};
    Ambient *_resource;

public:
    AmbientInfo(/* args */) = default;
    ~AmbientInfo()          = default;
    inline void         setSkyColor(const Color &val){};
    inline const Color &getSkyColor() { return _skyColor; }
    inline void         setSkyIllum(float val) {}
    inline float        getSkyIllum() const { return _skyIllum; }
    inline void         setGroundAlbedo(const Color &val) {}
    inline const Color &getGroundAlbedo() { return _groundAlbedo; }
    inline void         activate(Ambient *resource) {}
};

class Skybox;
class SkyboxInfo {
protected:
    bool    _isRGBE{false};
    bool    _enabled{false};
    bool    _useIBL{false};
    Skybox *_resource;

public:
    SkyboxInfo(/* args */) = default;
    ~SkyboxInfo()          = default;
    inline void setEnabled(bool val) { _enabled = val; }
    inline bool getEnabled() const { return _enabled; }
    inline void setIBL(bool val) { _useIBL = val; }
    inline bool getIBL() const { return _useIBL; }
    inline void setRGBE(bool val) { _isRGBE = val; }
    inline bool getRGBE() const { return _isRGBE; }
    inline void activate(Skybox *resource) {}
};

class Shadows;
class ShadowInfo {
protected:
    Color _shadowColor{0, 0, 0, 76};
    bool  _enabled{false};
    Vec3  _normal{0, 1, 0};
    float _distance{0};
    float _autoAdapt{true};
    float _bias{0.00001F};
    float _normalBias{0};
    float _near{1};
    float _far{30};
    float _orthoSize{5};
    float _maxReceived{4};
    float _saturation{0.75};
    Vec2  _size{512, 512};

    Shadows *_resource{nullptr};

public:
    ShadowInfo(/* args */) = default;
    ~ShadowInfo()          = default;
    inline void activate(Shadows *resources) {}
};

class SceneGlobal {
public:
    SceneGlobal(/* args */) = default;
    ~SceneGlobal()          = default;
    AmbientInfo    ambient;
    ShadowInfo     shadows;
    SkyboxInfo     skybox;
    scene::FogInfo fog;
    inline void    activate() {}
};

} // namespace scenegraph
} // namespace cc
