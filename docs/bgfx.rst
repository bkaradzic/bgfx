API Reference
=============


.. note::
	
    If you're just getting started with bgfx, you might get more out of these simple walkthroughs for how to use bgfx's API:
    
    - `Hello, bgfx! <https://dev.to/pperon/hello-bgfx-4dka>`_
    - `bgfx-minimal-example <https://github.com/jpcy/bgfx-minimal-example#bgfx-minimal-example>`_
    - `Using the bgfx library with C++ on Ubuntu <https://www.sandeepnambiar.com/getting-started-with-bgfx/>`_

General
-------

Initialization and Shutdown
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenstruct:: bgfx::Init
    :members:

.. doxygenstruct:: bgfx::Resolution
    :members:

.. doxygenfunction:: bgfx::init

.. doxygendefine:: BGFX_PCI_ID_NONE
.. doxygendefine:: BGFX_PCI_ID_SOFTWARE_RASTERIZER
.. doxygendefine:: BGFX_PCI_ID_AMD
.. doxygendefine:: BGFX_PCI_ID_INTEL
.. doxygendefine:: BGFX_PCI_ID_NVIDIA

.. doxygenstruct:: bgfx::CallbackI
    :members:

.. doxygenfunction:: bgfx::shutdown

Updating
~~~~~~~~

Reset
*****

.. doxygenfunction:: bgfx::reset

.. doxygendefine:: BGFX_RESET_NONE
.. doxygendefine:: BGFX_RESET_FULLSCREEN
.. doxygendefine:: BGFX_RESET_MSAA_X2
.. doxygendefine:: BGFX_RESET_MSAA_X4
.. doxygendefine:: BGFX_RESET_MSAA_X8
.. doxygendefine:: BGFX_RESET_MSAA_X16
.. doxygendefine:: BGFX_RESET_VSYNC
.. doxygendefine:: BGFX_RESET_MAXANISOTROPY
.. doxygendefine:: BGFX_RESET_CAPTURE
.. doxygendefine:: BGFX_RESET_FLUSH_AFTER_RENDER
.. doxygendefine:: BGFX_RESET_FLIP_AFTER_RENDER
.. doxygendefine:: BGFX_RESET_SRGB_BACKBUFFER
.. doxygendefine:: BGFX_RESET_HDR10
.. doxygendefine:: BGFX_RESET_HIDPI
.. doxygendefine:: BGFX_RESET_DEPTH_CLAMP

Frame
*****

.. doxygenfunction:: bgfx::frame

Debug
~~~~~

Debug Features
**************

.. doxygenfunction:: bgfx::setDebug

Debug Flags
***********

.. doxygendefine:: BGFX_DEBUG_NONE
.. doxygendefine:: BGFX_DEBUG_WIREFRAME
.. doxygendefine:: BGFX_DEBUG_IFH
.. doxygendefine:: BGFX_DEBUG_STATS
.. doxygendefine:: BGFX_DEBUG_TEXT
.. doxygendefine:: BGFX_DEBUG_PROFILER

Debug Text Display
******************

.. doxygenfunction:: bgfx::dbgTextClear
.. doxygenfunction:: bgfx::dbgTextPrintf
.. doxygenfunction:: bgfx::dbgTextPrintfVargs
.. doxygenfunction:: bgfx::dbgTextImage

Querying information
~~~~~~~~~~~~~~~~~~~~

Renderer
********

.. doxygenfunction:: bgfx::getSupportedRenderers

.. doxygenfunction:: bgfx::getRendererType

.. doxygenstruct:: bgfx::RendererType
    :members:

Capabilities
************

.. doxygenfunction:: bgfx::getCaps

.. doxygenstruct:: bgfx::Caps
    :members:

Available Caps
""""""""""""""

