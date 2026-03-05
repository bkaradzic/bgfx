Internals
=========

Sort-based draw call bucketing
-------------------------------

bgfx uses sort-based draw call bucketing. This means that the order in which draw calls are submitted does not necessarily match the order in which they are rendered. Instead, draw calls are assigned a 64-bit **sort key** and sorted before execution on the render thread, enabling more optimal GPU state management and batching.

On the high level bgfx uses a **declarative API**: the user declares views, their render targets, clear parameters, and transforms up front, then submits draw calls in any order. Internally, the sort key ensures that draw calls are grouped by view first, then ordered within each view according to the active **view mode** (see ``bgfx::setViewMode``):

- **Default** - Sort by program first, then by depth. This groups draw calls with the same shader program together to minimise state changes, using depth as a secondary key.
- **Sequential** - Preserve submission order. Draw calls are rendered in exactly the order ``submit`` was called. Useful for UI/GUI rendering where painter's-order matters.
- **DepthAscending** - Sort by depth (front-to-back). Helps maximise early-Z rejection for opaque geometry.
- **DepthDescending** - Sort by depth (back-to-front). Required for correct blending of transparent geometry.

Sort key layout
~~~~~~~~~~~~~~~

Each draw call is encoded into a 64-bit sort key. The highest bits encode the **view ID**, so draw calls are always grouped by view first. Below the view bits, a **draw bit** distinguishes draw calls from compute dispatches. For draw calls, a **draw type** field selects one of three encodings to implement the view modes above:

- **Program sort** (Default mode): ``[view | draw | type=0 | blend | alphaRef | program | depth]``
- **Depth sort** (DepthAscending/DepthDescending): ``[view | draw | type=1 | depth | blend | alphaRef | program]``
- **Sequence sort** (Sequential mode): ``[view | draw | type=2 | sequence | blend | alphaRef | program]``

Compute dispatches always use sequential ordering: ``[view | compute | sequence | program]``.

Sort keys are sorted via radix sort on the render thread just before GPU submission.

- More detailed description of sort-based draw call bucketing can be found at: `Order your graphics draw calls around! <http://realtimecollisiondetection.net/blog/?p=86>`__

API thread and render thread
-----------------------------

bgfx separates work into two threads: the **API thread** and the **render thread**.

API thread
~~~~~~~~~~

The API thread is the thread from which ``bgfx::init`` is called. Once ``bgfx::init`` has been called, bgfx internally assumes that all subsequent API calls will be made from this same thread, with the exception of the Resource API, View API, and Encoder API (see sections below).

The API thread is where application logic runs: setting up views, submitting draw calls via encoders, and calling ``bgfx::frame`` to advance to the next frame.

Render thread
~~~~~~~~~~~~~

The render thread is where ``bgfx::renderFrame`` executes. This is the thread that talks to the GPU: it processes the command buffer, sorts draw calls, submits them to the graphics API, and performs the back-buffer flip.

On most operating systems, certain graphics APIs require that rendering happens on the "main" thread (the thread on which the process was started, i.e. the thread that called ``main``). When using bgfx in multithreaded mode, the render thread is typically the main thread, while the API thread runs on a user-created secondary thread.

Double-buffered frame pipeline
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bgfx maintains two ``Frame`` objects internally: the **submit buffer** (written by the API thread) and the **render buffer** (read by the render thread). This double buffering allows the API thread and the render thread to run in parallel:

1. **API thread** builds a frame by recording draw calls, state changes, and resource commands into the submit buffer.
2. When the API thread calls ``bgfx::frame``, it waits for the render thread to finish the previous frame, then swaps the submit and render buffers (via ``bx::swap``) and signals the render thread to begin.
3. **Render thread** (in ``bgfx::renderFrame``) wakes up, executes pre-render commands (resource creation/updates), sorts draw calls by sort key via radix sort, submits them to the GPU, executes post-render commands, flips the back buffer, and then signals back to the API thread.
4. The API thread is now free to start building the next frame while the render thread is still executing GPU commands.

The synchronisation between the two threads uses a pair of semaphores:

- ``apiSemPost`` / ``apiSemWait`` - the API thread signals the render thread that a new frame is ready to process.
- ``renderSemPost`` / ``renderSemWait`` - the render thread signals the API thread that it has finished processing.

Multithreaded mode
~~~~~~~~~~~~~~~~~~

