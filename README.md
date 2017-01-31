[bgfx](https://github.com/bkaradzic/bgfx) - Cross-platform rendering library
============================================================================

[![Build Status](https://travis-ci.org/bkaradzic/bgfx.svg?branch=master)](https://travis-ci.org/bkaradzic/bgfx)
[![Build status](https://ci.appveyor.com/api/projects/status/ipa3ojgeaet1oko5?svg=true)](https://ci.appveyor.com/project/bkaradzic/bgfx)
[![License](https://img.shields.io/badge/license-BSD--2%20clause-blue.svg)](https://bkaradzic.github.io/bgfx/license.html)
[![Join the chat at https://gitter.im/bkaradzic/bgfx](https://badges.gitter.im/bkaradzic/bgfx.svg)](https://gitter.im/bkaradzic/bgfx)

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
 * WebGL 2.0

Supported HMD:

 * OculusVR (1.3.0)

Supported platforms:

 * Android (14+, ARM, x86, MIPS)
 * asm.js/Emscripten (1.25.0)
 * FreeBSD
 * iOS (iPhone, iPad, AppleTV)
 * Linux
 * MIPS Creator CI20
 * Native Client (PPAPI 37+, ARM, x86, x64, PNaCl)
 * OSX (10.9+)
 * RaspberryPi
 * SteamLink
 * Windows (XP, Vista, 7, 8, 10)
 * WinRT (WinPhone 8.0+)

Supported compilers:

 * Clang 3.3 and above
 * GCC 4.6 and above
 * VS2012 and above

Languages:

 * [C/C++ API documentation](https://bkaradzic.github.io/bgfx/bgfx.html)
 * [C#/VB/F# language API bindings](https://github.com/MikePopoloski/SharpBgfx)
 * [D language API bindings](https://github.com/DerelictOrg/DerelictBgfx)
 * [Go language API bindings](https://github.com/james4k/go-bgfx)
 * [Haskell language API bindings](https://github.com/haskell-game/bgfx)
 * [Lightweight Java Game Library 3 bindings](https://github.com/LWJGL/lwjgl3)
 * [Lua language API bindings](https://github.com/excessive/lua-bgfx)
 * [Nim language API bindings](https://github.com/Halsys/nim-bgfx)
 * [Python language API bindings](https://github.com/jnadro/pybgfx#pybgf)
 * [Rust language API bindings](https://github.com/rhoot/bgfx-rs)
 * [Swift language API bindings](https://github.com/stuartcarnie/SwiftBGFX)

[Building](https://bkaradzic.github.io/bgfx/build.html)
----------------------------------------------------

 - AppVeyor https://ci.appveyor.com/project/bkaradzic/bgfx
 - TravisCI https://travis-ci.org/bkaradzic/bgfx

[Examples](https://bkaradzic.github.io/bgfx/examples.html)
----------------------------------------------------------

[API Reference](https://bkaradzic.github.io/bgfx/bgfx.html)
-----------------------------------------------------------

[Tools](https://bkaradzic.github.io/bgfx/tools.html)
----------------------------------------------------

Who is using it?
----------------

## Airmech

http://airmech.com/ AirMech is a free-to-play futuristic action real-time
strategy video game developed and published by Carbon Games.  
![airmech](https://www.mobygames.com/images/shots/l/830630-airmech-playstation-4-screenshot-blue-bar-on-your-mech-indicates.jpg)

## cmftStudio

https://github.com/dariomanesku/cmftStudio cmftStudio - cubemap filtering tool.  
![cmftStudio](https://github.com/dariomanesku/cmftStudio/raw/master/screenshots/cmftStudio_small.jpg)

## Crown

https://github.com/taylor001/crown Crown is a general purpose data-driven game
engine, written from scratch with a minimalistic and data-oriented design
philosophy in mind.  
![Crown screenshot](https://raw.githubusercontent.com/taylor001/crown/master/docs/shots/level-editor.png)

## Offroad Legends 2

http://www.dogbytegames.com/ Dogbyte Games is an indie mobile developer studio
focusing on racing games.  
![ios](http://www.dogbytegames.com/bgfx/offroadlegends2_bgfx_ipad2.jpg)

## Torque6

https://github.com/andr3wmac/Torque6 Torque 6 is an MIT licensed 3D engine
loosely based on Torque2D. Being neither Torque2D or Torque3D it is the 6th
derivative of the original Torque Engine.
<a href="http://www.youtube.com/watch?feature=player_embedded&v=p4LTM_QGK34
" target="_blank"><img src="http://img.youtube.com/vi/p4LTM_QGK34/0.jpg" 
alt="Torque 6 Material Editor" width="640" height="480" border="0" /></a>

## twinkle

https://github.com/cgbystrom/twinkle GPU-accelerated UI framework powered by
JavaScript for desktop/mobile apps. Idea is to combine the fast workflow and
deployment model of web with the performance of native code and GPU acceleration.

## Lumix Engine

https://github.com/nem0/LumixEngine LumixEngine is a MIT licensed 3D engine.
The main goal is performance and Unity-like usability.  
![LumixEngine screenshot](https://cloud.githubusercontent.com/assets/153526/12904252/3fcf130e-cece-11e5-878b-c9fe24c1b11a.png)

## Kepler Orbits

https://github.com/podgorskiy/KeplerOrbits KeplerOrbits - Tool that calculates
positions of celestial bodies using their orbital elements. [Web Demo](http://podgorskiy.com/KeplerOrbits/KeplerOrbits.html)

## CETech

https://github.com/cyberegoorg/cetech - CETech is Data-Driven game engine and
toolbox inspired by Bitsquid/Stingray engine.  
![CETech screenshot](https://github.com/cyberegoorg/cetech/raw/master/docs/img/prototyp.png)

## ioquake3

https://github.com/jpcy/ioq3-renderer-bgfx - A renderer for ioquake3 written in
C++ and using bgfx to support multiple rendering APIs.  
![ioq3-renderer-bgfx screenshot](https://camo.githubusercontent.com/052aa40c05120e56306294d3a1bb5f99f97de8c8/687474703a2f2f692e696d6775722e636f6d2f64364f6856594b2e6a7067)

## DLS

http://makingartstudios.itch.io/dls - DLS the digital logic simulator game.  
![dls-screenshot](https://img.itch.io/aW1hZ2UvMzk3MTgvMTc5MjQ4LnBuZw==/original/kA%2FQPb.png)

## MAME

https://github.com/mamedev/mame MAME - Multiple Arcade Machine Emulator
[Try MAME in Browser!](http://fos.textfiles.com/dfjustin/pacman/pacman/)  
![mame-screenshot](https://raw.githubusercontent.com/mamedev/www.mamedev.org/d8d716dbb63919a11964b5d47b9b7f6cfa006b56/bgfx/Raiden.png)

## Blackshift

https://blackshift.itch.io/blackshift - Blackshift is a grid-based, space-themed
action puzzle game which isn't afraid of complexity — think Chip's Challenge on
crack. 
<a href="http://www.youtube.com/watch?feature=player_embedded&v=PUl8612Y-ds
" target="_blank"><img src="http://img.youtube.com/vi/PUl8612Y-ds/0.jpg" 
alt="Blackshift Trailer, May 2016"
width="640" height="480" border="0" /></a>

## Real-Time Polygonal-Light Shading with Linearly Transformed Cosines

https://eheitzresearch.wordpress.com/415-2/ - Real-Time Polygonal-Light Shading
with Linearly Transformed Cosines, Eric Heitz, Jonathan Dupuy, Stephen Hill and
David Neubelt, ACM SIGGRAPH 2016
<a href="http://www.youtube.com/watch?feature=player_embedded&v=ZLRgEN7AQgM
" target="_blank"><img src="http://img.youtube.com/vi/ZLRgEN7AQgM/0.jpg" 
alt="Real-Time Polygonal-Light Shading with Linearly Transformed Cosines"
width="640" height="480" border="0" /></a>

## Dead Venture

http://www.dogbytegames.com/dead_venture.html - Dead Venture is a new Drive 'N
Gun game where you help a handful of survivals reach the safe haven: a military
base on a far island.
<a href="http://www.youtube.com/watch?feature=player_embedded&v=CgMr1g12yXw
" target="_blank"><img src="http://img.youtube.com/vi/CgMr1g12yXw/0.jpg" 
alt="Dead Venture - Gameplay Teaser (iOS / Android)"
width="640" height="480" border="0" /></a>

## REGoth

https://github.com/degenerated1123/REGoth - Open source reimplementation of the
zEngine, used by the game "Gothic" and "Gothic II".

Browser demo: http://gothic-dx11.de/gothic-js/REGoth.html

<a href="http://www.youtube.com/watch?feature=player_embedded&v=8bLAGttYYpY
" target="_blank"><img src="http://img.youtube.com/vi/8bLAGttYYpY/0.jpg" 
alt="REGoth Engine"
width="640" height="480" border="0" /></a>

## Ethereal Engine

https://github.com/volcoma/EtherealEngine EtherealEngine C++ Game Engine and
WYSIWYG Editor  
![EtherealEngine screenshot](https://cloud.githubusercontent.com/assets/1499411/19988985/2a302204-a22c-11e6-98af-5f446d0c79ac.png)

## Go Rally

http://gorallygame.com/ - Go Rally is top-down rally game with a career mode,
multiplayer time challenges, and a track creator.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=ckbkQsB6RVY
" target="_blank"><img src="http://img.youtube.com/vi/ckbkQsB6RVY/0.jpg" 
alt="Go Rally"
width="640" height="480" border="0" /></a>

## Fiber2D

https://github.com/s1ddok/Fiber2D#fiber2d - Fiber2D - Cross-platform 2D Game
Engine in pure Swift  
![Fiber2D Demo Gif](http://imgur.com/CP6d9kT.gif)

[License (BSD 2-clause)](https://bkaradzic.github.io/bgfx/license.html)
-----------------------------------------------------------------------

<a href="http://opensource.org/licenses/BSD-2-Clause" target="_blank">
<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">
</a>

	Copyright 2010-2017 Branimir Karadzic. All rights reserved.
	
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
