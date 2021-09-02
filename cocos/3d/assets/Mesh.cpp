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
#include "3d/misc/BufferBlob.h"
#include "math/Quaternion.h"

#include "MurmurHash2/MurmurHash2.h"
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
uint32_t getComponentByteLength(gfx::Format format) {
    const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    return info.size / info.count;
}

using DataReaderCallback = std::function<TypedArrayElementType(uint32_t)>;

DataReaderCallback getReader(const DataView &dataView, gfx::Format format) {
    const auto &   info   = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    const uint32_t stride = info.size / info.count;

    switch (info.type) {
        case gfx::FormatType::UNORM: {
            switch (stride) {
                case 1: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getUint8(offset); };
                case 2: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getUint16(offset); };
                case 4: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getUint32(offset); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::SNORM: {
            switch (stride) {
                case 1: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getInt8(offset); };
                case 2: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getInt16(offset); };
                case 4: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getInt32(offset); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::INT: {
            switch (stride) {
                case 1: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getInt8(offset); };
                case 2: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getInt16(offset); };
                case 4: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getInt32(offset); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::UINT: {
            switch (stride) {
                case 1: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getUint8(offset); };
                case 2: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getUint16(offset); };
                case 4: return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getUint32(offset); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::FLOAT: {
            return [&](uint32_t offset) -> TypedArrayElementType { return dataView.getFloat32(offset); };
        }
        default:
            break;
    }

    return nullptr;
}

using DataWritterCallback = std::function<void(uint32_t, TypedArrayElementType)>;

DataWritterCallback getWriter(DataView &dataView, gfx::Format format) {
    const auto &   info   = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    const uint32_t stride = info.size / info.count;

    switch (info.type) {
        case gfx::FormatType::UNORM: {
            switch (stride) {
                case 1: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setUint8(offset, std::get<uint8_t>(value)); };
                case 2: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setUint16(offset, std::get<uint16_t>(value)); };
                case 4: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setUint32(offset, std::get<uint32_t>(value)); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::SNORM: {
            switch (stride) {
                case 1: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setInt8(offset, std::get<int8_t>(value)); };
                case 2: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setInt16(offset, std::get<int8_t>(value)); };
                case 4: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setInt32(offset, std::get<int8_t>(value)); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::INT: {
            switch (stride) {
                case 1: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setInt8(offset, std::get<int8_t>(value)); };
                case 2: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setInt16(offset, std::get<int16_t>(value)); };
                case 4: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setInt32(offset, std::get<int32_t>(value)); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::UINT: {
            switch (stride) {
                case 1: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setUint8(offset, std::get<uint8_t>(value)); };
                case 2: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setUint16(offset, std::get<uint16_t>(value)); };
                case 4: return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setUint32(offset, std::get<uint32_t>(value)); };
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::FLOAT: {
            return [&](uint32_t offset, const TypedArrayElementType &value) { dataView.setFloat32(offset, std::get<float>(value)); };
        }
        default:
            break;
    }

    return nullptr;
}

} // namespace

std::any Mesh::getNativeAsset() const {
    //cjh TODO: return nullptr;
}

void Mesh::setNativeAsset(const std::any &obj) {
}

uint32_t Mesh::getSubMeshCount() const {
    return _renderingSubMeshes.size();
}

const Vec3 &Mesh::getMinPosition() const {
    return _struct.minPosition.has_value() ? _struct.minPosition.value() : Vec3::ZERO;
}

const Vec3 &Mesh::getMaxPosition() const {
    return _struct.maxPosition.has_value() ? _struct.maxPosition.value() : Vec3::ZERO;
}

