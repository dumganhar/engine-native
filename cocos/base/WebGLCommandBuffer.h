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

        createBuffer,
        createFramebuffer,
        createProgram,
        createRenderbuffer,
        createShader,
        createTexture,

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
        clearDepth,
        clearStencil,
        colorMask,
        compileShader,
        compressedTexImage2D,
        compressedTexSubImage2D,
        copyTexImage2D,
        copyTexSubImage2D,
        cullFace,
        depthFunc,
        depthMask,
        depthRange,
        detachShader,
        disable,
        disableVertexAttribArray,
        drawArrays,
        drawElements,
        enable,
        enableVertexAttribArray,
        glFinish,
        flush,
        framebufferRenderbuffer,
        framebufferTexture2D,
        frontFace,
        generateMipmap,
        getActiveAttrib,
        getActiveUniform,
        getAttachedShaders,
        getAttribLocation,
        getBufferParameter, //cjh
        getParameter,
        getError,
        getFramebufferAttachmentParameter, //cjh
        getProgramParameter,
        getProgramInfoLog,
        getRenderbufferParameter, //cjh
        getShaderParameter,
        getShaderPrecisionFormat,
        getShaderInfoLog,
        getShaderSource,
        getTexParameter,
        getUniform,
        getUniformLocation,
        getVertexAttrib,
        getVertexAttribOffset,
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
        renderbufferStorage,
        sampleCoverage,
        scissor,
        shaderSource,
        stencilFunc,
        stencilFuncSeparate,
        stencilMask,
        stencilMaskSeparate,
        stencilOp,
        stencilOpSeparate,
        texImage2D,
        texParameterf,
        texParameteri,
        texSubImage2D,
        uniform1f,
        uniform2f,
        uniform3f,
        uniform4f,
        uniform1i,
        uniform2i,
        uniform3i,
        uniform4i,
        uniform1fv,
        uniform2fv,
        uniform3fv,
        uniform4fv,
        uniform1iv,
        uniform2iv,
        uniform3iv,
        uniform4iv,
        uniformMatrix2fv,
        uniformMatrix3fv,
        uniformMatrix4fv,
        useProgram,
        validateProgram,
        vertexAttrib1f,
        vertexAttrib2f,
        vertexAttrib3f,
        vertexAttrib4f,
        vertexAttrib1fv,
        vertexAttrib2fv,
        vertexAttrib3fv,
        vertexAttrib4fv,
        vertexAttribPointer,
        viewport,

        End,
        RendererShutdownEnd,

        deleteBuffer,
        deleteFramebuffer,
        deleteProgram,
        deleteRenderbuffer,
        deleteShader,
        deleteTexture,

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

