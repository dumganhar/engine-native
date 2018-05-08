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
#include <assert.h>

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
//    bx::Thread    m_thread;
#endif
}

namespace fakegl {

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
//            printf("apiSemPost\n");
            m_apiSem.post();
        }
    }

    bool apiSemWait(int32_t _msecs/* = -1*/)
    {
        if (m_singleThreaded)
        {
            return true;
        }

//        printf("apiSemWait\n");
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
//            printf("renderSemPost\n");
            m_renderSem.post();
        }
    }

    void renderSemWait()
    {
        if (!m_singleThreaded)
        {
//            printf("renderSemWait\n");
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

//        if (m_thread.isRunning() )
//        {
//            m_thread.shutdown();
//        }

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
                    if (memory != nullptr)
                    {
                        m_renderCtx->bufferData(target, memory->size, memory->data, usage);
                        release(memory);
                    }
                    else
                    {
                        m_renderCtx->bufferData(target, 0, nullptr, usage);
                    }
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
                    if (memory != nullptr)
                    {
                        m_renderCtx->bufferSubData(target, offset, memory->size, memory->data);
                        release(memory);
                    }
                    else
                    {
                        m_renderCtx->bufferSubData(target, offset, 0, nullptr);
                    }
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
                    GLchar* name = new (std::nothrow) GLchar[bufsize];
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
                    GLchar* name = new (std::nothrow) GLchar[bufsize];

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

                    GLuint* buffer = new (std::nothrow) GLuint[maxcount];
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
                    _cmdbuf.read(pname);
                    m_renderCtx->getIntegerv(pname, __intSyncCommandReturn);
                    //FIXME: how to determine how many integer value opengl actually returns.
                }
                    break;

                case CommandBuffer::getProgramiv:
                {
                    GLuint program;
                    GLenum pname;
                    _cmdbuf.read(program);
                    _cmdbuf.read(pname);
                    m_renderCtx->getProgramiv(program, pname, __intSyncCommandReturn);
                    //FIXME: how to determine how many integer value opengl actually returns.
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
                    __intSyncCommandReturn[0] = (GLint)length;
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
                    GLfloat* params;
                    _cmdbuf.read(program);
                    _cmdbuf.read(location);
                    _cmdbuf.read(params);
                    m_renderCtx->getUniformfv(program, location, params);
                }
                    break;

                case CommandBuffer::getUniformiv:
                {
                    GLuint program;
                    GLint location;
                    GLint* params;
                    _cmdbuf.read(program);
                    _cmdbuf.read(location);
                    _cmdbuf.read(params);
                    m_renderCtx->getUniformiv(program, location, params);
                }
                    break;

                case CommandBuffer::getUniformLocation:
                {
                    GLuint program;
                    const GLchar* name;
                    _cmdbuf.read(program);
                    _cmdbuf.read(name);
                    GLint location = m_renderCtx->getUniformLocation(program, name);
                    __intSyncCommandReturn[0] = location;
                }
                    break;

                case CommandBuffer::getVertexAttribfv:
                {
                    GLuint index;
                    GLenum pname;
                    GLfloat* params;
                    _cmdbuf.read(index);
                    _cmdbuf.read(pname);
                    _cmdbuf.read(params);
                    m_renderCtx->getVertexAttribfv(index, pname, params);
                }
                    break;

                case CommandBuffer::getVertexAttribiv:
                {
                    GLuint index;
                    GLenum pname;
                    GLint* params;
                    _cmdbuf.read(index);
                    _cmdbuf.read(pname);
                    _cmdbuf.read(params);
                    m_renderCtx->getVertexAttribiv(index, pname, params);
                }
                    break;

                case CommandBuffer::getVertexAttribPointerv:
                {
                    GLuint index;
                    GLenum pname;
                    GLvoid** pointer;
                    _cmdbuf.read(index);
                    _cmdbuf.read(pname);
                    _cmdbuf.read(pointer);
                    m_renderCtx->getVertexAttribPointerv(index, pname, pointer);
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
                    GLint x;
                    GLint y;
                    GLsizei width;
                    GLsizei height;
                    GLenum format;
                    GLenum type;
                    GLvoid *pixels;
                    _cmdbuf.read(x);
                    _cmdbuf.read(y);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    _cmdbuf.read(format);
                    _cmdbuf.read(type);
                    _cmdbuf.read(pixels);
                    m_renderCtx->readPixels(x, y, width, height, format, type, pixels);
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
                    m_renderCtx->shaderSource(shader, count, (const GLchar**)&string->data, nullptr);
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
                    const GLvoid* pixels;
                    _cmdbuf.read(target);
                    _cmdbuf.read(level);
                    _cmdbuf.read(internalformat);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    _cmdbuf.read(border);
                    _cmdbuf.read(format);
                    _cmdbuf.read(type);
                    _cmdbuf.read(pixels);
                    m_renderCtx->texImage2D(target, level, internalformat, width, height, border, format, type, pixels);
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
                    const GLvoid* pixels;
                    _cmdbuf.read(target);
                    _cmdbuf.read(level);
                    _cmdbuf.read(xoffset);
                    _cmdbuf.read(yoffset);
                    _cmdbuf.read(width);
                    _cmdbuf.read(height);
                    _cmdbuf.read(format);
                    _cmdbuf.read(type);
                    _cmdbuf.read(pixels);
                    m_renderCtx->texSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
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

static void blockMainThreadAndWaitResultFromGLThread()
{
    renderSemWait();
    m_flipped = true;
    frameNoRenderWait();
    renderSemWait();
    frameNoRenderWait();
}

void glActiveTexture(GLenum texture)
{
    auto& cmd = getCommandBuffer(CommandBuffer::activeTexture);
    cmd.write(texture);
}

void glAttachShader(GLuint program, GLuint shader)
{
    auto& cmd = getCommandBuffer(CommandBuffer::attachShader);
    cmd.write(program);
    cmd.write(shader);
}

void glBindAttribLocation(GLuint program, GLuint index, const GLchar* name)
{
    assert(name && strlen(name) > 0);
    auto& cmd = getCommandBuffer(CommandBuffer::bindAttribLocation);
    cmd.write(program);
    cmd.write(index);
    const Memory* m = bgfx::copy(name, (uint32_t)strlen(name) + 1);
    cmd.write(m);
}

void glBindBuffer(GLenum target, GLuint buffer)
{
    auto& cmd = getCommandBuffer(CommandBuffer::bindBuffer);
    cmd.write(target);
    cmd.write(buffer);
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
    auto& cmd = getCommandBuffer(CommandBuffer::bindFramebuffer);
    cmd.write(target);
    cmd.write(framebuffer);
}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
    auto& cmd = getCommandBuffer(CommandBuffer::bindRenderbuffer);
    cmd.write(target);
    cmd.write(renderbuffer);
}

void glBindTexture(GLenum target, GLuint texture)
{
    auto& cmd = getCommandBuffer(CommandBuffer::bindTexture);
    cmd.write(target);
    cmd.write(texture);
}

void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    auto& cmd = getCommandBuffer(CommandBuffer::blendColor);
    cmd.write(red);
    cmd.write(green);
    cmd.write(blue);
    cmd.write(alpha);
}

