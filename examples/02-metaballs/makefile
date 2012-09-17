#
# Copyright 2011-2012 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

ifndef TARGET
.PHONY: all
all:;@echo Usage: make TARGET=# [clean]
	@echo 	TARGET=0 (dx9)
	@echo 	TARGET=2 (dx11)
	@echo 	TARGET=3 (nacl)
	@echo 	TARGET=4 (android)
	@echo 	TARGET=5 (linux)
else
SHADERC="../../../../tools/bin/shaderc"

EXT=sc

ifeq ($(TARGET), 0)
VS_FLAGS=--platform windows -p vs_2_0 -O 3
FS_FLAGS=--platform windows -p ps_2_a -O 3
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

BUILD_OUTPUT_DIR=$(addprefix ./, $(SHADER_PATH))
BUILD_INTERMEDIATE_DIR=$(addprefix ../../.build/, $(SHADER_PATH))

VS_SOURCES=$(wildcard vs_*.$(EXT))
VS_DEPS=$(addprefix $(BUILD_INTERMEDIATE_DIR)/,$(addsuffix .bin.d, $(basename $(VS_SOURCES))))

FS_SOURCES=$(wildcard fs_*.$(EXT))
FS_DEPS=$(addprefix $(BUILD_INTERMEDIATE_DIR)/,$(addsuffix .bin.d, $(basename $(FS_SOURCES))))

CMD_MKDIR=cmd /C "if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))""
CMD_RMDIR=cmd /C "if exist "$(subst /,\,$(1))" rmdir /S /Q "$(subst /,\,$(1))""

VS_BIN = $(addprefix $(BUILD_INTERMEDIATE_DIR)/, $(addsuffix .bin, $(basename $(VS_SOURCES))))
FS_BIN = $(addprefix $(BUILD_INTERMEDIATE_DIR)/, $(addsuffix .bin, $(basename $(FS_SOURCES))))

BIN = $(VS_BIN) $(FS_BIN)
ASM = $(VS_ASM) $(FS_ASM)

$(BUILD_INTERMEDIATE_DIR)/vs_%.bin : vs_%.$(EXT)
	@echo [$(<)]
	@$(SHADERC) $(VS_FLAGS) --type vertex --depends -o $(@) -f $(<)
	@cp $(@) $(BUILD_OUTPUT_DIR)/$(@F)

$(BUILD_INTERMEDIATE_DIR)/fs_%.bin : fs_%.$(EXT)
	@echo [$(<)]
	@$(SHADERC) $(FS_FLAGS) --type fragment --depends -o $(@) -f $(<)
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
