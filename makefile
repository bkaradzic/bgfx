#
# Copyright 2011-2021 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
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

help:
	@echo Available targets:
	@grep -E "^[a-zA-Z0-9_-]+:.*?## .*$$" $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

else
OS=windows

help: projgen

endif

# $(info $(OS))

BX_DIR?=../bx
GENIE?=$(BX_DIR)/tools/bin/$(OS)/genie $(EXTRA_GENIE_ARGS)
NINJA?=$(BX_DIR)/tools/bin/$(OS)/ninja

.PHONY: help

clean: ## Clean all intermediate files.
	@echo Cleaning...
	-@rm -rf .build
	@mkdir .build

projgen: ## Generate project files for all configurations.
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib                       vs2017
	$(GENIE) --with-tools --with-combined-examples                   --vs=winstore100      vs2017
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=mingw-gcc       gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=linux-gcc       gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=osx-x64         gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=osx-arm64       gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --xcode=osx           xcode9
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --xcode=ios           xcode9
	$(GENIE)              --with-combined-examples --with-shared-lib --gcc=freebsd         gmake
	$(GENIE)              --with-combined-examples                   --gcc=android-arm     gmake
	$(GENIE)              --with-combined-examples                   --gcc=android-arm64   gmake
	$(GENIE)              --with-combined-examples                   --gcc=android-x86     gmake
	$(GENIE)              --with-examples                            --gcc=wasm2js         gmake
	$(GENIE)              --with-combined-examples                   --gcc=ios-arm         gmake
	$(GENIE)              --with-combined-examples                   --gcc=ios-arm64       gmake
	$(GENIE)              --with-combined-examples                   --gcc=ios-simulator   gmake
	$(GENIE)              --with-combined-examples                   --gcc=ios-simulator64 gmake
	$(GENIE)              --with-combined-examples                   --gcc=rpi             gmake

idl: ## Generate code from IDL.
	@echo Generating code from IDL.
	cd scripts && ../$(GENIE) idl

.build/projects/gmake-android-arm:
	$(GENIE) --gcc=android-arm gmake
android-arm-debug: .build/projects/gmake-android-arm ## Build - Android ARM Debug
	$(MAKE) -R -C .build/projects/gmake-android-arm config=debug
android-arm-release: .build/projects/gmake-android-arm ## Build - Android ARM Release
	$(MAKE) -R -C .build/projects/gmake-android-arm config=release
android-arm: android-arm-debug android-arm-release ## Build - Android ARM Debug and Release

.build/projects/gmake-android-arm64:
	$(GENIE) --gcc=android-arm64 gmake
android-arm64-debug: .build/projects/gmake-android-arm64 ## Build - Android ARM64 Debug
	$(MAKE) -R -C .build/projects/gmake-android-arm64 config=debug
android-arm64-release: .build/projects/gmake-android-arm64 ## Build - Android ARM64 Release
	$(MAKE) -R -C .build/projects/gmake-android-arm64 config=release
android-arm64: android-arm64-debug android-arm64-release ## Build - Android ARM64 Debug and Release

.build/projects/gmake-android-x86:
	$(GENIE) --gcc=android-x86 gmake
android-x86-debug: .build/projects/gmake-android-x86 ## Build - Android x86 Debug and Release
	$(MAKE) -R -C .build/projects/gmake-android-x86 config=debug
android-x86-release: .build/projects/gmake-android-x86 ## Build - Android x86 Debug and Release
	$(MAKE) -R -C .build/projects/gmake-android-x86 config=release
android-x86: android-x86-debug android-x86-release ## Build - Android x86 Debug and Release

.build/projects/gmake-wasm2js: # Wasm2JS: The JavaScript fallback for web builds when Wasm is not supported by browser
	$(GENIE) --gcc=wasm2js --with-combined-examples gmake
wasm2js-debug: .build/projects/gmake-wasm2js ## Build - Emscripten Debug
	$(MAKE) -R -C .build/projects/gmake-wasm2js config=debug
wasm2js-release: .build/projects/gmake-wasm2js ## Build - Emscripten Release
	$(MAKE) -R -C .build/projects/gmake-wasm2js config=release
wasm2js: wasm2js-debug wasm2js-release ## Build - Emscripten Debug and Release

.build/projects/gmake-wasm:
	$(GENIE) --gcc=wasm --with-combined-examples gmake
wasm-debug: .build/projects/gmake-wasm ## Build - Emscripten Debug
	$(MAKE) -R -C .build/projects/gmake-wasm config=debug
wasm-release: .build/projects/gmake-wasm ## Build - Emscripten Release
	$(MAKE) -R -C .build/projects/gmake-wasm config=release
