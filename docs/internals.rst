Internals
=========

Sort based draw call bucketing
------------------------------

bgfx is using sort-based draw call bucketing. This means that submission order doesn't necessarily match the rendering order, but on the low-level they will be sorted and ordered correctly. On the high level bgfx uses **declarative API** and internal sorting allows more optimal way of submitting draw calls for all passes at one place, and on the low-level this allows better optimization of rendering order. This sometimes creates undesired results usually for GUI rendering, where draw order should usually match submit order. bgfx provides way to enable sequential rendering for these cases (see ``bgfx::setViewMode``).

 - More detailed description of sort-based draw call bucketing can be found at: `Order your graphics draw calls around! <http://realtimecollisiondetection.net/blog/?p=86>`__

API and render thread
---------------------

API thread is thread from which ``bgfx::init`` is called. Once ``bgfx::init`` is called on thread, internally bgfx assumes that all API calls will be called from the same thread with exception of Resource, View, and Encoder API.

Render thread from where internal rendering ``bgfx::renderFrame`` is called. On most of OS' it's required that this call be called on thread that OS created when executing process (some refer to this thread as "main" thread, or thread where ``main`` function is called).

When bgfx is compiled with option ``BGFX_CONFIG_MULTITHREADED=1`` (default is on) ``bgfx::renderFrame`` can be called by user. It's required to be called before ``bgfx::init`` from thread that will be used as render thread. If both ``bgfx::renderFrame`` and ``bgfx::init`` are called from the same thread, bgfx will switch to execute in single threaded mode, and calling ``bgfx::renderFrame`` is not required, since it will be called automatically during ``bgfx::frame`` call.

Resource API
------------

Any API call starting with ``bgfx::create*``, ``bgfx::destroy*``, ``bgfx::update*``, ``bgfx::alloc*`` is considered part of resource API. Internally resource API calls are guarded by mutex. There is no limit of number of threads that can call resource API simultaneously. Calling any resource API is infrequent, and functions are cheap since most of work with resource is done at later point on render thread.

View API
--------

Any API call starting with ``bgfx::setView*`` is considered part of view API. View API is not designed to be thread safe at all since all views are independentent from each other. Calling any view API for different views from different threads is safe. What's not safe is to update the same view from multiple threads. This will lead to undefined behavior. Only view API that has to be set before any draw calls are issued is view mode ``bgfx::setViewMode``. Internal encoder requires view mode to select sort key encoding and if user changes view mode after submit it will cause incorrect sort behavior within the view.

Encoder API
-----------

Encoder API can be obtained by calling ``bgfx::begin``. bgfx by default allows 8 simultaneous threads to use encoders. This can be configured by changing ``Limits.maxEncoders`` init option of ``bgfx::Init`` structure.

Customization
-------------

By default each platform has sane default values. For example on Windows default renderer is DirectX, on Linux it is OpenGL, and on OSX it's Metal. On Windows platform almost all rendering backends are available. For OpenGL ES on desktop you can find more information at:- `OpenGL ES 2.0 and EGL on desktop <http://www.g-truc.net/post-0457.html>`__

If you're targeting specific mobile hardware, you can find GLES support in their official SDKs: `Adreno
SDK <http://developer.qualcomm.com/mobile-development/mobile-technologies/gaming-graphics-optimization-adreno/tools-and-resources>`__, `Mali SDK <http://www.malideveloper.com/>`__, `PowerVR SDK <http://www.imgtec.com/powervr/insider/sdkdownloads/>`__.

All configuration settings are located inside `src/config.h <https://github.com/bkaradzic/bgfx/blob/master/src/config.h>`__.

Every ``BGFX_CONFIG_*`` setting can be changed by passing defines thru compiler switches. For example setting preprocessor define ``BGFX_CONFIG_RENDERER_OPENGL=1`` will change backend renderer to OpenGL 2.1. on Windows. Since rendering APIs are platform specific, this obviously won't work nor make sense in all cases.

Options
~~~~~~~

``BGFX_CONFIG_MULTITHREADED`` is used to enable/disable threading support inside bgfx. By default set to 1 on all platforms that support threading.
