#
# Copyright 2011-2013 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

all:
	premake4 --file=premake/premake4.lua vs2008
	premake4 --file=premake/premake4.lua vs2010
	premake4 --file=premake/premake4.lua vs2012
	premake4 --file=premake/premake4.lua --gcc=android-arm gmake
	premake4 --file=premake/premake4.lua --gcc=android-mips gmake
	premake4 --file=premake/premake4.lua --gcc=android-x86 gmake
	premake4 --file=premake/premake4.lua --gcc=nacl gmake
	premake4 --file=premake/premake4.lua --gcc=nacl-arm gmake
	premake4 --file=premake/premake4.lua --gcc=pnacl gmake
	premake4 --file=premake/premake4.lua --gcc=mingw gmake
	premake4 --file=premake/premake4.lua --gcc=linux-gcc gmake
	premake4 --file=premake/premake4.lua --gcc=osx gmake
	premake4 --file=premake/premake4.lua --gcc=ios-arm gmake
	premake4 --file=premake/premake4.lua --gcc=ios-simulator gmake
	premake4 --file=premake/premake4.lua xcode4

.build/projects/gmake-android-arm:
	premake4 --file=premake/premake4.lua --gcc=android-arm gmake
android-arm-debug: .build/projects/gmake-android-arm
	make -R -C .build/projects/gmake-android-arm config=debug
android-arm-release: .build/projects/gmake-android-arm
	make -R -C .build/projects/gmake-android-arm config=release
android-arm: android-arm-debug android-arm-release

.build/projects/gmake-android-mips:
	premake4 --file=premake/premake4.lua --gcc=android-mips gmake
android-mips-debug: .build/projects/gmake-android-mips
	make -R -C .build/projects/gmake-android-mips config=debug
android-mips-release: .build/projects/gmake-android-mips
	make -R -C .build/projects/gmake-android-mips config=release
android-mips: android-mips-debug android-mips-release

.build/projects/gmake-android-x86:
	premake4 --file=premake/premake4.lua --gcc=android-x86 gmake
android-x86-debug: .build/projects/gmake-android-x86
	make -R -C .build/projects/gmake-android-x86 config=debug
android-x86-release: .build/projects/gmake-android-x86
	make -R -C .build/projects/gmake-android-x86 config=release
android-x86: android-x86-debug android-x86-release

.build/projects/gmake-linux:
	premake4 --file=premake/premake4.lua --gcc=linux-gcc gmake
linux-debug32: .build/projects/gmake-linux
	make -R -C .build/projects/gmake-linux config=debug32
linux-release32: .build/projects/gmake-linux
	make -R -C .build/projects/gmake-linux config=release32
linux-debug64: .build/projects/gmake-linux
	make -R -C .build/projects/gmake-linux config=debug64
linux-release64: .build/projects/gmake-linux
	make -R -C .build/projects/gmake-linux config=release64
linux: linux-debug32 linux-release32 linux-debug64 linux-release64

.build/projects/gmake-mingw:
	premake4 --file=premake/premake4.lua --gcc=mingw gmake
mingw-debug32: .build/projects/gmake-mingw
	make -R -C .build/projects/gmake-mingw config=debug32
mingw-release32: .build/projects/gmake-mingw
	make -R -C .build/projects/gmake-mingw config=release32
mingw-debug64: .build/projects/gmake-mingw
	make -R -C .build/projects/gmake-mingw config=debug64
mingw-release64: .build/projects/gmake-mingw
	make -R -C .build/projects/gmake-mingw config=release64
mingw: mingw-debug32 mingw-release32 mingw-debug64 mingw-release64

.build/projects/vs2008:
	premake4 --file=premake/premake4.lua vs2008
vs2008-debug32:
	devenv .build/projects/vs2008/bgfx.sln /Build "Debug|Win32"
vs2008-release32:
	devenv .build/projects/vs2008/bgfx.sln /Build "Release|Win32"
vs2008-debug64:
	devenv .build/projects/vs2008/bgfx.sln /Build "Debug|x64"
vs2008-release64:
	devenv .build/projects/vs2008/bgfx.sln /Build "Release|x64"
vs2008: vs2008-debug32 vs2008-release32 vs2008-debug64 vs2008-release64

.build/projects/vs2010:
	premake4 --file=premake/premake4.lua vs2010

.build/projects/vs2012:
	premake4 --file=premake/premake4.lua vs2012

.build/projects/gmake-nacl:
	premake4 --file=premake/premake4.lua --gcc=nacl gmake
nacl-debug32: .build/projects/gmake-nacl
	make -R -C .build/projects/gmake-nacl config=debug32
nacl-release32: .build/projects/gmake-nacl
	make -R -C .build/projects/gmake-nacl config=release32
nacl-debug64: .build/projects/gmake-nacl
	make -R -C .build/projects/gmake-nacl config=debug64
nacl-release64: .build/projects/gmake-nacl
	make -R -C .build/projects/gmake-nacl config=release64
nacl: nacl-debug32 nacl-release32 nacl-debug64 nacl-release64

.build/projects/gmake-nacl-arm:
	premake4 --file=premake/premake4.lua --gcc=nacl-arm gmake
nacl-arm-debug: .build/projects/gmake-nacl-arm
	make -R -C .build/projects/gmake-nacl-arm config=debug
nacl-arm-release: .build/projects/gmake-nacl-arm
	make -R -C .build/projects/gmake-nacl-arm config=release
nacl-arm: nacl-arm-debug32 nacl-arm-release32

.build/projects/gmake-pnacl:
	premake4 --file=premake/premake4.lua --gcc=pnacl gmake
pnacl-debug: .build/projects/gmake-pnacl
	make -R -C .build/projects/gmake-pnacl config=debug
pnacl-release: .build/projects/gmake-pnacl
	make -R -C .build/projects/gmake-pnacl config=release
pnacl: pnacl-debug pnacl-release

.build/projects/gmake-osx:
	premake4 --file=premake/premake4.lua --gcc=osx gmake
osx-debug32: .build/projects/gmake-osx
	make -C .build/projects/gmake-osx config=debug32
osx-release32: .build/projects/gmake-osx
	make -C .build/projects/gmake-osx config=release32
osx-debug64: .build/projects/gmake-osx
	make -C .build/projects/gmake-osx config=debug64
osx-release64: .build/projects/gmake-osx
	make -C .build/projects/gmake-osx config=release64
osx: osx-debug32 osx-release32 osx-debug64 osx-release64

.build/projects/gmake-ios-arm:
	premake4 --file=premake/premake4.lua --gcc=ios-arm gmake
ios-arm-debug: .build/projects/gmake-ios-arm
	make -R -C .build/projects/gmake-ios-arm config=debug
ios-arm-release: .build/projects/gmake-ios-arm
	make -R -C .build/projects/gmake-ios-arm config=release
ios-arm: ios-arm-debug ios-arm-release

.build/projects/gmake-ios-simulator:
	premake4 --file=premake/premake4.lua --gcc=ios-simulator gmake
ios-simulator-debug: .build/projects/gmake-ios-simulator
	make -R -C .build/projects/gmake-ios-simulator config=debug
ios-simulator-release: .build/projects/gmake-ios-simulator
	make -R -C .build/projects/gmake-ios-simulator config=release
ios-simulator: ios-simulator-debug ios-simulator-release

rebuild-shaders:
	make -R -C examples rebuild

analyze:
	cppcheck src/
	cppcheck examples/

docs:
	doxygen premake/bgfx.doxygen
	markdown README.md > .build/docs/readme.html

clean:
	@echo Cleaning...
	-@rm -rf .build
