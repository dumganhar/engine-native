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

#include "core/scene-graph/NodeEventProcessor.h"
#include "core/scene-graph/BaseNode.h"
namespace cc {
namespace scenegraph {
bool NodeEventProcessor::hasEventListener(NodeEventType  /*type*/, const std::function<void(BaseNode *)> & /*callback*/, const std::any & /*target*/, bool  /*useCapture*/) {
    bool has = false;
    return has;
}

bool NodeEventProcessor::hasEventListener(NodeEventType  /*type*/) {
    bool has = false;
    return has;
}

void NodeEventProcessor::targetOff(NodeEventType target) {
}

bool NodeEventProcessor::on(NodeEventType  /*type*/, const std::function<void(BaseNode *)> & /*callback*/, const std::any & /*target*/, bool  /*useCapture*/) {
    return false;
}

bool NodeEventProcessor::once(NodeEventType  /*type*/, const std::function<void(BaseNode *)> & /*callback*/, const std::any & /*target*/, bool  /*useCapture*/) {
    return false;
}

bool NodeEventProcessor::off(NodeEventType  /*type*/, const std::function<void(BaseNode *)> & /*callback*/, const std::any & /*target*/, bool  /*useCapture*/) {
    return false;
}

void NodeEventProcessor::emit(NodeEventType type, const std::any &arg1, const std::any &arg2, const std::any &arg3, const std::any &arg4) {
}

} // namespace scenegraph
} // namespace cc