When bgfx is compiled with ``BGFX_CONFIG_MULTITHREADED=1`` (the default on all platforms that support threading), the user can call ``bgfx::renderFrame`` directly. Calling ``bgfx::renderFrame`` before ``bgfx::init`` from the intended render thread prevents bgfx from creating its own internal render thread - the user takes responsibility for calling ``bgfx::renderFrame`` externally each frame.

If both ``bgfx::renderFrame`` and ``bgfx::init`` are called from the same thread, bgfx detects this and switches to **single-threaded mode**: ``bgfx::frame`` will internally invoke ``bgfx::renderFrame`` automatically, and the user does not need to call it separately.

Single-threaded mode
~~~~~~~~~~~~~~~~~~~~

When compiled with ``BGFX_CONFIG_MULTITHREADED=0``, or when single-threaded mode is detected at runtime, there is no separate render thread. The call to ``bgfx::frame`` swaps buffers and immediately performs rendering inline (calls ``bgfx::renderFrame`` internally). The double-buffer swap still happens, but both sides execute on the same thread sequentially.

Resource API
------------

Any API call starting with ``bgfx::create*``, ``bgfx::destroy*``, ``bgfx::update*``, or ``bgfx::alloc*`` is considered part of the Resource API. Internally, Resource API calls are guarded by a mutex (``m_resourceApiLock``), so there is no limit on the number of threads that can call Resource API functions simultaneously.

Calling any Resource API function is generally infrequent and cheap on the API thread side, because the actual GPU work (uploading textures, creating buffers, etc.) is deferred: the commands are recorded into the frame's command buffer and executed later on the render thread via ``rendererExecCommands``.

Resource handles (``TextureHandle``, ``VertexBufferHandle``, etc.) are returned immediately on creation and can be used in draw calls right away, even though the GPU resource may not yet exist. The render thread will process the creation command before it processes any draw calls that reference the handle.

View API
--------

Any API call starting with ``bgfx::setView*`` is considered part of the View API. The View API is **not** internally thread safe - but it doesn't need to be, because views are independent from each other. Calling any view API for different views from different threads is safe. What is **not** safe is updating the same view from multiple threads simultaneously; doing so leads to undefined behaviour.

One important constraint: ``bgfx::setViewMode`` must be set **before** any draw calls are submitted to that view within a frame. The internal encoder reads the view mode at submit time to select the sort key encoding. Changing the view mode after draw calls have already been submitted to that view will cause incorrect sort behaviour.

The maximum number of views is configured by ``BGFX_CONFIG_MAX_VIEWS`` (default: 256, must be a power of 2). Views are referenced by ``ViewId`` (a 16-bit integer).

Encoder API
-----------

The Encoder API is used for submitting draw calls and dispatches from multiple threads. An encoder is obtained by calling ``bgfx::begin`` and returned with ``bgfx::end``.

By default, bgfx allows up to **8 simultaneous encoders** (configurable via ``Limits.maxEncoders`` in ``bgfx::Init``). Each encoder writes into its own ``UniformBuffer``, so there is no contention between threads when recording draw calls.

When ``bgfx::frame`` is called, it waits for all active encoders to finish (``encoderApiWait``), then locks the encoder mutex to prevent new encoders from being created. The submit buffer is then finalized and swapped.

Encoder 0 is special: it is the "default encoder" used by the legacy non-encoder API (``bgfx::setState``, ``bgfx::submit``, etc.) and is always allocated internally. The remaining encoder slots are available for user-created encoders for multithreaded submission.

Transient buffers
-----------------

Transient vertex and index buffers are per-frame temporary allocations intended for dynamic geometry that changes every frame (e.g. debug rendering, particles, UI). They are allocated from a ring buffer that is reset each frame.

Each of the two ``Frame`` objects owns its own transient vertex buffer and transient index buffer. When the frame buffers are swapped, the new submit buffer gets a fresh transient allocation. This means that pointers obtained from ``bgfx::allocTransientVertexBuffer`` / ``bgfx::allocTransientIndexBuffer`` are only valid until the next call to ``bgfx::frame``.

The maximum size of transient buffers can be configured via ``Limits.maxTransientVbSize`` and ``Limits.maxTransientIbSize`` in ``bgfx::Init``.

Customization
-------------

By default each platform has sane default values. For example on Windows the default renderer is Direct3D 12, on Linux it is Vulkan, and on macOS it's Metal. On Windows, almost all rendering backends are available. For OpenGL ES on desktop you can find more information at: `OpenGL ES 2.0 and EGL on desktop <http://www.g-truc.net/post-0457.html>`__

