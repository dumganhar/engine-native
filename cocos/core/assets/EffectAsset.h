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

#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>

#include "base/Value.h"
#include "core/Types.h"
#include "core/assets/Asset.h"
#include "gfx-base/GFXDef-common.h"
#include "gfx-base/GFXShader.h"
#include "rapidjson/document.h"
#include "renderer/core/PassUtils.h"
#include "renderer/gfx-base/GFXDef.h"
#include "renderer/pipeline/Define.h"
//#include "scene/Define.h"

namespace cc {

using IPropertyHandleInfo = std::tuple<std::string, uint32_t, gfx::Type>;

struct IPropertyInfo {
    int32_t                                                      type;        // auto-extracted from shader
    std::optional<IPropertyHandleInfo>                           handleInfo;  // auto-generated from 'target'
    std::optional<uint64_t>                                      samplerHash; // auto-generated from 'sampler'
    std::optional<std::variant<std::vector<float>, std::string>> value;
};

// Pass instance itself are compliant to IPassStates too
struct IPassStates {
    std::optional<int32_t>                   priority;
    std::optional<gfx::PrimitiveMode>        primitive;
    std::optional<pipeline::RenderPassStage> stage;
    std::optional<gfx::RasterizerState *>    rasterizerState; //cjh TODO: need to change to shared_ptr?
    std::optional<gfx::DepthStencilState *>  depthStencilState;
    std::optional<gfx::BlendState *>         blendState;
    std::optional<gfx::DynamicStateFlags>    dynamicStates;
    std::optional<std::string>               phase;
};

using PassOverrides = IPassStates;

using PassPropertyInfoMap = std::unordered_map<std::string, IPropertyInfo>;

struct IPassInfo : public IPassStates {
    std::string                        program; // auto-generated from 'vert' and 'frag'
    std::optional<MacroRecord>         embeddedMacros;
    index_t                            propertyIndex{-1};
    std::optional<std::string>         switch_;
    std::optional<PassPropertyInfoMap> properties;
};

struct IPassInfoFull final : public IPassInfo {
    // generated part
    index_t                      passIndex{0};
    MacroRecord                  defines;
    std::optional<PassOverrides> stateOverrides;
};

struct ITechniqueInfo {
    std::vector<IPassInfoFull> passes;
    std::optional<std::string> name;
};

struct IBlockInfo {
    int32_t                            binding{-1};
    std::string                        name;
    std::vector<gfx::Uniform>          members;
    uint32_t                           count{0};
    gfx::ShaderStageFlags              stageFlags{gfx::ShaderStageFlags::NONE};
    std::optional<gfx::DescriptorType> descriptorType{};
};

struct ISamplerTextureInfo {
    int32_t                            binding{-1}; //cjh : number;
    std::string                        name;
    gfx::Type                          type{gfx::Type::UNKNOWN};
    uint32_t                           count{0};
    gfx::ShaderStageFlags              stageFlags{gfx::ShaderStageFlags::NONE};
    std::optional<gfx::DescriptorType> descriptorType;
};

struct IAttributeInfo : public gfx::Attribute {
    std::vector<std::string> defines;
};

struct IDefineInfo {
    std::string                             name;
    std::string                             type;
    std::optional<std::vector<float>>       range; //cjh number is float?  ?: number[];
    std::optional<std::vector<std::string>> options;
    std::optional<std::string>              defaultVal;
};

struct IBuiltin {
    std::string              name;
    std::vector<std::string> defines;
};

struct IBuiltinInfo {
    std::vector<IBuiltin> blocks;
    std::vector<IBuiltin> samplerTextures;
};

struct IBuiltins {
    IBuiltinInfo                             globals;
    IBuiltinInfo                             locals;
    std::unordered_map<std::string, int32_t> statistics;
};

struct IShaderSource {
    std::string vert;
    std::string frag;
};

struct IShaderInfo {
    std::string                      name;
    uint64_t                         hash{-1ULL}; //cjh hash is 64 bit?
    IShaderSource                    glsl4;
    IShaderSource                    glsl3;
    IShaderSource                    glsl1;
    IBuiltins                        builtins;
    std::vector<IDefineInfo>         defines;
    std::vector<IBlockInfo>          blocks;
    std::vector<ISamplerTextureInfo> samplerTextures;
    std::vector<IAttributeInfo>      attributes;

    const IShaderSource *getSource(const std::string &version) const {
        if (version == "glsl1") return &glsl1;
        if (version == "glsl3") return &glsl4;
        if (version == "glsl4") return &glsl1;
        return nullptr;
    }
};

using IPreCompileInfoValueType = std::variant<std::vector<bool>, std::vector<float>, std::vector<std::string>>; //cjh number is float?
using IPreCompileInfo          = std::unordered_map<std::string, IPreCompileInfoValueType>;

class EffectAsset final : public Asset {
public:
    using Super = Asset;

    EffectAsset()           = default;
    ~EffectAsset() override = default;
    /**
     * @en Register the effect asset to the static map
     * @zh 将指定 effect 注册到全局管理器。
     */
    static void registerAsset(EffectAsset *asset);

    /**
     * @en Unregister the effect asset from the static map
     * @zh 将指定 effect 从全局管理器移除。
     */
    static void remove(const std::string &name);
    static void remove(EffectAsset *asset);

    /**
     * @en Get the effect asset by the given name.
     * @zh 获取指定名字的 effect 资源。
     */
    static EffectAsset *get(const std::string &name);

    using RegisteredEffectAssetMap = std::unordered_map<std::string, EffectAsset *>;
    /**
     * @en Get all registered effect assets.
     * @zh 获取所有已注册的 effect 资源。
     */
    static RegisteredEffectAssetMap &getAll() { return __effects; }

    /**
     * @en The techniques used by the current effect.
     * @zh 当前 effect 的所有可用 technique。

    @serializable
    @editable*/
    std::vector<ITechniqueInfo> _techniques;

    /**
     * @en The shaders used by the current effect.
     * @zh 当前 effect 使用的所有 shader。

    @serializable
    @editable*/
    std::vector<IShaderInfo> _shaders;

    /**
     * @en The preprocess macro combinations for the shader
     * @zh 每个 shader 需要预编译的宏定义组合。

    @serializable
    @editable*/
    std::vector<IPreCompileInfo> _combinations;

    /*
    @serializable
    @editorOnly
     */
    bool hideInEditor = false;

    /**
     * @en The loaded callback which should be invoked by the [[Loader]], will automatically register the effect.
     * @zh 通过 [[Loader]] 加载完成时的回调，将自动注册 effect 资源。
     */
    void onLoaded() override;
    bool destroy() override;
    void initDefault(const std::optional<std::string> &uuid) override;
    bool validate() const override;

    void deserialize(const rapidjson::Value &serializedData);

protected:
    static std::vector<MacroRecord> doCombine(const std::vector<MacroRecord> &cur, const IPreCompileInfo &info, IPreCompileInfo::iterator iter);
    static std::vector<MacroRecord> generateRecords(const std::string &key, const IPreCompileInfoValueType &value);
    static std::vector<MacroRecord> insertInfoValue(const std::vector<MacroRecord> &records,
                                                    const std::string &             key,
                                                    const IPreCompileInfoValueType &value);

    void precompile();

protected:
    static RegisteredEffectAssetMap __effects; //cjh TODO: how to clear when game exits.

    CC_DISALLOW_COPY_MOVE_ASSIGN(EffectAsset);
};

} // namespace cc
