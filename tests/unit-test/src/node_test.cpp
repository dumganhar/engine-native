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
#include "core/Director.h"
#include "core/Root.h"
#include "core/platform/event-manager/Events.h"
#include "core/scene-graph/SceneGraphModuleHeader.h"
#include "gtest/gtest.h"
#include "renderer/GFXDeviceManager.h"
#include "renderer/gfx-base/GFXDef.h"
#include "utils.h"

using namespace cc;
using namespace cc::event;
using namespace cc::gfx;

namespace {

template <typename T>
struct FunctionTraits
: public FunctionTraits<decltype(&T::operator())> {};

template <typename ClassType, typename ReturnType, typename... Args>
struct FunctionTraits<ReturnType (ClassType::*)(Args...) const> {
    typedef std::function<ReturnType(Args...)> type;
};

template <typename ClassType, typename ReturnType, typename... Args>
struct FunctionTraits<ReturnType (ClassType::*)(Args...)> {
    typedef std::function<ReturnType(Args...)> type;
};

template <typename T>
typename FunctionTraits<T>::type toFunction(T l) {
    return static_cast<typename FunctionTraits<T>::type>(l);
}

} // namespace

template <typename... Args>
class TestFunctor final {
public:
    using Fn = std::function<void(Args...)>;

    TestFunctor(Fn &&cb)
    : _cb(std::forward<Fn>(cb)) {
    }

    template <typename Lambda>
    TestFunctor(const Lambda &cb) {
        _cb = toFunction(cb);
    }

    void operator()(Args &&...args) {
        _cb(std::forward<Args>(args)...);
        *_calledCount = *_calledCount + 1;
    }

    uint32_t getCalledCount() const {
        return *_calledCount;
    }

    void clear() {
        *_calledCount = 0;
    }

private:
    Fn                        _cb;
    std::shared_ptr<uint32_t> _calledCount{std::make_shared<uint32_t>(0)};
};

class MyCallbackTarget {
public:
};

TEST(NodeTest, inverseTransformPoint) {
    initCocos(100, 100);

    auto *director = Director::getInstance();
    auto *scene    = director->getScene();

    auto *parentNode = new Node("");
    auto *subNode    = new Node("");
    parentNode->setPosition(20.F, -30.F, 100.F);
    subNode->setPosition(55, 35, 22);
    parentNode->setParent(scene);
    subNode->setParent(parentNode);
    auto p = Vec3(100.F, 200.F, 0.F);
    subNode->inverseTransformPoint(p, p);

    EXPECT_EQ(p, Vec3(25.F, 195.F, -122.F));

    // //xwx FIXME: gfx-validator Assert
    destroyCocos();
}

TEST(NodeTest, activeInHierarchyChanged) {
    // TODO(xwx): should fix once implementation first
    // initCocos(100, 100);
    // auto *        director = Director::getInstance();
    // auto *        scene    = director->getScene();
    // auto *        node     = new Node();
    // TestFunctor<> cb{[](Node *node) {
    //     EXPECT_TRUE(node->isActiveInHierarchy());
    // }};
    // node->once(NodeEventType::ACTIVE_IN_HIERARCHY_CHANGED, cb);
    // scene->addChild(node);
    // TestFunctor<> cb1{[](Node *node) {
    //     EXPECT_FALSE(node->isActiveInHierarchy());
    // }};
    // node->once(NodeEventType::ACTIVE_IN_HIERARCHY_CHANGED, cb1);
    // node->setActive(false);
    // node->once(NodeEventType::ACTIVE_IN_HIERARCHY_CHANGED, cb);
    // node->setActive(true);

    // auto* node2 = new Node();
    // scene->addChild(node2);
    // node2->setActive(false);
    // node->once(NodeEventType::ACTIVE_IN_HIERARCHY_CHANGED,cb1);
    // node2->addChild(node);

    // node->once(NodeEventType::ACTIVE_IN_HIERARCHY_CHANGED, cb);
    // node->setParent(scene);
    // EXPECT_EQ(cb.getCalledCount(), 3);
    // EXPECT_EQ(cb1.getCalledCount(), 2);

    // // xwx FIXME: gfx-validator Assert
    // destroyCocos();
}