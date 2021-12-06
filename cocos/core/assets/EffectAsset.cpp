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
#include "renderer/core/ProgramLib.h"

namespace cc {

IPassStates::IPassStates(const IPassInfoFull &o) {
    *this = o;
}

IPassStates &IPassStates::operator=(const IPassInfoFull &o) {
    priority          = o.priority;
    primitive         = o.primitive;
    stage             = o.stage;
    rasterizerState   = o.rasterizerState;
    depthStencilState = o.depthStencilState;
    blendState        = o.blendState;
    dynamicStates     = o.dynamicStates;
    phase             = o.phase;
    return *this;
}

EffectAsset::RegisteredEffectAssetMap EffectAsset::__effects;

/* static */
void EffectAsset::registerAsset(EffectAsset *asset) {
    if (asset == nullptr) {
        return;
    }

    __effects.emplace(asset->getName(), asset);
    asset->addRef();
}

/* static */
void EffectAsset::remove(const std::string &name) {
    auto iter = __effects.find(name);
    if (iter != __effects.end() && iter->second->getName() == name) {
        __effects.erase(iter); //cjh TODO: need to delete asset here ?
        iter->second->release();
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
        iter->second->release();
    }
}

/* static */
void EffectAsset::remove(EffectAsset *asset) {
    if (asset == nullptr) {
        return;
    }

    auto iter = __effects.find(asset->getName());
    if (iter != __effects.end() && iter->second == asset) {
        iter->second->release();
        __effects.erase(iter); //cjh TODO: need to delete asset here ?
    }
}

/* static */
EffectAsset *EffectAsset::get(const std::string &name) {
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
    return nullptr;
}

void EffectAsset::onLoaded() {
    ProgramLib::getInstance()->registerEffect(this);
    EffectAsset::registerAsset(this);
    //cjh TODO:    if (!EDITOR){
    //cjh    legacyCC.game.once(legacyCC.Game.EVENT_ENGINE_INITED, this._precompile, this);
    // }
}

bool EffectAsset::destroy() {
    EffectAsset::remove(this);
    return Super::destroy();
}

void EffectAsset::initDefault(const std::optional<std::string> &uuid) {
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

void EffectAsset::precompile() {
    Root *root = Root::getInstance();
    for (index_t i = 0; i < _shaders.size(); ++i) {
        auto shader = _shaders[i];
        if (i >= _combinations.size())
            continue;
        auto combination = _combinations[i];
        if (combination.empty()) continue;

        //TODO: minggo (do unit test)
        std::vector<MacroRecord> defines = EffectAsset::doCombine(std::vector<MacroRecord>(), combination, combination.begin());
        for (auto &define : defines) {
            ProgramLib::getInstance()->getGFXShader(root->getDevice(), shader.name, define, root->getPipeline());
        }
    }
}

/*
// input

const combination = {
USE_TEXTURE: [true, false],
COLOR_MODE: [0, 1, 2, 3],
ROUGHNESS_CHANNEL: ['r', 'g', 'b'],
};
 
// output

const defines = [
                 {
                 USE_TEXTURE: true,
                 COLOR_MODE: 0,
                 ROUGHNESS_CHANNEL: 'r'
                 },
                 {
                 USE_TEXTURE: true,
                 COLOR_MODE: 0,
                 ROUGHNESS_CHANNEL: 'g'
                 },
                 {
                 USE_TEXTURE: true,
                 COLOR_MODE: 0,
                 ROUGHNESS_CHANNEL: 'b'
                 },
                 {
                 USE_TEXTURE: true,
                 COLOR_MODE: 1,
                 ROUGHNESS_CHANNEL: 'r'
                 },
                 // ... all the combinations (2x4x3 in this case)
                 ];
 */
std::vector<MacroRecord> EffectAsset::doCombine(const std::vector<MacroRecord> &cur, const IPreCompileInfo &info, IPreCompileInfo::iterator iter) {
    if (iter == info.end()) {
        return cur;
    }

    const IPreCompileInfoValueType &values = iter->second;
    const std::string &             key    = iter->first;

    std::vector<MacroRecord> records;
    if (cur.empty()) {
        records = EffectAsset::generateRecords(key, values);
    } else {
        records = EffectAsset::insertInfoValue(cur, key, values);
    }

    return EffectAsset::doCombine(records, info, ++iter);
}

std::vector<MacroRecord> EffectAsset::generateRecords(const std::string &key, const IPreCompileInfoValueType &value) {
    std::vector<MacroRecord> ret;
    if (auto *boolValues = std::get_if<std::vector<bool>>(&value)) {
        for (const bool value : *boolValues) {
            MacroRecord record;
            record[key] = value;
            ret.emplace_back(record);
        }
    } else if (auto *floatValues = std::get_if<std::vector<float>>(&value)) {
        for (const bool value : *floatValues) {
            MacroRecord record;
            record[key] = value;
            ret.emplace_back(record);
        }
    } else if (auto *stringValues = std::get_if<std::vector<std::string>>(&value)) {
        for (const std::string &value : *stringValues) {
            MacroRecord record;
            record[key] = value;
            ret.emplace_back(record);
        }
    } else {
        CC_ASSERT(false);
    }

    return ret;
}

std::vector<MacroRecord> EffectAsset::insertInfoValue(const std::vector<MacroRecord> &records,
                                                      const std::string &             key,
                                                      const IPreCompileInfoValueType &value) {
    std::vector<MacroRecord> ret;
    for (const auto &record : records) {
        if (auto *boolValues = std::get_if<std::vector<bool>>(&value)) {
            for (const bool value : *boolValues) {
                MacroRecord tmpRecord = record;
                tmpRecord[key]        = value;
                ret.emplace_back(tmpRecord);
            }
        } else if (auto *floatValues = std::get_if<std::vector<float>>(&value)) {
            for (const bool value : *floatValues) {
                MacroRecord tmpRecord = record;
                tmpRecord[key]        = value;
                ret.emplace_back(tmpRecord);
            }
        } else if (auto *stringValues = std::get_if<std::vector<std::string>>(&value)) {
            for (const std::string &value : *stringValues) {
                MacroRecord tmpRecord = record;
                tmpRecord[key]        = value;
                ret.emplace_back(tmpRecord);
            }
        } else {
            CC_ASSERT(false);
        }
    }

    return ret;
}

} // namespace cc
