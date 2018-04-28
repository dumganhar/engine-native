#include "FakeGL.h"
#include "WebGLCommandBuffer.h"
#include "WebGLRenderContext.h"
#include "WebGLFrame.h"

#include "bx/platform.h"
#include "bx/thread.h"
#include "bx/timer.h"

#include "bgfx.h"
#include "bgfx_p.h"
#include "bgfx_platform.h"

#include <unistd.h>

#define BGFX_DEBUG_NONE                  UINT32_C(0x00000000) //!< No debug. //cjh
#define BGFX_API_THREAD_MAGIC UINT32_C(0x78666762)

namespace bgfx {
    extern bool s_renderFrameCalled;
}

using namespace bgfx;

namespace {
    std::string __strSyncCommandReturn;
    GLint __intSyncCommandReturn[256];
    float __floatSyncCommandReturn[256];

    Frame  m_frame[1+(BGFX_CONFIG_MULTITHREADED ? 1 : 0)];
    Frame* m_render;
    Frame* m_submit;

    WebGLRenderContext* m_renderCtx;

    Init     m_init;
    int64_t  m_frameTimeLast = 0;
    uint32_t m_frames = 0;
    uint32_t m_debug = 0;

    bool _isGLContextInitialized = false;
    bool m_rendererInitialized = false;
    bool m_exit = false;
    bool m_flipAfterRender = false;
    bool m_singleThreaded = false;
    bool m_flipped = false;

#if BGFX_CONFIG_MULTITHREADED
    bx::Semaphore m_renderSem;
    bx::Semaphore m_apiSem;
    bx::Semaphore m_encoderEndSem;
    bx::Mutex     m_encoderApiLock;
    bx::Mutex     m_resourceApiLock;
    bx::Thread    m_thread;
#endif
}

namespace fakegl {

    static int32_t renderThread(bx::Thread* /*_self*/, void* /*_userData*/)
    {
        //cjh        BX_TRACE("render thread start");
        //        BGFX_PROFILER_SET_CURRENT_THREAD_NAME("bgfx - Render Thread");
        while (RenderFrame::Exiting != bgfx::renderFrame() ) {};
        //cjh        BX_TRACE("render thread exit");
        return bx::kExitSuccess;
    }

    uint32_t frame(bool _capture = false);

    CommandBuffer& getCommandBuffer(CommandBuffer::Enum _cmd)
    {
        CommandBuffer& cmdbuf = _cmd < CommandBuffer::End ? m_submit->m_cmdPre : m_submit->m_cmdPost;
        uint8_t cmd = (uint8_t)_cmd;
        cmdbuf.write(cmd);
        return cmdbuf;
    }

    void reset(uint32_t _width, uint32_t _height, uint32_t _flags)
    {
        //cjh        BX_WARN(g_caps.limits.maxTextureSize >= _width
        //                &&  g_caps.limits.maxTextureSize >= _height
        //                , "Frame buffer resolution width or height can't be larger than limits.maxTextureSize %d (width %d, height %d)."
        //                , g_caps.limits.maxTextureSize
        //                , _width
        //                , _height
        //                );
        //        m_init.resolution.width  = bx::clamp(_width,  1u, g_caps.limits.maxTextureSize);
        //        m_init.resolution.height = bx::clamp(_height, 1u, g_caps.limits.maxTextureSize);
        //        m_init.resolution.reset  = 0
        //        | _flags
        //        | (g_platformDataChangedSinceReset ? BGFX_RESET_INTERNAL_FORCE : 0)
        //        ;
        //        g_platformDataChangedSinceReset = false;
        //
        //        m_flipAfterRender = !!(_flags & BGFX_RESET_FLIP_AFTER_RENDER);
        //
        //        for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
        //        {
        //            m_view[ii].setFrameBuffer(BGFX_INVALID_HANDLE);
        //        }
        //
        //        for (uint16_t ii = 0, num = m_textureHandle.getNumHandles(); ii < num; ++ii)
        //        {
        //            uint16_t textureIdx = m_textureHandle.getHandleAt(ii);
        //            const TextureRef& textureRef = m_textureRef[textureIdx];
        //            if (BackbufferRatio::Count != textureRef.m_bbRatio)
        //            {
        //                TextureHandle handle = { textureIdx };
        //                resizeTexture(handle
        //                              , uint16_t(m_init.resolution.width)
        //                              , uint16_t(m_init.resolution.height)
        //                              , textureRef.m_numMips
        //                              );
        //                m_init.resolution.reset |= BGFX_RESET_INTERNAL_FORCE;
        //            }
        //        }
    }

#if BGFX_CONFIG_MULTITHREADED
    void apiSemPost()
    {
        if (!m_singleThreaded)
        {
            m_apiSem.post();
        }
    }

    bool apiSemWait(int32_t _msecs/* = -1*/)
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
#else
    void apiSemPost()
    {
    }

    bool apiSemWait(int32_t _msecs/* = -1*/)
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

    bool isInited()
    {
        return _isGLContextInitialized;
    }

    bool init(const Init& _init)
    {
        BX_CHECK(!m_rendererInitialized, "Already initialized?");

        _isGLContextInitialized = true;

        m_render = &m_frame[0];
        m_submit = &m_frame[BGFX_CONFIG_MULTITHREADED ? 1 : 0];
        m_frames = 0;
        m_renderCtx = NULL;
        m_rendererInitialized = false;
        m_exit = false;
        m_flipAfterRender = false;
        m_singleThreaded = false;

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
//cjh            m_singleThreaded = true
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

    void shutdown()
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
            frame();
        }

        frame(); // If any VertexDecls needs to be destroyed.

        getCommandBuffer(CommandBuffer::RendererShutdownEnd);
        frame();

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

