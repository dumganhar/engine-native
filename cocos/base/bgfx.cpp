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

static WebGLContext* s_ctx = NULL;
static bool s_renderFrameCalled = false;

RenderFrame::Enum renderFrame(int32_t _msecs)
{
    if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
    {
        if (NULL == s_ctx)
        {
            s_renderFrameCalled = true;
            s_threadIndex = ~BGFX_API_THREAD_MAGIC;
            return RenderFrame::NoContext;
        }

        BGFX_CHECK_RENDER_THREAD();
        int32_t msecs = -1 == _msecs
        ? BGFX_CONFIG_API_SEMAPHORE_TIMEOUT
        : _msecs
        ;
        RenderFrame::Enum result = s_ctx->renderFrame(msecs);
        if (RenderFrame::Exiting == result)
        {
            WebGLContext* ctx = s_ctx;
            ctx->apiSemWait();
            s_ctx = NULL;
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
    return s_ctx->frame(_capture);
}

} // namespace bgfx
