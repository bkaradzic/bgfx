BINARIES = ../../tools/bin/windows/d3d4linux.exe

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

../../tools/bin/windows/d3d4linux.exe: d3d4linux.cpp $(INCLUDE) Makefile
	x86_64-w64-mingw32-c++ $(CXXFLAGS) $(filter %.cpp, $^) -static -o $@ -ldxguid

clean:
	rm -f $(BINARIES)
