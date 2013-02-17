#
# Copyright 2011-2013 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

all:
	premake4 --file=premake/premake4.lua vs2008
	premake4 --file=premake/premake4.lua vs2010
	premake4 --file=premake/premake4.lua --gcc=nacl gmake
	premake4 --file=premake/premake4.lua --gcc=nacl-arm gmake
	premake4 --file=premake/premake4.lua --gcc=pnacl gmake
	premake4 --file=premake/premake4.lua --gcc=mingw gmake
	premake4 --file=premake/premake4.lua --gcc=linux gmake
	premake4 --file=premake/premake4.lua --gcc=emscripten gmake
	premake4 --file=premake/premake4.lua --gcc=osx gmake
	premake4 --file=premake/premake4.lua xcode4
	make -s --no-print-directory -C src

linux-debug32:
	make -R -C .build/projects/gmake-linux config=debug32
linux-release32:
	make -R -C .build/projects/gmake-linux config=release32
linux-debug64:
	make -R -C .build/projects/gmake-linux config=debug64
linux-release64:
	make -R -C .build/projects/gmake-linux config=release64
linux: linux-debug32 linux-release32 linux-debug64 linux-release64

mingw-debug32:
	make -R -C .build/projects/gmake-mingw config=debug32
mingw-release32:
	make -R -C .build/projects/gmake-mingw config=release32
mingw-debug64:
	make -R -C .build/projects/gmake-mingw config=debug64
mingw-release64:
	make -R -C .build/projects/gmake-mingw config=release64
mingw: mingw-debug32 mingw-release32 mingw-debug64 mingw-release64

vs2008-debug32:
	devenv .build/projects/vs2008/bgfx.sln /Build "Debug|Win32"
vs2008-release32:
	devenv .build/projects/vs2008/bgfx.sln /Build "Release|Win32"
vs2008-debug64:
	devenv .build/projects/vs2008/bgfx.sln /Build "Debug|x64"
vs2008-release64:
	devenv .build/projects/vs2008/bgfx.sln /Build "Release|x64"
vs2008: vs2008-debug32 vs2008-release32 vs2008-debug64 vs2008-release64

nacl-debug32:
	make -R -C .build/projects/gmake-nacl config=debug32
nacl-release32:
	make -R -C .build/projects/gmake-nacl config=release32
nacl-debug64:
	make -R -C .build/projects/gmake-nacl config=debug64
nacl-release64:
	make -R -C .build/projects/gmake-nacl config=release64
nacl: nacl-debug32 nacl-release32 nacl-debug64 nacl-release64

nacl-arm-debug32:
	make -R -C .build/projects/gmake-nacl-arm config=debug32
nacl-arm-release32:
	make -R -C .build/projects/gmake-nacl-arm config=release32
nacl-arm: nacl-arm-debug32 nacl-arm-release32

pnacl-debug:
	make -R -C .build/projects/gmake-pnacl config=debug64
pnacl-release:
	make -R -C .build/projects/gmake-pnacl config=release64
pnacl: pnacl-debug pnacl-release

osx-debug32:
	make -C .build/projects/gmake-osx config=debug32
osx-release32:
	make -C .build/projects/gmake-osx config=release32
osx-debug64:
	make -C .build/projects/gmake-osx config=debug64
osx-release64:
	make -C .build/projects/gmake-osx config=release64
osx: osx-debug32 osx-release32 osx-debug64 osx-release64

rebuild-shaders:
	make -C examples/01-cubes rebuild
	make -C examples/02-metaballs rebuild
	make -C examples/03-raymarch rebuild
	make -C examples/04-mesh rebuild
	make -C examples/05-instancing rebuild
	make -C examples/06-bump rebuild
	make -C examples/07-callback rebuild
	make -C examples/08-update rebuild

docs:
	markdown README.md > .build/docs/readme.html

clean:
	@echo Cleaning...
	-rm -r .build
	-rm -r .debug