wasm: wasm-debug wasm-release ## Build - Emscripten Debug and Release

.build/projects/gmake-linux:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=linux-gcc gmake
linux-debug64: .build/projects/gmake-linux ## Build - Linux x64 Debug
	$(MAKE) -R -C .build/projects/gmake-linux config=debug64
linux-release64: .build/projects/gmake-linux ## Build - Linux x64 Release
	$(MAKE) -R -C .build/projects/gmake-linux config=release64
linux: linux-debug64 linux-release64 ## Build - Linux x86/x64 Debug and Release

.build/projects/gmake-freebsd:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=freebsd gmake
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
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --os=windows --gcc=mingw-gcc gmake
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

.build/projects/vs2017:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib vs2017
vs2017-debug32: .build/projects/vs2017 ## Build - vs2017 x86 Debug
	devenv .build/projects/vs2017/bgfx.sln /Build "Debug|Win32"
vs2017-release32: .build/projects/vs2017 ## Build - vs2017 x86 Release
	devenv .build/projects/vs2017/bgfx.sln /Build "Release|Win32"
vs2017-debug64: .build/projects/vs2017 ## Build - vs2017 x64 Debug
	devenv .build/projects/vs2017/bgfx.sln /Build "Debug|x64"
vs2017-release64: .build/projects/vs2017 ## Build - vs2017 x64 Release
	devenv .build/projects/vs2017/bgfx.sln /Build "Release|x64"
vs2017: vs2017-debug32 vs2017-release32 vs2017-debug64 vs2017-release64 ## Build - vs2017 x86/x64 Debug and Release

.build/projects/vs2017-winstore100:
	$(GENIE) --with-combined-examples --vs=winstore100 vs2017
vs2017-winstore100-debug32: .build/projects/vs2017-winstore100 ## Build - vs2017-winstore100 x86 Debug
	devenv .build/projects/vs2017-winstore100/bgfx.sln /Build "Debug|Win32"
vs2017-winstore100-release32: .build/projects/vs2017-winstore100 ## Build - vs2017-winstore100 x86 Release
	devenv .build/projects/vs2017-winstore100/bgfx.sln /Build "Release|Win32"
vs2017-winstore100-debug64: .build/projects/vs2017-winstore100 ## Build - vs2017-winstore100 x64 Debug
	devenv .build/projects/vs2017-winstore100/bgfx.sln /Build "Debug|x64"
vs2017-winstore100-release64: .build/projects/vs2017-winstore100 ## Build - vs2017-winstore100 x64 Release
	devenv .build/projects/vs2017-winstore100/bgfx.sln /Build "Release|x64"
vs2017-winstore100: vs2017-winstore100-debug32 vs2017-winstore100-release32 vs2017-winstore100-debug64 vs2017-winstore100-release64 ## Build - vs2017-winstore100 x86/x64 Debug and Release

.build/projects/gmake-osx-x64:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=osx-x64 gmake
.build/projects/gmake-osx-arm64:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=osx-arm64 gmake

osx-debug: osx-x64-debug osx-arm64-debug ## Build - macOS Universal Debug
osx-release: osx-x64-release osx-arm64-release ## Build - macOS Universal Release
osx: osx-debug osx-release ## Build - macOS Universal Debug and Release

osx-x64-debug: .build/projects/gmake-osx-x64 ## Build - macOS x64 Debug
	$(MAKE) -C .build/projects/gmake-osx-x64 config=debug
osx-x64-release: .build/projects/gmake-osx-x64 ## Build - macOS x64 Release
	$(MAKE) -C .build/projects/gmake-osx-x64 config=release
osx-x64: osx-x64-debug osx-x64-release ## Build - macOS x64 Debug and Release

osx-arm64-debug: .build/projects/gmake-osx-arm64 ## Build - macOS ARM Debug
	$(MAKE) -C .build/projects/gmake-osx-arm64 config=debug
osx-arm64-release: .build/projects/gmake-osx-arm64 ## Build - macOS ARM Release
	$(MAKE) -C .build/projects/gmake-osx-arm64 config=release
osx-arm: osx-arm64-debug osx-arm64-release ## Build - macOS ARM Debug and Release

.build/projects/gmake-ios-arm:
	$(GENIE) --gcc=ios-arm gmake
ios-arm-debug: .build/projects/gmake-ios-arm ## Build - iOS ARM Debug
	$(MAKE) -R -C .build/projects/gmake-ios-arm config=debug
