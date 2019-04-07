#!/bin/bash

GLSLANG_REV=ef807f4bc543e061f25dbbee6cb64dd5053b2adc
SPIRV_TOOLS_REV=12e4a7b649e6fe28683de9fc352200c82948a1f0
SPIRV_HEADERS_REV=111a25e4ae45e2b4d7c18415e1d6884712b958c4

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

