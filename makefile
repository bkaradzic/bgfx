#
# Copyright 2011-2016 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin FreeBSD GNU/kFreeBSD))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
ifeq ($(UNAME),$(filter $(UNAME),FreeBSD GNU/kFreeBSD))
OS=bsd
else
OS=linux
endif
endif
else
OS=windows

help: projgen

endif

# $(info $(OS))

BX_DIR?=../bx
GENIE?=$(BX_DIR)/tools/bin/$(OS)/genie

.PHONY: help

help:
	@echo Available targets:
	@grep -E "^[a-zA-Z0-9_-]+:.*?## .*$$" $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

clean: ## Clean all intermediate files.
	@echo Cleaning...
	-@rm -rf .build
	@mkdir .build

projgen: ## Generate project files for all configurations.
	$(GENIE) --with-tools --with-shared-lib vs2008
	$(GENIE) --with-tools --with-shared-lib vs2010
	$(GENIE) --with-tools --with-shared-lib vs2012
	$(GENIE) --with-tools --with-shared-lib vs2013
	$(GENIE) --with-tools --with-shared-lib vs2015
	$(GENIE) --with-tools --with-shared-lib --gcc=mingw-gcc gmake
	$(GENIE) --with-tools --with-shared-lib --gcc=linux-gcc gmake
	$(GENIE) --with-tools --with-shared-lib --gcc=osx gmake
	$(GENIE) --with-tools --with-shared-lib --xcode=osx xcode4
	$(GENIE) --with-tools --with-shared-lib --xcode=ios xcode4
	$(GENIE) --with-shared-lib --gcc=freebsd gmake

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
android-arm-debug: .build/projects/gmake-android-arm ## Build - Android ARM Debug
	$(MAKE) -R -C .build/projects/gmake-android-arm config=debug
android-arm-release: .build/projects/gmake-android-arm ## Build - Android ARM Release
	$(MAKE) -R -C .build/projects/gmake-android-arm config=release
android-arm: android-arm-debug android-arm-release ## Build - Android ARM Debug and Release

.build/projects/gmake-android-mips:
	$(GENIE) --gcc=android-mips gmake
android-mips-debug: .build/projects/gmake-android-mips ## Build - Android MIPS Debug
	$(MAKE) -R -C .build/projects/gmake-android-mips config=debug
android-mips-release: .build/projects/gmake-android-mips ## Build - Android MIPS Release
	$(MAKE) -R -C .build/projects/gmake-android-mips config=release
android-mips: android-mips-debug android-mips-release ## Build - Android MIPS Debug and Release

.build/projects/gmake-android-x86:
	$(GENIE) --gcc=android-x86 gmake
android-x86-debug: .build/projects/gmake-android-x86 ## Build - Android x86 Debug and Release
	$(MAKE) -R -C .build/projects/gmake-android-x86 config=debug
android-x86-release: .build/projects/gmake-android-x86 ## Build - Android x86 Debug and Release
	$(MAKE) -R -C .build/projects/gmake-android-x86 config=release
android-x86: android-x86-debug android-x86-release ## Build - Android x86 Debug and Release

.build/projects/gmake-asmjs:
	$(GENIE) --gcc=asmjs gmake
asmjs-debug: .build/projects/gmake-asmjs ## Build - Emscripten Debug
	$(MAKE) -R -C .build/projects/gmake-asmjs config=debug
asmjs-release: .build/projects/gmake-asmjs ## Build - Emscripten Release
	$(MAKE) -R -C .build/projects/gmake-asmjs config=release
asmjs: asmjs-debug asmjs-release ## Build - Emscripten Debug and Release

.build/projects/gmake-linux:
	$(GENIE) --with-tools --with-shared-lib --gcc=linux-gcc gmake
linux-debug32: .build/projects/gmake-linux ## Build - Linux x86 Debug
	$(MAKE) -R -C .build/projects/gmake-linux config=debug32
linux-release32: .build/projects/gmake-linux ## Build - Linux x86 Release
	$(MAKE) -R -C .build/projects/gmake-linux config=release32
linux-debug64: .build/projects/gmake-linux ## Build - Linux x64 Debug
	$(MAKE) -R -C .build/projects/gmake-linux config=debug64
linux-release64: .build/projects/gmake-linux ## Build - Linux x64 Release
	$(MAKE) -R -C .build/projects/gmake-linux config=release64
linux: linux-debug32 linux-release32 linux-debug64 linux-release64 ## Build - Linux x86/x64 Debug and Release