If you're targeting specific mobile hardware, you can find GLES support in their official SDKs: `Adreno SDK <http://developer.qualcomm.com/mobile-development/mobile-technologies/gaming-graphics-optimization-adreno/tools-and-resources>`__, `Mali SDK <http://www.malideveloper.com/>`__, `PowerVR SDK <http://www.imgtec.com/powervr/insider/sdkdownloads/>`__.

All configuration settings are located inside `src/config.h <https://github.com/bkaradzic/bgfx/blob/master/src/config.h>`__.

Every ``BGFX_CONFIG_*`` setting can be changed by passing defines through compiler switches. For example setting preprocessor define ``BGFX_CONFIG_RENDERER_OPENGL=1`` will change the backend renderer to OpenGL 2.1 on Windows. Since rendering APIs are platform specific, this obviously won't work nor make sense in all cases.

Options
~~~~~~~

Threading and synchronisation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``BGFX_CONFIG_MULTITHREADED`` - Enable/disable multithreaded rendering. When enabled, bgfx can use a separate render thread for GPU submission. Default is 1 on all platforms that support threading (0 on Emscripten).

``BGFX_CONFIG_API_SEMAPHORE_TIMEOUT`` - Timeout in milliseconds for the API/render thread semaphore wait. Default is 5000 ms. If the semaphore times out, it typically indicates a deadlock or the other thread has stalled.

``BGFX_CONFIG_DEFAULT_MAX_ENCODERS`` - Default maximum number of simultaneous encoders for multithreaded draw call submission. Default is 8 when multithreaded, 1 otherwise. Can be overridden at runtime via ``Limits.maxEncoders`` in ``bgfx::Init``.

``BGFX_CONFIG_ENCODER_API_ONLY`` - When set to 1, disable the legacy non-encoder API (``bgfx::setState``, ``bgfx::submit``, etc.) and require all submissions to go through the Encoder API (``bgfx::begin`` / ``bgfx::end``). Default is 0.

Renderer backends
^^^^^^^^^^^^^^^^^

``BGFX_CONFIG_RENDERER_AGC`` - Enable AGC renderer backend (PS5). Default is auto-detected per platform.

``BGFX_CONFIG_RENDERER_DIRECT3D11`` - Enable Direct3D 11 renderer backend. Default is 1 on Windows/Linux.

``BGFX_CONFIG_RENDERER_DIRECT3D12`` - Enable Direct3D 12 renderer backend. Default is 1 on Windows/Linux.

``BGFX_CONFIG_RENDERER_GNM`` - Enable GNM renderer backend (PS4). Default is auto-detected per platform.

``BGFX_CONFIG_RENDERER_METAL`` - Enable Metal renderer backend. Default is 1 on iOS/macOS/visionOS.

``BGFX_CONFIG_RENDERER_NVN`` - Enable NVN renderer backend (Nintendo Switch). Default is auto-detected per platform.

``BGFX_CONFIG_RENDERER_OPENGL`` - Enable OpenGL renderer backend. Set to the minimum GL version (e.g. 21 for OpenGL 2.1, 33 for 3.3, 44 for 4.4). Default is auto-detected per platform; minimum is 21 if enabled.

``BGFX_CONFIG_RENDERER_OPENGLES`` - Enable OpenGL ES renderer backend. Set to the minimum GLES version (e.g. 20 for ES 2.0, 30 for ES 3.0). Default is auto-detected per platform; minimum is 20 if enabled. Cannot be combined with ``BGFX_CONFIG_RENDERER_OPENGL``.

``BGFX_CONFIG_RENDERER_VULKAN`` - Enable Vulkan renderer backend. Default is 1 on Android/Linux/Windows/macOS/NX.

``BGFX_CONFIG_RENDERER_WEBGPU`` - Enable WebGPU renderer backend. Default is 1 on Linux/macOS/Windows.

``BGFX_CONFIG_RENDERER_USE_EXTENSIONS`` - Enable use of renderer-specific API extensions (e.g. OpenGL extensions, Vulkan extensions). Default is 1.

``BGFX_CONFIG_RENDERER_DIRECT3D11_USE_STAGING_BUFFER`` - Enable use of staging buffers in the Direct3D 11 renderer for texture and buffer updates. Default is 0.

``BGFX_CONFIG_RENDERER_VULKAN_MAX_DESCRIPTOR_SETS_PER_FRAME`` - Maximum number of Vulkan descriptor sets allocated per frame. Default is 1024. Each draw/compute call may consume one descriptor set.

Resource limits
^^^^^^^^^^^^^^^

``BGFX_CONFIG_MAX_DRAW_CALLS`` - Maximum number of draw/compute calls per frame. Default is 65535 (64K - 1).

