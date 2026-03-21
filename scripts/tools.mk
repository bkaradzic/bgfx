#
# Copyright 2011-2026 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
#

SILENT?=@

THISDIR:=$(dir $(lastword $(MAKEFILE_LIST)))

UNAME:=$(shell uname)
ifeq ($(UNAME),$(filter Linux Darwin,$(UNAME)))
ifeq ($(UNAME),$(filter Darwin,$(UNAME)))
OS=darwin
else
OS=linux
endif
else ifeq ($(UNAME),$(filter MINGW%,$(UNAME)))
OS=windows
else
OS=windows
endif

ifneq ($(findstring sh,$(notdir $(SHELL))),)
CMD_MKDIR=mkdir -p "$(1)"
CMD_RMDIR=rm -rf "$(1)"
else
CMD_MKDIR=cmd /C "if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))""
CMD_RMDIR=cmd /C "if exist "$(subst /,\,$(1))" rmdir /S /Q "$(subst /,\,$(1))""
endif

SHADERC:="$(THISDIR)../tools/bin/$(OS)/shaderc"
GEOMETRYC:="$(THISDIR)../tools/bin/$(OS)/geometryc"
TEXTUREC:="$(THISDIR)../tools/bin/$(OS)/texturec"
