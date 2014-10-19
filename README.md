[bgfx](https://github.com/bkaradzic/bgfx) - Cross-platform rendering library
============================================================================

What is it?
-----------

Cross-platform rendering library.

Supported rendering backends:

 * Direct3D 9
 * Direct3D 11
 * OpenGL 2.1
 * OpenGL 3.1+
 * OpenGL ES 2
 * OpenGL ES 3.1

Supported platforms:

 * Android (14+)
 * asm.js/Emscripten (1.25.0)
 * iOS
 * Linux
 * Native Client (37)
 * OSX (10.9)
 * RaspberryPi
 * Windows (XP, Vista, 7, 8, 10)

Supported compilers:

 * Clang 3.3 and above
 * GCC 4.6 and above
 * vs2008 and above

Languages:

 * [C99 API documentation](https://github.com/bkaradzic/bgfx/blob/master/include/bgfx.c99.h)
 * [C++ API documentation](https://github.com/bkaradzic/bgfx/blob/master/include/bgfx.h)
 * [C#/VB/F# language API bindings](https://github.com/MikePopoloski/SharpBgfx)
 * [D language API bindings](https://github.com/p0nce/DerelictBgfx)
 * [Go language API bindings](https://github.com/james4k/go-bgfx)

Who is using it?
----------------

http://airmech.com/ AirMech is a free-to-play futuristic action real-time
strategy video game developed and published by Carbon Games.

http://theengine.co/ Loom Game Engine developed by The Engine Company. Loom
is a powerful 2D game engine with live reloading of code and assets, a friendly
scripting language, and an efficient command-line workflow. Here is video where
they explain why they choose bgfx over alternatives:  
<a href="https://www.youtube.com/watch?feature=player_embedded&v=PHY_XHkMGIM&t=1m53s" target="_blank"><img src="https://img.youtube.com/vi/PHY_XHkMGIM/0.jpg" alt="Why did you choose bgfx?" width="240" height="180" border="10" /></a>

https://github.com/dariomanesku/cmftStudio cmftStudio - cubemap filtering tool.  
![cmftStudio](https://github.com/dariomanesku/cmftStudio/raw/master/screenshots/cmftStudio_small.jpg)

https://github.com/taylor001/crown Crown is a general purpose data-driven game
engine, written from scratch with a minimalistic and data-oriented design
philosophy in mind.

https://d-gamedev-team.github.io/gfm/ - GFM is a feature-rich library to ease
the creation of video games / multimedia applications with the D programming
language.

https://github.com/emoon/ProDBG - ProDBG is a new debugger under development
that will support a variety of targets and operating systems. Currently it's in
very early development and primary focusing on Mac as primary target. This is
how it currently looks.  
![mac_screenshot](https://raw.githubusercontent.com/emoon/ProDBG/master/data/screens/mac_screenshot.png)

Examples
--------

Most of the examples require shader/texture/mesh data to be loaded. When running
examples your current directory should be examples/runtime.

	<bgfx_path>/examples/runtime $ ../../.build/<config>/bin/example-00-helloworldDebug

### [00-helloworld](https://github.com/bkaradzic/bgfx/blob/master/examples/00-helloworld)

Initialization and debug text.

### [01-cubes](https://github.com/bkaradzic/bgfx/blob/master/examples/01-cubes/cubes.cpp)

Rendering simple static mesh.

![example-01-cubes](https://github.com/bkaradzic/bgfx/raw/master/examples/01-cubes/screenshot.png)

### [02-metaballs](https://github.com/bkaradzic/bgfx/blob/master/examples/02-metaballs)

Rendering with transient buffers and embedding shaders.

![example-02-metaballs](https://github.com/bkaradzic/bgfx/raw/master/examples/02-metaballs/screenshot.png)

### [03-raymarch](https://github.com/bkaradzic/bgfx/blob/master/examples/03-raymarch)

Updating shader uniforms.

![example-03-raymarch](https://github.com/bkaradzic/bgfx/raw/master/examples/03-raymarch/screenshot.png)

### [04-mesh](https://github.com/bkaradzic/bgfx/blob/master/examples/04-mesh)

Loading meshes.

![example-04-mesh](https://github.com/bkaradzic/bgfx/raw/master/examples/04-mesh/screenshot.png)

### [05-instancing](https://github.com/bkaradzic/bgfx/blob/master/examples/05-instancing)

Geometry instancing.

![example-05-instancing](https://github.com/bkaradzic/bgfx/raw/master/examples/05-instancing/screenshot.png)

### [06-bump](https://github.com/bkaradzic/bgfx/blob/master/examples/06-bump)

Loading textures.

![example-06-bump](https://github.com/bkaradzic/bgfx/raw/master/examples/06-bump/screenshot.png)

### [07-callback](https://github.com/bkaradzic/bgfx/blob/master/examples/07-callback)

Implementing application specific callbacks for taking screen shots, caching
OpenGL binary shaders, and video capture.

### [08-update](https://github.com/bkaradzic/bgfx/blob/master/examples/08-update)

Updating textures.

### [09-hdr](https://github.com/bkaradzic/bgfx/tree/master/examples/09-hdr)
Using multiple views and render targets.

![example-09-hdr](https://github.com/bkaradzic/bgfx/raw/master/examples/09-hdr/screenshot.png)

### [10-font](https://github.com/bkaradzic/bgfx/tree/master/examples/10-font)

Use the font system to display text and styled text.

![example-10-font](https://github.com/bkaradzic/bgfx/raw/master/examples/10-font/screenshot.png)

### [11-fontsdf](https://github.com/bkaradzic/bgfx/tree/master/examples/11-fontsdf)

Use a single distance field font to render text of various size.

![example-11-fontsdf](https://github.com/bkaradzic/bgfx/raw/master/examples/11-fontsdf/screenshot.png)

### [12-lod](https://github.com/bkaradzic/bgfx/tree/master/examples/12-lod)

Mesh LOD transitions.

![example-12-lod](https://github.com/bkaradzic/bgfx/raw/master/examples/12-lod/screenshot.png)

### [13-stencil](https://github.com/bkaradzic/bgfx/tree/master/examples/13-stencil)

Stencil reflections and shadows.

![example-13-stencil](https://github.com/bkaradzic/bgfx/raw/master/examples/13-stencil/screenshot.png)

### [14-shadowvolumes](https://github.com/bkaradzic/bgfx/tree/master/examples/14-shadowvolumes)

Shadow volumes.

![example-14-shadowvolumes](https://github.com/bkaradzic/bgfx/raw/master/examples/14-shadowvolumes/screenshot.png)

### [15-shadowmaps-simple](https://github.com/bkaradzic/bgfx/tree/master/examples/15-shadowmaps-simple)

![example-15-shadowmaps-simple](https://github.com/bkaradzic/bgfx/raw/master/examples/15-shadowmaps-simple/screenshot.png)

### [16-shadowmaps](https://github.com/bkaradzic/bgfx/tree/master/examples/16-shadowmaps)

![example-16-shadowmaps](https://github.com/bkaradzic/bgfx/raw/master/examples/16-shadowmaps/screenshot.png)

### [17-drawstress](https://github.com/bkaradzic/bgfx/blob/master/examples/17-drawstress)

#### 60Hz

Draw stress is CPU stress test to show what is the maximimum number of draw
calls while maintaining 60Hz frame rate. bgfx currently has limit of maximum 64K
draw calls per frame.

| CPU          | Renderer     | GPU       |Compiler| Arch | OS         | Dim | Calls |
|:-------------|:-------------|:----------|:------:|:----:|:----------:|----:|------:|
| i5-3570 3.8  | NV 331.49    | GTX560Ti  | GCC    | x64  | Linux      |  40 | 64000+|
| i7-920 2.66  | GL2.1        | GTX650Ti  | VS2008 | x64  | Windows7   |  38 | 54872 |
| i7-920 2.66  | GL2.1        | GTX650Ti  | VS2008 | x86  | Windows7   |  38 | 54872 |
| i7-920 2.66  | DX9          | GTX650Ti  | GCC    | x64  | Windows7   |  32 | 32768 |
| i7-920 2.66  | DX9          | GTX650Ti  | VS2008 | x64  | Windows7   |  32 | 32768 |
| i7-920 2.66  | DX9          | GTX650Ti  | GCC    | x86  | Windows7   |  30 | 27000 |
| i7-920 2.66  | DX9          | GTX650Ti  | VS2008 | x86  | Windows7   |  30 | 27000 |
| i5-4250U 1.3 | GL2.1        | HD5000    | Clang  | x64  | OSX 10.9   |  28 | 21852 |
| Q8200 2.33   | NV 319.32    | GTX260    | GCC    | x64  | Linux      |  27 | 19683 |
| i7-2600K 3.4 | DX9          | AMD6800   | VS2012 | x64  | Windows7   |  27 | 19683 |
| i7-2600K 3.4 | GL2.1        | AMD6800   | VS2012 | x64  | Windows7   |  26 | 17576 |
| i7-4770R 3.2 | Mesa 10.0.1  | HD5200    | GCC    | x64  | SteamOS    |  25 | 15625 |
| i7-4750HQ 2.0| Mesa 10.0.1  | HD5200    | GCC    | x64  | Linux      |  22 | 10648 |
| i7-4750HQ 2.0| Mesa 10.1.3  | HD5200    | GCC    | x64  | Linux      |  21 |  9261 |
| i7-920 2.66  | ES2-ANGLE    | GTX650Ti  | VS2008 | x86  | Windows7   |  21 |  9261 |
| Q8200 2.33   | Gallium 0.4  | AMD5770   | GCC    | x64  | Linux      |  21 |  9261 |
| i5-4250U 1.3 | ES2          | HD5000    | Clang  | JIT  | PNaCl 31   |  21 |  9261 |
| i5-4250U 1.3 | ES2          | HD5000    | GCC    | x86  | NaCl 31    |  20 |  8000 |
| Q8200 2.33   | Gallium 0.4  | GTX260    | GCC    | x64  | Linux      |  19 |  6859 |
| i5-2450M 2.5 | Mesa 10.2.0  | HD3000    | GCC    | x64  | Linux      |  19 |  6859 |
| i7-920 2.66  | ES2-PowerVR  | GTX650Ti  | VS2008 | x86  | Windows7   |  18 |  5832 |
| i7-920 2.66  | FF27-GL      | GTX650Ti  | Clang  | JIT  | W7-asm.js  |  17 |  4913 |
| i7-4750HQ 2.0| Mesa 8.0.5   | LLVMPIPE  | GCC    | x64  | Linux      |  16 |  4096 |
| i7-920 2.66  | ES2-Qualcomm | GTX650Ti  | VS2008 | x86  | Windows7   |  15 |  3375 |
| i7-920 2.66  | ES2          | GTX650Ti  | GCC    | x64  | NaCl 31    |  15 |  3375 |
| i7-920 2.66  | ES2          | GTX650Ti  | Clang  | JIT  | PNaCl 31   |  15 |  3375 |
| Q8200 2.33   | NV 319.32    | GTX260    | GCC    | x64  | NaCl 31    |  15 |  3375 |
| Q8200 2.33   | NV 319.32    | GTX260    | GCC    | x64  | PNaCl 31   |  15 |  3375 |
| '12 Nexus 7  | ES2          | Tegra3    | GCC    | ARM  | Android    |  15 |  3375 |
| i5-4250U 1.3 | ES2-FF27     | HD5000    | Clang  | JIT  | OSX-asm.js |  15 |  3375 |
| i5-4250U 1.3 | Chrome33     | HD5000    | Clang  | JIT  | OSX-asm.js |  15 |  3375 |
| iPad mini 2  | ES2          | PVR G6430 | Clang  | ARM64| iOS7       |  15 |  3375 |
| i7-920 2.66  | Chrome33     | GTX650Ti  | Clang  | JIT  | W7-asm.js  |  14 |  2744 |
| i7-920 2.66  | FF27-ANGLE   | GTX650Ti  | Clang  | JIT  | W7-asm.js  |  12 |  2744 |
| '13 Nexus 10 | ES2          | Mali T604 | GCC    | ARM  | Android    |  13 |  2197 |
| iPhone 5     | ES2          | PVR SGX543| Clang  | ARM  | iOS7       |  13 |  2197 |
| '13 Nexus 7  | ES2          | S4 Pro    | GCC    | ARM  | Android    |  12 |  1728 |
| iPad 2       | ES2          | PVR SGX543| Clang  | ARM  | iOS6       |  12 |  1728 |
| Xperia Z     | ES2          | Adreno320 | GCC    | ARM  | Android    |  11 |  1331 |
| iPod 4       | ES2          | PVR SGX535| Clang  | ARM  | iOS6       |   7 |   343 |
| i7-920 2.66  | ES2-Mali     | GTX650Ti  | VS2008 | x86  | Windows7   |   6 |   216 |
| RaspberryPi  | ES2          | VC IV     | GCC    | ARM  | Raspbian   |   6 |   216 |

To test browsers in 60Hz mode following changes were made:

 * Firefox 27 about:config adjustments: `webgl.prefer-native-gl true` (on Windows),
   and `layout.frame_rate 500`.
 * Chrome 33 command line option: `--disable-gpu-vsync`.

#### 30Hz (test for browsers)

By default browsers are using vsync, and don't have option to turn it off
programatically.

| CPU          | Renderer | GPU       |Compiler| Arch | OS           | Dim | Calls |
|:-------------|:---------|:----------|:------:|:----:|:------------:|----:|------:|
| i7-920 2.66  | GL2.1    | GTX650Ti  | VS2008 | x64  | Windows7     |  38 | 64000+|
| i5-4250U 1.3 | GL2.1    | HD5000    | Clang  | x64  | OSX 10.9     |  36 | 46656 |
| i5-4250U 1.3 | Chrome34 | HD5000    | Clang  | JIT  | OSX-PNaCl 31 |  28 | 21952 |
| i5-4250U 1.3 | Chrome33 | HD5000    | Clang  | JIT  | OSX-PNaCl 31 |  27 | 19683 |
| i5-4250U 1.3 | FF28     | HD5000    | Clang  | JIT  | OSX-asm.js   |  25 | 15625 |
| i5-4250U 1.3 | FF27     | HD5000    | Clang  | JIT  | OSX-asm.js   |  20 |  8000 |
| i7-920 2.66  | Chrome33 | GTX650Ti  | Clang  | JIT  | W7-PNaCl 31  |  20 |  8000 |
| i7-920 2.66  | Chrome34 | GTX650Ti  | Clang  | JIT  | W7-asm.js    |  18 |  5832 |
| i7-920 2.66  | Chrome33 | GTX650Ti  | Clang  | JIT  | W7-asm.js    |  18 |  5832 |
| i7-920 2.66  | FF28     | GTX650Ti  | Clang  | JIT  | W7-asm.js    |  18 |  5832 |
| i7-920 2.66  | FF27     | GTX650Ti  | Clang  | JIT  | W7-asm.js    |  18 |  5832 |
| i5-4250U 1.3 | Safari7  | HD5000    | Clang  | JIT  | OSX-asm.js   |  15 |  3375 |

 * [JavaScript+WebGL port](https://github.com/djg/webgl-drawstress-js)

### [18-ibl](https://github.com/bkaradzic/bgfx/tree/master/examples/18-ibl)

Image based lighting.

![example-18-ibl](https://github.com/bkaradzic/bgfx/raw/master/examples/18-ibl/screenshot.png)

### [19-oit](https://github.com/bkaradzic/bgfx/tree/master/examples/19-oit)

Weighted, Blended Order-Independent Transparency

![example-19-oit](https://github.com/bkaradzic/bgfx/raw/master/examples/19-oit/screenshot.png)

### [20-nanovg](https://github.com/bkaradzic/bgfx/tree/master/examples/20-nanovg)

NanoVG is small antialiased vector graphics rendering library.

![example-20-nanovg](https://github.com/bkaradzic/bgfx/raw/master/examples/20-nanovg/screenshot.png)

### [21-deferred](https://github.com/bkaradzic/bgfx/tree/master/examples/21-deferred)

MRT rendering and deferred shading.

![example-21-deferred](https://github.com/bkaradzic/bgfx/raw/master/examples/21-deferred/screenshot.png)

### [22-windows](https://github.com/bkaradzic/bgfx/tree/master/examples/22-windows)

Rendering into multiple windows.

Dependencies
------------

[https://github.com/bkaradzic/bx](https://github.com/bkaradzic/bx)

Building
--------

### Prerequisites

Windows users download GnuWin32 utilities from:  
[http://gnuwin32.sourceforge.net/packages/make.htm](http://gnuwin32.sourceforge.net/packages/make.htm)  
[http://gnuwin32.sourceforge.net/packages/coreutils.htm](http://gnuwin32.sourceforge.net/packages/coreutils.htm)  
[http://gnuwin32.sourceforge.net/packages/libiconv.htm](http://gnuwin32.sourceforge.net/packages/libiconv.htm)  
[http://gnuwin32.sourceforge.net/packages/libintl.htm](http://gnuwin32.sourceforge.net/packages/libintl.htm)

### Getting source

	git clone git://github.com/bkaradzic/bx.git
	git clone git://github.com/bkaradzic/bgfx.git
	cd bgfx
	make

After calling `make`, .build/projects/* directory will be generated. All
intermediate files generated by compiler will be inside .build directory
structure. Deleting .build directory at any time is safe.

### Prerequisites for Android

Download AndroidNDK from:  
[https://developer.android.com/tools/sdk/ndk/index.html](https://developer.android.com/tools/sdk/ndk/index.html)

	setx ANDROID_NDK_ROOT <path to AndroidNDK directory>
	setx ANDROID_NDK_ARM <path to AndroidNDK directory>\toolchains\arm-linux-androideabi-4.7\prebuilt\windows-x86_64
	setx ANDROID_NDK_MIPS <path to AndroidNDK directory>\toolchains\mipsel-linux-android-4.7\prebuilt\windows-x86_64
	setx ANDROID_NDK_X86 <path to AndroidNDK directory>\toolchains\x86-4.7\prebuilt\windows-x86_64

### Prerequisites for Linux

	sudo apt-get install libgl1-mesa-dev

### Prerequisites for Native Client

Download Native Client SDK from:  
[https://developers.google.com/native-client/sdk/download](https://developers.google.com/native-client/sdk/download)

	setx NACL_SDK_ROOT <path to Native Client SDK directory>

### Prerequisites for Windows

When building on Windows, you have to set DXSDK_DIR environment variable to
point to DirectX SDK directory.

	setx DXSDK_DIR <path to DirectX SDK directory>

If you're building with Visual Studio 2008, you'll need TR1 support from:  
[Visual C++ 2008 Feature Pack Release](https://www.microsoft.com/en-us/download/details.aspx?id=6922)

If you're building with MinGW/TDM compiler on Windows make DirectX SDK
directory link to directory without spaces in the path.

	mklink /D c:\dxsdk <path to DirectX SDK directory>
	setx DXSDK_DIR c:\dxsdk

Apply this [patch](https://github.com/bkaradzic/bx/blob/master/include/compat/mingw/dxsdk.patch)
to DXSDK from June 2010 to be able to use it with MinGW/TDM.

### Building

Visual Studio 2008 command line:

	make vs2008-release64

Visual Studio 2008 IDE:

	start .build/projects/vs2008/bgfx.sln

Xcode 5 IDE:

	open .build/projects/xcode4/bgfx.xcworkspace
Due to [inability](http://industriousone.com/debugdir) to set working directory for an Xcode project from premake configuration file, it has to be set manually for each example project:

1. Open *"Edit scheme..."* dialog for a given project.
2. Select *"Run"* settings.
3. Check *"Use custom working directory"* and enter following path: `${PROJECT_DIR}/../../../examples/runtime`.

Linux 64-bit:

	make linux-release64

Other platforms:

	make <configuration>

Configuration is `<platform>-<debug/release>[32/64]`. For example:

	linux-release32, nacl-debug64, nacl-arm-debug, pnacl-release, 
	android-release, etc.

Internals
---------

bgfx is using sort-based draw call bucketing. This means that submission order
doesn't necessarily match the rendering order, but on the low-level they
will be sorted and ordered correctly. On the high level this allows
more optimal way of submitting draw calls for all passes at one place, and on
the low-level this allows better optimization of rendering order. This sometimes
creates undesired results usually for GUI rendering, where draw order should
usually match submit order. bgfx provides way to enable sequential rendering for
these cases (see `bgfx::setViewSeq`).

Internally all low-level rendering draw calls are issued inside single function
`Context::rendererSubmit`. This function exist inside each renderer backend
implementation.

More detailed description of sort-based draw call bucketing can be found at:  
[Order your graphics draw calls around!](http://realtimecollisiondetection.net/blog/?p=86)

Customization
-------------

By default each platform has sane default values. For example on Windows default
renderer is DirectX9, and on Linux it is OpenGL 2.1. On Windows platform all
rendering backends are available. For OpenGL ES on desktop you can find more 
information at:- 
[OpenGL ES 2.0 and EGL on desktop](http://www.g-truc.net/post-0457.html)  

If you're targeting specific mobile hardware, you can find GLES support in their
official SDKs:
[Adreno SDK](http://developer.qualcomm.com/mobile-development/mobile-technologies/gaming-graphics-optimization-adreno/tools-and-resources),
[Mali SDK](http://www.malideveloper.com/),
[PowerVR SDK](http://www.imgtec.com/powervr/insider/sdkdownloads/).

All configuration settings are located inside [src/config.h](https://github.com/bkaradzic/bgfx/blob/master/src/config.h).

Every `BGFX_CONFIG_*` setting can be changed by passing defines thru compiler
switches. For example setting preprocessor define `BGFX_CONFIG_RENDERER_OPENGL=1`
will change backend renderer to OpenGL 2.1. on Windows. Since rendering APIs are
platform specific, this obviously won't work nor make sense in all cases.
Certain platforms have only single choice, for example the Native Client works
only with OpenGL ES 2.0 renderer, using anything other than that will result in
build errors.

Debugging and Profiling
-----------------------

### RenderDoc

Loading of RenderDoc is integrated in bgfx when using DX11 renderer. You can
drop in `renderdoc.dll` from RenderDoc distribution into working directory,
and it will be automatically loaded during bgfx initialization. This allows
frame capture at any time by pressing **F11**.

Download: [RenderDoc](https://renderdoc.org/builds)

### IntelGPA

Right click **Intel GPA Monitor** tray icon, choose preferences, check
"Auto-detect launched applications" option. Find `InjectionList.txt` in GPA
directory and add `examples-*` to the list.

Download: [IntelGPA](https://software.intel.com/en-us/vcsource/tools/intel-gpa)

Other debuggers:

| Name      | OS            | DX9  | DX11 |  GL  | GLES | Source |
|:----------|:--------------|:----:|:----:|:----:|:----:|:------:|
| APITrace  | Linux/OSX/Win |   x  |  x   |  x   |   x  |    x   |
| CodeXL    | Linux/Win     |      |      |  x   |      |        |
| IntelGPA  | Linux/OSX/Win |   x  |  x   |      |   x  |        |
| Nsight    | Win           |   x  |  x   |  x   |      |        |
| PerfHUD   | Win           |   x  |  x   |      |      |        |
| RenderDoc | Win           |      |  x   |      |      |    x   |
| vogl      | Linux         |      |      |  x   |      |    x   |

Download:  
[APITrace](https://apitrace.github.io/)  
[CodeXL](http://developer.amd.com/tools-and-sdks/opencl-zone/codexl/)  
[Nsight](https://developer.nvidia.com/nvidia-nsight-visual-studio-edition)  
[PerfHUD](https://developer.nvidia.com/nvidia-perfhud)  
[vogl](https://github.com/ValveSoftware/vogl)  

SDL, GLFW, etc.
---------------

It is possible to use bgfx with SDL, GLFW and similar cross platform windowing
libraries. The main requirement is that windowing library provides access to
native window handle that's used to create Direct3D device or OpenGL context.

Using bgfx with SDL example:

	#include <SDL.h>
	#include <bgfxplatform.h> // it must be included after SDL to enable SDL
	                          // integration code path.
	
	#include <bgfx.h>
	...
	
	int main(...
	{
	    SDL_window* window = SDL_CreateWindow(...
	    bgfx::sdlSetWindow(window);
	
	    ...
	    bgfx::init();

Tools
-----

### Shader Compiler (shaderc)

bgfx cross-platform shader language is based on GLSL syntax. It's uses ANSI C
preprocessor to transform GLSL like language syntax into HLSL. This technique
has certain drawbacks, but overall it's simple and allows quick authoring of
cross-platform shaders.

Some differences between bgfx's shaderc flavor of GLSL and regular GLSL:

 - No `bool/int` uniforms, all uniforms must be `float`.
 - Attributes and varyings can be accessed only from `main()` function.
 - Must use `SAMPLER2D/3D/CUBE/etc.` macros instead of `sampler2D/3D/Cube/etc.`
   tokens.
 - Must use `vec2/3/4_splat(<value>)` instead of `vec2/3/4(<value>)`.
 - Must use `mul(x, y)` when multiplying vectors and matrices.
 - Must use `varying.def.sc` to define input/output semantic and precission
   instead of using `attribute/in` and `varying/in/out`.
 - `$input/$output` tokens must appear at the begining of shader.

For more info see [shader helper macros](https://github.com/bkaradzic/bgfx/blob/master/src/bgfx_shader.sh).

### Texture Compiler (texturec)

This tool doesn't currently exist. To produce DDS, KTX or PVR textures use:

[.dds - nVidia Texture Tools - DDS Utilities](https://developer.nvidia.com/legacy-texture-tools)  
[.ktx - Mali GPU Texture Compression Tool](http://malideveloper.arm.com/develop-for-mali/mali-gpu-texture-compression-tool/)  
[.pvr - PowerVR Insider SDK](http://www.imgtec.com/powervr/insider/sdkdownloads/index.asp)

### Geometry Compiler (geometryc)

Converts Wavefront .obj mesh file to format optimal for using with bgfx.

Todo
----

 - Blit between textures.
 - Occlusion queries.
 - Fullscreen mode.
 - ETC2, PVRTC1/2 decoding fallback for targets that don't support it natively.

Contact
-------

[@bkaradzic](https://twitter.com/bkaradzic)  
http://www.stuckingeometry.com

Project page  
https://github.com/bkaradzic/bgfx

3rd Party Libraries
-------------------

All required 3rd party libraries are included in bgfx repository in [3rdparty/](https://github.com/bkaradzic/bgfx/tree/master/3rdparty)
directory.

### Blendish (MIT)

Blendish - Blender 2.5 UI based theming functions for NanoVG.

https://bitbucket.org/duangle/oui-blendish

### edtaa3 (MIT)

Contour Rendering by Distance Fields

https://github.com/OpenGLInsights/OpenGLInsightsCode/tree/master/Chapter%2012%202D%20Shape%20Rendering%20by%20Distance%20Fields

### fcpp (BSD)

Frexx C preprocessor

https://github.com/bagder/fcpp

### Forsyth Triangle Order Optimizer (Public Domain)

http://gameangst.com/?p=9

### FreeType

http://www.freetype.org/

### glsl-optimizer (MIT)

GLSL optimizer based on Mesa's GLSL compiler. Used in Unity for mobile shader
optimization.

https://github.com/aras-p/glsl-optimizer

### NanoVG (ZLIB)

NanoVG is small antialiased vector graphics rendering library.

https://github.com/memononen/nanovg

### SDF (MIT)

Sweep-and-update Euclidean distance transform of an antialised image for contour
texturing.

https://github.com/memononen/SDF

### stb_image, stb_truetype (Public Domain)

http://nothings.org

Assets
------

Bunny  
[Stanford University Computer Graphics Laboratory](http://www-graphics.stanford.edu/data/3Dscanrep/)

Uffizi  
[Light Probe Image Gallery](http://www.pauldebevec.com/Probes/)

Wells  
[Bernhard Vogl Light probes](http://dativ.at/lightprobes/)

Pisa, Ennis, Grace  
[High-Resolution Light Probe Image Gallery](http://gl.ict.usc.edu/Data/HighResProbes/)

Droid Sans Font  
http://www.fontsquirrel.com/license/Droid-Sans

Bleeding Cowboys Font  
http://www.dafont.com/bleeding-cowboys.font

Cheap Fire Font  
http://www.dafont.com/cheap-fire.font

Five Minutes Font  
http://www.fonts2u.com/fiveminutes.font

Mias Scribblings Font  
http://www.dafont.com/mias-scribblings.font

Ruritania Font  
http://www.dafont.com/ruritania.font

Signika Font  
http://fontfabric.com/signika-font/

Visitor Font  
http://www.dafont.com/visitor.font

Special-Elite Font  
http://www.fontspace.com/astigmatic-one-eye-typographic-institute/special-elite

FontAwesome Font  
http://fontawesome.io/

Sherlock Holmes text  
http://www.gutenberg.org/ebooks/1661

Tree Pack 1  
http://www.turbosquid.com/3d-models/free-obj-mode-tree-pack/506851

Getting involved
----------------

Everyone is welcome to contribute to bgfx by submitting bug reports, testing
on different platforms, writing examples, improving documentation, profiling
and optimizing, etc.

When contributing to the bgfx project you must agree to the BSD 2-clause
licensing terms.

Contributors
------------

Garett Bass ([@gtbass](https://github.com/gtbass)) - OSX port.  
Jeremie Roy ([@jeremieroy](https://github.com/jeremieroy)) - Font system and
  examples.  
Milos Tosic ([@milostosic](https://github.com/milostosic)) - 12-lod example.  
Dario Manesku ([@dariomanesku](https://github.com/dariomanesku)) - 13-stencil, 
  14-shadowvolumes, 15-shadowmaps-simple, 16-shadowmaps, 18-ibl  
James Gray ([@james4k](https://github.com/james4k)) - Go language API bindings.  
p0nce ([@p0nce](https://github.com/p0nce)) - D language API bindings.  
Mike Popoloski ([@MikePopoloski](https://github.com/MikePopoloski)) - C#/VB/F# 
language API bindings  

[License (BSD 2-clause)](https://github.com/bkaradzic/bgfx/blob/master/LICENSE)
-------------------------------------------------------------------------------

	Copyright 2010-2014 Branimir Karadzic. All rights reserved.
	
	https://github.com/bkaradzic/bgfx
	
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	
	   1. Redistributions of source code must retain the above copyright notice,
	      this list of conditions and the following disclaimer.
	
	   2. Redistributions in binary form must reproduce the above copyright notice,
	      this list of conditions and the following disclaimer in the documentation
	      and/or other materials provided with the distribution.
	
	THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDER ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
	EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
	OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
