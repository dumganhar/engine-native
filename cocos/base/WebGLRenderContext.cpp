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

#include "WebGLRenderContext.h"

namespace bgfx {

    WebGLRenderContext::WebGLRenderContext()
    {

    }

    WebGLRenderContext::~WebGLRenderContext()
    {
        
    }

    WebGLContextAttributes getContextAttributes()
    {
        return WebGLContextAttributes();
    }

    bool isContextLost()
    {
        return false;
    }

    std::vector<std::string> getSupportedExtensions()
    {
        return std::vector<std::string>();
    }

    //    object getExtension(const std::string& name); //cjh
    void WebGLRenderContext::activeTexture(GLenum texture)
    {

    }

    void WebGLRenderContext::attachShader(WebGLProgram program, WebGLShader shader)
    {

    }

    void WebGLRenderContext::bindAttribLocation(WebGLProgram program, GLuint index, const std::string& name)
    {

    }

    void WebGLRenderContext::bindBuffer(GLenum target, WebGLBuffer buffer)
    {

    }

    void WebGLRenderContext::bindFramebuffer(GLenum target, WebGLFramebuffer framebuffer)
    {

    }

    void WebGLRenderContext::bindRenderbuffer(GLenum target, WebGLRenderbuffer renderbuffer)
    {

    }

    void WebGLRenderContext::bindTexture(GLenum target, WebGLTexture texture)
    {

    }

    void WebGLRenderContext::blendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {

    }

    void WebGLRenderContext::blendEquation(GLenum mode)
    {

    }

    void WebGLRenderContext::blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
    {

    }

    void WebGLRenderContext::blendFunc(GLenum sfactor, GLenum dfactor)
    {

    }

    void WebGLRenderContext::blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
    {

    }

    void WebGLRenderContext::bufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
    {

    }

    void WebGLRenderContext::bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
    {

    }

    GLenum WebGLRenderContext::checkFramebufferStatus(GLenum target)
    {
        return 0;
    }

    void WebGLRenderContext::clear(GLbitfield mask)
    {
        glClear(mask);
    }

    void WebGLRenderContext::clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {
        glClearColor(red, green, blue, alpha);
    }

    void WebGLRenderContext::clearDepth(GLclampf depth)
    {

    }

    void WebGLRenderContext::clearStencil(GLint s)
    {

    }

    void WebGLRenderContext::colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
    {

    }

    void WebGLRenderContext::compileShader(WebGLShader shader)
    {

    }

    void WebGLRenderContext::compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
    {

    }

    void WebGLRenderContext::compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
    {

    }

    void WebGLRenderContext::copyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
    {

    }

    void WebGLRenderContext::copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
    {

    }

    WebGLBuffer WebGLRenderContext::createBuffer()
    {
        return 0;
    }

    WebGLFramebuffer WebGLRenderContext::createFramebuffer()
    {
        return 0;
    }

    WebGLProgram WebGLRenderContext::createProgram()
    {
        return 0;
    }

    WebGLRenderbuffer WebGLRenderContext::createRenderbuffer()
    {
        return 0;
    }

    WebGLShader WebGLRenderContext::createShader(GLenum type)
    {
        return 0;
    }

    WebGLTexture WebGLRenderContext::createTexture()
    {
        return 0;
    }

    void WebGLRenderContext::cullFace(GLenum mode)
    {

    }

    void WebGLRenderContext::deleteBuffer(WebGLBuffer buffer)
    {

    }

    void WebGLRenderContext::deleteFramebuffer(WebGLFramebuffer framebuffer)
    {

    }

    void WebGLRenderContext::deleteProgram(WebGLProgram program)
    {

    }

    void WebGLRenderContext::deleteRenderbuffer(WebGLRenderbuffer renderbuffer)
    {

    }

    void WebGLRenderContext::deleteShader(WebGLShader shader)
    {

    }

    void WebGLRenderContext::deleteTexture(WebGLTexture texture)
    {

    }

    void WebGLRenderContext::depthFunc(GLenum func)
    {

    }

    void WebGLRenderContext::depthMask(GLboolean flag)
    {

    }

    void WebGLRenderContext::depthRange(GLclampf zNear, GLclampf zFar)
    {

    }

    void WebGLRenderContext::detachShader(WebGLProgram program, WebGLShader shader)
    {

    }

    void WebGLRenderContext::disable(GLenum cap)
    {

    }

    void WebGLRenderContext::disableVertexAttribArray(GLuint index)
    {

    }

    void WebGLRenderContext::drawArrays(GLenum mode, GLint first, GLsizei count)
    {

    }