``BGFX_CONFIG_MAX_BLIT_ITEMS`` - Maximum number of blit items per frame. Default is 1024.

``BGFX_CONFIG_MAX_VIEWS`` - Maximum number of views. Default is 256. Must be a power of 2.

``BGFX_CONFIG_MAX_VIEW_NAME`` - Maximum length of a view name string. Default is 256.

``BGFX_CONFIG_MAX_VERTEX_LAYOUTS`` - Maximum number of vertex layout declarations. Default is 64.

``BGFX_CONFIG_MAX_INDEX_BUFFERS`` - Maximum number of static index buffer handles. Default is 4096.

``BGFX_CONFIG_MAX_VERTEX_BUFFERS`` - Maximum number of static vertex buffer handles. Default is 4096.

``BGFX_CONFIG_MAX_VERTEX_STREAMS`` - Maximum number of vertex streams per draw call. Default is 4.

``BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS`` - Maximum number of dynamic index buffer handles. Default is 4096.

``BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS`` - Maximum number of dynamic vertex buffer handles. Default is 4096.

``BGFX_CONFIG_MAX_SHADERS`` - Maximum number of shader handles (vertex + fragment + compute). Default is 512.

``BGFX_CONFIG_MAX_TEXTURES`` - Maximum number of texture handles. Default is 4096.

``BGFX_CONFIG_MAX_TEXTURE_SAMPLERS`` - Maximum number of texture samplers per draw call. Default is 16.

``BGFX_CONFIG_MAX_FRAME_BUFFERS`` - Maximum number of frame buffer handles. Default is 128.

``BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS`` - Maximum number of attachments (color + depth/stencil) per frame buffer. Default is 8.

``BGFX_CONFIG_MAX_UNIFORMS`` - Maximum number of uniform handles. Default is 512.

``BGFX_CONFIG_MAX_OCCLUSION_QUERIES`` - Maximum number of occlusion query handles. Default is 256.

``BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT`` - Maximum number of instance data vec4 attributes per draw call. Default is 5. Total instance stride is count × 16 bytes.

``BGFX_CONFIG_MAX_COLOR_PALETTE`` - Maximum number of color palette entries for indexed clear colors. Default is 16.

``BGFX_CONFIG_MAX_SCREENSHOTS`` - Maximum number of screenshot requests that can be queued per frame. Default is 4.

``BGFX_CONFIG_MAX_PROGRAMS`` - Maximum number of linked programs. Derived from ``2^BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM``. Default is 512. Cannot be configured directly.

Buffer sizes
^^^^^^^^^^^^^

``BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE`` - Initial size in bytes of the dynamic index buffer backing store. Default is 1 MB. The backing store grows as needed via sub-allocation.

``BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE`` - Initial size in bytes of the dynamic vertex buffer backing store. Default is 3 MB. The backing store grows as needed via sub-allocation.

``BGFX_CONFIG_MAX_TRANSIENT_VERTEX_BUFFER_SIZE`` - Maximum transient vertex buffer size. There is no growth; all transient vertices must fit into this buffer. Default is 6 MB.

``BGFX_CONFIG_MAX_TRANSIENT_INDEX_BUFFER_SIZE`` - Maximum transient index buffer size. There is no growth; all transient indices must fit into this buffer. Default is 2 MB.

``BGFX_CONFIG_MIN_RESOURCE_COMMAND_BUFFER_SIZE`` - Minimum initial size of the resource command buffer (pre/post render commands for resource creation and updates). Default is 64 KB. The buffer grows as needed.

``BGFX_CONFIG_MIN_UNIFORM_BUFFER_SIZE`` - Minimum initial size in bytes of the per-encoder uniform buffer. Default is 1 MB. This buffer will resize on demand.

``BGFX_CONFIG_UNIFORM_BUFFER_RESIZE_THRESHOLD_SIZE`` - Maximum amount of unused uniform buffer space (in bytes) before the buffer is shrunk. Default is 64 KB.

``BGFX_CONFIG_UNIFORM_BUFFER_RESIZE_INCREMENT_SIZE`` - Increment size for uniform buffer resize. Default is 1 MB.

``BGFX_CONFIG_CACHED_DEVICE_MEMORY_ALLOCATIONS_SIZE`` - Amount of allowed memory allocations left on device to use for recycling during later allocations. This can be beneficial in case the driver is slow allocating memory on the device. Default is 128 MB. Currently only used by the Vulkan backend.

