#
# Copyright 2013 Dario Manesku. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

BGFX_DIR=../..
RUNTIME_DIR=$(BGFX_DIR)/examples/runtime
BUILD_DIR=../../.build

include $(BGFX_DIR)/premake/shader.mk

geometry: ../runtime/meshes/column.bin

../runtime/meshes/column.bin: column.obj
	../../tools/bin/geometryc -f column.obj -o ../runtime/meshes/column.bin --packnormal 1

rebuild:
	@make -s --no-print-directory TARGET=0 clean all
	@make -s --no-print-directory TARGET=1 clean all
	@make -s --no-print-directory TARGET=2 clean all
	@make -s --no-print-directory TARGET=3 clean all
	@make -s --no-print-directory TARGET=4 clean all
