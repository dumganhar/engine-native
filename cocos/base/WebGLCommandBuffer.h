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

#include "bx/bx_p.h"
#include "bgfx_config.h"

namespace bgfx {

class CommandBuffer
{
    BX_CLASS(CommandBuffer
             , NO_COPY
             , NO_ASSIGNMENT
             );

public:
    CommandBuffer()
    : m_pos(0)
    , m_size(BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE)
    {
        finish();
    }

    enum Enum
    {
        RendererInit,
        RendererShutdownBegin,

        activeTexture,
        attachShader,
        bindAttribLocation,
        bindBuffer,
        bindFramebuffer,
        bindRenderbuffer,
        bindTexture,
        blendColor,
        blendEquation,
        blendEquationSeparate,
        blendFunc,
        blendFuncSeparate,
        bufferData,
        bufferSubData,
        checkFramebufferStatus,
        clear,
        clearColor,
        clearDepthf,
        clearStencil,
        colorMask,
        compileShader,
        compressedTexImage2D,
        compressedTexSubImage2D,
        copyTexImage2D,
        copyTexSubImage2D,
        createProgram,
        createShader,
        cullFace,
        deleteBuffers,
        deleteFramebuffers,
        deleteProgram,
        deleteRenderbuffers,
        deleteShader,
        deleteTextures,
        depthFunc,
        depthMask,
        depthRangef,
        detachShader,
        disable,
        disableVertexAttribArray,
        drawArrays,
        drawElements,
        enable,
        enableVertexAttribArray,
        _finish,
        flush,
        framebufferRenderbuffer,
        framebufferTexture2D,
        frontFace,
        genBuffers,
        generateMipmap,
        genFramebuffers,
        genRenderbuffers,
        genTextures,
        getActiveAttrib,
        getActiveUniform,
        getAttachedShaders,
        getAttribLocation,
        getBooleanv,
        getBufferParameteriv,
        getError,
        getFloatv,
        getFramebufferAttachmentParameteriv,
        getIntegerv,
        getProgramiv,
        getProgramInfoLog,
        getRenderbufferParameteriv,
        getShaderiv,
        getShaderInfoLog,
        getShaderPrecisionFormat,
        getShaderSource,
        getString,
        getTexParameterfv,
        getTexParameteriv,
        getUniformfv,
        getUniformiv,
        getUniformLocation,
        getVertexAttribfv,
        getVertexAttribiv,
        getVertexAttribPointerv,
        hint,
        isBuffer,
        isEnabled,
        isFramebuffer,
        isProgram,
        isRenderbuffer,
        isShader,
        isTexture,
        lineWidth,
        linkProgram,
        pixelStorei,
        polygonOffset,
        readPixels,
        releaseShaderCompiler,
        renderbufferStorage,
        sampleCoverage,
        scissor,
        shaderBinary,
        shaderSource,
        stencilFunc,
        stencilFuncSeparate,
        stencilMask,
        stencilMaskSeparate,
        stencilOp,
        stencilOpSeparate,
        texImage2D,
        texParameterf,
        texParameterfv,
        texParameteri,
        texParameteriv,
        texSubImage2D,
        uniform1f,
        uniform1fv,
        uniform1i,
        uniform1iv,
        uniform2f,
        uniform2fv,
        uniform2i,
        uniform2iv,
        uniform3f,
        uniform3fv,
        uniform3i,
        uniform3iv,
        uniform4f,
        uniform4fv,
        uniform4i,
        uniform4iv,
        uniformMatrix2fv,
        uniformMatrix3fv,
        uniformMatrix4fv,
        useProgram,
        validateProgram,
        vertexAttrib1f,
        vertexAttrib1fv,
        vertexAttrib2f,
        vertexAttrib2fv,
        vertexAttrib3f,
        vertexAttrib3fv,
        vertexAttrib4f,
        vertexAttrib4fv,
        vertexAttribPointer,
        viewport,

        drawBuffer,
        readBuffer,

        End,
        RendererShutdownEnd,

        RequestScreenShot,
    };

    void write(const void* _data, uint32_t _size)
    {
        BX_CHECK(m_size == BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE, "Called write outside start/finish?");
        BX_CHECK(m_pos < m_size, "CommandBuffer::write error (pos: %d, size: %d).", m_pos, m_size);
        bx::memCopy(&m_buffer[m_pos], _data, _size);
        m_pos += _size;
    }

    template<typename Type>
    void write(const Type& _in)
    {
        align(BX_ALIGNOF(Type) );
        write(reinterpret_cast<const uint8_t*>(&_in), sizeof(Type) );
    }

    void read(void* _data, uint32_t _size)
    {
        BX_CHECK(m_pos < m_size, "CommandBuffer::read error (pos: %d, size: %d).", m_pos, m_size);
        bx::memCopy(_data, &m_buffer[m_pos], _size);
        m_pos += _size;
    }

    template<typename Type>
    void read(Type& _in)
    {
        align(BX_ALIGNOF(Type) );
        read(reinterpret_cast<uint8_t*>(&_in), sizeof(Type) );
    }

    const uint8_t* skip(uint32_t _size)
    {
        BX_CHECK(m_pos < m_size, "CommandBuffer::skip error (pos: %d, size: %d).", m_pos, m_size);
        const uint8_t* result = &m_buffer[m_pos];
        m_pos += _size;
        return result;
    }

    template<typename Type>
    void skip()
    {
        align(BX_ALIGNOF(Type) );
        skip(sizeof(Type) );
    }

    void align(uint32_t _alignment)
    {
        const uint32_t mask = _alignment-1;
        const uint32_t pos = (m_pos+mask) & (~mask);
        m_pos = pos;
    }

    void reset()
    {
        m_pos = 0;
    }

    void start()
    {
        m_pos = 0;
        m_size = BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE;
    }

    void finish()
    {
        uint8_t cmd = End;
        write(cmd);
        m_size = m_pos;
        m_pos = 0;
    }

    uint32_t m_pos;
    uint32_t m_size;
    uint8_t m_buffer[BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE];
};

} // namespace bgfx {

