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

#include "core/Types.h"
#include "core/asset-manager/Cache.h"
#include "core/asset-manager/Shared.h"

namespace cc {

struct Versions {
    std::vector<std::string> import;
    std::vector<std::string> native;
};

struct IConfigOption {
    std::string importBase;
    std::string nativeBase;
    std::string base;
    std::string name;
    std::vector<std::string> deps;
    std::vector<std::string> uuids;
    Record<std::string, std::vector<std::any>> paths;
    Record<std::string, std::string> scenes;
    Record<std::string, std::vector<std::string>> packs;
    Versions versions;
    std::vector<std::string> redirect;
    bool debug {false};
    std::vector<std::string> types;
    Record<std::string, std::vector<std::string>> extensionMap;
};

struct IPackInfo;

struct IAssetInfo {
    std::string uuid;
    std::vector<std::shared_ptr<IPackInfo>> packs;
    std::string redirect;
    std::string ver;
    std::string nativeVer;
    std::string extension;
};

struct IPackInfo : public IAssetInfo {
    std::vector<std::string> packedUuids;
    std::string ext;
};

struct IAddressableInfo : public IAssetInfo {
    std::string path;
    AssetType ctor;
};

struct ISceneInfo : public IAssetInfo {
    std::string url;
};

bool isMatchByWord(const std::string& path, const std::string& test);

void processOptions(const IConfigOption& options);

class Config final {
public:
    std::string name;

    std::string base;

    std::string importBase;

    std::string nativeBase;

    std::vector<std::string> deps;

    Cache<IAssetInfo> assetInfos;

    Cache<ISceneInfo> scenes;

    Cache<std::vector<IAddressableInfo>> paths;

    void init (const IConfigOption& options);

    IAddressableInfo* getInfoWithPath (const std::string& path, AssetType type);

    std::vector<IAddressableInfo*> getDirWithPath (const std::string& path, AssetType type);

    IAssetInfo* getAssetInfo (const std::string& uuid);

    ISceneInfo* getSceneInfo (const std::string& name);

    void destroy ();

    void initUuid (const std::vector<std::string>& uuidList);

private:
    using PathList = Record<std::string, std::vector<std::string>>;
    using SceneList = Record<std::string, std::string>;
    using PackageList = Record<std::string, std::vector<std::string>>;

    void initPath (const PathList& pathList);

    void initScene (const SceneList& sceneList);

    void initPackage (const PackageList& packageList);

    void initVersion (const Versions& versions);

    void initRedirect (const std::vector<std::string>& redirect);
};

} // namespace cc {
