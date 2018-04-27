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
#include <OpenGL/OpenGL.h>

namespace bgfx {

    WebGLRenderContext::WebGLRenderContext()
    {

    }

    WebGLRenderContext::~WebGLRenderContext()
    {
        
    }

    void WebGLRenderContext::activeTexture(GLenum texture)
    {

    }

    void WebGLRenderContext::attachShader(GLuint program, GLuint shader)
    {

    }

    void WebGLRenderContext::bindAttribLocation(GLuint program, GLuint index, const GLchar* name)
    {

    }

    void WebGLRenderContext::bindBuffer(GLenum target, GLuint buffer)
    {

    }

    void WebGLRenderContext::bindFramebuffer(GLenum target, GLuint framebuffer)
    {

    }

    void WebGLRenderContext::bindRenderbuffer(GLenum target, GLuint renderbuffer)
    {

    }

    void WebGLRenderContext::bindTexture(GLenum target, GLuint texture)
    {

    }

    void WebGLRenderContext::blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
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

    void WebGLRenderContext::bufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
    {

    }

    void WebGLRenderContext::bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
    {

    }

    GLenum checkFramebufferStatus(GLenum target)
    {
        return 0;
    }

    void WebGLRenderContext::clear(GLbitfield mask)
    {

    }

    void WebGLRenderContext::clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {

    }

    void WebGLRenderContext::clearDepthf(GLclampf depth)
    {

    }

    void WebGLRenderContext::clearStencil(GLint s)
    {

    }

    void WebGLRenderContext::colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
    {

    }

    void WebGLRenderContext::compileShader(GLuint shader)
    {

    }

    void WebGLRenderContext::compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
    {

    }

    void WebGLRenderContext::compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
    {

    }

    void WebGLRenderContext::copyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
    {

    }

    void WebGLRenderContext::copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
    {

    }

    GLuint WebGLRenderContext::createProgram(void)
    {
        return 0;
    }

    GLuint WebGLRenderContext::createShader(GLenum type)
    {
        return 0;
    }

    void WebGLRenderContext::cullFace(GLenum mode)
    {

    }

    void WebGLRenderContext::deleteBuffers(GLsizei n, const GLuint* buffers)
    {

    }

    void WebGLRenderContext::deleteFramebuffers(GLsizei n, const GLuint* framebuffers)
    {

    }

    void WebGLRenderContext::deleteProgram(GLuint program)
    {

    }

    void WebGLRenderContext::deleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
    {

    }

    void WebGLRenderContext::deleteShader(GLuint shader)
    {

    }

    void WebGLRenderContext::deleteTextures(GLsizei n, const GLuint* textures)
    {

    }

    void WebGLRenderContext::depthFunc(GLenum func)
    {

    }

    void WebGLRenderContext::depthMask(GLboolean flag)
    {

    }

    void WebGLRenderContext::depthRangef(GLclampf zNear, GLclampf zFar)
    {

    }

    void WebGLRenderContext::detachShader(GLuint program, GLuint shader)
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

    void WebGLRenderContext::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
    {

    }

    void WebGLRenderContext::enable(GLenum cap)
    {

    }

    void WebGLRenderContext::enableVertexAttribArray(GLuint index)
    {

    }

    void WebGLRenderContext::finish(void)
    {

    }

    void WebGLRenderContext::flush(void)
    {

    }

    void WebGLRenderContext::framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
    {

    }

    void WebGLRenderContext::framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
    {

    }

    void WebGLRenderContext::frontFace(GLenum mode)
    {

    }

    void WebGLRenderContext::genBuffers(GLsizei n, GLuint* buffers)
    {

    }

    void WebGLRenderContext::generateMipmap(GLenum target)
    {

    }

    void WebGLRenderContext::genFramebuffers(GLsizei n, GLuint* framebuffers)
    {

    }

    void WebGLRenderContext::genRenderbuffers(GLsizei n, GLuint* renderbuffers)
    {

    }

    void WebGLRenderContext::genTextures(GLsizei n, GLuint* textures)
    {

    }

    void WebGLRenderContext::getActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
    {

    }

    void WebGLRenderContext::getActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
    {

    }

    void WebGLRenderContext::getAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
    {

    }

    int  getAttribLocation(GLuint program, const GLchar* name)
    {
        return 0;
    }

    void WebGLRenderContext::getBooleanv(GLenum pname, GLboolean* params)
    {

    }

    void WebGLRenderContext::getBufferParameteriv(GLenum target, GLenum pname, GLint* params)
    {

    }

    GLenum getError(void)
    {
        return 0;
    }

    void WebGLRenderContext::getFloatv(GLenum pname, GLfloat* params)
    {

    }

    void WebGLRenderContext::getFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
    {

    }

    void WebGLRenderContext::getIntegerv(GLenum pname, GLint* params)
    {

    }

    void WebGLRenderContext::getProgramiv(GLuint program, GLenum pname, GLint* params)
    {

    }

    void WebGLRenderContext::getProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
    {

    }

    void WebGLRenderContext::getRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
    {

    }

    void WebGLRenderContext::getShaderiv(GLuint shader, GLenum pname, GLint* params)
    {

    }

    void WebGLRenderContext::getShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
    {

    }

    void WebGLRenderContext::getShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
    {

    }

    void WebGLRenderContext::getShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
    {

    }

    const GLubyte* getString(GLenum name)
    {
        return 0;
    }