void glBlendEquation(GLenum mode)
{
    auto& cmd = getCommandBuffer(CommandBuffer::blendEquation);
    cmd.write(mode);
}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
    auto& cmd = getCommandBuffer(CommandBuffer::blendEquationSeparate);
    cmd.write(modeRGB);
    cmd.write(modeAlpha);
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
    auto& cmd = getCommandBuffer(CommandBuffer::blendFunc);
    cmd.write(sfactor);
    cmd.write(dfactor);
}

void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
    auto& cmd = getCommandBuffer(CommandBuffer::blendFuncSeparate);
    cmd.write(srcRGB);
    cmd.write(dstRGB);
    cmd.write(srcAlpha);
    cmd.write(dstAlpha);
}

void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
    auto& cmd = getCommandBuffer(CommandBuffer::bufferData);
    cmd.write(target);
    const Memory* m = nullptr;
    if (size > 0 && data != nullptr)
    {
        m = bgfx::copy(data, (uint32_t)size);
    }
    cmd.write(m);
    cmd.write(usage);
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
    auto& cmd = getCommandBuffer(CommandBuffer::bufferSubData);
    cmd.write(target);
    cmd.write(offset);
    const Memory* m = nullptr;
    if (size > 0 && data != nullptr)
    {
        m = bgfx::copy(data, (uint32_t)size);
    }
    cmd.write(m);
}

GLenum glCheckFramebufferStatus(GLenum target)
{
    auto& cmd = getCommandBuffer(CommandBuffer::checkFramebufferStatus);
    cmd.write(target);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
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
    auto& cmd = getCommandBuffer(CommandBuffer::clearDepthf);
    cmd.write(depth);
}

