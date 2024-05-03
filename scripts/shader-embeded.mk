#
# Copyright 2011-2024 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
#

THISDIR:=$(dir $(lastword $(MAKEFILE_LIST)))
include $(THISDIR)/tools.mk

VS_FLAGS+=-i $(THISDIR)../src/ --type vertex
FS_FLAGS+=-i $(THISDIR)../src/ --type fragment
CS_FLAGS+=-i $(THISDIR)../src/ --type compute

VS_SOURCES=$(wildcard vs_*.sc)
FS_SOURCES=$(wildcard fs_*.sc)
CS_SOURCES=$(wildcard cs_*.sc)

VS_BIN = $(addsuffix .bin.h, $(basename $(VS_SOURCES)))
FS_BIN = $(addsuffix .bin.h, $(basename $(FS_SOURCES)))
CS_BIN = $(addsuffix .bin.h, $(basename $(CS_SOURCES)))

BIN = $(VS_BIN) $(FS_BIN) $(CS_BIN)

SHADER_TMP = $(TEMP)/tmp

vs_%.bin.h : vs_%.sc
	@echo [$(<)]
	 $(SILENT) $(SHADERC) $(VS_FLAGS) --platform linux   -p 120         -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_glsl
	@cat "$(SHADER_TMP)" > $(@)
	-$(SILENT) $(SHADERC) $(VS_FLAGS) --platform android -p 100_es      -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_essl
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) $(VS_FLAGS) --platform linux   -p spirv       -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_spv
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) $(VS_FLAGS) --platform windows -p s_5_0 -O 3  -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_dx11
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) $(VS_FLAGS) --platform ios     -p metal -O 3  -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_mtl
	-@cat "$(SHADER_TMP)" >> $(@)
	-@printf "extern const uint8_t* $(basename $(<))_pssl;\n" | tr -d '\015' >> $(@)
	-@printf "extern const uint32_t $(basename $(<))_pssl_size;\n" | tr -d '\015' >> $(@)

fs_%.bin.h : fs_%.sc
	@echo [$(<)]
	 $(SILENT) $(SHADERC) $(FS_FLAGS) --platform linux   -p 120         -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_glsl
	@cat "$(SHADER_TMP)" > $(@)
	-$(SILENT) $(SHADERC) $(FS_FLAGS) --platform android -p 100_es      -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_essl
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) $(FS_FLAGS) --platform linux   -p spirv       -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_spv
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) $(FS_FLAGS) --platform windows -p s_5_0 -O 3  -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_dx11
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) $(FS_FLAGS) --platform ios     -p metal -O 3  -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_mtl
	-@cat "$(SHADER_TMP)" >> $(@)
	-@printf "extern const uint8_t* $(basename $(<))_pssl;\n" | tr -d '\015' >> $(@)
	-@printf "extern const uint32_t $(basename $(<))_pssl_size;\n" | tr -d '\015' >> $(@)

cs_%.bin.h : cs_%.sc
	@echo [$(<)]
	 $(SILENT) $(SHADERC) $(CS_FLAGS) --platform linux   -p 430         -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_glsl
	@cat "$(SHADER_TMP)" > $(@)
	-$(SILENT) $(SHADERC) $(CS_FLAGS) --platform android                -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_essl
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) $(CS_FLAGS) --platform linux   -p spirv       -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_spv
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) $(CS_FLAGS) --platform windows -p s_5_0 -O 1  -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_dx11
	-@cat "$(SHADER_TMP)" >> $(@)
	-@printf "extern const uint8_t* $(basename $(<))_pssl;\n" | tr -d '\015' >> $(@)
	-@printf "extern const uint32_t $(basename $(<))_pssl_size;\n" | tr -d '\015' >> $(@)

.PHONY: all
all: $(BIN)

.PHONY: clean
clean:
	@echo Cleaning...
	@-rm -vf $(BIN)

.PHONY: rebuild
rebuild: clean all