.build/projects/gmake-freebsd:
	$(GENIE) --with-tools --with-shared-lib --gcc=freebsd gmake
freebsd-debug32: .build/projects/gmake-freebsd ## Build - FreeBSD x86 Debug
	$(MAKE) -R -C .build/projects/gmake-freebsd config=debug32
freebsd-release32: .build/projects/gmake-freebsd ## Build - FreeBSD x86 Release
	$(MAKE) -R -C .build/projects/gmake-freebsd config=release32
freebsd-debug64: .build/projects/gmake-freebsd ## Build - FreeBSD x86 Debug
	$(MAKE) -R -C .build/projects/gmake-freebsd config=debug64
freebsd-release64: .build/projects/gmake-freebsd ## Build - FreeBSD x86 Release
	$(MAKE) -R -C .build/projects/gmake-freebsd config=release64
freebsd: freebsd-debug32 freebsd-release32 freebsd-debug64 freebsd-release64 ## Build - FreeBSD x86/x64 Debug and Release

.build/projects/gmake-mingw-gcc:
	$(GENIE) --with-tools --with-shared-lib --gcc=mingw-gcc gmake
mingw-gcc-debug32: .build/projects/gmake-mingw-gcc ## Build - MinGW GCC x86 Debug
	$(MAKE) -R -C .build/projects/gmake-mingw-gcc config=debug32
mingw-gcc-release32: .build/projects/gmake-mingw-gcc ## Build - MinGW GCC x86 Release
	$(MAKE) -R -C .build/projects/gmake-mingw-gcc config=release32
mingw-gcc-debug64: .build/projects/gmake-mingw-gcc ## Build - MinGW GCC x64 Debug
	$(MAKE) -R -C .build/projects/gmake-mingw-gcc config=debug64
mingw-gcc-release64: .build/projects/gmake-mingw-gcc ## Build - MinGW GCC x64 Release
	$(MAKE) -R -C .build/projects/gmake-mingw-gcc config=release64
mingw-gcc: mingw-gcc-debug32 mingw-gcc-release32 mingw-gcc-debug64 mingw-gcc-release64 ## Build - MinGW GCC x86/x64 Debug and Release

.build/projects/gmake-mingw-clang:
	$(GENIE) --gcc=mingw-clang gmake
mingw-clang-debug32: .build/projects/gmake-mingw-clang ## Build - MinGW Clang x86 Debug
	$(MAKE) -R -C .build/projects/gmake-mingw-clang config=debug32
mingw-clang-release32: .build/projects/gmake-mingw-clang ## Build - MinGW Clang x86 Release
	$(MAKE) -R -C .build/projects/gmake-mingw-clang config=release32
mingw-clang-debug64: .build/projects/gmake-mingw-clang ## Build - MinGW Clang x64 Debug
	$(MAKE) -R -C .build/projects/gmake-mingw-clang config=debug64
mingw-clang-release64: .build/projects/gmake-mingw-clang ## Build - MinGW Clang x64 Release
	$(MAKE) -R -C .build/projects/gmake-mingw-clang config=release64
mingw-clang: mingw-clang-debug32 mingw-clang-release32 mingw-clang-debug64 mingw-clang-release64 ## Build - MinGW Clang x86/x64 Debug and Release

.build/projects/vs2008:
	$(GENIE) --with-tools --with-shared-lib vs2008
vs2008-debug32: .build/projects/vs2008 ## Build - VS2008 x86 Debug
	devenv .build/projects/vs2008/bgfx.sln /Build "Debug|Win32"
vs2008-release32: .build/projects/vs2008 ## Build - VS2008 x86 Release
	devenv .build/projects/vs2008/bgfx.sln /Build "Release|Win32"
vs2008-debug64: .build/projects/vs2008 ## Build - VS2008 x64 Debug
	devenv .build/projects/vs2008/bgfx.sln /Build "Debug|x64"
vs2008-release64: .build/projects/vs2008 ## Build - VS2008 x64 Release
	devenv .build/projects/vs2008/bgfx.sln /Build "Release|x64"
vs2008: vs2008-debug32 vs2008-release32 vs2008-debug64 vs2008-release64 ## Build - VS2008 x86/x64 Debug and Release

.build/projects/vs2010:
	$(GENIE) --with-tools --with-shared-lib vs2010
vs2010-debug32: .build/projects/vs2010 ## Build - VS2010 x86 Debug
	devenv .build/projects/vs2010/bgfx.sln /Build "Debug|Win32"
