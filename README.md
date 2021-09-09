<p align="center">
<img src="https://repository-images.githubusercontent.com/3925242/a4566200-912a-11ea-984f-c387546a3126">
</p>

[bgfx](https://github.com/bkaradzic/bgfx) - Cross-platform rendering library
============================================================================

<p align="center">
    <a href="#what-is-it">What is it?</a> -
    <a href="https://bkaradzic.github.io/bgfx/build.html">Building</a> -
    <a href="https://bkaradzic.github.io/bgfx/overview.html#getting-involved">Getting Involved</a> -
    <a href="https://bkaradzic.github.io/bgfx/examples.html">Examples</a> -
    <a href="https://bkaradzic.github.io/bgfx/bgfx.html">API Reference</a> -
    <a href="https://bkaradzic.github.io/bgfx/tools.html">Tools</a> -
    <a href="#who-is-using-it-madewithbgfx">Who is using it?</a> -
    <a href="#license-bsd-2-clause">License</a>
</p>

[![Build status](https://ci.appveyor.com/api/projects/status/ipa3ojgeaet1oko5?svg=true)](https://ci.appveyor.com/project/bkaradzic/bgfx)
[![License](https://img.shields.io/badge/license-BSD--2%20clause-blue.svg)](https://bkaradzic.github.io/bgfx/license.html)
[![Join the chat at https://discord.gg/9eMbv7J](https://img.shields.io/discord/712512073522872352?color=%237289DA&label=bgfx&logo=discord&logoColor=white)](https://discord.gg/9eMbv7J)

 * [GitHub Discussions](https://github.com/bkaradzic/bgfx/discussions)
 * [Discord Chat](https://discord.gg/9eMbv7J)
 * [AppVeyor CI](https://ci.appveyor.com/project/bkaradzic/bgfx)

[What is it?](https://bkaradzic.github.io/bgfx/overview.html)
-------------------------------------------------------------

Cross-platform, graphics API agnostic, "Bring Your Own Engine/Framework" style
rendering library.

Supported rendering backends:

 * Direct3D 9
 * Direct3D 11
 * Direct3D 12
 * GNM (only for licensed PS4 developers, search DevNet forums for source)
 * Metal
 * OpenGL 2.1
 * OpenGL 3.1+
 * OpenGL ES 2
 * OpenGL ES 3.1
 * Vulkan
 * WebGL 1.0
 * WebGL 2.0
 * WebGPU/Dawn (experimental)

Supported platforms:

 * Android (14+, ARM, x86, MIPS)
 * asm.js/Emscripten (1.25.0)
 * FreeBSD
 * iOS (iPhone, iPad, AppleTV)
 * Linux
 * MIPS Creator CI20
 * OSX (10.12+)
 * PlayStation 4
 * RaspberryPi
 * Windows (XP, Vista, 7, 8, 10)
 * UWP (Universal Windows, Xbox One)

Supported compilers:

 * Clang 3.3 and above
 * GCC 5 and above
 * VS2017 and above

Languages:

 * [C/C++ API documentation](https://bkaradzic.github.io/bgfx/bgfx.html)
 * [Beef API bindings](https://github.com/bkaradzic/bgfx/tree/master/bindings/bf)
 * [C# language API bindings #1](https://github.com/bkaradzic/bgfx/tree/master/bindings/cs)
 * [C#/VB/F# language API bindings #2](https://github.com/MikePopoloski/SharpBgfx)
 * [D language API bindings](https://github.com/GoaLitiuM/bindbc-bgfx)
 * [Go language API bindings](https://github.com/james4k/go-bgfx)
 * [Haskell language API bindings](https://github.com/haskell-game/bgfx)
 * [Lightweight Java Game Library 3 bindings](https://github.com/LWJGL/lwjgl3)
 * [Lua language API bindings](https://github.com/cloudwu/lua-bgfx)
 * [Nim language API bindings](https://github.com/Halsys/nim-bgfx)
 * [Pascal language API bindings](https://github.com/Akira13641/PasBGFX)
 * [Python language API bindings #1](https://github.com/fbertola/bgfx-python#-----bgfx-python--)
 * [Python language API bindings #2](https://github.com/jnadro/pybgfx#pybgfx)
 * [Rust language API bindings (obsolete)](https://github.com/rhoot/bgfx-rs)
 * [Rust language API bindings (new)](https://github.com/emoon/bgfx-rs)
 * [Swift language API bindings](https://github.com/stuartcarnie/SwiftBGFX)

Who is using it? [#madewithbgfx](https://twitter.com/search?q=%23madewithbgfx&f=live)
-------------------------------------------------------------------------------------

## Airmech

http://airmech.com/ AirMech is a free-to-play futuristic action real-time
strategy video game developed and published by Carbon Games.  
![airmech](https://www.mobygames.com/images/shots/l/830630-airmech-playstation-4-screenshot-blue-bar-on-your-mech-indicates.jpg)

## cmftStudio

https://github.com/dariomanesku/cmftStudio cmftStudio - cubemap filtering tool.  
![cmftStudio](https://github.com/dariomanesku/cmftStudio/raw/master/screenshots/cmftStudio_small.jpg)

## Crown

https://github.com/dbartolini/crown Crown is a general purpose data-driven game
engine, written from scratch with a minimalistic and data-oriented design
philosophy in mind.  
![Crown screenshot](https://raw.githubusercontent.com/dbartolini/crown/master/docs/shots/level-editor.png)

## Offroad Legends 2

http://www.dogbytegames.com/ Dogbyte Games is an indie mobile developer studio
focusing on racing games.  
![ios](http://www.dogbytegames.com/bgfx/offroadlegends2_bgfx_ipad2.jpg)

## Torque6

https://github.com/andr3wmac/Torque6 Torque 6 is an MIT licensed 3D engine
loosely based on Torque2D. Being neither Torque2D or Torque3D it is the 6th
derivative of the original Torque Engine.
<a href="http://www.youtube.com/watch?feature=player_embedded&v=p4LTM_QGK34" 
target="_blank"><img src="http://img.youtube.com/vi/p4LTM_QGK34/0.jpg" 
alt="Torque 6 Material Editor" width="640" height="480" border="0" /></a>

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
<a href="http://www.youtube.com/watch?feature=player_embedded&v=6o1-sQRNqcA
" target="_blank"><img src="http://img.youtube.com/vi/6o1-sQRNqcA/0.jpg" 
alt="DLS - Creating a 4-bit Register "
width="640" height="480" border="0" /></a>

http://dls.makingartstudios.com/sandbox/ - DLS: The Sandbox  
![dls-sandbox-screenshot](https://pbs.twimg.com/media/DBaFwOKWAAEq0mp.jpg:large)

## MAME

https://github.com/mamedev/mame MAME - Multiple Arcade Machine Emulator
[Try MAME in Browser!](http://fos.textfiles.com/dfjustin/pacman/pacman/)  
![mame-screenshot](https://raw.githubusercontent.com/mamedev/www.mamedev.org/d8d716dbb63919a11964b5d47b9b7f6cfa006b56/bgfx/Raiden.png)

## Blackshift

https://blackshift.itch.io/blackshift - Blackshift is a grid-based, space-themed
action puzzle game which isn't afraid of complexity — think Chip's Challenge on
crack.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=PUl8612Y-ds" 
target="_blank"><img src="http://img.youtube.com/vi/PUl8612Y-ds/0.jpg" 
alt="Blackshift Trailer, May 2016"
width="640" height="480" border="0" /></a>

## Real-Time Polygonal-Light Shading with Linearly Transformed Cosines

https://eheitzresearch.wordpress.com/415-2/ - Real-Time Polygonal-Light Shading
with Linearly Transformed Cosines, Eric Heitz, Jonathan Dupuy, Stephen Hill and
David Neubelt, ACM SIGGRAPH 2016

<a href="http://www.youtube.com/watch?feature=player_embedded&v=ZLRgEN7AQgM" 
target="_blank"><img src="http://img.youtube.com/vi/ZLRgEN7AQgM/0.jpg" 
alt="Real-Time Polygonal-Light Shading with Linearly Transformed Cosines"
width="640" height="480" border="0" /></a>

## Dead Venture

http://www.dogbytegames.com/dead_venture.html - Dead Venture is a new Drive 'N
Gun game where you help a handful of survivals reach the safe haven: a military
base on a far island.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=CgMr1g12yXw" 
target="_blank"><img src="http://img.youtube.com/vi/CgMr1g12yXw/0.jpg" 
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
![EtherealEngine screenshot](https://user-images.githubusercontent.com/1499411/29488403-ff3c3df6-8512-11e7-869f-32a783530cc3.png)

## Go Rally

http://gorallygame.com/ - Go Rally is top-down rally game with a career mode,
multiplayer time challenges, and a track creator.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=ckbkQsB6RVY" 
target="_blank"><img src="http://img.youtube.com/vi/ckbkQsB6RVY/0.jpg" 
alt="Go Rally"
width="640" height="480" border="0" /></a>

## vg-renderer

https://github.com/jdryg/vg-renderer#vg-renderer - A vector graphics renderer
for bgfx, based on ideas from both NanoVG and ImDrawList (Dear ImGUI)  
![vg-renderer](https://raw.githubusercontent.com/jdryg/vg-renderer/master/img/vgrenderer_tiger.png)

## Zombie Safari

http://www.dogbytegames.com/zombie_safari.html - Do what you please in this
Open-World Offroad Driving game: explore massive landscapes, complete challenges,
smash zombies, find secret locations, unlock and upgrade cars and weapons, it's
up to you!

<a href="http://www.youtube.com/watch?feature=player_embedded&v=LSiH0lRkw8g" 
target="_blank"><img src="http://img.youtube.com/vi/LSiH0lRkw8g/0.jpg" 
alt="Zombie Safari - Official Gameplay Trailer (Android)"
width="640" height="480" border="0" /></a>

## Smith and Winston

http://www.smithandwinston.com/ - Smith and Winston is an exploration twin stick
shooter for PC, PS4 & XBoxOne arriving in late 2018. Smith and Winston features
a massively destructable voxel world, rapid twin stick combat, physics puzzles
and Metroid style discovery.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Mr_L7KuiByU" 
target="_blank"><img src="http://img.youtube.com/vi/Mr_L7KuiByU/0.jpg" 
alt="Smith and Winston: Gameplay Video"
width="640" height="480" border="0" /></a>

## Football Manager 2018

http://www.footballmanager.com/ - Football Manager 2018 is a 2017 football
management simulation video game developed by Sports Interactive and published
by Sega.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=1Woak1Bl_KI" 
target="_blank"><img src="http://img.youtube.com/vi/1Woak1Bl_KI/0.jpg" 
alt="Match Engine | Football Manager 2018"
width="640" height="480" border="0" /></a>

## WonderWorlds

http://wonderworlds.me/ - WonderWorlds is a place to play thousands
of user-created levels and stories, make your own using the extensive in-game
tools and share them with whomever you want.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=nY8y_dFolKo" 
target="_blank"><img src="http://img.youtube.com/vi/nY8y_dFolKo/0.jpg" 
alt="WonderWorlds"
width="640" height="480" border="0" /></a>

## two-io / mud

https://hugoam.github.io/two-io/ - an all-purpose c++ app prototyping library,
focused towards live graphical apps and games.

![mud](https://raw.githubusercontent.com/hugoam/mud-io/master/media/14_live_gfx.png)

## Talking Tom Pool

https://outfit7.com/apps/talking-tom-pool/ - "Sling and match” puzzle game for
mobile devices.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=eNSI45zDEo0" 
target="_blank"><img src="http://img.youtube.com/vi/eNSI45zDEo0/0.jpg" 
alt="Talking Tom Pool"
width="640" height="480" border="0" /></a>

## GPlayEngine

https://github.com/fredakilla/GPlayEngine#gplayengine - GPlayEngine is C++ 
cross-platform game engine for creating 2D/3D games based on the GamePlay 3D 
engine v3.0.

![](https://camo.githubusercontent.com/d89a364fb306f208ca14a58267c8303f60f0f0cf/68747470733a2f2f692e696d6775722e636f6d2f306569395932382e706e67)

## Off The Road

http://www.dogbytegames.com/off_the_road.html - Sandbox off-road driving
simulator.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=IUmxqAWdXvk" 
target="_blank"><img src="http://img.youtube.com/vi/IUmxqAWdXvk/0.jpg" 
alt="Off The Road"
width="640" height="480" border="0" /></a>

## Coal Burnout

https://beardsvibe.com/ - Multiplayer PVP rhythm game.

![coal-burnout](https://beardsvibe.com/scr/0l.png)

## My Talking Tom 2

https://outfit7.com/apps/my-talking-tom-2/ - Many mini games for mobile devices.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=I0U7EQKKDjw" 
target="_blank"><img src="http://img.youtube.com/vi/I0U7EQKKDjw/0.jpg" 
alt="My Talking Tom 2"
width="640" height="480" border="0" /></a>

## NeoAxis Engine

https://www.neoaxis.com/ - Versatile 3D project development environment.

![neoaxis-engine](https://www.neoaxis.com/files/NeoAxisEngine04.jpg)

## xatlas

https://github.com/jpcy/xatlas#xatlas - Mesh parameterization library 

![xatlas](https://user-images.githubusercontent.com/3744372/43034066-53a62dee-8d18-11e8-9767-0b38ed3fa2d3.png)

## Heroes of Hammerwatch

https://store.steampowered.com/app/677120/Heroes_of_Hammerwatch/ Heroes of Hammerwatch
is a rogue-lite action-adventure game set in the same universe as Hammerwatch.
Encounter endless hordes of enemies, traps, puzzles, secrets and lots of loot,
as you battle your way through procedurally generated levels to reach the top
of the Forsaken Spire.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=uTIVDKdNvms" 
target="_blank"><img src="http://img.youtube.com/vi/uTIVDKdNvms/0.jpg" 
alt="Heroes of Hammerwatch"
width="640" height="480" border="0" /></a>

## Babylon Native

Build cross-platform native applications with the power of the Babylon.js
JavaScript framework.

[Babylon Native](https://github.com/BabylonJS/BabylonNative#babylon-native)

## Nira

Instantly load and view assets on any device. All you need is a web browser.

[Nira](https://nira.app/)  
[SIGGRAPH 2019: Project Nira: Instant Interactive Real-Time Access to Multi-Gigabyte Sized 3D Assets on Any Device](https://s2019.siggraph.org/presentation/?sess=sess104&id=real_130#038;id=real_130)

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Gz9weuemhDA&t=3350" 
target="_blank"><img src="http://img.youtube.com/vi/Gz9weuemhDA/0.jpg" 
alt="Heroes of Hammerwatch"
width="640" height="480" border="0" /></a>

## openblack

An open source reimplementation of the game Black & White (2001).

[OpenBlack](https://github.com/openblack/openblack#openblack)

![openblack](https://user-images.githubusercontent.com/1388267/67631321-93c85380-f88c-11e9-9103-804807844af2.png)

## Cluster

Implementation of Clustered Shading and Physically Based Rendering with the bgfx rendering library.

[Cluster](https://github.com/pezcode/Cluster#cluster)

![cluster](https://raw.githubusercontent.com/pezcode/Cluster/master/images/sponza.jpg)

## NIMBY Rails

NIMBY Rails is a management and design sandbox game for railways you build in the real world.

[NIMBY Rails](https://store.steampowered.com/app/1134710/NIMBY_Rails/)

![NIMBY Rails](https://user-images.githubusercontent.com/28320/78472283-03d5e200-7727-11ea-8bd4-db8754f52dc3.jpg)

## Minecraft

https://www.minecraft.net/zh-hant/attribution/

![home-hero-1200x600](https://user-images.githubusercontent.com/814772/79185288-57050000-7dcb-11ea-87b4-2126fcd1545b.jpg)


## FFNx

Next generation driver for Final Fantasy VII and Final Fantasy VIII
(with native Steam 2013 release support!)

[FFNx](https://github.com/julianxhokaxhiu/FFNx#ffnx)

![FFVIII](https://raw.githubusercontent.com/julianxhokaxhiu/FFNx/master/.screens/ff8.png)


## Shadow Gangs

Shadow Gangs is an arcade style ninja action game.

https://www.microsoft.com/en-gb/p/shadow-gangs/9n6hkcr65qdq

![Shadow Gangs](https://user-images.githubusercontent.com/814772/94508248-64ba1080-01c6-11eb-800f-47dc374ef054.jpeg)

## Growtopia

Growtopia is a free-to-play sandbox MMO game with almost endless possibilities
for world creation, customization and having fun with your friends. Enjoy
thousands of items, challenges and events.

https://growtopiagame.com/

![growtopia](https://s3.eu-west-1.amazonaws.com/cdn.growtopiagame.com/website/resources/assets/images/grow_header.jpg)

## Galaxy Trucker

Digital implementation of tabletop spaceship building in real-time or turn-based mode,
then surviving space adventures, with AI opponents, multiplayer, achievements
and solo campaign.

https://galaxytrucker.com/

![Galaxy Trucker](https://press.galaxytrucker.com/images/GTAT_junk.png)

## Through the Ages

The card tabletop deep strategy game in your devices. Lead your civilization from pyramids
to space flights. Challenges, achievements, skilled AIs and online multiplayer.

https://throughtheages.com/

![Through the Ages](https://press.throughtheages.com/images/tta01.png)

## Codenames

One of the best party game. Two rival spymasters know the secret identities of 25 agents.
Their teammates know the agents only by their codenames. Simple to explain,
easy to understand, challenging gameplay.

https://codenamesgame.com/

![Codenames](https://codenamesgame.com/img/game-features-img-1.jpg)

## PeakFinder

PeakFinder shows the names of all mountains and peaks with a 360° panorama display.
More than 850'000 peaks - from Mount Everest to the little hill around the corner.

https://www.peakfinder.org/

![PeakFinder](https://pfweb-c125.kxcdn.com/images/mobile/cards//en/cameramode.jpg)

## Ember Sword

Ember Sword is a free to play MMORPG running directly in your browser and is
being developed and published by Bright Star Studios.

https://embersword.com

![Ember-Sword-ConceptArt5](https://user-images.githubusercontent.com/814772/120714133-a860ca80-c477-11eb-8680-f5a948dfd050.png)

## Off The Road Unleashed

Off The Road Unleashed is a sandbox driving game for the Nintendo Switch.  
If you see a vehicle you bet you can hop into it! Pilot big rigs, helicopters, boats, airplanes or even trains. Sand dunes, frozen plains, mountains to climb and conquer.

https://www.nintendo.com/games/detail/off-the-road-unleashed-switch/

<a href="http://www.youtube.com/watch?feature=player_embedded&v=cwDR0Wj3LO4" 
target="_blank"><img src="http://img.youtube.com/vi/cwDR0Wj3LO4/0.jpg" 
alt="Off The Road Unleashed"
width="640" height="480" border="0" /></a>

[License (BSD 2-clause)](https://bkaradzic.github.io/bgfx/license.html)
-----------------------------------------------------------------------

<a href="http://opensource.org/licenses/BSD-2-Clause" target="_blank">
<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">
</a>

	Copyright 2010-2021 Branimir Karadzic
	
	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	
	   1. Redistributions of source code must retain the above copyright notice, this
	      list of conditions and the following disclaimer.
	
	   2. Redistributions in binary form must reproduce the above copyright notice,
	      this list of conditions and the following disclaimer in the documentation
	      and/or other materials provided with the distribution.
	
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
	OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
	OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
	OF THE POSSIBILITY OF SUCH DAMAGE.
