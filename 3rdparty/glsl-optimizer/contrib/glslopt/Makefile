# Linux build for the sample app

OBJS = Main.o

.PHONY: clean all

LDFLAGS += -Wl,-O1 -Wl,-gc-sections
CPPFLAGS += -I ../../src/glsl -L ../../src/glsl
CXXFLAGS += -Wall -Os -s

all: $(OBJS)
	g++ -o glslopt Main.o $(CPPFLAGS) -lglslopt $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f glslopt $(OBJS)

