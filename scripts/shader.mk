#
# Copyright 2011-2022 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
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
	@echo "  TARGET=0 (hlsl  - d3d9  / Windows only!)"
	@echo "  TARGET=1 (hlsl  - d3d11 / Windows only!)"
	@echo "  TARGET=3 (essl  - android)"
	@echo "  TARGET=4 (glsl)"
	@echo "  TARGET=5 (metal)"
	@echo "  TARGET=6 (pssl)"
	@echo "  TARGET=7 (spirv)"

.PHONY: build
build:
ifeq ($(OS), windows)
	@make -s --no-print-directory TARGET=0 all
	@make -s --no-print-directory TARGET=1 all
endif
	@make -s --no-print-directory TARGET=3 all
	@make -s --no-print-directory TARGET=4 all
	@make -s --no-print-directory TARGET=5 all
	@make -s --no-print-directory TARGET=7 all

.PHONY: clean
clean:
ifeq ($(OS), windows)
	@make -s --no-print-directory TARGET=0 clean
	@make -s --no-print-directory TARGET=1 clean
endif
	@make -s --no-print-directory TARGET=3 clean
	@make -s --no-print-directory TARGET=4 clean
	@make -s --no-print-directory TARGET=5 clean
	@make -s --no-print-directory TARGET=7 clean

.PHONY: rebuild
rebuild: clean build

else

ADDITIONAL_INCLUDES?=

ifeq ($(TARGET), 0)
VS_FLAGS=--platform windows -p vs_3_0 -O 3
FS_FLAGS=--platform windows -p ps_3_0 -O 3
SHADER_PATH=shaders/dx9
else
ifeq ($(TARGET), 1)
VS_FLAGS=--platform windows -p vs_5_0 -O 3
FS_FLAGS=--platform windows -p ps_5_0 -O 3
CS_FLAGS=--platform windows -p cs_5_0 -O 1
SHADER_PATH=shaders/dx11
else
ifeq ($(TARGET), 2)
VS_FLAGS=--platform nacl
FS_FLAGS=--platform nacl
SHADER_PATH=shaders/essl
else
ifeq ($(TARGET), 3)
VS_FLAGS=--platform android
FS_FLAGS=--platform android
CS_FLAGS=--platform android
SHADER_PATH=shaders/essl
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
else
ifeq ($(TARGET), 6)
VS_FLAGS=--platform orbis -p pssl
FS_FLAGS=--platform orbis -p pssl
CS_FLAGS=--platform orbis -p pssl
SHADER_PATH=shaders/pssl
else
ifeq ($(TARGET), 7)
VS_FLAGS=--platform linux -p spirv
FS_FLAGS=--platform linux -p spirv
CS_FLAGS=--platform linux -p spirv
SHADER_PATH=shaders/spirv
endif
endif
endif
endif
endif
endif
endif
endif

THISDIR := $(dir $(lastword $(MAKEFILE_LIST)))
VS_FLAGS+=-i $(THISDIR)../src/ $(ADDITIONAL_INCLUDES)
FS_FLAGS+=-i $(THISDIR)../src/ $(ADDITIONAL_INCLUDES)
CS_FLAGS+=-i $(THISDIR)../src/ $(ADDITIONAL_INCLUDES)

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

ifeq ($(TARGET), $(filter $(TARGET),1 3 4 5 6 7))
BIN += $(CS_BIN)
ASM += $(CS_ASM)
endif

$(BUILD_INTERMEDIATE_DIR)/vs_%.bin: $(SHADERS_DIR)vs_%.sc
	@echo [$(<)]
	$(SILENT) $(SHADERC) $(VS_FLAGS) --type vertex --depends -o $(@) -f $(<) --disasm
	$(SILENT) cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

$(BUILD_INTERMEDIATE_DIR)/fs_%.bin: $(SHADERS_DIR)fs_%.sc
	@echo [$(<)]
	$(SILENT) $(SHADERC) $(FS_FLAGS) --type fragment --depends -o $(@) -f $(<) --disasm
	$(SILENT) cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

$(BUILD_INTERMEDIATE_DIR)/cs_%.bin: $(SHADERS_DIR)cs_%.sc
	@echo [$(<)]
	$(SILENT) $(SHADERC) $(CS_FLAGS) --type compute --depends -o $(@) -f $(<) --disasm
	$(SILENT) cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

.PHONY: all
all: dirs $(BIN)
	@echo Target $(notdir $(CURDIR)) / $(SHADER_PATH)

.PHONY: clean
clean:
	@echo Cleaning...
	@-rm -vf $(BIN)

.PHONY: cleanall
cleanall:
	@echo Cleaning...
	@-$(call CMD_RMDIR,$(BUILD_INTERMEDIATE_DIR))

.PHONY: dirs
dirs:
	@-$(call CMD_MKDIR,$(BUILD_INTERMEDIATE_DIR))
	@-$(call CMD_MKDIR,$(BUILD_OUTPUT_DIR))

.PHONY: rebuild
rebuild: clean all

$(BIN) : | $(BUILD_INTERMEDIATE_DIR)

endif # TARGET

-include $(VS_DEPS)
-include $(FS_DEPS)
-include $(CS_DEPS)
