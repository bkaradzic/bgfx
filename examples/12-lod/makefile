#
# Copyright 2013 Milos Tosic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

BGFX_DIR=../..
RUNTIME_DIR=$(BGFX_DIR)/examples/runtime
BUILD_DIR=../../.build

include $(BGFX_DIR)/premake/shader.mk

GEOMETRY_SOURCES = \
		tree1b_lod0_1 \
		tree1b_lod0_2 \
		tree1b_lod1_1 \
		tree1b_lod1_2 \
		tree1b_lod2_1 \
		tree1b_lod2_2

GEOMETRY_BIN = $(addprefix ../runtime/meshes/, $(addsuffix .bin, $(basename $(GEOMETRY_SOURCES))))

geometry: $(GEOMETRY_BIN)

../runtime/meshes/%.bin : %.obj
	$(BGFX_DIR)/tools/bin/geometryc -f $(<) -o $(@) -s 0.1 --packnormal 1

rebuild:
	@make -s --no-print-directory TARGET=0 clean all
	@make -s --no-print-directory TARGET=1 clean all
	@make -s --no-print-directory TARGET=2 clean all
	@make -s --no-print-directory TARGET=3 clean all
	@make -s --no-print-directory TARGET=4 clean all