vs2010-release32: .build/projects/vs2010 ## Build - VS2010 x86 Release
	devenv .build/projects/vs2010/bgfx.sln /Build "Release|Win32"
vs2010-debug64: .build/projects/vs2010 ## Build - VS2010 x64 Debug
	devenv .build/projects/vs2010/bgfx.sln /Build "Debug|x64"
vs2010-release64: .build/projects/vs2010 ## Build - VS2010 x64 Release
	devenv .build/projects/vs2010/bgfx.sln /Build "Release|x64"
vs2010: vs2010-debug32 vs2010-release32 vs2010-debug64 vs2010-release64 ## Build - VS2010 x86/x64 Debug and Release

.build/projects/vs2012:
	$(GENIE) --with-tools --with-shared-lib vs2012
vs2012-debug32: .build/projects/vs2012 ## Build - VS2012 x86 Debug
	devenv .build/projects/vs2012/bgfx.sln /Build "Debug|Win32"
vs2012-release32: .build/projects/vs2012 ## Build - VS2012 x86 Release
	devenv .build/projects/vs2012/bgfx.sln /Build "Release|Win32"
vs2012-debug64: .build/projects/vs2012 ## Build - VS2012 x64 Debug
	devenv .build/projects/vs2012/bgfx.sln /Build "Debug|x64"
vs2012-release64: .build/projects/vs2012 ## Build - VS2012 x64 Release
	devenv .build/projects/vs2012/bgfx.sln /Build "Release|x64"
vs2012: vs2012-debug32 vs2012-release32 vs2012-debug64 vs2012-release64 ## Build - VS2012 x86/x64 Debug and Release

.build/projects/vs2013:
	$(GENIE) --with-tools --with-shared-lib vs2013
vs2013-debug32: .build/projects/vs2013 ## Build - VS2013 x86 Debug
	devenv .build/projects/vs2013/bgfx.sln /Build "Debug|Win32"
vs2013-release32: .build/projects/vs2013 ## Build - VS2013 x86 Release
	devenv .build/projects/vs2013/bgfx.sln /Build "Release|Win32"
vs2013-debug64: .build/projects/vs2013 ## Build - VS2013 x64 Debug
	devenv .build/projects/vs2013/bgfx.sln /Build "Debug|x64"
vs2013-release64: .build/projects/vs2013 ## Build - VS2013 x64 Release
	devenv .build/projects/vs2013/bgfx.sln /Build "Release|x64"
vs2013: vs2013-debug32 vs2013-release32 vs2013-debug64 vs2013-release64 ## Build - VS2013 x86/x64 Debug and Release

.build/projects/vs2015:
	$(GENIE) --with-tools --with-shared-lib vs2015
vs2015-debug32: .build/projects/vs2015 ## Build - VS2015 x86 Debug
	devenv .build/projects/vs2015/bgfx.sln /Build "Debug|Win32"
vs2015-release32: .build/projects/vs2015 ## Build - VS2015 x86 Release
	devenv .build/projects/vs2015/bgfx.sln /Build "Release|Win32"
vs2015-debug64: .build/projects/vs2015 ## Build - VS2015 x64 Debug
	devenv .build/projects/vs2015/bgfx.sln /Build "Debug|x64"
vs2015-release64: .build/projects/vs2015 ## Build - VS2015 x64 Release
	devenv .build/projects/vs2015/bgfx.sln /Build "Release|x64"
vs2015: vs2015-debug32 vs2015-release32 vs2015-debug64 vs2015-release64 ## Build - VS2015 x86/x64 Debug and Release

.build/projects/gmake-nacl:
	$(GENIE) --gcc=nacl gmake
nacl-debug32: .build/projects/gmake-nacl ## Build - Native Client x86 Debug
	$(MAKE) -R -C .build/projects/gmake-nacl config=debug32
nacl-release32: .build/projects/gmake-nacl ## Build - Native Client x86 Release
	$(MAKE) -R -C .build/projects/gmake-nacl config=release32
nacl-debug64: .build/projects/gmake-nacl ## Build - Native Client x64 Debug
	$(MAKE) -R -C .build/projects/gmake-nacl config=debug64
nacl-release64: .build/projects/gmake-nacl ## Build - Native Client x64 Release
	$(MAKE) -R -C .build/projects/gmake-nacl config=release64
nacl: nacl-debug32 nacl-release32 nacl-debug64 nacl-release64 ## Build - Native Client x86/x64 Debug and Release

.build/projects/gmake-nacl-arm:
	$(GENIE) --gcc=nacl-arm gmake
