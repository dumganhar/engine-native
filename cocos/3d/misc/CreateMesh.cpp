#include "3d/misc/CreateMesh.h"
#include <algorithm>
#include "3d/assets/Mesh.h"
#include "3d/misc/BufferBlob.h"
#include "core/ArrayBuffer.h"
#include "core/DataView.h"
#include "renderer/gfx-base/GFXDef-common.h"

namespace cc {
namespace {
gfx::AttributeList defAttrs = {
    gfx::Attribute{.name = gfx::ATTR_NAME_POSITION, .format = gfx::Format::RGB32F},
    gfx::Attribute{.name = gfx::ATTR_NAME_NORMAL, .format = gfx::Format::RGB32F},
    gfx::Attribute{.name = gfx::ATTR_NAME_TEX_COORD, .format = gfx::Format::RG32F},
    gfx::Attribute{.name = gfx::ATTR_NAME_TANGENT, .format = gfx::Format::RGBA32F},
    gfx::Attribute{.name = gfx::ATTR_NAME_COLOR, .format = gfx::Format::RGBA32F},
};

// TODO(xwx): temporary usage and need to adjustment future
// default params behaviors just like on an plain, compact Float32Array
template <typename T>
void writeBuffer(DataView &target, const std::vector<T> &data, const gfx::Format &format = gfx::Format::R32F, uint32_t offset = 0, uint32_t stride = 0) {
    const gfx::FormatInfo &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(format)];
    if (stride == 0) {
        stride = info.size;
    }
    const uint32_t componentBytesLength = info.size / info.count;
    const uint32_t nSeg                 = std::floor(data.size() / info.count);

    const uint32_t bytes = info.size / info.count * 8;

    for (uint32_t iSeg = 0; iSeg < nSeg; ++iSeg) {
        uint32_t x = offset + stride * iSeg;
        for (uint32_t iComponent = 0; iComponent < info.count; ++iComponent) {
            const uint32_t y = x + componentBytesLength * iComponent;
            // default Little-Endian
            switch (info.type) {
                case gfx::FormatType::UINT:
                case gfx::FormatType::UNORM:
                    switch (bytes) {
                        case 8:
                            target.setUint8(y, data[info.count * iSeg + iComponent]);
                            break;
                        case 16:
                            target.setUint16(y, data[info.count * iSeg + iComponent]);
                            break;
                        case 32:
                            target.setUint32(y, data[info.count * iSeg + iComponent]);
                            break;
                        default:
                            CC_ASSERT(false);
                            break;
                    }
                    break;
                case gfx::FormatType::INT:
                case gfx::FormatType::SNORM:
                    switch (bytes) {
                        case 8:
                            target.setInt8(y, data[info.count * iSeg + iComponent]);
                            break;
                        case 16:
                            target.setInt16(y, data[info.count * iSeg + iComponent]);
                            break;
                        case 32:
                            target.setInt32(y, data[info.count * iSeg + iComponent]);
                            break;
                        default:
                            CC_ASSERT(false);
                            break;
                    }
                    break;
                case gfx::FormatType::UFLOAT:
                case gfx::FormatType::FLOAT:
                    switch (bytes) {
                        case 8:
                            target.setFloat32(y, data[info.count * iSeg + iComponent]);
                            break;
                        case 16:
                            target.setFloat32(y, data[info.count * iSeg + iComponent]);
                            break;
                        case 32:
                            target.setFloat32(y, data[info.count * iSeg + iComponent]);
                            break;
                        default:
                            CC_ASSERT(false);
                            break;
                    }
                    break;
                default:
                    CC_ASSERT(false);
                    break;
            }
        }
    }
}
} // namespace

