#
# Copyright 2011-2012 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

all:
	premake --file=premake/premake4.lua vs2008
	premake --file=premake/premake4.lua vs2010
	premake --file=premake/premake4.lua --gcc=nacl gmake
	premake --file=premake/premake4.lua --gcc=pnacl gmake
	premake --file=premake/premake4.lua --gcc=mingw gmake
	premake --file=premake/premake4.lua --gcc=linux gmake
	premake --file=premake/premake4.lua --gcc=emscripten gmake
	premake --file=premake/premake4.lua xcode4
	make -s --no-print-directory -C src

linux-debug32:
	make -C .build/projects/gmake-linux config=debug32
linux-release32:
	make -C .build/projects/gmake-linux config=release32
linux-debug64:
	make -C .build/projects/gmake-linux config=debug64
linux-release64:
	make -C .build/projects/gmake-linux config=release64
linux: linux-debug32 linux-release32 linux-debug64 linux-release64

mingw-debug32:
	make -C .build/projects/gmake-mingw config=debug32
mingw-release32:
	make -C .build/projects/gmake-mingw config=release32
mingw-debug64:
	make -C .build/projects/gmake-mingw config=debug64
mingw-release64:
	make -C .build/projects/gmake-mingw config=release64
mingw: mingw-debug32 mingw-release32 mingw-debug64 mingw-release64

nacl-debug32:
	make -C .build/projects/gmake-nacl config=debug32
nacl-release32:
	make -C .build/projects/gmake-nacl config=release32
nacl-debug64:
	make -C .build/projects/gmake-nacl config=debug64
nacl-release64:
	make -C .build/projects/gmake-nacl config=release64
nacl: nacl-debug32 nacl-release32 nacl-debug64 nacl-release64

pnacl-debug:
	make -C .build/projects/gmake-pnacl config=debug64
pnacl-release:
	make -C .build/projects/gmake-pnacl config=release64

docs:
	# doxygen premake/bgfx.doxygen
	markdown README.md > .build/docs/readme.html

clean:
	@echo Cleaning...
	-rm -r .build
	-rm -r .debug
