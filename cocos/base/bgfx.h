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

#include <stdarg.h> // va_list
#include <stdint.h> // uint32_t
#include <stdlib.h> // NULL

namespace bx { struct AllocatorI; }

/// BGFX
namespace bgfx
{
    /// Fatal error enum.
    ///
    /// @attention C99 equivalent is `bgfx_fatal_t`.
    ///
    struct Fatal
    {
        enum Enum
        {
            DebugCheck,
            InvalidShader,
            UnableToInitialize,
            UnableToCreateTexture,
            DeviceLost,

            Count
        };
    };

    /// Renderer backend type enum.
    ///
    /// @attention C99 equivalent is `bgfx_renderer_type_t`.
    ///
    struct RendererType
    {
        /// Renderer types:
        enum Enum
        {
            Noop,         //!< No rendering.
            Direct3D9,    //!< Direct3D 9.0
            Direct3D11,   //!< Direct3D 11.0
            Direct3D12,   //!< Direct3D 12.0
            Gnm,          //!< GNM
            Metal,        //!< Metal
            OpenGLES,     //!< OpenGL ES 2.0+
            OpenGL,       //!< OpenGL 2.1+
            Vulkan,       //!< Vulkan

            Count
        };
    };

    /// Texture format enum.
    ///
    /// Notation:
    ///
    ///       RGBA16S
    ///       ^   ^ ^
    ///       |   | +-- [ ]Unorm
    ///       |   |     [F]loat
    ///       |   |     [S]norm
    ///       |   |     [I]nt
    ///       |   |     [U]int
    ///       |   +---- Number of bits per component
    ///       +-------- Components
    ///
    /// @attention Availability depends on Caps (see: formats).
    ///
    /// @attention C99 equivalent is `bgfx_texture_format_t`.
    ///
    struct TextureFormat
    {
        /// Texture formats:
        enum Enum
        {
            BC1,          //!< DXT1
            BC2,          //!< DXT3
            BC3,          //!< DXT5
            BC4,          //!< LATC1/ATI1
            BC5,          //!< LATC2/ATI2
            BC6H,         //!< BC6H
            BC7,          //!< BC7
            ETC1,         //!< ETC1 RGB8
            ETC2,         //!< ETC2 RGB8
            ETC2A,        //!< ETC2 RGBA8
            ETC2A1,       //!< ETC2 RGB8A1
            PTC12,        //!< PVRTC1 RGB 2BPP
            PTC14,        //!< PVRTC1 RGB 4BPP
            PTC12A,       //!< PVRTC1 RGBA 2BPP
            PTC14A,       //!< PVRTC1 RGBA 4BPP
            PTC22,        //!< PVRTC2 RGBA 2BPP
            PTC24,        //!< PVRTC2 RGBA 4BPP

            Unknown,      // Compressed formats above.

            R1,
            A8,
            R8,
            R8I,
            R8U,
            R8S,
            R16,
            R16I,
            R16U,
            R16F,
            R16S,
            R32I,
            R32U,
            R32F,
            RG8,
            RG8I,
            RG8U,
            RG8S,
            RG16,
            RG16I,
            RG16U,
            RG16F,
            RG16S,
            RG32I,
            RG32U,
            RG32F,
            RGB8,
            RGB8I,
            RGB8U,
            RGB8S,
            RGB9E5F,
            BGRA8,
            RGBA8,
            RGBA8I,
            RGBA8U,
            RGBA8S,
            RGBA16,
            RGBA16I,
            RGBA16U,
            RGBA16F,
            RGBA16S,
            RGBA32I,
            RGBA32U,
            RGBA32F,
            R5G6B5,
            RGBA4,
            RGB5A1,
            RGB10A2,
            RG11B10F,

            UnknownDepth, // Depth formats below.

            D16,
            D24,
            D24S8,
            D32,
            D16F,
            D24F,
            D32F,
            D0S8,

