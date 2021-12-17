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

#include <cstdint>
#include <string>
#include <vector>
#include "cocos/base/Optional.h"
namespace cc {

struct IMeshBufferView {
    uint32_t offset{0};
    uint32_t length{0};
    uint32_t count{0};
    uint32_t stride{0};
};

using MeshWeightsType = std::vector<float>;

struct MorphTarget {
    /**
     * Displacement of each target attribute.
     */
    std::vector<IMeshBufferView> displacements;
};

struct SubMeshMorph {
    /**
     * Attributes to morph.
     */
    std::vector<std::string> attributes;

    /**
     * Targets.
     */
    std::vector<MorphTarget> targets;

    /**
     * Initial weights of each target.
     */
    cc::optional<MeshWeightsType> weights;
};

struct Morph {
    /**
     * Morph data of each sub-mesh.
     */
    std::vector<cc::optional<SubMeshMorph>> subMeshMorphs;

    /**
     * Common initial weights of each sub-mesh.
     */
    cc::optional<MeshWeightsType> weights;

    /**
     * Name of each target of each sub-mesh morph.
     * This field is only meaningful if every sub-mesh has the same number of targets.
     */
    cc::optional<std::vector<std::string>> targetNames;
};

} // namespace cc
