#
# Copyright 2011-2019 Branimir Karadzic. All rights reserved.
# License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
#

SILENT?=@

THISDIR:=$(dir $(lastword $(MAKEFILE_LIST)))

UNAME:=$(shell uname)
ifeq ($(UNAME),$(filter $(UNAME),Linux Darwin))
CMD_MKDIR=if [ ! -d "$(1)" ]; then mkdir -p "$(1)"; fi
CMD_RMDIR=if [ -d "$(1)" ]; then rm -r "$(1)"; fi
ifeq ($(UNAME),$(filter $(UNAME),Darwin))
OS=darwin
else
OS=linux
endif
else
ifeq ($(findstring MINGW,$(UNAME)),MINGW)
CMD_MKDIR=if [ ! -d "$(1)" ]; then mkdir -p "$(1)"; fi
CMD_RMDIR=if [ -d "$(1)" ]; then rm -r "$(1)"; fi
else
CMD_MKDIR=cmd /C "if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))""
CMD_RMDIR=cmd /C "if exist "$(subst /,\,$(1))" rmdir /S /Q "$(subst /,\,$(1))""
endif
OS=windows
endif

SHADERC:="$(THISDIR)../tools/bin/$(OS)/shaderc"
GEOMETRYC:="$(THISDIR)../tools/bin/$(OS)/geometryc"
TEXTUREC:="$(THISDIR)../tools/bin/$(OS)/texturec"