.. doxygendefine:: BGFX_CAPS_ALPHA_TO_COVERAGE
.. doxygendefine:: BGFX_CAPS_BLEND_INDEPENDENT
.. doxygendefine:: BGFX_CAPS_COMPUTE
.. doxygendefine:: BGFX_CAPS_CONSERVATIVE_RASTER
.. doxygendefine:: BGFX_CAPS_DRAW_INDIRECT
.. doxygendefine:: BGFX_CAPS_FRAGMENT_DEPTH
.. doxygendefine:: BGFX_CAPS_FRAGMENT_ORDERING
.. doxygendefine:: BGFX_CAPS_GRAPHICS_DEBUGGER
.. doxygendefine:: BGFX_CAPS_HDR10
.. doxygendefine:: BGFX_CAPS_HIDPI
.. doxygendefine:: BGFX_CAPS_IMAGE_RW
.. doxygendefine:: BGFX_CAPS_INDEX32
.. doxygendefine:: BGFX_CAPS_INSTANCING
.. doxygendefine:: BGFX_CAPS_OCCLUSION_QUERY
.. doxygendefine:: BGFX_CAPS_RENDERER_MULTITHREADED
.. doxygendefine:: BGFX_CAPS_SWAP_CHAIN
.. doxygendefine:: BGFX_CAPS_TEXTURE_2D_ARRAY
.. doxygendefine:: BGFX_CAPS_TEXTURE_3D
.. doxygendefine:: BGFX_CAPS_TEXTURE_BLIT
.. doxygendefine:: BGFX_CAPS_TEXTURE_COMPARE_ALL
.. doxygendefine:: BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
.. doxygendefine:: BGFX_CAPS_TEXTURE_CUBE_ARRAY
.. doxygendefine:: BGFX_CAPS_TEXTURE_DIRECT_ACCESS
.. doxygendefine:: BGFX_CAPS_TEXTURE_READ_BACK
.. doxygendefine:: BGFX_CAPS_VERTEX_ATTRIB_HALF
.. doxygendefine:: BGFX_CAPS_VERTEX_ATTRIB_UINT10
.. doxygendefine:: BGFX_CAPS_VERTEX_ID

Statistics
**********

.. doxygenfunction:: bgfx::getStats

.. doxygenstruct:: bgfx::Stats
    :members:

.. doxygenstruct:: bgfx::ViewStats
    :members:

.. doxygenstruct:: bgfx::EncoderStats
    :members:

Platform specific
~~~~~~~~~~~~~~~~~

These are platform specific APIs.
It is only necessary to use these APIs in conjunction with creating windows.

.. doxygenfunction:: bgfx::renderFrame

.. doxygenstruct:: bgfx::RenderFrame
    :members:

.. doxygenfunction:: bgfx::setPlatformData

.. doxygenstruct:: bgfx::PlatformData
    :members:

.. doxygenfunction:: bgfx::getInternalData

.. doxygenstruct:: bgfx::InternalData
    :members:

.. doxygenfunction:: bgfx::overrideInternal(TextureHandle _handle, uintptr_t _ptr)
.. doxygenfunction:: bgfx::overrideInternal(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint64_t _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE)

Miscellaneous
~~~~~~~~~~~~~

.. doxygenfunction:: bgfx::vertexPack
.. doxygenfunction:: bgfx::vertexUnpack
.. doxygenfunction:: bgfx::vertexConvert
.. doxygenfunction:: bgfx::weldVertices

.. doxygenstruct:: bgfx::TopologyConvert
    :members:

.. doxygenfunction:: bgfx::topologyConvert

.. doxygenstruct:: bgfx::TopologySort
    :members:

.. doxygenfunction:: bgfx::topologySortTriList
.. doxygenfunction:: bgfx::discard
.. doxygenfunction:: bgfx::touch
.. doxygenfunction:: bgfx::setPaletteColor(uint8_t _index, uint32_t _rgba)
.. doxygenfunction:: bgfx::setPaletteColor(uint8_t _index, const float _rgba[4])
.. doxygenfunction:: bgfx::setPaletteColor(uint8_t _index, float _r, float _g, float _b, float _a)
.. doxygenfunction:: bgfx::requestScreenShot