void glClearStencil(GLint s)
{
    auto& cmd = getCommandBuffer(CommandBuffer::clearStencil);
    cmd.write(s);
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    auto& cmd = getCommandBuffer(CommandBuffer::colorMask);
    cmd.write(red);
    cmd.write(green);
    cmd.write(blue);
    cmd.write(alpha);
}

void glCompileShader(GLuint shader)
{
    auto& cmd = getCommandBuffer(CommandBuffer::compileShader);
    cmd.write(shader);
}

void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
{
    auto& cmd = getCommandBuffer(CommandBuffer::compressedTexImage2D);
    cmd.write(target);
    cmd.write(level);
    cmd.write(internalformat);
    cmd.write(width);
    cmd.write(height);
    cmd.write(border);
    const Memory* m = bgfx::copy(data, (uint32_t)imageSize);
    cmd.write(m);
}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
{
    auto& cmd = getCommandBuffer(CommandBuffer::compressedTexSubImage2D);
    cmd.write(target);
    cmd.write(level);
    cmd.write(xoffset);
    cmd.write(yoffset);
    cmd.write(width);
    cmd.write(height);
    cmd.write(format);
    const Memory* m = bgfx::copy(data, (uint32_t)imageSize);
    cmd.write(m);
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    auto& cmd = getCommandBuffer(CommandBuffer::copyTexImage2D);
    cmd.write(target);
    cmd.write(level);
    cmd.write(internalformat);
    cmd.write(x);
    cmd.write(y);
    cmd.write(width);
    cmd.write(height);
    cmd.write(border);
}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    auto& cmd = getCommandBuffer(CommandBuffer::copyTexSubImage2D);
    cmd.write(target);
    cmd.write(level);
    cmd.write(xoffset);
    cmd.write(yoffset);
    cmd.write(x);
    cmd.write(y);
    cmd.write(width);
    cmd.write(height);
}

GLuint glCreateProgram()
{
    auto& cmd = getCommandBuffer(CommandBuffer::createProgram);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

GLuint glCreateShader(GLenum type)
{
    auto& cmd = getCommandBuffer(CommandBuffer::createShader);
    cmd.write(type);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

void glCullFace(GLenum mode)
{
    auto& cmd = getCommandBuffer(CommandBuffer::cullFace);
    cmd.write(mode);
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
    auto& cmd = getCommandBuffer(CommandBuffer::deleteBuffers);
    cmd.write(n);
    const Memory* m = bgfx::copy(buffers, sizeof(GLuint) * n);
    cmd.write(m);
}

void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
    auto& cmd = getCommandBuffer(CommandBuffer::deleteFramebuffers);
    cmd.write(n);
    const Memory* m = bgfx::copy(framebuffers, sizeof(GLuint) * n);
    cmd.write(m);
}

void glDeleteProgram(GLuint program)
{
    auto& cmd = getCommandBuffer(CommandBuffer::deleteProgram);
    cmd.write(program);
}

void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
    auto& cmd = getCommandBuffer(CommandBuffer::deleteRenderbuffers);
    cmd.write(n);
    const Memory* m = bgfx::copy(renderbuffers, sizeof(GLuint) * n);
    cmd.write(m);
}

void glDeleteShader(GLuint shader)
{
    auto& cmd = getCommandBuffer(CommandBuffer::deleteShader);
    cmd.write(shader);
}

void glDeleteTextures(GLsizei n, const GLuint* textures)
{
    auto& cmd = getCommandBuffer(CommandBuffer::deleteTextures);
    cmd.write(n);
    const Memory* m = bgfx::copy(textures, sizeof(GLuint) * n);
    cmd.write(m);
}

void glDepthFunc(GLenum func)
{
    auto& cmd = getCommandBuffer(CommandBuffer::depthFunc);
    cmd.write(func);
}

void glDepthMask(GLboolean flag)
{
    auto& cmd = getCommandBuffer(CommandBuffer::depthMask);
    cmd.write(flag);
}

void glDepthRangef(GLclampf zNear, GLclampf zFar)
{
    auto& cmd = getCommandBuffer(CommandBuffer::depthRangef);
    cmd.write(zNear);
    cmd.write(zFar);
}

void glDetachShader(GLuint program, GLuint shader)
{
    auto& cmd = getCommandBuffer(CommandBuffer::detachShader);
    cmd.write(program);
    cmd.write(shader);
}