    void WebGLRenderContext::getTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
    {

    }

    void WebGLRenderContext::getTexParameteriv(GLenum target, GLenum pname, GLint* params)
    {

    }

    void WebGLRenderContext::getUniformfv(GLuint program, GLint location, GLfloat* params)
    {

    }

    void WebGLRenderContext::getUniformiv(GLuint program, GLint location, GLint* params)
    {

    }

    int WebGLRenderContext::getUniformLocation(GLuint program, const GLchar* name)
    {
        return 0;
    }

    void WebGLRenderContext::getVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
    {

    }

    void WebGLRenderContext::getVertexAttribiv(GLuint index, GLenum pname, GLint* params)
    {

    }

    void WebGLRenderContext::getVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer)
    {

    }

    void WebGLRenderContext::hint(GLenum target, GLenum mode)
    {

    }

    GLboolean WebGLRenderContext::isBuffer(GLuint buffer)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isEnabled(GLenum cap)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isFramebuffer(GLuint framebuffer)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isProgram(GLuint program)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isRenderbuffer(GLuint renderbuffer)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isShader(GLuint shader)
    {
        return 0;
    }

    GLboolean WebGLRenderContext::isTexture(GLuint texture)
    {
        return 0;
    }

    void WebGLRenderContext::lineWidth(GLfloat width)
    {

    }

    void WebGLRenderContext::linkProgram(GLuint program)
    {

    }

    void WebGLRenderContext::pixelStorei(GLenum pname, GLint param)
    {

    }

    void WebGLRenderContext::polygonOffset(GLfloat factor, GLfloat units)
    {

    }

    void WebGLRenderContext::readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
    {

    }

    void WebGLRenderContext::releaseShaderCompiler(void)
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

    void WebGLRenderContext::shaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
    {

    }

    void WebGLRenderContext::shaderSource(GLuint shader, GLsizei count, const GLchar* const *string, const GLint* length)
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

    void WebGLRenderContext::texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
    {

    }

    void WebGLRenderContext::texParameterf(GLenum target, GLenum pname, GLfloat param)
    {

    }

    void WebGLRenderContext::texParameterfv(GLenum target, GLenum pname, const GLfloat* params)
    {

    }

    void WebGLRenderContext::texParameteri(GLenum target, GLenum pname, GLint param)
    {

    }

    void WebGLRenderContext::texParameteriv(GLenum target, GLenum pname, const GLint* params)
    {

    }

    void WebGLRenderContext::texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
    {

    }

    void WebGLRenderContext::uniform1f(GLint location, GLfloat x)
    {

    }

    void WebGLRenderContext::uniform1fv(GLint location, GLsizei count, const GLfloat* v)
    {

    }

    void WebGLRenderContext::uniform1i(GLint location, GLint x)
    {

    }

    void WebGLRenderContext::uniform1iv(GLint location, GLsizei count, const GLint* v)
    {

    }

    void WebGLRenderContext::uniform2f(GLint location, GLfloat x, GLfloat y)
    {

    }

    void WebGLRenderContext::uniform2fv(GLint location, GLsizei count, const GLfloat* v)
    {

    }

    void WebGLRenderContext::uniform2i(GLint location, GLint x, GLint y)
    {

    }

    void WebGLRenderContext::uniform2iv(GLint location, GLsizei count, const GLint* v)
    {

    }

    void WebGLRenderContext::uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
    {

    }

    void WebGLRenderContext::uniform3fv(GLint location, GLsizei count, const GLfloat* v)
    {

    }

    void WebGLRenderContext::uniform3i(GLint location, GLint x, GLint y, GLint z)
    {

    }

    void WebGLRenderContext::uniform3iv(GLint location, GLsizei count, const GLint* v)
    {

    }

    void WebGLRenderContext::uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {

    }

    void WebGLRenderContext::uniform4fv(GLint location, GLsizei count, const GLfloat* v)
    {

    }

    void WebGLRenderContext::uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
    {

    }

    void WebGLRenderContext::uniform4iv(GLint location, GLsizei count, const GLint* v)
    {

    }

    void WebGLRenderContext::uniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
    {

    }

    void WebGLRenderContext::uniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
    {

    }

    void WebGLRenderContext::uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
    {

    }

    void WebGLRenderContext::useProgram(GLuint program)
    {

    }

    void WebGLRenderContext::validateProgram(GLuint program)
    {

    }

    void WebGLRenderContext::vertexAttrib1f(GLuint indx, GLfloat x)
    {

    }

    void WebGLRenderContext::vertexAttrib1fv(GLuint indx, const GLfloat* values)
    {

    }

    void WebGLRenderContext::vertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
    {

    }

    void WebGLRenderContext::vertexAttrib2fv(GLuint indx, const GLfloat* values)
    {

    }

    void WebGLRenderContext::vertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
    {

    }

    void WebGLRenderContext::vertexAttrib3fv(GLuint indx, const GLfloat* values)
    {

    }

    void WebGLRenderContext::vertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {

    }

    void WebGLRenderContext::vertexAttrib4fv(GLuint indx, const GLfloat* values)
    {

    }

    void WebGLRenderContext::vertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
    {

    }

    void WebGLRenderContext::viewport(GLint x, GLint y, GLsizei width, GLsizei height)
    {

    }


    void WebGLRenderContext::drawBuffer(GLenum mode)
    {

    }

    void WebGLRenderContext::readBuffer(GLenum mode)
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
