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

#include "core/assets/EffectAsset.h"
#include "core/Root.h"

namespace cc {

std::unordered_map<std::string, const EffectAsset *> EffectAsset::__effects;

/* static */
void EffectAsset::registerAsset(const EffectAsset *asset) {
    if (asset == nullptr)
        return;

    __effects.emplace(asset->getName(), asset);
}

/* static */
void EffectAsset::remove(const std::string &name) {
    auto iter = __effects.find(name);
    if (iter != __effects.end() && iter->second->getName() == name) {
        __effects.erase(iter); //cjh TODO: need to delete asset here ?
        return;
    }

    iter = __effects.begin();
    for (; iter != __effects.end(); ++iter) {
        if (iter->second->getUuid() == name) {
            break;
        }
    }

    if (iter != __effects.end()) {
        __effects.erase(iter);
    }
}

/* static */
void EffectAsset::remove(const EffectAsset *asset) {
    if (asset == nullptr)
        return;

    auto iter = __effects.find(asset->getName());
    if (iter != __effects.end() && iter->second == asset) {
        __effects.erase(iter); //cjh TODO: need to delete asset here ?
    }
}

/* static */
const EffectAsset *EffectAsset::get(const std::string &name) {
    auto iter = __effects.find(name);
    if (iter != __effects.end()) {
        return iter->second;
    }

    iter = __effects.begin();
    for (; iter != __effects.end(); ++iter) {
        if (iter->second->getUuid() == name) {
            return iter->second;
        }
    }
}

void EffectAsset::onLoaded() {
    //cjh TODO:    programLib.register(this);
    EffectAsset::registerAsset(this);
    //cjh TODO:    if (!EDITOR){
    //cjh    legacyCC.game.once(legacyCC.Game.EVENT_ENGINE_INITED, this._precompile, this);
    // }
}

bool EffectAsset::destroy() {
    EffectAsset::remove(this);
    return Super::destroy();
}

void EffectAsset::initDefault(const std::optional<std::string> &uuid /* = {}*/) {
    Super::initDefault(uuid);
    const auto *effect = EffectAsset::get("unlit");
    _name              = "unlit";
    _shaders           = effect->_shaders;
    _combinations      = effect->_combinations;
    _techniques        = effect->_techniques; //cjh TODO: shared_ptr ?
}

bool EffectAsset::validate() const {
    return !_techniques.empty() && !_shaders.empty();
}

void EffectAsset::_precompile() {
    //cjh TODO:    const root = legacyCC.director.root as Root;
    //    for (let i = 0; i < this.shaders.length; i++) {
    //        const shader = this.shaders[i];
    //        const combination = this.combinations[i];
    //        if (!combination) { continue; }
    //        const defines = Object.keys(combination).reduce((out, name) => out.reduce((acc, cur) => {
    //            const choices = combination[name];
    //            for (let i = 0; i < choices.length; ++i) {
    //                const defines = { ...cur };
    //                defines[name] = choices[i];
    //                acc.push(defines);
    //            }
    //            return acc;
    //        }, [] as MacroRecord[]), [{}] as MacroRecord[]);
    //        defines.forEach(
    //            (defines) => programLib.getGFXShader(root.device, shader.name, defines, root.pipeline),
    //        );
    //    }
}

} // namespace cc