Views
-----

Views are the primary sorting mechanism in bgfx.
They represent buckets of draw and compute calls, or what are often known as 'passes'.

When compute calls and draw calls occupy the same bucket, the compute calls will be sorted to execute first.
Compute calls are always executed in order of submission, while draw calls are sorted by internal state if
the View is not in sequential mode.
In most cases where the z-buffer is used, this change in order does not affect the desired output.
When draw call order needs to be preserved (e.g. when rendering GUIs), Views can be set to use sequential mode with `bgfx::setViewMode`.
Sequential order is less efficient, because it doesn't allow state change optimization, and should be avoided when possible.

By default, Views are sorted by their View ID, in ascending order.
For dynamic renderers where the right order might not be known until the last moment,
View IDs can be changed to use arbitrary ordering with `bgfx::setViewOrder`.

A View's state is preserved between frames.

.. doxygenfunction:: bgfx::setViewName
.. doxygenfunction:: bgfx::setViewRect(ViewId _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
.. doxygenfunction:: bgfx::setViewRect(ViewId _id, uint16_t _x, uint16_t _y, BackbufferRatio::Enum _ratio)
.. doxygenfunction:: bgfx::setViewScissor
.. doxygenfunction:: bgfx::setViewClear(ViewId _id, uint16_t _flags, uint32_t _rgba = 0x000000ff, float _depth = 1.0f, uint8_t _stencil = 0)
.. doxygenfunction:: bgfx::setViewClear(ViewId _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0 = UINT8_MAX, uint8_t _1 = UINT8_MAX, uint8_t _2 = UINT8_MAX, uint8_t _3 = UINT8_MAX, uint8_t _4 = UINT8_MAX, uint8_t _5 = UINT8_MAX, uint8_t _6 = UINT8_MAX, uint8_t _7 = UINT8_MAX)

.. doxygenstruct:: bgfx::ViewMode
    :members:

.. doxygenfunction:: bgfx::setViewMode
.. doxygenfunction:: bgfx::setViewFrameBuffer
.. doxygenfunction:: bgfx::setViewTransform
.. doxygenfunction:: bgfx::setViewOrder
.. doxygenfunction:: bgfx::resetView

Encoder
-------

Encoder
~~~~~~~

API for multi-threaded submission.

.. doxygenfunction:: bgfx::begin
.. doxygenfunction:: bgfx::end

.. doxygenstruct:: bgfx::Encoder
    :members:

Draw
~~~~

Draw state is not preserved between two draw calls.
All state is cleared after calling `bgfx::submit`.

State
*****

Debug
*****

.. doxygenfunction:: bgfx::setMarker
.. doxygenfunction:: bgfx::setName(ShaderHandle _handle, const char *_name, int32_t _len = INT32_MAX)
.. doxygenfunction:: bgfx::setName(TextureHandle _handle, const char *_name, int32_t _len = INT32_MAX)

State
*****

.. doxygenfunction:: bgfx::setState

State Flags
***********

**Write**

.. doxygendefine:: BGFX_STATE_WRITE_R
.. doxygendefine:: BGFX_STATE_WRITE_G
.. doxygendefine:: BGFX_STATE_WRITE_B
.. doxygendefine:: BGFX_STATE_WRITE_RGB
.. doxygendefine:: BGFX_STATE_WRITE_A
.. doxygendefine:: BGFX_STATE_WRITE_Z

**Depth Test**

.. doxygendefine:: BGFX_STATE_DEPTH_TEST_LESS
.. doxygendefine:: BGFX_STATE_DEPTH_TEST_LEQUAL
.. doxygendefine:: BGFX_STATE_DEPTH_TEST_EQUAL
.. doxygendefine:: BGFX_STATE_DEPTH_TEST_GEQUAL
.. doxygendefine:: BGFX_STATE_DEPTH_TEST_GREATER
.. doxygendefine:: BGFX_STATE_DEPTH_TEST_NOTEQUAL
.. doxygendefine:: BGFX_STATE_DEPTH_TEST_NEVER
.. doxygendefine:: BGFX_STATE_DEPTH_TEST_ALWAYS

**Blend Mode**

.. doxygendefine:: BGFX_STATE_BLEND_ZERO
.. doxygendefine:: BGFX_STATE_BLEND_ONE
.. doxygendefine:: BGFX_STATE_BLEND_SRC_COLOR
.. doxygendefine:: BGFX_STATE_BLEND_INV_SRC_COLOR
.. doxygendefine:: BGFX_STATE_BLEND_SRC_ALPHA
.. doxygendefine:: BGFX_STATE_BLEND_INV_SRC_ALPHA
.. doxygendefine:: BGFX_STATE_BLEND_DST_ALPHA
.. doxygendefine:: BGFX_STATE_BLEND_INV_DST_ALPHA
.. doxygendefine:: BGFX_STATE_BLEND_DST_COLOR
.. doxygendefine:: BGFX_STATE_BLEND_INV_DST_COLOR
.. doxygendefine:: BGFX_STATE_BLEND_SRC_ALPHA_SAT
.. doxygendefine:: BGFX_STATE_BLEND_FACTOR
.. doxygendefine:: BGFX_STATE_BLEND_INV_FACTOR

**Blend Equaation**

.. doxygendefine:: BGFX_STATE_BLEND_EQUATION_ADD
.. doxygendefine:: BGFX_STATE_BLEND_EQUATION_SUB
.. doxygendefine:: BGFX_STATE_BLEND_EQUATION_REVSUB
.. doxygendefine:: BGFX_STATE_BLEND_EQUATION_MIN
.. doxygendefine:: BGFX_STATE_BLEND_EQUATION_MAX

**Primitive Culling**

.. doxygendefine:: BGFX_STATE_CULL_CW
.. doxygendefine:: BGFX_STATE_CULL_CCW

**Primitive Type**

.. doxygendefine:: BGFX_STATE_PT_TRISTRIP
.. doxygendefine:: BGFX_STATE_PT_LINES
.. doxygendefine:: BGFX_STATE_PT_LINESTRIP
.. doxygendefine:: BGFX_STATE_PT_POINTS

**Misc**

.. doxygendefine:: BGFX_STATE_BLEND_INDEPENDENT
.. doxygendefine:: BGFX_STATE_BLEND_ALPHA_TO_COVERAGE

.. doxygendefine:: BGFX_STATE_MSAA
.. doxygendefine:: BGFX_STATE_LINEAA

Stencil
*******

.. doxygenfunction:: bgfx::setStencil

Stencil Flags
*************

.. doxygendefine:: BGFX_STENCIL_TEST_LESS

Scissor
*******

If the Scissor rectangle needs to be changed for
every draw call in a View, use `bgfx::setScissor`.
Otherwise, use `bgfx::setViewScissor`.

.. doxygenfunction:: bgfx::setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
.. doxygenfunction:: bgfx::setScissor(uint16_t _cache = UINT16_MAX)

Transform
*********

.. doxygenfunction:: bgfx::allocTransform
.. doxygenfunction:: bgfx::setTransform(const void *_mtx, uint16_t _num = 1)
.. doxygenfunction:: bgfx::setTransform(uint32_t _cache, uint16_t _num = 1)

Conditional Rendering
*********************

.. doxygenfunction:: bgfx::setCondition


Buffers
*******

.. doxygenfunction:: bgfx::setIndexBuffer(IndexBufferHandle _handle)
.. doxygenfunction:: bgfx::setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
.. doxygenfunction:: bgfx::setIndexBuffer(DynamicIndexBufferHandle _handle)
.. doxygenfunction:: bgfx::setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)

