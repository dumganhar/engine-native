#include "bgfx.h"
#include "bgfx_platform.h"
#include "bgfx_config.h"
#include "bx/bx.h"
#include "WebGLContext.h"

namespace bgfx {

#define BGFX_API_THREAD_MAGIC UINT32_C(0x78666762)

#if BGFX_CONFIG_MULTITHREADED
#    define BGFX_CHECK_API_THREAD() \
BX_CHECK(NULL != s_ctx, "Library is not initialized yet."); \
BX_CHECK(BGFX_API_THREAD_MAGIC == s_threadIndex, "Must be called from main thread.")
#    define BGFX_CHECK_RENDER_THREAD() BX_CHECK(BGFX_API_THREAD_MAGIC != s_threadIndex, "Must be called from render thread.")
#else
#    define BGFX_CHECK_API_THREAD()
#    define BGFX_CHECK_RENDER_THREAD()
#endif // BGFX_CONFIG_MULTITHREADED

#ifndef BGFX_CONFIG_MEMORY_TRACKING
#    define BGFX_CONFIG_MEMORY_TRACKING (BGFX_CONFIG_DEBUG && BX_CONFIG_SUPPORTS_THREADING)
#endif // BGFX_CONFIG_MEMORY_TRACKING

    struct CallbackStub : public CallbackI
    {
        virtual ~CallbackStub()
        {
        }

        virtual void fatal(Fatal::Enum _code, const char* _str) override
        {
            if (Fatal::DebugCheck == _code)
            {
                bx::debugBreak();
            }
            else
            {
                BX_TRACE("0x%08x: %s", _code, _str);
                BX_UNUSED(_code, _str);
                abort();
            }
        }

        virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
        {
            char temp[2048];
            char* out = temp;
            va_list argListCopy;
            va_copy(argListCopy, _argList);
            int32_t len   = bx::snprintf(out, sizeof(temp), "%s (%d): ", _filePath, _line);
            int32_t total = len + bx::vsnprintf(out + len, sizeof(temp)-len, _format, argListCopy);
            va_end(argListCopy);
            if ( (int32_t)sizeof(temp) < total)
            {
                out = (char*)alloca(total+1);
                bx::memCopy(out, temp, len);
                bx::vsnprintf(out + len, total-len, _format, _argList);
            }
            out[total] = '\0';
            bx::debugOutput(out);
        }

        virtual void profilerBegin(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
        {
        }

        virtual void profilerBeginLiteral(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
        {
        }

        virtual void profilerEnd() override
        {
        }

        virtual uint32_t cacheReadSize(uint64_t /*_id*/) override
        {
            return 0;
        }

        virtual bool cacheRead(uint64_t /*_id*/, void* /*_data*/, uint32_t /*_size*/) override
        {
            return false;
        }

        virtual void cacheWrite(uint64_t /*_id*/, const void* /*_data*/, uint32_t /*_size*/) override
        {
        }

        virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip) override
        {
            BX_UNUSED(_filePath, _width, _height, _pitch, _data, _size, _yflip);

            const int32_t len = bx::strLen(_filePath)+5;
            char* filePath = (char*)alloca(len);
            bx::strCopy(filePath, len, _filePath);
            bx::strCat(filePath, len, ".tga");

//cjh            bx::FileWriter writer;
//            if (bx::open(&writer, filePath) )
//            {
//                bimg::imageWriteTga(&writer, _width, _height, _pitch, _data, false, _yflip);
//                bx::close(&writer);
//            }
        }

        virtual void captureBegin(uint32_t /*_width*/, uint32_t /*_height*/, uint32_t /*_pitch*/, TextureFormat::Enum /*_format*/, bool /*_yflip*/) override
        {
            BX_TRACE("Warning: using capture without callback (a.k.a. pointless).");
        }

        virtual void captureEnd() override
        {
        }

        virtual void captureFrame(const void* /*_data*/, uint32_t /*_size*/) override
        {
        }
    };

    const size_t kNaturalAlignment = 8;

    class AllocatorStub : public bx::AllocatorI
    {
    public:
        AllocatorStub()
#if BGFX_CONFIG_MEMORY_TRACKING
        : m_numBlocks(0)
        , m_maxBlocks(0)
#endif // BGFX_CONFIG_MEMORY_TRACKING
        {
        }

