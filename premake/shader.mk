#
# Copyright 2011-2012 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

ifndef TARGET
.PHONY: all
all:;@echo Usage: make TARGET=# [clean]
	@echo 	TARGET=0 (hlsl - dx9)
	@echo 	TARGET=1 (hlsl - dx11)
	@echo 	TARGET=2 (glsl - nacl)
	@echo 	TARGET=3 (glsl - android)
	@echo 	TARGET=4 (glsl - linux)
else
SHADERC="$(BGFX_DIR)/tools/bin/shaderc"

ifeq ($(TARGET), 0)
VS_FLAGS=--platform windows -p vs_3_0 -O 3
FS_FLAGS=--platform windows -p ps_3_0 -O 3
SHADER_PATH=shaders/dx9
else
ifeq ($(TARGET), 1)
VS_FLAGS=--platform windows -p vs_4_0 -O 3
FS_FLAGS=--platform windows -p ps_4_0 -O 3
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
SHADER_PATH=shaders/gles
else
ifeq ($(TARGET), 4)
VS_FLAGS=--platform linux -p 140
FS_FLAGS=--platform linux -p 140
SHADER_PATH=shaders/glsl
endif
endif
endif
endif
endif

BUILD_OUTPUT_DIR=$(addprefix ./, $(RUNTIME_DIR)/$(SHADER_PATH))
BUILD_INTERMEDIATE_DIR=$(addprefix $(BGFX_DIR)/.build/, $(SHADER_PATH))

VS_SOURCES=$(wildcard vs_*.sc)
VS_DEPS=$(addprefix $(BUILD_INTERMEDIATE_DIR)/,$(addsuffix .bin.d, $(basename $(VS_SOURCES))))

FS_SOURCES=$(wildcard fs_*.sc)
FS_DEPS=$(addprefix $(BUILD_INTERMEDIATE_DIR)/,$(addsuffix .bin.d, $(basename $(FS_SOURCES))))

CMD_MKDIR=cmd /C "if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))""
CMD_RMDIR=cmd /C "if exist "$(subst /,\,$(1))" rmdir /S /Q "$(subst /,\,$(1))""

VS_BIN = $(addprefix $(BUILD_INTERMEDIATE_DIR)/, $(addsuffix .bin, $(basename $(VS_SOURCES))))
FS_BIN = $(addprefix $(BUILD_INTERMEDIATE_DIR)/, $(addsuffix .bin, $(basename $(FS_SOURCES))))

BIN = $(VS_BIN) $(FS_BIN)
ASM = $(VS_ASM) $(FS_ASM)

$(BUILD_INTERMEDIATE_DIR)/vs_%.bin : vs_%.sc
	@echo [$(<)]
	@$(SHADERC) $(VS_FLAGS) --type vertex --depends -o $(@) -f $(<) --disasm
	@cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

$(BUILD_INTERMEDIATE_DIR)/fs_%.bin : fs_%.sc
	@echo [$(<)]
	@$(SHADERC) $(FS_FLAGS) --type fragment --depends -o $(@) -f $(<) --disasm
	@cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

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