            Count
        };
    };

/// Callback interface to implement application specific behavior.
/// Cached items are currently used for OpenGL and Direct3D 12 binary
/// shaders.
///
/// @remarks
///   'fatal' and 'trace' callbacks can be called from any thread. Other
///   callbacks are called from the render thread.
///
/// @attention C99 equivalent is `bgfx_callback_interface_t`.
///
struct CallbackI
{
    virtual ~CallbackI() = 0;

    /// This callback is called on unrecoverable errors.
    /// It's not safe to continue (Exluding _code `Fatal::DebugCheck`),
    /// inform the user and terminate the application.
    ///
    /// @param[in] _code Fatal error code.
    /// @param[in] _str More information about error.
    ///
    /// @remarks
    ///   Not thread safe and it can be called from any thread.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.fatal`.
    ///
    virtual void fatal(Fatal::Enum _code, const char* _str) = 0;

    /// Print debug message.
    ///
    /// @param[in] _filePath File path where debug message was generated.
    /// @param[in] _line Line where debug message was generated.
    /// @param[in] _format `printf` style format.
    /// @param[in] _argList Variable arguments list initialized with
    ///   `va_start`.
    ///
    /// @remarks
    ///   Not thread safe and it can be called from any thread.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.trace_vargs`.
    ///
    virtual void traceVargs(
                            const char* _filePath
                            , uint16_t _line
                            , const char* _format
                            , va_list _argList
                            ) = 0;

    /// Profiler region begin.
    ///
    /// @param[in] _name Region name, contains dynamic string.
    /// @param[in] _abgr Color of profiler region.
    /// @param[in] _filePath File path where `profilerBegin` was called.
    /// @param[in] _line Line where `profilerBegin` was called.
    ///
    /// @remarks
    ///   Not thread safe and it can be called from any thread.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.profiler_begin`.
    ///
    virtual void profilerBegin(
                               const char* _name
                               , uint32_t _abgr
                               , const char* _filePath
                               , uint16_t _line
                               ) = 0;

    /// Profiler region begin with string literal name.
    ///
    /// @param[in] _name Region name, contains string literal.
    /// @param[in] _abgr Color of profiler region.
    /// @param[in] _filePath File path where `profilerBeginLiteral` was called.
    /// @param[in] _line Line where `profilerBeginLiteral` was called.
    ///
    /// @remarks
    ///   Not thread safe and it can be called from any thread.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.profiler_begin_literal`.
    ///
    virtual void profilerBeginLiteral(
                                      const char* _name
                                      , uint32_t _abgr
                                      , const char* _filePath
                                      , uint16_t _line
                                      ) = 0;

    /// Profiler region end.
    ///
    /// @remarks
    ///   Not thread safe and it can be called from any thread.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.profiler_end`.
    ///
    virtual void profilerEnd() = 0;

    /// Returns the size of a cached item. Returns 0 if no cached item was
    /// found.
    ///
    /// @param[in] _id Cache id.
    /// @returns Number of bytes to read.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.cache_read_size`.
    ///
    virtual uint32_t cacheReadSize(uint64_t _id) = 0;

    /// Read cached item.
    ///
    /// @param[in] _id Cache id.
    /// @param[in] _data Buffer where to read data.
    /// @param[in] _size Size of data to read.
    ///
    /// @returns True if data is read.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.cache_read`.
    ///
    virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) = 0;

    /// Write cached item.
    ///
    /// @param[in] _id Cache id.
    /// @param[in] _data Data to write.
    /// @param[in] _size Size of data to write.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.cache_write`.
    ///
    virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) = 0;

    /// Screenshot captured. Screenshot format is always 4-byte BGRA.
    ///
    /// @param[in] _filePath File path.
    /// @param[in] _width Image width.
    /// @param[in] _height Image height.
    /// @param[in] _pitch Number of bytes to skip between the start of
    ///   each horizontal line of the image.
    /// @param[in] _data Image data.
    /// @param[in] _size Image size.
    /// @param[in] _yflip If true, image origin is bottom left.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.screen_shot`.
    ///
    virtual void screenShot(
                            const char* _filePath
                            , uint32_t _width
                            , uint32_t _height
                            , uint32_t _pitch
                            , const void* _data
                            , uint32_t _size
                            , bool _yflip
                            ) = 0;

    /// Called when a video capture begins.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.capture_begin`.
    ///
    virtual void captureBegin(
                              uint32_t _width
                              , uint32_t _height
                              , uint32_t _pitch
                              , TextureFormat::Enum _format
                              , bool _yflip
                              ) = 0;

    /// Called when a video capture ends.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.capture_end`.
    ///
    virtual void captureEnd() = 0;

    /// Captured frame.
    ///
    /// @param[in] _data Image data.
    /// @param[in] _size Image size.
    ///
    /// @attention C99 equivalent is `bgfx_callback_vtbl.capture_frame`.
    ///
    virtual void captureFrame(const void* _data, uint32_t _size) = 0;
};

