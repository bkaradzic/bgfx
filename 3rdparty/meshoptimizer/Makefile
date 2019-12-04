.SUFFIXES:
MAKEFLAGS+=-r

config=debug
files=demo/pirate.obj

BUILD=build/$(config)

LIBRARY_SOURCES=$(wildcard src/*.cpp)
LIBRARY_OBJECTS=$(LIBRARY_SOURCES:%=$(BUILD)/%.o)

DEMO_SOURCES=$(wildcard demo/*.c demo/*.cpp) tools/meshloader.cpp
DEMO_OBJECTS=$(DEMO_SOURCES:%=$(BUILD)/%.o)

GLTFPACK_SOURCES=tools/gltfpack.cpp tools/meshloader.cpp tools/basistoktx.cpp
GLTFPACK_OBJECTS=$(GLTFPACK_SOURCES:%=$(BUILD)/%.o)

OBJECTS=$(LIBRARY_OBJECTS) $(DEMO_OBJECTS) $(GLTFPACK_OBJECTS)

LIBRARY=$(BUILD)/libmeshoptimizer.a
EXECUTABLE=$(BUILD)/meshoptimizer

CFLAGS=-g -Wall -Wextra -Werror -std=c89
CXXFLAGS=-g -Wall -Wextra -Wshadow -Wno-missing-field-initializers -Werror -std=c++98
LDFLAGS=

WASM_SOURCES=src/vertexcodec.cpp src/indexcodec.cpp
WASM_EXPORTS=["_meshopt_decodeVertexBuffer","_meshopt_decodeIndexBuffer","_sbrk","__start"]
WASM_FLAGS=-O3 -DNDEBUG -s EXPORTED_FUNCTIONS='$(WASM_EXPORTS)' -s ALLOW_MEMORY_GROWTH=1 -s TOTAL_STACK=24576 -s TOTAL_MEMORY=65536

ifeq ($(config),iphone)
	IPHONESDK=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk
	CFLAGS+=-arch armv7 -arch arm64 -isysroot $(IPHONESDK)
	CXXFLAGS+=-arch armv7 -arch arm64 -isysroot $(IPHONESDK) -stdlib=libc++
	LDFLAGS+=-arch armv7 -arch arm64 -isysroot $(IPHONESDK) -L $(IPHONESDK)/usr/lib -mios-version-min=7.0
endif

ifeq ($(config),trace)
	CXXFLAGS+=-DTRACE=2
endif

ifeq ($(config),release)
	CXXFLAGS+=-O3 -DNDEBUG
endif

ifeq ($(config),coverage)
	CXXFLAGS+=-coverage
	LDFLAGS+=-coverage
endif

ifeq ($(config),sanitize)
	CXXFLAGS+=-fsanitize=address,undefined -fno-sanitize-recover=all
	LDFLAGS+=-fsanitize=address,undefined
endif

ifeq ($(config),analyze)
	CXXFLAGS+=--analyze
endif

all: $(EXECUTABLE)

test: $(EXECUTABLE)
	$(EXECUTABLE) $(files)

check: $(EXECUTABLE)
	$(EXECUTABLE)

dev: $(EXECUTABLE)
	$(EXECUTABLE) -d $(files)

format:
	clang-format -i $(LIBRARY_SOURCES) $(DEMO_SOURCES) $(GLTFPACK_SOURCES)

gltfpack: $(GLTFPACK_OBJECTS) $(LIBRARY)
	$(CXX) $^ $(LDFLAGS) -o $@

build/decoder_base.wasm: $(WASM_SOURCES)
	@mkdir -p build
	emcc $^ $(WASM_FLAGS) -o $@

build/decoder_simd.wasm: $(WASM_SOURCES)
	@mkdir -p build
	emcc $^ $(WASM_FLAGS) -o $@ -munimplemented-simd128 -mbulk-memory

js/meshopt_decoder.js: build/decoder_base.wasm build/decoder_simd.wasm
	sed -i "s#\(var wasm_base = \)\".*\";#\\1\"$$(cat build/decoder_base.wasm | hexdump -v -e '1/1 "%02X"')\";#" $@
	sed -i "s#\(var wasm_simd = \)\".*\";#\\1\"$$(cat build/decoder_simd.wasm | hexdump -v -e '1/1 "%02X"')\";#" $@

$(EXECUTABLE): $(DEMO_OBJECTS) $(LIBRARY)
	$(CXX) $^ $(LDFLAGS) -o $@

$(LIBRARY): $(LIBRARY_OBJECTS)
	ar rcs $@ $^

$(BUILD)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $< $(CXXFLAGS) -c -MMD -MP -o $@

$(BUILD)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -MMD -MP -o $@

-include $(OBJECTS:.o=.d)

clean:
	rm -rf $(BUILD)

.PHONY: all clean format
