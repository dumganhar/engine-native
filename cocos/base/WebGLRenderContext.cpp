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
    void activeTexture(GLenum texture)
    {

    }

    void attachShader(WebGLProgram program, WebGLShader shader)
    {

    }

    void bindAttribLocation(WebGLProgram program, GLuint index, const std::string& name)
    {

    }

    void bindBuffer(GLenum target, WebGLBuffer buffer)
    {

    }

    void bindFramebuffer(GLenum target, WebGLFramebuffer framebuffer)
    {

    }

    void bindRenderbuffer(GLenum target, WebGLRenderbuffer renderbuffer)
    {

    }

    void bindTexture(GLenum target, WebGLTexture texture)
    {

    }

    void blendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {

    }

    void blendEquation(GLenum mode)
    {

    }

    void blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
    {

    }

    void blendFunc(GLenum sfactor, GLenum dfactor)
    {

    }

    void blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
    {

    }

    void bufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
    {

    }

    void bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
    {

    }

    GLenum checkFramebufferStatus(GLenum target)
    {
        return 0;
    }

    void clear(GLbitfield mask)
    {

    }

    void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
    {

    }

    void clearDepth(GLclampf depth)
    {

    }

    void clearStencil(GLint s)
    {

    }

    void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
    {

    }

    void compileShader(WebGLShader shader)
    {

    }

    void compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
    {

    }

    void compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
    {

    }

    void copyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
    {

    }

    void copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
    {

    }

    WebGLBuffer createBuffer()
    {
        return 0;
    }

    WebGLFramebuffer createFramebuffer()
    {
        return 0;
    }

    WebGLProgram createProgram()
    {
        return 0;
    }

    WebGLRenderbuffer createRenderbuffer()
    {
        return 0;
    }

    WebGLShader createShader(GLenum type)
    {
        return 0;
    }

    WebGLTexture createTexture()
    {
        return 0;
    }

    void cullFace(GLenum mode)
    {

    }

    void deleteBuffer(WebGLBuffer buffer)
    {

    }

    void deleteFramebuffer(WebGLFramebuffer framebuffer)
    {

    }

    void deleteProgram(WebGLProgram program)
    {

    }

    void deleteRenderbuffer(WebGLRenderbuffer renderbuffer)
    {

    }

    void deleteShader(WebGLShader shader)
    {

    }

    void deleteTexture(WebGLTexture texture)
    {

    }

    void depthFunc(GLenum func)
    {

    }

    void depthMask(GLboolean flag)
    {

    }

    void depthRange(GLclampf zNear, GLclampf zFar)
    {

    }

    void detachShader(WebGLProgram program, WebGLShader shader)
    {

    }

    void disable(GLenum cap)
    {

    }

    void disableVertexAttribArray(GLuint index)
    {

    }

    void drawArrays(GLenum mode, GLint first, GLsizei count)
    {

    }

    void drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset)
    {

    }

    void enable(GLenum cap)
    {

    }

    void enableVertexAttribArray(GLuint index)
    {

    }

    void finish()
    {

    }

    void flush()
    {

    }

    void framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, WebGLRenderbuffer renderbuffer)
    {

    }

    void framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, WebGLTexture texture, GLint level)
    {

    }

    void frontFace(GLenum mode)
    {

    }

    void generateMipmap(GLenum target)
    {

    }

    WebGLActiveInfo getActiveAttrib(WebGLProgram program, GLuint index)
    {
        return {};
    }

    WebGLActiveInfo getActiveUniform(WebGLProgram program, GLuint index)
    {
        return {};
    }

    std::vector<WebGLShader> getAttachedShaders(WebGLProgram program)
    {
        return std::vector<WebGLShader>();
    }

    GLint getAttribLocation(WebGLProgram program, const std::string& name)
    {
        return 0;
    }

    any getBufferParameter(GLenum target, GLenum pname)
    {
        return 0;
    }

    any getParameter(GLenum pname)
    {
        return 0;
    }

    GLenum getError()
    {
        return 0;
    }

    any getFramebufferAttachmentParameter(GLenum target, GLenum attachment, GLenum pname)
    {
        return 0;
    }

    any getProgramParameter(WebGLProgram program, GLenum pname)
    {
        return 0;
    }

    const std::string& getProgramInfoLog(WebGLProgram program)
    {
        static const std::string EMPTY = "";
        return EMPTY;
    }

    any getRenderbufferParameter(GLenum target, GLenum pname)
    {
        return 0;
    }

    any getShaderParameter(WebGLShader shader, GLenum pname)
    {
        return 0;
    }

    WebGLShaderPrecisionFormat getShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype)
    {
        return WebGLShaderPrecisionFormat();
    }

    const std::string& getShaderInfoLog(WebGLShader shader)
    {
        static const std::string EMPTY;
        return EMPTY;
    }

    const std::string& getShaderSource(WebGLShader shader)
    {
        static const std::string EMPTY;
        return EMPTY;
    }

    any getTexParameter(GLenum target, GLenum pname)
    {
        return 0;
    }

    any getUniform(WebGLProgram program, WebGLUniformLocation location)
    {
        return 0;
    }

    WebGLUniformLocation getUniformLocation(WebGLProgram program, const std::string& name)
    {
        return 0;
    }

    any getVertexAttrib(GLuint index, GLenum pname)
    {
        return 0;
    }

    GLintptr getVertexAttribOffset(GLuint index, GLenum pname)
    {
        return 0;
    }

    void hint(GLenum target, GLenum mode)
    {

    }

    GLboolean isBuffer(WebGLBuffer buffer)
    {
        return 0;
    }

    GLboolean isEnabled(GLenum cap)
    {
        return 0;
    }

    GLboolean isFramebuffer(WebGLFramebuffer framebuffer)
    {
        return 0;
    }

    GLboolean isProgram(WebGLProgram program)
    {
        return 0;
    }

    GLboolean isRenderbuffer(WebGLRenderbuffer renderbuffer)
    {
        return 0;
    }

    GLboolean isShader(WebGLShader shader)
    {
        return 0;
    }

    GLboolean isTexture(WebGLTexture texture)
    {
        return 0;
    }

    void lineWidth(GLfloat width)
    {

    }

    void linkProgram(WebGLProgram program)
    {

    }

    void pixelStorei(GLenum pname, GLint param)
    {

    }

    void polygonOffset(GLfloat factor, GLfloat units)
    {

    }

    void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
    {

    }

    void renderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
    {

    }

    void sampleCoverage(GLclampf value, GLboolean invert)
    {

    }

    void scissor(GLint x, GLint y, GLsizei width, GLsizei height)
    {

    }

    void shaderSource(WebGLShader shader, const std::string& source)
    {

    }

    void stencilFunc(GLenum func, GLint ref, GLuint mask)
    {

    }

    void stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
    {

    }

    void stencilMask(GLuint mask)
    {

    }

    void stencilMaskSeparate(GLenum face, GLuint mask)
    {

    }

    void stencilOp(GLenum fail, GLenum zfail, GLenum zpass)
    {

    }

    void stencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
    {

    }

    void texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
    {

    }

    void texParameterf(GLenum target, GLenum pname, GLfloat param)
    {

    }

    void texParameteri(GLenum target, GLenum pname, GLint param)
    {

    }

    void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
    {

    }

    void uniform1f(WebGLUniformLocation location, GLfloat x)
    {

    }

    void uniform2f(WebGLUniformLocation location, GLfloat x, GLfloat y)
    {

    }

    void uniform3f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z)
    {

    }

    void uniform4f(WebGLUniformLocation location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {

    }

    void uniform1i(WebGLUniformLocation location, GLint x)
    {

    }

    void uniform2i(WebGLUniformLocation location, GLint x, GLint y)
    {

    }

    void uniform3i(WebGLUniformLocation location, GLint x, GLint y, GLint z)
    {

    }

    void uniform4i(WebGLUniformLocation location, GLint x, GLint y, GLint z, GLint w)
    {

    }

    void uniform1fv(WebGLUniformLocation location, GLsizei count, const GLfloat *value)
    {

    }

    void uniform2fv(WebGLUniformLocation location, GLsizei count, const GLfloat *value)
    {

    }

    void uniform3fv(WebGLUniformLocation location, GLsizei count, const GLfloat *value)
    {

    }

    void uniform4fv(WebGLUniformLocation location, GLsizei count, const GLfloat *value)
    {

    }

    void uniform1iv(WebGLUniformLocation location, GLsizei count, const GLint *value)
    {

    }

    void uniform2iv(WebGLUniformLocation location, GLsizei count, const GLint *value)
    {

    }

    void uniform3iv(WebGLUniformLocation location, GLsizei count, const GLint *value)
    {

    }

    void uniform4iv(WebGLUniformLocation location, GLsizei count, const GLint *value)
    {

    }

    void uniformMatrix2fv(WebGLUniformLocation location, GLsizei count, GLboolean transpose, const GLfloat *value)
    {

    }

    void uniformMatrix3fv(WebGLUniformLocation location, GLsizei count, GLboolean transpose, const GLfloat *value)
    {

    }

    void uniformMatrix4fv(WebGLUniformLocation location, GLsizei count, GLboolean transpose, const GLfloat *value)
    {

    }

    void useProgram(WebGLProgram program)
    {

    }

    void validateProgram(WebGLProgram program)
    {

    }

    void vertexAttrib1f(GLuint index, GLfloat x)
    {

    }

    void vertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
    {

    }

    void vertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
    {

    }

    void vertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {

    }

    void vertexAttrib1fv(GLuint index, const GLfloat *v)
    {

    }

    void vertexAttrib2fv(GLuint index, const GLfloat *v)
    {

    }

    void vertexAttrib3fv(GLuint index, const GLfloat *v)
    {

    }

    void vertexAttrib4fv(GLuint index, const GLfloat *v)
    {

    }

    void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset)
    {

    }

    void viewport(GLint x, GLint y, GLsizei width, GLsizei height)
    {

    }

    //
    void submit(Frame* _render)
    {

    }

} // namespace bgfx {
