#
# Copyright 2013 Dario Manesku. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

BGFX_DIR=../..
RUNTIME_DIR=$(BGFX_DIR)/examples/runtime
BUILD_DIR=../../.build

include $(BGFX_DIR)/premake/shader.mk

geometry: ../runtime/meshes/bunny_patched.bin ../runtime/meshes/bunny_decimated.bin 

../runtime/meshes/bunny_patched.bin: bunny_patched.obj
	../../tools/bin/geometryc -f bunny_patched.obj -o ../runtime/meshes/bunny_patched.bin --packnormal 1

../runtime/meshes/bunny_decimated.bin: bunny_decimated.obj
	../../tools/bin/geometryc -f bunny_decimated.obj -o ../runtime/meshes/bunny_decimated.bin --packnormal 1

rebuild:
	@make -s --no-print-directory TARGET=0 clean all
	@make -s --no-print-directory TARGET=1 clean all
	@make -s --no-print-directory TARGET=2 clean all
	@make -s --no-print-directory TARGET=3 clean all
	@make -s --no-print-directory TARGET=4 clean all
