/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

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

#import <Cocoa/Cocoa.h>
#import <algorithm>
#import <mutex>

#include "base/CCScheduler.h"
#include "base/CCAutoreleasePool.h"
#include "base/CCGLUtils.h"
#import "platform/CCApplication.h"
#import "platform/desktop/CCGLView-desktop.h"
#import "scripting/js-bindings/event/EventDispatcher.h"
#import "renderer/gfx/DeviceGraphics.h"
#import "scripting/js-bindings/jswrapper/SeApi.h"
#include "base/bgfx_platform.h"
#include "base/bgfx.h"
#include "bx/thread.h"

NS_CC_BEGIN

namespace
{
    int g_width = 0;
    int g_height = 0;
    bool setCanvasCallback(se::Object* global)
    {
        se::ScriptEngine* se = se::ScriptEngine::getInstance();
        char commandBuf[200] = {0};
        sprintf(commandBuf, "window.innerWidth = %d; window.innerHeight = %d;",
                g_width,
                g_height);
        se->evalString(commandBuf);
        fakegl::glViewport(0, 0, g_width, g_height);
        fakegl::glDepthMask(GL_TRUE);
        return true;
    }

    int32_t threadFunc(bx::Thread* _thread, void* _userData)
    {
        BX_UNUSED(_thread);

        Application* app = (Application*)_userData;

        CFBundleRef mainBundle = CFBundleGetMainBundle();
        if (mainBundle != nil)
        {
            CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
            if (resourcesURL != nil)
            {
                char path[PATH_MAX];
                if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8*)path, PATH_MAX) )
                {
                    chdir(path);
                }

                CFRelease(resourcesURL);
            }
        }

//        MainThreadEntry* self = (MainThreadEntry*)_userData;
//        return main(self->m_argc, self->m_argv);

        bgfx::Init init;
        init.type     = bgfx::RendererType::OpenGLES;
//        init.vendorId = BGFX_PCI_ID_NONE;
        init.resolution.width  = 960;
        init.resolution.height = 640;
        init.resolution.reset  = 0;
        bgfx::init(init);

//cjh        se::ScriptEngine* se = se::ScriptEngine::getInstance();
//        se->addRegisterCallback(setCanvasCallback);
//
//        if(!app->applicationDidFinishLaunching())
//            return -1;

        float r = 0;
        float g = 0;
        float b = 0;
        bool sub = false;

        std::chrono::steady_clock::time_point prevTime;
        std::chrono::steady_clock::time_point now;
        float dt = 0.f;

        while(true)
        {
            if (sub)
                r -= 0.01f;
            else
                r += 0.01f;

            if (r >= 1.0f)
            {
                sub = true;
                r = 1.0f;
            }
            else if (r < 0.0f)
            {
                sub = false;
                r = 0.0f;
            }

//cjh            app->_scheduler->update(dt);
//            EventDispatcher::dispatchTickEvent(dt);

            fakegl::glClearColor(r, g, b, 1);
            fakegl::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//            GLuint id = bgfx::createBuffer();
//            printf("bgfx::createBuffer returns: %u\n", id);
            bgfx::frame();

            PoolManager::getInstance()->getCurrentPool()->clear();

            now = std::chrono::steady_clock::now();
            dt = std::chrono::duration_cast<std::chrono::microseconds>(now - prevTime).count() / 1000000.f;
        }

        bgfx::shutdown();

        return 0;
    }
}

Application* Application::_instance = nullptr;

#define CAST_VIEW(view)    ((GLView*)view)

Application::Application(const std::string& name)
{
    Application::_instance = this;
    
    _scheduler = new Scheduler();
    
    createView(name);
    
    renderer::DeviceGraphics::setScaleFactor(CAST_VIEW(_view)->getScaleFactor());
    EventDispatcher::init();
    se::ScriptEngine::getInstance();
}

Application::~Application()
{
    // TODO: destroy DeviceGraphics
    EventDispatcher::destroy();
    se::ScriptEngine::destroyInstance();
    
    delete CAST_VIEW(_view);
    _view = nullptr;
    
    delete _scheduler;
    _scheduler = nullptr;
    
    Application::_instance = nullptr;
}

