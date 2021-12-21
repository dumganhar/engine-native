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

#include "core/TypedArray.h"

//cjh TODO: TerrainLod is not used in ts?

namespace cc {

constexpr int32_t TERRAIN_LOD_VERTS       = 33;
constexpr int32_t TERRAIN_LOD_TILES       = 32;
constexpr int32_t TERRAIN_LOD_LEVELS      = 4;
constexpr int32_t TERRAIN_LOD_NORTH_INDEX = 0;
constexpr int32_t TERRAIN_LOD_SOUTH_INDEX = 1;
constexpr int32_t TERRAIN_LOD_WEST_INDEX  = 2;
constexpr int32_t TERRAIN_LOD_EAST_INDEX  = 3;

struct TerrainIndexPool {
    int32_t     size{0};
    Uint16Array indices{nullptr};
};

struct TerrainIndexData {
    int32_t     start{0};
    int32_t     size{0};
    Uint16Array buffer;
    int32_t     prim_count{0};
};

struct TerrainLodKey {
    int32_t level{0};
    int32_t north{0};
    int32_t south{0};
    int32_t west{0};
    int32_t east{0};

    bool compare(const TerrainLodKey &rk) {
        return level == rk.level && north == rk.north && south == rk.south && west == rk.west && east == rk.east;
    }
};

class TerrainLod final {
public:
    TerrainLod();
    ~TerrainLod() = default;

private:
    void genBodyIndex();
    void genBodyIndexByLevel(int32_t level);
    void genConnecterIndex();
    void genConnecterIndexNorth(int32_t level, int32_t connecter);
    void genConnecterIndexSouth(int32_t level, int32_t connecter);
    void genConnecterIndexWest(int32_t level, int32_t connecter);
    void genConnecterIndexEast(int32_t level, int32_t connecter);

    TerrainIndexPool mBodyIndex[TERRAIN_LOD_LEVELS]{};
    TerrainIndexPool mConnecterIndex[TERRAIN_LOD_LEVELS][TERRAIN_LOD_LEVELS][4]{};
};

} // namespace cc
