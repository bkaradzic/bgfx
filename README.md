[bgfx](https://github.com/bkaradzic/bgfx) - Cross-platform rendering library
============================================================================

[What is it?](https://bkaradzic.github.io/bgfx/overview.html)
-------------------------------------------------------------

Cross-platform, graphics API agnostic, "Bring Your Own Engine/Framework" style
rendering library.

Supported rendering backends:

 * Direct3D 9
 * Direct3D 11
 * Direct3D 12 (WIP)
 * Metal (WIP)
 * OpenGL 2.1
 * OpenGL 3.1+
 * OpenGL ES 2
 * OpenGL ES 3.1
 * WebGL 1.0

Supported HMD:

 * OculusVR (0.4.2+)

Supported platforms:

 * Android (14+, ARM, x86, MIPS)
 * asm.js/Emscripten (1.25.0)
 * FreeBSD
 * iOS (iPhone, iPad, AppleTV)
 * Linux ![](https://tc27.draster.com/app/rest/builds/buildType:(id:Bgfx_Linux)/statusIcon)
 * MIPS Creator CI20
 * Native Client (PPAPI 37+, ARM, x86, x64, PNaCl)
 * OSX (10.9+)
 * RaspberryPi
 * Windows (XP, Vista, 7, 8, 10) ![](https://tc27.draster.com/app/rest/builds/buildType:(id:Bgfx_Windows)/statusIcon)
 * WinRT (WinPhone 8.0+)

Supported compilers:

 * Clang 3.3 and above
 * GCC 4.6 and above
 * vs2008 and above

Languages:

 * [C/C++ API documentation](https://bkaradzic.github.io/bgfx/bgfx.html)
 * [C#/VB/F# language API bindings](https://github.com/MikePopoloski/SharpBgfx)
 * [D language API bindings](https://github.com/DerelictOrg/DerelictBgfx)
 * [Go language API bindings](https://github.com/james4k/go-bgfx)
 * [Java language API bindings](https://github.com/enleeten/twilight-bgfx)
 * [Haskell language API bindings](https://github.com/haskell-game/bgfx)

Build status
------------

https://tc27.draster.com/guestAuth/overview.html

Who is using it?
----------------

http://airmech.com/ AirMech is a free-to-play futuristic action real-time
strategy video game developed and published by Carbon Games.

https://github.com/dariomanesku/cmftStudio cmftStudio - cubemap filtering tool.  
![cmftStudio](https://github.com/dariomanesku/cmftStudio/raw/master/screenshots/cmftStudio_small.jpg)

https://github.com/taylor001/crown Crown is a general purpose data-driven game
engine, written from scratch with a minimalistic and data-oriented design
philosophy in mind.  
![Crown screenshot](https://raw.githubusercontent.com/taylor001/crown/master/docs/shots/level-editor.png)

https://github.com/emoon/ProDBG - ProDBG is a new debugger under development
that will support a variety of targets and operating systems. Currently it's in
very early development and primary focusing on Mac as primary target. This is
how it currently looks.  
![ProDBG_screenshot](https://raw.githubusercontent.com/emoon/ProDBG/master/data/screens/mac_screenshot.png)

http://www.dogbytegames.com/ Dogbyte Games is an indie mobile developer studio
focusing on racing games.  
![ios](http://www.dogbytegames.com/bgfx/offroadlegends2_bgfx_ipad2.jpg)

https://github.com/andr3wmac/Torque6 Torque 6 is an MIT licensed 3D engine
loosely based on Torque2D. Being neither Torque2D or Torque3D it is the 6th
derivative of the original Torque Engine.
<a href="http://www.youtube.com/watch?feature=player_embedded&v=p4LTM_QGK34
" target="_blank"><img src="http://img.youtube.com/vi/p4LTM_QGK34/0.jpg" 
alt="Torque 6 Material Editor" width="640" height="480" border="0" /></a>

https://github.com/cgbystrom/twinkle GPU-accelerated UI framework powered by
JavaScript for desktop/mobile apps. Idea is to combine the fast workflow and
deployment model of web with the performance of native code and GPU acceleration.

https://github.com/nem0/LumixEngine LumixEngine is a MIT licensed 3D engine.
The main goal is performance and Unity-like usability.  
![LumixEngine screenshot](https://cloud.githubusercontent.com/assets/153526/10109455/450c51be-63c7-11e5-9c87-96d9d00efe02.png)

https://github.com/podgorskiy/KeplerOrbits KeplerOrbits - Tool that calculates
positions of celestial bodies using their orbital elements. [Web Demo](http://podgorskiy.com/KeplerOrbits/KeplerOrbits.html)

https://github.com/cyberegoorg/cetech - CETech is Data-Driven game engine and
toolbox inspired by Bitsquid/Stingray engine.  
![CETech screenshot](https://github.com/cyberegoorg/cetech/raw/master/docs/img/prototyp.png)

https://github.com/jpcy/ioq3-renderer-bgfx - A renderer for ioquake3 written in
C++ and using bgfx to support multiple rendering APIs.  
![ioq3-renderer-bgfx screenshot](https://camo.githubusercontent.com/052aa40c05120e56306294d3a1bb5f99f97de8c8/687474703a2f2f692e696d6775722e636f6d2f64364f6856594b2e6a7067)

[Building](https://bkaradzic.github.io/bgfx/build.html)
-------------------------------------------------------

[Examples](https://bkaradzic.github.io/bgfx/examples.html)
----------------------------------------------------------

[API Reference](https://bkaradzic.github.io/bgfx/bgfx.html)
-----------------------------------------------------------

[Tools](https://bkaradzic.github.io/bgfx/tools.html)
----------------------------------------------------

[License (BSD 2-clause)](https://bkaradzic.github.io/bgfx/license.html)
-----------------------------------------------------------------------

<a href="http://opensource.org/licenses/BSD-2-Clause" target="_blank">
<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">
</a>

	Copyright 2010-2016 Branimir Karadzic. All rights reserved.
	
	https://github.com/bkaradzic/bgfx
	
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	
	   1. Redistributions of source code must retain the above copyright notice,
	      this list of conditions and the following disclaimer.
	
	   2. Redistributions in binary form must reproduce the above copyright
	      notice, this list of conditions and the following disclaimer in the
	      documentation and/or other materials provided with the distribution.
	
	THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDER ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
	EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