uint64_t Mesh::getHash() {
    if (_hash == 0) {
        _hash = murmurhash2::MurmurHash2(_data.data(), _data.size(), 666);
    }

    return _hash;
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
        const auto joints    = readAttribute(p, gfx::ATTR_NAME_JOINTS);
        const auto weights   = readAttribute(p, gfx::ATTR_NAME_WEIGHTS);
        const auto positions = readAttribute(p, gfx::ATTR_NAME_POSITION);
        if (joints.index() == 0 || weights.index() == 0 || positions.index() == 0) {
            continue;
        }

        uint32_t vertCount = std::min({typedarray::getSize(joints) / 4, typedarray::getSize(weights) / 4, typedarray::getSize(positions) / 3});
        for (uint32_t i = 0; i < vertCount; i++) {
            Vec3 v3_1{
                typedarray::castToFloat(typedarray::get(positions, 3 * i + 0)),
                typedarray::castToFloat(typedarray::get(positions, 3 * i + 1)),
                typedarray::castToFloat(typedarray::get(positions, 3 * i + 2))};

            for (uint32_t j = 0; j < 4; ++j) {
                const uint32_t idx   = 4 * i + j;
                const int32_t  joint = typedarray::castToInt32(typedarray::get(joints, idx));
                if (typedarray::castToInt32(typedarray::get(weights, idx)) == 0 || joint >= bindposes.size()) {
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

bool Mesh::merge(Mesh *mesh, const Mat4 *worldMatrix /* = nullptr */, bool validate /* = false*/) {
    if (validate) {
        if (!validateMergingMesh(mesh)) {
            return false;
        }
    }

    Vec3           vec3_temp;
    Quaternion     rotate;
    geometry::AABB boundingBox;
    if (worldMatrix != nullptr) {
        worldMatrix->getRotation(&rotate);
    }
    if (!_initialized) {
        auto structInfo = mesh->_struct; //NOTE: Need copy struct, so don't use referece
        auto data       = mesh->_data;   //NOTE: Need copy struct, so don't use referece
        if (worldMatrix != nullptr) {
            if (_struct.maxPosition.has_value() && _struct.minPosition.has_value()) {
                Vec3::add(_struct.maxPosition.value(), _struct.minPosition.value(), &boundingBox.center);
                boundingBox.center.scale(0.5F);
                Vec3::subtract(_struct.maxPosition.value(), _struct.minPosition.value(), &boundingBox.halfExtents);
                boundingBox.halfExtents.scale(0.5F);

                boundingBox.transform(*worldMatrix, &boundingBox);
                Vec3::add(boundingBox.center, boundingBox.halfExtents, &_struct.maxPosition.value());
                Vec3::subtract(boundingBox.center, boundingBox.halfExtents, &_struct.minPosition.value());
            }
            for (size_t i = 0; i < _struct.vertexBundles.size(); i++) {
                const auto &vtxBdl = _struct.vertexBundles[i];
                for (size_t j = 0; j < vtxBdl.attributes.size(); j++) {
                    if (vtxBdl.attributes[j].name == gfx::ATTR_NAME_POSITION || vtxBdl.attributes[j].name == gfx::ATTR_NAME_NORMAL) {
                        const gfx::Format format = vtxBdl.attributes[j].format;

                        DataView inputView(data, vtxBdl.view.offset + getOffset(vtxBdl.attributes, j));

                        auto reader = getReader(inputView, format);
                        if (reader == nullptr) {
                            continue;
                        }

                        auto writer = getWriter(inputView, format);
                        if (writer == nullptr) {
                            continue;
                        }

                        const uint32_t vertexCount = vtxBdl.view.count;

                        const uint32_t vertexStride            = vtxBdl.view.stride;
                        const uint32_t attrComponentByteLength = getComponentByteLength(format);
                        for (uint32_t vtxIdx = 0; vtxIdx < vertexCount; vtxIdx++) {
                            const uint32_t xOffset = vtxIdx * vertexStride;
                            const uint32_t yOffset = xOffset + attrComponentByteLength;
                            const uint32_t zOffset = yOffset + attrComponentByteLength;
                            vec3_temp.set(
                                typedarray::castToFloat(reader(xOffset)),
                                typedarray::castToFloat(reader(yOffset)),
                                typedarray::castToFloat(reader(zOffset)));
                            const auto &attrName = vtxBdl.attributes[j].name;

                            if (attrName == gfx::ATTR_NAME_POSITION) {
                                vec3_temp.transformMat4(vec3_temp, *worldMatrix);
                            } else if (attrName == gfx::ATTR_NAME_NORMAL) {
                                vec3_temp.transformQuat(rotate);
                            }

                            writer(xOffset, vec3_temp.x);
                            writer(yOffset, vec3_temp.y);
                            writer(zOffset, vec3_temp.z);
                        }
                    }
                }
            }
        }
        reset({structInfo, data});
        initialize();
        return true;
    }

    // merge buffer
    BufferBlob bufferBlob;

    // merge vertex buffer
    uint32_t vertCount  = 0;
    uint32_t vertStride = 0;
    uint32_t srcOffset  = 0;
    uint32_t dstOffset  = 0;

    uint32_t srcAttrOffset = 0;
    uint32_t srcVBOffset   = 0;
    uint32_t dstVBOffset   = 0;
    uint32_t attrSize      = 0;

    bool hasAttr = false;

    std::vector<Mesh::IVertexBundle> vertexBundles;
    vertexBundles.resize(_struct.vertexBundles.size());

    for (size_t i = 0; i < _struct.vertexBundles.size(); ++i) {
        Uint8Array vbView;
        Uint8Array srcVBView;
        Uint8Array dstVBView;
        Uint8Array dstAttrView;

        const auto &bundle    = _struct.vertexBundles[i];
        auto &      dstBundle = mesh->_struct.vertexBundles[i];

        srcOffset  = bundle.view.offset;
        dstOffset  = dstBundle.view.offset;
        vertStride = bundle.view.stride;
        vertCount  = bundle.view.count + dstBundle.view.count;

        vbView.resize(vertCount * vertStride);
        srcVBView.resize(bundle.view.length);
        std::copy(_data.begin() + srcOffset, _data.begin() + bundle.view.length, srcVBView.begin());
        srcOffset += srcVBView.size();

        dstVBView.resize(dstBundle.view.length);
        std::copy(mesh->_data.begin() + dstOffset, mesh->_data.begin() + dstOffset + dstBundle.view.length, dstVBView.begin());
        dstOffset += dstVBView.size();

        std::copy(srcVBView.begin(), srcVBView.end(), vbView.begin());

        srcAttrOffset = 0;
        for (const auto &attr : bundle.attributes) {
            dstVBOffset = 0;
            hasAttr     = false;
            for (const auto &dstAttr : dstBundle.attributes) {
                if (attr.name == dstAttr.name && attr.format == dstAttr.format) {
                    hasAttr = true;
                    break;
                }
                dstVBOffset += gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(dstAttr.format)].size;
            }
            if (hasAttr) {
                attrSize    = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attr.format)].size;
                srcVBOffset = bundle.view.length + srcAttrOffset;
                for (uint32_t v = 0; v < dstBundle.view.count; ++v) {
                    dstAttrView.resize(attrSize);
                    std::copy(dstVBView.begin() + dstVBOffset, dstVBView.begin() + dstVBOffset + attrSize, dstAttrView.begin());
                    std::copy(dstAttrView.begin(), dstAttrView.end(), vbView.begin() + srcVBOffset);

                    if ((attr.name == gfx::ATTR_NAME_POSITION || attr.name == gfx::ATTR_NAME_NORMAL) && worldMatrix != nullptr) {
                        float *  f32Temp      = reinterpret_cast<float *>(vbView.data() + srcVBOffset);
                        uint32_t f32TempCount = 3;

                        vec3_temp.set(f32Temp[0], f32Temp[1], f32Temp[2]);
                        if (attr.name == gfx::ATTR_NAME_POSITION) {
                            vec3_temp.transformMat4(vec3_temp, *worldMatrix);
                        } else if (attr.name == gfx::ATTR_NAME_NORMAL) {
                            vec3_temp.transformQuat(rotate);
                        }

                        f32Temp[0] = vec3_temp.x;
                        f32Temp[1] = vec3_temp.y;
                        f32Temp[2] = vec3_temp.z;
                    }
                    srcVBOffset += bundle.view.stride;
                    dstVBOffset += dstBundle.view.stride;
                }
            }
            srcAttrOffset += gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attr.format)].size;
        }

        auto &vertexBundle       = vertexBundles[i];
        vertexBundle.attributes  = bundle.attributes,
        vertexBundle.view.offset = bufferBlob.getLength();
        vertexBundle.view.length = vbView.size();
        vertexBundle.view.count  = vertCount;
        vertexBundle.view.stride = vertStride;

        bufferBlob.addBuffer(vbView);
    }

    // merge index buffer
    uint32_t idxCount       = 0;
    uint32_t idxStride      = 2;
    uint32_t vertBatchCount = 0;

    std::vector<Mesh::ISubMesh> primitives;
    primitives.resize(_struct.primitives.size());

    for (size_t i = 0; i < _struct.primitives.size(); ++i) {
        const auto &prim    = _struct.primitives[i];
        auto &      dstPrim = mesh->_struct.primitives[i];

        primitives[i].primitiveMode       = prim.primitiveMode;
        primitives[i].vertexBundelIndices = prim.vertexBundelIndices;

        for (const uint32_t bundleIdx : prim.vertexBundelIndices) {
            vertBatchCount = std::max(vertBatchCount, _struct.vertexBundles[bundleIdx].view.count);
        }

        if (prim.indexView.has_value() && dstPrim.indexView.has_value()) {
            idxCount = prim.indexView.value().count;
            idxCount += dstPrim.indexView.value().count;

            srcOffset = prim.indexView.value().offset;
            dstOffset = dstPrim.indexView.value().offset;

            if (idxCount < 256) {
                idxStride = 1;
            } else if (idxCount < 65536) {
                idxStride = 2;
            } else {
                idxStride = 4;
            }

            ArrayBuffer ib;
            ib.resize(idxCount * idxStride);

            TypedArray ibView;
            TypedArray srcIBView;
            TypedArray dstIBView;

            if (idxStride == 2) {
                //cjh TODO:                ibView = Uint16Array(ib);
            } else if (idxStride == 1) {
                //                ibView = new Uint8Array(ib);
            } else { // Uint32
                     //                ibView = new Uint32Array(ib);
            }

            // merge src indices
            if (prim.indexView.value().stride == 2) {
                //                srcIBView = new Uint16Array(_data.buffer, srcOffset, prim.indexView.count);
            } else if (prim.indexView.value().stride == 1) {
                //                srcIBView = new Uint8Array(_data.buffer, srcOffset, prim.indexView.count);
            } else { // Uint32
                     //                srcIBView = new Uint32Array(_data.buffer, srcOffset, prim.indexView.count);
            }
            //
            if (idxStride == prim.indexView.value().stride) {
                //                ibView.set(srcIBView);
            } else {
                for (uint32_t n = 0; n < prim.indexView.value().count; ++n) {
                    //                    ibView[n] = srcIBView[n];
                }
            }
            srcOffset += prim.indexView.value().length;

            // merge dst indices
            if (dstPrim.indexView.value().stride == 2) {
                //cjh TODO:                dstIBView = new Uint16Array(mesh._data.buffer, dstOffset, dstPrim.indexView.count);
            } else if (dstPrim.indexView.value().stride == 1) {
                //cjh TODO:                dstIBView = new Uint8Array(mesh._data.buffer, dstOffset, dstPrim.indexView.count);
            } else { // Uint32
                     //cjh TODO:                dstIBView = new Uint32Array(mesh._data.buffer, dstOffset, dstPrim.indexView.count);
            }
            for (uint32_t n = 0; n < dstPrim.indexView.value().count; ++n) {
                //                ibView[prim.indexView.count + n] = vertBatchCount + dstIBView[n];
            }
            dstOffset += dstPrim.indexView.value().length;

            primitives[i].indexView.value().offset = bufferBlob.getLength();
            primitives[i].indexView.value().length = ib.size();
            primitives[i].indexView.value().count  = idxCount;
            primitives[i].indexView.value().stride = idxStride;

            bufferBlob.setNextAlignment(idxStride);
            bufferBlob.addBuffer(ib);
        }
    }

    // Create mesh struct.
    Mesh::IStruct meshStruct;
    meshStruct.vertexBundles = vertexBundles;
    meshStruct.primitives    = primitives;
    meshStruct.minPosition   = _struct.minPosition;
    meshStruct.maxPosition   = _struct.maxPosition;

    if (meshStruct.minPosition && mesh->_struct.minPosition && meshStruct.maxPosition && mesh->_struct.maxPosition) {
        if (worldMatrix != nullptr) {
            if (mesh->_struct.maxPosition.has_value() && mesh->_struct.minPosition.has_value()) {
                Vec3::add(mesh->_struct.maxPosition.value(), mesh->_struct.minPosition.value(), &boundingBox.center);
            }
            boundingBox.center.scale(0.5F);
            if (mesh->_struct.maxPosition.has_value() && mesh->_struct.minPosition.has_value()) {
                Vec3::subtract(mesh->_struct.maxPosition.value(), mesh->_struct.minPosition.value(), &boundingBox.halfExtents);
            }
            boundingBox.halfExtents.scale(0.5F);
            boundingBox.transform(*worldMatrix, &boundingBox);

            Vec3::add(boundingBox.center, boundingBox.halfExtents, &vec3_temp);
            Vec3::max(meshStruct.maxPosition.value(), vec3_temp, &meshStruct.maxPosition.value());
            Vec3::subtract(boundingBox.center, boundingBox.halfExtents, &vec3_temp);
            Vec3::min(meshStruct.minPosition.value(), vec3_temp, &meshStruct.minPosition.value());
        } else {
            Vec3::min(meshStruct.minPosition.value(), mesh->_struct.minPosition.value(), &meshStruct.minPosition.value());
            Vec3::max(meshStruct.maxPosition.value(), mesh->_struct.maxPosition.value(), &meshStruct.maxPosition.value());
        }
    }

    // Create mesh.
    Mesh::ICreateInfo createInfo;
    createInfo.structInfo = meshStruct;
    createInfo.data       = std::move(bufferBlob.getCombined());
    reset(createInfo);
    initialize();
    return true;
}

