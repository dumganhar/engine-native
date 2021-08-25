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

#include <string>
#include <unordered_map>
#include "base/Value.h"
#include "core/Types.h"
#include "core/assets/Asset.h"
#include "renderer/core/PassUtils.h"
#include "renderer/gfx-base/GFXDef.h"
#include "renderer/pipeline/Define.h"
#include "scene/Define.h"

namespace cc {

struct IPropertyInfo {
    int32_t             type;        // auto-extracted from shader
    ValueVector         handleInfo;  //cjh check: ?: [string, number, number]; // auto-generated from 'target'
    uint32_t            samplerHash; // auto-generated from 'sampler'
    std::vector<double> numberValue; //cjh     ?: number[] | string;
    std::string         stringValue;
};

// Pass instance itself are compliant to IPassStates too
struct IPassStates {
    std::optional<int32_t>             priority;
    gfx::PrimitiveMode                 primitive;
    pipeline::RenderPassStage          stage;
    gfx::RasterizerState               rasterizerState;
    gfx::DepthStencilState             depthStencilState;
    gfx::BlendState                    blendState;
    gfx::DynamicStateFlags             dynamicStates;
    std::variant<std::string, int32_t> phase;
};

using PassOverrides = IPassStates;

struct IPassInfo : public IPassStates {
    std::string                                    program; // auto-generated from 'vert' and 'frag'
    MacroRecord                                    embeddedMacros;
    int32_t                                        propertyIndex;
    std::string                                    switch_;
    std::unordered_map<std::string, IPropertyInfo> properties;
};

struct ITechniqueInfo {
    std::vector<IPassInfo> passes;
    std::string            name;
};

struct IBlockInfo {
    int32_t                   binding;
    std::string               name;
    std::vector<gfx::Uniform> members;
    uint32_t                  count;
    gfx::ShaderStageFlags     stageFlags;
    gfx::DescriptorType       descriptorType;
};

struct ISamplerTextureInfo {
    int32_t               binding; //cjh : number;
    std::string           name;
    gfx::Type             type;
    uint32_t              count;
    gfx::ShaderStageFlags stageFlags;
    gfx::DescriptorType   descriptorType;
};

struct IAttributeInfo : public gfx::Attribute {
    std::vector<std::string> defines;
};

struct IDefineInfo {
    std::string              name;
    std::string              type;
    std::vector<float>       range; //cjh number is float?  ?: number[];
    std::vector<std::string> options;
    std::string              defaultVal;
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
    uint64_t                         hash; //cjh hash is 64 bit?
    IShaderSource                    glsl4;
    IShaderSource                    glsl3;
    IShaderSource                    glsl1;
    IBuiltins                        builtins;
    std::vector<IDefineInfo>         defines;
    std::vector<IBlockInfo>          blocks;
    std::vector<ISamplerTextureInfo> samplerTextures;
    std::vector<IAttributeInfo>      attributes;
};

//cjh    [name: string]: boolean[] | number[] | string[];
using IPreCompileInfo = std::unordered_map<std::string, Value>;

class EffectAsset final : public Asset {
public:
    using Super = Asset;
    /**
     * @en Register the effect asset to the static map
     * @zh 将指定 effect 注册到全局管理器。
     */
    static void registerAsset(const EffectAsset *asset);

    /**
     * @en Unregister the effect asset from the static map
     * @zh 将指定 effect 从全局管理器移除。
     */
    static void remove(const std::string &name);
    static void remove(const EffectAsset *asset);

    /**
     * @en Get the effect asset by the given name.
     * @zh 获取指定名字的 effect 资源。
     */
    static const EffectAsset *get(const std::string &name);

    /**
     * @en Get all registered effect assets.
     * @zh 获取所有已注册的 effect 资源。
     */
    static std::unordered_map<std::string, const EffectAsset *> &getAll() { return __effects; }

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
    void initDefault(const std::string &uuid) override;
    bool validate() const override;

protected:
    void _precompile();

protected:
    static std::unordered_map<std::string, const EffectAsset *> __effects; //cjh TODO: how to clear when game exits.

    CC_DISALLOW_COPY_MOVE_ASSIGN(EffectAsset);
};

} // namespace cc
