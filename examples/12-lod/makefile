#
# Copyright 2013 Milos Tosic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

BGFX_DIR=../..
RUNTIME_DIR=$(BGFX_DIR)/examples/runtime
BUILD_DIR=../../.build

include $(BGFX_DIR)/premake/shader.mk

geometry:	../runtime/meshes/tree1b_lod0_1.bin
		../runtime/meshes/tree1b_lod0_2.bin
		../runtime/meshes/tree1b_lod1_1.bin
		../runtime/meshes/tree1b_lod1_2.bin
		../runtime/meshes/tree1b_lod2_1.bin
		../runtime/meshes/tree1b_lod2_2.bin			

../runtime/meshes/tree1b_lod0_1.bin: tree1b_lod0_1.obj
	..\..\tools\bin\geometryc -f tree1b_lod0_1.obj -o ..\runtime\meshes\tree1b_lod0_1.bin -s 0.1 --packnormal 1

../runtime/meshes/tree1b_lod0_2.bin: tree1b_lod0_2.obj
	..\..\tools\bin\geometryc -f tree1b_lod0_2.obj -o ..\runtime\meshes\tree1b_lod0_2.bin -s 0.1 --packnormal 1

../runtime/meshes/tree1b_lod1_1.bin: tree1b_lod1_1.obj
	..\..\tools\bin\geometryc -f tree1b_lod1_1.obj -o ..\runtime\meshes\tree1b_lod1_1.bin -s 0.1 --packnormal 1

../runtime/meshes/tree1b_lod1_2.bin: tree1b_lod1_2.obj
	..\..\tools\bin\geometryc -f tree1b_lod1_2.obj -o ..\runtime\meshes\tree1b_lod1_2.bin -s 0.1 --packnormal 1

../runtime/meshes/tree1b_lod2_1.bin: tree1b_lod2_1.obj
	..\..\tools\bin\geometryc -f tree1b_lod2_1.obj -o ..\runtime\meshes\tree1b_lod2_1.bin -s 0.1 --packnormal 1

../runtime/meshes/tree1b_lod2_2.bin: tree1b_lod2_2.obj
	..\..\tools\bin\geometryc -f tree1b_lod2_2.obj -o ..\runtime\meshes\tree1b_lod2_2.bin -s 0.1 --packnormal 1

rebuild:
	@make -s --no-print-directory TARGET=0 clean all
	@make -s --no-print-directory TARGET=1 clean all
	@make -s --no-print-directory TARGET=2 clean all
	@make -s --no-print-directory TARGET=3 clean all
	@make -s --no-print-directory TARGET=4 clean all