bool Mesh::validateMergingMesh(Mesh *mesh) {
    // validate vertex bundles
    if (_struct.vertexBundles.size() != mesh->_struct.vertexBundles.size()) {
        return false;
    }

    for (size_t i = 0; i < _struct.vertexBundles.size(); ++i) {
        const auto &bundle    = _struct.vertexBundles[i];
        auto &      dstBundle = mesh->_struct.vertexBundles[i];

        if (bundle.attributes.size() != dstBundle.attributes.size()) {
            return false;
        }
        for (size_t j = 0; j < bundle.attributes.size(); ++j) {
            if (bundle.attributes[j].format != dstBundle.attributes[j].format) {
                return false;
            }
        }
    }

    // validate primitives
    if (_struct.primitives.size() != mesh->_struct.primitives.size()) {
        return false;
    }
    for (size_t i = 0; i < _struct.primitives.size(); ++i) {
        const auto &prim    = _struct.primitives[i];
        auto &      dstPrim = mesh->_struct.primitives[i];
        if (prim.vertexBundelIndices.size() != dstPrim.vertexBundelIndices.size()) {
            return false;
        }
        for (size_t j = 0; j < prim.vertexBundelIndices.size(); ++j) {
            if (prim.vertexBundelIndices[j] != dstPrim.vertexBundelIndices[j]) {
                return false;
            }
        }
        if (prim.primitiveMode != dstPrim.primitiveMode) {
            return false;
        }

        if (prim.indexView.has_value()) {
            if (!dstPrim.indexView.has_value()) {
                return false;
            }
        } else if (dstPrim.indexView.has_value()) {
            return false;
        }
    }

    return true;
}

