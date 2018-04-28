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
#include <OpenGL/gl.h>

namespace bgfx {

    WebGLRenderContext::WebGLRenderContext()
    {

    }

    WebGLRenderContext::~WebGLRenderContext()
    {
        
    }

    void WebGLRenderContext::activeTexture(GLenum texture)
    {
        glActiveTexture(texture);
    }

    void WebGLRenderContext::attachShader(GLuint program, GLuint shader)
    {
        glAttachShader(program, shader);
    }

    void WebGLRenderContext::bindAttribLocation(GLuint program, GLuint index, const GLchar* name)
    {
        glBindAttribLocation(program, index, name);
    }

    void WebGLRenderContext::bindBuffer(GLenum target, GLuint buffer)
    {
        glBindBuffer(target, buffer);
    }

    void WebGLRenderContext::bindFramebuffer(GLenum target, GLuint framebuffer)
    {
        glBindFramebuffer(target, framebuffer);
    }

    void WebGLRenderContext::bindRenderbuffer(GLenum target, GLuint renderbuffer)
    {
        glBindRenderbuffer(target, renderbuffer);
    }

    void WebGLRenderContext::bindTexture(GLenum target, GLuint texture)
    {
        glBindTexture(target, texture);
    }

    void WebGLRenderContext::blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        glBlendColor(red, green, blue, alpha);
    }

    void WebGLRenderContext::blendEquation(GLenum mode)
    {
        glBlendEquation(mode);
    }

    void WebGLRenderContext::blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
    {
        glBlendEquationSeparate(modeRGB, modeAlpha);
    }

    void WebGLRenderContext::blendFunc(GLenum sfactor, GLenum dfactor)
    {
        glBlendFunc(sfactor, dfactor);
    }

    void WebGLRenderContext::blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
    {
        glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
    }

    void WebGLRenderContext::bufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
    {
        glBufferData(target, size, data, usage);
    }

    void WebGLRenderContext::bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
    {
        glBufferSubData(target, offset, size, data);
    }

    GLenum WebGLRenderContext::checkFramebufferStatus(GLenum target)
    {
        return glCheckFramebufferStatus(target);
    }

    void WebGLRenderContext::clear(GLbitfield mask)
    {
        glClear(mask);
    }

    void WebGLRenderContext::clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        glClearColor(red, green, blue, alpha);
    }

    void WebGLRenderContext::clearDepthf(GLclampf depth)
    {
        glClearDepth(depth);
    }

    void WebGLRenderContext::clearStencil(GLint s)
    {
        glClearStencil(s);
    }

    void WebGLRenderContext::colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
    {
        glColorMask(red, green, blue, alpha);
    }

    void WebGLRenderContext::compileShader(GLuint shader)
    {
        glCompileShader(shader);
    }

    void WebGLRenderContext::compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
    {
        glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
    }

    void WebGLRenderContext::compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
    {
        glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
    }

    void WebGLRenderContext::copyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
    {
        glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
    }

    void WebGLRenderContext::copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
    {
        glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
    }

    GLuint WebGLRenderContext::createProgram()
    {
        return glCreateProgram();
    }

    GLuint WebGLRenderContext::createShader(GLenum type)
    {
        return glCreateShader(type);
    }

    void WebGLRenderContext::cullFace(GLenum mode)
    {
        glCullFace(mode);
    }

    void WebGLRenderContext::deleteBuffers(GLsizei n, const GLuint* buffers)
    {
        glDeleteBuffers(n, buffers);
    }

    void WebGLRenderContext::deleteFramebuffers(GLsizei n, const GLuint* framebuffers)
    {
        glDeleteFramebuffers(n, framebuffers);
    }

    void WebGLRenderContext::deleteProgram(GLuint program)
    {
        glDeleteProgram(program);
    }

    void WebGLRenderContext::deleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
    {
        glDeleteRenderbuffers(n, renderbuffers);
    }

    void WebGLRenderContext::deleteShader(GLuint shader)
    {
        glDeleteShader(shader);
    }

    void WebGLRenderContext::deleteTextures(GLsizei n, const GLuint* textures)
    {
        glDeleteTextures(n, textures);
    }

    void WebGLRenderContext::depthFunc(GLenum func)
    {
        glDepthFunc(func);
    }

    void WebGLRenderContext::depthMask(GLboolean flag)
    {
        glDepthMask(flag);
    }

    void WebGLRenderContext::depthRangef(GLclampf zNear, GLclampf zFar)
    {
        glDepthRange(zNear, zFar);
    }

    void WebGLRenderContext::detachShader(GLuint program, GLuint shader)
    {
        glDetachShader(program, shader);
    }

    void WebGLRenderContext::disable(GLenum cap)
    {
        glDisable(cap);
    }

    void WebGLRenderContext::disableVertexAttribArray(GLuint index)
    {
        glDisableVertexAttribArray(index);
    }

    void WebGLRenderContext::drawArrays(GLenum mode, GLint first, GLsizei count)
    {
        glDrawArrays(mode, first, count);
    }

    void WebGLRenderContext::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
    {
        glDrawElements(mode, count, type, indices);
    }

    void WebGLRenderContext::enable(GLenum cap)
    {
        glEnable(cap);
    }

    void WebGLRenderContext::enableVertexAttribArray(GLuint index)
    {
        glEnableVertexAttribArray(index);
    }

    void WebGLRenderContext::finish()
    {
        glFinish();
    }

    void WebGLRenderContext::flush()
    {
        glFlush();
    }

    void WebGLRenderContext::framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
    {
        glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
    }

    void WebGLRenderContext::framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
    {
        glFramebufferTexture2D(target, attachment, textarget, texture, level);
    }

    void WebGLRenderContext::frontFace(GLenum mode)
    {
        glFrontFace(mode);
    }

    void WebGLRenderContext::genBuffers(GLsizei n, GLuint* buffers)
    {
        glGenBuffers(n, buffers);
    }

    void WebGLRenderContext::generateMipmap(GLenum target)
    {
        glGenerateMipmap(target);
    }

    void WebGLRenderContext::genFramebuffers(GLsizei n, GLuint* framebuffers)
    {
        glGenFramebuffers(n, framebuffers);
    }

    void WebGLRenderContext::genRenderbuffers(GLsizei n, GLuint* renderbuffers)
    {
        glGenRenderbuffers(n, renderbuffers);
    }

    void WebGLRenderContext::genTextures(GLsizei n, GLuint* textures)
    {
        glGenTextures(n, textures);
    }

    void WebGLRenderContext::getActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
    {
        glGetActiveAttrib(program, index, bufsize, length, size, type, name);
    }

    void WebGLRenderContext::getActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
    {
        glGetActiveUniform(program, index, bufsize, length, size, type, name);
    }

    void WebGLRenderContext::getAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
    {
        glGetAttachedShaders(program, maxcount, count, shaders);
    }

    GLint WebGLRenderContext::getAttribLocation(GLuint program, const GLchar* name)
    {
        return glGetAttribLocation(program, name);
    }

    void WebGLRenderContext::getBooleanv(GLenum pname, GLboolean* params)
    {
        glGetBooleanv(pname, params);
    }

    void WebGLRenderContext::getBufferParameteriv(GLenum target, GLenum pname, GLint* params)
    {
        glGetBufferParameteriv(target, pname, params);
    }

    GLenum WebGLRenderContext::getError()
    {
        return glGetError();
    }

    void WebGLRenderContext::getFloatv(GLenum pname, GLfloat* params)
    {
        glGetFloatv(pname, params);
    }

    void WebGLRenderContext::getFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
    {
        glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
    }

    void WebGLRenderContext::getIntegerv(GLenum pname, GLint* params)
    {
        glGetIntegerv(pname, params);
    }

    void WebGLRenderContext::getProgramiv(GLuint program, GLenum pname, GLint* params)
    {
        glGetProgramiv(program, pname, params);
    }

    void WebGLRenderContext::getProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
    {
        glGetProgramInfoLog(program, bufsize, length, infolog);
    }

    void WebGLRenderContext::getRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
    {
        glGetRenderbufferParameteriv(target, pname, params);
    }

    void WebGLRenderContext::getShaderiv(GLuint shader, GLenum pname, GLint* params)
    {
        glGetShaderiv(shader, pname, params);
    }

    void WebGLRenderContext::getShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
    {
        glGetShaderInfoLog(shader, bufsize, length, infolog);
    }

    void WebGLRenderContext::getShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
    {
        glGetShaderSource(shader, bufsize, length, source);
    }

    const GLubyte* WebGLRenderContext::getString(GLenum name)
    {
        return glGetString(name);
    }

    void WebGLRenderContext::getTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
    {
        glGetTexParameterfv(target, pname, params);
    }

    void WebGLRenderContext::getTexParameteriv(GLenum target, GLenum pname, GLint* params)
    {
        glGetTexParameteriv(target, pname, params);
    }

    void WebGLRenderContext::getUniformfv(GLuint program, GLint location, GLfloat* params)
    {
        glGetUniformfv(program, location, params);
    }

    void WebGLRenderContext::getUniformiv(GLuint program, GLint location, GLint* params)
    {
        glGetUniformiv(program, location, params);
    }

    GLint WebGLRenderContext::getUniformLocation(GLuint program, const GLchar* name)
    {
        return glGetUniformLocation(program, name);
    }

    void WebGLRenderContext::getVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
    {
        glGetVertexAttribfv(index, pname, params);
    }

    void WebGLRenderContext::getVertexAttribiv(GLuint index, GLenum pname, GLint* params)
    {
        glGetVertexAttribiv(index, pname, params);
    }

    void WebGLRenderContext::getVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer)
    {
        glGetVertexAttribPointerv(index, pname, pointer);
    }

    void WebGLRenderContext::hint(GLenum target, GLenum mode)
    {
        glHint(target, mode);
    }

    GLboolean WebGLRenderContext::isBuffer(GLuint buffer)
    {
        return glIsBuffer(buffer);
    }

    GLboolean WebGLRenderContext::isEnabled(GLenum cap)
    {
        return glIsEnabled(cap);
    }

    GLboolean WebGLRenderContext::isFramebuffer(GLuint framebuffer)
    {
        return glIsFramebuffer(framebuffer);
    }

    GLboolean WebGLRenderContext::isProgram(GLuint program)
    {
        return glIsProgram(program);
    }

    GLboolean WebGLRenderContext::isRenderbuffer(GLuint renderbuffer)
    {
        return glIsRenderbuffer(renderbuffer);
    }

    GLboolean WebGLRenderContext::isShader(GLuint shader)
    {
        return glIsShader(shader);
    }

    GLboolean WebGLRenderContext::isTexture(GLuint texture)
    {
        return glIsTexture(texture);
    }

    void WebGLRenderContext::lineWidth(GLfloat width)
    {
        glLineWidth(width);
    }

    void WebGLRenderContext::linkProgram(GLuint program)
    {
        glLinkProgram(program);
    }

    void WebGLRenderContext::pixelStorei(GLenum pname, GLint param)
    {
        glPixelStorei(pname, param);
    }

    void WebGLRenderContext::polygonOffset(GLfloat factor, GLfloat units)
    {
        glPolygonOffset(factor, units);
    }

    void WebGLRenderContext::readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
    {
        glReadPixels(x, y, width, height, format, type, pixels);
    }

    void WebGLRenderContext::renderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
    {
        glRenderbufferStorage(target, internalformat, width, height);
    }

    void WebGLRenderContext::sampleCoverage(GLclampf value, GLboolean invert)
    {
        glSampleCoverage(value, invert);
    }

    void WebGLRenderContext::scissor(GLint x, GLint y, GLsizei width, GLsizei height)
    {
        glScissor(x, y, width, height);
    }

    void WebGLRenderContext::shaderSource(GLuint shader, GLsizei count, const GLchar* const *string, const GLint* length)
    {
        glShaderSource(shader, count, string, length);
    }

    void WebGLRenderContext::stencilFunc(GLenum func, GLint ref, GLuint mask)
    {
        glStencilFunc(func, ref, mask);
    }

    void WebGLRenderContext::stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
    {
        glStencilFuncSeparate(face, func, ref, mask);
    }

    void WebGLRenderContext::stencilMask(GLuint mask)
    {
        glStencilMask(mask);
    }

    void WebGLRenderContext::stencilMaskSeparate(GLenum face, GLuint mask)
    {
        glStencilMaskSeparate(face, mask);
    }

    void WebGLRenderContext::stencilOp(GLenum fail, GLenum zfail, GLenum zpass)
    {
        glStencilOp(fail, zfail, zpass);
    }

    void WebGLRenderContext::stencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
    {
        glStencilOpSeparate(face, fail, zfail, zpass);
    }

    void WebGLRenderContext::texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
    {
        glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    }

    void WebGLRenderContext::texParameterf(GLenum target, GLenum pname, GLfloat param)
    {
        glTexParameterf(target, pname, param);
    }

    void WebGLRenderContext::texParameterfv(GLenum target, GLenum pname, const GLfloat* params)
    {
        glTexParameterfv(target, pname, params);
    }

    void WebGLRenderContext::texParameteri(GLenum target, GLenum pname, GLint param)
    {
        glTexParameteri(target, pname, param);
    }

    void WebGLRenderContext::texParameteriv(GLenum target, GLenum pname, const GLint* params)
    {
        glTexParameteriv(target, pname, params);
    }

    void WebGLRenderContext::texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
    {
        glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
    }

    void WebGLRenderContext::uniform1f(GLint location, GLfloat x)
    {
        glUniform1f(location, x);
    }

    void WebGLRenderContext::uniform1fv(GLint location, GLsizei count, const GLfloat* v)
    {
        glUniform1fv(location, count, v);
    }

    void WebGLRenderContext::uniform1i(GLint location, GLint x)
    {
        glUniform1i(location, x);
    }

    void WebGLRenderContext::uniform1iv(GLint location, GLsizei count, const GLint* v)
    {
        glUniform1iv(location, count, v);
    }

    void WebGLRenderContext::uniform2f(GLint location, GLfloat x, GLfloat y)
    {
        glUniform2f(location, x, y);
    }

    void WebGLRenderContext::uniform2fv(GLint location, GLsizei count, const GLfloat* v)
    {
        glUniform2fv(location, count, v);
    }

    void WebGLRenderContext::uniform2i(GLint location, GLint x, GLint y)
    {
        glUniform2i(location, x, y);
    }

    void WebGLRenderContext::uniform2iv(GLint location, GLsizei count, const GLint* v)
    {
        glUniform2iv(location, count, v);
    }

    void WebGLRenderContext::uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
    {
        glUniform3f(location, x, y, z);
    }

    void WebGLRenderContext::uniform3fv(GLint location, GLsizei count, const GLfloat* v)
    {
        glUniform3fv(location, count, v);
    }

    void WebGLRenderContext::uniform3i(GLint location, GLint x, GLint y, GLint z)
    {
        glUniform3i(location, x, y, z);
    }

    void WebGLRenderContext::uniform3iv(GLint location, GLsizei count, const GLint* v)
    {
        glUniform3iv(location, count, v);
    }

    void WebGLRenderContext::uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        glUniform4f(location, x, y, z, w);
    }

    void WebGLRenderContext::uniform4fv(GLint location, GLsizei count, const GLfloat* v)
    {
        glUniform4fv(location, count, v);
    }

    void WebGLRenderContext::uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
    {
        glUniform4i(location, x, y, z, w);
    }

    void WebGLRenderContext::uniform4iv(GLint location, GLsizei count, const GLint* v)
    {
        glUniform4iv(location, count, v);
    }

    void WebGLRenderContext::uniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
    {
        glUniformMatrix2fv(location, count, transpose, value);
    }

    void WebGLRenderContext::uniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
    {
        glUniformMatrix3fv(location, count, transpose, value);
    }

    void WebGLRenderContext::uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
    {
        glUniformMatrix4fv(location, count, transpose, value);
    }

    void WebGLRenderContext::useProgram(GLuint program)
    {
        glUseProgram(program);
    }

    void WebGLRenderContext::validateProgram(GLuint program)
    {
        glValidateProgram(program);
    }

    void WebGLRenderContext::vertexAttrib1f(GLuint index, GLfloat x)
    {
        glVertexAttrib1f(index, x);
    }

    void WebGLRenderContext::vertexAttrib1fv(GLuint index, const GLfloat* values)
    {
        glVertexAttrib1fv(index, values);
    }

    void WebGLRenderContext::vertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
    {
        glVertexAttrib2f(index, x, y);
    }

    void WebGLRenderContext::vertexAttrib2fv(GLuint index, const GLfloat* values)
    {
        glVertexAttrib2fv(index, values);
    }

    void WebGLRenderContext::vertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
    {
        glVertexAttrib3f(index, x, y, z);
    }

    void WebGLRenderContext::vertexAttrib3fv(GLuint index, const GLfloat* values)
    {
        glVertexAttrib3fv(index, values);
    }

    void WebGLRenderContext::vertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        glVertexAttrib4f(index, x, y, z, w);
    }

    void WebGLRenderContext::vertexAttrib4fv(GLuint index, const GLfloat* values)
    {
        glVertexAttrib4fv(index, values);
    }

    void WebGLRenderContext::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
    {
        glVertexAttribPointer(index, size, type, normalized, stride, ptr);
    }

    void WebGLRenderContext::viewport(GLint x, GLint y, GLsizei width, GLsizei height)
    {
        glViewport(x, y, width, height);
    }


    void WebGLRenderContext::drawBuffer(GLenum mode)
    {
        glDrawBuffer(mode);
    }

    void WebGLRenderContext::readBuffer(GLenum mode)
    {
        glReadBuffer(mode);
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
