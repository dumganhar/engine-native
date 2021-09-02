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

#include "3d/assets/Mesh.h"
#include "3d/assets/Morph.h"
#include "3d/assets/Skeleton.h"

#include "renderer/gfx-base/GFXDevice.h"

namespace cc {

namespace {

uint32_t getOffset(const gfx::AttributeList &attributes, index_t attributeIndex) {
    uint32_t result = 0;
    for (index_t i = 0; i < attributeIndex; ++i) {
        const auto &attribute = attributes[i];
        result += gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attribute.format)].size;
    }
    return result;
}
//
//const { isLittleEndian } = sys;
//
uint32_t getComponentByteLength(gfx::Format format) {
    const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    return info.size / info.count;
}

using DataReaderCallback = std::function<float(uint32_t)>;

DataReaderCallback getReader(const DataView &dataView, gfx::Format format, Mesh::AttributeType *outType) {
    if (outType == nullptr)
        return nullptr;
    const auto &   info   = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    const uint32_t stride = info.size / info.count;

    switch (info.type) {
        case gfx::FormatType::UNORM: {
            switch (stride) {
                case 1: *outType = Mesh::AttributeType::UINT8; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getUint8(offset)); };
                case 2: *outType = Mesh::AttributeType::UINT16; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getUint16(offset)); };
                case 4: *outType = Mesh::AttributeType::UINT32; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getUint32(offset)); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::SNORM: {
            switch (stride) {
                case 1: *outType = Mesh::AttributeType::INT8; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getInt8(offset)); };
                case 2: *outType = Mesh::AttributeType::INT16; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getInt16(offset)); };
                case 4: *outType = Mesh::AttributeType::INT32; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getInt32(offset)); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::INT: {
            switch (stride) {
                case 1: *outType = Mesh::AttributeType::INT8; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getInt8(offset)); };
                case 2: *outType = Mesh::AttributeType::INT16; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getInt16(offset)); };
                case 4: *outType = Mesh::AttributeType::INT32; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getInt32(offset)); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::UINT: {
            switch (stride) {
                case 1: *outType = Mesh::AttributeType::UINT8; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getUint8(offset)); };
                case 2: *outType = Mesh::AttributeType::UINT16; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getUint16(offset)); };
                case 4: *outType = Mesh::AttributeType::UINT32; return [&](uint32_t offset) -> float { return static_cast<float>(dataView.getUint32(offset)); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::FLOAT: {
            *outType = Mesh::AttributeType::FLOAT;
            return [&](uint32_t offset) -> float { return dataView.getFloat32(offset); };
        }
        default:
            break;
    }

    return nullptr;
}

using DataWritterCallback = std::function<void(uint32_t, float)>;

