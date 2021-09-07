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

#include "core/assets/RenderingSubMesh.h"
#include "3d/assets/Mesh.h"

namespace cc {

RenderingSubMesh::RenderingSubMesh(const gfx::BufferList &   vertexBuffers,
                                   const gfx::AttributeList &attributes,
                                   gfx::PrimitiveMode        primitiveMode,
                                   gfx::Buffer *             indexBuffer /* = nullptr*/,
                                   gfx::Buffer *             indirectBuffer /* = nullptr*/)
: _vertexBuffers(vertexBuffers), _attributes(attributes), _primitiveMode(primitiveMode), _indexBuffer(indexBuffer), _indirectBuffer(indirectBuffer) {
    _iaInfo.attributes     = attributes;
    _iaInfo.vertexBuffers  = vertexBuffers; //cjh how to release?
    _iaInfo.indexBuffer    = indexBuffer;
    _iaInfo.indirectBuffer = indirectBuffer;
    init();
}

RenderingSubMesh::~RenderingSubMesh() = default;

const IGeometricInfo &RenderingSubMesh::geometricInfo() {
    if (_geometricInfo.has_value()) {
        return _geometricInfo.value();
    }

    static const IGeometricInfo EMPTY_GEOMETRIC_INFO;
    if (_mesh == nullptr) {
        return EMPTY_GEOMETRIC_INFO;
    }

    if (!_subMeshIdx.has_value()) {
        return EMPTY_GEOMETRIC_INFO;
    }

    auto index = static_cast<index_t>(_subMeshIdx.value());

    const auto &positionsVar = _mesh->readAttribute(index, gfx::ATTR_NAME_POSITION);
    if (const auto *pPositions = std::get_if<Float32Array>(&positionsVar); pPositions != nullptr) {
        const auto &positions  = *pPositions;
        const auto &indicesVar = _mesh->readIndices(index);
        if (const auto *pIndices = std::get_if<Uint16Array>(&indicesVar); pIndices != nullptr) {
            const auto &indices = *pIndices;

            Vec3 max;
            Vec3 min;

            if (auto iter = std::find_if(_attributes.cbegin(), _attributes.cend(), [](const gfx::Attribute &element) -> bool {
                    return element.name == gfx::ATTR_NAME_POSITION;
                });
                iter != _attributes.cend()) {
                const auto &   attri = *iter;
                const uint32_t count = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attri.format)].count;
                if (count == 2) {
                    max.set(positions[0], positions[1], 0);
                    min.set(positions[0], positions[1], 0);
                } else {
                    max.set(positions[0], positions[1], positions[2]);
                    min.set(positions[0], positions[1], positions[2]);
                }

                for (size_t i = 0; i < positions.size(); i += count) {
                    if (count == 2) {
                        max.x = positions[i] > max.x ? positions[i] : max.x;
                        max.y = positions[i + 1] > max.y ? positions[i + 1] : max.y;
                        min.x = positions[i] < min.x ? positions[i] : min.x;
                        min.y = positions[i + 1] < min.y ? positions[i + 1] : min.y;
                    } else {
                        max.x = positions[i] > max.x ? positions[i] : max.x;
                        max.y = positions[i + 1] > max.y ? positions[i + 1] : max.y;
                        max.z = positions[i + 2] > max.z ? positions[i + 2] : max.z;
                        min.x = positions[i] < min.x ? positions[i] : min.x;
                        min.y = positions[i + 1] < min.y ? positions[i + 1] : min.y;
                        min.z = positions[i + 2] < min.z ? positions[i + 2] : min.z;
                    }
                }
            }

            IGeometricInfo info;
            info.positions       = positions;
            info.indices         = indices;
            info.boundingBox.max = max;
            info.boundingBox.min = min;

            _geometricInfo = info;
            return _geometricInfo.value();
        }
    }

    return EMPTY_GEOMETRIC_INFO;
}

void RenderingSubMesh::genFlatBuffers() {
    if (!_flatBuffers.empty() || _mesh != nullptr || !_subMeshIdx.has_value()) {
        return;
    }

    uint32_t    idxCount = 0;
    const auto &prim     = _mesh->getStruct().primitives[_subMeshIdx.value()];
    if (prim.indexView.has_value()) {
        idxCount = prim.indexView.value().count;
    }
    for (size_t i = 0; i < prim.vertexBundelIndices.size(); i++) {
        const uint32_t             bundleIdx    = prim.vertexBundelIndices[i];
        const Mesh::IVertexBundle &vertexBundle = _mesh->getStruct().vertexBundles[bundleIdx];
        const uint32_t             vbCount      = prim.indexView.has_value() ? prim.indexView.value().count : vertexBundle.view.count;
        const uint32_t             vbStride     = vertexBundle.view.stride;
        const uint32_t             vbSize       = vbStride * vbCount;
        //cjh  no need to deal with length?      Uint8Array view{_mesh->getData(), vertexBundle.view.offset, vertexBundle.view.length};
        const uint8_t *view = _mesh->getData().data() + vertexBundle.view.offset;
        Uint8Array     sharedView;
        sharedView.resize(prim.indexView.has_value() ? vbSize : vertexBundle.view.length);
        //
        if (!prim.indexView.has_value()) {
            std::copy(_mesh->getData().begin() + vertexBundle.view.offset, _mesh->getData().begin() + vertexBundle.view.offset + vertexBundle.view.length, sharedView.begin());
            _flatBuffers.emplace_back(IFlatBuffer{vbStride, vbCount, sharedView});
            continue;
        }

        TypedArray ibView = _mesh->readIndices(_subMeshIdx.value());
        // transform to flat buffer
        for (uint32_t n = 0; n < idxCount; ++n) {
            int32_t  idx       = typedarray::castToInt32(typedarray::get(ibView, n));
            uint32_t offset    = n * vbStride;
            uint32_t srcOffset = idx * vbStride;
            for (uint32_t m = 0; m < vbStride; ++m) {
                sharedView[offset + m] = view[srcOffset + m];
            }
        }
        _flatBuffers.emplace_back(IFlatBuffer{vbStride, vbCount, std::move(sharedView)});
    }
}

void RenderingSubMesh::enableVertexIdChannel(gfx::Device *device) {
    //TODO:minggo
}

void RenderingSubMesh::init() {
    //TODO:minggo
}

bool RenderingSubMesh::destroy() {
    //TODO:minggo
}

} // namespace cc
