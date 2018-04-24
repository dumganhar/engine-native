/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

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

#pragma once

#include "bx/platform.h"
#include "bx/thread.h"
#include "bx/timer.h"

#include "bgfx.h"
#include "bgfx_p.h"
#include "bgfx_platform.h"

#include "WebGLCommandBuffer.h"
#include "WebGLFrame.h"

namespace bgfx {

class WebGLRendererContext;

class WebGLContext
{
public:
    WebGLContext();
    ~WebGLContext();

    static int32_t renderThread(bx::Thread* /*_self*/, void* /*_userData*/)
    {
//cjh        BX_TRACE("render thread start");
//        BGFX_PROFILER_SET_CURRENT_THREAD_NAME("bgfx - Render Thread");
        while (RenderFrame::Exiting != bgfx::renderFrame() ) {};
//cjh        BX_TRACE("render thread exit");
        return bx::kExitSuccess;
    }

    BGFX_API_FUNC(uint32_t frame(bool _capture = false) );

    // game thread
    bool init(const Init& _init);
    void shutdown();

    CommandBuffer& getCommandBuffer(CommandBuffer::Enum _cmd)
    {
        CommandBuffer& cmdbuf = _cmd < CommandBuffer::End ? m_submit->m_cmdPre : m_submit->m_cmdPost;
        uint8_t cmd = (uint8_t)_cmd;
        cmdbuf.write(cmd);
        return cmdbuf;
    }

    void frameNoRenderWait();
    void swap();

    // render thread
    void flip();
    RenderFrame::Enum renderFrame(int32_t _msecs = -1);
    void rendererExecCommands(CommandBuffer& _cmdbuf);

#if BGFX_CONFIG_MULTITHREADED
    void apiSemPost()
    {
        if (!m_singleThreaded)
        {
            m_apiSem.post();
        }
    }

    bool apiSemWait(int32_t _msecs = -1)
    {
        if (m_singleThreaded)
        {
            return true;
        }

        BGFX_PROFILER_SCOPE("bgfx/API thread wait", 0xff2040ff);
        int64_t start = bx::getHPCounter();
        bool ok = m_apiSem.wait(_msecs);
        if (ok)
        {
            m_render->m_waitSubmit = bx::getHPCounter()-start;
//cjh            m_submit->m_perfStats.waitSubmit = m_submit->m_waitSubmit;
            return true;
        }

        return false;
    }

    void renderSemPost()
    {
        if (!m_singleThreaded)
        {
            m_renderSem.post();
        }
    }

    void renderSemWait()
    {
        if (!m_singleThreaded)
        {
            BGFX_PROFILER_SCOPE("bgfx/Render thread wait", 0xff2040ff);
            int64_t start = bx::getHPCounter();
            bool ok = m_renderSem.wait();
            BX_CHECK(ok, "Semaphore wait failed."); BX_UNUSED(ok);
            m_submit->m_waitRender = bx::getHPCounter() - start;
//cjh            m_submit->m_perfStats.waitRender = m_submit->m_waitRender;
        }
    }

//cjh    void encoderApiWait()
//    {
//        uint16_t numEncoders = m_encoderHandle->getNumHandles();
//
//        for (uint16_t ii = 1; ii < numEncoders; ++ii)
//        {
//            m_encoderEndSem.wait();
//        }
//
//        for (uint16_t ii = 0; ii < numEncoders; ++ii)
//        {
//            uint16_t idx = m_encoderHandle->getHandleAt(ii);
//            m_encoderStats[ii].cpuTimeBegin = m_encoder[idx].m_cpuTimeBegin;
//            m_encoderStats[ii].cpuTimeEnd   = m_encoder[idx].m_cpuTimeEnd;
//        }
//
//        m_submit->m_perfStats.numEncoders = uint8_t(numEncoders);
//
//        m_encoderHandle->reset();
//        uint16_t idx = m_encoderHandle->alloc();
//        BX_CHECK(0 == idx, "Internal encoder handle is not 0 (idx %d).", idx); BX_UNUSED(idx);
//    }

    bx::Semaphore m_renderSem;
    bx::Semaphore m_apiSem;
    bx::Semaphore m_encoderEndSem;
    bx::Mutex     m_encoderApiLock;
    bx::Mutex     m_resourceApiLock;
    bx::Thread    m_thread;
#else
    void apiSemPost()
    {
    }

    bool apiSemWait(int32_t _msecs = -1)
    {
        BX_UNUSED(_msecs);
        return true;
    }

    void renderSemPost()
    {
    }

    void renderSemWait()
    {
    }

    void encoderApiWait()
    {
        m_encoderStats[0].cpuTimeBegin = m_encoder[0].m_cpuTimeBegin;
        m_encoderStats[0].cpuTimeEnd   = m_encoder[0].m_cpuTimeEnd;
        m_submit->m_perfStats.numEncoders = 1;
    }
#endif // BGFX_CONFIG_MULTITHREADED

    Frame  m_frame[1+(BGFX_CONFIG_MULTITHREADED ? 1 : 0)];
    Frame* m_render;
    Frame* m_submit;

    WebGLRendererContext* m_renderCtx;

    Init     m_init;
    int64_t  m_frameTimeLast;
    uint32_t m_frames;
    uint32_t m_debug;
    
    bool m_rendererInitialized;
    bool m_exit;
    bool m_flipAfterRender;
    bool m_singleThreaded;
    bool m_flipped;
};

} // namespace bgfx {
