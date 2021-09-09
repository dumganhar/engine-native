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

EffectAsset::RegisteredEffectAssetMap EffectAsset::__effects;

/* static */
void EffectAsset::registerAsset(EffectAsset *asset) {
    if (asset == nullptr) {
        return;
    }

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
void EffectAsset::remove(EffectAsset *asset) {
    if (asset == nullptr) {
        return;
    }

    auto iter = __effects.find(asset->getName());
    if (iter != __effects.end() && iter->second == asset) {
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
    ProgramLib::getInstance()->registerEffect(*this);
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
        auto shader      = _shaders[i];
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

static MacroRecord jsonToMacroRecord(const rapidjson::Value &embeddedMacrosVal) {
    MacroRecord cEmbeddedMacros;
    for (const auto &macro : embeddedMacrosVal.GetObject()) {
        const auto *name  = macro.name.GetString();
        const auto &value = macro.value;

        // using MacroValue = std::variant<int32_t, float, bool, std::string>;
        // MacroValue only support one of int32_t, float, bool, std::string
        if (value.IsInt()) {
            cEmbeddedMacros.emplace(name, value.GetInt());
            //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%d", name, value.GetInt());
        } else if (value.IsInt64()) {
            cEmbeddedMacros.emplace(name, static_cast<int32_t>(value.GetInt64())); //cjh TODO: need int64?
                                                                                   //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%ld", name, value.GetInt64());
        } else if (value.IsFloat()) {
            cEmbeddedMacros.emplace(name, value.GetFloat());
            //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%f", name, value.GetFloat());
        } else if (value.IsDouble()) {
            cEmbeddedMacros.emplace(name, static_cast<float>(value.GetDouble())); //cjh TODO: need double?
                                                                                  //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%lf", name, value.GetDouble());
        } else if (value.IsBool()) {
            cEmbeddedMacros.emplace(name, value.GetBool());
            //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%d", name, static_cast<int32_t>(value.GetBool()));
        } else if (value.IsString()) {
            cEmbeddedMacros.emplace(name, value.GetString());
            //            CC_LOG_DEBUG(">> embeddedMacros[%s]=%s", name, value.GetString());
        } else {
            CC_LOG_WARNING("Unknown macro value type: %s", name);
        }
    }

    return cEmbeddedMacros;
}

static IPropertyHandleInfo jsonToPropertyHandleInfo(const rapidjson::Value &handleInfoVal) {
    if (handleInfoVal.IsArray()) {
        // using IPropertyHandleInfo = std::tuple<std::string, uint32_t, gfx::Type>;
        std::string t0;
        uint32_t    t1 = 0;
        gfx::Type   t2 = gfx::Type::UNKNOWN;
        int32_t     i  = 0;

        for (const auto &e : handleInfoVal.GetArray()) {
            switch (i) {
                case 0:
                    t0 = e.GetString();
                    break;
                case 1:
                    t1 = e.GetUint();
                    break;
                case 2:
                    t2 = static_cast<gfx::Type>(e.GetUint());
                    break;
                default:
                    break;
            }

            ++i;
        }

        return IPropertyHandleInfo{t0, t1, t2};
    }

    return {};
}

static IPropertyInfo jsonToPropertyInfo(const rapidjson::Value &propertyInfoVal) {
    IPropertyInfo ret;

    ret.type = propertyInfoVal["type"].GetInt();

    if (propertyInfoVal.HasMember("value")) {
        const auto &val = propertyInfoVal["value"];
        if (val.IsArray()) {
            std::vector<float> arr;
            arr.reserve(val.GetArray().Size());
            for (const auto &e : val.GetArray()) {
                if (e.IsNumber()) {
                    arr.emplace_back(e.GetFloat());
                }
            }
            ret.value = std::move(arr);
        } else if (val.IsString()) {
            ret.value = val.GetString();
        } else {
            CC_ASSERT(false);
        }
    }

    if (propertyInfoVal.HasMember("handleInfo")) {
        ret.handleInfo = jsonToPropertyHandleInfo(propertyInfoVal["handleInfo"]);
        // using IPropertyHandleInfo = std::tuple<std::string, uint32_t, gfx::Type>;
        //        CC_LOG_DEBUG("handleInfo: %s, %u, %u", std::get<0>(ret.handleInfo.value()).c_str(), std::get<1>(ret.handleInfo.value()), static_cast<uint32_t>(std::get<2>(ret.handleInfo.value())));
    }

    if (propertyInfoVal.HasMember("samplerHash")) {
        ret.samplerHash = propertyInfoVal.GetUint64();
        //        CC_LOG_DEBUG("samplerHash: %lu", ret.samplerHash.value());
    }

    return ret;
}

static PassPropertyInfoMap jsonToPassPropertyInfoMap(const rapidjson::Value &propertyInfoMapVal) {
    PassPropertyInfoMap propertyInfoMap;

    for (const auto &propertyVal : propertyInfoMapVal.GetObject()) {
        const auto *name  = propertyVal.name.GetString();
        const auto &value = propertyVal.value;
        propertyInfoMap.emplace(name, jsonToPropertyInfo(value));
    }

    return propertyInfoMap;
}

static gfx::RasterizerState *jsonToRasterizerState(const rapidjson::Value &rasterizerStateVal) {
    gfx::RasterizerState *rasterizerState = new gfx::RasterizerState(); //cjh TODO: how to release, shared_ptr?

    CC_ASSERT(rasterizerStateVal.IsObject());

    if (rasterizerStateVal.HasMember("cullMode")) {
        rasterizerState->cullMode = static_cast<gfx::CullMode>(rasterizerStateVal["cullMode"].GetInt());
        //        CC_LOG_DEBUG("cullMode: %d", static_cast<int32_t>(rasterizerState->cullMode));
    }

    if (rasterizerStateVal.HasMember("isDiscard")) {
        rasterizerState->isDiscard = rasterizerStateVal["isDiscard"].GetUint();
    }

    if (rasterizerStateVal.HasMember("polygonMode")) {
        rasterizerState->polygonMode = static_cast<gfx::PolygonMode>(rasterizerStateVal["polygonMode"].GetInt());
    }

    if (rasterizerStateVal.HasMember("shadeModel")) {
        rasterizerState->shadeModel = static_cast<gfx::ShadeModel>(rasterizerStateVal["shadeModel"].GetInt());
    }

    if (rasterizerStateVal.HasMember("isFrontFaceCCW")) {
        rasterizerState->isFrontFaceCCW = rasterizerStateVal["isFrontFaceCCW"].GetUint();
    }

    if (rasterizerStateVal.HasMember("depthBiasEnabled")) {
        rasterizerState->depthBiasEnabled = rasterizerStateVal["depthBiasEnabled"].GetUint();
    }

    if (rasterizerStateVal.HasMember("depthBias")) {
        rasterizerState->depthBias = rasterizerStateVal["depthBias"].GetFloat();
    }

    if (rasterizerStateVal.HasMember("depthBiasClamp")) {
        rasterizerState->depthBiasClamp = rasterizerStateVal["depthBiasClamp"].GetFloat();
    }

    if (rasterizerStateVal.HasMember("depthBiasSlop")) {
        rasterizerState->depthBiasSlop = rasterizerStateVal["depthBiasSlop"].GetFloat();
    }

    if (rasterizerStateVal.HasMember("isDepthClip")) {
        rasterizerState->isDepthClip = rasterizerStateVal["isDepthClip"].GetUint();
    }

    if (rasterizerStateVal.HasMember("isMultisample")) {
        rasterizerState->isMultisample = rasterizerStateVal["isMultisample"].GetUint();
    }

    if (rasterizerStateVal.HasMember("lineWidth")) {
        rasterizerState->lineWidth = rasterizerStateVal["lineWidth"].GetFloat();
    }

    return rasterizerState;
}

static gfx::DepthStencilState *jsonToDepthStencilState(const rapidjson::Value &val) {
    gfx::DepthStencilState *dss = new gfx::DepthStencilState(); //cjh TODO: how to release, shared_ptr?

    CC_ASSERT(val.IsObject());

    if (val.HasMember("depthTest")) {
        dss->depthTest = val["depthTest"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("depthWrite")) {
        dss->depthWrite = val["depthWrite"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("depthFunc")) {
        dss->depthFunc = static_cast<gfx::ComparisonFunc>(val["depthFunc"].GetInt());
    }

    if (val.HasMember("stencilTestFront")) {
        dss->stencilTestFront = val["stencilTestFront"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("stencilFuncFront")) {
        dss->stencilFuncFront = static_cast<gfx::ComparisonFunc>(val["stencilFuncFront"].GetInt());
    }

    if (val.HasMember("stencilReadMaskFront")) {
        dss->stencilReadMaskFront = val["stencilReadMaskFront"].GetUint();
    }

    if (val.HasMember("stencilWriteMaskFront")) {
        dss->stencilWriteMaskFront = val["stencilWriteMaskFront"].GetUint();
    }

    if (val.HasMember("stencilFailOpFront")) {
        dss->stencilFailOpFront = static_cast<gfx::StencilOp>(val["stencilFailOpFront"].GetUint());
    }

    if (val.HasMember("stencilZFailOpFront")) {
        dss->stencilZFailOpFront = static_cast<gfx::StencilOp>(val["stencilZFailOpFront"].GetUint());
    }

    if (val.HasMember("stencilPassOpFront")) {
        dss->stencilPassOpFront = static_cast<gfx::StencilOp>(val["stencilPassOpFront"].GetUint());
    }

    if (val.HasMember("stencilRefFront")) {
        dss->stencilRefFront = val["stencilRefFront"].GetUint();
    }

    if (val.HasMember("stencilTestBack")) {
        dss->stencilTestBack = val["stencilTestBack"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("stencilFuncBack")) {
        dss->stencilFuncBack = static_cast<gfx::ComparisonFunc>(val["stencilFuncBack"].GetInt());
    }

    if (val.HasMember("stencilReadMaskBack")) {
        dss->stencilReadMaskBack = val["stencilReadMaskBack"].GetUint();
    }

    if (val.HasMember("stencilWriteMaskBack")) {
        dss->stencilWriteMaskBack = val["stencilWriteMaskBack"].GetUint();
    }

    if (val.HasMember("stencilFailOpBack")) {
        dss->stencilFailOpBack = static_cast<gfx::StencilOp>(val["stencilFailOpBack"].GetInt());
    }

    if (val.HasMember("stencilZFailOpBack")) {
        dss->stencilZFailOpBack = static_cast<gfx::StencilOp>(val["stencilZFailOpBack"].GetInt());
    }

    if (val.HasMember("stencilPassOpBack")) {
        dss->stencilPassOpBack = static_cast<gfx::StencilOp>(val["stencilPassOpBack"].GetInt());
    }

    if (val.HasMember("stencilRefBack")) {
        dss->stencilWriteMaskBack = val["stencilRefBack"].GetUint();
    }

    return dss;
}

static void jsonToBlendTarget(const rapidjson::Value &val, gfx::BlendTarget *outBlendTarget) {
    if (outBlendTarget == nullptr) {
        return;
    }

    CC_ASSERT(val.IsObject());

    if (val.HasMember("blend")) {
        outBlendTarget->blend = val["blend"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("blendSrc")) {
        outBlendTarget->blendSrc = static_cast<gfx::BlendFactor>(val["blendSrc"].GetInt());
    }

    if (val.HasMember("blendDst")) {
        outBlendTarget->blendDst = static_cast<gfx::BlendFactor>(val["blendDst"].GetInt());
    }

    if (val.HasMember("blendEq")) {
        outBlendTarget->blendEq = static_cast<gfx::BlendOp>(val["blendEq"].GetInt());
    }

    if (val.HasMember("blendSrcAlpha")) {
        outBlendTarget->blendSrcAlpha = static_cast<gfx::BlendFactor>(val["blendSrcAlpha"].GetInt());
    }

    if (val.HasMember("blendDstAlpha")) {
        outBlendTarget->blendDstAlpha = static_cast<gfx::BlendFactor>(val["blendDstAlpha"].GetInt());
    }

    if (val.HasMember("blendAlphaEq")) {
        outBlendTarget->blendAlphaEq = static_cast<gfx::BlendOp>(val["blendAlphaEq"].GetInt());
    }

    if (val.HasMember("blendColorMask")) {
        outBlendTarget->blendColorMask = static_cast<gfx::ColorMask>(val["blendColorMask"].GetInt());
    }
}

static gfx::BlendState *jsonToBlendState(const rapidjson::Value &val) {
    CC_ASSERT(val.IsObject());

    gfx::BlendState *bs = new gfx::BlendState(); //cjh TODO: how to release, shared_ptr?

    if (val.HasMember("isA2C")) {
        bs->isA2C = val["isA2C"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("isIndepend")) {
        bs->isIndepend = val["isIndepend"].GetBool() ? 1 : 0;
    }

    if (val.HasMember("blendColor")) {
        //cjh TODO:
    }

    if (val.HasMember("targets")) {
        if (val["targets"].IsArray()) {
            const auto &targetsVal = val["targets"].GetArray();
            bs->targets.resize(targetsVal.Size());
            int32_t i = 0;
            for (const auto &targetVal : targetsVal) {
                jsonToBlendTarget(targetVal, &bs->targets[i]);
                ++i;
            }
        }
    }

    return bs;
}

static void deserializeTechnique(const rapidjson::Value &techniques, std::vector<ITechniqueInfo> &cTechniques) {
    if (techniques.IsArray()) {
        index_t techIndex = 0;
        cTechniques.resize(techniques.GetArray().Size());
        for (const auto &technique : techniques.GetArray()) {
            if (technique.IsObject()) {
                auto &cTechnique = cTechniques[techIndex];
                if (technique.HasMember("name")) {
                    cTechnique.name = technique["name"].GetString();
                    //                    CC_LOG_DEBUG("tech name: %s", _techniques[techIndex].name.value().c_str());
                }

                if (technique.HasMember("passes")) {
                    const auto &passesVal = technique["passes"];
                    if (passesVal.IsArray()) {
                        cTechnique.passes.resize(passesVal.GetArray().Size());
                        index_t passIndex = 0;
                        for (const auto &passVal : passesVal.GetArray()) {
                            auto &cPass = cTechnique.passes[passIndex];

                            // Filling IPassInfo is enough, the properties in IPassInfoFull will be assigned in Material::createPasses
                            if (passVal.IsObject()) {
                                // IPassInfo
                                cPass.program = passVal["program"].GetString();
                                //                                CC_LOG_DEBUG("program: %s", cPass.program.c_str());
                                if (passVal.HasMember("embeddedMacros")) {
                                    cPass.embeddedMacros = jsonToMacroRecord(passVal["embeddedMacros"]);
                                }

                                if (passVal.HasMember("propertyIndex")) {
                                    cPass.propertyIndex = passVal["propertyIndex"].GetInt();
                                    //                                    CC_LOG_DEBUG("propertyIndex: %d", cPass.propertyIndex);
                                }

                                if (passVal.HasMember("switch")) {
                                    cPass.switch_ = passVal["switch"].GetString();
                                    //                                    CC_LOG_DEBUG("switch: %s", cPass.switch_.value().c_str());
                                }

                                if (passVal.HasMember("properties")) {
                                    cPass.properties = jsonToPassPropertyInfoMap(passVal["properties"]);
                                }

                                // IPassStates
                                if (passVal.HasMember("priority")) {
                                    cPass.priority = passVal["priority"].GetInt();
                                    //                                    CC_LOG_DEBUG("priority: %d", cPass.priority.value());
                                }

                                if (passVal.HasMember("primitive")) {
                                    cPass.primitive = static_cast<gfx::PrimitiveMode>(passVal["primitive"].GetInt());
                                }

                                if (passVal.HasMember("stage")) {
                                    cPass.stage = static_cast<pipeline::RenderPassStage>(passVal["stage"].GetInt());
                                }

                                if (passVal.HasMember("rasterizerState")) {
                                    cPass.rasterizerState = jsonToRasterizerState(passVal["rasterizerState"]);
                                }

                                if (passVal.HasMember("depthStencilState")) {
                                    cPass.depthStencilState = jsonToDepthStencilState(passVal["depthStencilState"]);
                                }

                                if (passVal.HasMember("blendState")) {
                                    cPass.blendState = jsonToBlendState(passVal["blendState"]);
                                }

                                if (passVal.HasMember("dynamicStates")) {
                                    cPass.dynamicStates = static_cast<gfx::DynamicStateFlags>(passVal["dynamicStates"].GetInt());
                                }

                                if (passVal.HasMember("phase")) {
                                    cPass.phase = passVal["phase"].GetString();
                                    CC_LOG_DEBUG("phase: %s", cPass.phase.value().c_str());
                                }
                            }

                            ++passIndex;
                        }
                    }
                }
            }
            ++techIndex;
        }
    }
}

void EffectAsset::deserialize(const rapidjson::Value &serializedData) {
    CC_ASSERT(serializedData.IsObject());
    _name = serializedData["name"].GetString(); //cjh TODO: name needs to be deserialize in CCObject class.
                                                //    CC_LOG_DEBUG("EffectAsset::deserialize: %s", _name.c_str());
    const auto &techniques = serializedData["techniques"];
    deserializeTechnique(techniques, _techniques);
}

} // namespace cc