ios-arm-release: .build/projects/gmake-ios-arm ## Build - iOS ARM Release
	$(MAKE) -R -C .build/projects/gmake-ios-arm config=release
ios-arm: ios-arm-debug ios-arm-release ## Build - iOS ARM Debug and Release

.build/projects/gmake-ios-arm64:
	$(GENIE) --gcc=ios-arm64 gmake
ios-arm64-debug: .build/projects/gmake-ios-arm64 ## Build - iOS ARM64 Debug
	$(MAKE) -R -C .build/projects/gmake-ios-arm64 config=debug
ios-arm64-release: .build/projects/gmake-ios-arm64 ## Build - iOS ARM64 Release
	$(MAKE) -R -C .build/projects/gmake-ios-arm64 config=release
ios-arm64: ios-arm64-debug ios-arm64-release ## Build - iOS ARM64 Debug and Release

.build/projects/gmake-ios-simulator:
	$(GENIE) --gcc=ios-simulator gmake
ios-simulator-debug: .build/projects/gmake-ios-simulator ## Build - iOS Simulator Debug
	$(MAKE) -R -C .build/projects/gmake-ios-simulator config=debug
ios-simulator-release: .build/projects/gmake-ios-simulator ## Build - iOS Simulator Release
	$(MAKE) -R -C .build/projects/gmake-ios-simulator config=release
ios-simulator: ios-simulator-debug ios-simulator-release ## Build - iOS Simulator Debug and Release

.build/projects/gmake-ios-simulator64:
	$(GENIE) --gcc=ios-simulator64 gmake
ios-simulator64-debug: .build/projects/gmake-ios-simulator64 ## Build - iOS Simulator Debug
	$(MAKE) -R -C .build/projects/gmake-ios-simulator64 config=debug
ios-simulator64-release: .build/projects/gmake-ios-simulator64 ## Build - iOS Simulator Release
	$(MAKE) -R -C .build/projects/gmake-ios-simulator64 config=release
ios-simulator64: ios-simulator64-debug ios-simulator64-release ## Build - iOS Simulator Debug and Release

.build/projects/gmake-rpi:
	$(GENIE) --gcc=rpi gmake
rpi-debug: .build/projects/gmake-rpi ## Build - RasberryPi Debug
	$(MAKE) -R -C .build/projects/gmake-rpi config=debug
rpi-release: .build/projects/gmake-rpi ## Build - RasberryPi Release
	$(MAKE) -R -C .build/projects/gmake-rpi config=release
rpi: rpi-debug rpi-release ## Build - RasberryPi Debug and Release

build-darwin: osx-x64

build-linux: linux-debug64 linux-release64

build-windows: mingw-gcc

build: build-$(OS)

rebuild-shaders:
	$(MAKE) -R -C examples rebuild

assets: # Build assets.
	$(NINJA) -C scripts

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
BUILD_PROJECT_DIR=gmake-osx-x64
BUILD_OUTPUT_DIR=osx-x64
BUILD_TOOLS_CONFIG=release
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
	$(SILENT) $(MAKE) -C .build/projects/$(BUILD_PROJECT_DIR) geometryc config=$(BUILD_TOOLS_CONFIG)
	$(SILENT) cp .build/$(BUILD_OUTPUT_DIR)/bin/geometryc$(BUILD_TOOLS_SUFFIX)$(EXE) tools/bin/$(OS)/geometryc$(EXE)

geometryv: .build/projects/$(BUILD_PROJECT_DIR) ## Build geometryv tool.
	$(SILENT) $(MAKE) -C .build/projects/$(BUILD_PROJECT_DIR) geometryv config=$(BUILD_TOOLS_CONFIG)
	$(SILENT) cp .build/$(BUILD_OUTPUT_DIR)/bin/geometryv$(BUILD_TOOLS_SUFFIX)$(EXE) tools/bin/$(OS)/geometryv$(EXE)

shaderc: .build/projects/$(BUILD_PROJECT_DIR) ## Build shaderc tool.
	$(SILENT) $(MAKE) -C .build/projects/$(BUILD_PROJECT_DIR) shaderc config=$(BUILD_TOOLS_CONFIG)
	$(SILENT) cp .build/$(BUILD_OUTPUT_DIR)/bin/shaderc$(BUILD_TOOLS_SUFFIX)$(EXE) tools/bin/$(OS)/shaderc$(EXE)

texturec: .build/projects/$(BUILD_PROJECT_DIR) ## Build texturec tool.
	$(SILENT) $(MAKE) -C .build/projects/$(BUILD_PROJECT_DIR) texturec config=$(BUILD_TOOLS_CONFIG)
	$(SILENT) cp .build/$(BUILD_OUTPUT_DIR)/bin/texturec$(BUILD_TOOLS_SUFFIX)$(EXE) tools/bin/$(OS)/texturec$(EXE)

