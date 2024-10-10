Overview
========

What is it?
-----------

Cross-platform, graphics API agnostic, "Bring Your Own Engine/Framework" style rendering library,
licensed under permissive BSD-2 clause open source license.

.. raw:: html

    <p>
    <iframe src="https://ghbtns.com/github-btn.html?user=bkaradzic&repo=bgfx&type=star&count=true&size=large" frameborder="0" scrolling="0" width="160px" height="30px"></iframe>
    <iframe src="https://ghbtns.com/github-btn.html?user=bkaradzic&repo=bgfx&type=fork&count=true&size=large" frameborder="0" scrolling="0" width="158px" height="30px"></iframe>
    </p>

Supported rendering backends
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-  Direct3D 11
-  Direct3D 12
-  GNM (only for licensed PS4 developers, search DevNet forums for source)
-  Metal
-  OpenGL 2.1
-  OpenGL 3.1+
-  OpenGL ES 2
-  OpenGL ES 3.1
-  Vulkan
-  WebGL 1.0
-  WebGL 2.0

Supported Platforms
~~~~~~~~~~~~~~~~~~~

-  Android (14+)
-  iOS/iPadOS/tvOS (16.0+)
-  Linux (both X11 and Wayland)
-  macOS (13.0+)
-  PlayStation 4
-  RaspberryPi
-  UWP (Universal Windows, Xbox One)
-  Wasm/Emscripten
-  Windows (7+)

Supported Compilers
~~~~~~~~~~~~~~~~~~~

-  Clang 11 and above
-  GCC 8 and above
-  VS2019 and above
-  Apple clang 12 and above

Supported Languages
~~~~~~~~~~~~~~~~~~~

-  `C/C++ API documentation <https://bkaradzic.github.io/bgfx/bgfx.html>`__
-  `Beef API bindings <https://github.com/bkaradzic/bgfx/tree/master/bindings/bf>`__
-  `C# language API bindings #1 <https://github.com/bkaradzic/bgfx/tree/master/bindings/cs>`__
-  `D language API bindings <https://github.com/BindBC/bindbc-bgfx>`__
-  `Go language API bindings <https://github.com/james4k/go-bgfx>`__
-  `Haskell language API bindings <https://github.com/haskell-game/bgfx>`__
-  `Lightweight Java Game Library 3 bindings <https://github.com/LWJGL/lwjgl3#lwjgl---lightweight-java-game-library-3>`__
-  `Lua language API bindings <https://github.com/cloudwu/lua-bgfx>`__
-  `Nim language API bindings <https://github.com/Halsys/nim-bgfx>`__
-  `Pascal language API bindings <https://github.com/Akira13641/PasBGFX>`__
-  `Python language API bindings #1 <https://github.com/fbertola/bgfx-python#-----bgfx-python-->`__
-  `Python language API bindings #2 <https://github.com/jnadro/pybgfx#pybgfx>`__
-  `Rust language API bindings <https://github.com/rhoot/bgfx-rs#bgfx-rs>`__
-  `Swift language API bindings <https://github.com/stuartcarnie/SwiftBGFX>`__
-  `Zig language API bindings <https://github.com/bkaradzic/bgfx/tree/master/bindings/zig>`__


Project Page
~~~~~~~~~~~~

- https://github.com/bkaradzic/bgfx

Contact
~~~~~~~

 - `GitHub Discussions <https://github.com/bkaradzic/bgfx/discussions>`__
 - `Discord Chat <https://discord.gg/9eMbv7J>`__
 - GitHub `@bkaradzic <https://github.com/bkaradzic>`__
 - Twitter `@bkaradzic <https://twitter.com/bkaradzic>`__

Debugging and Profiling
-----------------------

RenderDoc
~~~~~~~~~

Loading of RenderDoc is integrated in bgfx when using DX11 or OpenGL
renderer. You can drop in ``renderdoc.dll`` from RenderDoc distribution
into working directory, and it will be automatically loaded during bgfx
initialization. This allows frame capture at any time by pressing
**F11**.

Download: `RenderDoc <https://renderdoc.org/builds>`__

RenderDoc `How do I ...? <https://renderdoc.org/docs/how/index.html>`__ documentation.

`Shader debugging <https://software.intel.com/en-us/articles/shader-debugging-for-bgfx-rendering-engine>`__
with RenderDoc and MSVC.

SDL, GLFW, etc.
---------------

It is possible to use bgfx with SDL, GLFW and similar cross platform
windowing libraries. The main requirement is that windowing library
provides access to native window handle that's used to create Direct3D
device or OpenGL context.

For more info see: :doc:`bgfx`.

.. note:: You can use ``--with-sdl`` when running GENie to enable SDL2 integration with examples:
          ``genie --with-sdl vs2012``

.. note:: ``--with-glfw`` is also available, but it's just simple stub to be used to test GLFW
          integration API.

