#
# Copyright 2011-2016 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

include ../../../scripts/shader-embeded.mk

droidsans.ttf.h: ../../runtime/font/droidsans.ttf
	@bin2c -f $(<) -o $(@) -n s_droidSansTtf

icons_font_awesome.ttf.h: ../../runtime/font/fontawesome-webfont.ttf
	@bin2c -f $(<) -o $(@) -n s_iconsFontAwesome

icons_kenney.ttf.h: ../../runtime/font/kenney-icon-font.ttf
	@bin2c -f $(<) -o $(@) -n s_iconsKenney

rebuild: droidsans.ttf.h icons_font_awesome.ttf.h icons_kenney.ttf.h
	@make -s --no-print-directory clean all