inline CallbackI::~CallbackI()
{
}

/// Backbuffer resolution and reset parameters.
///
/// @attention C99 equivalent is `bgfx_resolution_t`.
///
struct Resolution
{
    Resolution();

    uint32_t width;  //!< Backbuffer width.
    uint32_t height; //!< Backbuffer height.
    uint32_t reset;     //!< Reset parameters.
};

/// Initialization parameters used by `bgfx::init`.
///
/// @attention C99 equivalent is `bgfx_init_t`.
///
struct Init
{
    Init();

    /// Select rendering backend. When set to RendererType::Count
    /// a default rendering backend will be selected appropriate to the platform.
    /// See: `bgfx::RendererType`
    RendererType::Enum type;

    /// Vendor PCI id. If set to `BGFX_PCI_ID_NONE` it will select the first
    /// device.
    ///   - `BGFX_PCI_ID_NONE` - Autoselect adapter.
    ///   - `BGFX_PCI_ID_SOFTWARE_RASTERIZER` - Software rasterizer.
    ///   - `BGFX_PCI_ID_AMD` - AMD adapter.
    ///   - `BGFX_PCI_ID_INTEL` - Intel adapter.
    ///   - `BGFX_PCI_ID_NVIDIA` - nVidia adapter.
    uint16_t vendorId;

    /// Device id. If set to 0 it will select first device, or device with
    /// matching id.
    uint16_t deviceId;

    Resolution resolution; //!< Backbuffer resolution and reset parameters.

    struct Limits
    {
        uint16_t maxEncoders;     //!< Maximum number of encoder threads.
        uint32_t transientVbSize; //!<
        uint32_t transientIbSize; //!<
    };

    Limits limits;

    /// Provide application specific callback interface.
    /// See: `bgfx::CallbackI`
    CallbackI* callback;

    /// Custom allocator. When a custom allocator is not
    /// specified, bgfx uses the CRT allocator. Bgfx assumes
    /// custom allocator is thread safe.
    bx::AllocatorI* allocator;
};

/// Initialize bgfx library.
///
/// @param[in] _init Initialization parameters. See: `bgfx::Init` for more info.
///
/// @returns `true` if initialization was successful.
///
/// @attention C99 equivalent is `bgfx_init`.
///
bool init(const Init& _init = {});

/// Shutdown bgfx library.
///
/// @attention C99 equivalent is `bgfx_shutdown`.
///
void shutdown();


/// Memory release callback.
///
/// param[in] _ptr Pointer to allocated data.
/// param[in] _userData User defined data if needed.
///
/// @attention C99 equivalent is `bgfx_release_fn_t`.
///
typedef void (*ReleaseFn)(void* _ptr, void* _userData);

/// Memory obtained by calling `bgfx::alloc`, `bgfx::copy`, or `bgfx::makeRef`.
///
/// @attention C99 equivalent is `bgfx_memory_t`.
///
struct Memory
{
    uint8_t* data; //!< Pointer to data.
    uint32_t size; //!< Data size.
};

/// Renderer capabilities.
///
/// @attention C99 equivalent is `bgfx_caps_t`.
///
struct Caps
{
    /// Renderer backend type. See: `bgfx::RendererType`
    RendererType::Enum rendererType;

    /// Supported functionality.
    ///
    /// @attention See BGFX_CAPS_* flags at https://bkaradzic.github.io/bgfx/bgfx.html#available-caps
    ///
    uint64_t supported;