        virtual void* realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line) override
        {
            if (0 == _size)
            {
                if (NULL != _ptr)
                {
                    if (kNaturalAlignment >= _align)
                    {
#if BGFX_CONFIG_MEMORY_TRACKING
                        {
                            bx::MutexScope scope(m_mutex);
                            BX_CHECK(m_numBlocks > 0, "Number of blocks is 0. Possible alloc/free mismatch?");
                            --m_numBlocks;
                        }
#endif // BGFX_CONFIG_MEMORY_TRACKING

                        ::free(_ptr);
                    }
                    else
                    {
                        bx::alignedFree(this, _ptr, _align, _file, _line);
                    }
                }

                return NULL;
            }
            else if (NULL == _ptr)
            {
                if (kNaturalAlignment >= _align)
                {
#if BGFX_CONFIG_MEMORY_TRACKING
                    {
                        bx::MutexScope scope(m_mutex);
                        ++m_numBlocks;
                        m_maxBlocks = bx::max(m_maxBlocks, m_numBlocks);
                    }
#endif // BGFX_CONFIG_MEMORY_TRACKING

                    return ::malloc(_size);
                }

                return bx::alignedAlloc(this, _size, _align, _file, _line);
            }

            if (kNaturalAlignment >= _align)
            {
#if BGFX_CONFIG_MEMORY_TRACKING
                if (NULL == _ptr)
                {
                    bx::MutexScope scope(m_mutex);
                    ++m_numBlocks;
                    m_maxBlocks = bx::max(m_maxBlocks, m_numBlocks);
                }
#endif // BGFX_CONFIG_MEMORY_TRACKING

                return ::realloc(_ptr, _size);
            }

            return bx::alignedRealloc(this, _ptr, _size, _align, _file, _line);
        }

        void checkLeaks();

    protected:
#if BGFX_CONFIG_MEMORY_TRACKING
        bx::Mutex m_mutex;
        uint32_t m_numBlocks;
        uint32_t m_maxBlocks;
#endif // BGFX_CONFIG_MEMORY_TRACKING
    };

    static CallbackStub*  s_callbackStub  = NULL;
    static AllocatorStub* s_allocatorStub = NULL;
    static bool s_graphicsDebuggerPresent = false;

    CallbackI* g_callback = NULL;
    bx::AllocatorI* g_allocator = NULL;

    Caps g_caps;

#if BGFX_CONFIG_MULTITHREADED && !defined(BX_THREAD_LOCAL)
    class ThreadData
    {
        BX_CLASS(ThreadData
                 , NO_COPY
                 , NO_ASSIGNMENT
                 );

    public:
        ThreadData(uintptr_t _rhs)
        {
            union { uintptr_t ui; void* ptr; } cast = { _rhs };
            m_tls.set(cast.ptr);
        }

        operator uintptr_t() const
        {
            union { uintptr_t ui; void* ptr; } cast;
            cast.ptr = m_tls.get();
            return cast.ui;
        }

        uintptr_t operator=(uintptr_t _rhs)
        {
            union { uintptr_t ui; void* ptr; } cast = { _rhs };
            m_tls.set(cast.ptr);
            return _rhs;
        }

        bool operator==(uintptr_t _rhs) const
        {
            uintptr_t lhs = *this;
            return lhs == _rhs;
        }

    private:
        bx::TlsData m_tls;
    };

static ThreadData s_threadIndex(0);
#elif !BGFX_CONFIG_MULTITHREADED
static uint32_t s_threadIndex(0);
#else
static BX_THREAD_LOCAL uint32_t s_threadIndex(0);
#endif

bool s_renderFrameCalled = false;

RenderFrame::Enum renderFrame(int32_t _msecs)
{
    if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
    {
        if (NULL == WebGLContext::s_ctx)
        {
//cjh            s_renderFrameCalled = true;
//            s_threadIndex = ~BGFX_API_THREAD_MAGIC;
            return RenderFrame::NoContext;
        }

        BGFX_CHECK_RENDER_THREAD();
        int32_t msecs = -1 == _msecs
        ? BGFX_CONFIG_API_SEMAPHORE_TIMEOUT
        : _msecs
        ;
        RenderFrame::Enum result = WebGLContext::s_ctx->renderFrame(msecs);
        if (RenderFrame::Exiting == result)
        {
            WebGLContext* ctx = WebGLContext::s_ctx;
            ctx->apiSemWait();
            WebGLContext::s_ctx = NULL;
            ctx->renderSemPost();
        }

        return result;
    }

    BX_CHECK(false, "This call only makes sense if used with multi-threaded renderer.");
    return RenderFrame::NoContext;
}

uint32_t frame(bool _capture)
{
    BGFX_CHECK_API_THREAD();
    return WebGLContext::s_ctx->frame(_capture);
}