.. note:: Special care is necessary to make custom windowing to work with multithreaded renderer.
          Each platform has rules about where renderer can be and how multithreading interacts
          with context/device. To disable multithreaded render use ``BGFX_CONFIG_MULTITHREADED=0``
          preprocessor define.

Getting Involved
----------------

Everyone is welcome to contribute to bgfx by submitting bug reports, testing on different
platforms, writing examples (see `ideas <https://github.com/bkaradzic/bgfx/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+needed%22>`__),
improving documentation, profiling and optimizing, etc.

.. note:: **When contributing to the bgfx project you must agree to the BSD 2-clause
          licensing terms.**

Contributors
~~~~~~~~~~~~

Chronological order:

 - Branimir Karadžić (`@bkaradzic <https://github.com/bkaradzic>`__)
 - Garett Bass (`@garettbass <https://github.com/garettbass>`__) - macOS port.
 - Jeremie Roy (`@jeremieroy <https://github.com/jeremieroy>`__) -
   `10-font <examples.html#font>`__,
   and `11-fontsdf <examples.html#fontsdf>`__ examples.
 - Miloš Tošić (`@milostosic <https://github.com/milostosic>`__) -
   `12-lod <examples.html#lod>`__ example.
 - Dario Manesku (`@dariomanesku <https://github.com/dariomanesku>`__) -
   `13-stencil <examples.html#stencil>`__,
   `14-shadowvolumes <examples.html#shadowvolumes>`__,
   `15-shadowmaps-simple <examples.html#shadowmaps-simple>`__,
   `16-shadowmaps <examples.html#shadowmaps>`__,
   `18-ibl <examples.html#ibl>`__,
   and `28-wireframe <examples.html#wireframe>`__ example.
 - James Gray (`@james4k <https://github.com/james4k>`__) - Go language API bindings.
 - Guillaume Piolat (`@p0nce <https://github.com/p0nce>`__) - D language API bindings.
 - Mike Popoloski (`@MikePopoloski <https://github.com/MikePopoloski>`__) - C#/VB/F# language API
   bindings, WinRT/WinPhone support.
 - Kai Jourdan (`@questor <https://github.com/questor>`__) -
   `23-vectordisplay <examples.html#vectordisplay>`__ example.
 - Stanlo Slasinski (`@stanlo <https://github.com/stanlo>`__) -
   `24-nbody <examples.html#nbody>`__ example.
 - Daniel Collin (`@emoon <https://github.com/emoon>`__) - Port of Ocornut's ImGui to bgfx.
 - Andre Weissflog (`@floooh <https://github.com/floooh>`__) - Alternative build system fips.
 - Andrew Johnson (`@ajohnson23 <https://github.com/ajohnson23>`__) - TeamCity build.
 - Tony McCrary (`@enleeten <https://github.com/enleeten>`__) - Java language API bindings.
 - Attila Kocsis (`@attilaz <https://github.com/attilaz>`__) - Metal rendering backend, various macOS
   and iOS improvements and bug fixes, `39-assao <examples.html#assao>`__ example.
 - Richard Gale (`@RichardGale <https://github.com/RichardGale>`__) - Emscripten entry input
   handling.
 - Andrew Mac (`@andr3wmac <https://github.com/andr3wmac>`__) -
   `27-terrain <examples.html#terrain>`__ example.
 - Oliver Charles (`@ocharles <https://github.com/ocharles>`__) - Haskel language API bindings.
 - Johan Sköld (`@rhoot <https://github.com/rhoot>`__) - Rust language API bindings.
 - Jean-François Verdon (`@Nodrev <https://github.com/Nodrev>`__) - Alternative deployment for
   Android.
 - Jason Nadro (`@jnadro <https://github.com/jnadro>`__) - Python language API bindings.
 - Krzysztof Kondrak (`@kondrak <https://github.com/kondrak>`__) - OculusVR integration.
 - Colby Klein (`@excessive <https://github.com/excessive>`__) - Lua language API bindings.
 - Stuart Carnie (`@stuartcarnie <https://github.com/stuartcarnie>`__) - Swift language API
   bindings.
 - Joseph Cherlin (`@jcherlin <https://github.com/jcherlin>`__) -
   `30-picking <examples.html#picking>`__,
   and `31-rsm <examples.html#rsm>`__ example.
 - Olli Wang (`@olliwang <https://github.com/olliwang>`__) - Various NanoVG integration improvements.
 - Cory Golden (`@Halsys <https://github.com/Halsys>`__) - Nim language API bindings.
 - Camilla Berglund (`@elmindreda <https://github.com/elmindreda>`__) - GLFW support.
 - Daniel Ludwig (`@code-disaster <https://github.com/code-disaster>`__) - Lightweight Java Game
   Library 3 bindings.
 - Benoit Jacquier (`@benoitjacquier <https://github.com/benoitjacquier>`__) - Added support for
   cubemap as texture 2D array in a compute shader.
 - Apoorva Joshi (`@ApoorvaJ <https://github.com/ApoorvaJ>`__) -
   `33-pom <examples.html#pom>`__ example.
 - Stanislav Pidhorsky (`@podgorskiy <https://github.com/podgorskiy>`__) -
   `36-sky <examples.html#sky>`__ example.
 - 云风 (`@cloudwu <https://github.com/cloudwu>`__) - Alternative Lua bindings, bgfx IDL scripts,
   `42-bunnylod <examples.html#bunnylod>`__ example.
 - Kostas Anagnostou (`@KostasAAA <https://github.com/KostasAAA>`__) -
   `37-gpudrivenrendering <examples.html#gpudrivenrendering>`__ example.
 - Andrew Willmott (`@andrewwillmott <https://github.com/andrewwillmott>`__) - ATC and ASTC support.
 - Aleš Mlakar (`@jazzbre <https://github.com/jazzbre>`__) -
   `40-svt <examples.html#svt>`__ example.
 - Matt Chiasson (`@mchiasson <https://github.com/mchiasson>`__) - Various fixes and improvements.
 - Phil Peron (`@pperon <https://github.com/pperon>`__) - Tutorial how to use bgfx API.
 - Vincent Cruz (`@BlockoS <https://github.com/BlockoS>`__) - Wayland support.
 - Jonathan Young (`@jpcy <https://github.com/jpcy>`__) - Renderer for ioquake3 that uses bgfx,
   minimal bgfx example.
 - Nick Waanders (`@NickWaanders <https://github.com/NickWaanders>`__) - shaderc: Metal fixes.
 - Vladimir Vukićević (`@vvuk <https://github.com/vvuk>`__) - HTML5 context.
 - Daniel Gavin (`@DanielGavin <https://github.com/DanielGavin>`__) - `41-tess <examples.html#tess>`__ example.
 - Ji-yong Kwon (`@rinthel <https://github.com/rinthel>`__) - Vulkan rendering backend.
 - Leandro Freire (`@leandrolfre <https://github.com/leandrolfre>`__).
 - Ari Vuollet (`@GoaLitiuM <https://github.com/GoaLitiuM>`__) IDL generator for D language
   bindings.
 - Sebastian Marketsmueller (`@sebastianmunity3d <https://github.com/sebastianmunity3d>`__).
 - Cedric Guillemet (`@CedricGuillemet <https://github.com/CedricGuillemet>`__).
 - Pablo Escobar (`@pezcode <https://github.com/pezcode>`__) - Various Vulkan fixes.
 - Paul Gruenbacher (`@pgruenbacher <https://github.com/pgruenbacher>`__) - Various bug fixes.
 - Jukka Jylänki (`@juj <https://github.com/juj>`__) - Various WebGL optimizations and fixes.
 - Hugo Amnov (`@hugoam <https://github.com/hugoam>`__) - WebGPU/Dawn rendering backend.
 - Christophe Dehais (`@goodartistscopy <https://github.com/goodartistscopy>`__) - Various bug fixes.
 - elvencache (`@elvencache <https://github.com/elvencache>`__) -
   `43-denoise <examples.html#denoise>`__,
   `44-sss <examples.html#sss>`__,
   and `45-bokeh <examples.html#bokeh>`__ example.
 - Richard Schubert (`@Hemofektik <https://github.com/Hemofektik>`__) - `46-fsr <examples.html#fsr>`__ example.
 - Sandy Carter (`@bwrsandman <https://github.com/bwrsandman>`__) - `47-pixelformats
   <examples.html#pixelformats>`__ example, and various fixes and improvements.
 - Liam Twigger (`@SnapperTT <https://github.com/SnapperTT>`__) - `48-drawindirect <examples.html#drawindirect>`__ example.
 - Preetish Kakkar (`@blackhole <https://github.com/preetishkakkar>`__) - `49-hextile <examples.html#49-hextile>`__ example.
 - Biswapriyo Nath (`@Biswa96 <https://github.com/Biswa96>`__) - GitHub Actions CI.
 - Raziel Alphadios (`@RazielXYZ <https://github.com/RazielXYZ>`__) - Various fixes and improvements.
 - IchorDev (`@IchorDev <https://github.com/ichordev>`__) - Improved D language bindings.

and `others <https://github.com/bkaradzic/bgfx/graphs/contributors>`__...

Repository visualization
~~~~~~~~~~~~~~~~~~~~~~~~

.. image:: https://api.star-history.com/svg?repos=bkaradzic/bgfx&type=Date

.. raw:: html

    <p>
    <iframe width="694" height="390" src="https://www.youtube.com/embed/5ZeN_d_-BHo" frameborder="0" allowfullscreen></iframe>
    </p>
