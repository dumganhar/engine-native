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

#include <any>
#include <functional>
#include <string>
#include <variant>
#include "core/event/CallbacksInvoker.h"
#include "core/event/Event.h"
#include "core/scene-graph/BaseNode.h"
#include "core/scene-graph/NodeEvent.h"

namespace cc {

class BaseNode;
class NodeEventProcessor final {
private:
    BaseNode *_node{nullptr};

public:
    NodeEventProcessor(/* args */) = default;
    ~NodeEventProcessor()          = default;
    inline BaseNode *getNode() { return _node; }
    inline void      reattach() {}
    inline void      destroy() {}
    inline void      dispatchEvent(event::Event eve) {}

    CallbacksInvoker *bubblingTargets{nullptr};

    static bool hasEventListener(const std::string &);
    static bool hasEventListener(const std::string &, const std::function<void(BaseNode *)> &);
    static bool hasEventListener(const std::string &, const std::function<void(BaseNode *)> &, const std::any &, bool useCapture = false);
    static bool on(const std::string &, const std::function<void(BaseNode *)> &);
    static bool on(const std::string &, const std::function<void(BaseNode *)> &, const std::any &, bool useCapture = false);
    static bool once(const std::string &, const std::function<void(BaseNode *)> &);
    static bool once(const std::string &, const std::function<void(BaseNode *)> &, const std::any &, bool useCapture = false);
    static bool off(const std::string &, const std::function<void(BaseNode *)> &);
    static bool off(const std::string &, const std::function<void(BaseNode *)> &, const std::any &, bool useCapture = false);
    void        emit(const std::string &, const std::any &);
    void        emit(const std::string &, const std::any &, const std::any &, const std::any &, const std::any &);
    void        targetOff(const std::string &);
};

} // namespace cc
