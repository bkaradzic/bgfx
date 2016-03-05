#
# Copyright 2011-2016 Branimir Karadzic. All rights reserved.
# License: http://www.opensource.org/licenses/BSD-2-Clause
#

include ../../../scripts/shader-embeded.mk

droidsans.ttf.h: ../../runtime/font/droidsans.ttf
	@bin2c -f $(<) -o $(@) -n s_droidSansTtf

rebuild: droidsans.ttf.h
	@make -s --no-print-directory clean all