nacl-arm-debug: .build/projects/gmake-nacl-arm ## Build - Native Client ARM Debug
	$(MAKE) -R -C .build/projects/gmake-nacl-arm config=debug
nacl-arm-release: .build/projects/gmake-nacl-arm ## Build - Native Client ARM Release
	$(MAKE) -R -C .build/projects/gmake-nacl-arm config=release
nacl-arm: nacl-arm-debug32 nacl-arm-release32 ## Build - Native Client ARM Debug and Release

.build/projects/gmake-pnacl:
	$(GENIE) --gcc=pnacl gmake
pnacl-debug: .build/projects/gmake-pnacl ## Build - Portable Native Client Debug
	$(MAKE) -R -C .build/projects/gmake-pnacl config=debug
pnacl-release: .build/projects/gmake-pnacl ## Build - Portable Native Client Release
	$(MAKE) -R -C .build/projects/gmake-pnacl config=release
pnacl: pnacl-debug pnacl-release ## Build - Portable Native Client Debug and Release

.build/projects/gmake-osx:
	$(GENIE) --with-tools --with-shared-lib --gcc=osx gmake
osx-debug32: .build/projects/gmake-osx ## Build - OSX x86 Debug
	$(MAKE) -C .build/projects/gmake-osx config=debug32
osx-release32: .build/projects/gmake-osx ## Build - OSX x86 Release
	$(MAKE) -C .build/projects/gmake-osx config=release32
osx-debug64: .build/projects/gmake-osx ## Build - OSX x64 Debug
	$(MAKE) -C .build/projects/gmake-osx config=debug64
osx-release64: .build/projects/gmake-osx ## Build - OSX x64 Release
	$(MAKE) -C .build/projects/gmake-osx config=release64
osx: osx-debug32 osx-release32 osx-debug64 osx-release64 ## Build - OSX x86/x64 Debug and Release

.build/projects/gmake-ios-arm:
	$(GENIE) --gcc=ios-arm gmake
ios-arm-debug: .build/projects/gmake-ios-arm ## Build - iOS ARM Debug
	$(MAKE) -R -C .build/projects/gmake-ios-arm config=debug
ios-arm-release: .build/projects/gmake-ios-arm ## Build - iOS ARM Release
	$(MAKE) -R -C .build/projects/gmake-ios-arm config=release
ios-arm: ios-arm-debug ios-arm-release ## Build - iOS ARM Debug and Release

.build/projects/gmake-ios-simulator:
	$(GENIE) --gcc=ios-simulator gmake
ios-simulator-debug: .build/projects/gmake-ios-simulator ## Build - iOS Simulator Debug
	$(MAKE) -R -C .build/projects/gmake-ios-simulator config=debug
ios-simulator-release: .build/projects/gmake-ios-simulator ## Build - iOS Simulator Release
	$(MAKE) -R -C .build/projects/gmake-ios-simulator config=release
ios-simulator: ios-simulator-debug ios-simulator-release ## Build - iOS Simulator Debug and Release

.build/projects/gmake-rpi:
	$(GENIE) --gcc=rpi gmake
rpi-debug: .build/projects/gmake-rpi ## Build - RasberryPi Debug
	$(MAKE) -R -C .build/projects/gmake-rpi config=debug
rpi-release: .build/projects/gmake-rpi ## Build - RasberryPi Release
	$(MAKE) -R -C .build/projects/gmake-rpi config=release
rpi: rpi-debug rpi-release ## Build - RasberryPi Debug and Release

build-darwin: osx

build-linux: linux-debug64 linux-release64

build-windows: mingw-gcc

build: build-$(OS)

rebuild-shaders:
	$(MAKE) -R -C examples rebuild

analyze:
	cppcheck src/
	cppcheck examples/

docs:
	doxygen scripts/bgfx.doxygen
	markdown README.md > .build/docs/readme.html

###