TypedArray Mesh::readAttribute(index_t primitiveIndex, const char *attributeName) {
    TypedArray result;
    accessAttribute(primitiveIndex, attributeName, [&](const IVertexBundle &vertexBundle, uint32_t iAttribute) {
        const uint32_t    vertexCount = vertexBundle.view.count;
        const gfx::Format format      = vertexBundle.attributes[iAttribute].format;
        if (vertexCount == 0) {
            return;
        }

        DataView inputView(_data, vertexBundle.view.offset + getOffset(vertexBundle.attributes, iAttribute));

        const auto &formatInfo = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];

        auto reader = getReader(inputView, format);
        if (reader == nullptr) {
            return;
        }

        const uint32_t componentCount = formatInfo.count;
        result                        = createTypedArrayWithGFXFormat(format, vertexCount * componentCount);
        const uint32_t inputStride    = vertexBundle.view.stride;
        for (uint32_t iVertex = 0; iVertex < vertexCount; ++iVertex) {
            for (uint32_t iComponent = 0; iComponent < componentCount; ++iComponent) {
                auto value = reader(inputStride * iVertex + typedarray::getBytesPerElement(result) * iComponent);
                typedarray::set(result, componentCount * iVertex + iComponent, value);
            }
        }
    });
    return result;
}

