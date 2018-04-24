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

#include "WebGLContext.h"

namespace bgfx {
    uint32_t WebGLContext::frame(bool _capture)
    {
//cjh        m_encoder[0].end(true);

#if BGFX_CONFIG_MULTITHREADED
        bx::MutexScope resourceApiScope(m_resourceApiLock);

//cjh        encoderApiWait();
        bx::MutexScope encoderApiScope(m_encoderApiLock);
#else
        encoderApiWait();
#endif // BGFX_CONFIG_MULTITHREADED

//cjh        m_submit->m_capture = _capture;

        BGFX_PROFILER_SCOPE("bgfx/API thread frame", 0xff2040ff);
        // wait for render thread to finish
        renderSemWait();
        frameNoRenderWait();

//cjh        m_encoder[0].begin(m_submit, 0);

        return m_frames;
    }

    void WebGLContext::frameNoRenderWait()
    {
        swap();

        // release render thread
        apiSemPost();
    }

    void WebGLContext::swap()
    {
//cjh        freeDynamicBuffers();
//cjh        m_submit->m_resolution = m_init.resolution;
//cjh        m_init.resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;
//cjh        m_submit->m_debug = m_debug;
//        m_submit->m_perfStats.numViews = 0;

//        bx::memCopy(m_submit->m_viewRemap, m_viewRemap, sizeof(m_viewRemap) );
//        bx::memCopy(m_submit->m_view, m_view, sizeof(m_view) );
//
//        if (m_colorPaletteDirty > 0)
//        {
//            --m_colorPaletteDirty;
//            bx::memCopy(m_submit->m_colorPalette, m_clearColor, sizeof(m_clearColor) );
//        }
//
//        freeAllHandles(m_submit);
//        m_submit->resetFreeHandles();

        m_submit->finish();

        bx::xchg(m_render, m_submit);

//cjh        bx::memCopy(m_render->m_occlusion, m_submit->m_occlusion, sizeof(m_submit->m_occlusion) );

        if (!BX_ENABLED(BGFX_CONFIG_MULTITHREADED)
            ||  m_singleThreaded)
        {
            renderFrame();
        }

        m_frames++;
        m_submit->start();

//cjh        bx::memSet(m_seq, 0, sizeof(m_seq) );

//cjh        m_submit->m_textVideoMem->resize(
//                                         m_render->m_textVideoMem->m_small
//                                         , m_init.resolution.width
//                                         , m_init.resolution.height
//                                         );

        int64_t now = bx::getHPCounter();
//cjh        m_submit->m_perfStats.cpuTimeFrame = now - m_frameTimeLast;
        m_frameTimeLast = now;
    }
} // namespace bgfx {