DataWritterCallback getWriter(DataView &dataView, gfx::Format format, Mesh::AttributeType *outType) {
    if (outType == nullptr)
        return nullptr;
    const auto &   info   = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    const uint32_t stride = info.size / info.count;

    switch (info.type) {
        case gfx::FormatType::UNORM: {
            switch (stride) {
                case 1: *outType = Mesh::AttributeType::UINT8; return [&](uint32_t offset, float value) { dataView.setUint8(offset, value); };
                case 2: *outType = Mesh::AttributeType::UINT16; return [&](uint32_t offset, float value) { dataView.setUint16(offset, value); };
                case 4: *outType = Mesh::AttributeType::UINT32; return [&](uint32_t offset, float value) { dataView.setUint32(offset, value); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::SNORM: {
            switch (stride) {
                case 1: *outType = Mesh::AttributeType::INT8; return [&](uint32_t offset, float value) { dataView.setInt8(offset, value); };
                case 2: *outType = Mesh::AttributeType::INT16; return [&](uint32_t offset, float value) { dataView.setInt16(offset, value); };
                case 4: *outType = Mesh::AttributeType::INT32; return [&](uint32_t offset, float value) { dataView.setInt32(offset, value); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::INT: {
            switch (stride) {
                case 1: *outType = Mesh::AttributeType::INT8; return [&](uint32_t offset, float value) { dataView.setInt8(offset, value); };
                case 2: *outType = Mesh::AttributeType::INT16; return [&](uint32_t offset, float value) { dataView.setInt16(offset, value); };
                case 4: *outType = Mesh::AttributeType::INT32; return [&](uint32_t offset, float value) { dataView.setInt32(offset, value); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::UINT: {
            switch (stride) {
                case 1: *outType = Mesh::AttributeType::UINT8; return [&](uint32_t offset, float value) { dataView.setUint8(offset, value); };
                case 2: *outType = Mesh::AttributeType::UINT16; return [&](uint32_t offset, float value) { dataView.setUint16(offset, value); };
                case 4: *outType = Mesh::AttributeType::UINT32; return [&](uint32_t offset, float value) { dataView.setUint32(offset, value); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::FLOAT: {
            *outType = Mesh::AttributeType::FLOAT;
            return [&](uint32_t offset, float value) { dataView.setFloat32(offset, value); };
        }
        default:
            break;
    }

    return nullptr;
}

template <typename T>
T getValueFromArrayBuffer(const ArrayBuffer &buffer, Mesh::AttributeType type, index_t offset) {
    T ret{};
    switch (type) {
        case Mesh::AttributeType::UINT8:
            ret = static_cast<T>(buffer[offset]);
            break;
        case Mesh::AttributeType::UINT16:
            ret = static_cast<T>(*(reinterpret_cast<const uint16_t *>(buffer.data()) + offset));
            break;
        case Mesh::AttributeType::UINT32:
            ret = static_cast<T>(*(reinterpret_cast<const uint32_t *>(buffer.data()) + offset));
            break;
        case Mesh::AttributeType::INT8:
            ret = static_cast<T>(buffer[offset]);
            break;
        case Mesh::AttributeType::INT16:
            ret = static_cast<T>(*(reinterpret_cast<const int16_t *>(buffer.data()) + offset));
            break;
        case Mesh::AttributeType::INT32:
            ret = static_cast<T>(*(reinterpret_cast<const int32_t *>(buffer.data()) + offset));
            break;
        case Mesh::AttributeType::FLOAT:
            ret = static_cast<T>(*(reinterpret_cast<const float *>(buffer.data()) + offset));
            break;
        default:
            break;
    }
    return ret;
}

uint32_t getAttributeSizeByType(Mesh::AttributeType type) {
    uint32_t ret = 0;
    switch (type) {
        case Mesh::AttributeType::UINT8:
        case Mesh::AttributeType::INT8:
            ret = 1;
            break;
        case Mesh::AttributeType::UINT16:
        case Mesh::AttributeType::INT16:
            ret = 2;
            break;
        case Mesh::AttributeType::UINT32:
        case Mesh::AttributeType::INT32:
        case Mesh::AttributeType::FLOAT:
            ret = 4;
            break;
        default:
            break;
    }
    return ret;
}

} // namespace

std::any Mesh::getNativeAsset() const {
    return nullptr;
}

void Mesh::setNativeAsset(const std::any &obj) {
}

uint32_t Mesh::getSubMeshCount() const {
    return 0;
}

const Vec3 &Mesh::getMinPosition() const {
    static Vec3 v;
    return v;
}

const Vec3 &Mesh::getMaxPosition() const {
    static Vec3 v;
    return v;
}

uint64_t Mesh::getHash() const {
    return 0;
}

const Mesh::JointBufferIndicesType &Mesh::getJointBufferIndices() {
    static JointBufferIndicesType ret;
    return ret;
}

void Mesh::initialize() {
    if (_initialized) {
        return;
    }

    _initialized                                  = true;
    auto &                          buffer        = _data;
    gfx::Device *                   gfxDevice     = gfx::Device::getInstance();
    auto                            vertexBuffers = createVertexBuffers(gfxDevice, buffer);
    gfx::BufferList                 indexBuffers;
    std::vector<RenderingSubMesh *> subMeshes;

    for (size_t i = 0; i < _struct.primitives.size(); i++) {
        auto &prim = _struct.primitives[i];
        if (prim.vertexBundelIndices.empty()) {
            continue;
        }

        gfx::Buffer *indexBuffer = nullptr;
        void *       ib          = nullptr;
        if (prim.indexView.has_value()) {
            const auto &idxView = prim.indexView.value();

            uint32_t dstStride = idxView.stride;
            uint32_t dstSize   = idxView.length;
            if (dstStride == 4 && !gfxDevice->hasFeature(gfx::Feature::ELEMENT_INDEX_UINT)) {
                uint32_t vertexCount = _struct.vertexBundles[prim.vertexBundelIndices[0]].view.count;
                if (vertexCount >= 65536) {
                    //cjh                    warnID(10001, vertexCount, 65536);
                    continue; // Ignore this primitive
                } else {
                    dstStride >>= 1; // Reduce to short.
                    dstSize >>= 1;
                }
            }

            indexBuffer = gfxDevice->createBuffer(gfx::BufferInfo{
                gfx::BufferUsageBit::INDEX,
                gfx::MemoryUsageBit::DEVICE,
                dstSize,
                dstStride,
            });
            indexBuffers.emplace_back(indexBuffer);

            ib = buffer.data() + idxView.offset;

            //            ib = new (getIndexStrideCtor(idxView.stride))(buffer, idxView.offset, idxView.count);
            if (idxView.stride != dstStride) {
                //cjh  need in c++?              ib = getIndexStrideCtor(dstStride).from(ib);
            }
            indexBuffer->update(ib);
        }

        gfx::BufferList vbReference;
        vbReference.reserve(prim.vertexBundelIndices.size());
        for (const auto &idx : prim.vertexBundelIndices) {
            vbReference.emplace_back(vertexBuffers[idx]);
        }

        gfx::AttributeList gfxAttributes;
        if (!prim.vertexBundelIndices.empty()) {
            uint32_t                  idx          = prim.vertexBundelIndices[0];
            const IVertexBundle &     vertexBundle = _struct.vertexBundles[idx];
            const gfx::AttributeList &attrs        = vertexBundle.attributes;
            for (size_t j = 0; j < attrs.size(); ++j) {
                const auto &attr = attrs[j];
                gfxAttributes[j] = gfx::Attribute{attr.name, attr.format, attr.isInstanced, attr.stream, attr.isInstanced, attr.location};
            }
        }

        auto *subMesh = new RenderingSubMesh(vbReference, gfxAttributes, prim.primitiveMode, indexBuffer); //cjh how to release?
        subMesh->setMesh(this);
        subMesh->setSubMeshIdx(i);

        subMeshes.emplace_back(subMesh);
    }

    _renderingSubMeshes = subMeshes;

    if (_struct.morph.has_value()) {
        morphRendering = createMorphRendering(this, gfxDevice);
    }
}

void Mesh::destroyRenderingMesh() {
    if (!_renderingSubMeshes.empty()) {
        for (auto &submesh : _renderingSubMeshes) {
            submesh->destroy();
        }
        _renderingSubMeshes.clear();
        _initialized = false;
    }
}

void Mesh::assign(const IStruct &structInfo, const Uint8Array &data) {
    reset({structInfo, data});
}

void Mesh::reset(const ICreateInfo &info) {
    destroyRenderingMesh();
    _struct = info.structInfo;
    _data   = info.data;
    _hash   = 0;
}

Mesh::BoneSpaceBounds Mesh::getBoneSpaceBounds(Skeleton *skeleton) {
    if (auto iter = _boneSpaceBounds.find(skeleton->getHash()); iter != _boneSpaceBounds.end()) {
        return iter->second;
    }

    BoneSpaceBounds bounds;
    _boneSpaceBounds.emplace(skeleton->getHash(), bounds);
    std::vector<bool> valid;
    auto &            bindposes = skeleton->getBindposes();
    valid.reserve(bindposes.size());
    for (size_t i = 0; i < bindposes.size(); i++) {
        bounds.emplace_back(geometry::AABB{
            std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(),
            -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity()});
        valid.emplace_back(false);
    }
    const auto &primitives = _struct.primitives;
    for (index_t p = 0; p < primitives.size(); p++) {
        AttributeType jointAttType;
        AttributeType weightAttType;
        AttributeType positionAttType;
        const auto &  joints    = readAttribute(p, gfx::ATTR_NAME_JOINTS, &jointAttType);
        const auto &  weights   = readAttribute(p, gfx::ATTR_NAME_WEIGHTS, &weightAttType);
        const auto &  positions = readAttribute(p, gfx::ATTR_NAME_POSITION, &positionAttType);
        if (joints.empty() || weights.empty() || positions.empty()) {
            continue;
        }

        uint32_t vertCount = std::min({joints.size() / 4, weights.size() / 4, positions.size() / 3});
        for (uint32_t i = 0; i < vertCount; i++) {
            Vec3 v3_1{
                getValueFromArrayBuffer<float>(positions, positionAttType, 3 * i + 0),
                getValueFromArrayBuffer<float>(positions, positionAttType, 3 * i + 1),
                getValueFromArrayBuffer<float>(positions, positionAttType, 3 * i + 2)};

            for (uint32_t j = 0; j < 4; ++j) {
                const uint32_t idx   = 4 * i + j;
                const int32_t  joint = getValueFromArrayBuffer<int32_t>(joints, jointAttType, idx);
                if (weights[idx] == 0 || joint >= bindposes.size()) {
                    continue;
                }

                Vec3 v3_2;
                Vec3::transformMat4(v3_1, bindposes[joint], &v3_2);
                valid[joint] = true;
                auto &b      = bounds[joint];
                Vec3::min(b.center, v3_2, &b.center);
                Vec3::max(b.halfExtents, v3_2, &b.halfExtents);
            }
        }
    }
    for (size_t i = 0; i < bindposes.size(); i++) {
        auto &b = bounds[i];
        if (!valid[i]) {
            bounds[i] = {};
        } else {
            geometry::AABB::fromPoints(b.center, b.halfExtents, &b);
        }
    }
    return bounds;
}

bool Mesh::merge(Mesh *mesh, const Mat4 &worldMatrix, bool validate /* = false*/) {
    return false;
}

bool Mesh::validateMergingMesh(Mesh *mesh) {
    return false;
}

ArrayBuffer Mesh::readAttribute(index_t primitiveIndex, const char *attributeName, AttributeType *outType) {
    ArrayBuffer result;
    accessAttribute(primitiveIndex, attributeName, [&](const IVertexBundle &vertexBundle, uint32_t iAttribute) {
        const uint32_t    vertexCount = vertexBundle.view.count;
        const gfx::Format format      = vertexBundle.attributes[iAttribute].format;
        //cjh        const StorageConstructor = getTypedArrayConstructor(FormatInfos[format]);
        if (vertexCount == 0) {
            return;
        }

        DataView inputView(_data, vertexBundle.view.offset + getOffset(vertexBundle.attributes, iAttribute));

        const auto &formatInfo = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
        auto        reader     = getReader(inputView, format, outType);
        if (/*cjh todo !StorageConstructor || */ reader == nullptr) {
            return;
        }

        const uint32_t componentCount = formatInfo.count;
        result.resize(vertexCount * componentCount * getAttributeSizeByType(*outType));
        //cjh         storage = new StorageConstructor(vertexCount * componentCount);
        const uint32_t inputStride = vertexBundle.view.stride;
        for (uint32_t iVertex = 0; iVertex < vertexCount; ++iVertex) {
            for (uint32_t iComponent = 0; iComponent < componentCount; ++iComponent) {
                //cjh TODO: how?                storage[componentCount * iVertex + iComponent] = reader(inputStride * iVertex + storage.BYTES_PER_ELEMENT * iComponent);
            }
        }
        //cjh        result = storage;
    });
    return result;
}

bool Mesh::copyAttribute(index_t primitiveIndex, const char *attributeName, ArrayBuffer &buffer, uint32_t stride, uint32_t offset) {
    return false;
}

ArrayBuffer Mesh::readIndices(index_t primitiveIndex) {
    return ArrayBuffer{};
}

bool Mesh::copyIndices(index_t primitiveIndex, ArrayBuffer &outputArray) {
    return false;
}

void Mesh::accessAttribute(index_t primitiveIndex, const char *attributeName, const AccessorType &accessor) {
    if (primitiveIndex >= _struct.primitives.size()) {
        return;
    }

    auto &primitive = _struct.primitives[primitiveIndex];
    for (const auto &vertexBundleIndex : primitive.vertexBundelIndices) {
        const auto &vertexBundle = _struct.vertexBundles[vertexBundleIndex];
        auto        iter         = std::find_if(vertexBundle.attributes.begin(), vertexBundle.attributes.end(), [&](const auto &a) -> bool { return a.name == attributeName; });
        if (iter == vertexBundle.attributes.end()) {
            continue;
            ;
        }
        accessor(vertexBundle, iter - vertexBundle.attributes.begin());
        break;
    }
}

gfx::BufferList Mesh::createVertexBuffers(gfx::Device *gfxDevice, const ArrayBuffer &data) {
    return gfx::BufferList{};
}

void Mesh::initDefault(const std::optional<std::string> &uuid /* = {}*/) {
}

bool Mesh::validate() const {
    return false;
}

} // namespace cc
