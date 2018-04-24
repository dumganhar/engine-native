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

#include "WebGLCommandBuffer.h"

namespace bgfx {

class Frame
{
public:
    Frame()
    : m_waitSubmit(0)
    , m_waitRender(0)
    {
    }

    ~Frame()
    {
    }

    void create()
    {
        reset();
        start();
    }

    void destroy()
    {
    }

    void reset()
    {
        start();
        finish();
//        resetFreeHandles();
    }

    void start()
    {
//        m_perfStats.transientVbUsed = m_vboffset;
//        m_perfStats.transientIbUsed = m_iboffset;
//
//        m_frameCache.reset();
//        m_numRenderItems = 0;
//        m_numBlitItems   = 0;
//        m_iboffset = 0;
//        m_vboffset = 0;
        m_cmdPre.start();
        m_cmdPost.start();
//        m_capture = false;
    }

    void finish()
    {
        m_cmdPre.finish();
        m_cmdPost.finish();

        //            if (0 < m_numDropped)
        //            {
        //                BX_TRACE("Too many draw calls: %d, dropped %d (max: %d)"
        //                    , m_numRenderItems+m_numDropped
        //                    , m_numDropped
        //                    , BGFX_CONFIG_MAX_DRAW_CALLS
        //                    );
        //            }
    }

private:
    CommandBuffer m_cmdPre;
    CommandBuffer m_cmdPost;

    int64_t m_waitSubmit;
    int64_t m_waitRender;

    friend class WebGLContext;
};

} // namespace bgfx {