    uint16_t vendorId;         //!< Selected GPU vendor PCI id.
    uint16_t deviceId;         //!< Selected GPU device id.
    bool     homogeneousDepth; //!< True when NDC depth is in [-1, 1] range, otherwise its [0, 1].
    bool     originBottomLeft; //!< True when NDC origin is at bottom left.
    uint8_t  numGPUs;          //!< Number of enumerated GPUs.

    /// GPU info.
    ///
    /// @attention C99 equivalent is `bgfx_caps_gpu_t`.
    ///
    struct GPU
    {
        uint16_t vendorId; //!< Vendor PCI id. See `BGFX_PCI_ID_*`.
        uint16_t deviceId; //!< Device id.
    };

    GPU gpu[4]; //!< Enumerated GPUs.

    struct Limits
    {
        uint32_t maxDrawCalls;            //!< Maximum number of draw calls.
        uint32_t maxBlits;                //!< Maximum number of blit calls.
        uint32_t maxTextureSize;          //!< Maximum texture size.
        uint32_t maxTextureLayers;        //!< Maximum texture layers.
        uint32_t maxViews;                //!< Maximum number of views.
        uint32_t maxFrameBuffers;         //!< Maximum number of frame buffer handles.
        uint32_t maxFBAttachments;        //!< Maximum number of frame buffer attachments.
        uint32_t maxPrograms;             //!< Maximum number of program handles.
        uint32_t maxShaders;              //!< Maximum number of shader handles.
        uint32_t maxTextures;             //!< Maximum number of texture handles.
        uint32_t maxTextureSamplers;      //!< Maximum number of texture samplers.
        uint32_t maxVertexDecls;          //!< Maximum number of vertex format declarations.
        uint32_t maxVertexStreams;        //!< Maximum number of vertex streams.
        uint32_t maxIndexBuffers;         //!< Maximum number of index buffer handles.
        uint32_t maxVertexBuffers;        //!< Maximum number of vertex buffer handles.
        uint32_t maxDynamicIndexBuffers;  //!< Maximum number of dynamic index buffer handles.
        uint32_t maxDynamicVertexBuffers; //!< Maximum number of dynamic vertex buffer handles.
        uint32_t maxUniforms;             //!< Maximum number of uniform handles.
        uint32_t maxOcclusionQueries;     //!< Maximum number of occlusion query handles.
        uint32_t maxEncoders;             //!< Maximum number of encoder threads.
        uint32_t transientVbSize;         //!<
        uint32_t transientIbSize;         //!<
    };

    Limits limits;

    /// Supported texture format capabilities flags:
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_NONE` - Texture format is not supported.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_2D` - Texture format is supported.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB` - Texture as sRGB format is supported.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED` - Texture format is emulated.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_3D` - Texture format is supported.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB` - Texture as sRGB format is supported.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED` - Texture format is emulated.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE` - Texture format is supported.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB` - Texture as sRGB format is supported.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED` - Texture format is emulated.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_VERTEX` - Texture format can be used from vertex shader.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_IMAGE` - Texture format can be used as image from compute
    ///     shader.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER` - Texture format can be used as frame
    ///     buffer.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA` - Texture format can be used as MSAA
    ///     frame buffer.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_MSAA` - Texture can be sampled as MSAA.
    ///   - `BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN` - Texture format supports auto-generated
    ///     mips.
    uint16_t formats[TextureFormat::Count];
};

//void clear(GLbitfield mask);
//void clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
//GLuint createBuffer();

/// Advance to next frame. When using multithreaded renderer, this call
/// just swaps internal buffers, kicks render thread, and returns. In
/// singlethreaded renderer this call does frame rendering.
///
/// @param[in] _capture Capture frame with graphics debugger.
///
/// @returns Current frame number. This might be used in conjunction with
///   double/multi buffering data outside the library and passing it to
///   library via `bgfx::makeRef` calls.
///
/// @attention C99 equivalent is `bgfx_frame`.
///
uint32_t frame(bool _capture = false);

} // namespace bgfx

