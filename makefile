#
# Copyright 2011-2014 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
OS=linux
endif
else
OS=windows
endif

PREMAKE4=../bx/tools/bin/$(OS)/premake4

all:
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib vs2008
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib vs2010
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib vs2012
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib vs2013
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib --gcc=mingw gmake
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib --gcc=linux-gcc gmake
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib --gcc=osx gmake
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib xcode4
	
	$(PREMAKE4) --file=premake/premake4.lua --gcc=android-arm gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=android-mips gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=android-x86 gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=asmjs gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=ios-arm gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=ios-simulator gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=nacl gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=nacl-arm gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=pnacl gmake
	$(PREMAKE4) --file=premake/premake4.lua --gcc=rpi gmake

.build/projects/gmake-android-arm:
	$(PREMAKE4) --file=premake/premake4.lua --gcc=android-arm gmake
android-arm-debug: .build/projects/gmake-android-arm
	make -R -C .build/projects/gmake-android-arm config=debug
android-arm-release: .build/projects/gmake-android-arm
	make -R -C .build/projects/gmake-android-arm config=release
android-arm: android-arm-debug android-arm-release

.build/projects/gmake-android-mips:
	$(PREMAKE4) --file=premake/premake4.lua --gcc=android-mips gmake
android-mips-debug: .build/projects/gmake-android-mips
	make -R -C .build/projects/gmake-android-mips config=debug
android-mips-release: .build/projects/gmake-android-mips
	make -R -C .build/projects/gmake-android-mips config=release
android-mips: android-mips-debug android-mips-release

.build/projects/gmake-android-x86:
	$(PREMAKE4) --file=premake/premake4.lua --gcc=android-x86 gmake
android-x86-debug: .build/projects/gmake-android-x86
	make -R -C .build/projects/gmake-android-x86 config=debug
android-x86-release: .build/projects/gmake-android-x86
	make -R -C .build/projects/gmake-android-x86 config=release
android-x86: android-x86-debug android-x86-release

.build/projects/gmake-asmjs:
	$(PREMAKE4) --file=premake/premake4.lua --gcc=asmjs gmake
asmjs-debug: .build/projects/gmake-asmjs
	make -R -C .build/projects/gmake-asmjs config=debug
asmjs-release: .build/projects/gmake-asmjs
	make -R -C .build/projects/gmake-asmjs config=release
asmjs: asmjs-debug asmjs-release

.build/projects/gmake-linux:
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib --gcc=linux-gcc gmake
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
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib --gcc=mingw gmake
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
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib vs2008
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
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib vs2010

.build/projects/vs2012:
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib vs2012

.build/projects/vs2013:
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib vs2013

.build/projects/gmake-nacl:
	$(PREMAKE4) --file=premake/premake4.lua --gcc=nacl gmake
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
	$(PREMAKE4) --file=premake/premake4.lua --gcc=nacl-arm gmake
nacl-arm-debug: .build/projects/gmake-nacl-arm
	make -R -C .build/projects/gmake-nacl-arm config=debug
nacl-arm-release: .build/projects/gmake-nacl-arm
	make -R -C .build/projects/gmake-nacl-arm config=release
nacl-arm: nacl-arm-debug32 nacl-arm-release32

.build/projects/gmake-pnacl:
	$(PREMAKE4) --file=premake/premake4.lua --gcc=pnacl gmake
pnacl-debug: .build/projects/gmake-pnacl
	make -R -C .build/projects/gmake-pnacl config=debug
pnacl-release: .build/projects/gmake-pnacl
	make -R -C .build/projects/gmake-pnacl config=release
pnacl: pnacl-debug pnacl-release

.build/projects/gmake-osx:
	$(PREMAKE4) --file=premake/premake4.lua --with-tools --with-shared-lib --gcc=osx gmake
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
	$(PREMAKE4) --file=premake/premake4.lua --gcc=ios-arm gmake
ios-arm-debug: .build/projects/gmake-ios-arm
	make -R -C .build/projects/gmake-ios-arm config=debug
ios-arm-release: .build/projects/gmake-ios-arm
	make -R -C .build/projects/gmake-ios-arm config=release
ios-arm: ios-arm-debug ios-arm-release

.build/projects/gmake-ios-simulator:
	$(PREMAKE4) --file=premake/premake4.lua --gcc=ios-simulator gmake
ios-simulator-debug: .build/projects/gmake-ios-simulator
	make -R -C .build/projects/gmake-ios-simulator config=debug
ios-simulator-release: .build/projects/gmake-ios-simulator
	make -R -C .build/projects/gmake-ios-simulator config=release
ios-simulator: ios-simulator-debug ios-simulator-release

.build/projects/gmake-rpi:
	$(PREMAKE4) --file=premake/premake4.lua --gcc=rpi gmake
rpi-debug: .build/projects/gmake-rpi
	make -R -C .build/projects/gmake-rpi config=debug
rpi-release: .build/projects/gmake-rpi
	make -R -C .build/projects/gmake-rpi config=release
rpi: rpi-debug rpi-release

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

###

SILENT ?= @

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
BUILD_PROJECT_DIR=gmake-osx
BUILD_OUTPUT_DIR=osx64_gcc
BUILD_TOOLS_CONFIG=release64
EXE=
else
OS=linux
BUILD_PROJECT_DIR=gmake-linux
BUILD_OUTPUT_DIR=linux64_gcc
BUILD_TOOLS_CONFIG=release64
EXE=
endif
else
OS=windows
BUILD_PROJECT_DIR=gmake-mingw
BUILD_OUTPUT_DIR=win32_mingw
BUILD_TOOLS_CONFIG=release32
EXE=.exe
endif

.build/$(BUILD_OUTPUT_DIR)/bin/shadercRelease$(EXE): .build/projects/$(BUILD_PROJECT_DIR)
	$(SILENT) make -C .build/projects/$(BUILD_PROJECT_DIR) -f shaderc.make config=$(BUILD_TOOLS_CONFIG)

tools/bin/$(OS)/shaderc$(EXE): .build/$(BUILD_OUTPUT_DIR)/bin/shadercRelease$(EXE)
	$(SILENT) cp $(<) $(@)

.build/$(BUILD_OUTPUT_DIR)/bin/geometrycRelease$(EXE): .build/projects/$(BUILD_PROJECT_DIR)
	$(SILENT) make -C .build/projects/$(BUILD_PROJECT_DIR) -f geometryc.make config=$(BUILD_TOOLS_CONFIG)

tools/bin/$(OS)/geometryc$(EXE): .build/$(BUILD_OUTPUT_DIR)/bin/geometrycRelease$(EXE)
	$(SILENT) cp $(<) $(@)

tools: tools/bin/$(OS)/shaderc$(EXE) tools/bin/$(OS)/geometryc$(EXE)
