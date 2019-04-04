#!/bin/bash

GLSLANG_REV=a51d3d9f223361165127ded3cd2e59d81e22d91f
SPIRV_TOOLS_REV=bdcb155163d453fa67a03f59b4d5e00bd7c0f209
SPIRV_HEADERS_REV=03a081524afabdde274d885880c2fef213e46a59

if [ -d external/glslang ]; then
	echo "Updating glslang to revision $GLSLANG_REV."
	cd external/glslang
	git fetch origin
	git checkout $GLSLANG_REV
else
	echo "Cloning glslang revision $GLSLANG_REV."
	mkdir -p external
	cd external
	git clone git://github.com/KhronosGroup/glslang.git
	cd glslang
	git checkout $GLSLANG_REV
fi
cd ../..

if [ -d external/spirv-tools ]; then
	echo "Updating SPIRV-Tools to revision $SPIRV_TOOLS_REV."
	cd external/spirv-tools
	git fetch origin
	git checkout $SPIRV_TOOLS_REV
else
	echo "Cloning SPIRV-Tools revision $SPIRV_TOOLS_REV."
	mkdir -p external
	cd external
	git clone git://github.com/KhronosGroup/SPIRV-Tools.git spirv-tools
	cd spirv-tools
	git checkout $SPIRV_TOOLS_REV
fi

if [ -d external/spirv-headers ]; then
	cd external/spirv-headers
	git pull origin master
	git checkout $SPIRV_HEADERS_REV
	cd ../..
else
	git clone git://github.com/KhronosGroup/SPIRV-Headers.git external/spirv-headers
	cd external/spirv-headers
	git checkout $SPIRV_HEADERS_REV
	cd ../..
fi

cd ../..

