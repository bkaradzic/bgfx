#
# Copyright 2011-2020 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
#

SILENT?=@

THISDIR:=$(dir $(lastword $(MAKEFILE_LIST)))

UNAME:=$(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin))
CMD_MKDIR=mkdir -p "$(1)"
CMD_RMDIR=rm -r "$(1)"
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
OS=linux
endif
else
CMD_MKDIR=cmd /C "if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))""
CMD_RMDIR=cmd /C "if exist "$(subst /,\,$(1))" rmdir /S /Q "$(subst /,\,$(1))""
OS=windows
endif

SHADERC:="$(THISDIR)../tools/bin/$(OS)/shaderc"
GEOMETRYC:="$(THISDIR)../tools/bin/$(OS)/geometryc"
TEXTUREC:="$(THISDIR)../tools/bin/$(OS)/texturec"
