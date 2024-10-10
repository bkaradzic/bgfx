#
# Copyright 2011-2024 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
#

THISDIR:=$(dir $(lastword $(MAKEFILE_LIST)))
include $(THISDIR)/../scripts/tools.mk

SHADER_TMP = $(TEMP)/tmp

BIN = vs_debugfont.bin.h \
	  fs_debugfont.bin.h \
	  vs_clear.bin.h \
	  fs_clear0.bin.h \
	  fs_clear1.bin.h \
	  fs_clear2.bin.h \
	  fs_clear3.bin.h \
	  fs_clear4.bin.h \
	  fs_clear5.bin.h \
	  fs_clear6.bin.h \
	  fs_clear7.bin.h \

.PHONY: all
all: $(BIN)

define shader-embedded
	@echo [$(<)]
	 $(SILENT) $(SHADERC) --type $(1) --platform linux   -p 120        -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_glsl
	 @cat "$(SHADER_TMP)" > $(@)
	-$(SILENT) $(SHADERC) --type $(1) --platform android -p 100_es     -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_essl
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) --type $(1) --platform linux   -p spirv      -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_spv
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) --type $(1) --platform windows -p $(2)  -O 3 -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_dx11
	-@cat "$(SHADER_TMP)" >> $(@)
	-$(SILENT) $(SHADERC) --type $(1) --platform ios     -p metal -O 3 -f $(<) -o "$(SHADER_TMP)" --bin2c $(basename $(<))_mtl
	-@cat "$(SHADER_TMP)" >> $(@)
	-@printf "extern const uint8_t* $(basename $(<))_pssl;\n" | tr -d '\015' >> $(@)
	-@printf "extern const uint32_t $(basename $(<))_pssl_size;\n" | tr -d '\015' >> $(@)
endef

vs_debugfont.bin.h : vs_debugfont.sc
	$(call shader-embedded, v, s_4_0)

fs_debugfont.bin.h : fs_debugfont.sc
	$(call shader-embedded, f, s_4_0)

vs_clear.bin.h : vs_clear.sc
	$(call shader-embedded, v, s_4_0)

fs_clear0.bin.h : fs_clear0.sc
	$(call shader-embedded, f, s_4_0)

fs_clear1.bin.h : fs_clear1.sc
	$(call shader-embedded, f, s_4_0)

fs_clear2.bin.h : fs_clear2.sc
	$(call shader-embedded, f, s_4_0)

fs_clear3.bin.h : fs_clear3.sc
	$(call shader-embedded, f, s_4_0)

fs_clear4.bin.h : fs_clear4.sc
	$(call shader-embedded, f, s_4_0)

fs_clear5.bin.h : fs_clear5.sc
	$(call shader-embedded, f, s_4_0)

fs_clear6.bin.h : fs_clear6.sc
	$(call shader-embedded, f, s_4_0)

fs_clear7.bin.h : fs_clear7.sc
	$(call shader-embedded, f, s_4_0)

.PHONY: clean
clean:
	@echo Cleaning...
	@-rm -vf $(BIN)

.PHONY: rebuild
rebuild: clean all
