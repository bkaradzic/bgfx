#
# Copyright 2011-2015 Branimir Karadzic. All rights reserved.
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

GENIE=../bx/tools/bin/$(OS)/genie

all:
	$(GENIE) --with-tools --with-shared-lib vs2008
	$(GENIE) --with-tools --with-shared-lib vs2010
	$(GENIE) --with-tools --with-shared-lib vs2012
	$(GENIE) --with-tools --with-shared-lib vs2013
	$(GENIE) --with-tools --with-shared-lib --gcc=mingw-gcc gmake
	$(GENIE) --with-tools --with-shared-lib --gcc=linux-gcc gmake
	$(GENIE) --with-tools --with-shared-lib --gcc=osx gmake
	$(GENIE) --with-tools --with-shared-lib --xcode=osx xcode4
	$(GENIE) --with-tools --with-shared-lib --xcode=ios xcode4

	$(GENIE) --gcc=android-arm gmake
	$(GENIE) --gcc=android-mips gmake
	$(GENIE) --gcc=android-x86 gmake
	$(GENIE) --gcc=asmjs gmake
	$(GENIE) --gcc=ios-arm gmake
	$(GENIE) --gcc=ios-simulator gmake
	$(GENIE) --gcc=nacl gmake
	$(GENIE) --gcc=nacl-arm gmake
	$(GENIE) --gcc=pnacl gmake
	$(GENIE) --gcc=rpi gmake

.build/projects/gmake-android-arm:
	$(GENIE) --gcc=android-arm gmake
android-arm-debug: .build/projects/gmake-android-arm
	make -R -C .build/projects/gmake-android-arm config=debug
android-arm-release: .build/projects/gmake-android-arm
	make -R -C .build/projects/gmake-android-arm config=release
android-arm: android-arm-debug android-arm-release

.build/projects/gmake-android-mips:
	$(GENIE) --gcc=android-mips gmake
android-mips-debug: .build/projects/gmake-android-mips
	make -R -C .build/projects/gmake-android-mips config=debug
android-mips-release: .build/projects/gmake-android-mips
	make -R -C .build/projects/gmake-android-mips config=release
android-mips: android-mips-debug android-mips-release

.build/projects/gmake-android-x86:
	$(GENIE) --gcc=android-x86 gmake
android-x86-debug: .build/projects/gmake-android-x86
	make -R -C .build/projects/gmake-android-x86 config=debug
android-x86-release: .build/projects/gmake-android-x86
	make -R -C .build/projects/gmake-android-x86 config=release
android-x86: android-x86-debug android-x86-release

.build/projects/gmake-asmjs:
	$(GENIE) --gcc=asmjs gmake
asmjs-debug: .build/projects/gmake-asmjs
	make -R -C .build/projects/gmake-asmjs config=debug
asmjs-release: .build/projects/gmake-asmjs
	make -R -C .build/projects/gmake-asmjs config=release
asmjs: asmjs-debug asmjs-release

.build/projects/gmake-linux:
	$(GENIE) --with-tools --with-shared-lib --gcc=linux-gcc gmake
linux-debug32: .build/projects/gmake-linux
	make -R -C .build/projects/gmake-linux config=debug32
linux-release32: .build/projects/gmake-linux
	make -R -C .build/projects/gmake-linux config=release32
linux-debug64: .build/projects/gmake-linux
	make -R -C .build/projects/gmake-linux config=debug64
linux-release64: .build/projects/gmake-linux
	make -R -C .build/projects/gmake-linux config=release64
linux: linux-debug32 linux-release32 linux-debug64 linux-release64

.build/projects/gmake-mingw-gcc:
	$(GENIE) --with-tools --with-shared-lib --gcc=mingw-gcc gmake
mingw-gcc-debug32: .build/projects/gmake-mingw-gcc
	make -R -C .build/projects/gmake-mingw-gcc config=debug32
mingw-gcc-release32: .build/projects/gmake-mingw-gcc
	make -R -C .build/projects/gmake-mingw-gcc config=release32
mingw-gcc-debug64: .build/projects/gmake-mingw-gcc
	make -R -C .build/projects/gmake-mingw-gcc config=debug64
mingw-gcc-release64: .build/projects/gmake-mingw-gcc
	make -R -C .build/projects/gmake-mingw-gcc config=release64
mingw-gcc: mingw-gcc-debug32 mingw-gcc-release32 mingw-gcc-debug64 mingw-gcc-release64

.build/projects/gmake-mingw-clang:
	$(GENIE) --gcc=mingw-clang gmake
mingw-clang-debug32: .build/projects/gmake-mingw-clang
	make -R -C .build/projects/gmake-mingw-clang config=debug32
mingw-clang-release32: .build/projects/gmake-mingw-clang
	make -R -C .build/projects/gmake-mingw-clang config=release32
mingw-clang-debug64: .build/projects/gmake-mingw-clang
	make -R -C .build/projects/gmake-mingw-clang config=debug64
mingw-clang-release64: .build/projects/gmake-mingw-clang
	make -R -C .build/projects/gmake-mingw-clang config=release64
mingw-clang: mingw-clang-debug32 mingw-clang-release32 mingw-clang-debug64 mingw-clang-release64

.build/projects/vs2008:
	$(GENIE) --with-tools --with-shared-lib vs2008
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
	$(GENIE) --with-tools --with-shared-lib vs2010

.build/projects/vs2012:
	$(GENIE) --with-tools --with-shared-lib vs2012

.build/projects/vs2013:
	$(GENIE) --with-tools --with-shared-lib vs2013

.build/projects/gmake-nacl:
	$(GENIE) --gcc=nacl gmake
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
	$(GENIE) --gcc=nacl-arm gmake
nacl-arm-debug: .build/projects/gmake-nacl-arm
	make -R -C .build/projects/gmake-nacl-arm config=debug
nacl-arm-release: .build/projects/gmake-nacl-arm
	make -R -C .build/projects/gmake-nacl-arm config=release
nacl-arm: nacl-arm-debug32 nacl-arm-release32

.build/projects/gmake-pnacl:
	$(GENIE) --gcc=pnacl gmake
pnacl-debug: .build/projects/gmake-pnacl
	make -R -C .build/projects/gmake-pnacl config=debug
pnacl-release: .build/projects/gmake-pnacl
	make -R -C .build/projects/gmake-pnacl config=release
pnacl: pnacl-debug pnacl-release

.build/projects/gmake-osx:
	$(GENIE) --with-tools --with-shared-lib --gcc=osx gmake
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
	$(GENIE) --gcc=ios-arm gmake
ios-arm-debug: .build/projects/gmake-ios-arm
	make -R -C .build/projects/gmake-ios-arm config=debug
ios-arm-release: .build/projects/gmake-ios-arm
	make -R -C .build/projects/gmake-ios-arm config=release
ios-arm: ios-arm-debug ios-arm-release

.build/projects/gmake-ios-simulator:
	$(GENIE) --gcc=ios-simulator gmake
ios-simulator-debug: .build/projects/gmake-ios-simulator
	make -R -C .build/projects/gmake-ios-simulator config=debug
ios-simulator-release: .build/projects/gmake-ios-simulator
	make -R -C .build/projects/gmake-ios-simulator config=release
ios-simulator: ios-simulator-debug ios-simulator-release

.build/projects/gmake-rpi:
	$(GENIE) --gcc=rpi gmake
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
	doxygen scripts/bgfx.doxygen
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
BUILD_OUTPUT_DIR=osx64_clang
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
BUILD_PROJECT_DIR=gmake-mingw-gcc
BUILD_OUTPUT_DIR=win32_mingw-gcc
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
