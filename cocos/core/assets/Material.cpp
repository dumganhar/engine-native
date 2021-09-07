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

#include "core/assets/Material.h"

#include "base/Utils.h"
#include "core/assets/EffectAsset.h"
#include "math/Color.h"
#include "scene/Pass.h"

namespace cc {

/* static */
uint64_t Material::getHashForMaterial(Material *material) {
    if (material == nullptr) {
        return 0;
    }

    uint64_t hash = 0;
    for (auto *pass : material->_passes) {
        hash ^= pass->getHash();
    }
    return hash;
}

void Material::initialize(const IMaterialInfo &info) {
    if (!_passes.empty()) {
        //cjh TODO:        warnID(12005);
        return;
    }

    if (!_defines.empty()) {
        _defines.clear();
    }
    if (!_states.empty()) {
        _states.clear();
    }
    if (!_props.empty()) {
        _props.clear();
    }

    if (info.technique != std::nullopt) {
        _techIdx = info.technique.value();
    }

    if (info.effectAsset != nullptr) {
        _effectAsset = info.effectAsset; //cjh TODO:
    } else if (info.effectName != std::nullopt) {
        _effectAsset = EffectAsset::get(info.effectName.value());
    }

    if (info.defines != std::nullopt) {
        prepareInfo(info.defines.value(), _defines);
    }

    if (info.states != std::nullopt) {
        prepareInfo(info.states.value(), _states);
    }
    update();
}

void Material::reset(const IMaterialInfo &info) { // to be consistent with other assets
    initialize(info);
}

bool Material::destroy() {
    doDestroy();
    return Super::destroy();
}

void Material::doDestroy() {
    if (!_passes.empty()) {
        for (auto *pass : _passes) {
            pass->destroy();
        }
    }
    _passes.clear();
}

void Material::recompileShaders(const MacroRecord &overrides, index_t passIdx = CC_INVALID_INDEX) {
    CC_LOG_WARNING("Shaders in material asset '%s' cannot be modified at runtime, please instantiate the material first.", _name.c_str());
}

void Material::overridePipelineStates(const PassOverrides &overrides, index_t passIdx = CC_INVALID_INDEX) {
    CC_LOG_WARNING("Pipeline states in material asset '%s' cannot be modified at runtime, please instantiate the material first.", _name.c_str());
}

void Material::onLoaded() {
    update();
}

void Material::resetUniforms(bool clearPasses /* = true */) {
    _props.resize(_passes.size());

    if (!clearPasses) {
        return;
    }

    for (auto *pass : _passes) {
        pass->resetUBOs();
        pass->resetTextures();
    }
}

void Material::setProperty(const std::string &name, const MaterialPropertyVariant &val, index_t passIdx /* = CC_INVALID_INDEX */) {
    bool success = false;
    if (passIdx == CC_INVALID_INDEX) { // try set property for all applicable passes
        size_t len = _passes.size();
        for (size_t i = 0; i < len; i++) {
            auto *pass = _passes[i];
            if (uploadProperty(pass, name, val)) {
                _props[pass->getPropertyIndex()][name] = val;
                success                                = true;
            }
        }
    } else {
        if (passIdx >= _passes.size()) {
            CC_LOG_WARNING("illegal pass index: %d.", passIdx);
            return;
        }

        auto *pass = _passes[passIdx];
        if (uploadProperty(pass, name, val)) {
            _props[pass->getPropertyIndex()][name] = val;
            success                                = true;
        }
    }

    if (!success) {
        CC_LOG_WARNING("illegal property name: %s.", name.c_str());
    }
}

MaterialPropertyVariant *Material::getProperty(const std::string &name, index_t passIdx) {
    if (passIdx == CC_INVALID_INDEX) { // try get property in all possible passes
        auto & propsArray = _props;
        size_t len        = propsArray.size();
        for (size_t i = 0; i < len; i++) {
            auto &props = propsArray[i];
            auto  iter  = props.find(name);
            if (iter != props.end()) {
                return &iter->second;
            }
        }
    } else {
        if (passIdx >= _props.size()) {
            CC_LOG_WARNING("illegal pass index: %d.", passIdx);
            return nullptr;
        }

        auto &props = _props[_passes[passIdx]->getPropertyIndex()];
        auto  iter  = props.find(name);
        if (iter != props.end()) {
            return &iter->second;
        }
    }
    return nullptr;
}

void Material::copy(const Material *mat) {
    if (mat == nullptr) {
        return;
    }

    _techIdx = mat->_techIdx;
    _props.resize(mat->_props.size());
    for (size_t i = 0, len = mat->_props.size(); i < len; ++i) {
        _props[i] = mat->_props[i];
    }
    _defines.resize(mat->_defines.size());
    for (size_t i = 0, len = mat->_defines.size(); i < len; ++i) {
        _defines[i] = mat->_defines[i];
    }
    _states.resize(mat->_states.size());
    for (size_t i = 0, len = mat->_states.size(); i < len; ++i) {
        _states[i] = mat->_states[i];
    }
    _effectAsset = mat->_effectAsset; //cjh TODO: lifecycle
    update();
}

void Material::update(bool keepProps /* = true*/) {
    if (_effectAsset) {
        _passes = createPasses();
        // handle property values
        size_t totalPasses = _effectAsset->_techniques[_techIdx].passes.size();
        _props.resize(totalPasses);
        if (keepProps) {
            auto cb = [this](auto *pass, size_t i) {
                if (i >= _props.size()) {
                    _props.resize(i + 1);
                }

                auto &props = _props[i];

                if (pass->getPropertyIndex() != CC_INVALID_INDEX) {
                    props = _props[pass->getPropertyIndex()];
                }

                for (const auto &[key, value] : props) {
                    uploadProperty(pass, key, value);
                }
            };

            for (size_t i = 0, len = _passes.size(); i < len; ++i) {
                cb(_passes[i], i);
            }
        }
        //cjh FIXME: no need since we resize _props?
        //        else {
        //            for (size_t i = 0; i < _props.size(); i++) {
        //                _props[i] = {};
        //            }
        //        }
    }
    _hash = Material::getHashForMaterial(this);
}

std::vector<scene::Pass *> Material::createPasses() {
    std::vector<scene::Pass *> passes;
    ITechniqueInfo *           tech = nullptr;
    if (_techIdx < _effectAsset->_techniques.size()) {
        tech = &_effectAsset->_techniques[_techIdx];
    }

    if (tech == nullptr) {
        return passes;
    }

    size_t passNum = tech->passes.size();
    for (size_t k = 0; k < passNum; ++k) {
        auto &  passInfo = tech->passes[k];
        index_t propIdx = passInfo.passIndex = static_cast<index_t>(k);

        if (propIdx >= _defines.size()) {
            _defines.resize(propIdx + 1);
        }
        passInfo.defines = _defines[propIdx]; //cjh JS object assignment is weak reference but c++ container assignment is strong copy operation  // const defines = passInfo.defines = this._defines[propIdx] || (this._defines[propIdx] = {});
        auto &defines    = passInfo.defines;

        if (propIdx >= _states.size()) {
            _states.resize(propIdx + 1);
        }
        passInfo.stateOverrides = _states[propIdx]; //cjh same question as described above
        auto &states            = passInfo.stateOverrides.value();

        if (passInfo.propertyIndex != CC_INVALID_INDEX) {
            utils::mergeToMap(defines, _defines[passInfo.propertyIndex]);
            states = _states[passInfo.propertyIndex];
        }

        if (passInfo.embeddedMacros.has_value()) {
            utils::mergeToMap(defines, passInfo.embeddedMacros.value());
        }

        if (passInfo.switch_.has_value() && defines.find(passInfo.switch_.value()) == defines.end()) {
            continue;
        }

        auto pass = new scene::Pass(/*legacyCC.director.root*/); //cjh how to pass Root ?
        pass->initialize(passInfo);
        passes.emplace_back(pass);
    }
    return passes;
}

bool Material::uploadProperty(scene::Pass *pass, const std::string &name, const MaterialPropertyVariant &val) {
    uint32_t handle = pass->getHandle(name);
    if (!handle) {
        return false;
    }

    const auto propertyType = scene::Pass::getPropertyTypeFromHandle(handle);
    if (propertyType == PropertyType::BUFFER) {
        if (val.index() == MaterialPropertyIndexList) {
            pass->setUniformArray(handle, std::get<MaterialPropertyList>(val));
        } else if (val.index() == MaterialPropertyIndexSingle) {
            pass->setUniform(handle, std::get<MaterialProperty>(val));
        } else {
            pass->resetUniform(name);
        }
    } else if (propertyType == PropertyType::TEXTURE) {
        if (val.index() == MaterialPropertyIndexList) {
            auto &textureArray = std::get<MaterialPropertyList>(val);
            for (size_t i = 0; i < textureArray.size(); i++) {
                bindTexture(pass, handle, textureArray[i], i);
            }
        } else if (val.index() == MaterialPropertyIndexSingle) {
            bindTexture(pass, handle, std::get<MaterialProperty>(val));
        } else {
            pass->resetTexture(name);
        }
    }
    return true;
}

void Material::bindTexture(scene::Pass *pass, uint32_t handle, const MaterialProperty &val, index_t index /* = CC_INVALID_INDEX*/) {
    if (pass == nullptr) {
        return;
    }

    const uint32_t binding = scene::Pass::getBindingFromHandle(handle);
    if (auto pTexture = std::get_if<gfx::Texture *>(&val)) {
        pass->bindTexture(binding, const_cast<gfx::Texture *>(*pTexture), index);
    } else if (auto pTextureBase = std::get_if<TextureBase *>(&val)) {
        auto *        textureBase = *pTextureBase;
        gfx::Texture *texture     = textureBase->getGFXTexture();
        if (texture == nullptr || texture->getWidth() == 0 || texture->getHeight() == 0) {
            // console.warn(`material '${this._uuid}' received incomplete texture asset '${val._uuid}'`);
            return;
        }
        pass->bindTexture(binding, texture, index);
        pass->bindSampler(binding, textureBase->getGFXSampler(), index);
    }
}

void Material::initDefault(const std::optional<std::string> &uuid /* = {}*/) {
    Super::initDefault(uuid);
    MacroRecord   defines{{"USE_COLOR", true}};
    IMaterialInfo info{
        .effectName = "unlit",
        .defines    = defines};
    initialize(std::move(info));
    setProperty("mainColor", Color{0xFF, 0x00, 0xFF, 0xFF});
}

bool Material::validate() const {
    return _effectAsset != nullptr && !_effectAsset->isDefault() && !_passes.empty();
}

template <typename T1, typename T2>
void Material::prepareInfo(const T1 &patch, std::vector<T2> &cur) {
    if (auto *pOneElement = std::get_if<T2>(patch)) {
        size_t len = _effectAsset != nullptr ? _effectAsset->_techniques[_techIdx].passes.size() : 1;

        std::vector<T2> patchArray;
        patchArray.reserve(len);
        for (size_t i = 0; i < len; ++i) {
            patchArray.emplace_back(patch);
        }

        cur.resize(patchArray.size());

        for (size_t i = 0; i < len; ++i) {
            cur[i] = patchArray[i];
        }
    } else {
        const T1 &patchArray = patch;
        size_t    len        = patchArray.size();
        cur.resize(len);

        for (size_t i = 0; i < len; ++i) {
            cur[i] = patchArray[i];
        }
    }
}

} // namespace cc
