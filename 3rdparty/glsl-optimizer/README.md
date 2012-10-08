GLSL optimizer
==============

A C++ library that takes GLSL shaders, does some GPU-independent optimizations on them
and outputs GLSL back. Optimizations are function inlining, dead code removal, copy propagation,
constant folding, constant propagation, arithmetic optimizations and so on.

Apparently quite a few mobile platforms are pretty bad at optimizing GLSL shaders; and
unfortunately they *also* lack offline shader compilers. So using a GLSL optimizer offline
before can make the shader run much faster on a platform like that. See performance numbers
in [this blog post](http://aras-p.info/blog/2010/09/29/glsl-optimizer/).

Almost all actual code is [Mesa 3D's GLSL](http://cgit.freedesktop.org/mesa/mesa/log/)
compiler; all this library does is spits out optimized GLSL back, and adds GLES type precision
handling to the optimizer.

This GLSL optimizer is made for [Unity's](http://unity3d.com/) purposes and is built-in
in [Unity 3](http://unity3d.com/unity/whats-new/unity-3) and later.

GLSL Optimizer is licensed according to the terms of the MIT license.


Usage
-----

Visual Studio 2008 (Windows, x86) and Xcode 3.2 (Mac, i386) project files for a static
library are provided in `src/glsl/msvc/mesaglsl2.vcproj` and `src/glsl/xcode/mesaglsl2`
respectively.

For Linux you can use cmake. Just type "cmake . && make" in the root directory.
This will build the optimizer library and some executable binaries.

Interface for the library is `src/glsl/glsl_optimizer.h`. General usage is:
 
	ctx = glslopt_initialize();
	for (lots of shaders) {
		shader = glslopt_optimize (ctx, shaderType, shaderSource, options);
		if (glslopt_get_status (shader)) {
			newSource = glslopt_get_output (shader);
		} else {
			errorLog = glslopt_get_log (shader);
		}
		glslopt_shader_delete (shader);
	}
	glslopt_cleanup (ctx);

Notes
-----

* GLSL versions 1.10 and 1.20 are supported. 1.10 is the default, use #version 120 to specify 
1.20.
* GLSL ES version 1.00 is supported.
