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
#include "WebGLCommandBuffer.h"
#include "WebGLRenderContext.h"

#include <unistd.h>

#define BGFX_DEBUG_NONE                  UINT32_C(0x00000000) //!< No debug. //cjh

#define BGFX_API_THREAD_MAGIC UINT32_C(0x78666762)

namespace bgfx {

    extern bool s_renderFrameCalled;

    WebGLContext* WebGLContext::s_ctx = nullptr;

    WebGLContext::WebGLContext()
    : m_render(&m_frame[0])
    , m_submit(&m_frame[BGFX_CONFIG_MULTITHREADED ? 1 : 0])
//cjh    , m_numFreeDynamicIndexBufferHandles(0)
//    , m_numFreeDynamicVertexBufferHandles(0)
//    , m_numFreeOcclusionQueryHandles(0)
//    , m_colorPaletteDirty(0)
    , m_frames(0)
//cjh    , m_debug(BGFX_DEBUG_NONE)
//    , m_rtMemoryUsed(0)
//    , m_textureMemoryUsed(0)
    , m_renderCtx(NULL)
    , m_rendererInitialized(false)
    , m_exit(false)
    , m_flipAfterRender(false)
    , m_singleThreaded(false)
    {

    }

    WebGLContext::~WebGLContext()
    {

    }

    bool WebGLContext::init(const Init& _init)
    {
        BX_CHECK(!m_rendererInitialized, "Already initialized?");

        m_init = _init;
        m_init.resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;

        m_exit    = false;
        m_flipped = true;
        m_frames  = 0;
        m_debug   = BGFX_DEBUG_NONE;
        m_frameTimeLast = bx::getHPCounter();

        m_submit->create();

#if BGFX_CONFIG_MULTITHREADED
        m_render->create();

        if (s_renderFrameCalled)
        {
            // When bgfx::renderFrame is called before init render thread
            // should not be created.
            BX_TRACE("Application called bgfx::renderFrame directly, not creating render thread.");
            m_singleThreaded = true
//cjh            && ~BGFX_API_THREAD_MAGIC == s_threadIndex
            ;
        }
        else
        {
            BX_TRACE("Creating rendering thread.");
//cjh            m_thread.init(renderThread, this, 0, "bgfx - renderer backend thread");
            m_singleThreaded = false;
        }
#else
        BX_TRACE("Multithreaded renderer is disabled.");
        m_singleThreaded = true;
#endif // BGFX_CONFIG_MULTITHREADED

        BX_TRACE("Running in %s-threaded mode", m_singleThreaded ? "single" : "multi");

//cjh        s_threadIndex = BGFX_API_THREAD_MAGIC;

//cjh        for (uint32_t ii = 0; ii < BX_COUNTOF(m_viewRemap); ++ii)
//        {
//            m_viewRemap[ii] = ViewId(ii);
//        }
//
//        for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
//        {
//            resetView(ViewId(ii) );
//        }
//
//        for (uint32_t ii = 0; ii < BX_COUNTOF(m_clearColor); ++ii)
//        {
//            m_clearColor[ii][0] = 0.0f;
//            m_clearColor[ii][1] = 0.0f;
//            m_clearColor[ii][2] = 0.0f;
//            m_clearColor[ii][3] = 1.0f;
//        }
//
//        m_declRef.init();

        CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::RendererInit);
        cmdbuf.write(_init);

        frameNoRenderWait();

//cjh        m_encoderHandle = bx::createHandleAlloc(g_allocator, _init.limits.maxEncoders);
//        m_encoder       = (EncoderImpl*)BX_ALLOC(g_allocator, sizeof(EncoderImpl)*_init.limits.maxEncoders);
//        m_encoderStats  = (EncoderStats*)BX_ALLOC(g_allocator, sizeof(EncoderStats)*_init.limits.maxEncoders);
//        for (uint32_t ii = 0, num = _init.limits.maxEncoders; ii < num; ++ii)
//        {
//            BX_PLACEMENT_NEW(&m_encoder[ii], EncoderImpl);
//        }
//
//        uint16_t idx = m_encoderHandle->alloc();
//        BX_CHECK(0 == idx, "Internal encoder handle is not 0 (idx %d).", idx); BX_UNUSED(idx);
//        m_encoder[0].begin(m_submit, 0);
//        m_encoder0 = reinterpret_cast<Encoder*>(&m_encoder[0]);

        // Make sure renderer init is called from render thread.
        // g_caps is initialized and available after this point.
        frame();

