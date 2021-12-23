/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#include "PipelineSceneData.h"
#include "core/ArrayBuffer.h"
#include "gfx-base/GFXDef-common.h"
#include "gfx-base/GFXDevice.h"
#include "gfx-base/GFXFramebuffer.h"

namespace cc {
namespace pipeline {

PipelineSceneData::PipelineSceneData() {
    _fog     = new scene::Fog(); //cjh how to delete?
    _ambient = new scene::Ambient();
    _skybox  = new scene::Skybox();
    _shadow  = new scene::Shadows();
}

PipelineSceneData::~PipelineSceneData() {
    CC_SAFE_DELETE(_fog); //cjh correct ?
    CC_SAFE_DELETE(_ambient);
    CC_SAFE_DELETE(_skybox);
    CC_SAFE_DELETE(_shadow);
}

void PipelineSceneData::activate(gfx::Device *device, RenderPipeline *pipeline) {
    _device   = device;
    _pipeline = pipeline;
    _sphere   = CC_NEW(geometry::Sphere);
    _initOcclusionQuery();
}

void PipelineSceneData::destroy() {
    CC_SAFE_DELETE(_sphere);
    for (auto &pair : _shadowFrameBufferMap) {
        pair.second->destroy();
        delete pair.second;
    }

    _shadowFrameBufferMap.clear();

    CC_SAFE_DESTROY_NULL(_occlusionQueryInputAssembler);
    CC_SAFE_DESTROY_NULL(_occlusionQueryVertexBuffer);
    CC_SAFE_DESTROY_NULL(_occlusionQueryIndicesBuffer);
}

void PipelineSceneData::_initOcclusionQuery() {
    if (!_occlusionQueryInputAssembler) {
        _occlusionQueryInputAssembler = _createOcclusionQueryIA();
    }

    if (!_occlusionQueryMaterial) {
        Material *mat = new Material();
        mat->initDefault("default-occlusion-query-material");
        IMaterialInfo info;
        info.effectName = "occlusion-query";
        mat->initialize(info);
        _occlusionQueryMaterial = mat;
        const auto &passes      = mat->getPasses();
        _occlusionQueryShader   = passes[0].get()->getShaderVariant();
    }
}

scene::Pass *PipelineSceneData::getOcclusionQueryPass() {
    if (_occlusionQueryMaterial) {
        const auto &passes = _occlusionQueryMaterial->getPasses();
        return passes[0].get();
    }

    return nullptr;
}

gfx::InputAssembler *PipelineSceneData::_createOcclusionQueryIA() {
    // create vertex buffer
    const int8_t vertexData[] = {-1, -1, -1, 1, -1, -1, -1, 1, -1, 1, 1, -1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1};
    auto *       arrayBuffer  = new cc::ArrayBuffer((const uint8_t *)vertexData, sizeof(vertexData));
    auto *       vertices     = new Float32Array(arrayBuffer);
    auto         vbStride     = Float32Array::BYTES_PER_ELEMENT * 3;
    auto         vbSize       = vbStride * 8;

    _occlusionQueryVertexBuffer = _device->createBuffer(gfx::BufferInfo{
        gfx::BufferUsageBit::VERTEX | gfx::BufferUsageBit::TRANSFER_DST,
        gfx::MemoryUsageBit::DEVICE, vbSize, vbStride});
    _occlusionQueryVertexBuffer->update(vertices);

    // create index buffer
    uint8_t indicesData[]        = {0, 2, 1, 1, 2, 3, 4, 5, 6, 5, 7, 6, 1, 3, 7, 1, 7, 5, 0, 4, 6, 0, 6, 2, 0, 1, 5, 0, 5, 4, 2, 6, 7, 2, 7, 3};
    auto *  indicesBuffer        = new cc::ArrayBuffer((const uint8_t *)indicesData, sizeof(indicesData));
    auto    indices              = new Uint16Array(indicesBuffer);
    auto    ibStride             = Uint16Array::BYTES_PER_ELEMENT;
    auto    ibSize               = ibStride * 36;
    _occlusionQueryIndicesBuffer = _device->createBuffer(gfx::BufferInfo{
        gfx::BufferUsageBit::INDEX | gfx::BufferUsageBit::TRANSFER_DST,
        gfx::MemoryUsageBit::DEVICE, ibSize, ibStride});
    _occlusionQueryIndicesBuffer->update(indices);

    gfx::AttributeList attributes;
    attributes.emplace_back(gfx::Attribute{gfx::ATTR_NAME_POSITION, gfx::Format::RGBA32F});

    // create cube input assembler
    gfx::BufferList buffers;
    buffers.push_back(_occlusionQueryVertexBuffer);
    gfx::InputAssemblerInfo info{attributes, buffers, _occlusionQueryIndicesBuffer};
    auto                    inputAssembler = _device->createInputAssembler(info);

    return inputAssembler;
}

} // namespace pipeline
} // namespace cc