.. doxygenstruct:: bgfx::TransientIndexBuffer
    :members:

.. doxygenfunction:: bgfx::setIndexBuffer(const TransientIndexBuffer *_tib)
.. doxygenfunction:: bgfx::setIndexBuffer(const TransientIndexBuffer *_tib, uint32_t _firstIndex, uint32_t _numIndices)

.. doxygenfunction:: bgfx::setVertexBuffer(uint8_t _stream, VertexBufferHandle _handle)
.. doxygenfunction:: bgfx::setVertexBuffer(uint8_t _stream, VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE)
.. doxygenfunction:: bgfx::setVertexBuffer(uint8_t _stream, DynamicVertexBufferHandle _handle)
.. doxygenfunction:: bgfx::setVertexBuffer(uint8_t _stream, DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE)

.. doxygenstruct:: bgfx::TransientVertexBuffer
    :members:

.. doxygenfunction:: bgfx::setVertexBuffer(uint8_t _stream, const TransientVertexBuffer *_tvb)
.. doxygenfunction:: bgfx::setVertexBuffer(uint8_t _stream, const TransientVertexBuffer *_tvb, uint32_t _startVertex, uint32_t _numVertices, VertexLayoutHandle _layoutHandle = BGFX_INVALID_HANDLE)
.. doxygenfunction:: bgfx::setVertexCount