    void WebGLRenderContext::drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset)
    {

    }

    void WebGLRenderContext::enable(GLenum cap)
    {

    }

    void WebGLRenderContext::enableVertexAttribArray(GLuint index)
    {

    }

    void WebGLRenderContext::finish()
    {

    }

    void WebGLRenderContext::flush()
    {

    }

    void WebGLRenderContext::framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, WebGLRenderbuffer renderbuffer)
    {

    }

    void WebGLRenderContext::framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, WebGLTexture texture, GLint level)
    {

    }

    void WebGLRenderContext::frontFace(GLenum mode)
    {

    }

    void WebGLRenderContext::generateMipmap(GLenum target)
    {

    }

    WebGLActiveInfo WebGLRenderContext::getActiveAttrib(WebGLProgram program, GLuint index)
    {
        return {};
    }

    WebGLActiveInfo WebGLRenderContext::getActiveUniform(WebGLProgram program, GLuint index)
    {
        return {};
    }

    std::vector<WebGLShader> WebGLRenderContext::getAttachedShaders(WebGLProgram program)
    {
        return std::vector<WebGLShader>();
    }

    GLint WebGLRenderContext::getAttribLocation(WebGLProgram program, const std::string& name)
    {
        return 0;
    }

    any WebGLRenderContext::getBufferParameter(GLenum target, GLenum pname)
    {
        return 0;
    }

    any WebGLRenderContext::getParameter(GLenum pname)
    {
        return 0;
    }

    GLenum WebGLRenderContext::getError()
    {
        return 0;
    }

    any WebGLRenderContext::getFramebufferAttachmentParameter(GLenum target, GLenum attachment, GLenum pname)
    {
        return 0;
    }

    any WebGLRenderContext::getProgramParameter(WebGLProgram program, GLenum pname)
    {
        return 0;
    }

    const std::string& WebGLRenderContext::getProgramInfoLog(WebGLProgram program)
    {
        static const std::string EMPTY = "";
        return EMPTY;
    }

    any WebGLRenderContext::getRenderbufferParameter(GLenum target, GLenum pname)
    {
        return 0;
    }

    any WebGLRenderContext::getShaderParameter(WebGLShader shader, GLenum pname)
    {
        return 0;
    }

    WebGLShaderPrecisionFormat WebGLRenderContext::getShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype)
    {
        return WebGLShaderPrecisionFormat();
    }

    const std::string& WebGLRenderContext::getShaderInfoLog(WebGLShader shader)
    {
        static const std::string EMPTY;
        return EMPTY;
    }

    const std::string& WebGLRenderContext::getShaderSource(WebGLShader shader)
    {
        static const std::string EMPTY;
        return EMPTY;
    }

    any WebGLRenderContext::getTexParameter(GLenum target, GLenum pname)
    {
        return 0;
    }

    any WebGLRenderContext::getUniform(WebGLProgram program, WebGLUniformLocation location)
    {
        return 0;
    }

    WebGLUniformLocation WebGLRenderContext::getUniformLocation(WebGLProgram program, const std::string& name)
    {
        return 0;
    }

    any WebGLRenderContext::getVertexAttrib(GLuint index, GLenum pname)
    {
        return 0;
    }

    GLintptr WebGLRenderContext::getVertexAttribOffset(GLuint index, GLenum pname)
    {
        return 0;
    }

    void WebGLRenderContext::hint(GLenum target, GLenum mode)
    {

    }

    GLboolean WebGLRenderContext::isBuffer(WebGLBuffer buffer)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isEnabled(GLenum cap)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isFramebuffer(WebGLFramebuffer framebuffer)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isProgram(WebGLProgram program)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isRenderbuffer(WebGLRenderbuffer renderbuffer)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isShader(WebGLShader shader)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isTexture(WebGLTexture texture)
    {
        return 0;
    }

    void WebGLRenderContext::lineWidth(GLfloat width)
    {

    }

    void WebGLRenderContext::linkProgram(WebGLProgram program)
    {

    }

    void WebGLRenderContext::pixelStorei(GLenum pname, GLint param)
    {

    }

    void WebGLRenderContext::polygonOffset(GLfloat factor, GLfloat units)
    {

    }

    void WebGLRenderContext::readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
    {

    }

    void WebGLRenderContext::renderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
    {

    }

    void WebGLRenderContext::sampleCoverage(GLclampf value, GLboolean invert)
    {

    }

    void WebGLRenderContext::scissor(GLint x, GLint y, GLsizei width, GLsizei height)
    {

    }

    void WebGLRenderContext::shaderSource(WebGLShader shader, const std::string& source)
    {

    }

    void WebGLRenderContext::stencilFunc(GLenum func, GLint ref, GLuint mask)
    {

    }

    void WebGLRenderContext::stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
    {

    }

    void WebGLRenderContext::stencilMask(GLuint mask)
    {

    }

    void WebGLRenderContext::stencilMaskSeparate(GLenum face, GLuint mask)
    {

    }

    void WebGLRenderContext::stencilOp(GLenum fail, GLenum zfail, GLenum zpass)
    {

    }

    void WebGLRenderContext::stencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
    {

    }

    void WebGLRenderContext::texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
    {

    }

    void WebGLRenderContext::texParameterf(GLenum target, GLenum pname, GLfloat param)
    {

    }

    void WebGLRenderContext::texParameteri(GLenum target, GLenum pname, GLint param)
    {

    }

    void WebGLRenderContext::texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
    {

    }

    void WebGLRenderContext::uniform1f(WebGLUniformLocation location, GLfloat x)
    {

    }

    void WebGLRenderContext::uniform2f(WebGLUniformLocation location, GLfloat x, GLfloat y)
    {

    }

    void WebGLRenderContext::uniform3f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z)
    {

    }

    void WebGLRenderContext::uniform4f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {

    }

    void WebGLRenderContext::uniform1i(WebGLUniformLocation location, GLint x)
    {

    }

    void WebGLRenderContext::uniform2i(WebGLUniformLocation location, GLint x, GLint y)
    {

    }

    void WebGLRenderContext::uniform3i(WebGLUniformLocation location, GLint x, GLint y, GLint z)
    {

    }

    void WebGLRenderContext::uniform4i(WebGLUniformLocation location, GLint x, GLint y, GLint z, GLint w)
    {

    }

    void WebGLRenderContext::uniform1fv(WebGLUniformLocation location, GLsizei count, const GLfloat *value)
    {

    }

    void WebGLRenderContext::uniform2fv(WebGLUniformLocation location, GLsizei count, const GLfloat *value)
    {

    }

    void WebGLRenderContext::uniform3fv(WebGLUniformLocation location, GLsizei count, const GLfloat *value)
    {

    }

    void WebGLRenderContext::uniform4fv(WebGLUniformLocation location, GLsizei count, const GLfloat *value)
    {

    }

    void WebGLRenderContext::uniform1iv(WebGLUniformLocation location, GLsizei count, const GLint *value)
    {

    }

    void WebGLRenderContext::uniform2iv(WebGLUniformLocation location, GLsizei count, const GLint *value)
    {

    }

    void WebGLRenderContext::uniform3iv(WebGLUniformLocation location, GLsizei count, const GLint *value)
    {

    }

    void WebGLRenderContext::uniform4iv(WebGLUniformLocation location, GLsizei count, const GLint *value)
    {

    }

    void WebGLRenderContext::uniformMatrix2fv(WebGLUniformLocation location, GLsizei count, GLboolean transpose, const GLfloat *value)
    {

    }

    void WebGLRenderContext::uniformMatrix3fv(WebGLUniformLocation location, GLsizei count, GLboolean transpose, const GLfloat *value)
    {

    }

    void WebGLRenderContext::uniformMatrix4fv(WebGLUniformLocation location, GLsizei count, GLboolean transpose, const GLfloat *value)
    {

    }

    void WebGLRenderContext::useProgram(WebGLProgram program)
    {

    }

    void WebGLRenderContext::validateProgram(WebGLProgram program)
    {

    }

    void WebGLRenderContext::vertexAttrib1f(GLuint index, GLfloat x)
    {

    }

    void WebGLRenderContext::vertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
    {

    }

    void WebGLRenderContext::vertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
    {

    }

    void WebGLRenderContext::vertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {

    }

    void WebGLRenderContext::vertexAttrib1fv(GLuint index, const GLfloat *v)
    {

    }

    void WebGLRenderContext::vertexAttrib2fv(GLuint index, const GLfloat *v)
    {

    }

    void WebGLRenderContext::vertexAttrib3fv(GLuint index, const GLfloat *v)
    {

    }

    void WebGLRenderContext::vertexAttrib4fv(GLuint index, const GLfloat *v)
    {

    }

    void WebGLRenderContext::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset)
    {

    }

    void WebGLRenderContext::viewport(GLint x, GLint y, GLsizei width, GLsizei height)
    {

    }

    //
    bool WebGLRenderContext::isDeviceRemoved()
    {
        return false;
    }

    void WebGLRenderContext::flip()
    {
        if (m_flip)
        {
//cjh            for (uint32_t ii = 1, num = m_numWindows; ii < num; ++ii)
//            {
//                FrameBufferGL& frameBuffer = m_frameBuffers[m_windows[ii].idx];
//                if (frameBuffer.m_needPresent)
//                {
//                    m_glctx.swap(frameBuffer.m_swapChain);
//                    frameBuffer.m_needPresent = false;
//                }
//            }
//
//            if (m_needPresent)
//            {
//                m_ovr.flip();
//                m_ovr.swap(_hmd);
//
//                // Ensure the back buffer is bound as the source of the flip
//                GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_backBufferFbo));
//
//                // need to swap GL render context even if OVR is enabled to get
//                // the mirror texture in the output
//                m_glctx.swap();
//                m_needPresent = false;
//            }
        }
    }

    void WebGLRenderContext::submit(Frame* _render)
    {

    }

} // namespace bgfx {
