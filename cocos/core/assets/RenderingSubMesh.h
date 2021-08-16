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

#include "core/assets/Asset.h"
#include "renderer/gfx-base/GFXDef.h"

#include <variant>

namespace cc {

/**
 * @en Array views for index buffer
 * @zh 允许存储索引的数组视图。
 */
using IBArray = std::variant<Uint8Array, Uint16Array, Uint32Array>;

/**
 * @en The interface of geometric information
 * @zh 几何信息。
 */
struct IGeometricInfo {
    /**
     * @en Vertex positions
     * @zh 顶点位置。
     */
    Float32Array positions;

    /**
     * @en Indices data
     * @zh 索引数据。
     */
    IBArray indices;

    /**
     * @en Whether the geometry is treated as double sided
     * @zh 是否将图元按双面对待。
     */
    bool doubleSided;

    /**
     * @en The bounding box
     * @zh 此几何体的轴对齐包围盒。
     */
    BoundingBox boundingBox;
};

/**
 * @en Flat vertex buffer
 * @zh 扁平化顶点缓冲区
 */
struct IFlatBuffer {
    uint32_t stride;
    uint32_t count;
    Uint8Array buffer;
};

class Mesh;

namespace gfx {
    class Buffer;
}
/**
 * @en Sub mesh for rendering which contains all geometry data, it can be used to create [[InputAssembler]].
 * @zh 包含所有顶点数据的渲染子网格，可以用来创建 [[InputAssembler]]。
 */
class RenderingSubMesh final : public Asset {
public:
    Mesh* mesh {nullptr};

    uint32_t subMeshIdx {0};

private:
    std::vector<IFlatBuffer> _flatBuffers;

    std::vector<gfx::Buffer*> _jointMappedBuffers;

    std::vector<uint32_t> _jointMappedBufferIndices;

    VertexIdChannel _vertexIdChannel;

    IGeometricInfo _geometricInfo;

    std::vector<gfx::Buffer*> _vertexBuffers;

    gfx::AttributeList _attributes;

    gfx::Buffer* _indexBuffer {nullptr};

    gfx::Buffer* _indirectBuffer {nullptr};

    gfx::PrimitiveMode _primitiveMode {gfx::PrimitiveMode::TRIANGLE_LIST};

    gfx::InputAssemblerInfo _iaInfo;
};

} // namespace cc {