        m_submit->destroy();
        _isGLContextInitialized = false;
    }

    uint32_t frame(bool _capture)
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

    void frameNoRenderWait()
    {
        swap();

        // release render thread
        apiSemPost();
    }

    void swap()
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

    void rendererExecCommands(CommandBuffer& _cmdbuf)
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
                case CommandBuffer::activeTexture:
                {
                    GLenum texture;
                    _cmdbuf.read(texture);
                    m_renderCtx->activeTexture(texture);
                }
                    break;

                case CommandBuffer::attachShader:
                {
                    GLuint program;
                    GLuint shader;
                    _cmdbuf.read(program);
                    _cmdbuf.read(shader);
                    m_renderCtx->attachShader(program, shader);
                }
                    break;

                case CommandBuffer::bindAttribLocation:
                {
                    GLuint program;
                    GLuint index;
                    Memory* m;
                    _cmdbuf.read(program);
                    _cmdbuf.read(index);
                    _cmdbuf.read(m);
                    const GLchar* name = (const GLchar*)m->data;
                    m_renderCtx->bindAttribLocation(program, index, name);
                    release(m);
                }
                    break;

                case CommandBuffer::bindBuffer:
                {
                    GLenum target;
                    GLuint buffer;
                    _cmdbuf.read(target);
                    _cmdbuf.read(buffer);
                    m_renderCtx->bindBuffer(target, buffer);
                }
                    break;

                case CommandBuffer::bindFramebuffer:
                {
                    GLenum target;
                    GLuint framebuffer;
                    _cmdbuf.read(target);
                    _cmdbuf.read(framebuffer);
                    m_renderCtx->bindFramebuffer(target, framebuffer);
                }
                    break;

                case CommandBuffer::bindRenderbuffer:
                {
                    GLenum target;
                    GLuint renderbuffer;
                    _cmdbuf.read(target);
                    _cmdbuf.read(renderbuffer);
                    m_renderCtx->bindRenderbuffer(target, renderbuffer);
                }
                    break;

                case CommandBuffer::bindTexture:
                {
                    GLenum target;
                    GLuint texture;
                    _cmdbuf.read(target);
                    _cmdbuf.read(texture);
                    m_renderCtx->bindTexture(target, texture);
                }
                    break;

                case CommandBuffer::blendColor:
                {
                    GLfloat red, green, blue, alpha;
                    _cmdbuf.read(red);
                    _cmdbuf.read(green);
                    _cmdbuf.read(blue);
                    _cmdbuf.read(alpha);
                    m_renderCtx->blendColor(red, green, blue, alpha);
                }
                    break;

                case CommandBuffer::blendEquation:
                {
                    GLenum mode;
                    _cmdbuf.read(mode);
                    m_renderCtx->blendEquation(mode);
                }
                    break;

                case CommandBuffer::blendEquationSeparate:
                {
                    GLenum modeRGB, modeAlpha;
                    _cmdbuf.read(modeRGB);
                    _cmdbuf.read(modeAlpha);
                    m_renderCtx->blendEquationSeparate(modeRGB, modeAlpha);
                }
                    break;

                case CommandBuffer::blendFunc:
                {
                    GLenum sfactor;
                    GLenum dfactor;
                    _cmdbuf.read(sfactor);
                    _cmdbuf.read(dfactor);
                    m_renderCtx->blendFunc(sfactor, dfactor);
                }
                    break;

                case CommandBuffer::blendFuncSeparate:
                {
                    GLenum srcRGB, dstRGB, srcAlpha, dstAlpha;
                    _cmdbuf.read(srcRGB);
                    _cmdbuf.read(dstRGB);
                    _cmdbuf.read(srcAlpha);
                    _cmdbuf.read(dstAlpha);
                    m_renderCtx->blendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
                }
                    break;

                case CommandBuffer::bufferData:
                {
                    GLenum target;
                    const Memory* memory;
                    GLenum usage;
                    _cmdbuf.read(target);
                    _cmdbuf.read(memory);
                    _cmdbuf.read(usage);
                    m_renderCtx->bufferData(target, memory->size, memory->data, usage);
                    release(memory);
                }
                    break;

                case CommandBuffer::bufferSubData:
                {
                    GLenum target;
                    GLintptr offset;
                    const Memory* memory;
                    _cmdbuf.read(target);
                    _cmdbuf.read(offset);
                    _cmdbuf.read(memory);
                    m_renderCtx->bufferSubData(target, offset, memory->size, memory->data);
                    release(memory);
                }
                    break;

                case CommandBuffer::checkFramebufferStatus:
                {
                    GLenum target;
                    _cmdbuf.read(target);
                    GLenum status = m_renderCtx->checkFramebufferStatus(target);
                    __intSyncCommandReturn[0] = status;
                }
                    break;

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

                case CommandBuffer::clearDepthf:
                {
                    GLclampf depth;
                    _cmdbuf.read(depth);
                    m_renderCtx->clearDepthf(depth);
                }
                    break;

                case CommandBuffer::clearStencil:
                {
                    GLint s;
                    _cmdbuf.read(s);
                    m_renderCtx->clearStencil(s);
                }
                    break;

                case CommandBuffer::colorMask:
                {
                    GLboolean red, green, blue, alpha;
                    _cmdbuf.read(red);
                    _cmdbuf.read(green);
                    _cmdbuf.read(blue);
                    _cmdbuf.read(alpha);
                    m_renderCtx->colorMask(red, green, blue, alpha);
                }
                    break;

                case CommandBuffer::compileShader:
                {
                    GLuint shader;
                    _cmdbuf.read(shader);
                    m_renderCtx->compileShader(shader);
                }
                    break;

                case CommandBuffer::compressedTexImage2D:
                {
                    GLenum target;
                    GLint level;
                    GLenum internalformat;
                    GLsizei width;
                    GLsizei height;
                    GLint border;
                    Memory* memory;
                    _cmdbuf.read(target);
                    _cmdbuf.read(level);
                    _cmdbuf.read(internalformat);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    _cmdbuf.read(border);
                    _cmdbuf.read(memory);
                    m_renderCtx->compressedTexImage2D(target, level, internalformat, width, height, border, memory->size, memory->data);
                    release(memory);
                }
                    break;

                case CommandBuffer::compressedTexSubImage2D:
                {
                    GLenum target;
                    GLint level;
                    GLint xoffset;
                    GLint yoffset;
                    GLsizei width;
                    GLsizei height;
                    GLenum format;
                    Memory* memory;
                    _cmdbuf.read(target);
                    _cmdbuf.read(level);
                    _cmdbuf.read(xoffset);
                    _cmdbuf.read(yoffset);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    _cmdbuf.read(format);
                    _cmdbuf.read(memory);
                    m_renderCtx->compressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, memory->size, memory->data);
                    release(memory);
                }
                    break;

                case CommandBuffer::copyTexImage2D:
                {
                    GLenum target;
                    GLint level;
                    GLenum internalformat;
                    GLint x;
                    GLint y;
                    GLsizei width;
                    GLsizei height;
                    GLint border;
                    _cmdbuf.read(target);
                    _cmdbuf.read(level);
                    _cmdbuf.read(internalformat);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    _cmdbuf.read(border);
                    m_renderCtx->copyTexImage2D(target, level, internalformat, x, y, width, height, border);
                }
                    break;

                case CommandBuffer::copyTexSubImage2D:
                {
                    GLenum target;
                    GLint level;
                    GLint xoffset;
                    GLint yoffset;
                    GLint x;
                    GLint y;
                    GLsizei width;
                    GLsizei height;
                    _cmdbuf.read(target);
                    _cmdbuf.read(level);
                    _cmdbuf.read(xoffset);
                    _cmdbuf.read(yoffset);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    m_renderCtx->copyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
                }
                    break;

                case CommandBuffer::createProgram:
                {
                    GLuint id = m_renderCtx->createProgram();
                    __intSyncCommandReturn[0] = id;
                }
                    break;

                case CommandBuffer::createShader:
                {
                    GLenum type;
                    _cmdbuf.read(type);
                    GLuint id = m_renderCtx->createShader(type);
                    __intSyncCommandReturn[0] = id;
                }
                    break;

                case CommandBuffer::cullFace:
                {
                    GLenum mode;
                    _cmdbuf.read(mode);
                    m_renderCtx->cullFace(mode);
                }
                    break;

                case CommandBuffer::deleteBuffers:
                {
                    GLsizei n;
                    const Memory* buffers;
                    _cmdbuf.read(n);
                    _cmdbuf.read(buffers);
                    m_renderCtx->deleteBuffers(n, (const GLuint*)buffers->data);
                    release(buffers);
                }
                    break;

                case CommandBuffer::deleteFramebuffers:
                {
                    GLsizei n;
                    const Memory* buffers;
                    _cmdbuf.read(n);
                    _cmdbuf.read(buffers);
                    m_renderCtx->deleteFramebuffers(n, (const GLuint*)buffers->data);
                    release(buffers);
                }
                    break;

                case CommandBuffer::deleteProgram:
                {
                    GLuint program;
                    _cmdbuf.read(program);
                    m_renderCtx->deleteProgram(program);
                }
                    break;

                case CommandBuffer::deleteRenderbuffers:
                {
                    GLsizei n;
                    const Memory* buffers;
                    _cmdbuf.read(n);
                    _cmdbuf.read(buffers);
                    m_renderCtx->deleteRenderbuffers(n, (const GLuint*)buffers->data);
                    release(buffers);
                }
                    break;

                case CommandBuffer::deleteShader:
                {
                    GLuint shader;
                    _cmdbuf.read(shader);
                    m_renderCtx->deleteShader(shader);
                }
                    break;

                case CommandBuffer::deleteTextures:
                {
                    GLsizei n;
                    const Memory* buffers;
                    _cmdbuf.read(n);
                    _cmdbuf.read(buffers);
                    m_renderCtx->deleteTextures(n, (const GLuint*)buffers->data);
                    release(buffers);
                }
                    break;

                case CommandBuffer::depthFunc:
                {
                    GLenum func;
                    _cmdbuf.read(func);
                    m_renderCtx->depthFunc(func);
                }
                    break;

                case CommandBuffer::depthMask:
                {
                    GLboolean flag;
                    _cmdbuf.read(flag);
                    m_renderCtx->depthMask(flag);
                }
                    break;

                case CommandBuffer::depthRangef:
                {
                    GLclampf zNear;
                    GLclampf zFar;
                    _cmdbuf.read(zNear);
                    _cmdbuf.read(zFar);
                    m_renderCtx->depthRangef(zNear, zFar);
                }
                    break;

                case CommandBuffer::detachShader:
                {
                    GLuint program;
                    GLuint shader;
                    _cmdbuf.read(program);
                    _cmdbuf.read(shader);
                    m_renderCtx->detachShader(program, shader);
                }
                    break;

                case CommandBuffer::disable:
                {
                    GLenum cap;
                    _cmdbuf.read(cap);
                    m_renderCtx->disable(cap);
                }
                    break;

                case CommandBuffer::disableVertexAttribArray:
                {
                    GLuint index;
                    _cmdbuf.read(index);
                    m_renderCtx->disableVertexAttribArray(index);
                }
                    break;

                case CommandBuffer::drawArrays:
                {
                    GLenum mode;
                    GLint first;
                    GLsizei count;
                    _cmdbuf.read(mode);
                    _cmdbuf.read(first);
                    _cmdbuf.read(count);
                    m_renderCtx->drawArrays(mode, first, count);
                }
                    break;

                case CommandBuffer::drawElements:
                {
                    GLenum mode;
                    GLsizei count;
                    GLenum type;
                    const GLvoid *indices;
                    _cmdbuf.read(mode);
                    _cmdbuf.read(count);
                    _cmdbuf.read(type);
                    _cmdbuf.read(indices);
                    m_renderCtx->drawElements(mode, count, type, indices);
                }
                    break;

                case CommandBuffer::enable:
                {
                    GLenum cap;
                    _cmdbuf.read(cap);
                    m_renderCtx->enable(cap);
                }
                    break;

                case CommandBuffer::enableVertexAttribArray:
                {
                    GLuint index;
                    _cmdbuf.read(index);
                    m_renderCtx->enableVertexAttribArray(index);
                }
                    break;

                case CommandBuffer::_finish:
                {
                    m_renderCtx->finish();
                }
                    break;

                case CommandBuffer::flush:
                {
                    m_renderCtx->flush();
                }
                    break;

                case CommandBuffer::framebufferRenderbuffer:
                {
                    GLenum target;
                    GLenum attachment;
                    GLenum renderbuffertarget;
                    GLuint renderbuffer;
                    _cmdbuf.read(target);
                    _cmdbuf.read(attachment);
                    _cmdbuf.read(renderbuffertarget);
                    _cmdbuf.read(renderbuffer);
                    m_renderCtx->framebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
                }
                    break;

                case CommandBuffer::framebufferTexture2D:
                {
                    GLenum target;
                    GLenum attachment;
                    GLenum textarget;
                    GLuint texture;
                    GLint level;
                    _cmdbuf.read(target);
                    _cmdbuf.read(attachment);
                    _cmdbuf.read(textarget);
                    _cmdbuf.read(texture);
                    _cmdbuf.read(level);
                    m_renderCtx->framebufferTexture2D(target, attachment, textarget, texture, level);
                }
                    break;

                case CommandBuffer::frontFace:
                {
                    GLenum mode;
                    _cmdbuf.read(mode);
                    m_renderCtx->frontFace(mode);
                }
                    break;

                case CommandBuffer::genBuffers:
                {
                    GLsizei n;
                    _cmdbuf.read(n);
                    assert(n < sizeof(__intSyncCommandReturn) / sizeof(__intSyncCommandReturn[0]));
                    m_renderCtx->genBuffers(n, (GLuint*)__intSyncCommandReturn);
                }
                    break;

                case CommandBuffer::generateMipmap:
                {
                    GLenum target;
                    _cmdbuf.read(target);
                    m_renderCtx->generateMipmap(target);
                }
                    break;

                case CommandBuffer::genFramebuffers:
                {
                    GLsizei n;
                    _cmdbuf.read(n);
                    assert(n < sizeof(__intSyncCommandReturn) / sizeof(__intSyncCommandReturn[0]));
                    m_renderCtx->genFramebuffers(n, (GLuint*)__intSyncCommandReturn);
                }
                    break;

                case CommandBuffer::genRenderbuffers:
                {
                    GLsizei n;
                    _cmdbuf.read(n);
                    assert(n < sizeof(__intSyncCommandReturn) / sizeof(__intSyncCommandReturn[0]));
                    m_renderCtx->genRenderbuffers(n, (GLuint*)__intSyncCommandReturn);
                }
                    break;

                case CommandBuffer::genTextures:
                {
                    GLsizei n;
                    _cmdbuf.read(n);
                    assert(n < sizeof(__intSyncCommandReturn) / sizeof(__intSyncCommandReturn[0]));
                    m_renderCtx->genTextures(n, (GLuint*)__intSyncCommandReturn);
                }
                    break;

                case CommandBuffer::getActiveAttrib:
                {
                    GLuint program;
                    GLuint index;
                    GLsizei bufsize;
                    _cmdbuf.read(program);
                    _cmdbuf.read(index);
                    _cmdbuf.read(bufsize);

                    GLsizei length = 0;
                    GLint size = 0;
                    GLenum type = 0;
                    m_renderCtx->getProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
                    GLchar* name = new (std::nothrow) GLchar[length];

                    m_renderCtx->getActiveAttrib(program, index, bufsize, &length, &size, &type, name);
                    __intSyncCommandReturn[0] = length;
                    __intSyncCommandReturn[1] = size;
                    __intSyncCommandReturn[2] = type;
                    __strSyncCommandReturn = (const char*)name;
                    free(name);
                }
                    break;

                case CommandBuffer::getActiveUniform:
                {
                    GLuint program;
                    GLuint index;
                    GLsizei bufsize;
                    _cmdbuf.read(program);
                    _cmdbuf.read(index);
                    _cmdbuf.read(bufsize);

                    GLsizei length = 0;
                    GLint size = 0;
                    GLenum type = 0;
                    m_renderCtx->getProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
                    GLchar* name = new (std::nothrow) GLchar[length];

                    m_renderCtx->getActiveUniform(program, index, bufsize, &length, &size, &type, name);
                    __intSyncCommandReturn[0] = length;
                    __intSyncCommandReturn[1] = size;
                    __intSyncCommandReturn[2] = type;
                    __strSyncCommandReturn = (const char*)name;
                    free(name);
                }
                    break;

                case CommandBuffer::getAttachedShaders:
                {
                    GLuint program;
                    GLsizei maxcount;
                    _cmdbuf.read(program);
                    _cmdbuf.read(maxcount);

                    GLsizei length;
                    m_renderCtx->getProgramiv(program, GL_ATTACHED_SHADERS, &length);

                    GLuint* buffer = new (std::nothrow) GLuint[length];
                    memset(buffer, 0, length * sizeof(GLuint));

                    GLsizei count = 0;
                    m_renderCtx->getAttachedShaders(program, maxcount, &count, buffer);
                    __intSyncCommandReturn[0] = count;
                    assert(count < sizeof(__intSyncCommandReturn) / sizeof(__intSyncCommandReturn[0]));
                    for (GLsizei i = 0; i < count; ++i)
                    {
                        __intSyncCommandReturn[i+1] = buffer[i];
                    }
                }
                    break;

                case CommandBuffer::getAttribLocation:
                {
                    GLuint program;
                    const Memory *name;
                    _cmdbuf.read(program);
                    _cmdbuf.read(name);
                    int location = m_renderCtx->getAttribLocation(program, (const GLchar*)name->data);
                    __intSyncCommandReturn[0] = location;
                    release(name);
                }
                    break;

                case CommandBuffer::getBooleanv:
                {
                    GLenum pname;
                    GLsizei count;
                    _cmdbuf.read(pname);
                    _cmdbuf.read(count);
                    assert(count < sizeof(__intSyncCommandReturn) / sizeof(__intSyncCommandReturn[0]));
                    GLboolean ret[count];
                    m_renderCtx->getBooleanv(pname, ret);
                    for (GLsizei i = 0; i < count; ++i)
                    {
                        __intSyncCommandReturn[i] = ret[i];
                    }
                }
                    break;

                case CommandBuffer::getBufferParameteriv:
                {
                    assert(false); //cjh
                }
                    break;

                case CommandBuffer::getError:
                {
                    GLenum err = m_renderCtx->getError();
                    __intSyncCommandReturn[0] = err;
                }
                    break;

                case CommandBuffer::getFloatv:
                {
                    GLenum pname;
                    GLsizei count;
                    _cmdbuf.read(pname);
                    _cmdbuf.read(count);
                    assert(count < sizeof(__floatSyncCommandReturn) / sizeof(__floatSyncCommandReturn[0]));
                    GLfloat ret[count];
                    m_renderCtx->getFloatv(pname, ret);
                    for (GLsizei i = 0; i < count; ++i)
                    {
                        __floatSyncCommandReturn[i] = ret[i];
                    }
                }
                    break;

                case CommandBuffer::getFramebufferAttachmentParameteriv:
                {
                    assert(false);
//cjh                    m_renderCtx->getFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params);
                }
                    break;

                case CommandBuffer::getIntegerv:
                {
                    GLenum pname;
                    GLsizei count;
                    _cmdbuf.read(pname);
                    _cmdbuf.read(count);
                    assert(count < sizeof(__intSyncCommandReturn) / sizeof(__intSyncCommandReturn[0]));
                    m_renderCtx->getIntegerv(pname, __intSyncCommandReturn);
                }
                    break;

                case CommandBuffer::getProgramiv:
                {
                    GLuint program;
                    GLenum pname;
                    GLuint count;
                    _cmdbuf.read(program);
                    _cmdbuf.read(pname);
                    _cmdbuf.read(count);
                    assert(count < sizeof(__intSyncCommandReturn) / sizeof(__intSyncCommandReturn[0]));
                    m_renderCtx->getProgramiv(program, pname, __intSyncCommandReturn);
                }
                    break;

                case CommandBuffer::getProgramInfoLog:
                {
                    GLuint program;
                    GLsizei bufsize;
                    _cmdbuf.read(program);
                    _cmdbuf.read(bufsize);
                    GLsizei length;
                    GLchar* infolog = (GLchar*)malloc(bufsize);
                    m_renderCtx->getProgramInfoLog(program, bufsize, &length, infolog);
                    __strSyncCommandReturn = infolog;
                    free(infolog);
                }
                    break;

                case CommandBuffer::getRenderbufferParameteriv:
                {
                    assert(false); //cjh
                }
                    break;

                case CommandBuffer::getShaderiv:
                {
                    GLuint shader;
                    GLenum pname;
                    _cmdbuf.read(shader);
                    _cmdbuf.read(pname);
                    GLint params;
                    m_renderCtx->getShaderiv(shader, pname, &params);
                    __intSyncCommandReturn[0] = params;
                }
                    break;

                case CommandBuffer::getShaderInfoLog:
                {
                    GLuint shader;
                    GLsizei bufsize;
                    _cmdbuf.read(shader);
                    _cmdbuf.read(bufsize);

                    GLsizei length = 0;
                    GLchar* infolog = (GLchar*)malloc(bufsize);
                    m_renderCtx->getShaderInfoLog(shader, bufsize, &length, infolog);
                    __intSyncCommandReturn[0] = length;
                    __strSyncCommandReturn = infolog;
                    free(infolog);
                }
                    break;

                case CommandBuffer::getShaderSource:
                {
                    GLuint shader;
                    GLsizei bufsize;
                    _cmdbuf.read(shader);
                    _cmdbuf.read(bufsize);

                    GLsizei length = 0;
                    GLchar* source = (GLchar*)malloc(bufsize);
                    m_renderCtx->getShaderSource(shader, bufsize, &length, source);
                    __intSyncCommandReturn[0] = length;
                    __strSyncCommandReturn = source;
                    free(source);
                }
                    break;

                case CommandBuffer::getString:
                {
                    GLenum name;
                    _cmdbuf.read(name);
                    const GLubyte* str = m_renderCtx->getString(name);
                    __strSyncCommandReturn = (const char*)str;
                }
                    break;

                case CommandBuffer::getTexParameterfv:
                {
                    GLenum target;
                    GLenum pname;
                    _cmdbuf.read(target);
                    _cmdbuf.read(pname);
                    GLfloat params;
                    m_renderCtx->getTexParameterfv(target, pname, &params);
                    __floatSyncCommandReturn[0] = params;
                }
                    break;

                case CommandBuffer::getTexParameteriv:
                {
                    GLenum target;
                    GLenum pname;
                    _cmdbuf.read(target);
                    _cmdbuf.read(pname);
                    GLint params;
                    m_renderCtx->getTexParameteriv(target, pname, &params);
                    __intSyncCommandReturn[0] = params;
                }
                    break;

                case CommandBuffer::getUniformfv:
                {
                    GLuint program;
                    GLint location;
                    GLsizei floatCount;
                    _cmdbuf.read(program);
                    _cmdbuf.read(location);
                    _cmdbuf.read(floatCount);
                    assert(floatCount < sizeof(__floatSyncCommandReturn)/sizeof(__floatSyncCommandReturn[0]));
                    GLfloat* params = (GLfloat*)malloc(sizeof(GLfloat) * floatCount);
                    m_renderCtx->getUniformfv(program, location, params);
                    for (GLsizei i = 0; i < floatCount; ++i)
                    {
                        __floatSyncCommandReturn[i] = params[i];
                    }
                    free(params);
                }
                    break;

                case CommandBuffer::getUniformiv:
                {
                    GLuint program;
                    GLint location;
                    GLsizei intCount;
                    _cmdbuf.read(program);
                    _cmdbuf.read(location);
                    _cmdbuf.read(intCount);
                    assert(intCount < sizeof(__intSyncCommandReturn)/sizeof(__intSyncCommandReturn[0]));
                    GLint* params = (GLint*)malloc(sizeof(GLint) * intCount);
                    m_renderCtx->getUniformiv(program, location, params);
                    for (GLsizei i = 0; i < intCount; ++i)
                    {
                        __intSyncCommandReturn[i] = params[i];
                    }
                    free(params);
                }
                    break;

                case CommandBuffer::getUniformLocation:
                {
                    GLuint program;
                    const Memory* name;
                    _cmdbuf.read(program);
                    _cmdbuf.read(name);
                    GLint location = m_renderCtx->getUniformLocation(program, (const GLchar*)name->data);
                    __intSyncCommandReturn[0] = location;
                }
                    break;

                case CommandBuffer::getVertexAttribfv:
                {
                    GLuint index;
                    GLenum pname;
                    GLsizei count;
                    _cmdbuf.read(index);
                    _cmdbuf.read(pname);
                    _cmdbuf.read(count);
                    assert(count < sizeof(__floatSyncCommandReturn)/sizeof(__floatSyncCommandReturn[0]));
                    m_renderCtx->getVertexAttribfv(index, pname, __floatSyncCommandReturn);
                }
                    break;

                case CommandBuffer::getVertexAttribiv:
                {
                    GLuint index;
                    GLenum pname;
                    GLsizei count;
                    _cmdbuf.read(index);
                    _cmdbuf.read(pname);
                    _cmdbuf.read(count);
                    assert(count < sizeof(__intSyncCommandReturn)/sizeof(__intSyncCommandReturn[0]));
                    m_renderCtx->getVertexAttribiv(index, pname, __intSyncCommandReturn);
                }
                    break;

                case CommandBuffer::getVertexAttribPointerv:
                {
                    GLuint index;
                    GLenum pname;
                    _cmdbuf.read(index);
                    _cmdbuf.read(pname);
                    GLvoid *pointer;
                    m_renderCtx->getVertexAttribPointerv(index, pname, &pointer);
                    __intSyncCommandReturn[0] = (int)(intptr_t)pointer;
                }
                    break;

                case CommandBuffer::hint:
                {
                    GLenum target;
                    GLenum mode;
                    _cmdbuf.read(target);
                    _cmdbuf.read(mode);
                    m_renderCtx->hint(target, mode);
                }
                    break;

                case CommandBuffer::isBuffer:
                {
                    GLuint buffer;
                    _cmdbuf.read(buffer);
                    GLboolean ret = m_renderCtx->isBuffer(buffer);
                    __intSyncCommandReturn[0] = ret;
                }
                    break;

                case CommandBuffer::isEnabled:
                {
                    GLenum cap;
                    _cmdbuf.read(cap);
                    GLboolean ret = m_renderCtx->isEnabled(cap);
                    __intSyncCommandReturn[0] = ret;
                }
                    break;

                case CommandBuffer::isFramebuffer:
                {
                    GLuint buffer;
                    _cmdbuf.read(buffer);
                    GLboolean ret = m_renderCtx->isFramebuffer(buffer);
                    __intSyncCommandReturn[0] = ret;
                }
                    break;

                case CommandBuffer::isProgram:
                {
                    GLuint id;
                    _cmdbuf.read(id);
                    GLboolean ret = m_renderCtx->isProgram(id);
                    __intSyncCommandReturn[0] = ret;
                }
                    break;

                case CommandBuffer::isRenderbuffer:
                {
                    GLuint id;
                    _cmdbuf.read(id);
                    GLboolean ret = m_renderCtx->isRenderbuffer(id);
                    __intSyncCommandReturn[0] = ret;
                }
                    break;

                case CommandBuffer::isShader:
                {
                    GLuint id;
                    _cmdbuf.read(id);
                    GLboolean ret = m_renderCtx->isShader(id);
                    __intSyncCommandReturn[0] = ret;
                }
                    break;

                case CommandBuffer::isTexture:
                {
                    GLuint id;
                    _cmdbuf.read(id);
                    GLboolean ret = m_renderCtx->isTexture(id);
                    __intSyncCommandReturn[0] = ret;
                }
                    break;

                case CommandBuffer::lineWidth:
                {
                    GLfloat width;
                    _cmdbuf.read(width);
                    m_renderCtx->lineWidth(width);
                }
                    break;

                case CommandBuffer::linkProgram:
                {
                    GLuint program;
                    _cmdbuf.read(program);
                    m_renderCtx->linkProgram(program);
                }
                    break;

                case CommandBuffer::pixelStorei:
                {
                    GLenum pname;
                    GLint param;
                    _cmdbuf.read(pname);
                    _cmdbuf.read(param);
                    m_renderCtx->pixelStorei(pname, param);
                }
                    break;

                case CommandBuffer::polygonOffset:
                {
                    GLfloat factor;
                    GLfloat units;
                    _cmdbuf.read(factor);
                    _cmdbuf.read(units);
                    m_renderCtx->polygonOffset(factor, units);
                }
                    break;

                case CommandBuffer::readPixels:
                {
                    assert(false);//cjh
                }
                    break;

                case CommandBuffer::renderbufferStorage:
                {
                    GLenum target;
                    GLenum internalformat;
                    GLsizei width;
                    GLsizei height;
                    _cmdbuf.read(target);
                    _cmdbuf.read(internalformat);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    m_renderCtx->renderbufferStorage(target, internalformat, width, height);
                }
                    break;

                case CommandBuffer::sampleCoverage:
                {
                    GLclampf value;
                    GLboolean invert;
                    _cmdbuf.read(value);
                    _cmdbuf.read(invert);
                    m_renderCtx->sampleCoverage(value, invert);
                }
                    break;

                case CommandBuffer::scissor:
                {
                    GLint x;
                    GLint y;
                    GLsizei width;
                    GLsizei height;
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    m_renderCtx->scissor(x, y, width, height);
                }
                    break;

                case CommandBuffer::shaderSource:
                {
                    GLuint shader;
                    GLsizei count;
                    const Memory *string;
                    _cmdbuf.read(shader);
                    _cmdbuf.read(count);
                    _cmdbuf.read(string);
                    assert(count == 1);
                    m_renderCtx->shaderSource(shader, count, (const GLchar**)&string->data, __intSyncCommandReturn);
                    release(string);
                }
                    break;

                case CommandBuffer::stencilFunc:
                {
                    GLenum func;
                    GLint ref;
                    GLuint mask;
                    _cmdbuf.read(func);
                    _cmdbuf.read(ref);
                    _cmdbuf.read(mask);
                    m_renderCtx->stencilFunc(func, ref, mask);
                }
                    break;

                case CommandBuffer::stencilFuncSeparate:
                {
                    GLenum face;
                    GLenum func;
                    GLint ref;
                    GLuint mask;
                    _cmdbuf.read(face);
                    _cmdbuf.read(func);
                    _cmdbuf.read(ref);
                    _cmdbuf.read(mask);
                    m_renderCtx->stencilFuncSeparate(face, func, ref, mask);
                }
                    break;

                case CommandBuffer::stencilMask:
                {
                    GLuint mask;
                    _cmdbuf.read(mask);
                    m_renderCtx->stencilMask(mask);
                }
                    break;

                case CommandBuffer::stencilMaskSeparate:
                {
                    GLenum face;
                    GLuint mask;
                    _cmdbuf.read(face);
                    _cmdbuf.read(mask);
                    m_renderCtx->stencilMaskSeparate(face, mask);
                }
                    break;

                case CommandBuffer::stencilOp:
                {
                    GLenum fail;
                    GLenum zfail;
                    GLenum zpass;
                    _cmdbuf.read(fail);
                    _cmdbuf.read(zfail);
                    _cmdbuf.read(zpass);
                    m_renderCtx->stencilOp(fail, zfail, zpass);
                }
                    break;

                case CommandBuffer::stencilOpSeparate:
                {
                    GLenum face;
                    GLenum fail;
                    GLenum zfail;
                    GLenum zpass;
                    _cmdbuf.read(face);
                    _cmdbuf.read(fail);
                    _cmdbuf.read(zfail);
                    _cmdbuf.read(zpass);
                    m_renderCtx->stencilOpSeparate(face, fail, zfail, zpass);
                }
                    break;

                case CommandBuffer::texImage2D:
                {
                    GLenum target;
                    GLint level;
                    GLint internalformat;
                    GLsizei width;
                    GLsizei height;
                    GLint border;
                    GLenum format;
                    GLenum type;
                    const Memory* pixels;
                    _cmdbuf.read(target);
                    _cmdbuf.read(level);
                    _cmdbuf.read(internalformat);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    _cmdbuf.read(border);
                    _cmdbuf.read(format);
                    _cmdbuf.read(type);
                    _cmdbuf.read(pixels);
                    m_renderCtx->texImage2D(target, level, internalformat, width, height, border, format, type, pixels->data);
                    release(pixels);
                }
                    break;

                case CommandBuffer::texParameterf:
                {
                    GLenum target;
                    GLenum pname;
                    GLfloat param;
                    _cmdbuf.read(target);
                    _cmdbuf.read(pname);
                    _cmdbuf.read(param);
                    m_renderCtx->texParameterf(target, pname, param);
                }
                    break;

                case CommandBuffer::texParameterfv:
                {
                    assert(false);//cjh
                }
                    break;

                case CommandBuffer::texParameteri:
                {
                    GLenum target;
                    GLenum pname;
                    GLint param;
                    _cmdbuf.read(target);
                    _cmdbuf.read(pname);
                    _cmdbuf.read(param);
                    m_renderCtx->texParameteri(target, pname, param);
                }
                    break;

                case CommandBuffer::texParameteriv:
                {
                    assert(false);//cjh
                }
                    break;

                case CommandBuffer::texSubImage2D:
                {
                    GLenum target;
                    GLint level;
                    GLint xoffset;
                    GLint yoffset;
                    GLsizei width;
                    GLsizei height;
                    GLenum format;
                    GLenum type;
                    const Memory* pixels;
                    _cmdbuf.read(target);
                    _cmdbuf.read(level);
                    _cmdbuf.read(xoffset);
                    _cmdbuf.read(yoffset);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    _cmdbuf.read(format);
                    _cmdbuf.read(type);
                    _cmdbuf.read(pixels);
                    m_renderCtx->texSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels->data);
                    release(pixels);
                }
                    break;

                case CommandBuffer::uniform1f:
                {
                    GLint location;
                    GLfloat x;
                    _cmdbuf.read(location);
                    _cmdbuf.read(x);
                    m_renderCtx->uniform1f(location, x);
                }
                    break;

                case CommandBuffer::uniform1fv:
                {
                    GLint location;
                    GLsizei count;
                    const Memory* v;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(v);
                    m_renderCtx->uniform1fv(location, count, (const GLfloat*)v->data);
                    release(v);
                }
                    break;

                case CommandBuffer::uniform1i:
                {
                    GLint location;
                    GLint x;
                    _cmdbuf.read(location);
                    _cmdbuf.read(x);
                    m_renderCtx->uniform1i(location, x);
                }
                    break;

                case CommandBuffer::uniform1iv:
                {
                    GLint location;
                    GLsizei count;
                    const Memory* v;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(v);
                    m_renderCtx->uniform1iv(location, count, (const GLint*)v->data);
                    release(v);
                }
                    break;

                case CommandBuffer::uniform2f:
                {
                    GLint location;
                    GLfloat x;
                    GLfloat y;
                    _cmdbuf.read(location);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    m_renderCtx->uniform2f(location, x, y);
                }
                    break;

                case CommandBuffer::uniform2fv:
                {
                    GLint location;
                    GLsizei count;
                    const Memory* v;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(v);
                    m_renderCtx->uniform2fv(location, count, (const GLfloat*)v->data);
                    release(v);
                }
                    break;

                case CommandBuffer::uniform2i:
                {
                    GLint location;
                    GLint x;
                    GLint y;
                    _cmdbuf.read(location);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    m_renderCtx->uniform2i(location, x, y);
                }
                    break;

                case CommandBuffer::uniform2iv:
                {
                    GLint location;
                    GLsizei count;
                    const Memory* v;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(v);
                    m_renderCtx->uniform2iv(location, count, (const GLint*)v->data);
                    release(v);
                }
                    break;

                case CommandBuffer::uniform3f:
                {
                    GLint location;
                    GLfloat x;
                    GLfloat y;
                    GLfloat z;
                    _cmdbuf.read(location);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(z);
                    m_renderCtx->uniform3f(location, x, y, z);
                }
                    break;

                case CommandBuffer::uniform3fv:
                {
                    GLint location;
                    GLsizei count;
                    const Memory* v;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(v);
                    m_renderCtx->uniform3fv(location, count, (const GLfloat*)v->data);
                    release(v);
                }
                    break;

                case CommandBuffer::uniform3i:
                {
                    GLint location;
                    GLint x;
                    GLint y;
                    GLint z;
                    _cmdbuf.read(location);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(z);
                    m_renderCtx->uniform3i(location, x, y, z);
                }
                    break;

                case CommandBuffer::uniform3iv:
                {
                    GLint location;
                    GLsizei count;
                    const Memory* v;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(v);
                    m_renderCtx->uniform3iv(location, count, (const GLint*)v->data);
                    release(v);
                }
                    break;

                case CommandBuffer::uniform4f:
                {
                    GLint location;
                    GLfloat x;
                    GLfloat y;
                    GLfloat z;
                    GLfloat w;
                    _cmdbuf.read(location);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(z);
                    _cmdbuf.read(w);
                    m_renderCtx->uniform4f(location, x, y, z, w);
                }
                    break;

                case CommandBuffer::uniform4fv:
                {
                    GLint location;
                    GLsizei count;
                    const Memory* v;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(v);
                    m_renderCtx->uniform4fv(location, count, (const GLfloat*)v->data);
                    release(v);
                }
                    break;

                case CommandBuffer::uniform4i:
                {
                    GLint location;
                    GLint x;
                    GLint y;
                    GLint z;
                    GLint w;
                    _cmdbuf.read(location);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(z);
                    _cmdbuf.read(w);
                    m_renderCtx->uniform4i(location, x, y, z, w);
                }
                    break;

                case CommandBuffer::uniform4iv:
                {
                    GLint location;
                    GLsizei count;
                    const Memory* v;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(v);
                    m_renderCtx->uniform4iv(location, count, (const GLint*)v->data);
                    release(v);
                }
                    break;

                case CommandBuffer::uniformMatrix2fv:
                {
                    GLint location;
                    GLsizei count;
                    GLboolean transpose;
                    const Memory *value;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(transpose);
                    _cmdbuf.read(value);
                    m_renderCtx->uniformMatrix2fv(location, count, transpose, (const GLfloat *)value->data);
                    release(value);
                }
                    break;

                case CommandBuffer::uniformMatrix3fv:
                {
                    GLint location;
                    GLsizei count;
                    GLboolean transpose;
                    const Memory *value;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(transpose);
                    _cmdbuf.read(value);
                    m_renderCtx->uniformMatrix3fv(location, count, transpose, (const GLfloat *)value->data);
                    release(value);
                }
                    break;

                case CommandBuffer::uniformMatrix4fv:
                {
                    GLint location;
                    GLsizei count;
                    GLboolean transpose;
                    const Memory *value;
                    _cmdbuf.read(location);
                    _cmdbuf.read(count);
                    _cmdbuf.read(transpose);
                    _cmdbuf.read(value);
                    m_renderCtx->uniformMatrix4fv(location, count, transpose, (const GLfloat *)value->data);
                    release(value);
                }
                    break;

                case CommandBuffer::useProgram:
                {
                    GLuint program;
                    _cmdbuf.read(program);
                    m_renderCtx->useProgram(program);
                }
                    break;

                case CommandBuffer::validateProgram:
                {
                    GLuint program;
                    _cmdbuf.read(program);
                    m_renderCtx->validateProgram(program);
                }
                    break;

                case CommandBuffer::vertexAttrib1f:
                {
                    GLuint index;
                    GLfloat x;
                    _cmdbuf.read(index);
                    _cmdbuf.read(x);
                    m_renderCtx->vertexAttrib1f(index, x);
                }
                    break;

                case CommandBuffer::vertexAttrib1fv:
                {
                    GLuint index;
                    const Memory *values;
                    _cmdbuf.read(index);
                    _cmdbuf.read(values);
                    m_renderCtx->vertexAttrib1fv(index, (const GLfloat *)values->data);
                    release(values);
                }
                    break;

                case CommandBuffer::vertexAttrib2f:
                {
                    GLuint index;
                    GLfloat x;
                    GLfloat y;
                    _cmdbuf.read(index);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    m_renderCtx->vertexAttrib2f(index, x, y);
                }
                    break;

                case CommandBuffer::vertexAttrib2fv:
                {
                    GLuint index;
                    const Memory *values;
                    _cmdbuf.read(index);
                    _cmdbuf.read(values);
                    m_renderCtx->vertexAttrib2fv(index, (const GLfloat *)values->data);
                    release(values);
                }
                    break;

                case CommandBuffer::vertexAttrib3f:
                {
                    GLuint index;
                    GLfloat x;
                    GLfloat y;
                    GLfloat z;
                    _cmdbuf.read(index);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(z);
                    m_renderCtx->vertexAttrib3f(index, x, y, z);
                }
                    break;

                case CommandBuffer::vertexAttrib3fv:
                {
                    GLuint index;
                    const Memory *values;
                    _cmdbuf.read(index);
                    _cmdbuf.read(values);
                    m_renderCtx->vertexAttrib3fv(index, (const GLfloat *)values->data);
                    release(values);
                }
                    break;

                case CommandBuffer::vertexAttrib4f:
                {
                    GLuint index;
                    GLfloat x;
                    GLfloat y;
                    GLfloat z;
                    GLfloat w;
                    _cmdbuf.read(index);
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(z);
                    _cmdbuf.read(w);
                    m_renderCtx->vertexAttrib4f(index, x, y, z, w);
                }
                    break;

                case CommandBuffer::vertexAttrib4fv:
                {
                    GLuint index;
                    const Memory *values;
                    _cmdbuf.read(index);
                    _cmdbuf.read(values);
                    m_renderCtx->vertexAttrib4fv(index, (const GLfloat *)values->data);
                    release(values);
                }
                    break;

                case CommandBuffer::vertexAttribPointer:
                {
                    GLuint index;
                    GLint size;
                    GLenum type;
                    GLboolean normalized;
                    GLsizei stride;
                    const GLvoid *ptr;
                    _cmdbuf.read(index);
                    _cmdbuf.read(size);
                    _cmdbuf.read(type);
                    _cmdbuf.read(normalized);
                    _cmdbuf.read(stride);
                    _cmdbuf.read(ptr);
                    m_renderCtx->vertexAttribPointer(index, size, type, normalized, stride, ptr);
                }
                    break;

                case CommandBuffer::viewport:
                {
                    GLint x;
                    GLint y;
                    GLsizei width;
                    GLsizei height;
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    m_renderCtx->viewport(x, y, width, height);
                }
                    break;

                case CommandBuffer::drawBuffer:
                {
                    GLenum mode;
                    _cmdbuf.read(mode);
                    m_renderCtx->drawBuffer(mode);
                }
                    break;

                case CommandBuffer::readBuffer:
                {
                    GLenum mode;
                    _cmdbuf.read(mode);
                    m_renderCtx->readBuffer(mode);
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

    void flip()
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

    RenderFrame::Enum renderFrame(int32_t _msecs)
    {
        BGFX_PROFILER_SCOPE("bgfx::renderFrame", 0xff2040ff);

        if (!m_flipAfterRender)
        {
            BGFX_PROFILER_SCOPE("bgfx/flip", 0xff2040ff);
            if (m_flipped)
            {
                static int sss = 0;
                printf("Sync command called!: %d\n", ++sss);
            }
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


// OPENGL API IMPLEMENTATION BEGIN

void glActiveTexture(GLenum texture)
{

}

void glAttachShader(GLuint program, GLuint shader)
{

}

void glBindAttribLocation(GLuint program, GLuint index, const GLchar* name)
{

}

void glBindBuffer(GLenum target, GLuint buffer)
{

}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{

}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{

}

void glBindTexture(GLenum target, GLuint texture)
{

}

void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{

}

void glBlendEquation(GLenum mode)
{

}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{

}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{

}

void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{

}

void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{

}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
{

}

GLenum glCheckFramebufferStatus(GLenum target)
{
    return 0;
}

void glClear(GLbitfield mask)
{
    auto& cmd = getCommandBuffer(CommandBuffer::clear);
    cmd.write(mask);
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    auto& cmd = getCommandBuffer(CommandBuffer::clearColor);
    cmd.write(red);
    cmd.write(green);
    cmd.write(blue);
    cmd.write(alpha);
}

void glClearDepthf(GLclampf depth)
{

}

void glClearStencil(GLint s)
{

}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{

}

void glCompileShader(GLuint shader)
{

}

void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
{

}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
{

}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{

}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{

}

GLuint glCreateProgram(void)
{
    return 0;
}

GLuint glCreateShader(GLenum type)
{
    return 0;
}

void glCullFace(GLenum mode)
{

}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{

}

void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{

}

void glDeleteProgram(GLuint program)
{

}

void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{

}

void glDeleteShader(GLuint shader)
{

}

void glDeleteTextures(GLsizei n, const GLuint* textures)
{

}

void glDepthFunc(GLenum func)
{

}

void glDepthMask(GLboolean flag)
{

}

void glDepthRangef(GLclampf zNear, GLclampf zFar)
{

}

void glDetachShader(GLuint program, GLuint shader)
{

}

void glDisable(GLenum cap)
{

}

void glDisableVertexAttribArray(GLuint index)
{

}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{

}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{

}

void glEnable(GLenum cap)
{

}

void glEnableVertexAttribArray(GLuint index)
{

}

void glFinish(void)
{

}

void glFlush(void)
{

}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{

}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{

}

void glFrontFace(GLenum mode)
{

}

void glGenBuffers(GLsizei n, GLuint* buffers)
{

}

void glGenerateMipmap(GLenum target)
{

}

void glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{

}

void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{

}

void glGenTextures(GLsizei n, GLuint* textures)
{

}

void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{

}

void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{

}

void glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{

}

int glGetAttribLocation(GLuint program, const GLchar* name)
{
    return 0;
}

void glGetBooleanv(GLenum pname, GLboolean* params)
{

}

void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{

}

GLenum glGetError(void)
{
    return 0;
}

void glGetFloatv(GLenum pname, GLfloat* params)
{

}

void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{

}

void glGetIntegerv(GLenum pname, GLint* params)
{

}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{

}

void glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{

}

void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{

}

void glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{

}

void glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{

}

void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{

}

void glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
{

}

const GLubyte* glGetString(GLenum name)
{
    return 0;
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{

}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{

}

void glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{

}

void glGetUniformiv(GLuint program, GLint location, GLint* params)
{

}

int glGetUniformLocation(GLuint program, const GLchar* name)
{
    return 0;
}

void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{

}

void glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{

}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer)
{

}

void glHint(GLenum target, GLenum mode)
{

}

GLboolean glIsBuffer(GLuint buffer)
{
    return 0;
}

GLboolean glIsEnabled(GLenum cap)
{
    return 0;
}

GLboolean glIsFramebuffer(GLuint framebuffer)
{
    return 0;
}

GLboolean glIsProgram(GLuint program)
{
    return 0;
}

GLboolean glIsRenderbuffer(GLuint renderbuffer)
{
    return 0;
}

GLboolean glIsShader(GLuint shader)
{
    return 0;
}

GLboolean glIsTexture(GLuint texture)
{
    return 0;
}

void glLineWidth(GLfloat width)
{

}

void glLinkProgram(GLuint program)
{

}

void glPixelStorei(GLenum pname, GLint param)
{

}

void glPolygonOffset(GLfloat factor, GLfloat units)
{

}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
{

}

void glReleaseShaderCompiler(void)
{

}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{

}

void glSampleCoverage(GLclampf value, GLboolean invert)
{

}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{

}

void glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
{

}

void glShaderSource(GLuint shader, GLsizei count, const GLchar* const *string, const GLint* length)
{

}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)
{

}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{

}

void glStencilMask(GLuint mask)
{

}

void glStencilMaskSeparate(GLenum face, GLuint mask)
{

}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{

}

void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{

}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{

}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{

}

void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{

}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{

}

void glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{

}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
{

}

void glUniform1f(GLint location, GLfloat x)
{

}

void glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{

}

void glUniform1i(GLint location, GLint x)
{

}

void glUniform1iv(GLint location, GLsizei count, const GLint* v)
{

}

void glUniform2f(GLint location, GLfloat x, GLfloat y)
{

}

void glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{

}

void glUniform2i(GLint location, GLint x, GLint y)
{

}

void glUniform2iv(GLint location, GLsizei count, const GLint* v)
{

}

void glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{

}

void glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{

}

void glUniform3i(GLint location, GLint x, GLint y, GLint z)
{

}

void glUniform3iv(GLint location, GLsizei count, const GLint* v)
{

}

void glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{

}

void glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{

}

void glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{

}

void glUniform4iv(GLint location, GLsizei count, const GLint* v)
{

}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{

}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{

}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{

}

void glUseProgram(GLuint program)
{

}

void glValidateProgram(GLuint program)
{

}

void glVertexAttrib1f(GLuint indx, GLfloat x)
{

}

void glVertexAttrib1fv(GLuint indx, const GLfloat* values)
{

}

void glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{

}

void glVertexAttrib2fv(GLuint indx, const GLfloat* values)
{

}

void glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{

}

void glVertexAttrib3fv(GLuint indx, const GLfloat* values)
{

}

void glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{

}

void glVertexAttrib4fv(GLuint indx, const GLfloat* values)
{

}

void glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{

}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{

}

void glDrawBuffer(GLenum mode)
{

}

void glReadBuffer(GLenum mode)
{

}


} // namespace fakegl {

