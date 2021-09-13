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

bool NodeEventProcessor::hasEventListener(const std::string & /*type*/, const std::function<void(BaseNode *)> & /*callback*/, const std::any & /*target*/, bool /*useCapture*/) {
    bool has = false;
    return has;
}

bool NodeEventProcessor::hasEventListener(const std::string & /*type*/, const std::function<void(BaseNode *)> & /*callback*/) {
    bool has = false;
    return has;
}

bool NodeEventProcessor::hasEventListener(const std::string & /*type*/) {
    bool has = false;
    return has;
}

void NodeEventProcessor::targetOff(const std::string &target) {
}

bool NodeEventProcessor::on(const std::string & /*unused*/, const std::function<void(BaseNode *)> & /*unused*/) {
    return false;
}

bool NodeEventProcessor::on(const std::string & /*unused*/, const std::function<void(BaseNode *)> & /*callback*/, const std::any & /*target*/, bool /*useCapture*/) {
    return false;
}

bool NodeEventProcessor::once(const std::string & /*unused*/, const std::function<void(BaseNode *)> & /*unused*/) {
    return false;
}

bool NodeEventProcessor::once(const std::string & /*type*/, const std::function<void(BaseNode *)> & /*callback*/, const std::any & /*target*/, bool /*useCapture*/) {
    return false;
}

bool NodeEventProcessor::off(const std::string & /*unused*/, const std::function<void(BaseNode *)> & /*unused*/) {
    return false;
}

bool NodeEventProcessor::off(const std::string & /*type*/, const std::function<void(BaseNode *)> & /*callback*/, const std::any & /*target*/, bool /*useCapture*/) {
    return false;
}

void NodeEventProcessor::emit(const std::string &type, const std::any &args) {
}

void NodeEventProcessor::emit(const std::string &type, const std::any &arg1, const std::any &arg2, const std::any &arg3, const std::any &arg4) {
}

} // namespace cc