bool Mesh::copyAttribute(index_t primitiveIndex, const char *attributeName, ArrayBuffer &buffer, uint32_t stride, uint32_t offset) {
    bool written = false;
    accessAttribute(primitiveIndex, attributeName, [&](const IVertexBundle &vertexBundle, uint32_t iAttribute) {
        const uint32_t vertexCount = vertexBundle.view.count;
        if (vertexCount == 0) {
            written = true;
            return;
        }
        const gfx::Format format = vertexBundle.attributes[iAttribute].format;

        DataView inputView(_data, vertexBundle.view.offset + getOffset(vertexBundle.attributes, iAttribute));

        DataView outputView(buffer, offset);

        const auto &formatInfo = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];

        auto reader = getReader(inputView, format);
        if (reader == nullptr) {
            return;
        }

        auto writer = getWriter(outputView, format);
        if (writer == nullptr) {
            return;
        }

        const uint32_t componentCount = formatInfo.count;

        const uint32_t inputStride               = vertexBundle.view.stride;
        const uint32_t inputComponentByteLength  = getComponentByteLength(format);
        const uint32_t outputStride              = stride;
        const uint32_t outputComponentByteLength = inputComponentByteLength;
        for (uint32_t iVertex = 0; iVertex < vertexCount; ++iVertex) {
            for (uint32_t iComponent = 0; iComponent < componentCount; ++iComponent) {
                const uint32_t inputOffset  = inputStride * iVertex + inputComponentByteLength * iComponent;
                const uint32_t outputOffset = outputStride * iVertex + outputComponentByteLength * iComponent;
                writer(outputOffset, reader(inputOffset));
            }
        }
        written = true;
    });
    return written;
}