void glDisable(GLenum cap)
{
    auto& cmd = getCommandBuffer(CommandBuffer::disable);
    cmd.write(cap);
}

void glDisableVertexAttribArray(GLuint index)
{
    auto& cmd = getCommandBuffer(CommandBuffer::disableVertexAttribArray);
    cmd.write(index);
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    auto& cmd = getCommandBuffer(CommandBuffer::drawArrays);
    cmd.write(mode);
    cmd.write(first);
    cmd.write(count);
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
    auto& cmd = getCommandBuffer(CommandBuffer::drawElements);
    cmd.write(mode);
    cmd.write(count);
    cmd.write(type);
    cmd.write(indices);
}

void glEnable(GLenum cap)
{
    auto& cmd = getCommandBuffer(CommandBuffer::enable);
    cmd.write(cap);
}

void glEnableVertexAttribArray(GLuint index)
{
    auto& cmd = getCommandBuffer(CommandBuffer::enableVertexAttribArray);
    cmd.write(index);
}

void glFinish()
{
    getCommandBuffer(CommandBuffer::_finish);
}

void glFlush()
{
    getCommandBuffer(CommandBuffer::flush);
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    auto& cmd = getCommandBuffer(CommandBuffer::framebufferRenderbuffer);
    cmd.write(target);
    cmd.write(attachment);
    cmd.write(renderbuffertarget);
    cmd.write(renderbuffer);
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    auto& cmd = getCommandBuffer(CommandBuffer::framebufferTexture2D);
    cmd.write(target);
    cmd.write(attachment);
    cmd.write(textarget);
    cmd.write(texture);
    cmd.write(level);
}

void glFrontFace(GLenum mode)
{
    auto& cmd = getCommandBuffer(CommandBuffer::frontFace);
    cmd.write(mode);
}

void glGenBuffers(GLsizei n, GLuint* buffers)
{
    auto& cmd = getCommandBuffer(CommandBuffer::genBuffers);
    cmd.write(n);
    blockMainThreadAndWaitResultFromGLThread();
    for (GLsizei i = 0; i < n; ++i)
    {
        buffers[i] = __intSyncCommandReturn[i];
    }
}

void glGenerateMipmap(GLenum target)
{
    auto& cmd = getCommandBuffer(CommandBuffer::generateMipmap);
    cmd.write(target);
}

void glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
    auto& cmd = getCommandBuffer(CommandBuffer::genFramebuffers);
    cmd.write(n);
    blockMainThreadAndWaitResultFromGLThread();
    for (GLsizei i = 0; i < n; ++i)
    {
        framebuffers[i] = __intSyncCommandReturn[i];
    }
}

void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
    auto& cmd = getCommandBuffer(CommandBuffer::genRenderbuffers);
    cmd.write(n);
    blockMainThreadAndWaitResultFromGLThread();
    for (GLsizei i = 0; i < n; ++i)
    {
        renderbuffers[i] = __intSyncCommandReturn[i];
    }
}

void glGenTextures(GLsizei n, GLuint* textures)
{
    auto& cmd = getCommandBuffer(CommandBuffer::genTextures);
    cmd.write(n);
    blockMainThreadAndWaitResultFromGLThread();
    for (GLsizei i = 0; i < n; ++i)
    {
        textures[i] = __intSyncCommandReturn[i];
    }
}

void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getActiveAttrib);
    cmd.write(program);
    cmd.write(index);
    cmd.write(bufsize);

    blockMainThreadAndWaitResultFromGLThread();
    if (length)
    {
        *length = (GLsizei)__intSyncCommandReturn[0];
    }

    if (size)
    {
        *size = __intSyncCommandReturn[1];
    }

    if (type)
    {
        *type = (GLenum)__intSyncCommandReturn[2];
    }

    assert(bufsize > __strSyncCommandReturn.length());
    strncpy(name, __strSyncCommandReturn.c_str(), __strSyncCommandReturn.length() + 1);
}

void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getActiveUniform);
    cmd.write(program);
    cmd.write(index);
    cmd.write(bufsize);

    blockMainThreadAndWaitResultFromGLThread();
    if (length)
    {
        *length = (GLsizei)__intSyncCommandReturn[0];
    }

    if (size)
    {
        *size = __intSyncCommandReturn[1];
    }

    if (type)
    {
        *type = (GLenum)__intSyncCommandReturn[2];
    }

    assert(bufsize > __strSyncCommandReturn.length());
    strncpy(name, __strSyncCommandReturn.c_str(), __strSyncCommandReturn.length()+1);
}

void glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getAttachedShaders);
    cmd.write(program);
    cmd.write(maxcount);
    blockMainThreadAndWaitResultFromGLThread();
    GLsizei realCount = (GLsizei)__intSyncCommandReturn[0];;
    if (count)
    {
        *count = realCount;
    }

    if (shaders)
    {
        for (GLsizei i = 0; i < realCount; ++i)
        {
            shaders[i] = (GLuint)__intSyncCommandReturn[i+1];
        }
    }
}

GLint glGetAttribLocation(GLuint program, const GLchar* name)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getAttribLocation);
    cmd.write(program);
    const Memory* m = bgfx::copy(name, (uint32_t)strlen(name) + 1);
    cmd.write(m);
    blockMainThreadAndWaitResultFromGLThread();

    return __intSyncCommandReturn[0];
}

void glGetBooleanv(GLenum pname, GLboolean* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getBooleanv);
    cmd.write(pname);
    assert(false);//cjh
}

void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getBufferParameteriv);
    assert(false);//cjh
}

GLenum glGetError()
{
    getCommandBuffer(CommandBuffer::getError);
    blockMainThreadAndWaitResultFromGLThread();
    return (GLenum)__intSyncCommandReturn[0];
}

void glGetFloatv(GLenum pname, GLfloat* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getFloatv);
    assert(false);//cjh
}

void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getFramebufferAttachmentParameteriv);
    assert(false);//cjh
}

void glGetIntegerv(GLenum pname, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getIntegerv);
    cmd.write(pname);
    blockMainThreadAndWaitResultFromGLThread();
    if (params)
    {
        *params = __intSyncCommandReturn[0];
    }
}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getProgramiv);
    cmd.write(program);
    cmd.write(pname);
    blockMainThreadAndWaitResultFromGLThread();
    if (params)
    {
        *params = __intSyncCommandReturn[0];
    }
}

void glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getProgramInfoLog);
    cmd.write(program);
    cmd.write(bufsize);
    blockMainThreadAndWaitResultFromGLThread();
    GLsizei infoLogLen = __intSyncCommandReturn[0];
    if (length)
    {
        *length = infoLogLen;
    }
    if (infolog)
    {
        assert(infoLogLen == __strSyncCommandReturn.length());
        assert(bufsize > __strSyncCommandReturn.length());
        strncpy(infolog, __strSyncCommandReturn.c_str(), __strSyncCommandReturn.length()+1);
    }
}

void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getRenderbufferParameteriv);
    assert(false);
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getShaderiv);
    cmd.write(shader);
    cmd.write(pname);
    blockMainThreadAndWaitResultFromGLThread();
    if (params)
    {
        *params = __intSyncCommandReturn[0];
    }
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getShaderInfoLog);
    cmd.write(shader);
    cmd.write(bufsize);
    blockMainThreadAndWaitResultFromGLThread();
    GLsizei infoLogLen = __intSyncCommandReturn[0];
    if (length)
    {
        *length = infoLogLen;
    }
    if (infolog)
    {
        assert(infoLogLen == __strSyncCommandReturn.length());
        assert(bufsize > __strSyncCommandReturn.length());
        strncpy(infolog, __strSyncCommandReturn.c_str(), __strSyncCommandReturn.length()+1);
    }
}

void glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getShaderSource);
    cmd.write(shader);
    cmd.write(bufsize);
    blockMainThreadAndWaitResultFromGLThread();
    GLsizei sourceLen = __intSyncCommandReturn[0];
    if (length)
    {
        *length = sourceLen;
    }
    if (source)
    {
        assert(sourceLen == __strSyncCommandReturn.length());
        assert(bufsize > __strSyncCommandReturn.length());
        strncpy(source, __strSyncCommandReturn.c_str(), __strSyncCommandReturn.length()+1);
    }
}

const GLubyte* glGetString(GLenum name)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getString);
    cmd.write(name);
    blockMainThreadAndWaitResultFromGLThread();
    static std::string str;
    str = __strSyncCommandReturn;
    return (const GLubyte*)str.c_str();
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getTexParameterfv);
    cmd.write(target);
    cmd.write(pname);
    blockMainThreadAndWaitResultFromGLThread();
    if (params)
    {
        *params = __floatSyncCommandReturn[0];
    }
}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getTexParameteriv);
    cmd.write(target);
    cmd.write(pname);
    blockMainThreadAndWaitResultFromGLThread();
    if (params)
    {
        *params = __intSyncCommandReturn[0];
    }
}

void glGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getUniformfv);
    cmd.write(program);
    cmd.write(location);
    cmd.write(params);
    blockMainThreadAndWaitResultFromGLThread();
}

void glGetUniformiv(GLuint program, GLint location, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getUniformiv);
    cmd.write(program);
    cmd.write(location);
    cmd.write(params);
    blockMainThreadAndWaitResultFromGLThread();
}

GLint glGetUniformLocation(GLuint program, const GLchar* name)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getUniformLocation);
    cmd.write(program);
    cmd.write(name);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getVertexAttribfv);
    cmd.write(index);
    cmd.write(pname);
    cmd.write(params);
    blockMainThreadAndWaitResultFromGLThread();
}

void glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getVertexAttribiv);
    cmd.write(index);
    cmd.write(pname);
    cmd.write(params);
    blockMainThreadAndWaitResultFromGLThread();
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer)
{
    auto& cmd = getCommandBuffer(CommandBuffer::getVertexAttribPointerv);
    cmd.write(index);
    cmd.write(pname);
    cmd.write(pointer);
    blockMainThreadAndWaitResultFromGLThread();
}

void glHint(GLenum target, GLenum mode)
{
    auto& cmd = getCommandBuffer(CommandBuffer::hint);
    cmd.write(target);
    cmd.write(mode);
}