void Application::start()
{
    ccInvalidateStateCache();

    if (!_view)
        return;

    bx::Thread thread;
    thread.init(threadFunc, this);

    std::chrono::steady_clock::time_point prevTime;
    std::chrono::steady_clock::time_point now;
    float dt = 0.f;
    
    while (!CAST_VIEW(_view)->windowShouldClose())
    {
        prevTime = std::chrono::steady_clock::now();

        bgfx::renderFrame();
        
        CAST_VIEW(_view)->pollEvents();
//cjh        _scheduler->update(dt);
//        EventDispatcher::dispatchTickEvent(dt);
//
        CAST_VIEW(_view)->swapBuffers();
//        PoolManager::getInstance()->getCurrentPool()->clear();

        now = std::chrono::steady_clock::now();
        dt = std::chrono::duration_cast<std::chrono::microseconds>(now - prevTime).count() / 1000000.f;
    }
}

void Application::setAnimationInterval(float interval)
{
    _animationInterval = interval * 1000.0f;
}

Application::Platform Application::getPlatform() const
{
    return Platform::MAC;
}

std::string Application::getCurrentLanguageCode() const
{
    static char code[3]={0};
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];
    
    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];
    [languageCode getCString:code maxLength:3 encoding:NSASCIIStringEncoding];
    code[2]='\0';
    return code;
}

Application::LanguageType Application::getCurrentLanguage() const
{
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];
    
    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];
    
    if ([languageCode isEqualToString:@"zh"]) return LanguageType::CHINESE;
    if ([languageCode isEqualToString:@"en"]) return LanguageType::ENGLISH;
    if ([languageCode isEqualToString:@"fr"]) return LanguageType::FRENCH;
    if ([languageCode isEqualToString:@"it"]) return LanguageType::ITALIAN;
    if ([languageCode isEqualToString:@"de"]) return LanguageType::GERMAN;
    if ([languageCode isEqualToString:@"es"]) return LanguageType::SPANISH;
    if ([languageCode isEqualToString:@"nl"]) return LanguageType::DUTCH;
    if ([languageCode isEqualToString:@"ru"]) return LanguageType::RUSSIAN;
    if ([languageCode isEqualToString:@"ko"]) return LanguageType::KOREAN;
    if ([languageCode isEqualToString:@"ja"]) return LanguageType::JAPANESE;
    if ([languageCode isEqualToString:@"hu"]) return LanguageType::HUNGARIAN;
    if ([languageCode isEqualToString:@"pt"]) return LanguageType::PORTUGUESE;
    if ([languageCode isEqualToString:@"ar"]) return LanguageType::ARABIC;
    if ([languageCode isEqualToString:@"nb"]) return LanguageType::NORWEGIAN;
    if ([languageCode isEqualToString:@"pl"]) return LanguageType::POLISH;
    if ([languageCode isEqualToString:@"tr"]) return LanguageType::TURKISH;
    if ([languageCode isEqualToString:@"uk"]) return LanguageType::UKRAINIAN;
    if ([languageCode isEqualToString:@"ro"]) return LanguageType::ROMANIAN;
    if ([languageCode isEqualToString:@"bg"]) return LanguageType::BULGARIAN;
    return LanguageType::ENGLISH;

}

bool Application::openURL(const std::string &url)
{
    NSString* msg = [NSString stringWithCString:url.c_str() encoding:NSUTF8StringEncoding];
    NSURL* nsUrl = [NSURL URLWithString:msg];
    return [[NSWorkspace sharedWorkspace] openURL:nsUrl];
}

bool Application::applicationDidFinishLaunching()
{
    return true;
}

void Application::applicationDidEnterBackground()
{
}

void Application::applicationWillEnterForeground()
{
}

void Application::setMultitouch(bool)
{
}

void Application::onCreateView(int&x, int& y, int& width, int& height, PixelFormat& pixelformat, DepthFormat& depthFormat, int& multisamplingCount)
{
    x = 0;
    y = 0;
    width = 960;
    height = 640;
    
    pixelformat = PixelFormat::RGBA8;
    depthFormat = DepthFormat::DEPTH24_STENCIL8;

    multisamplingCount = 0;
}

void Application::createView(const std::string& name)
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int multisamplingCount = 0;
    PixelFormat pixelformat;
    DepthFormat depthFormat;
    
    onCreateView(x,
                 y,
                 width,
                 height,
                 pixelformat,
                 depthFormat,
                 multisamplingCount);

    _view = new GLView(this, name, x, y, width, height, pixelformat, depthFormat, multisamplingCount);
    
    g_width = width;
    g_height = height;
}

NS_CC_END