    Resolution::Resolution()
    : width(1280)
    , height(720)
//cjh    , reset(BGFX_RESET_NONE)
    {
    }

    Init::Init()
    : type(RendererType::Count)
//cjh    , vendorId(BGFX_PCI_ID_NONE)
    , deviceId(0)
    , callback(NULL)
    , allocator(NULL)
    {
//cjh        limits.maxEncoders     = BGFX_CONFIG_DEFAULT_MAX_ENCODERS;
//        limits.transientVbSize = BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE;
//        limits.transientIbSize = BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE;
    }

    bool init(const Init& _init)
    {
        if (NULL != WebGLContext::s_ctx)
        {
            BX_TRACE("bgfx is already initialized.");
            return false;
        }

        struct ErrorState
        {
            enum Enum
            {
                Default,
                ContextAllocated,
            };
        };

        ErrorState::Enum errorState = ErrorState::Default;

        if (NULL != _init.allocator)
        {
            g_allocator = _init.allocator;
        }
        else
        {
            bx::DefaultAllocator allocator;
            g_allocator =
            s_allocatorStub = BX_NEW(&allocator, AllocatorStub);
        }

        if (NULL != _init.callback)
        {
            g_callback = _init.callback;
        }
        else
        {
            g_callback =
            s_callbackStub = BX_NEW(g_allocator, CallbackStub);
        }

//        if (true
//            &&  !BX_ENABLED(BX_PLATFORM_EMSCRIPTEN || BX_PLATFORM_PS4)
//            &&  RendererType::Noop != _init.type
////cjh            &&  NULL == g_platformData.ndt
////            &&  NULL == g_platformData.nwh
////            &&  NULL == g_platformData.context
////            &&  NULL == g_platformData.backBuffer
////            &&  NULL == g_platformData.backBufferDS
//            )
//        {
//            BX_TRACE("bgfx platform data like window handle or backbuffer must be set.");
//            goto error;
//        }

        bx::memSet(&g_caps, 0, sizeof(g_caps) );
        g_caps.limits.maxDrawCalls            = BGFX_CONFIG_MAX_DRAW_CALLS;
        g_caps.limits.maxBlits                = BGFX_CONFIG_MAX_BLIT_ITEMS;
        g_caps.limits.maxTextureSize          = 0;
        g_caps.limits.maxTextureLayers        = 1;
        g_caps.limits.maxViews                = BGFX_CONFIG_MAX_VIEWS;
        g_caps.limits.maxFrameBuffers         = BGFX_CONFIG_MAX_FRAME_BUFFERS;
        g_caps.limits.maxPrograms             = BGFX_CONFIG_MAX_PROGRAMS;
        g_caps.limits.maxShaders              = BGFX_CONFIG_MAX_SHADERS;
        g_caps.limits.maxTextures             = BGFX_CONFIG_MAX_TEXTURES;
        g_caps.limits.maxTextureSamplers      = BGFX_CONFIG_MAX_TEXTURE_SAMPLERS;
        g_caps.limits.maxVertexDecls          = BGFX_CONFIG_MAX_VERTEX_DECLS;
        g_caps.limits.maxVertexStreams        = 1;
        g_caps.limits.maxIndexBuffers         = BGFX_CONFIG_MAX_INDEX_BUFFERS;
        g_caps.limits.maxVertexBuffers        = BGFX_CONFIG_MAX_VERTEX_BUFFERS;
        g_caps.limits.maxDynamicIndexBuffers  = BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS;
        g_caps.limits.maxDynamicVertexBuffers = BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS;
        g_caps.limits.maxUniforms             = BGFX_CONFIG_MAX_UNIFORMS;
        g_caps.limits.maxOcclusionQueries     = BGFX_CONFIG_MAX_OCCLUSION_QUERIES;
        g_caps.limits.maxFBAttachments        = 1;
        g_caps.limits.maxEncoders             = (0 != BGFX_CONFIG_MULTITHREADED) ? _init.limits.maxEncoders : 1;
        g_caps.limits.transientVbSize         = _init.limits.transientVbSize;
        g_caps.limits.transientIbSize         = _init.limits.transientIbSize;

        g_caps.vendorId = _init.vendorId;
        g_caps.deviceId = _init.deviceId;

        BX_TRACE("Init...");

        errorState = ErrorState::ContextAllocated;

        WebGLContext::s_ctx = BX_ALIGNED_NEW(g_allocator, WebGLContext, 64);
        if (WebGLContext::s_ctx->init(_init) )
        {
            BX_TRACE("Init complete.");
            return true;
        }

    error:
        BX_TRACE("Init failed.");

        switch (errorState)
        {
            case ErrorState::ContextAllocated:
                BX_ALIGNED_DELETE(g_allocator, WebGLContext::s_ctx, 64);
                WebGLContext::s_ctx = NULL;
                BX_FALLTHROUGH;

            case ErrorState::Default:
                if (NULL != s_callbackStub)
                {
                    BX_DELETE(g_allocator, s_callbackStub);
                    s_callbackStub = NULL;
                }

                if (NULL != s_allocatorStub)
                {
                    bx::DefaultAllocator allocator;
                    BX_DELETE(&allocator, s_allocatorStub);
                    s_allocatorStub = NULL;
                }

                s_threadIndex = 0;
                g_callback    = NULL;
                g_allocator   = NULL;
                break;
        }

        return false;
    }

