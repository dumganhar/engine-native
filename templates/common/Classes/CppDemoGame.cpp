/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "Game.h"
#include "cocos/bindings/event/CustomEventTypes.h"
#include "cocos/bindings/event/EventDispatcher.h"
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_classtype.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "cocos/bindings/manual/jsb_module_register.h"
#include "cocos/platform/FileUtils.h"

#if (CC_PLATFORM == CC_PLATFORM_MAC_IOS)
    #include "platform/Device.h"
#endif

#include "SimpleDemo.h"
#include "base/Scheduler.h"
#include "core/platform/Macro.h"

SimpleDemo simpleDemo;

Game::Game(int width, int height, uintptr_t windowHandle) : cc::Application(width, height) {
    _windowHandle = windowHandle;
}

bool Game::init() {
    cc::Application::init();

#if 0
    
    se::ScriptEngine *se = se::ScriptEngine::getInstance();

    jsb_set_xxtea_key("");
    jsb_init_file_operation_delegate();

    #if defined(CC_DEBUG) && (CC_DEBUG > 0)
    // Enable debugger here
    jsb_enable_debugger("0.0.0.0", 6086, false);
    #endif

    se->setExceptionCallback([](const char *location, const char *message, const char *stack) {
        // Send exception information to server like Tencent Bugly.
        CC_LOG_ERROR("\nUncaught Exception:\n - location :  %s\n - msg : %s\n - detail : \n      %s\n", location, message, stack);
    });

    jsb_register_all_modules();

    se->start();

    auto fu = cc::FileUtils::getInstance();;
    
    fu->addSearchPath("gen-res");
    
    se::AutoHandleScope hs;
    jsb_run_script("jsb-adapter/jsb-builtin.js");
    jsb_run_script("main.js");

#endif

#if (CC_PLATFORM == CC_PLATFORM_MAC_IOS)
    cc::Vec2 logicSize  = getViewLogicalSize();
    float    pixelRatio = cc::Device::getDevicePixelRatio();
    cc::EventDispatcher::dispatchResizeEvent(logicSize.x * pixelRatio, logicSize.y * pixelRatio);
#endif

    simpleDemo.setup(getViewLogicalSize().x, getViewLogicalSize().y, _windowHandle);

    cc::Application::getInstance()->getScheduler()->schedule([](float dt) {
        simpleDemo.step(dt);
        //        v8::Isolate::GetCurrent()->RunMicrotasks();
    },
                                                             &simpleDemo, 0.F, cc::macro::REPEAT_FOREVER, 0, false, "simpleDemo");

    return true;
}

void Game::onPause() {
    cc::Application::onPause();
    cc::EventDispatcher::dispatchEnterBackgroundEvent();
}

void Game::onResume() {
    cc::Application::onResume();
    cc::EventDispatcher::dispatchEnterForegroundEvent();
}

void Game::onClose() {
    simpleDemo.finalize();

    cc::Application::onClose();
    cc::EventDispatcher::dispatchCloseEvent();
}
