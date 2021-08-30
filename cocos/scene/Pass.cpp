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

#include "scene/Pass.h"

#include <sstream>

#include "MurmurHash2/MurmurHash2.h"
#include "core/Root.h"
#include "core/assets/TextureBase.h"
#include "core/builtin/BuiltinResMgr.h"
#include "renderer/core/PassUtils.h"
#include "renderer/gfx-base/GFXDef.h"
#include "renderer/pipeline/Define.h"

namespace cc {
namespace scene {

namespace {

const gfx::BufferInfo _bufferInfo{
    (gfx::BufferUsageBit::UNIFORM | gfx::BufferUsageBit::TRANSFER_DST),
    (gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE),
    0U,
    0U,
    gfx::BufferFlagBit::NONE};

const gfx::BufferViewInfo _bufferViewInfo;

gfx::DescriptorSetInfo _dsInfo;

std::string serializeBlendState(const gfx::BlendState *bs) {
    std::stringstream res;
    res << ",bs," << bs->isA2C;
    for (const auto &t : bs->targets) {
        res << ",bt," << t.blend << "," << static_cast<uint32_t>(t.blendEq) << "," << static_cast<uint32_t>(t.blendAlphaEq) << "," << static_cast<uint32_t>(t.blendColorMask);
        res << "," << static_cast<uint32_t>(t.blendSrc) << "," << static_cast<uint32_t>(t.blendDst) << "," << static_cast<uint32_t>(t.blendSrcAlpha) << "," << static_cast<uint32_t>(t.blendDstAlpha);
    }
    return res.str();
}

std::string serializeRasterizerState(const gfx::RasterizerState *rs) {
    std::stringstream res;
    res << ",rs," << static_cast<uint32_t>(rs->cullMode) << "," << static_cast<uint32_t>(rs->depthBias) << "," << static_cast<uint32_t>(rs->isFrontFaceCCW);
    return res.str();
}

std::string serializeDepthStencilState(const gfx::DepthStencilState *dss) {
    std::stringstream res;
    res << ",dss," << static_cast<uint32_t>(dss->depthTest) << "," << static_cast<uint32_t>(dss->depthWrite) << "," << static_cast<uint32_t>(dss->depthFunc);
    res << "," << static_cast<uint32_t>(dss->stencilTestFront) << "," << static_cast<uint32_t>(dss->stencilFuncFront) << "," << static_cast<uint32_t>(dss->stencilRefFront) << "," << static_cast<uint32_t>(dss->stencilReadMaskFront);
    res << "," << static_cast<uint32_t>(dss->stencilFailOpFront) << "," << static_cast<uint32_t>(dss->stencilZFailOpFront) << "," << static_cast<uint32_t>(dss->stencilPassOpFront) << "," << static_cast<uint32_t>(dss->stencilWriteMaskFront);
    res << "," << static_cast<uint32_t>(dss->stencilTestBack) << "," << static_cast<uint32_t>(dss->stencilFuncBack) << "," << static_cast<uint32_t>(dss->stencilRefBack) << "," << static_cast<uint32_t>(dss->stencilReadMaskBack);
    res << "," << static_cast<uint32_t>(dss->stencilFailOpBack) << "," << static_cast<uint32_t>(dss->stencilZFailOpBack) << "," << static_cast<uint32_t>(dss->stencilPassOpBack) << "," << dss->stencilWriteMaskBack;
    return res.str();
}

} // namespace

/*static*/
void Pass::fillPipelineInfo(Pass *pass, const PassOverrides &info) {
    if (info.priority.has_value()) {
        pass->_priority = static_cast<pipeline::RenderPriority>(info.priority.value());
    }
    if (info.primitive.has_value()) {
        pass->_primitive = info.primitive.value();
    }
    if (info.stage.has_value()) {
        pass->_stage = info.stage.value();
    }
    if (info.dynamicStates.has_value()) {
        pass->_dynamicStates = info.dynamicStates.value();
    }
    if (info.phase.has_value()) {
        pass->_phase = pipeline::getPhaseID(info.phase.value());
    }

    auto *bs = pass->_blendState;
    if (info.blendState.has_value()) {
        const auto *bsInfo  = info.blendState.value();
        const auto &targets = bsInfo->targets;
        for (size_t i = 0, len = targets.size(); i < len; ++i) {
            bs->setTarget(i, targets[i]);
        }

        //cjh        if (bsInfo.isA2C !== undefined) {
        bs->isA2C = bsInfo->isA2C;
        //        }
        //        if (bsInfo.isIndepend !== undefined) {
        bs->isIndepend = bsInfo->isIndepend;
        //        }
        //        if (bsInfo.blendColor !== undefined) {
        bs->blendColor = bsInfo->blendColor;
        //        }
    }

    pass->_rs                = info.rasterizerState.has_value() ? info.rasterizerState.value() : pass->_rs;
    pass->_depthStencilState = info.depthStencilState.has_value() ? info.depthStencilState.value() : pass->_depthStencilState;
}

/* static */
uint64_t Pass::getPassHash(Pass *pass) {
    const std::string &shaderKey = ProgramLib::getInstance()->getKey(pass->getProgram(), pass->getDefines());
    std::stringstream  res;
    res << shaderKey << "," << static_cast<uint32_t>(pass->_primitive) << "," << static_cast<uint32_t>(pass->_dynamicStates);
    res << serializeBlendState(pass->_blendState);
    res << serializeDepthStencilState(pass->_depthStencilState);
    res << serializeRasterizerState(pass->_rs);

    std::string str{res.str()};
    return murmurhash2::MurmurHash2(str.data(), str.length(), 666);
}

Pass::Pass() {
    _phase             = pipeline::getPhaseID("default");
    _blendState        = new gfx::BlendState(); //cjh how to delete ?
    _depthStencilState = new gfx::DepthStencilState();
    _rs                = new gfx::RasterizerState();
}

Pass::~Pass() {
}

void Pass::initialize(const IPassInfoFull &info) {
    doInit(info);
    resetUBOs();
    resetTextures();
    tryCompile();
}

uint32_t Pass::getHandle(const std::string &name, uint32_t offset /* = 0 */, gfx::Type targetType /* = gfx::Type::UNKNOWN */) const {
    uint32_t handle = 0;
    auto     iter   = _propertyHandleMap.find(name); // handle = _propertyHandleMap[name];
    if (iter == _propertyHandleMap.end()) {
        return 0;
    } else {
        handle = iter->second;
    }

    if (targetType != gfx::Type::UNKNOWN) {
        handle = customizeType(handle, targetType);
    } else if (offset) {
        handle = customizeType(handle, static_cast<gfx::Type>(static_cast<uint32_t>(getTypeFromHandle(handle)) - offset));
    }
    return handle + offset;
}

int32_t Pass::getBinding(const std::string &name) const {
    uint32_t handle = getHandle(name);
    if (0 == handle) {
        return -1;
    }
    return Pass::getBindingFromHandle(handle);
}

void Pass::setUniform(uint32_t handle, const MaterialProperty &value) {
    const uint32_t  binding = Pass::getBindingFromHandle(handle);
    const gfx::Type type    = Pass::getTypeFromHandle(handle);
    const uint32_t  ofs     = Pass::getOffsetFromHandle(handle);
    Float32Array &  block   = _blocks[binding];
    if (auto iter = type2writer.find(type); iter != type2writer.end()) {
        iter->second(block.data(), value, ofs);
    }

    _rootBufferDirty = true;
}

MaterialProperty &Pass::getUniform(uint32_t handle, MaterialProperty &out) const {
    const uint32_t      binding = Pass::getBindingFromHandle(handle);
    const gfx::Type     type    = Pass::getTypeFromHandle(handle);
    const uint32_t      ofs     = Pass::getOffsetFromHandle(handle);
    const Float32Array &block   = _blocks[binding];
    if (auto iter = type2reader.find(type); iter != type2reader.end()) {
        iter->second(block.data(), out, ofs);
    }
    return out;
}

void Pass::setUniformArray(uint32_t handle, const MaterialPropertyList &value) {
    const uint32_t  binding = Pass::getBindingFromHandle(handle);
    const gfx::Type type    = Pass::getTypeFromHandle(handle);
    const uint32_t  stride  = gfx::getTypeSize(type) >> 2;
    Float32Array &  block   = _blocks[binding];
    uint32_t        ofs     = Pass::getOffsetFromHandle(handle);
    for (size_t i = 0; i < value.size(); i++, ofs += stride) {
        if (value[i].index() == 0) {
            continue;
        }
        if (auto iter = type2writer.find(type); iter != type2writer.end()) {
            iter->second(block.data(), value[i], ofs);
        }
    }
    _rootBufferDirty = true;
}

void Pass::bindTexture(uint32_t binding, gfx::Texture *value, index_t index /* = CC_INVALID_INDEX */) {
    _descriptorSet->bindTexture(binding, value, (index != CC_INVALID_INDEX) || 0);
}

void Pass::bindSampler(uint32_t binding, gfx::Sampler *value, index_t index /* = CC_INVALID_INDEX */) {
    _descriptorSet->bindSampler(binding, value, (index != CC_INVALID_INDEX) || 0);
}

void Pass::setDynamicState(gfx::DynamicStateFlagBit state, int32_t value) {
    auto &ds = _dynamics[static_cast<uint32_t>(state)];
    if (ds.value == value) {
        return;
    }

    ds.value = value;
    ds.dirty = true;
}

void Pass::overridePipelineStates(const IPassInfo &original, const PassOverrides &overrides) {
    CC_LOG_WARNING("base pass cannot override states, please use pass instance instead.");
}

void Pass::update() {
    if (_descriptorSet == nullptr) {
        //cjh        errorID(12006);
        return;
    }

    if (_rootBufferDirty && _rootBuffer) {
        _rootBuffer->update(_rootBlock, _rootBuffer->getSize());
        _rootBufferDirty = false;
    }
    _descriptorSet->update();
}

void Pass::destroy() {
    auto &blocks = _shaderInfo->blocks;
    for (size_t i = 0, len = blocks.size(); i < len; ++i) {
        const auto &u = blocks[i];
        _buffers[u.binding]->destroy();
    }

    _buffers.clear();

    if (_rootBuffer) {
        _rootBuffer->destroy();
        _rootBuffer = nullptr;
    }

    _descriptorSet->destroy();
    //cjh    _rs->destroy();
    //    _dss->destroy();
    //    _bs->destroy();
}

void Pass::resetUniform(const std::string &name) {
    const uint32_t handle = getHandle(name);
    if (0 == handle) {
        return;
    }
    const gfx::Type type    = Pass::getTypeFromHandle(handle);
    const uint32_t  binding = Pass::getBindingFromHandle(handle);
    const uint32_t  ofs     = Pass::getOffsetFromHandle(handle);
    Float32Array &  block   = _blocks[binding];

    //cjh todo: https://github.com/cocos-creator/3d-tasks/issues/8907
    //    const auto& info = _properties[name];
    //    const value = (info && info.value) || getDefaultFromType(type);
    //    type2writer[type](block, value, ofs);

    _rootBufferDirty = true;
}

void Pass::resetTexture(const std::string &name, index_t index /* = CC_INVALID_INDEX */) {
    const uint32_t handle = getHandle(name);
    if (0 == handle) {
        return;
    }
    const gfx::Type type    = Pass::getTypeFromHandle(handle);
    const uint32_t  binding = Pass::getBindingFromHandle(handle);
    std::string     texName;
    IPropertyInfo * info = nullptr;
    if (auto iter = _properties.find(name); iter != _properties.end()) {
        if (iter->second.value.has_value()) {
            info                 = &iter->second;
            std::string *pStrVal = std::get_if<std::string>(&iter->second.value.value());
            if (pStrVal != nullptr) {
                texName = (*pStrVal) + "-texture";
            }
        }
    }

    if (texName.empty()) {
        texName = getDefaultStringFromType(type);
    }

    TextureBase *           textureBase = BuiltinResMgr::getInstance()->get<TextureBase>(texName);
    gfx::Texture *          texture     = textureBase != nullptr ? textureBase->getGFXTexture() : nullptr;
    std::optional<uint64_t> samplerHash;
    if (info != nullptr && info->samplerHash.has_value()) {
        samplerHash = info->samplerHash.value();
    } else if (textureBase != nullptr) {
        samplerHash = textureBase->getSamplerHash();
    }

    if (samplerHash.has_value()) {
        auto *sampler = pipeline::SamplerLib::getSampler(samplerHash.value());
        _descriptorSet->bindSampler(binding, sampler, index);
        _descriptorSet->bindTexture(binding, texture, index);
    } else {
        CC_LOG_WARNING("sampler hash could not be found!");
    }
}

void Pass::resetUBOs() {
    for (size_t i = 0; i < _shaderInfo->blocks.size(); i++) {
        const auto &u     = _shaderInfo->blocks[i];
        auto &      block = _blocks[u.binding];
        uint32_t    ofs   = 0;
        for (size_t j = 0; j < u.members.size(); j++) {
            const auto &   cur          = u.members[j];
            const auto &   info         = _properties[cur.name];
            const auto &   givenDefault = info.value;
            const auto &   value        = (givenDefault.has_value() ? std::get<std::vector<float>>(givenDefault.value()) : getDefaultFloatArrayFromType(cur.type));
            const uint32_t size         = (gfx::getTypeSize(cur.type) >> 2) * cur.count;
            for (size_t k = 0; (k + value.size()) <= size; k += value.size()) {
                std::copy(value.begin(), value.begin() + ofs + k, block.begin()); //cjh memory issue?
            }
            ofs += size;
        }
    }
    _rootBufferDirty = true;
}

void Pass::resetTextures() {
    for (size_t i = 0; i < _shaderInfo->samplerTextures.size(); i++) {
        const auto &u = _shaderInfo->samplerTextures[i];
        for (size_t j = 0; j < u.count; j++) {
            resetTexture(u.name, j);
        }
    }
}

bool Pass::tryCompile() {
    //cjh    const { pipeline } = _root;
    //    if (!pipeline) { return false; }
    syncBatchingScheme();
    auto *shader = ProgramLib::getInstance()->getGFXShader(_device, _programName, _defines, _root->getPipeline());
    if (!shader) {
        CC_LOG_WARNING("create shader %s failed", _programName.c_str());
        return false;
    }
    _shader         = shader; //cjh
    _pipelineLayout = ProgramLib::getInstance()->getTemplateInfo(_programName)->pipelineLayout;
    _hash           = Pass::getPassHash(this);
    return true;
}

gfx::Shader *Pass::getShaderVariant(const std::vector<IMacroPatch> &patches) {
    if (!_shader && !tryCompile()) {
        CC_LOG_WARNING("pass resources incomplete");
        return nullptr;
    }

    //cjh    if (EDITOR) {
    //        for (let i = 0; i < patches.length; i++) {
    //            if (!patches[i].name.startsWith('CC_')) {
    //                console.warn('cannot patch non-builtin macros');
    //                return null;
    //            }
    //        }
    //    }

    auto *pipeline = _root->getPipeline();
    for (size_t i = 0; i < patches.size(); ++i) {
        const auto &patch    = patches[i];
        _defines[patch.name] = patch.value;
    }

    auto *shader = ProgramLib::getInstance()->getGFXShader(_device, _programName, _defines, pipeline);

    for (size_t i = 0; i < patches.size(); ++i) {
        const auto &patch = patches[i];
        if (auto iter = _defines.find(patch.name); iter != _defines.end()) {
            _defines.erase(iter);
        }
    }
    return shader;
}

void Pass::setState(gfx::BlendState *bs, gfx::DepthStencilState *dss, gfx::RasterizerState *rs, gfx::DescriptorSet *ds) {
    //cjh how to control lifecycle?
    _blendState        = bs;
    _depthStencilState = dss;
    _rs                = rs;
    _descriptorSet     = ds;
}

void Pass::doInit(const IPassInfoFull &info, bool copyDefines /* = false */) {
    _priority  = pipeline::RenderPriority::DEFAULT;
    _stage     = pipeline::RenderPassStage::DEFAULT;
    _phase     = pipeline::getPhaseID("default");
    _primitive = gfx::PrimitiveMode::TRIANGLE_LIST;

    _passIndex     = info.passIndex;
    _propertyIndex = info.propertyIndex != CC_INVALID_INDEX ? info.propertyIndex : info.passIndex;
    _programName   = info.program;
    _defines       = info.defines; //cjh c++ always does copy by assignment.  copyDefines ? ({ ...info.defines }) : info.defines;
    _shaderInfo    = ProgramLib::getInstance()->getTemplate(info.program);
    if (info.properties.has_value()) {
        _properties = info.properties.value();
    }
    //
    //    const device = _device;
    Pass::fillPipelineInfo(this, info);
    if (info.stateOverrides.has_value()) {
        Pass::fillPipelineInfo(this, info.stateOverrides.value());
    }

    // init descriptor set
    _dsInfo.layout = ProgramLib::getInstance()->getDescriptorSetLayout(_device, info.program);
    _descriptorSet = _device->createDescriptorSet(_dsInfo);

    // calculate total size required
    //    const blocks = _shaderInfo.blocks;
    //    const tmplInfo = programLib.getTemplateInfo(info.program);
    //    const { blockSizes, handleMap } = tmplInfo;
    //    const alignment = device.capabilities.uboOffsetAlignment;
    //    const startOffsets: number[] = [];
    //    let lastSize = 0; let lastOffset = 0;
    //    for (let i = 0; i < blocks.length; i++) {
    //        const size = blockSizes[i];
    //        startOffsets.push(lastOffset);
    //        lastOffset += Math.ceil(size / alignment) * alignment;
    //        lastSize = size;
    //    }
    //    // create gfx buffer resource
    //    const totalSize = startOffsets[startOffsets.length - 1] + lastSize;
    //    if (totalSize) {
    //        // https://bugs.chromium.org/p/chromium/issues/detail?id=988988
    //        _bufferInfo.size = Math.ceil(totalSize / 16) * 16;
    //        _rootBuffer = device.createBuffer(_bufferInfo);
    //        _rootBlock = new ArrayBuffer(totalSize);
    //    }
    //    // create buffer views
    //    for (let i = 0, count = 0; i < blocks.length; i++) {
    //        const { binding } = blocks[i];
    //        const size = blockSizes[i];
    //        _bufferViewInfo.buffer = _rootBuffer!;
    //        _bufferViewInfo.offset = startOffsets[count++];
    //        _bufferViewInfo.range = Math.ceil(size / 16) * 16;
    //        const bufferView = _buffers[binding] = device.createBuffer(_bufferViewInfo);
    //        // non-builtin UBO data pools, note that the effect compiler
    //        // guarantees these bindings to be consecutive, starting from 0 and non-array-typed
    //        _blocks[binding] = new Float32Array(_rootBlock!, _bufferViewInfo.offset,
    //            size / Float32Array.BYTES_PER_ELEMENT);
    //        _descriptorSet.bindBuffer(binding, bufferView);
    //    }
    //    // store handles
    //    const directHandleMap = _propertyHandleMap = handleMap;
    //    const indirectHandleMap: Record<string, number> = {};
    //    for (const name in _properties) {
    //        const prop = _properties[name];
    //        if (!prop.handleInfo) { continue; }
    //        indirectHandleMap[name] = getHandle.apply(this, prop.handleInfo)!;
    //    }
    //    Object.assign(directHandleMap, indirectHandleMap);
}

void Pass::syncBatchingScheme() {
    if (auto iter = _defines.find("USE_INSTANCING"); iter != _defines.end()) {
        if (_device->hasFeature(gfx::Feature::INSTANCED_ARRAYS)) {
            _batchingScheme = BatchingSchemes::INSTANCING;
        } else {
            iter->second    = false;
            _batchingScheme = BatchingSchemes::NONE;
        }
    } else if (auto iter = _defines.find("USE_BATCHING"); iter != _defines.end()) {
        _batchingScheme = BatchingSchemes::VB_MERGING;
    } else {
        _batchingScheme = BatchingSchemes::NONE;
    }
}

void Pass::initPassFromTarget(Pass *target, gfx::DepthStencilState *dss, gfx::BlendState *bs, uint64_t hashFactor) {
    _priority          = target->_priority;
    _stage             = target->_stage;
    _phase             = target->_phase;
    _batchingScheme    = target->_batchingScheme;
    _primitive         = target->_primitive;
    _dynamicStates     = target->_dynamicStates;
    _blendState        = bs; //cjh lifecycle?
    _depthStencilState = dss;
    _descriptorSet     = target->_descriptorSet;
    _rs                = target->getRasterizerState();
    _passIndex         = target->_passIndex;
    _propertyIndex     = target->_propertyIndex;
    _programName       = target->getProgram();
    _defines           = target->_defines;
    //cjh    _shaderInfo = target->_shaderInfo;
    _properties = target->_properties;

    _blocks   = target->_blocks;
    _dynamics = target->_dynamics;

    _shader = target->_shader;

    _pipelineLayout = ProgramLib::getInstance()->getTemplateInfo(_programName)->pipelineLayout;
    _hash           = target->_hash ^ hashFactor;
}

} // namespace scene
} // namespace cc
