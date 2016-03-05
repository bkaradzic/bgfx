#
# Copyright 2011-2016 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

THISDIR:=$(dir $(lastword $(MAKEFILE_LIST)))
include $(THISDIR)/tools.mk

# Define SHADERS_DIR if your shader files are in a different dir than the makefile including this.
# Notice: If defined, SHADERS_DIR should end with dir slash '/'.
# Example:
#     SHADERS_DIR=shader_files/

ifndef TARGET
.PHONY: all
all:
	@echo Usage: make TARGET=# [clean, all, rebuild]
	@echo "  TARGET=0 (hlsl  - dx9)"
	@echo "  TARGET=1 (hlsl  - dx11)"
	@echo "  TARGET=2 (glsl  - nacl)"
	@echo "  TARGET=3 (glsl  - android)"
	@echo "  TARGET=4 (glsl  - linux)"
	@echo "  TARGET=5 (metal - OSX/iOS)"
	@echo "  VERBOSE=1 show build commands."
else

ifeq ($(TARGET), 0)
VS_FLAGS=--platform windows -p vs_3_0 -O 3
FS_FLAGS=--platform windows -p ps_3_0 -O 3
SHADER_PATH=shaders/dx9
else
ifeq ($(TARGET), 1)
VS_FLAGS=--platform windows -p vs_4_0 -O 3
FS_FLAGS=--platform windows -p ps_4_0 -O 3
CS_FLAGS=--platform windows -p cs_5_0 -O 1
SHADER_PATH=shaders/dx11
else
ifeq ($(TARGET), 2)
VS_FLAGS=--platform nacl
FS_FLAGS=--platform nacl
SHADER_PATH=shaders/gles
else
ifeq ($(TARGET), 3)
VS_FLAGS=--platform android
FS_FLAGS=--platform android
CS_FLAGS=--platform android
SHADER_PATH=shaders/gles
else
ifeq ($(TARGET), 4)
VS_FLAGS=--platform linux -p 120
FS_FLAGS=--platform linux -p 120
CS_FLAGS=--platform linux -p 430
SHADER_PATH=shaders/glsl
else
ifeq ($(TARGET), 5)
VS_FLAGS=--platform osx -p metal
FS_FLAGS=--platform osx -p metal
CS_FLAGS=--platform osx -p metal
SHADER_PATH=shaders/metal
endif
endif
endif
endif
endif
endif

THISDIR := $(dir $(lastword $(MAKEFILE_LIST)))
VS_FLAGS+=-i $(THISDIR)../src/
FS_FLAGS+=-i $(THISDIR)../src/
CS_FLAGS+=-i $(THISDIR)../src/

BUILD_OUTPUT_DIR=$(addprefix ./, $(RUNTIME_DIR)/$(SHADER_PATH))
BUILD_INTERMEDIATE_DIR=$(addprefix $(BUILD_DIR)/, $(SHADER_PATH))

VS_SOURCES=$(notdir $(wildcard $(addprefix $(SHADERS_DIR), vs_*.sc)))
VS_DEPS=$(addprefix $(BUILD_INTERMEDIATE_DIR)/,$(addsuffix .bin.d, $(basename $(notdir $(VS_SOURCES)))))

FS_SOURCES=$(notdir $(wildcard $(addprefix $(SHADERS_DIR), fs_*.sc)))
FS_DEPS=$(addprefix $(BUILD_INTERMEDIATE_DIR)/,$(addsuffix .bin.d, $(basename $(notdir $(FS_SOURCES)))))

CS_SOURCES=$(notdir $(wildcard $(addprefix $(SHADERS_DIR), cs_*.sc)))
CS_DEPS=$(addprefix $(BUILD_INTERMEDIATE_DIR)/,$(addsuffix .bin.d, $(basename $(notdir $(CS_SOURCES)))))

VS_BIN = $(addprefix $(BUILD_INTERMEDIATE_DIR)/, $(addsuffix .bin, $(basename $(notdir $(VS_SOURCES)))))
FS_BIN = $(addprefix $(BUILD_INTERMEDIATE_DIR)/, $(addsuffix .bin, $(basename $(notdir $(FS_SOURCES)))))
CS_BIN = $(addprefix $(BUILD_INTERMEDIATE_DIR)/, $(addsuffix .bin, $(basename $(notdir $(CS_SOURCES)))))

BIN = $(VS_BIN) $(FS_BIN)
ASM = $(VS_ASM) $(FS_ASM)

ifeq ($(TARGET), 1)
BIN += $(CS_BIN)
ASM += $(CS_ASM)
else
ifeq ($(TARGET), 3)
BIN += $(CS_BIN)
ASM += $(CS_ASM)
else
ifeq ($(TARGET), 4)
BIN += $(CS_BIN)
ASM += $(CS_ASM)
endif
endif
endif

$(BUILD_INTERMEDIATE_DIR)/vs_%.bin : $(SHADERS_DIR)vs_%.sc
	@echo [$(<)]
	$(SILENT) $(SHADERC) $(VS_FLAGS) --type vertex --depends -o $(@) -f $(<) --disasm
	$(SILENT) cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

$(BUILD_INTERMEDIATE_DIR)/fs_%.bin : $(SHADERS_DIR)fs_%.sc
	@echo [$(<)]
	$(SILENT) $(SHADERC) $(FS_FLAGS) --type fragment --depends -o $(@) -f $(<) --disasm
	$(SILENT) cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

$(BUILD_INTERMEDIATE_DIR)/cs_%.bin : $(SHADERS_DIR)cs_%.sc
	@echo [$(<)]
	$(SILENT) $(SHADERC) $(CS_FLAGS) --type compute --depends -o $(@) -f $(<) --disasm
	$(SILENT) cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

.PHONY: all
all: dirs $(BIN)
	@echo Target $(SHADER_PATH)

.PHONY: clean
clean:
	@echo Cleaning...
	@-rm -vf $(BIN)
	@-$(call CMD_RMDIR,$(BUILD_INTERMEDIATE_DIR))

.PHONY: dirs
dirs:
	@-$(call CMD_MKDIR,$(BUILD_INTERMEDIATE_DIR))
	@-$(call CMD_MKDIR,$(BUILD_OUTPUT_DIR))

.PHONY: rebuild
rebuild: clean all

endif # TARGET

-include $(VS_DEPS)
-include $(FS_DEPS)
-include $(CS_DEPS)
