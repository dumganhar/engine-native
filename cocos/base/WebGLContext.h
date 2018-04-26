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

#include "base/FakeGL.h"

#include "bx/platform.h"
#include "bx/thread.h"
#include "bx/timer.h"

#include "bgfx.h"
#include "bgfx_p.h"
#include "bgfx_platform.h"

#include "WebGLCommandBuffer.h"
#include "WebGLFrame.h"


namespace bgfx {

class WebGLRenderContext;

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

    // WEBGL API BEGIN
    void activeTexture(GLenum texture);
    void attachShader(GLuint program, GLuint shader);
    void bindAttribLocation(GLuint program, GLuint index, const GLchar* name);
    void bindBuffer(GLenum target, GLuint buffer);
    void bindFramebuffer(GLenum target, GLuint framebuffer);
    void bindRenderbuffer(GLenum target, GLuint renderbuffer);
    void bindTexture(GLenum target, GLuint texture);
    void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void blendEquation(GLenum mode);
    void blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
    void blendFunc(GLenum sfactor, GLenum dfactor);
    void blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
    void bufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
    void bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
    GLenum checkFramebufferStatus(GLenum target);
    void clear(GLbitfield mask);
    void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void clearDepthf(GLclampf depth);
    void clearStencil(GLint s);
    void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    void compileShader(GLuint shader);
    void compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
    void compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
    void copyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
    void copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    GLuint createProgram(void);
    GLuint createShader(GLenum type);
    void cullFace(GLenum mode);
    void deleteBuffers(GLsizei n, const GLuint* buffers);
    void deleteFramebuffers(GLsizei n, const GLuint* framebuffers);
    void deleteProgram(GLuint program);
    void deleteRenderbuffers(GLsizei n, const GLuint* renderbuffers);
    void deleteShader(GLuint shader);
    void deleteTextures(GLsizei n, const GLuint* textures);
    void depthFunc(GLenum func);
    void depthMask(GLboolean flag);
    void depthRangef(GLclampf zNear, GLclampf zFar);
    void detachShader(GLuint program, GLuint shader);
    void disable(GLenum cap);
    void disableVertexAttribArray(GLuint index);
    void drawArrays(GLenum mode, GLint first, GLsizei count);
    void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
    void enable(GLenum cap);
    void enableVertexAttribArray(GLuint index);
    void finish(void);
    void flush(void);
    void framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
    void framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    void frontFace(GLenum mode);
    void genBuffers(GLsizei n, GLuint* buffers);
    void generateMipmap(GLenum target);
    void genFramebuffers(GLsizei n, GLuint* framebuffers);
    void genRenderbuffers(GLsizei n, GLuint* renderbuffers);
    void genTextures(GLsizei n, GLuint* textures);
    void getActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
    void getActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
    void getAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
    int  getAttribLocation(GLuint program, const GLchar* name);
    void getBooleanv(GLenum pname, GLboolean* params);
    void getBufferParameteriv(GLenum target, GLenum pname, GLint* params);
    GLenum getError(void);
    void getFloatv(GLenum pname, GLfloat* params);
    void getFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params);
    void getIntegerv(GLenum pname, GLint* params);
    void getProgramiv(GLuint program, GLenum pname, GLint* params);
    void getProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    void getRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params);
    void getShaderiv(GLuint shader, GLenum pname, GLint* params);
    void getShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    void getShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
    void getShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
    const GLubyte* getString(GLenum name);
    void getTexParameterfv(GLenum target, GLenum pname, GLfloat* params);
    void getTexParameteriv(GLenum target, GLenum pname, GLint* params);
    void getUniformfv(GLuint program, GLint location, GLfloat* params);
    void getUniformiv(GLuint program, GLint location, GLint* params);
    int  getUniformLocation(GLuint program, const GLchar* name);
    void getVertexAttribfv(GLuint index, GLenum pname, GLfloat* params);
    void getVertexAttribiv(GLuint index, GLenum pname, GLint* params);
    void getVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer);
    void hint(GLenum target, GLenum mode);
    GLboolean isBuffer(GLuint buffer);
    GLboolean isEnabled(GLenum cap);
    GLboolean isFramebuffer(GLuint framebuffer);
    GLboolean isProgram(GLuint program);
    GLboolean isRenderbuffer(GLuint renderbuffer);
    GLboolean isShader(GLuint shader);
    GLboolean isTexture(GLuint texture);
    void lineWidth(GLfloat width);
    void linkProgram(GLuint program);
    void pixelStorei(GLenum pname, GLint param);
    void polygonOffset(GLfloat factor, GLfloat units);
    void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
    void releaseShaderCompiler(void);
    void renderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
    void sampleCoverage(GLclampf value, GLboolean invert);
    void scissor(GLint x, GLint y, GLsizei width, GLsizei height);
    void shaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length);
    void shaderSource(GLuint shader, GLsizei count, const GLchar* const *string, const GLint* length);
    void stencilFunc(GLenum func, GLint ref, GLuint mask);
    void stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
    void stencilMask(GLuint mask);
    void stencilMaskSeparate(GLenum face, GLuint mask);
    void stencilOp(GLenum fail, GLenum zfail, GLenum zpass);
    void stencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
    void texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
    void texParameterf(GLenum target, GLenum pname, GLfloat param);
    void texParameterfv(GLenum target, GLenum pname, const GLfloat* params);
    void texParameteri(GLenum target, GLenum pname, GLint param);
    void texParameteriv(GLenum target, GLenum pname, const GLint* params);
    void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
    void uniform1f(GLint location, GLfloat x);
    void uniform1fv(GLint location, GLsizei count, const GLfloat* v);
    void uniform1i(GLint location, GLint x);
    void uniform1iv(GLint location, GLsizei count, const GLint* v);
    void uniform2f(GLint location, GLfloat x, GLfloat y);
    void uniform2fv(GLint location, GLsizei count, const GLfloat* v);
    void uniform2i(GLint location, GLint x, GLint y);
    void uniform2iv(GLint location, GLsizei count, const GLint* v);
    void uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z);
    void uniform3fv(GLint location, GLsizei count, const GLfloat* v);
    void uniform3i(GLint location, GLint x, GLint y, GLint z);
    void uniform3iv(GLint location, GLsizei count, const GLint* v);
    void uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void uniform4fv(GLint location, GLsizei count, const GLfloat* v);
    void uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w);
    void uniform4iv(GLint location, GLsizei count, const GLint* v);
    void uniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void uniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void useProgram(GLuint program);
    void validateProgram(GLuint program);
    void vertexAttrib1f(GLuint indx, GLfloat x);
    void vertexAttrib1fv(GLuint indx, const GLfloat* values);
    void vertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);
    void vertexAttrib2fv(GLuint indx, const GLfloat* values);
    void vertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
    void vertexAttrib3fv(GLuint indx, const GLfloat* values);
    void vertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void vertexAttrib4fv(GLuint indx, const GLfloat* values);
    void vertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
    void viewport(GLint x, GLint y, GLsizei width, GLsizei height);

    void drawBuffer(GLenum mode);
    void readBuffer(GLenum mode);
    // WEBGL API END

    CommandBuffer& getCommandBuffer(CommandBuffer::Enum _cmd)
    {
        CommandBuffer& cmdbuf = _cmd < CommandBuffer::End ? m_submit->m_cmdPre : m_submit->m_cmdPost;
        uint8_t cmd = (uint8_t)_cmd;
        cmdbuf.write(cmd);
        return cmdbuf;
    }

    BGFX_API_FUNC(void reset(uint32_t _width, uint32_t _height, uint32_t _flags) )
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

    static WebGLContext* s_ctx;

    Frame  m_frame[1+(BGFX_CONFIG_MULTITHREADED ? 1 : 0)];
    Frame* m_render;
    Frame* m_submit;

    WebGLRenderContext* m_renderCtx;

    Init     m_init;
    int64_t  m_frameTimeLast = 0;
    uint32_t m_frames = 0;
    uint32_t m_debug = 0;
    
    bool m_rendererInitialized = false;
    bool m_exit = false;
    bool m_flipAfterRender = false;
    bool m_singleThreaded = false;
    bool m_flipped = false;
};

} // namespace bgfx {