.. doxygenstruct:: bgfx::InstanceDataBuffer
    :members:

.. doxygenfunction:: bgfx::setInstanceDataBuffer(const InstanceDataBuffer *_idb)
.. doxygenfunction:: bgfx::setInstanceDataBuffer(const InstanceDataBuffer *_idb, uint32_t _start, uint32_t _num)
.. doxygenfunction:: bgfx::setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _start, uint32_t _num)
.. doxygenfunction:: bgfx::setInstanceDataBuffer(DynamicVertexBufferHandle _handle, uint32_t _start, uint32_t _num)
.. doxygenfunction:: bgfx::setInstanceCount

Textures
********

.. doxygenfunction:: bgfx::setTexture(uint8_t, UniformHandle, TextureHandle, uint32_t)

Submit
******

In Views, all draw commands are executed **after** blit and compute commands.

.. doxygenfunction:: bgfx::submit(ViewId _id, ProgramHandle _program, uint32_t _depth = 0, uint8_t _flags = BGFX_DISCARD_ALL)
.. doxygenfunction:: bgfx::submit(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint32_t _depth = 0, uint8_t _flags = BGFX_DISCARD_ALL)
.. doxygenfunction:: bgfx::submit(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start = 0, uint16_t _num = 1, uint32_t _depth = 0, uint8_t _flags = BGFX_DISCARD_ALL)

Compute
~~~~~~~

Compute state is not preserved between compute dispatches; all state is cleared after calling `bgfx::dispatch`.

Buffers
*******

.. doxygenstruct:: bgfx::Access
    :members:

.. doxygenfunction:: bgfx::setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access)
.. doxygenfunction:: bgfx::setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access)
.. doxygenfunction:: bgfx::setBuffer(uint8_t _stage, DynamicIndexBufferHandle _handle, Access::Enum _access)
.. doxygenfunction:: bgfx::setBuffer(uint8_t _stage, DynamicVertexBufferHandle _handle, Access::Enum _access)
.. doxygenfunction:: bgfx::setBuffer(uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access)

Images
******

.. doxygenfunction:: bgfx::setImage(uint8_t, TextureHandle, uint8_t, Access::Enum, TextureFormat::Enum)

Dispatch
********

In Views, all draw commands are executed **after** blit and compute commands.