Mesh *createMesh(const IGeometry &geometry, const ICreateMeshOptions &options /* = {}*/) {
    // Collect attributes and calculate length of result vertex buffer.
    gfx::AttributeList attributes;
    uint32_t           stride = 0;
    struct Channel {
        uint32_t           offset{0};
        std::vector<float> data; // float?
        gfx::Attribute     attribute;
    };
    std::vector<Channel> channels;
    uint32_t             vertCount = 0;

    const gfx::Attribute *attr = nullptr;

    std::vector<float> positions(geometry.positions);

    if (!positions.empty()) {
        attr = nullptr;
        if (geometry.attributes.has_value()) {
            for (const auto &att : geometry.attributes.value()) {
                if (att.name == gfx::ATTR_NAME_POSITION) {
                    attr = &att;
                    break;
                }
            }
        }

        if (attr == nullptr) {
            attr = &defAttrs[0];
        }

        attributes.emplace_back(*attr);
        const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attr->format)];
        vertCount        = std::max(vertCount, static_cast<uint32_t>(std::floor(positions.size() / info.count)));
        channels.emplace_back(Channel{.offset = stride, .data = positions, .attribute = *attr});
        stride += info.size;
    }

    if (geometry.normals.has_value() && !geometry.normals.value().empty()) {
        attr = nullptr;
        if (geometry.attributes.has_value()) {
            for (const auto &att : geometry.attributes.value()) {
                if (att.name == gfx::ATTR_NAME_NORMAL) {
                    attr = &att;
                    break;
                }
            }
        }

        if (attr == nullptr) {
            attr = &defAttrs[1];
        }

        attributes.emplace_back(*attr);
        const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attr->format)];
        vertCount        = std::max(vertCount, static_cast<uint32_t>(std::floor(geometry.normals->size() / info.count)));
        channels.emplace_back(Channel{.offset = stride, .data = geometry.normals.value(), .attribute = *attr});
        stride += info.size;
    }

    if (geometry.uvs.has_value() && !geometry.uvs.value().empty()) {
        attr = nullptr;
        if (geometry.attributes.has_value()) {
            for (const auto &att : geometry.attributes.value()) {
                if (att.name == gfx::ATTR_NAME_TEX_COORD) {
                    attr = &att;
                    break;
                }
            }
        }

        if (attr == nullptr) {
            attr = &defAttrs[2];
        }

        attributes.emplace_back(*attr);
        const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attr->format)];
        vertCount        = std::max(vertCount, static_cast<uint32_t>(std::floor(geometry.uvs->size() / info.count)));
        channels.emplace_back(Channel{.offset = stride, .data = geometry.uvs.value(), .attribute = *attr});
        stride += info.size;
    }

    if (geometry.tangents.has_value() && !geometry.tangents.value().empty()) {
        attr = nullptr;
        if (geometry.attributes.has_value()) {
            for (const auto &att : geometry.attributes.value()) {
                if (att.name == gfx::ATTR_NAME_TANGENT) {
                    attr = &att;
                    break;
                }
            }
        }

        if (attr == nullptr) {
            attr = &defAttrs[3];
        }

        attributes.emplace_back(*attr);
        const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attr->format)];
        vertCount        = std::max(vertCount, static_cast<uint32_t>(std::floor(geometry.tangents->size() / info.count)));
        channels.emplace_back(Channel{.offset = stride, .data = geometry.tangents.value(), .attribute = *attr});
        stride += info.size;
    }

    if (geometry.colors.has_value() && !geometry.colors.value().empty()) {
        attr = nullptr;
        if (geometry.attributes.has_value()) {
            for (const auto &att : geometry.attributes.value()) {
                if (att.name == gfx::ATTR_NAME_COLOR) {
                    attr = &att;
                    break;
                }
            }
        }

        if (attr == nullptr) {
            attr = &defAttrs[4];
        }

        attributes.emplace_back(*attr);
        const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attr->format)];
        vertCount        = std::max(vertCount, static_cast<uint32_t>(std::floor(geometry.colors->size() / info.count)));
        channels.emplace_back(Channel{.offset = stride, .data = geometry.colors.value(), .attribute = *attr});
        stride += info.size;
    }

    if (geometry.customAttributes.has_value()) {
        for (auto ca : geometry.customAttributes.value()) {
            const auto &info = gfx::GFX_FORMAT_INFOS[static_cast<uint32_t>(attr->format)];
            attributes.emplace_back(ca.attr);
            vertCount = std::max(vertCount, static_cast<uint32_t>(std::floor(ca.values.size() / info.count)));
            channels.emplace_back(Channel{.offset = stride, .data = ca.values, .attribute = ca.attr});
            stride += info.size;
        }
    }

    // Use this to generate final merged buffer.
    BufferBlob bufferBlob;

    // Fill vertex buffer.
    auto *   vertexBuffer = new ArrayBuffer(vertCount * stride);
    DataView vertexBufferView(vertexBuffer);
    for (const auto &channel : channels) {
        writeBuffer(vertexBufferView, channel.data, channel.attribute.format, channel.offset, stride);
    }
    bufferBlob.setNextAlignment(0);
    Mesh::IVertexBundle vertexBundle{
        .view = Mesh::IBufferView{
            .offset = bufferBlob.getLength(),
            .length = static_cast<uint32_t>(vertexBuffer->byteLength()),
            .count  = vertCount,
            .stride = stride},
        .attributes = attributes};
    bufferBlob.addBuffer(vertexBuffer);

    // Fill index buffer.
    ArrayBuffer *  indexBuffer{nullptr};
    uint32_t       idxCount  = 0;
    const uint32_t idxStride = 2;
    if (geometry.indices.has_value()) {
        const std::vector<uint32_t> &indices = geometry.indices.value();
        idxCount                             = indices.size();
        indexBuffer                          = new ArrayBuffer(idxStride * idxCount);
        DataView indexBufferView(indexBuffer);
        writeBuffer(indexBufferView, indices, gfx::Format::R16UI);
    }

    // Create primitive.
    Mesh::ISubMesh primitive{
        .vertexBundelIndices = {0},
        .primitiveMode       = geometry.primitiveMode.has_value() ? geometry.primitiveMode.value() : gfx::PrimitiveMode::TRIANGLE_LIST};

    if (indexBuffer) {
        bufferBlob.setNextAlignment(idxStride);
        primitive.indexView = Mesh::IBufferView{
            .offset = bufferBlob.getLength(),
            .length = indexBuffer->byteLength(),
            .count  = idxCount,
            .stride = idxStride};
        bufferBlob.addBuffer(indexBuffer);
    }

    cc::optional<Vec3> minPosition = geometry.minPos;
    if (minPosition.has_value() && options.calculateBounds.has_value() && options.calculateBounds.value()) {
        minPosition = Vec3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        for (uint32_t iVertex = 0; iVertex < vertCount; ++iVertex) {
            Vec3::min(minPosition.value(), Vec3(positions[iVertex * 3 + 0], positions[iVertex * 3 + 1], positions[iVertex * 3 + 2]), &minPosition.value());
        }
    }

    cc::optional<Vec3> maxPosition = geometry.maxPos;
    if (maxPosition.has_value() && options.calculateBounds.has_value() && options.calculateBounds.value()) {
        maxPosition = Vec3(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
        for (uint32_t iVertex = 0; iVertex < vertCount; ++iVertex) {
            Vec3::max(maxPosition.value(), Vec3(positions[iVertex * 3 + 0], positions[iVertex * 3 + 1], positions[iVertex * 3 + 2]), &maxPosition.value());
        }
    }

    // Create mesh struct
    Mesh::IStruct meshStruct{
        .vertexBundles = {vertexBundle},
        .primitives    = {primitive}};

    if (minPosition.has_value()) {
        meshStruct.minPosition = minPosition.value();
    }
    if (maxPosition.has_value()) {
        meshStruct.maxPosition = maxPosition.value();
    }

    // Create mesh.
    auto* out = new Mesh();
    out->reset(
        Mesh::ICreateInfo({
            .structInfo = std::move(meshStruct),
            .data       = Uint8Array(bufferBlob.getCombined())
        }));

    return out;
}

} // namespace cc
