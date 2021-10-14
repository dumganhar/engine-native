/****************************************************************************
Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

http://www.cocos.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

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
#include "core/scene-graph/SceneGraphModuleHeader.h"
#include "gtest/gtest.h"
#include "renderer/GFXDeviceManager.h"
#include "renderer/gfx-base/GFXDef.h"
#include "utils.h"

using namespace cc;
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

    //    TestFunctor(const TestFunctor&) {
    //        CC_LOG_DEBUG("copy consturctor");
    //    }
    //
    //    TestFunctor& operator=(const TestFunctor&) {
    //        CC_LOG_DEBUG("copy operator");
    //    }
    //
    //    TestFunctor(TestFunctor&&) {
    //        CC_LOG_DEBUG("move consturctor");
    //    }
    //
    //    TestFunctor& operator=(TestFunctor&&) {
    //        CC_LOG_DEBUG("move operator");
    //    }

private:
    Fn                        _cb;
    std::shared_ptr<uint32_t> _calledCount{std::make_shared<uint32_t>(0)};
};

class MyCallbackTarget {
public:
};

TEST(CoreEventCallbacksInvoker, output_log) {
    static CallbackInfoBase::ID id1{0};
    static CallbackInfoBase::ID id2{0};
    static CallbackInfoBase::ID id3{0};
    static CallbackInfoBase::ID id4{0};
    static CallbackInfoBase::ID id5{0};
    static CallbackInfoBase::ID id6{0};

    CallbacksInvoker ci;

    class MyTarget : CCObject {
    public:
        MyTarget(CallbacksInvoker &ci)
        : _ci(ci) {}
        void foo() {
            CC_LOG_DEBUG("magic: %d, foo", magic);
        }

        void haha1(int a) {
            CC_LOG_DEBUG("magic: %d, haha1", magic);
            _ci.off("memberfunction0", id5);
        }

        void haha2(int a) {
            CC_LOG_DEBUG("magic: %d, haha2", magic);
        }

        void haha3(int a) {
            CC_LOG_DEBUG("magic: %d, haha3", magic);
        }

        void haha4(int a) {
            CC_LOG_DEBUG("magic: %d, haha4", magic);
        }

        void haha5(int a) {
            CC_LOG_DEBUG("magic: %d, haha5", magic);
        }

        void foo1(int a) {
            CC_LOG_DEBUG("magic: %d, foo1, a: %d", magic, a);
        }

        void foo2(int a, float b) {
            CC_LOG_DEBUG("magic: %d, foo2, a: %d, b: %f", magic, a, b);
        }
        void foo3(int a, float b, bool c) {
            CC_LOG_DEBUG("magic: %d, foo3, a: %d, b: %f, c: %d", magic, a, b, c);
        }

        void xxx() {
            CC_LOG_DEBUG("magic: %d, xxx", magic);
        }

        void xxx1(int a) {
            CC_LOG_DEBUG("magic: %d, xxx1, a: %d", magic, a);
        }

        void xxx2(int a, float b) {
            CC_LOG_DEBUG("magic: %d, xxx2, a: %d, b: %f", magic, a, b);
        }
        void xxx3(int a, float b, bool c) {
            CC_LOG_DEBUG("magic: %d, xxx3, a: %d, b: %f, c: %d", magic, a, b, c);
        }

        int               magic = 12334;
        CallbacksInvoker &_ci;
    };
    MyTarget target{ci};

    ci.on("hello", [](int a) {
        CC_LOG_DEBUG("hello callback, a: %d", a);
    });

    ci.emit("hello", 100);

    auto ret = ci.hasEventListener("xxx");
    ret      = ci.hasEventListener("hello");

    ci.on("memberfunction0", CC_CALLBACK_INVOKE_1(MyTarget::haha1, &target, int), id3);
    ci.on("memberfunction0", CC_CALLBACK_INVOKE_1(MyTarget::haha2, &target, int), id4);
    ci.on("memberfunction0", CC_CALLBACK_INVOKE_1(MyTarget::haha3, &target, int), id5);
    ci.on("memberfunction0", CC_CALLBACK_INVOKE_1(MyTarget::haha4, &target, int), id6);
    ci.on("memberfunction0", CC_CALLBACK_INVOKE_1(MyTarget::foo1, &target, int), id1);
    ci.on("memberfunction0", CC_CALLBACK_INVOKE_1(MyTarget::xxx1, &target, int), id2);

    ci.emit("memberfunction0", 100);
    CC_LOG_DEBUG("--------------------------");
    ci.emit("memberfunction0", 100);
    CC_LOG_DEBUG("--------------------------");
    ci.off("memberfunction0", id1);
    ci.emit("memberfunction0", 100);
    CC_LOG_DEBUG("--------------------------");
    ci.on("memberfunction1", CC_CALLBACK_INVOKE_1(MyTarget::foo1, &target, int));
    ci.emit("memberfunction1", 123);
    CC_LOG_DEBUG("--------------------------");
    ci.on("memberfunction2", CC_CALLBACK_INVOKE_2(MyTarget::foo2, &target, int, float));
    ci.emit("memberfunction2", 234, 345.3F);
    CC_LOG_DEBUG("--------------------------");
    ci.on("memberfunction3", CC_CALLBACK_INVOKE_3(MyTarget::foo3, &target, int, float, bool));
    ci.emit("memberfunction3", 323, 34.3F, true);
    CC_LOG_DEBUG("--------------------------");
}

TEST(CoreEventCallbacksInvoker, test) {
    CallbacksInvoker     ci;
    CallbackInfoBase::ID id1{0}, id2{0}, id3{0};

    TestFunctor<> cb1{[]() {}};
    TestFunctor<> cb2{[]() {}};
    TestFunctor<> cb3{[]() {}};

    ci.on("a", cb1, id1);
    EXPECT_FALSE(ci.hasEventListener("a", 12334));
    EXPECT_TRUE(ci.hasEventListener("a", id1));
    ci.on("a", cb2, id2);
    ci.on("b", cb3, id3);

    ci.emit("a");
    EXPECT_EQ(cb1.getCalledCount(), 1);
    EXPECT_EQ(cb2.getCalledCount(), 1);

    ci.emit("b");
    EXPECT_EQ(cb3.getCalledCount(), 1);

    ci.off("a", id2);
    ci.emit("a");
    EXPECT_EQ(cb1.getCalledCount(), 2);
    EXPECT_EQ(cb2.getCalledCount(), 1);

    ci.on("a", cb2);
    EXPECT_TRUE(ci.hasEventListener("a"));
    ci.offAll("a");
    EXPECT_FALSE(ci.hasEventListener("a"));

    ci.emit("a");
    EXPECT_EQ(cb1.getCalledCount(), 2);
    EXPECT_EQ(cb2.getCalledCount(), 1);
}

TEST(CoreEventCallbacksInvoker, remove_self_during_invoking) {
    CallbacksInvoker ci;

    CallbackInfoBase::ID id1{0};
    TestFunctor<>        cb1{[&ci, &id1]() {
        ci.off("eve", id1);
    }};
    TestFunctor<>        cb2{[]() {}};

    ci.on("eve", cb1, id1);
    ci.on("eve", cb2);
    ci.emit("eve");
    EXPECT_EQ(cb2.getCalledCount(), 1);
    ci.emit("eve");
    EXPECT_EQ(cb1.getCalledCount(), 1);
    EXPECT_EQ(cb2.getCalledCount(), 2);
}

TEST(CoreEventCallbacksInvoker, remove_self_with_target_during_invoking) {
    CallbacksInvoker     ci;
    MyCallbackTarget     target;
    CallbackInfoBase::ID id1{0};

    TestFunctor<> cb1{[&]() {
        ci.off("eve", id1, &target);
    }};

    TestFunctor<> cb2{[]() {}};

    ci.on("eve", cb1, id1, &target);
    ci.on("eve", cb2, &target);
    ci.emit("eve");
    EXPECT_EQ(cb1.getCalledCount(), 1);
    EXPECT_EQ(cb2.getCalledCount(), 1);

    ci.emit("eve");
    EXPECT_EQ(cb1.getCalledCount(), 1);
    EXPECT_EQ(cb2.getCalledCount(), 2);
}