.. doxygenfunction:: bgfx::dispatch(ViewId _id, ProgramHandle _handle, uint32_t _numX = 1, uint32_t _numY = 1, uint32_t _numZ = 1, uint8_t _flags = BGFX_DISCARD_ALL)
.. doxygenfunction:: bgfx::dispatch(ViewId _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start = 0, uint16_t _num = 1, uint8_t _flags = BGFX_DISCARD_ALL)

Blit
~~~~

In Views, all draw commands are executed **after** blit and compute commands.

.. doxygenfunction:: bgfx::blit(ViewId _id, TextureHandle _dst, uint16_t _dstX, uint16_t _dstY, TextureHandle _src, uint16_t _srcX = 0, uint16_t _srcY = 0, uint16_t _width = UINT16_MAX, uint16_t _height = UINT16_MAX)
.. doxygenfunction:: bgfx::blit(ViewId _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip = 0, uint16_t _srcX = 0, uint16_t _srcY = 0, uint16_t _srcZ = 0, uint16_t _width = UINT16_MAX, uint16_t _height = UINT16_MAX, uint16_t _depth = UINT16_MAX)

Resources
---------

.. doxygenstruct:: bgfx::Memory
    :members:

.. doxygenfunction:: bgfx::alloc
.. doxygenfunction:: bgfx::copy
.. doxygenfunction:: bgfx::makeRef

Shaders and Programs
~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: bgfx::createShader
.. doxygenfunction:: bgfx::getShaderUniforms
.. doxygenfunction:: bgfx::destroy(ShaderHandle _handle)
.. doxygenfunction:: bgfx::createProgram(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders = false)
.. doxygenfunction:: bgfx::createProgram(ShaderHandle _csh, bool _destroyShader = false)
.. doxygenfunction:: bgfx::destroy(ProgramHandle _handle)

Uniforms
~~~~~~~~

.. doxygenfunction:: bgfx::createUniform
.. doxygenfunction:: bgfx::getUniformInfo
.. doxygenfunction:: bgfx::destroy(UniformHandle _handle)

.. doxygenstruct:: bgfx::UniformType
    :members:

.. doxygenstruct:: bgfx::UniformInfo
    :members:

Vertex Buffers
~~~~~~~~~~~~~~

.. doxygenfunction:: bgfx::createVertexLayout
.. doxygenfunction:: bgfx::destroy(VertexLayoutHandle _handle)

.. doxygenfunction:: bgfx::createVertexBuffer
.. doxygenfunction:: bgfx::setName(VertexBufferHandle _handle, const char *_name, int32_t _len = INT32_MAX)
.. doxygenfunction:: bgfx::destroy(VertexBufferHandle _handle)

.. doxygenstruct:: bgfx::VertexLayout
    :members:

.. doxygenstruct:: bgfx::Attrib
    :members:

.. doxygenstruct:: bgfx::AttribType
    :members:

.. doxygenfunction:: bgfx::createDynamicVertexBuffer(uint32_t _num, const VertexLayout &_layout, uint16_t _flags = BGFX_BUFFER_NONE)
.. doxygenfunction:: bgfx::createDynamicVertexBuffer(const Memory *_mem, const VertexLayout &_layout, uint16_t _flags = BGFX_BUFFER_NONE)
.. doxygenfunction:: bgfx::update(DynamicVertexBufferHandle _handle, uint32_t _startVertex, const Memory *_mem)
.. doxygenfunction:: bgfx::destroy(DynamicVertexBufferHandle _handle)
.. doxygenfunction:: bgfx::getAvailTransientVertexBuffer
.. doxygenfunction:: bgfx::allocTransientVertexBuffer

Index Buffers
~~~~~~~~~~~~~

