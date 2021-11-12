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

#include <string>

namespace cc {

class EventTypesToJS final {
public:
    static const std::string ROOT_BATCH2D_INIT;
    static const std::string ROOT_BATCH2D_UPDATE;
    static const std::string ROOT_BATCH2D_UPLOAD_BUFFERS;
    static const std::string ROOT_BATCH2D_RESET;

    static const std::string NODE_REATTACH;
    static const std::string NODE_REMOVE_PERSIST_ROOT_NODE;
    static const std::string NODE_DESTROY_COMPONENTS;
    static const std::string NODE_UI_TRANSFORM_DIRTY;
    static const std::string NODE_ACTIVE_NODE;
    static const std::string NODE_ON_BATCH_CREATED;

    static const std::string MODEL_UPDATE_TRANSFORM;
    static const std::string MODEL_UPDATE_UBO;
    static const std::string MODEL_UPDATE_LOCAL_DESCRIPTORS;
    static const std::string MODEL_UPDATE_INSTANCED_ATTRIBUTES;
    static const std::string MODEL_GET_MACRO_PATCHES;
};

} // namespace cc
