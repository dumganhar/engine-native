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

#include "platform/CCPlatformConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#include <OpenGL/gltypes.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <OpenGLES/gltypes.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/gltypes-android.h"
#else
#error "Please include platform gl header file!"
#endif

#include <string>

namespace bgfx {


class Frame;

class WebGLRenderContext
{
public:
    WebGLRenderContext();
    ~WebGLRenderContext();

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
    GLuint createProgram();
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
    void finish();
    void flush();
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
    GLint getAttribLocation(GLuint program, const GLchar* name);
    void getBooleanv(GLenum pname, GLboolean* params);
    void getBufferParameteriv(GLenum target, GLenum pname, GLint* params);
    GLenum getError();
    void getFloatv(GLenum pname, GLfloat* params);
    void getFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params);
    void getIntegerv(GLenum pname, GLint* params);
    void getProgramiv(GLuint program, GLenum pname, GLint* params);
    void getProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    void getRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params);
    void getShaderiv(GLuint shader, GLenum pname, GLint* params);
    void getShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    void getShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
    const GLubyte* getString(GLenum name);
    void getTexParameterfv(GLenum target, GLenum pname, GLfloat* params);
    void getTexParameteriv(GLenum target, GLenum pname, GLint* params);
    void getUniformfv(GLuint program, GLint location, GLfloat* params);
    void getUniformiv(GLuint program, GLint location, GLint* params);
    GLint getUniformLocation(GLuint program, const GLchar* name);
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
    void renderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
    void sampleCoverage(GLclampf value, GLboolean invert);
    void scissor(GLint x, GLint y, GLsizei width, GLsizei height);
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
    void vertexAttrib1f(GLuint index, GLfloat x);
    void vertexAttrib1fv(GLuint index, const GLfloat* values);
    void vertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
    void vertexAttrib2fv(GLuint index, const GLfloat* values);
    void vertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
    void vertexAttrib3fv(GLuint index, const GLfloat* values);
    void vertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void vertexAttrib4fv(GLuint index, const GLfloat* values);
    void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
    void viewport(GLint x, GLint y, GLsizei width, GLsizei height);

    void drawBuffer(GLenum mode);
    void readBuffer(GLenum mode);

    //
    bool isDeviceRemoved();
    void flip();
    void submit(Frame* _render);

private:
    bool m_flip = false;

//cjh    WebGLBuffer _indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
//    WebGLBuffer _vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
//    WebGLShader _shaders[BGFX_CONFIG_MAX_SHADERS];
//    WebGLProgram _program[BGFX_CONFIG_MAX_PROGRAMS];
//    WebGLTexture _textures[BGFX_CONFIG_MAX_TEXTURES];
//    WebGLFramebuffer _framebuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
//    WebGLRenderbuffer _renderbuffers[BGFX_CONFIG_MAX_RENDER_BUFFERS];
};

} // namespace bgfx {

