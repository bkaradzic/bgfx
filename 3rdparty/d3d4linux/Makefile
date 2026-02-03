
BINARIES = d3d4linux.exe test/compile-hlsl

INCLUDE = include/d3d4linux.h \
          include/d3d4linux_common.h \
          include/d3d4linux_enums.h \
          include/d3d4linux_impl.h \
          include/d3d4linux_types.h

CXXFLAGS += -O2 -Wall -I./include -std=c++11

ifeq ($(OS), Windows_NT)
CXX := x86_64-w64-mingw32-c++
LDFLAGS = -s -static-libgcc -static-libstdc++ -ldxguid -static -ld3dcompiler -static -lpthread
else
LDFLAGS = -g
endif

all: $(BINARIES)

d3d4linux.exe: d3d4linux.cpp $(INCLUDE) Makefile
	x86_64-w64-mingw32-c++ $(CXXFLAGS) $(filter %.cpp, $^) -static -o $@ -ldxguid

test/compile-hlsl: test/compile-hlsl.cpp $(INCLUDE) Makefile
	$(CXX) $(CXXFLAGS) $(filter %.cpp, $^) -o $@ $(LDFLAGS)

check: all
	D3D4LINUX_VERBOSE=1 \
        D3D4LINUX_WINE="/usr/bin/wine64" \
        D3D4LINUX_EXE="$(CURDIR)/d3d4linux.exe" \
        D3D4LINUX_DLL="z:$(CURDIR)/d3dcompiler_47.dll" \
        WINEPREFIX="$(CURDIR)/.wine" \
          ./test/compile-hlsl test/ps_sample.hlsl ps_main ps_4_0

clean:
	rm -f $(BINARIES)