texturev: .build/projects/$(BUILD_PROJECT_DIR) ## Build texturev tool.
	$(SILENT) $(MAKE) -C .build/projects/$(BUILD_PROJECT_DIR) texturev config=$(BUILD_TOOLS_CONFIG)
	$(SILENT) cp .build/$(BUILD_OUTPUT_DIR)/bin/texturev$(BUILD_TOOLS_SUFFIX)$(EXE) tools/bin/$(OS)/texturev$(EXE)

tools: geometryc geometryv shaderc texturec texturev ## Build tools.

clean-tools: ## Clean tools projects.
	-$(SILENT) rm -r .build/projects/$(BUILD_PROJECT_DIR)

dist-windows: .build/projects/gmake-mingw-gcc
	$(SILENT) $(MAKE) -C .build/projects/gmake-mingw-gcc config=release64 -j 6 geometryc
	$(SILENT) cp .build/win64_mingw-gcc/bin/geometrycRelease.exe tools/bin/windows/geometryc.exe
	$(SILENT) $(MAKE) -C .build/projects/gmake-mingw-gcc config=release64 -j 6 geometryv
	$(SILENT) cp .build/win64_mingw-gcc/bin/geometryvRelease.exe tools/bin/windows/geometryv.exe
	$(SILENT) $(MAKE) -C .build/projects/gmake-mingw-gcc config=release64 -j 6 shaderc
	$(SILENT) cp .build/win64_mingw-gcc/bin/shadercRelease.exe   tools/bin/windows/shaderc.exe
	$(SILENT) $(MAKE) -C .build/projects/gmake-mingw-gcc config=release64 -j 6 texturec
	$(SILENT) cp .build/win64_mingw-gcc/bin/texturecRelease.exe  tools/bin/windows/texturec.exe
	$(SILENT) $(MAKE) -C .build/projects/gmake-mingw-gcc config=release64 -j 6 texturev
	$(SILENT) cp .build/win64_mingw-gcc/bin/texturevRelease.exe tools/bin/windows/texturev.exe

dist-linux: .build/projects/gmake-linux
	$(SILENT) $(MAKE) -C .build/projects/gmake-linux     config=release64 -j 6 geometryc
	$(SILENT) cp .build/linux64_gcc/bin/geometrycRelease tools/bin/linux/geometryc
	$(SILENT) $(MAKE) -C .build/projects/gmake-linux     config=release64 -j 6 geometryv
	$(SILENT) cp .build/linux64_gcc/bin/geometryvRelease tools/bin/linux/geometryv
	$(SILENT) $(MAKE) -C .build/projects/gmake-linux     config=release64 -j 6 shaderc
	$(SILENT) cp .build/linux64_gcc/bin/shadercRelease   tools/bin/linux/shaderc
	$(SILENT) $(MAKE) -C .build/projects/gmake-linux     config=release64 -j 6 texturec
	$(SILENT) cp .build/linux64_gcc/bin/texturecRelease  tools/bin/linux/texturec
	$(SILENT) $(MAKE) -C .build/projects/gmake-linux     config=release64 -j 6 texturev
	$(SILENT) cp .build/linux64_gcc/bin/texturevRelease  tools/bin/linux/texturev

dist-darwin: .build/projects/gmake-osx-x64
	$(SILENT) $(MAKE) -C .build/projects/gmake-osx-x64 config=release -j 6 geometryc
	$(SILENT) cp .build/osx-x64/bin/geometrycRelease tools/bin/darwin/geometryc
	$(SILENT) $(MAKE) -C .build/projects/gmake-osx-x64 config=release -j 6 geometryv
	$(SILENT) cp .build/osx-x64/bin/geometryvRelease tools/bin/darwin/geometryv
	$(SILENT) $(MAKE) -C .build/projects/gmake-osx-x64 config=release -j 6 shaderc
	$(SILENT) cp .build/osx-x64/bin/shadercRelease tools/bin/darwin/shaderc
	$(SILENT) $(MAKE) -C .build/projects/gmake-osx-x64 config=release -j 6 texturec
	$(SILENT) cp .build/osx-x64/bin/texturecRelease tools/bin/darwin/texturec
	$(SILENT) $(MAKE) -C .build/projects/gmake-osx-x64 config=release -j 6 texturev
	$(SILENT) cp .build/osx-x64/bin/texturevRelease tools/bin/darwin/texturev

dist: clean dist-windows dist-linux dist-darwin