.. doxygenfunction:: bgfx::createIndexBuffer
.. doxygenfunction:: bgfx::setName(IndexBufferHandle _handle, const char *_name, int32_t _len = INT32_MAX)
.. doxygenfunction:: bgfx::destroy(IndexBufferHandle _handle)
.. doxygenfunction:: bgfx::createDynamicIndexBuffer(uint32_t _num, uint16_t _flags = BGFX_BUFFER_NONE)
.. doxygenfunction:: bgfx::createDynamicIndexBuffer(const Memory *_mem, uint16_t _flags = BGFX_BUFFER_NONE)
.. doxygenfunction:: bgfx::update(DynamicIndexBufferHandle _handle, uint32_t _startIndex, const Memory *_mem)
.. doxygenfunction:: bgfx::destroy(DynamicIndexBufferHandle _handle)
.. doxygenfunction:: bgfx::getAvailTransientIndexBuffer
.. doxygenfunction:: bgfx::allocTransientIndexBuffer

Textures
~~~~~~~~

.. doxygenstruct:: bgfx::TextureFormat
    :members:

.. doxygenfunction:: bgfx::isTextureValid

.. doxygenstruct:: bgfx::TextureInfo
    :members:

.. doxygenfunction:: bgfx::calcTextureSize
.. doxygenfunction:: bgfx::createTexture

.. doxygenfunction:: bgfx::createTexture2D(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint64_t _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE, const Memory *_mem = NULL)
.. doxygenfunction:: bgfx::createTexture2D(BackbufferRatio::Enum _ratio, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint64_t _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE)
.. doxygenfunction:: bgfx::updateTexture2D
.. doxygenfunction:: bgfx::createTexture3D
.. doxygenfunction:: bgfx::updateTexture3D
.. doxygenfunction:: bgfx::createTextureCube
.. doxygenfunction:: bgfx::updateTextureCube
.. doxygenfunction:: bgfx::readTexture(TextureHandle, void *, uint8_t)
.. doxygenfunction:: bgfx::getDirectAccessPtr
.. doxygenfunction:: bgfx::destroy(TextureHandle _handle)

Frame Buffers
~~~~~~~~~~~~~

.. doxygenfunction:: bgfx::createFrameBuffer(uint16_t _width, uint16_t _height, TextureFormat::Enum _format, uint64_t _textureFlags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP)
.. doxygenfunction:: bgfx::createFrameBuffer(BackbufferRatio::Enum _ratio, TextureFormat::Enum _format, uint64_t _textureFlags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP)
.. doxygenfunction:: bgfx::createFrameBuffer(uint8_t _num, const TextureHandle *_handles, bool _destroyTextures = false)
.. doxygenfunction:: bgfx::createFrameBuffer(void *_nwh, uint16_t _width, uint16_t _height, TextureFormat::Enum _format = TextureFormat::Count, TextureFormat::Enum _depthFormat = TextureFormat::Count)

.. doxygenstruct:: bgfx::Attachment
    :members:

.. doxygenfunction:: bgfx::createFrameBuffer(uint8_t _num, const Attachment *_attachment, bool _destroyTextures = false)
.. doxygenfunction:: bgfx::getTexture
.. doxygenfunction:: bgfx::setName(FrameBufferHandle _handle, const char *_name, int32_t _len = INT32_MAX)
.. doxygenfunction:: bgfx::destroy(FrameBufferHandle _handle)

Instance Buffer
~~~~~~~~~~~~~~~

.. doxygenfunction:: bgfx::getAvailInstanceDataBuffer
.. doxygenfunction:: bgfx::allocInstanceDataBuffer

Indirect Buffer
~~~~~~~~~~~~~~~

.. doxygenfunction:: bgfx::createIndirectBuffer
.. doxygenfunction:: bgfx::destroy(IndirectBufferHandle _handle)

Occlusion Query
~~~~~~~~~~~~~~~

.. doxygenfunction:: bgfx::createOcclusionQuery

.. doxygenstruct:: bgfx::OcclusionQueryResult
    :members:

.. doxygenfunction:: bgfx::getResult
.. doxygenfunction:: bgfx::destroy(OcclusionQueryHandle _handle)