TypedArray Mesh::readIndices(index_t primitiveIndex) {
    if (primitiveIndex >= _struct.primitives.size()) {
        return {};
    }
    const auto &primitive = _struct.primitives[primitiveIndex];
    if (!primitive.indexView.has_value()) {
        return {};
    }
    const uint32_t stride     = primitive.indexView.value().stride;
    const uint32_t count      = primitive.indexView.value().count;
    const uint32_t byteOffset = primitive.indexView.value().offset;
    TypedArray     ret;
    if (stride == 1) {
        Uint8Array result(count); //cjh TODO: it's reference in JS but we use copy operation here
        std::memcpy(_data.data() + byteOffset, result.data(), count * 1);
        ret = result;
    } else if (stride == 2) {
        Uint16Array result(count);
        std::memcpy(_data.data() + byteOffset, result.data(), count * 2);
        ret = result;
    } else {
        Uint32Array result(count);
        std::memcpy(_data.data() + byteOffset, result.data(), count * 4);
        ret = result;
    }

    return ret;
}

bool Mesh::copyIndices(index_t primitiveIndex, TypedArray &outputArray) {
    if (primitiveIndex >= _struct.primitives.size()) {
        return false;
    }
    const auto &primitive = _struct.primitives[primitiveIndex];
    if (!primitive.indexView.has_value()) {
        return false;
    }

    const uint32_t    indexCount  = primitive.indexView.value().count;
    const gfx::Format indexFormat = primitive.indexView.value().stride == 1 ? gfx::Format::R8UI : (primitive.indexView.value().stride == 2 ? gfx::Format::R16UI : gfx::Format::R32UI);
    DataView          view{_data};
    auto              reader = getReader(view, indexFormat);
    for (uint32_t i = 0; i < indexCount; ++i) {
        typedarray::set(outputArray, i, reader(primitive.indexView.value().offset + gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(indexFormat)].size * i));
    }
    return true;
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
    gfx::BufferList buffers;
    for (const auto &vertexBundle : _struct.vertexBundles) {
        auto vertexBuffer = gfxDevice->createBuffer({gfx::BufferUsageBit::VERTEX,
                                                     gfx::MemoryUsageBit::DEVICE,
                                                     vertexBundle.view.length,
                                                     vertexBundle.view.stride});

        vertexBuffer->update(data.data() + vertexBundle.view.offset, vertexBundle.view.length);
        buffers.emplace_back(vertexBuffer);
    }
}

void Mesh::initDefault(const std::optional<std::string> &uuid /* = {}*/) {
    Super::initDefault(uuid);
    ICreateInfo info;
    reset(info);
}

bool Mesh::validate() const {
    return !_renderingSubMeshes.empty() && !_data.empty();
}

TypedArray Mesh::createTypedArrayWithGFXFormat(gfx::Format format, uint32_t count) {
    const auto &   info   = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    const uint32_t stride = info.size / info.count;

    switch (info.type) {
        case gfx::FormatType::UNORM:
        case gfx::FormatType::UINT: {
            switch (stride) {
                case 1: return Uint8Array(count);
                case 2: return Uint16Array(count);
                case 4: return Uint32Array(count);
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::SNORM:
        case gfx::FormatType::INT: {
            switch (stride) {
                case 1: return Int8Array(count);
                case 2: return Int16Array(count);
                case 4: return Int32Array(count);
                default:
                    break;
            }
            break;
        }
        case gfx::FormatType::FLOAT: {
            return Float32Array(count);
        }
        default:
            break;
    }

    return Float32Array(count);
}

} // namespace cc
