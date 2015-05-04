#
# Copyright 2013-2014 Dario Manesku. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

BGFX_DIR=../..
RUNTIME_DIR=$(BGFX_DIR)/examples/runtime
BUILD_DIR=../../.build

include $(BGFX_DIR)/scripts/shader.mk

GEOMETRY_SRC= \
	tree \
	hollowcube

GEOMETRY_BIN=$(addprefix $(RUNTIME_DIR)/meshes/, $(addsuffix .bin, $(basename $(GEOMETRY_SRC))))

geometry: $(GEOMETRY_BIN)

$(RUNTIME_DIR)/meshes/%.bin : %.obj
	$(SILENT) $(GEOMETRYC) -f $(<) -o $(@) --packnormal 1

rebuild:
	@make -s --no-print-directory TARGET=0 clean all
	@make -s --no-print-directory TARGET=1 clean all
	@make -s --no-print-directory TARGET=2 clean all
	@make -s --no-print-directory TARGET=3 clean all
	@make -s --no-print-directory TARGET=4 clean all