``BGFX_CONFIG_MAX_STAGING_SCRATCH_BUFFER_SIZE`` - Threshold of data size above which the staging scratch buffer will not be used; instead a separate device memory allocation will take place to stage the data. Default is 16 MB.

``BGFX_CONFIG_MAX_SCRATCH_STAGING_BUFFER_PER_FRAME_SIZE`` - Amount of scratch buffer size (per in-flight frame) reserved for staging data for copying to the device (vertex buffers, textures, etc.). Default is 32 MB. Currently only used by the Vulkan backend.

Sort key
^^^^^^^^

``BGFX_CONFIG_SORT_KEY_NUM_BITS_DEPTH`` - Number of bits used for depth in the sort key. Default is 32. Reducing this allows more bits for other sort key fields.

``BGFX_CONFIG_SORT_KEY_NUM_BITS_SEQ`` - Number of bits used for sequence number in the sort key. Default is 20. Determines the maximum number of draw calls per view in sequential mode (2^20 ≈ 1M).

``BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM`` - Number of bits used for program index in the sort key. Default is 9. Determines ``BGFX_CONFIG_MAX_PROGRAMS`` (2^9 = 512).

``BGFX_CONFIG_MAX_MATRIX_CACHE`` - Maximum number of cached transform matrices per frame. Default is ``BGFX_CONFIG_MAX_DRAW_CALLS + 1``.

``BGFX_CONFIG_MAX_RECT_CACHE`` - Maximum number of cached scissor rectangles per frame. Default is 4096.

Swap chain
^^^^^^^^^^

``BGFX_CONFIG_MAX_BACK_BUFFERS`` - Maximum number of back buffers for the swap chain. Default is 4. The actual number used is specified via ``bgfx::Resolution::numBackBuffers``.

``BGFX_CONFIG_MAX_FRAME_LATENCY`` - Maximum frame latency (number of frames that can be queued ahead). Default is 3. The actual value is specified via ``bgfx::Resolution::maxFrameLatency``.

Debugging and profiling
^^^^^^^^^^^^^^^^^^^^^^^

``BGFX_CONFIG_DEBUG_TEXT_MAX_SCALE`` - Debug text maximum scale factor for ``bgfx::dbgTextPrintf``. Default is 4.

``BGFX_CONFIG_DEBUG_PERFHUD`` - Enable nVidia PerfHUD integration. Default is 0.

``BGFX_CONFIG_DEBUG_ANNOTATION`` - Enable annotation for graphics debuggers (e.g. RenderDoc, PIX). Default matches ``BGFX_CONFIG_DEBUG``.

``BGFX_CONFIG_DEBUG_OBJECT_NAME`` - Enable debug names on graphics API objects (Direct3D 11/12, Vulkan, etc.). Default matches ``BGFX_CONFIG_DEBUG_ANNOTATION``.

``BGFX_CONFIG_DEBUG_UNIFORM`` - Enable runtime validation that uniforms are set before each draw call. Default matches ``BGFX_CONFIG_DEBUG``.

``BGFX_CONFIG_DEBUG_OCCLUSION`` - Enable runtime validation that occlusion queries are not reused within the same frame. Default matches ``BGFX_CONFIG_DEBUG``.

``BGFX_CONFIG_PROFILER`` - Enable internal profiler instrumentation. When enabled, bgfx will emit profiler scopes for frame, submit, resource, and view operations. Default is 0.

``BGFX_CONFIG_RENDERDOC_LOG_FILEPATH`` - File path for RenderDoc capture log output. Default is ``"temp/bgfx"``.

``BGFX_CONFIG_RENDERDOC_CAPTURE_KEYS`` - Key(s) to trigger a RenderDoc capture. Default is ``{ eRENDERDOC_Key_F11 }``.

Miscellaneous
^^^^^^^^^^^^^

``BGFX_CONFIG_USE_TINYSTL`` - Enable use of tinystl instead of std containers for internal data structures. Default is 1. Reduces binary size and avoids std library dependency.

``BGFX_CONFIG_MIP_LOD_BIAS`` - Global MIP level-of-detail bias applied to all texture sampling. Default is 0. Positive values select coarser MIP levels, negative values select finer MIP levels.

``BGFX_CONFIG_DRAW_INDIRECT_STRIDE`` - Stride in bytes of each draw indirect command. Fixed at 32 bytes. Not configurable.

``BGFX_CONFIG_PREFER_DISCRETE_GPU`` - On laptops with integrated and discrete GPU, prefer selection of the discrete GPU (nVidia and AMD). Default is 1 on Windows, 0 elsewhere.
