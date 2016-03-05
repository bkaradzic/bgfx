#
# Copyright 2011-2016 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

BGFX_DIR=../../..
RUNTIME_DIR=$(BGFX_DIR)/examples/runtime
BUILD_DIR=../../.build

include $(BGFX_DIR)/scripts/tools.mk

GEOMETRY_SRC= \
	bunny \
	bunny_decimated \
	bunny_patched \
	column \
	cube \
	hollowcube \
	orb \
	platform \
	tree \
	tree1b_lod0_1 \
	tree1b_lod0_2 \
	tree1b_lod1_1 \
	tree1b_lod1_2 \
	tree1b_lod2_1 \
	tree1b_lod2_2

GEOMETRY_BIN=$(addprefix $(RUNTIME_DIR)/meshes/, $(addsuffix .bin, $(basename $(GEOMETRY_SRC))))

all: $(GEOMETRY_BIN)

clean:
	@echo Cleaning...
	@-rm -vf $(GEOMETRY_BIN)

rebuild: clean all

$(RUNTIME_DIR)/meshes/%.bin : %.obj
	$(SILENT) $(GEOMETRYC) -f $(<) -o $(@) --packnormal 1