        if (!m_rendererInitialized)
        {
            getCommandBuffer(CommandBuffer::RendererShutdownEnd);
            frame();
            frame();
//cjh            m_declRef.shutdown(m_vertexDeclHandle);
            m_submit->destroy();
#if BGFX_CONFIG_MULTITHREADED
            m_render->destroy();
#endif // BGFX_CONFIG_MULTITHREADED
            return false;
        }

//        for (uint32_t ii = 0; ii < BX_COUNTOF(s_emulatedFormats); ++ii)
//        {
//            const uint32_t fmt = s_emulatedFormats[ii];
//            g_caps.formats[fmt] |= 0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_2D  ) ? BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED   : 0;
//            g_caps.formats[fmt] |= 0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_3D  ) ? BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED   : 0;
//            g_caps.formats[fmt] |= 0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_CUBE) ? BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED : 0;
//        }
//
//        for (uint32_t ii = 0; ii < TextureFormat::UnknownDepth; ++ii)
//        {
//            bool convertable = bimg::imageConvert(bimg::TextureFormat::BGRA8, bimg::TextureFormat::Enum(ii) );
//            g_caps.formats[ii] |= 0 == (g_caps.formats[ii] & BGFX_CAPS_FORMAT_TEXTURE_2D  ) && convertable ? BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED   : 0;
//            g_caps.formats[ii] |= 0 == (g_caps.formats[ii] & BGFX_CAPS_FORMAT_TEXTURE_3D  ) && convertable ? BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED   : 0;
//            g_caps.formats[ii] |= 0 == (g_caps.formats[ii] & BGFX_CAPS_FORMAT_TEXTURE_CUBE) && convertable ? BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED : 0;
//        }
//
//        g_caps.rendererType = m_renderCtx->getRendererType();
//        initAttribTypeSizeTable(g_caps.rendererType);
//
//        g_caps.supported |= 0
//        | (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) && !m_singleThreaded ? BGFX_CAPS_RENDERER_MULTITHREADED : 0)
//        | (isGraphicsDebuggerPresent() ? BGFX_CAPS_GRAPHICS_DEBUGGER : 0)
//        ;
//
//        dumpCaps();
//
//        m_textVideoMemBlitter.init();
//        m_clearQuad.init();
//
//        m_submit->m_transientVb = createTransientVertexBuffer(_init.limits.transientVbSize);
//        m_submit->m_transientIb = createTransientIndexBuffer(_init.limits.transientIbSize);
        frame();

        if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
        {
//cjh            m_submit->m_transientVb = createTransientVertexBuffer(_init.limits.transientVbSize);
//            m_submit->m_transientIb = createTransientIndexBuffer(_init.limits.transientIbSize);
            frame();
        }

//cjh        g_internalData.caps = getCaps();