SILENT ?= @

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin FreeBSD GNU/kFreeBSD))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
BUILD_PROJECT_DIR=gmake-osx
BUILD_OUTPUT_DIR=osx64_clang
BUILD_TOOLS_CONFIG=release64
BUILD_TOOLS_SUFFIX=Release
EXE=
else
ifeq ($(UNAME),$(filter $(UNAME),FreeBSD GNU/kFreeBSD))
OS=bsd
BUILD_PROJECT_DIR=gmake-freebsd
BUILD_OUTPUT_DIR=freebsd64_gcc
BUILD_TOOLS_CONFIG=release64
BUILD_TOOLS_SUFFIX=Release
EXE=
else
OS=linux
BUILD_PROJECT_DIR=gmake-linux
BUILD_OUTPUT_DIR=linux64_gcc
BUILD_TOOLS_CONFIG=release64
BUILD_TOOLS_SUFFIX=Release
EXE=
endif
endif
else
OS=windows
BUILD_PROJECT_DIR=gmake-mingw-gcc
BUILD_OUTPUT_DIR=win64_mingw-gcc
BUILD_TOOLS_CONFIG=release64
BUILD_TOOLS_SUFFIX=Release
EXE=.exe
endif

geometryc: .build/projects/$(BUILD_PROJECT_DIR) ## Build geometryc tool.
	$(SILENT) $(MAKE) -C .build/projects/$(BUILD_PROJECT_DIR) -f geometryc.make config=$(BUILD_TOOLS_CONFIG)
	$(SILENT) cp .build/$(BUILD_OUTPUT_DIR)/bin/geometryc$(BUILD_TOOLS_SUFFIX)$(EXE) tools/bin/$(OS)/geometryc$(EXE)

shaderc: .build/projects/$(BUILD_PROJECT_DIR) ## Build shaderc tool.
	$(SILENT) $(MAKE) -C .build/projects/$(BUILD_PROJECT_DIR) -f shaderc.make config=$(BUILD_TOOLS_CONFIG)
	$(SILENT) cp .build/$(BUILD_OUTPUT_DIR)/bin/shaderc$(BUILD_TOOLS_SUFFIX)$(EXE) tools/bin/$(OS)/shaderc$(EXE)

texturec: .build/projects/$(BUILD_PROJECT_DIR) ## Build texturec tool.
	$(SILENT) $(MAKE) -C .build/projects/$(BUILD_PROJECT_DIR) -f texturec.make config=$(BUILD_TOOLS_CONFIG)
	$(SILENT) cp .build/$(BUILD_OUTPUT_DIR)/bin/texturec$(BUILD_TOOLS_SUFFIX)$(EXE) tools/bin/$(OS)/texturec$(EXE)

tools: geometryc shaderc texturec ## Build tools.

dist-windows: .build/projects/gmake-mingw-gcc
	$(SILENT) $(MAKE) -C .build/projects/gmake-mingw-gcc config=release64 -j 6 geometryc
	$(SILENT) cp .build/win64_mingw-gcc/bin/geometrycRelease tools/bin/windows/geometryc.exe
	$(SILENT) $(MAKE) -C .build/projects/gmake-mingw-gcc config=release64 -j 6 shaderc
	$(SILENT) cp .build/win64_mingw-gcc/bin/shadercRelease   tools/bin/windows/shaderc.exe
	$(SILENT) $(MAKE) -C .build/projects/gmake-mingw-gcc config=release64 -j 6 texturec
	$(SILENT) cp .build/win64_mingw-gcc/bin/texturecRelease  tools/bin/windows/texturec.exe

dist-linux: .build/projects/gmake-linux
	$(SILENT) $(MAKE) -C .build/projects/gmake-linux     config=release64 -j 6 geometryc
	$(SILENT) cp .build/linux64_gcc/bin/geometrycRelease tools/bin/linux/geometryc
	$(SILENT) $(MAKE) -C .build/projects/gmake-linux     config=release64 -j 6 shaderc
	$(SILENT) cp .build/linux64_gcc/bin/shadercRelease   tools/bin/linux/shaderc
	$(SILENT) $(MAKE) -C .build/projects/gmake-linux     config=release64 -j 6 texturec
	$(SILENT) cp .build/linux64_gcc/bin/texturecRelease  tools/bin/linux/texturec

dist-darwin: .build/projects/gmake-osx
	$(SILENT) $(MAKE) -C .build/projects/gmake-osx       config=release64 -j 6 geometryc
	$(SILENT) cp .build/osx64_clang/bin/geometrycRelease tools/bin/darwin/geometryc
	$(SILENT) $(MAKE) -C .build/projects/gmake-osx       config=release64 -j 6 shaderc
	$(SILENT) cp .build/osx64_clang/bin/shadercRelease   tools/bin/darwin/shaderc
	$(SILENT) $(MAKE) -C .build/projects/gmake-osx       config=release64 -j 6 texturec
	$(SILENT) cp .build/osx64_clang/bin/texturecRelease  tools/bin/darwin/texturec

dist: clean dist-windows dist-linux dist-darwin
