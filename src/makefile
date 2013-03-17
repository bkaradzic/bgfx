#
# Copyright 2011-2013 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

.PHONY: all clean

all: vs_debugfont_dx9.bin.h fs_debugfont_dx9.bin.h \
	 vs_debugfont_glsl.bin.h fs_debugfont_glsl.bin.h \
	 vs_debugfont_dx11.bin.h fs_debugfont_dx11.bin.h \
	 vs_clear_dx11.bin.h fs_clear_dx11.bin.h

clean:
	rm *.bin.h

vs_debugfont_dx9.bin.h:
	..\tools\bin\shaderc -f vs_debugfont.sc -o vs_debugfont_dx9.bin.h --type v -p vs_2_0 --platform windows -O 3 --bin2c vs_debugfont_dx9

fs_debugfont_dx9.bin.h:
	..\tools\bin\shaderc -f fs_debugfont.sc -o fs_debugfont_dx9.bin.h --type f -p ps_2_a --platform windows -O 3 --bin2c fs_debugfont_dx9

vs_debugfont_glsl.bin.h:
	..\tools\bin\shaderc -f vs_debugfont.sc -o vs_debugfont_glsl.bin.h --type v --platform nacl -O 3 --bin2c vs_debugfont_glsl

fs_debugfont_glsl.bin.h:
	..\tools\bin\shaderc -f fs_debugfont.sc -o fs_debugfont_glsl.bin.h --type f --platform nacl -O 3 --bin2c fs_debugfont_glsl

vs_debugfont_dx11.bin.h:
	..\tools\bin\shaderc -f vs_debugfont.sc -o vs_debugfont_dx11.bin.h --type v -p vs_5_0 --platform windows -O 3 --bin2c vs_debugfont_dx11

fs_debugfont_dx11.bin.h:
	..\tools\bin\shaderc -f fs_debugfont.sc -o fs_debugfont_dx11.bin.h --type f -p ps_5_0 --platform windows -O 3 --bin2c fs_debugfont_dx11

vs_clear_dx11.bin.h:
	..\tools\bin\shaderc -f vs_clear.sc -o vs_clear_dx11.bin.h --type v -p vs_5_0 --platform windows -O 3 --bin2c vs_clear_dx11

fs_clear_dx11.bin.h:
	..\tools\bin\shaderc -f fs_clear.sc -o fs_clear_dx11.bin.h --type f -p ps_5_0 --platform windows -O 3 --bin2c fs_clear_dx11