GLboolean glIsBuffer(GLuint buffer)
{
    auto& cmd = getCommandBuffer(CommandBuffer::isBuffer);
    cmd.write(buffer);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

GLboolean glIsEnabled(GLenum cap)
{
    auto& cmd = getCommandBuffer(CommandBuffer::isEnabled);
    cmd.write(cap);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

GLboolean glIsFramebuffer(GLuint framebuffer)
{
    auto& cmd = getCommandBuffer(CommandBuffer::isFramebuffer);
    cmd.write(framebuffer);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

GLboolean glIsProgram(GLuint program)
{
    auto& cmd = getCommandBuffer(CommandBuffer::isProgram);
    cmd.write(program);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

GLboolean glIsRenderbuffer(GLuint renderbuffer)
{
    auto& cmd = getCommandBuffer(CommandBuffer::isRenderbuffer);
    cmd.write(renderbuffer);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

GLboolean glIsShader(GLuint shader)
{
    auto& cmd = getCommandBuffer(CommandBuffer::isShader);
    cmd.write(shader);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

GLboolean glIsTexture(GLuint texture)
{
    auto& cmd = getCommandBuffer(CommandBuffer::isTexture);
    cmd.write(texture);
    blockMainThreadAndWaitResultFromGLThread();
    return __intSyncCommandReturn[0];
}

void glLineWidth(GLfloat width)
{
    auto& cmd = getCommandBuffer(CommandBuffer::lineWidth);
    cmd.write(width);
}

void glLinkProgram(GLuint program)
{
    auto& cmd = getCommandBuffer(CommandBuffer::linkProgram);
    cmd.write(program);
}

void glPixelStorei(GLenum pname, GLint param)
{
    auto& cmd = getCommandBuffer(CommandBuffer::pixelStorei);
    cmd.write(pname);
    cmd.write(param);
}

void glPolygonOffset(GLfloat factor, GLfloat units)
{
    auto& cmd = getCommandBuffer(CommandBuffer::polygonOffset);
    cmd.write(factor);
    cmd.write(units);
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
{
    auto& cmd = getCommandBuffer(CommandBuffer::readPixels);
    cmd.write(x);
    cmd.write(y);
    cmd.write(width);
    cmd.write(height);
    cmd.write(format);
    cmd.write(type);
    cmd.write(pixels);
    blockMainThreadAndWaitResultFromGLThread();
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    auto& cmd = getCommandBuffer(CommandBuffer::renderbufferStorage);
    cmd.write(target);
    cmd.write(internalformat);
    cmd.write(width);
    cmd.write(height);
}

void glSampleCoverage(GLclampf value, GLboolean invert)
{
    auto& cmd = getCommandBuffer(CommandBuffer::sampleCoverage);
    cmd.write(value);
    cmd.write(invert);
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    auto& cmd = getCommandBuffer(CommandBuffer::scissor);
    cmd.write(x);
    cmd.write(y);
    cmd.write(width);
    cmd.write(height);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar* const *string, const GLint* length)
{
    assert(count == 1);
    assert(length == nullptr);
    assert(string != nullptr && string[0] != nullptr);
    auto& cmd = getCommandBuffer(CommandBuffer::shaderSource);
    cmd.write(shader);
    cmd.write(count);
    const Memory* m = bgfx::copy(string[0], (uint32_t)strlen(string[0]) + 1);
    cmd.write(m);
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
    auto& cmd = getCommandBuffer(CommandBuffer::stencilFunc);
    cmd.write(func);
    cmd.write(ref);
    cmd.write(mask);
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
    auto& cmd = getCommandBuffer(CommandBuffer::stencilFuncSeparate);
    cmd.write(face);
    cmd.write(func);
    cmd.write(ref);
    cmd.write(mask);
}

void glStencilMask(GLuint mask)
{
    auto& cmd = getCommandBuffer(CommandBuffer::stencilMask);
    cmd.write(mask);
}

void glStencilMaskSeparate(GLenum face, GLuint mask)
{
    auto& cmd = getCommandBuffer(CommandBuffer::stencilMaskSeparate);
    cmd.write(face);
    cmd.write(mask);
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
    auto& cmd = getCommandBuffer(CommandBuffer::stencilOp);
    cmd.write(fail);
    cmd.write(zfail);
    cmd.write(zpass);
}

void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
    auto& cmd = getCommandBuffer(CommandBuffer::stencilOpSeparate);
    cmd.write(face);
    cmd.write(fail);
    cmd.write(zfail);
    cmd.write(zpass);
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
    auto& cmd = getCommandBuffer(CommandBuffer::texImage2D);
    cmd.write(target);
    cmd.write(level);
    cmd.write(internalformat);
    cmd.write(width);
    cmd.write(height);
    cmd.write(border);
    cmd.write(format);
    cmd.write(type);
    cmd.write(pixels);
    blockMainThreadAndWaitResultFromGLThread();
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
    auto& cmd = getCommandBuffer(CommandBuffer::texParameterf);
    cmd.write(target);
    cmd.write(pname);
    cmd.write(param);
}

void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
    assert(false);//cjh
    auto& cmd = getCommandBuffer(CommandBuffer::texParameterfv);
    cmd.write(target);
    cmd.write(pname);
}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
    auto& cmd = getCommandBuffer(CommandBuffer::texParameteri);
    cmd.write(target);
    cmd.write(pname);
    cmd.write(param);
}

void glTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
    assert(false); //cjh
    auto& cmd = getCommandBuffer(CommandBuffer::texParameteriv);
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
{
    auto& cmd = getCommandBuffer(CommandBuffer::texSubImage2D);
    cmd.write(target);
    cmd.write(level);
    cmd.write(xoffset);
    cmd.write(yoffset);
    cmd.write(width);
    cmd.write(height);
    cmd.write(format);
    cmd.write(type);
    cmd.write(pixels);
    blockMainThreadAndWaitResultFromGLThread();
}

void glUniform1f(GLint location, GLfloat x)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform1f);
    cmd.write(location);
    cmd.write(x);
}

void glUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform1fv);
    cmd.write(location);
    cmd.write(count);
    const Memory* m = bgfx::copy(v, count * sizeof(GLfloat));
    cmd.write(m);
}

void glUniform1i(GLint location, GLint x)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform1i);
    cmd.write(location);
    cmd.write(x);
}

void glUniform1iv(GLint location, GLsizei count, const GLint* v)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform1iv);
    cmd.write(location);
    cmd.write(count);
    const Memory* m = bgfx::copy(v, count * sizeof(GLint));
    cmd.write(m);
}

void glUniform2f(GLint location, GLfloat x, GLfloat y)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform2f);
    cmd.write(location);
    cmd.write(x);
    cmd.write(y);
}

void glUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform2fv);
    cmd.write(location);
    cmd.write(count);
    const Memory* m = bgfx::copy(v, count * sizeof(GLfloat) * 2);
    cmd.write(m);
}

void glUniform2i(GLint location, GLint x, GLint y)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform2i);
    cmd.write(location);
    cmd.write(x);
    cmd.write(y);
}

void glUniform2iv(GLint location, GLsizei count, const GLint* v)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform2iv);
    cmd.write(location);
    cmd.write(count);
    const Memory* m = bgfx::copy(v, count * sizeof(GLint) * 2);
    cmd.write(m);
}

void glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform3f);
    cmd.write(location);
    cmd.write(x);
    cmd.write(y);
    cmd.write(z);
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform3fv);
    cmd.write(location);
    cmd.write(count);
    const Memory* m = bgfx::copy(v, count * sizeof(GLfloat) * 3);
    cmd.write(m);
}

void glUniform3i(GLint location, GLint x, GLint y, GLint z)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform3i);
    cmd.write(location);
    cmd.write(x);
    cmd.write(y);
    cmd.write(z);
}

void glUniform3iv(GLint location, GLsizei count, const GLint* v)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform3iv);
    cmd.write(location);
    cmd.write(count);
    const Memory* m = bgfx::copy(v, count * sizeof(GLint) * 3);
    cmd.write(m);
}

void glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform4f);
    cmd.write(location);
    cmd.write(x);
    cmd.write(y);
    cmd.write(z);
    cmd.write(w);
}

void glUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform4fv);
    cmd.write(location);
    cmd.write(count);
    const Memory* m = bgfx::copy(v, count * sizeof(GLfloat) * 4);
    cmd.write(m);
}

void glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform4i);
    cmd.write(location);
    cmd.write(x);
    cmd.write(y);
    cmd.write(z);
    cmd.write(w);
}

void glUniform4iv(GLint location, GLsizei count, const GLint* v)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniform4iv);
    cmd.write(location);
    cmd.write(count);
    const Memory* m = bgfx::copy(v, count * sizeof(GLint) * 4);
    cmd.write(m);
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniformMatrix2fv);
    cmd.write(location);
    cmd.write(count);
    cmd.write(transpose);
    const Memory* m = bgfx::copy(value, count * sizeof(GLfloat) * 4);
    cmd.write(m);
}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniformMatrix3fv);
    cmd.write(location);
    cmd.write(count);
    cmd.write(transpose);
    const Memory* m = bgfx::copy(value, count * sizeof(GLfloat) * 9);
    cmd.write(m);
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    auto& cmd = getCommandBuffer(CommandBuffer::uniformMatrix4fv);
    cmd.write(location);
    cmd.write(count);
    cmd.write(transpose);
    const Memory* m = bgfx::copy(value, count * sizeof(GLfloat) * 16);
    cmd.write(m);
}

void glUseProgram(GLuint program)
{
    auto& cmd = getCommandBuffer(CommandBuffer::useProgram);
    cmd.write(program);
}

void glValidateProgram(GLuint program)
{
    auto& cmd = getCommandBuffer(CommandBuffer::validateProgram);
    cmd.write(program);
}

void glVertexAttrib1f(GLuint index, GLfloat x)
{
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttrib1f);
    cmd.write(index);
    cmd.write(x);
}

void glVertexAttrib1fv(GLuint index, const GLfloat* values)
{
    assert(false);//cjh
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttrib1fv);
}

void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttrib2f);
    cmd.write(index);
    cmd.write(x);
    cmd.write(y);
}

void glVertexAttrib2fv(GLuint index, const GLfloat* values)
{
    assert(false);//cjh
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttrib2fv);
}

void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttrib3f);
    cmd.write(index);
    cmd.write(x);
    cmd.write(y);
    cmd.write(z);
}

void glVertexAttrib3fv(GLuint index, const GLfloat* values)
{
    assert(false);//cjh
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttrib3fv);
}

void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttrib4f);
    cmd.write(index);
    cmd.write(x);
    cmd.write(y);
    cmd.write(z);
    cmd.write(w);
}

void glVertexAttrib4fv(GLuint index, const GLfloat* values)
{
    assert(false);//cjh
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttrib4fv);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
    auto& cmd = getCommandBuffer(CommandBuffer::vertexAttribPointer);
    cmd.write(index);
    cmd.write(size);
    cmd.write(type);
    cmd.write(normalized);
    cmd.write(stride);
    cmd.write(ptr);
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    auto& cmd = getCommandBuffer(CommandBuffer::viewport);
    cmd.write(x);
    cmd.write(y);
    cmd.write(width);
    cmd.write(height);
}

void glDrawBuffer(GLenum mode)
{
    auto& cmd = getCommandBuffer(CommandBuffer::drawBuffer);
    cmd.write(mode);
}

void glReadBuffer(GLenum mode)
{
    auto& cmd = getCommandBuffer(CommandBuffer::readBuffer);
    cmd.write(mode);
}



} // namespace fakegl {

