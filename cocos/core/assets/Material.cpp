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
#include "core/assets/EffectAsset.h"

namespace cc {

/* static */
uint64_t Material::getHashForMaterial(Material *material) {
    uint64_t hash = 0;
    //cjh TODO:    for (const pass of material.passes) {
    //        hash ^= pass.hash;
    //    }
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
    _techIdx = info.technique;
    if (info.effectAsset) {
        _effectAsset = info.effectAsset;
    } else if (!info.effectName.empty()) {
        _effectAsset = EffectAsset::get(info.effectName);
    }
    if (!info.defines.empty()) {
        prepareInfo(info.defines, _defines);
    }

    if (!info.states.empty()) {
        prepareInfo(info.states, _states);
    }
    update();
}

void Material::reset(const IMaterialInfo &info) { // to be consistent with other assets
    initialize(info);
}

void Material::recompileShaders(const MacroRecord &overrides, index_t passIdx) {
    //cjh TODO:
}

void Material::overridePipelineStates(const PassOverrides &overrides, index_t passIdx) {
    //cjh TODO:
}

void Material::onLoaded() {
    //cjh TODO:
}

void Material::resetUniforms(bool clearPasses /* = true */) {
    //cjh TODO:
}

void Material::setProperty(const std::string &name, const MaterialProperty &val, index_t passIdx /* = CC_INVALID_INDEX */) {
    bool success = false;
    if (passIdx == CC_INVALID_INDEX) { // try set property for all applicable passes
        size_t len = _passes.size();
        for (size_t i = 0; i < len; i++) {
            auto *pass = _passes[i];
            if (uploadProperty(pass, name, val)) {
                //cjh TODO:                _props[pass->getPropertyIndex()][name] = val;
                success = true;
            }
        }
    } else {
        if (passIdx >= _passes.size()) {
            CC_LOG_WARNING("illegal pass index: %d.", passIdx);
            return;
        }

        auto *pass = _passes[passIdx];
        if (uploadProperty(pass, name, val)) {
            //cjh            _props[pass->getPropertyIndex()][name] = val;
            success = true;
        }
    }

    if (!success) {
        CC_LOG_WARNING("illegal property name: %s.", name.c_str());
    }
}

MaterialProperty *Material::getProperty(const std::string &name, index_t passIdx) {
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

        //cjh        auto& props = _props[_passes[passIdx]->getPropertyIndex()];
        //        auto iter = props.find(name);
        //        if (iter != props.end()) {
        //            return &iter->second;
        //        }
    }
    return nullptr;
}

void Material::copy(const Material *mat) {
    //cjh
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
                    _props.resize(i);
                }

                const auto &props = _props[i];

                //cjh                if (pass->getPropertyIndex() != undefined) {
                //                    Object.assign(props, _props[pass.propertyIndex]);
                //                }

                for (const auto &[key, value] : props) {
                    uploadProperty(pass, key, value);
                }
            };

            for (size_t i = 0, len = _passes.size(); i < len; ++i) {
                cb(_passes[i], i);
            }
        }
        //cjh FIXME: no need?        else {
        //            for (size_t i = 0; i < _props.size(); i++) {
        //                _props[i] = {};
        //            }
        //        }
    }
    _hash = Material::getHashForMaterial(this);
}

std::vector<scene::Pass *> Material::createPasses() {
    std::vector<scene::Pass *> passes;
    const ITechniqueInfo *     tech = nullptr;
    if (_techIdx < _effectAsset->_techniques.size()) {
        tech = &_effectAsset->_techniques[_techIdx];
    }

    if (tech == nullptr) {
        return passes;
    }

    //TODO:    const passNum         = tech.passes.length;
    //    const passes : Pass[] = [];
    //    for (let k = 0; k < passNum; ++k) {
    //        const passInfo = tech.passes[k] as IPassInfoFull;
    //        const propIdx = passInfo.passIndex = k;
    //        const defines = passInfo.defines = this._defines[propIdx] || (this._defines[propIdx] = {});
    //        const states = passInfo.stateOverrides = this._states[propIdx] || (this._states[propIdx] = {});
    //        if (passInfo.propertyIndex != = undefined) {
    //            Object.assign(defines, this._defines[passInfo.propertyIndex]);
    //            Object.assign(states, this._states[passInfo.propertyIndex]);
    //        }
    //        if (passInfo.embeddedMacros != = undefined) {
    //            Object.assign(defines, passInfo.embeddedMacros);
    //        }
    //        if (passInfo.switch && !defines[passInfo.switch]) {
    //            continue;
    //        }
    //        const pass = new Pass(legacyCC.director.root);
    //        pass.initialize(passInfo);
    //        passes.push(pass);
    //    }
    return passes;
}

bool Material::uploadProperty(scene::Pass *passs, const std::string &name, const MaterialProperty &val) {
    uint32_t handle = 0; //cjh pass->getHandle(name);
    if (!handle) {
        return false;
    }

    //cjh    const propertyType = Pass.getPropertyTypeFromHandle(handle);
    //    if (propertyType === PropertyType.BUFFER) {
    //        if (Array.isArray(val)) {
    //            pass.setUniformArray(handle, val as MaterialProperty[]);
    //        } else if (val !== null) {
    //            pass.setUniform(handle, val as MaterialProperty);
    //        } else {
    //            pass.resetUniform(name);
    //        }
    //    } else if (propertyType === PropertyType.TEXTURE) {
    //        if (Array.isArray(val)) {
    //            for (let i = 0; i < val.length; i++) {
    //                this._bindTexture(pass, handle, val[i], i);
    //            }
    //        } else if (val) {
    //            this._bindTexture(pass, handle, val);
    //        } else {
    //            pass.resetTexture(name);
    //        }
    //    }
    return true;
}

void Material::bindTexture(scene::Pass *pass, uint32_t handle, const MaterialProperty &val, index_t index) {
}

template <typename T>
void Material::prepareInfo(const T &patchArray, T &cur) {
    size_t len = patchArray.size();
    cur.resize(len);

    for (size_t i = 0; i < len; ++i) {
        cur[i] = patchArray[i];
    }
}

} // namespace cc
