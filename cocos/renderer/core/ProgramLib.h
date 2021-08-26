#pragma once

#include <cmath>
#include <functional>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include "core/Types.h"
#include "core/assets/EffectAsset.h"
#include "renderer/core/PassUtils.h"
#include "renderer/gfx-base/GFXDef-common.h"
#include "renderer/gfx-base/GFXDevice.h"
#include "renderer/gfx-base/GFXPipelineLayout.h"
#include "renderer/pipeline/Define.h"
#include "renderer/pipeline/RenderPipeline.h"

namespace cc {

struct IDefineRecord : public IDefineInfo {
    std::function<int32_t(std::any)> map;
    int32_t                          offset;
};
struct IMacroInfo {
    std::string name;
    std::string value;
    bool        isDefault;
};

struct ITemplateInfo {
    std::vector<gfx::UniformBlock>               gfxBlocks;
    std::vector<gfx::UniformSamplerTexture>      gfxSamplerTextures;
    std::vector<gfx::Attribute>                  gfxAttributes;
    std::vector<float>                           blockSizes;
    std::vector<gfx::ShaderStage>                gfxStages;
    std::vector<gfx::DescriptorSetLayout *>      setLayouts; // TODO(PatriceJiang): pointer / rc
    gfx::PipelineLayout *                        pipelineLayout{nullptr};
    Record<std::string, uint32_t>                handleMap;
    std::vector<gfx::DescriptorSetLayoutBinding> bindings;
    int32_t                                      samplerStartBinding{-1};
};

struct IProgramInfo : public IShaderInfo {
    std::string                effectName;
    std::vector<IDefineRecord> defines;
    std::string                constantMacros;
    bool                       uber; // macro number exceeds default limits, will fallback to string hash
};

const char *getDeviceShaderVersion(const gfx::Device &device);

/**
 * @en The global maintainer of all shader resources.
 * @zh 维护 shader 资源实例的全局管理器。
 */
class ProgramLib {
protected:
    Record<std::string, IProgramInfo>  _templates{}; // per shader
    Record<std::string, gfx::Shader *> _cache         = {};
    Record<uint64_t, ITemplateInfo>    _templateInfos = {};

public:
    void regist(EffectAsset &effect);

    /**
     * @en Register the shader template with the given info
     * @zh 注册 shader 模板。
     */
    IProgramInfo *define(IShaderInfo &shader);

    /**
     * @en Gets the shader template with its name
     * @zh 通过名字获取 Shader 模板
     * @param name Target shader name
     */

    IProgramInfo *getTemplate(const std::string &name);

    /**
     * @en Gets the shader template info with its name
     * @zh 通过名字获取 Shader 模版信息
     * @param name Target shader name
     */

    ITemplateInfo *getTemplateInfo(const std::string &name);

    /**
     * @en Gets the pipeline layout of the shader template given its name
     * @zh 通过名字获取 Shader 模板相关联的管线布局
     * @param name Target shader name
     */
    gfx::DescriptorSetLayout *getDescriptorSetLayout(gfx::Device &device, const std::string &name, bool isLocal = false);

    /**
     * @en
     * Does this library has the specified program
     * @zh
     * 当前是否有已注册的指定名字的 shader
     * @param name Target shader name
     */
    inline bool hasProgram(const std::string &name) const {
        return _templates.count(name) > 0;
    }

    /**
     * @en Gets the shader key with the name and a macro combination
     * @zh 根据 shader 名和预处理宏列表获取 shader key。
     * @param name Target shader name
     * @param defines The combination of preprocess macros
     */
    std::string getKey(const std::string &name, const MacroRecord &defines);

    /**
     * @en Destroy all shader instance match the preprocess macros
     * @zh 销毁所有完全满足指定预处理宏特征的 shader 实例。
     * @param defines The preprocess macros as filter
     */

    void destroyShaderByDefines(const MacroRecord &defines);

    /**
     * @en Gets the shader resource instance with given information
     * @zh 获取指定 shader 的渲染资源实例
     * @param name Shader name
     * @param defines Preprocess macros
     * @param pipeline The [[RenderPipeline]] which owns the render command
     * @param key The shader cache key, if already known
     */
    gfx::Shader *getGFXShader(gfx::Device &device, const std::string &name, MacroRecord &defines,
                              const pipeline::RenderPipeline &pipeline, std::string *key = nullptr);
};

} // namespace cc