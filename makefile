#
# Copyright 2011-2024 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
#

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
OS=linux
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
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib                       vs2022
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=mingw-gcc       gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=mingw-clang     gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=linux-gcc       gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=linux-clang     gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=osx-arm64       gmake
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --xcode=osx           xcode9
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --xcode=ios           xcode9
	$(GENIE)              --with-combined-examples --with-shared-lib --gcc=android-arm64   gmake
	$(GENIE)              --with-combined-examples                   --gcc=ios-arm64       gmake
	$(GENIE)              --with-combined-examples                   --gcc=rpi             gmake

idl: ## Generate code from IDL.
	@echo Generating code from IDL.
	cd scripts && ../$(GENIE) idl

.build/projects/gmake-android-arm64:
	$(GENIE) --gcc=android-arm64 --with-combined-examples --with-shared-lib gmake
android-arm64-debug: .build/projects/gmake-android-arm64 ## Build - Android ARM64 Debug
	$(MAKE) -R -C .build/projects/gmake-android-arm64 config=debug
android-arm64-release: .build/projects/gmake-android-arm64 ## Build - Android ARM64 Release
	$(MAKE) -R -C .build/projects/gmake-android-arm64 config=release
android-arm64: android-arm64-debug android-arm64-release ## Build - Android ARM64 Debug and Release

.build/projects/gmake-wasm:
	$(GENIE) --gcc=wasm --with-combined-examples gmake
wasm-debug: .build/projects/gmake-wasm ## Build - Emscripten Debug
	$(MAKE) -R -C .build/projects/gmake-wasm config=debug
wasm-release: .build/projects/gmake-wasm ## Build - Emscripten Release
	$(MAKE) -R -C .build/projects/gmake-wasm config=release
wasm: wasm-debug wasm-release ## Build - Emscripten Debug and Release

.build/projects/gmake-linux-gcc:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=linux-gcc gmake
linux-gcc-debug64: .build/projects/gmake-linux-gcc ## Build - Linux GCC x64 Debug
	$(MAKE) -R -C .build/projects/gmake-linux-gcc config=debug64
linux-gcc-release64: .build/projects/gmake-linux-gcc ## Build - Linux GCC x64 Release
	$(MAKE) -R -C .build/projects/gmake-linux-gcc config=release64
linux-gcc: linux-gcc-debug64 linux-gcc-release64 ## Build - Linux GCC x86/x64 Debug and Release

.build/projects/gmake-linux-clang:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=linux-clang gmake
linux-clang-debug64: .build/projects/gmake-linux-clang ## Build - Linux Clang x64 Debug
	$(MAKE) -R -C .build/projects/gmake-linux-clang config=debug64
linux-clang-release64: .build/projects/gmake-linux-clang ## Build - Linux Clang x64 Release
	$(MAKE) -R -C .build/projects/gmake-linux-clang config=release64
linux-clang: linux-clang-debug64 linux-clang-release64 ## Build - Linux Clang x86/x64 Debug and Release

.build/projects/gmake-mingw-gcc:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=mingw-gcc gmake
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
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=mingw-clang gmake
mingw-clang-debug32: .build/projects/gmake-mingw-clang ## Build - MinGW Clang x86 Debug
	$(MAKE) -R -C .build/projects/gmake-mingw-clang config=debug32
mingw-clang-release32: .build/projects/gmake-mingw-clang ## Build - MinGW Clang x86 Release
	$(MAKE) -R -C .build/projects/gmake-mingw-clang config=release32
mingw-clang-debug64: .build/projects/gmake-mingw-clang ## Build - MinGW Clang x64 Debug
	$(MAKE) -R -C .build/projects/gmake-mingw-clang config=debug64
mingw-clang-release64: .build/projects/gmake-mingw-clang ## Build - MinGW Clang x64 Release
	$(MAKE) -R -C .build/projects/gmake-mingw-clang config=release64
mingw-clang: mingw-clang-debug32 mingw-clang-release32 mingw-clang-debug64 mingw-clang-release64 ## Build - MinGW Clang x86/x64 Debug and Release

.build/projects/vs2022:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib vs2022
vs2022-debug32: .build/projects/vs2022 ## Build - vs2022 x86 Debug
	devenv .build/projects/vs2022/bgfx.sln /Build "Debug|Win32"
vs2022-release32: .build/projects/vs2022 ## Build - vs2022 x86 Release
	devenv .build/projects/vs2022/bgfx.sln /Build "Release|Win32"
vs2022-debug64: .build/projects/vs2022 ## Build - vs2022 x64 Debug
	devenv .build/projects/vs2022/bgfx.sln /Build "Debug|x64"
vs2022-release64: .build/projects/vs2022 ## Build - vs2022 x64 Release
	devenv .build/projects/vs2022/bgfx.sln /Build "Release|x64"
vs2022: vs2022-debug32 vs2022-release32 vs2022-debug64 vs2022-release64 ## Build - vs2022 x86/x64 Debug and Release

.build/projects/gmake-osx-arm64:
	$(GENIE) --with-tools --with-combined-examples --with-shared-lib --gcc=osx-arm64 gmake
osx-arm64-debug: .build/projects/gmake-osx-arm64 ## Build - macOS ARM Debug
	$(MAKE) -C .build/projects/gmake-osx-arm64 config=debug
osx-arm64-release: .build/projects/gmake-osx-arm64 ## Build - macOS ARM Release
	$(MAKE) -C .build/projects/gmake-osx-arm64 config=release
osx-arm64: osx-arm64-debug osx-arm64-release ## Build - macOS ARM Debug and Release

.build/projects/gmake-ios-arm64:
	$(GENIE) --gcc=ios-arm64 gmake
ios-arm64-debug: .build/projects/gmake-ios-arm64 ## Build - iOS ARM64 Debug
	$(MAKE) -R -C .build/projects/gmake-ios-arm64 config=debug
ios-arm64-release: .build/projects/gmake-ios-arm64 ## Build - iOS ARM64 Release
	$(MAKE) -R -C .build/projects/gmake-ios-arm64 config=release
ios-arm64: ios-arm64-debug ios-arm64-release ## Build - iOS ARM64 Debug and Release

.build/projects/gmake-rpi:
	$(GENIE) --gcc=rpi gmake
rpi-debug: .build/projects/gmake-rpi ## Build - RasberryPi Debug
	$(MAKE) -R -C .build/projects/gmake-rpi config=debug
rpi-release: .build/projects/gmake-rpi ## Build - RasberryPi Release
	$(MAKE) -R -C .build/projects/gmake-rpi config=release
rpi: rpi-debug rpi-release ## Build - RasberryPi Debug and Release

###

SILENT ?= @

UNAME := $(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin))
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
BUILD_PROJECT_DIR=gmake-osx-arm64
BUILD_OUTPUT_DIR=osx-arm64
BUILD_TOOLS_CONFIG=release
BUILD_TOOLS_SUFFIX=Release
EXE=
else
OS=linux
BUILD_PROJECT_DIR=gmake-linux-gcc
BUILD_OUTPUT_DIR=linux64_gcc
BUILD_TOOLS_CONFIG=release64
BUILD_TOOLS_SUFFIX=Release
EXE=
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
