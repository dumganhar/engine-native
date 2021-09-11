/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

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

#include "SimpleDemo.h"
#include "3d/framework/MeshRenderer.h"
#include "3d/misc/CreateMesh.h"
#include "base/Log.h"
#include "core/assets/AssetsModuleHeader.h"
#include "core/builtin/BuiltinResMgr.h"
#include "renderer/GFXDeviceManager.h"

using namespace cc;
using namespace cc::gfx;

void SimpleDemo::setup(int width, int height) {
    CC_LOG_INFO("SimpleDemo::%s", __FUNCTION__);

    BindingMappingInfo bindingMappingInfo;
    bindingMappingInfo.bufferOffsets  = std::vector<int>{0, pipeline::globalUBOCount + pipeline::localUBOCount, pipeline::globalUBOCount};
    bindingMappingInfo.samplerOffsets = std::vector<int>{-pipeline::globalUBOCount, pipeline::globalSamplerCount + pipeline::localSamplerCount, pipeline::globalSamplerCount - pipeline::localUBOCount};
    bindingMappingInfo.flexibleSet    = 1;

    DeviceInfo info;
    info.width              = width;
    info.height             = height;
    info.pixelRatio         = 1;
    info.bindingMappingInfo = bindingMappingInfo;
    _device                 = DeviceManager::create(info);

    BuiltinResMgr::getInstance()->initBuiltinRes(_device);
}

void SimpleDemo::step(float dt) {
    //    CC_LOG_INFO("SimpleDemo::%s, dt: %.06f", __FUNCTION__, dt);
}

void SimpleDemo::finalize() {
    CC_LOG_INFO("SimpleDemo::%s", __FUNCTION__);
}
