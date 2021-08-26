#pragma once

#include "renderer/core/ProgramLib.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include "core/Types.h"
#include "core/assets/EffectAsset.h"
#include "renderer/core/PassUtils.h"
#include "renderer/gfx-base/GFXDef-common.h"
#include "renderer/gfx-base/GFXPipelineLayout.h"
#include "renderer/pipeline/Define.h"

namespace cc {

template <typename T>
auto getBitCount(T cnt) {
    return std::ceil(std::log2(cnt > 2 ? 2 : cnt)); // std::max checks number types
}

static bool recordAsBool(const MacroRecord::mapped_type &v) {
    if (std::holds_alternative<bool>(v)) {
        return std::get<bool>(v);
    }
    if (std::holds_alternative<std::string>(v)) {
        return std::get<std::string>(v) == "true";
    }
    if (std::holds_alternative<float>(v)) {
        return std::get<float>(v) != 0;
    }
    return false;
}

static std::string recordAsString(const MacroRecord::mapped_type &v) {
    if (std::holds_alternative<bool>(v)) {
        return std::get<bool>(v) ? "1" : "0";
    }
    if (std::holds_alternative<std::string>(v)) {
        return std::get<std::string>(v);
    }
    if (std::holds_alternative<float>(v)) {
        return std::to_string(std::get<float>(v));
    }
    return "";
}

std::string mapDefine(const IDefineInfo &info, const std::optional<MacroRecord::mapped_type> &def) {
    if (info.type == "boolean") {
        return def.has_value() ? (recordAsBool(def.value()) ? "1" : "0") : "0";
    }
    if (info.type == "string") {
        return def.has_value() ? recordAsString(def.value()) : info.options[0];
    }
    if (info.type == "number") {
        return def.has_value() ? std::to_string(std::get<float>(def.value())) : std::to_string(info.range[0]);
    }
    CC_LOG_DEBUG("unknown define type '%s'", info.type.c_str());
    return "-1"; // should neven happen
}

std::vector<IMacroInfo> prepareDefines(const MacroRecord &records, const std::vector<IDefineRecord> &defList) {
    std::vector<IMacroInfo> macros{};
    for (const auto &tmp : defList) {
        auto name      = tmp.name;
        auto it        = records.find(name);
        auto value     = mapDefine(tmp, it == records.end() ? std::nullopt : std::optional(it->second));
        auto isDefault = !recordAsBool(it->second);
        macros.emplace_back(IMacroInfo{name, value, isDefault});
    }
    return macros;
}

std::string getShaderInstanceName(const std::string &name, const std::vector<IMacroInfo> &macros) {
    std::stringstream ret;
    ret << name;
    for (const auto &cur : macros) {
        if (!cur.isDefault) {
            ret << "|" << cur.name << cur.value;
        }
    }
    return ret.str();
}

void insertBuiltinBindings(const IProgramInfo &tmpl, const ITemplateInfo &tmplInfo, const pipeline::DescriptorSetLayoutInfos &source,
                           const std::string &type, std::vector<gfx::DescriptorSetLayoutBinding> *outBindings) {
    auto                           target = type == "globals" ? tmpl.builtins.globals : tmpl.builtins.locals;
    std::vector<gfx::UniformBlock> tempBlocks{};
    // TODO(PatriceJiang): dd
    // for (auto i = 0; i < target.blocks.size(); i++) {
    //     const auto &b       = target.blocks[i];
    //     const auto &info    = source.layouts[b.name] as UniformBlock | undefined;
    //     auto        binding = info && source.bindings.find((bd) = > bd.binding == = info.binding);
    //     if (!info || !binding || !(binding.descriptorType & DESCRIPTOR_BUFFER_TYPE)) {
    //         console.warn(`builtin UBO '${b.name}' not available !`);
    //         continue;
    //     }
    //     tempBlocks.push(info);
    //     if (outBindings && !outBindings.includes(binding)) outBindings.push(binding);
    // }
    // Array.prototype.unshift.apply(tmplInfo.gfxBlocks, tempBlocks);
    // const tempSamplerTextures : UniformSamplerTexture[] = [];
    // for (let i = 0; i < target.samplerTextures.length; i++) {
    //     const s       = target.samplerTextures[i];
    //     const info    = source.layouts[s.name] as UniformSamplerTexture;
    //     const binding = info && source.bindings.find((bd) = > bd.binding == = info.binding);
    //     if (!info || !binding || !(binding.descriptorType & DESCRIPTOR_SAMPLER_TYPE)) {
    //         console.warn(`builtin samplerTexture '${s.name}' not available !`);
    //         continue;
    //     }
    //     tempSamplerTextures.push(info);
    //     if (outBindings && !outBindings.includes(binding)) outBindings.push(binding);
    // }
    // Array.prototype.unshift.apply(tmplInfo.gfxSamplerTextures, tempSamplerTextures);
    // if (outBindings) outBindings.sort((a, b) = > a.binding - b.binding);
}

int getSize(const IBlockInfo &block) {
    auto s = 0;
    for (const auto &m : block.members) {
        s += getTypeSize(m.type) * m.count;
    }
}

auto genHandles(const IProgramInfo &tmpl) {
    Record<std::string, int> handleMap{};
    // block member handles
    for (const auto &block : tmpl.blocks) {
        const auto members = block.members;
        auto       offset  = 0;
        for (const auto &uniform : members) {
            handleMap[uniform.name] = genHandle(PropertyType::BUFFER,
                                                static_cast<uint32_t>(pipeline::SetIndex::MATERIAL),
                                                block.binding,
                                                uniform.type,
                                                offset);
            offset += (getTypeSize(uniform.type) >> 2) * uniform.count;
        }
    }
    // samplerTexture handles
    for (const auto &samplerTexture : tmpl.samplerTextures) {
        handleMap[samplerTexture.name] = genHandle(PropertyType::TEXTURE,
                                                   static_cast<uint32_t>(pipeline::SetIndex::MATERIAL),
                                                   samplerTexture.binding,
                                                   samplerTexture.type);
    }
    return handleMap;
}

bool dependencyCheck(const std::vector<std::string> &dependencies, const MacroRecord &defines) {
    for (const auto &d : dependencies) {
        if (d[0] == '!') { // negative dependency
            if (defines.find(d.substr(1)) != defines.end()) {
                return false;
            }
        } else if (defines.count(d) == 0 ? true : recordAsBool(defines.at(d))) {
            return false;
        }
    }
    return true;
}

std::vector<gfx::Attribute> getActiveAttributes(const IProgramInfo &tmpl, const ITemplateInfo &tmplInfo, const MacroRecord &defines) {
    std::vector<gfx::Attribute> out{};
    auto                        attributes    = tmpl.attributes;
    auto                        gfxAttributes = tmplInfo.gfxAttributes;
    for (auto i = 0; i < attributes.size(); i++) {
        if (!dependencyCheck(attributes[i].defines, defines)) {
            continue;
        }
        out.emplace_back(gfxAttributes[i]);
    }
    return out;
}

const char *getDeviceShaderVersion(const gfx::Device &device) {
    switch (device.getGfxAPI()) {
        case gfx::API::GLES2:
        case gfx::API::WEBGL:
            return "glsl1";
        case gfx::API::GLES3:
        case gfx::API::WEBGL2:
            return "glsl3";
        default:
            return "glsl4";
    }
}

void ProgramLib::regist(EffectAsset &effect) {
    for (auto i = 0; i < effect._shaders.size(); i++) {
        auto tmpl        = define(effect._shaders[i]);
        tmpl->effectName = effect.getName();
    }
}

IProgramInfo *ProgramLib::define(IShaderInfo &shader) {
    auto itCurrTmpl = _templates.find(shader.name);
    if (itCurrTmpl != _templates.end() && itCurrTmpl->second.hash == shader.hash) {
        return &itCurrTmpl->second;
    }
    auto &currTmpl = itCurrTmpl->second;
    //TODO(PatriceJiang): need copy
    IProgramInfo tmpl;
    tmpl.effectName = shader.name;
    // tmpl.defines = shader.defines; //TODO: can not do simple copy
    tmpl.defines.resize(shader.defines.size());
    for (auto i = 0; i < shader.defines.size(); i++) {
        *reinterpret_cast<IDefineInfo *>(&tmpl.defines[i]) = shader.defines[i];
    }
    // tmpl.constantMacros = ?? //TODO(PatriceJiang)
    // tmpl.uber = ??   //TODO(PatriceJiang)

    // calculate option mask offset
    auto offset = 0;
    for (auto i = 0; i < tmpl.defines.size(); i++) {
        auto &def = tmpl.defines[i];
        auto  cnt = 1;
        if (def.type == "number") {
            auto &range = def.range;
            cnt         = getBitCount(range[1] - range[0] + 1); // inclusive on both ends
            def.map     = [=](std::any value) { return static_cast<int>(std::any_cast<float>(value) - range[0]); };
        } else if (def.type == "string") {
            cnt     = getBitCount(def.options.size());
            def.map = [=](std::any value) {
                int idx = std::find(def.options.begin(), def.options.end(), std::any_cast<std::string>(value)) - def.options.begin();
                return static_cast<int>(std::max(0, idx));
            };
        } else if (def.type == "boolean") {
            def.map = [=](std::any value) {
                return std::any_cast<bool>(value) ? 1 : 0;
            };
        }
        def.offset = offset;
        offset += cnt;
    }
    if (offset > 31) {
        tmpl.uber = true;
    }
    // generate constant macros
    {
        std::stringstream ss;
        for (auto &key : tmpl.builtins.statistics) {
            ss << "#define " << key.first << " " << key.second << std::endl;
            tmpl.constantMacros += (std::string("#define ") + key.first + " " + key.second + "\n");
        }
        tmpl.constantMacros = ss.str();
    }
    // store it
    _templates[shader.name] = tmpl;
    if (_templateInfos.count(tmpl.hash > 0)) {
        ITemplateInfo tmplInfo{};
        // cache material-specific descriptor set layout
        tmplInfo.samplerStartBinding = tmpl.blocks.size();
        tmplInfo.gfxBlocks           = {};
        tmplInfo.gfxSamplerTextures  = {};
        tmplInfo.bindings            = {};
        tmplInfo.blockSizes          = {};
        for (auto i = 0; i < tmpl.blocks.size(); i++) {
            auto &block = tmpl.blocks[i];
            tmplInfo.blockSizes.emplace_back(getSize(block));
            tmplInfo.bindings.emplace_back(gfx::DescriptorSetLayoutBinding{block.binding,
                                                                           block.descriptorType || gfx::DescriptorType::UNIFORM_BUFFER, 1, block.stageFlags});
            tmplInfo.gfxBlocks.emplace_back(new UniformBlock(SetIndex.MATERIAL, block.binding, block.name,
                                                             block.members.map((m) = > new Uniform(m.name, m.type, m.count)), 1)); // effect compiler guarantees block count = 1
        }
        for (let i = 0; i < tmpl.samplerTextures.length; i++) {
            const samplerTexture = tmpl.samplerTextures[i];
            tmplInfo.bindings.push(new DescriptorSetLayoutBinding(samplerTexture.binding,
                                                                  samplerTexture.descriptorType || DescriptorType.SAMPLER_TEXTURE, samplerTexture.count, samplerTexture.stageFlags));
            tmplInfo.gfxSamplerTextures.push(new UniformSamplerTexture(
                SetIndex.MATERIAL, samplerTexture.binding, samplerTexture.name, samplerTexture.type, samplerTexture.count, ));
        }
        tmplInfo.gfxAttributes = [];
        for (let i = 0; i < tmpl.attributes.length; i++) {
            const attr = tmpl.attributes[i];
            tmplInfo.gfxAttributes.push(new Attribute(attr.name, attr.format, attr.isNormalized, 0, attr.isInstanced, attr.location));
        }
        insertBuiltinBindings(tmpl, tmplInfo, localDescriptorSetLayout, 'locals');

        tmplInfo.gfxStages = [];
        tmplInfo.gfxStages.push(new ShaderStage(ShaderStageFlagBit.VERTEX, ''));
        tmplInfo.gfxStages.push(new ShaderStage(ShaderStageFlagBit.FRAGMENT, ''));
        tmplInfo.handleMap  = genHandles(tmpl);
        tmplInfo.setLayouts = [];

        this._templateInfos[tmpl.hash] = tmplInfo;
    }
    return tmpl;
    // return nullptr;
}

/**
     * @en Gets the shader template with its name
     * @zh 通过名字获取 Shader 模板
     * @param name Target shader name
     */

IProgramInfo *ProgramLib::getTemplate(const std::string &name) {
    auto it = _templates.find(name);
    return it != _templates.end() ? &it->second : nullptr;
}

/**
     * @en Gets the shader template info with its name
     * @zh 通过名字获取 Shader 模版信息
     * @param name Target shader name
     */

ITemplateInfo *ProgramLib::getTemplateInfo(const std::string &name) {
    auto it = _templates.find(name);
    assert(it != _templates.end());
    auto hash   = it->second.hash;
    auto itInfo = _templateInfos.find(hash);
    return itInfo != _templateInfos.end() ? &itInfo->second : nullptr;
}

/**
     * @en Gets the pipeline layout of the shader template given its name
     * @zh 通过名字获取 Shader 模板相关联的管线布局
     * @param name Target shader name
     */
gfx::DescriptorSetLayout *ProgramLib::getDescriptorSetLayout(gfx::Device &device, const std::string &name, bool isLocal) {
    auto itTmpl = _templates.find(name);
    assert(itTmpl != _templates.end());
    const auto &tmpl      = itTmpl->second;
    auto        itTplInfo = _templateInfos.find(tmpl.hash);
    auto &      tmplInfo  = itTplInfo->second;
    if (tmplInfo.setLayouts.empty()) {
        gfx::DescriptorSetLayoutInfo info;
        tmplInfo.setLayouts.resize(static_cast<size_t>(pipeline::SetIndex::COUNT));
        info.bindings                                                           = tmplInfo.bindings;
        tmplInfo.setLayouts[static_cast<index_t>(pipeline::SetIndex::MATERIAL)] = device.createDescriptorSetLayout(info);
        info.bindings                                                           = pipeline::localDescriptorSetLayout.bindings;
        tmplInfo.setLayouts[static_cast<index_t>(pipeline::SetIndex::LOCAL)]    = device.createDescriptorSetLayout(info);
    }
    return tmplInfo.setLayouts[isLocal ? static_cast<index_t>(pipeline::SetIndex::LOCAL) : static_cast<index_t>(pipeline::SetIndex::MATERIAL)];
}

std::string ProgramLib::getKey(const std::string &name, const MacroRecord &defines) {
    auto itTpl = _templates.find(name);
    assert(itTpl != _templates.end());
    auto &tmpl     = itTpl->second;
    auto &tmplDefs = tmpl.defines;
    if (tmpl.uber) {
        std::stringstream key;
        for (auto i = 0; i < tmplDefs.size(); i++) {
            auto &tmplDef = tmplDefs[i];
            auto  itDef   = defines.find(tmplDef.name);
            if (itDef == defines.end() || !tmplDef.map) {
                continue;
            }
            auto &value  = itDef->second;
            auto  mapped = tmplDef.map(value);
            auto  offset = tmplDef.offset;
            key << offset << mapped << "|";
        }
        return key.str() + std::to_string(tmpl.hash);
    }
    auto              key = 0;
    std::stringstream ss;
    for (auto i = 0; i < tmplDefs.size(); i++) {
        auto &tmplDef = tmplDefs[i];
        auto  itDef   = defines.find(tmplDef.name);
        if (itDef == defines.end() || !tmplDef.map) {
            continue;
        }
        auto &value  = itDef->second;
        auto  mapped = tmplDef.map(value);
        auto  offset = tmplDef.offset;
        key |= (mapped << offset);
    }
    ss << std::hex << key;
    return ss.str() + std::to_string(tmpl.hash);
}

void ProgramLib::destroyShaderByDefines(const MacroRecord &defines) {
    if (defines.empty()) return;
    std::vector<std::string> defineValues;
    for (const auto &i : defines) {
        defineValues.emplace_back(i.first + recordAsString(i.second));
    }
    std::vector<std::string> matchedKeys;
    for (const auto &i : _cache) {
        bool matched = true;
        for (const auto &v : defineValues) {
            if (i.first.find(v) == std::string::npos) {
                matched = false;
                break;
            }
        }
        if (matched) {
            matchedKeys.emplace_back(i.first);
        }
    }
    for (const auto &key : matchedKeys) {
        CC_LOG_DEBUG("destroyed shader %s", key.c_str());
        _cache[key]->destroy(); // TODO(PatriceJiang): unref ?
        _cache.erase(key);
    }
}

gfx::Shader *ProgramLib::getGFXShader(gfx::Device &device, const std::string &name, MacroRecord &defines,
                                      const pipeline::RenderPipeline &pipeline, std::string *key_) {
    for (const auto it : pipeline.getMacros()) {
        defines[it.first] = it.second;
    }

    std::string key;
    if (!key_) key = getKey(name, defines);
    auto itRes = _cache.find(key);
    if (itRes != _cache.end()) {
        return itRes->second;
    }

    auto itTpl = _templates.find(name);
    assert(itTpl != _templates.end());

    const auto &tmpl      = itTpl->second;
    const auto  itTplInfo = _templateInfos.find(tmpl.hash);
    assert(itTplInfo != _templateInfos.end());
    auto tmplInfo = itTplInfo->second;

    if (!tmplInfo.pipelineLayout) {
        getDescriptorSetLayout(device, name); // ensure set layouts have been created
        insertBuiltinBindings(tmpl, tmplInfo, pipeline::globalDescriptorSetLayout, "globals", nullptr);
        tmplInfo.setLayouts[static_cast<index_t>(pipeline::SetIndex::GLOBAL)] = pipeline.getDescriptorSetLayout();
        tmplInfo.pipelineLayout                                               = device.createPipelineLayout(gfx::PipelineLayoutInfo{tmplInfo.setLayouts});
    }

    std::vector<IMacroInfo> macroArray = prepareDefines(defines, tmpl.defines);
    std::stringstream       ss;
    ss << std::endl;
    for (const auto &m : macroArray) {
        ss << "#define " << m.name << " " << m.value << std::endl;
    }
    auto prefix = pipeline.getConstantMacros() + tmpl.constantMacros + ss.str();

    const IShaderSource *src                 = &tmpl.glsl3;
    const auto *         deviceShaderVersion = getDeviceShaderVersion(device);
    if (deviceShaderVersion) {
        src = tmpl.getSource(deviceShaderVersion);
    } else {
        CC_LOG_ERROR("Invalid GFX API!");
    }
    tmplInfo.gfxStages[0].source = prefix + src->vert;
    tmplInfo.gfxStages[1].source = prefix + src->frag;

    // strip out the active attributes only, instancing depend on this
    auto attributes = getActiveAttributes(tmpl, tmplInfo, defines);

    auto instanceName          = getShaderInstanceName(name, macroArray);
    auto shaderInfo            = gfx::ShaderInfo{instanceName, tmplInfo.gfxStages, attributes, tmplInfo.gfxBlocks};
    shaderInfo.samplerTextures = tmplInfo.gfxSamplerTextures;
    auto *shader               = device.createShader(shaderInfo);
    _cache[key]                = shader;
    return shader;
}

} // namespace cc