        return true;
    }

    void WebGLContext::shutdown()
    {
        getCommandBuffer(CommandBuffer::RendererShutdownBegin);
        frame();

//cjh        destroyTransientVertexBuffer(m_submit->m_transientVb);
//        destroyTransientIndexBuffer(m_submit->m_transientIb);
//        m_textVideoMemBlitter.shutdown();
//        m_clearQuad.shutdown();
        frame();

        if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
        {
//cjh            destroyTransientVertexBuffer(m_submit->m_transientVb);
//            destroyTransientIndexBuffer(m_submit->m_transientIb);
            frame();
        }

        frame(); // If any VertexDecls needs to be destroyed.

        getCommandBuffer(CommandBuffer::RendererShutdownEnd);
        frame();

//cjh        m_encoder[0].end(true);
//        m_encoderHandle->free(0);
//        bx::destroyHandleAlloc(g_allocator, m_encoderHandle);
//        m_encoderHandle = NULL;
//
//        for (uint32_t ii = 0, num = g_caps.limits.maxEncoders; ii < num; ++ii)
//        {
//            m_encoder[ii].~EncoderImpl();
//        }
//        BX_FREE(g_allocator, m_encoder);
//        BX_FREE(g_allocator, m_encoderStats);
//
//        m_dynVertexBufferAllocator.compact();
//        m_dynIndexBufferAllocator.compact();
//
//        BX_CHECK(m_vertexDeclHandle.getNumHandles() == m_declRef.m_vertexDeclMap.getNumElements()
//                , "VertexDeclRef mismatch, num handles %d, handles in hash map %d."
//                , m_vertexDeclHandle.getNumHandles()
//                , m_declRef.m_vertexDeclMap.getNumElements()
//                );
//
//        m_declRef.shutdown(m_vertexDeclHandle);

#if BGFX_CONFIG_MULTITHREADED
        // Render thread shutdown sequence.
        renderSemWait(); // Wait for previous frame.
        apiSemPost();   // OK to set context to NULL.
        // s_ctx is NULL here.
        renderSemWait(); // In RenderFrame::Exiting state.

        if (m_thread.isRunning() )
        {
            m_thread.shutdown();
        }

        m_render->destroy();
#endif // BGFX_CONFIG_MULTITHREADED

//cjh        bx::memSet(&g_internalData, 0, sizeof(InternalData) );
        s_ctx = NULL;

        m_submit->destroy();

//cjh        if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
//        {
//#define CHECK_HANDLE_LEAK(_handleAlloc)                                                               \
//                    BX_MACRO_BLOCK_BEGIN                                                              \
//                        if (0 != _handleAlloc.getNumHandles() )                                       \
//                        {                                                                             \
//                            BX_TRACE("LEAK: " #_handleAlloc " %d (max: %d)"                           \
//                                , _handleAlloc.getNumHandles()                                        \
//                                , _handleAlloc.getMaxHandles()                                        \
//                                );                                                                    \
//                            for (uint16_t ii = 0, num = _handleAlloc.getNumHandles(); ii < num; ++ii) \
//                            {                                                                         \
//                                BX_TRACE("\t%3d: %4d", ii, _handleAlloc.getHandleAt(ii) );            \
//                            }                                                                         \
//                        }                                                                             \
//                    BX_MACRO_BLOCK_END
//
//#define CHECK_HANDLE_LEAK_NAME(_handleAlloc, _type, _ref)                                             \
//                    BX_MACRO_BLOCK_BEGIN                                                              \
//                        if (0 != _handleAlloc.getNumHandles() )                                       \
//                        {                                                                             \
//                            BX_TRACE("LEAK: " #_handleAlloc " %d (max: %d)"                           \
//                                , _handleAlloc.getNumHandles()                                        \
//                                , _handleAlloc.getMaxHandles()                                        \
//                                );                                                                    \
//                            for (uint16_t ii = 0, num = _handleAlloc.getNumHandles(); ii < num; ++ii) \
//                            {                                                                         \
//                                uint16_t idx = _handleAlloc.getHandleAt(ii);                          \
//                                const _type& ref = _ref[idx]; BX_UNUSED(ref);                         \
//                                BX_TRACE("\t%3d: %4d %s (count %d)"                                   \
//                                        , ii                                                          \
//                                        , idx                                                         \
//                                        , ref.m_name.getPtr()                                         \
//                                        , ref.m_refCount                                              \
//                                        );                                                            \
//                            }                                                                         \
//                        }                                                                             \
//                    BX_MACRO_BLOCK_END
//
//            CHECK_HANDLE_LEAK     (m_dynamicIndexBufferHandle                          );
//            CHECK_HANDLE_LEAK     (m_dynamicVertexBufferHandle                         );
//            CHECK_HANDLE_LEAK     (m_indexBufferHandle                                 );
//            CHECK_HANDLE_LEAK     (m_vertexDeclHandle                                  );
//            CHECK_HANDLE_LEAK     (m_vertexBufferHandle                                );
//            CHECK_HANDLE_LEAK_NAME(m_shaderHandle,             ShaderRef,  m_shaderRef );
//            CHECK_HANDLE_LEAK     (m_programHandle                                     );
//            CHECK_HANDLE_LEAK_NAME(m_textureHandle,            TextureRef, m_textureRef);
//            CHECK_HANDLE_LEAK     (m_frameBufferHandle                                 );
//            CHECK_HANDLE_LEAK_NAME(m_uniformHandle,            UniformRef, m_uniformRef);
//            CHECK_HANDLE_LEAK     (m_occlusionQueryHandle                              );
//#undef CHECK_HANDLE_LEAK
//#undef CHECK_HANDLE_LEAK_NAME
//        }
    }

    void WebGLContext::clear(GLbitfield mask)
    {
        BGFX_MUTEX_SCOPE(m_resourceApiLock);
        CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::clear);
        cmdbuf.write(mask);
    }

    void WebGLContext::clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {
        BGFX_MUTEX_SCOPE(m_resourceApiLock);
        CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::clearColor);
        cmdbuf.write(red);
        cmdbuf.write(green);
        cmdbuf.write(blue);
        cmdbuf.write(alpha);
    }

    GLuint WebGLContext::createBuffer()
    {
        BGFX_MUTEX_SCOPE(m_resourceApiLock);
        getCommandBuffer(CommandBuffer::createBuffer);
        GLuint id = 0;

        return id;
    }

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

    WebGLRenderContext* rendererCreate(const Init& _init)
    {
        WebGLRenderContext* renderCtx = new WebGLRenderContext();
        return renderCtx;
    }

    void rendererDestroy(WebGLRenderContext* _renderCtx)
    {
        if (NULL != _renderCtx)
        {
            delete _renderCtx;
//            s_rendererCreator[_renderCtx->getRendererType()].destroyFn();
        }
    }

    void WebGLContext::rendererExecCommands(CommandBuffer& _cmdbuf)
    {
        _cmdbuf.reset();

        bool end = false;

        if (NULL == m_renderCtx)
        {
            uint8_t command;
            _cmdbuf.read(command);

            switch (command)
            {
                case CommandBuffer::RendererShutdownEnd:
                    m_exit = true;
                    return;

                case CommandBuffer::End:
                    return;

                default:
                {
                    BX_CHECK(CommandBuffer::RendererInit == command
                             , "RendererInit must be the first command in command buffer before initialization. Unexpected command %d?"
                             , command
                             );
                    BX_CHECK(!m_rendererInitialized, "This shouldn't happen! Bad synchronization?");

                    Init init;
                    _cmdbuf.read(init);

                    m_renderCtx = rendererCreate(init);

                    m_rendererInitialized = NULL != m_renderCtx;

                    if (!m_rendererInitialized)
                    {
                        _cmdbuf.read(command);
                        BX_CHECK(CommandBuffer::End == command, "Unexpected command %d?"
                                 , command
                                 );
                        return;
                    }
                }
                    break;
            }
        }

        do
        {
            uint8_t command;
            _cmdbuf.read(command);

            switch (command)
            {
                case CommandBuffer::clear:
                {
                    GLbitfield mask;
                    _cmdbuf.read(mask);
                    m_renderCtx->clear(mask);
                }
                    break;

                case CommandBuffer::clearColor:
                {
                    GLclampf red, green, blue, alpha;
                    _cmdbuf.read(red);
                    _cmdbuf.read(green);
                    _cmdbuf.read(blue);
                    _cmdbuf.read(alpha);
                    m_renderCtx->clearColor(red, green, blue, alpha);
                }
                    break;

                case CommandBuffer::createBuffer:
                {
                    usleep(2000 * 1000);
                }
                    break;

                case CommandBuffer::RendererShutdownBegin:
                {
                    BX_CHECK(m_rendererInitialized, "This shouldn't happen! Bad synchronization?");
                    m_rendererInitialized = false;
                }
                    break;

                case CommandBuffer::RendererShutdownEnd:
                {
                    BX_CHECK(!m_rendererInitialized && !m_exit, "This shouldn't happen! Bad synchronization?");

                    rendererDestroy(m_renderCtx);
                    m_renderCtx = NULL;

                    m_exit = true;
                }
                    BX_FALLTHROUGH;

                case CommandBuffer::End:
                    end = true;
                    break;

                default:
                    break;
            }


        } while (!end);
    }

    void WebGLContext::flip()
    {
        if (m_rendererInitialized
            && !m_flipped)
        {
            m_renderCtx->flip();
            m_flipped = true;

            if (m_renderCtx->isDeviceRemoved() )
            {
                // Something horribly went wrong, fallback to noop renderer.
                rendererDestroy(m_renderCtx);

                Init init;
                init.type = RendererType::Noop;
                m_renderCtx = rendererCreate(init);
//cjh                g_caps.rendererType = RendererType::Noop;
            }
        }
    }

    RenderFrame::Enum WebGLContext::renderFrame(int32_t _msecs)
    {
        BGFX_PROFILER_SCOPE("bgfx::renderFrame", 0xff2040ff);

        if (!m_flipAfterRender)
        {
            BGFX_PROFILER_SCOPE("bgfx/flip", 0xff2040ff);
            flip();
        }

        if (apiSemWait(_msecs) )
        {
            {
                BGFX_PROFILER_SCOPE("bgfx/Exec commands pre", 0xff2040ff);
                rendererExecCommands(m_render->m_cmdPre);
            }

            if (m_rendererInitialized)
            {
                BGFX_PROFILER_SCOPE("bgfx/Render submit", 0xff2040ff);
//cjh                m_renderCtx->submit(m_render, m_clearQuad, m_textVideoMemBlitter);
                m_flipped = false;
            }

            {
                BGFX_PROFILER_SCOPE("bgfx/Exec commands post", 0xff2040ff);
                rendererExecCommands(m_render->m_cmdPost);
            }

            renderSemPost();

            if (m_flipAfterRender)
            {
                BGFX_PROFILER_SCOPE("bgfx/flip", 0xff2040ff);
                flip();
            }
        }
        else
        {
            return RenderFrame::Timeout;
        }

        return m_exit
        ? RenderFrame::Exiting
        : RenderFrame::Render
        ;
    }

} // namespace bgfx {