    bool init(RendererType::Enum _type, uint16_t _vendorId, uint16_t _deviceId, CallbackI* _callback, bx::AllocatorI* _allocator)
    {
        Init in;

        in.type      = _type;
        in.vendorId  = _vendorId;
        in.deviceId  = _deviceId;
        in.callback  = _callback;
        in.allocator = _allocator;

        return init(in);
    }

    void shutdown()
    {
        BX_TRACE("Shutdown...");

        BGFX_CHECK_API_THREAD();
        WebGLContext* ctx = WebGLContext::s_ctx; // it's going to be NULLd inside shutdown.
        ctx->shutdown();
        BX_CHECK(NULL == s_ctx, "bgfx is should be uninitialized here.");

        BX_ALIGNED_DELETE(g_allocator, ctx, 16);

        BX_TRACE("Shutdown complete.");

        if (NULL != s_allocatorStub)
        {
            s_allocatorStub->checkLeaks();
        }

        if (NULL != s_callbackStub)
        {
            BX_DELETE(g_allocator, s_callbackStub);
            s_callbackStub = NULL;
        }

        if (NULL != s_allocatorStub)
        {
            bx::DefaultAllocator allocator;
            BX_DELETE(&allocator, s_allocatorStub);
            s_allocatorStub = NULL;
        }

        s_threadIndex = 0;
        g_callback    = NULL;
        g_allocator   = NULL;
    }

    void reset(uint32_t _width, uint32_t _height, uint32_t _flags)
    {
        BGFX_CHECK_API_THREAD();
        BX_CHECK(0 == (_flags&BGFX_RESET_RESERVED_MASK), "Do not set reset reserved flags!");
        WebGLContext::s_ctx->reset(_width, _height, _flags);
    }

    void clear(GLbitfield mask)
    {
        BGFX_CHECK_API_THREAD();
        WebGLContext::s_ctx->clear(mask);
    }

    void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {
        BGFX_CHECK_API_THREAD();
        WebGLContext::s_ctx->clearColor(red, green, blue, alpha);
    }

    GLuint createBuffer()
    {
        BGFX_CHECK_API_THREAD();
        return WebGLContext::s_ctx->createBuffer();
    }

} // namespace bgfx
