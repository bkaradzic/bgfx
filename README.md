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

[![GitHub Actions](https://github.com/bkaradzic/bgfx/actions/workflows/main.yml/badge.svg)](https://github.com/bkaradzic/bgfx/actions)
[![License](https://img.shields.io/badge/license-BSD--2%20clause-blue.svg)](https://bkaradzic.github.io/bgfx/license.html)
[![Join the chat at https://discord.gg/9eMbv7J](https://img.shields.io/discord/712512073522872352?color=%237289DA&label=bgfx&logo=discord&logoColor=white)](https://discord.gg/9eMbv7J)

 * [GitHub Discussions](https://github.com/bkaradzic/bgfx/discussions)
 * [Discord Chat](https://discord.gg/g99upRc9pf)
 * [GitHub Actions](https://github.com/bkaradzic/bgfx/actions)

[What is it?](https://bkaradzic.github.io/bgfx/overview.html)
-------------------------------------------------------------

Cross-platform, graphics API agnostic, "Bring Your Own Engine/Framework" style
rendering library.

Supported rendering backends:

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

Supported platforms:

 * Android (14+)
 * iOS/iPadOS/tvOS (16.0+)
 * Linux
 * macOS (13.0+)
 * PlayStation 4
 * RaspberryPi
 * UWP (Universal Windows, Xbox One)
 * Wasm/Emscripten
 * Windows (7+)

Supported compilers:

 * Clang 11 and above
 * GCC 8 and above
 * VS2019 and above
 * Apple clang 12 and above

Languages:

 * [C/C++ API documentation](https://bkaradzic.github.io/bgfx/bgfx.html)
 * [Beef API bindings](https://github.com/bkaradzic/bgfx/tree/master/bindings/bf)
 * [C# language API bindings #1](https://github.com/bkaradzic/bgfx/tree/master/bindings/cs)
 * [D language API bindings](https://github.com/BindBC/bindbc-bgfx)
 * [Go language API bindings](https://github.com/james4k/go-bgfx)
 * [Haskell language API bindings](https://github.com/haskell-game/bgfx)
 * [Lightweight Java Game Library 3 bindings](https://github.com/LWJGL/lwjgl3)
 * [Lua language API bindings](https://github.com/cloudwu/lua-bgfx)
 * [Nim language API bindings](https://github.com/Halsys/nim-bgfx)
 * [Pascal language API bindings](https://github.com/Akira13641/PasBGFX)
 * [Python language API bindings #1](https://github.com/fbertola/bgfx-python#-----bgfx-python--)
 * [Python language API bindings #2](https://github.com/jnadro/pybgfx#pybgfx)
 * [Rust language API bindings (new)](https://github.com/emoon/bgfx-rs)
 * [Swift language API bindings](https://github.com/stuartcarnie/SwiftBGFX)
 * [Zig language API bindings](https://github.com/bkaradzic/bgfx/tree/master/bindings/zig)

Who is using it? [#madewithbgfx](https://twitter.com/search?q=%23madewithbgfx&src=typed_query&f=live)
-----------------------------------------------------------------------------------------------------

## AirMech

https://www.carbongames.com/airmech-strike - AirMech is a free-to-play
futuristic action real-time strategy video game developed and published by
Carbon Games.

![AirMech screenshot](https://www.mobygames.com/images/shots/l/830630-airmech-playstation-4-screenshot-blue-bar-on-your-mech-indicates.jpg)

## cmftStudio

https://github.com/dariomanesku/cmftStudio - cmftStudio - Cubemap filtering
tool.

![cmftStudio screenshot](https://github.com/dariomanesku/cmftStudio/raw/master/screenshots/cmftStudio_small.jpg)

## Crown

https://github.com/dbartolini/crown - Crown is a general purpose data-driven
game engine, written from scratch with a minimalistic and data-oriented design
philosophy in mind.

![Crown screenshot](https://raw.githubusercontent.com/dbartolini/crown/master/docs/shots/level-editor.png)

## Offroad Legends 2

http://www.dogbytegames.com/ - Dogbyte Games is an indie mobile developer studio
focusing on racing games.

![Offroad Legends 2](http://www.dogbytegames.com/bgfx/offroadlegends2_bgfx_ipad2.jpg)

## Torque6

https://github.com/andr3wmac/Torque6 - Torque 6 is an MIT licensed 3D engine
loosely based on Torque2D. Being neither Torque2D or Torque3D it is the 6th
derivative of the original Torque Engine.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=p4LTM_QGK34" 
target="_blank"><img src="http://img.youtube.com/vi/p4LTM_QGK34/0.jpg" 
alt="Torque 6 Material Editor" width="640" height="480" border="0" /></a>

## Kepler Orbits

https://github.com/podgorskiy/KeplerOrbits - KeplerOrbits - Tool that calculates
positions of celestial bodies using their orbital elements.

## CETech

https://github.com/cyberegoorg/cetech - CETech is a data-driven game engine and
toolbox inspired by Bitsquid/Stingray engine.

![CETech screenshot](https://github.com/cyberegoorg/cetech/raw/master/docs/img/prototyp.png)

## ioquake3

https://github.com/jpcy/ioq3-renderer-bgfx - A renderer for ioquake3 written in
C++ and using bgfx to support multiple rendering APIs.

![ioq3-renderer-bgfx screenshot](https://camo.githubusercontent.com/052aa40c05120e56306294d3a1bb5f99f97de8c8/687474703a2f2f692e696d6775722e636f6d2f64364f6856594b2e6a7067)

## DLS

http://makingartstudios.itch.io/dls - DLS, the digital logic simulator game.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=6o1-sQRNqcA
" target="_blank"><img src="http://img.youtube.com/vi/6o1-sQRNqcA/0.jpg" 
alt="DLS - Creating a 4-bit Register "
width="640" height="480" border="0" /></a>

http://dls.makingartstudios.com/sandbox/ - DLS: The Sandbox.

![DLS: The Sandbox screenshot](https://pbs.twimg.com/media/DBaFwOKWAAEq0mp.jpg:large)

## MAME

https://github.com/mamedev/mame - MAME - Multiple Arcade Machine Emulator.

![MAME screenshot](https://raw.githubusercontent.com/mamedev/www.mamedev.org/d8d716dbb63919a11964b5d47b9b7f6cfa006b56/bgfx/Raiden.png)

## Blackshift

https://blackshift.itch.io/blackshift - Blackshift is a grid-based, space-themed
action puzzle game which isn't afraid of complexity - think Chip's Challenge on
crack.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=PUl8612Y-ds" 
target="_blank"><img src="http://img.youtube.com/vi/PUl8612Y-ds/0.jpg" 
alt="Blackshift Trailer, May 2016"
width="640" height="480" border="0" /></a>

## Real-Time Polygonal-Light Shading with Linearly Transformed Cosines

https://eheitzresearch.wordpress.com/415-2/ - Real-Time Polygonal-Light Shading
with Linearly Transformed Cosines, Eric Heitz, Jonathan Dupuy, Stephen Hill and
David Neubelt, ACM SIGGRAPH 2016.

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

https://github.com/degenerated1123/REGoth - REGoth is an open-source
reimplementation of the zEngine, used by the game "Gothic" and "Gothic II".

<a href="http://www.youtube.com/watch?feature=player_embedded&v=8bLAGttYYpY
" target="_blank"><img src="http://img.youtube.com/vi/8bLAGttYYpY/0.jpg" 
alt="REGoth Engine"
width="640" height="480" border="0" /></a>

## Ethereal Engine

https://github.com/volcoma/EtherealEngine - EtherealEngine is a C++ game engine
and WYSIWYG dditor.

![EtherealEngine screenshot](https://user-images.githubusercontent.com/1499411/29488403-ff3c3df6-8512-11e7-869f-32a783530cc3.png)

## Go Rally

http://gorallygame.com/ - Go Rally is top-down rally game with a career mode,
multiplayer time challenges, and a track creator.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=ckbkQsB6RVY" 
target="_blank"><img src="http://img.youtube.com/vi/ckbkQsB6RVY/0.jpg" 
alt="Go Rally"
width="640" height="480" border="0" /></a>

## vg-renderer

https://github.com/jdryg/vg-renderer#vg-renderer - vg-renderer is a vector
graphics renderer for bgfx, based on ideas from both NanoVG and ImDrawList (Dear
ImGUI).

![vg-renderer screenshot](https://raw.githubusercontent.com/jdryg/vg-renderer/master/img/vgrenderer_tiger.png)

## Zombie Safari

http://www.dogbytegames.com/zombie_safari.html - Do what you please in this
open-world offroad driving game: explore massive landscapes, complete
challenges, smash zombies, find secret locations, unlock and upgrade cars and
weapons, it's up to you!

<a href="http://www.youtube.com/watch?feature=player_embedded&v=LSiH0lRkw8g" 
target="_blank"><img src="http://img.youtube.com/vi/LSiH0lRkw8g/0.jpg" 
alt="Zombie Safari - Official Gameplay Trailer (Android)"
width="640" height="480" border="0" /></a>

## Smith and Winston

http://www.smithandwinston.com/ - Smith and Winston is an exploration twin stick
shooter for PC, PS4 & XBoxOne arriving in late 2018. Smith and Winston features
a massively destructable voxel world, rapid twin stick combat, physics puzzles
and Metroid-style discovery.

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

http://wonderworlds.me/ - WonderWorlds is a place to play thousands of
user-created levels and stories, make your own using the extensive in-game tools
and share them with whomever you want.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=nY8y_dFolKo" 
target="_blank"><img src="http://img.youtube.com/vi/nY8y_dFolKo/0.jpg" 
alt="WonderWorlds"
width="640" height="480" border="0" /></a>

## two-io / mud

https://hugoam.github.io/two-io/ - An all-purpose c++ app prototyping library,
focused towards live graphical apps and games.

![two-io / mud screenshot](https://raw.githubusercontent.com/hugoam/mud-io/master/media/14_live_gfx.png)

## Talking Tom Pool

https://outfit7.com/apps/talking-tom-pool/ - A "sling and match" puzzle game for
mobile devices.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=eNSI45zDEo0" 
target="_blank"><img src="http://img.youtube.com/vi/eNSI45zDEo0/0.jpg" 
alt="Talking Tom Pool"
width="640" height="480" border="0" /></a>

## GPlayEngine

https://github.com/fredakilla/GPlayEngine#gplayengine - GPlayEngine is a C++
cross-platform game engine for creating 2D/3D games based on the GamePlay 3D
engine v3.0.

![GPlayEngine screenshot](https://camo.githubusercontent.com/d89a364fb306f208ca14a58267c8303f60f0f0cf/68747470733a2f2f692e696d6775722e636f6d2f306569395932382e706e67)

## Off The Road

http://www.dogbytegames.com/off_the_road.html - A sandbox off-road driving
simulator.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=RgnIReFkbyU" 
target="_blank"><img src="http://img.youtube.com/vi/RgnIReFkbyU/hq720.jpg" 
alt="Off The Road"
width="640" height="360" border="0" /></a>

## Coal Burnout

https://beardsvibe.com/ - A multiplayer PVP rhythm game.

![Coal Burnout screenshot](https://beardsvibe.com/scr/0l.png)

## My Talking Tom 2

https://outfit7.com/apps/my-talking-tom-2/ - Many mini games for mobile devices.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=I0U7EQKKDjw" 
target="_blank"><img src="http://img.youtube.com/vi/I0U7EQKKDjw/0.jpg" 
alt="My Talking Tom 2"
width="640" height="480" border="0" /></a>

## NeoAxis Engine

https://www.neoaxis.com/ - Versatile 3D project development environment.

![NeoAxis Engine screenshot](https://www.neoaxis.com/files/NeoAxisEngine04.jpg)

## xatlas

https://github.com/jpcy/xatlas#xatlas - Mesh parameterization library.

![xatlas screenshot](https://user-images.githubusercontent.com/3744372/43034066-53a62dee-8d18-11e8-9767-0b38ed3fa2d3.png)

## Heroes of Hammerwatch

https://store.steampowered.com/app/677120/Heroes_of_Hammerwatch/ - Heroes of
Hammerwatch is a rogue-lite action-adventure game set in the same universe as
Hammerwatch. Encounter endless hordes of enemies, traps, puzzles, secrets and
lots of loot, as you battle your way through procedurally generated levels to
reach the top of the Forsaken Spire.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=uTIVDKdNvms" 
target="_blank"><img src="http://img.youtube.com/vi/uTIVDKdNvms/0.jpg" 
alt="Heroes of Hammerwatch"
width="640" height="480" border="0" /></a>

## Babylon Native

https://github.com/BabylonJS/BabylonNative#babylon-native - Build cross-platform
native applications with the power of the Babylon.js JavaScript framework.

## Nira

https://nira.app/ - Instantly load and view assets on any device. All you need
is a web browser.

SIGGRAPH 2019: Project Nira: Instant Interactive Real-Time Access to
Multi-Gigabyte Sized 3D Assets on Any Device:
https://s2019.siggraph.org/presentation/?sess=sess104&id=real_130#038;id=real_130

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Gz9weuemhDA&t=3350" 
target="_blank"><img src="http://img.youtube.com/vi/Gz9weuemhDA/0.jpg" 
alt="Heroes of Hammerwatch"
width="640" height="480" border="0" /></a>

## openblack

https://github.com/openblack/openblack#openblack - An open-source
reimplementation of the game Black & White (2001).

![openblack screenshot](https://user-images.githubusercontent.com/32263167/184559293-56cfc6a7-a7da-4876-8fce-434ba8827eae.png)

## Cluster

https://github.com/pezcode/Cluster#cluster - Implementation of Clustered Shading
and Physically Based Rendering with the bgfx rendering library.

![Cluster screenshot](https://raw.githubusercontent.com/pezcode/Cluster/master/images/sponza.jpg)

## NIMBY Rails

https://store.steampowered.com/app/1134710/NIMBY_Rails/ - NIMBY Rails is a
management and design sandbox game for railways you build in the real world.

![NIMBY Rails screenshot](https://user-images.githubusercontent.com/28320/78472283-03d5e200-7727-11ea-8bd4-db8754f52dc3.jpg)

## Minecraft

https://www.minecraft.net/zh-hant/attribution/

![Minecraft screenshot](https://user-images.githubusercontent.com/814772/79185288-57050000-7dcb-11ea-87b4-2126fcd1545b.jpg)


## FFNx

https://github.com/julianxhokaxhiu/FFNx#ffnx - Next generation driver for Final
Fantasy VII and Final Fantasy VIII (with native Steam 2013 release support!)

![FFVIII screenshot](https://raw.githubusercontent.com/julianxhokaxhiu/FFNx/master/.screens/ff8.png)


## Shadow Gangs

https://www.microsoft.com/en-gb/p/shadow-gangs/9n6hkcr65qdq - Shadow Gangs is an
arcade style ninja action game.

![Shadow Gangs screenshot](https://user-images.githubusercontent.com/814772/94508248-64ba1080-01c6-11eb-800f-47dc374ef054.jpeg)

## Growtopia

https://growtopiagame.com/ - Growtopia is a free-to-play sandbox MMO game with
almost endless possibilities for world creation, customization and having fun
with your friends. Enjoy thousands of items, challenges and events.

![Growtopia screenshot](https://s3.eu-west-1.amazonaws.com/cdn.growtopiagame.com/website/resources/assets/images/grow_header.jpg)

## Galaxy Trucker

https://galaxytrucker.com/ - Digital implementation of tabletop spaceship
building in real-time or turn-based mode, then surviving space adventures, with
AI opponents, multiplayer, achievements and solo campaign.

![Galaxy Trucker screenshot](https://press.galaxytrucker.com/images/GTAT_junk.png)

## Through the Ages

https://throughtheages.com/ - The card tabletop deep strategy game in your
devices. Lead your civilization from pyramids to space flights. Challenges,
achievements, skilled AIs and online multiplayer.

![Through the Ages screenshot](https://press.throughtheages.com/images/tta01.png)

## Codenames

https://codenamesgame.com/ - One of the best party games. Two rival spymasters
know the secret identities of 25 agents. Their teammates know the agents only by
their codenames. Simple to explain, easy to understand, challenging gameplay.

![Codenames screenshot](https://codenamesgame.com/img/game-features-img-1.jpg)

## PeakFinder

https://www.peakfinder.org/ - PeakFinder shows the names of all mountains and
peaks with a 360° panorama display. More than 850'000 peaks - from Mount Everest
to the little hill around the corner.

![PeakFinder screenshot](https://pfweb-c125.kxcdn.com/videos/mobile/manual/v4/light/en/peakfinder-trecime.jpg)

## Ember Sword

https://embersword.com - Ember Sword is a free to play MMORPG running directly
in your browser and is being developed and published by Bright Star Studios.

![Ember Sword screenshot](https://user-images.githubusercontent.com/814772/120714133-a860ca80-c477-11eb-8680-f5a948dfd050.png)

## Off The Road Unleashed

https://www.nintendo.com/games/detail/off-the-road-unleashed-switch/ - Off The
Road Unleashed is a sandbox driving game for the Nintendo Switch. If you see a
vehicle you bet you can hop into it! Pilot big rigs, helicopters, boats,
airplanes or even trains. Sand dunes, frozen plains, mountains to climb and
conquer.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=cwDR0Wj3LO4" 
target="_blank"><img src="http://img.youtube.com/vi/cwDR0Wj3LO4/0.jpg" 
alt="Off The Road Unleashed"
width="640" height="480" border="0" /></a>

## Guild Wars 2

https://www.guildwars2.com/ - Guild Wars 2 is an online role-playing game with
fast-paced action combat, a rich and detailed universe of stories, awe-inspiring
landscapes to explore, two challenging player vs. player modes—and no
subscription fees!

![Guild Wars 2 screenshot](https://d3b4yo2b5lbfy.cloudfront.net/wp-content/uploads/2017/07/1a684WvW_ArmorT3.jpg)

## Griftlands

https://klei.com/games/griftlands - Griftlands is a roguelike deck-building game
with role-playing story elements in a science fiction setting, developed and
published by Klei Entertainment.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=ufl14_Ne5Lg" 
target="_blank"><img src="http://img.youtube.com/vi/ufl14_Ne5Lg/0.jpg" 
alt="Griftlands"
width="640" height="480" border="0" /></a>

## HARFANG 3D

https://www.harfang3d.com - HARFANG® 3D is a **BGFX-powered** 3D visualization
framework for C++, Python, Go, and Lua. It comes with a 3D editor, HARFANG
Studio.

![HARFANG Studio screenshot](https://raw.githubusercontent.com/harfang3d/image-storage/main/portfolio/3.2.2/harfang-studio-cyber-city.png)

## Marine Melodies / Resistance

https://www.pouet.net/prod.php?which=91906 - Demoscene musicdisk released at
Evoke 2022 demoparty.

https://github.com/astrofra/demo-marine-melodies

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Ma1-UBa3f2E" 
target="_blank"><img src="http://img.youtube.com/vi/Ma1-UBa3f2E/0.jpg" 
alt="Marine Melodies"
width="640" height="480" border="0" /></a>

## Activeworlds

https://www.activeworlds.com/ - Activeworlds is an online VR platform with rich
multimedia and presentation features. Create your own worlds or build in free
community worlds, hold your own event / meeting or join inworld events!

![Activeworlds screenshot](http://www.activeworlds.com/img/181107-213544_small_enkii.jpg)

## Equilibrium Engine

https://github.com/clibequilibrium/EquilibriumEngine - Equilibrium Engine is a
data-oriented and multi-threaded C11 Game Engine with libraries & shaders
hot-reloading.

![Equilibrium Engine screenshot](https://raw.githubusercontent.com/clibequilibrium/EquilibriumEngine/master/docs/city.png)

## Pinhole Universe

https://festina-lente-productions.com/pinhole-universe/ - Explore a generated
world where you can zoom in on anything, forever.

![Pinhole Universe capsule image](https://festina-lente-productions.com/ext/capsule_small.jpg)

## Unavowed (Nintendo Switch version only)

https://www.nintendo.com/us/store/products/unavowed-switch/ - A demon has possessed you
and used your body to tear a swath of bloodshed through New York. You are now free, but
life as you knew it is over. Your only path forward is joining the Unavowed - an ancient
society dedicated to stopping evil. No matter what the cost.

![Unavowed Title](https://assets.nintendo.com/image/upload/c_limit,f_auto,h_1000,q_auto,w_1700/v1/ncom/en_US/games/switch/u/unavowed-switch/Video/posters/Unavowed_Switch_Trailer_NOA)

## The Excavation of Hob's Barrow (Nintendo Switch version only)

https://www.nintendo.com/us/store/products/the-excavation-of-hobs-barrow-switch/ - A folk
horror narrative-driven adventure. Explore the isolated moors of rural Victorian England
as you uncover the mysteries of Hob's Barrow. The answers lie in the soil...

![The Excavation of Hob's Barrow Title](https://assets.nintendo.com/image/upload/c_limit,f_auto,h_1000,q_auto,w_1700/v1/ncom/en_US/games/switch/t/the-excavation-of-hobs-barrow-switch/Video/posters/The_Excavation_of_Hob_s_Barrow)

## Primordia (Nintendo Switch version only)

https://www.nintendo.com/us/store/products/primordia-switch/ - Life has ceased. Man is
but a myth. And now, even the machines have begun to fail. Lead Horatio Nullbuilt and his
sarcastic sidekick Crispin on a journey through the crumbling world of Primordia, facing
malfunctioning robots, ancient secrets, and an implacable, power-hungry foe.

![Primordia Title](https://assets.nintendo.com/image/upload/c_limit,f_auto,h_1000,q_auto,w_1700/v1/ncom/en_US/games/switch/p/primordia-switch/Video/posters/Primordia_Trailer)

## ProtoTwin

https://prototwin.com - Online industrial simulation software for manufacturing and material handling.

![ProtoTwin - Simulation for Industrial Automation](https://github.com/bkaradzic/bgfx/assets/37254625/7aac600f-2687-468f-8d60-441c45ec14a3)

## WARCANA

WARCANA is a fantasy inspired base defence, RTS game with a deck-building mechanic. 
Face hundreds of thousands of unrelenting monsters in a battle royale between 30 other 
mighty magicians. Build your deck. Prepare your defences. Summon your armies. 
Survive the onslaught.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=UioR5ptCFYU" 
target="_blank"><img src="http://img.youtube.com/vi/UioR5ptCFYU/0.jpg" 
alt="WARCANA Announcement Trailer" width="640" height="480" border="0" /></a>

## DiskBoard

https://www.diskboard.com - DiskBoard is the ultimate tool that can help you measure
the performance and monitor the health of your hardware. All of your devices are
presented in a clean and easy to understand view. The tests offer extensive
customization options, allowing you to simulate various workloads. The intuitive
visuals provide clear insights, benchmark comparisons, and performance guidelines.
Join a community of tech enthusiasts, compare your device's prowess, and witness
your hardware shine!

![Diskboard screenshot](https://www.diskboard.com/assets/diskboard3.png)

## Ant

https://github.com/ejoy/ant - Ant is an open-source game engine focused on mobile platforms. It is implemented
based on Lua, with excellent performance and easy customization.

[Red Frontier Game using Ant Game Engine](https://github.com/ejoy/vaststars)

![RedFrontier](https://github.com/ejoy/vaststars/blob/master/screenshot/startup.jpg)

## Crypt of the NecroDancer

https://braceyourselfgames.com/crypt-of-the-necrodancer/ - Crypt of the NecroDancer
is an award-winning hardcore roguelike rhythm game. Move to the music and deliver
beatdowns to the beat! The game uses bgfx on Windows, macOS, Linux, Nintendo
Switch and PlayStation 4.

![Crypt of the NecroDancer screenshot](https://raw.githubusercontent.com/Marukyu/marukyu.github.io/misc-assets/247080_20240322072858_1.png)

## Tomb4Plus

https://www.github.com/SaracenOne/Tomb4Plus - Tomb4Plus is an open source
reimplementation of the Tomb Raider: The Last Revelation engine. It is an
enhanced fork of the original [Tomb4](https://github.com/Trxyebeep/TOMB4)
reimplementation project which focuses on supporting the Level Editor runtime
and aims for full compatibility with the unofficial binary-patched scripting
extensions used by many custom levels. Tomb4Plus also replaces the original
legacy Direct3D renderer with bgfx.

![Tomb4Plus screenshot](https://raw.githubusercontent.com/SaracenOne/Tomb4Plus/level_editor_v2/.github/images/preview.png)

## Braid, Anniversary Edition

https://play.google.com/store/apps/details?id=com.netflix.NGP.BraidAnniversaryEdition - 
bgfx is used only in Android version of the game.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=U738YZG1k1I" 
target="_blank"><img src="http://img.youtube.com/vi/U738YZG1k1I/0.jpg" 
alt="Braid, Anniversary Edition"
width="640" height="480" border="0" /></a>

## Rotwood

https://store.steampowered.com/app/2015270/Rotwood/ - Rotwood is an upcoming
beat'em up, rogouelike video game developed and published by Klei Entertainment.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=SoTNhVPzmC8" 
target="_blank"><img src="http://img.youtube.com/vi/SoTNhVPzmC8/0.jpg" 
alt="Rotwood"
width="640" height="480" border="0" /></a>

## Cubzh

https://app.cu.bzh/ - Cubzh is a User Generated Social Universe, an online
platform where all items, avatars, games, and experiences are made by users
from the community.

Source: https://github.com/cubzh/cubzh

![Cubzh screenshot](https://camo.githubusercontent.com/154159f42f526cc87357d24419133d99d8996ee2a16513ae5b5d31bd7e06bc5d/68747470733a2f2f6672616d657275736572636f6e74656e742e636f6d2f696d616765732f4957384c7147575239496e696b7542534a6c5a664578647631412e77656270)

## World Of Goo 2

https://store.epicgames.com/en-US/p/world-of-goo-2 - Build bridges, 
grow towers, terraform terrain, and fuel flying machines in 
the stunning followup to the multi-award winning World of Goo.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=q3XVl53Ajsk" 
target="_blank"><img src="http://img.youtube.com/vi/q3XVl53Ajsk/0.jpg" 
alt="World Of Goo 2"
width="640" height="480" border="0" /></a>

[License (BSD 2-clause)](https://bkaradzic.github.io/bgfx/license.html)
-----------------------------------------------------------------------

<a href="http://opensource.org/licenses/BSD-2-Clause" target="_blank">
<img align="right" src="https://opensource.org/wp-content/uploads/2022/10/osi-badge-dark.svg" width="100" height="137">
</a>

	Copyright 2010-2024 Branimir Karadzic
	
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
