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
#include "core/platform/event-manager/EventListeners.h"
#include "core/scene-graph/Node.h"
#include "core/scene-graph/NodeEvent.h"

namespace cc {

class Node;
class NodeEventProcessor final {
public:
    NodeEventProcessor() = default;
    explicit NodeEventProcessor(Node *node);
    ~NodeEventProcessor() = default;

    inline Node *getNode() { return _node; }
    void         reattach();
    void         destroy();

    /**
     * @zh
     * 分发事件到事件流中。
     *
     * @param event - 分派到事件流中的事件对象。
     */
    void dispatchEvent(event::Event *event);

    bool hasEventListener(const std::string &type);
    bool hasEventListener(const std::string &type, const std::function<void(Node *)> &callback);
    bool hasEventListener(const std::string &type, const std::function<void(Node *)> &callback, void *target);

    bool on(const std::string &type, const std::function<void(Node *)> &callback);
    bool on(const std::string &type, const std::function<void(Node *)> &callback, void *target, bool useCapture = false);

    void once(const std::string &type, const std::function<void(Node *)> &callback);
    void once(const std::string &type, const std::function<void(Node *)> &callback, void *target, bool useCapture = false);

    void off(const std::string &type, const std::function<void(Node *)> &callback);
    void off(const std::string &type, const std::function<void(Node *)> &callback, void *target, bool useCapture = false);

    /**
     * @zh
     * 通过事件名发送自定义事件
     *
     * @param type - 一个监听事件类型的字符串。
     * @param arg0 - 回调第一个参数。
     * @param arg1 - 回调第二个参数。
     * @param arg2 - 回调第三个参数。
     * @param arg3 - 回调第四个参数。
     * @param arg4 - 回调第五个参数。
     */
    // TODO(xwx): need to finish template usage
    // template <typename... Args>
    // void emit(const std::string &type, Args &&...args);
    void emit(const std::string &type, const std::any &arg);
    void emit(const std::string &type, const std::any &arg1, const std::any &arg2, const std::any &arg3, const std::any &arg4);

    void targetOff(const std::string &);

    void getCapturingTargets(const std::string &type, std::vector<Node *> &targets) const;
    void getBubblingTargets(const std::string &type, std::vector<Node *> &targets) const;

    inline CallbacksInvoker *    getBubblingTargets() const { return _bubblingTargets; }
    inline CallbacksInvoker *    getCapturingTargets() const { return _capturingTargets; }
    inline event::EventListener *getTouchListener() const { return _touchListener; }
    inline event::EventListener *getMouseListener() const { return _mouseListener; }

private:
    /**
     * @zh
     * 节点冒泡事件监听器
     */
    CallbacksInvoker *_bubblingTargets{nullptr};

    /**
     * @zh
     * 节点捕获事件监听器
     */
    CallbacksInvoker *_capturingTargets{nullptr};

    /**
     * @zh
     * 触摸监听器
     */
    event::EventListenerTouchOneByOne *_touchListener{nullptr};

    /**
     * @zh
     * 鼠标监听器
     */
    event::EventListenerMouse *_mouseListener{nullptr};

    Node *_node{nullptr};

    bool checknSetupSysEvent(const std::string &type);

    const std::function<void(Node *)> &onDispatch(const std::string &type, const std::function<void(Node *)> &callback, bool useCapture = false);
    const std::function<void(Node *)> &onDispatch(const std::string &type, const std::function<void(Node *)> &callback, void *target, bool useCapture = false);
    void                               offDispatch(const std::string &) const;
    void                               offDispatch(const std::string &, const std::function<void(Node *)> &callback, bool useCapture = false) const;
    void                               offDispatch(const std::string &, const std::function<void(Node *)> &callback, void *target, bool useCapture = false) const;

    CC_DISALLOW_COPY_MOVE_ASSIGN(NodeEventProcessor);
};

} // namespace cc
