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

#include "core/event/EventTypesToJS.h"

namespace cc {

const std::string EventTypesToJS::ROOT_BATCH2D_INIT{"ROOT_BATCH2D_INIT"};
const std::string EventTypesToJS::ROOT_BATCH2D_UPDATE{"ROOT_BATCH2D_UPDATE"};
const std::string EventTypesToJS::ROOT_BATCH2D_UPLOAD_BUFFERS{"ROOT_BATCH2D_UPLOAD_BUFFERS"};
const std::string EventTypesToJS::ROOT_BATCH2D_RESET{"ROOT_BATCH2D_RESET"};

const std::string EventTypesToJS::NODE_REATTACH{"NODE_REATTACH"};
const std::string EventTypesToJS::NODE_REMOVE_PERSIST_ROOT_NODE{"NODE_REMOVE_PERSIST_ROOT_NODE"};
const std::string EventTypesToJS::NODE_DESTROY_COMPONENTS{"NODE_DESTROY_COMPONENTS"};
const std::string EventTypesToJS::NODE_UI_TRANSFORM_DIRTY{"NODE_UI_TRANSFORM_DIRTY"};
const std::string EventTypesToJS::NODE_ACTIVE_NODE{"NODE_ACTIVE_NODE"};
const std::string EventTypesToJS::NODE_ON_BATCH_CREATED{"NODE_ON_BATCH_CREATED"};

const std::string EventTypesToJS::MODEL_UPDATE_TRANSFORM{"MODEL_UPDATE_TRANSFORM"};
const std::string EventTypesToJS::MODEL_UPDATE_UBO{"MODEL_UPDATE_UBO"};
const std::string EventTypesToJS::MODEL_UPDATE_LOCAL_DESCRIPTORS{"MODEL_UPDATE_LOCAL_DESCRIPTORS"};
const std::string EventTypesToJS::MODEL_UPDATE_INSTANCED_ATTRIBUTES{"MODEL_UPDATE_INSTANCED_ATTRIBUTES"};
const std::string EventTypesToJS::MODEL_GET_MACRO_PATCHES{"MODEL_GET_MACRO_PATCHES"};

} // namespace cc
