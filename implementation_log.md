# D3D4Linux Integration - Implementation Log

**Branch:** feature/d3d4linux-integration  
**Issue:** #1869  
**Started:** February 3, 2026

---

## 2026-02-03: Project Initialization

### Branch Creation
- Created new branch: `feature/d3d4linux-integration`
- Base branch: `master`

### Documentation
- Created comprehensive proposal document: `PROPOSAL_D3D_LINUX.md`
- Created this implementation log for tracking progress

---

## 2026-02-03: Wine Setup and Verification

### Wine Installation Check
- Verified Wine 9.0 is installed on the system (Ubuntu 24.04)
- Wine version: `wine-9.0 (Ubuntu 9.0~repack-4build3)`
- Architecture: 64-bit (amd64)

### Wine Testing
- Successfully tested Wine with notepad application
- Command: `WINEARCH=win64 wine notepad`
- Result: ✅ Notepad launched successfully
- Note: wine32 warnings can be ignored - d3d4linux only requires 64-bit Wine support

### System Configuration
- **OS:** Ubuntu 24.04 (Noble)
- **Architecture:** amd64 with i386 support
- **Wine packages installed:**
  - wine (9.0~repack-4build3)
  - wine64 (9.0~repack-4build3)
  - libwine (9.0~repack-4build3)
  - fonts-wine
  - winetricks

### D3D4Linux Integration
- Cloned d3d4linux repository into `3rdparty/d3d4linux/`
- Using latest commit: `c9b1ca9` (Handle D3DReflect() regardless of d3dcompiler DLL version)
- Removed `.git` directory to match bgfx third-party dependency structure
- Files included:
  - `d3d4linux.cpp` - Main wrapper implementation
  - `d3dcompiler_43.dll` - Microsoft D3D compiler (64-bit)
  - `d3dcompiler_47.dll` - Microsoft D3D compiler (Windows 8 SDK)
  - `include/` - Header files
  - `Makefile` - Build configuration
  - `test/` - Test files

**Commit:** `2bc66540f` - "Add d3d4linux to 3rdparty for Linux HLSL shader compilation"

### Next Steps
- ✅ Clone d3d4linux into 3rdparty/
- Build d3d4linux for use with bgfx shaderc
- Modify shaderc source files for conditional HLSL compilation
- Update build system (scripts/shaderc.lua)
- Test HLSL shader compilation on Linux

---

## 2026-02-03: Wine Upgrade and D3D4Linux Testing

### Wine Dependency Issue
- Discovered `ppa:libretro/testing` had libzstd1 1.5.8-dev without matching i386 version
- This prevented WineHQ packages from installing (required matching 32/64-bit libraries)
- Removed the PPA: `sudo add-apt-repository --remove ppa:libretro/testing`
- Downgraded libzstd1 to official Ubuntu version: `1.5.5+dfsg2-2build1.1`

### Wine Upgrade
- Removed Ubuntu Wine 9.0 packages
- Installed WineHQ Wine 11.0 Stable from official repository
- Installed packages:
  - `winehq-stable` (11.0.0.0~noble-1)
  - `wine-stable-amd64` (11.0.0.0~noble-1)
  - `wine-stable-i386` (11.0.0.0~noble-1)

### Wine Components Installed
- Wine Mono Runtime (10.4.1) - downloaded from dl.winehq.org
- Wine Mono Windows Support
- Wine Gecko 32-bit (2.47.4)
- Wine Gecko 64-bit (2.47.4)

### D3D4Linux Build
- Built d3d4linux with `make` in `3rdparty/d3d4linux/`
- Created: `d3d4linux.exe` (545 KB) - Wine-based wrapper
- Created: `test/compile-hlsl` (481 KB) - Test utility

### D3D4Linux Test Results
- Command: `D3D4LINUX_EXE="$(pwd)/d3d4linux.exe" D3D4LINUX_WINE="/usr/bin/wine" ./test/compile-hlsl test/ps_sample.hlsl ps_main ps_5_0`
- **D3DCompile:** ✅ SUCCESS (Result: 0x0)
- Bytecode generated successfully (DXBC header visible in output)
- **D3DReflect:** ❌ Crashed with `std::bad_alloc`
- Note: D3DCompile is the critical function for shaderc - it works!
- The D3DReflect crash is in the test program, not the core compilation

### Conclusion
- HLSL shader compilation on Linux via Wine works
- Ready to proceed with shaderc integration

---

## 2026-02-03: D3D4Linux Struct Fix for Full Functionality

### Problem Analysis
- D3DReflect was crashing with `std::bad_alloc` after returning success (0x0) from Wine
- Investigation revealed a **struct size mismatch** between Windows and Linux sides

### Root Cause
The `D3D11_SIGNATURE_PARAMETER_DESC` struct in d3d4linux was **outdated**:

- d3d4linux was written in 2016 against older DirectX SDK headers
- The bundled `d3dcompiler_47.dll` (Windows 8 SDK) uses newer struct layouts
- Microsoft added `D3D_MIN_PRECISION MinPrecision` field in later SDK versions

**Struct Size Comparison:**

| Struct | Windows (64-bit) | d3d4linux (before fix) |
|--------|------------------|------------------------|
| D3D11_SHADER_DESC | 160 bytes | 160 bytes ✓ |
| D3D11_SIGNATURE_PARAMETER_DESC | **40 bytes** | **32 bytes** ❌ |
| D3D11_SHADER_INPUT_BIND_DESC | 40 bytes | 40 bytes ✓ |
| D3D11_SHADER_BUFFER_DESC | 24 bytes | 24 bytes ✓ |
| D3D11_SHADER_VARIABLE_DESC | 48 bytes | 48 bytes ✓ |

The 8-byte difference in `D3D11_SIGNATURE_PARAMETER_DESC` caused deserialization to read garbage values, leading to memory allocation failures.

### Fix Applied
Modified two files in `3rdparty/d3d4linux/include/`:

**1. d3d4linux_enums.h** - Added missing enum:
```cpp
typedef enum D3D_MIN_PRECISION
{
    D3D_MIN_PRECISION_DEFAULT = 0,
    D3D_MIN_PRECISION_FLOAT_16 = 1,
    D3D_MIN_PRECISION_FLOAT_2_8 = 2,
    D3D_MIN_PRECISION_RESERVED = 3,
    D3D_MIN_PRECISION_SINT_16 = 4,
    D3D_MIN_PRECISION_UINT_16 = 5,
    D3D_MIN_PRECISION_ANY_16 = 0xf0,
    D3D_MIN_PRECISION_ANY_10 = 0xf1,
}
D3D_MIN_PRECISION;
```

**2. d3d4linux_types.h** - Added missing field:
```cpp
struct D3D11_SIGNATURE_PARAMETER_DESC
{
    char const *SemanticName;             // 8 bytes (pointer)
    uint32_t SemanticIndex;               // 4 bytes
    uint32_t Register;                    // 4 bytes
    D3D_NAME SystemValueType;             // 4 bytes (enum)
    D3D_REGISTER_COMPONENT_TYPE ComponentType; // 4 bytes (enum)
    uint8_t Mask;                         // 1 byte
    uint8_t ReadWriteMask;                // 1 byte
    uint8_t _padding[2];                  // 2 bytes padding for alignment
    uint32_t Stream;                      // 4 bytes
    D3D_MIN_PRECISION MinPrecision;       // 4 bytes (enum) + 4 bytes padding = 40 total
};
```

### Build and Test
Standard build command:
```bash
cd 3rdparty/d3d4linux
make clean && make
```

Test command:
```bash
D3D4LINUX_VERBOSE=1 \
D3D4LINUX_WINE="/usr/bin/wine" \
D3D4LINUX_EXE="$PWD/d3d4linux.exe" \
D3D4LINUX_DLL="z:$PWD/d3dcompiler_47.dll" \
./test/compile-hlsl test/ps_sample.hlsl ps_main ps_4_0
```

### Final Test Results - All Functions Working

| Function | Result | Status |
|----------|--------|--------|
| D3DCompile | 0x0 | ✅ SUCCESS |
| D3DReflect | 0x0 | ✅ SUCCESS |
| D3DStripShader | 0x0 | ✅ SUCCESS |
| D3DDisassemble | 0x0 | ✅ SUCCESS |

**Sample Output:**
```
Creator: Microsoft (R) HLSL Shader Compiler 6.3.9600.16384
Input Parameters (2):
  0: NORMAL (0)
  1: TEXCOORD (0)
Output Parameters (1):
  0: SV_TARGET (0)
Bound Resources (3):
  0: g_samLinear
  1: g_txDiffuse
  2: cbPerFrame
Constant Buffers (1):
  0: cbPerFrame (2 variables):
    0: g_vLightDir (12 bytes)
    1: g_fAmbient (4 bytes)
```

### Environment
- **OS:** Ubuntu 24.04.3 LTS (Noble)
- **Wine:** WineHQ Wine 11.0 Stable
- **Wine Mono:** 10.4.1
- **Wine Gecko:** 2.47.4 (32-bit and 64-bit)
- **Cross Compiler:** x86_64-w64-mingw32-c++

### Notes
- The upstream d3d4linux repository (samhocevar/d3d4linux) has not been updated in 10 years
- No issues were filed about this struct mismatch on the upstream repo
- Modern Wine (11.0) uses unified `wine` command - no separate `wine64`
- The fix is specific to d3dcompiler_47.dll; d3dcompiler_43.dll may use older struct layouts

---

## 2026-02-03: DirectX Shader Compiler Research

### Legacy vs Modern HLSL Compilers

Microsoft has two HLSL compilation paths:

#### Legacy Path (FXC - d3dcompiler_47.dll)
- **Compiler:** fxc.exe / d3dcompiler_47.dll
- **Shader Models:** SM 2.0 - SM 5.1
- **Status:** Maintenance mode, version 47 is the final version number
- **d3d4linux:** Currently supports this path via Wine

#### Modern Path (DXC - dxcompiler.dll)
- **Compiler:** dxc.exe / dxcompiler.dll / dxil.dll
- **Shader Models:** SM 6.0+ (DXIL format)
- **Status:** Actively developed, open-source on GitHub
- **Repository:** https://github.com/microsoft/DirectXShaderCompiler
- **Latest Release:** v1.8.2505.1 (May 2025 Patch 1)
- **Features:** SPIR-V codegen, Metal codegen (experimental)

### bgfx Shader Model Support
- bgfx currently supports SM 4.0 - SM 5.0 for D3D11
- SM 6.0+ (DXC) would be needed for D3D12 advanced features
- For this issue (#1869), legacy d3dcompiler_47.dll is sufficient

### Decision
- Keep legacy d3dcompiler_47.dll for SM 2.0 - 5.1 (covers bgfx needs)
- DXC has native Linux support (libdxcompiler.so) - doesn't require Wine
- For future SM 6.0+ support, use native Linux DXC directly

---

## 2026-02-03: bgfx Shader Compilation Pipeline - Comprehensive Analysis

### Overview
The bgfx shader compilation system is a sophisticated cross-platform pipeline that transforms platform-agnostic shader source code (.sc files) into binary shader blobs for all supported graphics APIs.

### Architecture Summary
```
┌──────────────────────────────────────────────────────────────────────────┐
│                        bgfx Shader Pipeline                              │
├──────────────────────────────────────────────────────────────────────────┤
│                                                                          │
│  Input: .sc files (bgfx shader language - GLSL-like syntax)              │
│                                                                          │
│         vs_shader.sc                  fs_shader.sc                       │
│         varying.def.sc (attribute/varying definitions)                   │
│              │                              │                            │
│              ▼                              ▼                            │
│  ┌──────────────────────────────────────────────────────────────┐       │
│  │                    SHADERC (tools/shaderc/)                   │       │
│  │                                                               │       │
│  │  1. Preprocessing (fcpp - 3rdparty/fcpp/)                    │       │
│  │  2. varying.def.sc parsing → attribute/varying mapping       │       │
│  │  3. Platform-specific code transformation                    │       │
│  │  4. Backend compilation dispatch                             │       │
│  └───────────────────────────┬──────────────────────────────────┘       │
│                              │                                           │
│              ┌───────────────┼───────────────┐                          │
│              ▼               ▼               ▼                          │
│  ┌─────────────────┐ ┌─────────────────┐ ┌─────────────────┐            │
│  │   GLSL/ESSL     │ │      HLSL       │ │    SPIR-V       │            │
│  │  (glsl-optimizer)│ │  (D3DCompiler)  │ │   (glslang)     │            │
│  └─────────────────┘ └─────────────────┘ └─────────────────┘            │
│          │                   │                   │                       │
│          │                   │                   ▼                       │
│          │                   │           ┌─────────────────┐            │
│          │                   │           │   spirv-cross   │            │
│          │                   │           │  (Metal output) │            │
│          │                   │           └─────────────────┘            │
│          ▼                   ▼                   ▼                       │
│  ┌────────────────────────────────────────────────────────────┐         │
│  │                   OUTPUT: .bin shader blobs                 │         │
│  │  - BGFX_CHUNK_MAGIC_VSH (vertex)                           │         │
│  │  - BGFX_CHUNK_MAGIC_FSH (fragment)                         │         │
│  │  - BGFX_CHUNK_MAGIC_CSH (compute)                          │         │
│  └────────────────────────────────────────────────────────────┘         │
└──────────────────────────────────────────────────────────────────────────┘
```

### Core Components

#### 1. Shaderc Tool (tools/shaderc/)

| File | Purpose |
|------|---------|
| shaderc.h | Header with Options struct, Uniform types, compiler function declarations |
| shaderc.cpp | Main entry point, command-line parsing, preprocessing, platform dispatch (2936 lines) |
| shaderc_hlsl.cpp | HLSL compilation via D3DCompiler DLL (Windows-only, 865 lines) |
| shaderc_glsl.cpp | GLSL compilation via glsl-optimizer (405 lines) |
| shaderc_spirv.cpp | SPIR-V compilation via glslang + spirv-tools (904 lines) |
| shaderc_metal.cpp | Metal compilation via SPIR-V → spirv-cross (822 lines) |
| shaderc_pssl.cpp | PlayStation Shader Language (stub for open-source) |

#### 2. Shader Language (src/)

| File | Purpose |
|------|---------|
| bgfx_shader.sh | Shader library with cross-platform macros and helper functions |
| bgfx_compute.sh | Compute shader helpers |
| varying.def.sc | Default varying definitions template |

#### 3. 3rd Party Dependencies (3rdparty/)

| Dependency | Used By | Purpose |
|------------|---------|---------|
| fcpp/ | Preprocessor | C preprocessor for shader preprocessing |
| glsl-optimizer/ | GLSL backend | Mesa-based GLSL optimizer |
| glslang/ | SPIR-V backend | Khronos reference HLSL/GLSL → SPIR-V compiler |
| spirv-tools/ | SPIR-V backend | SPIR-V validation and optimization |
| spirv-cross/ | Metal backend | SPIR-V → Metal/GLSL cross-compiler |
| dxsdk/include/ | HLSL backend | DirectX SDK headers |

### HLSL Compilation Path - Deep Dive

This is the critical path for d3d4linux integration.

**Location:** `tools/shaderc/shaderc_hlsl.cpp`

#### Configuration Guard
```cpp
#ifndef SHADERC_CONFIG_HLSL
#	define SHADERC_CONFIG_HLSL BX_PLATFORM_WINDOWS
#endif
```
**CRITICAL:** HLSL is Windows-only by default! We must change this.

#### DLL Loading (lines 65-112)
```cpp
static const D3DCompiler s_d3dcompiler[] = {
    { "D3DCompiler_47.dll", { IID_ID3D11ShaderReflection47 } },
    { "D3DCompiler_46.dll", { IID_ID3D11ShaderReflection } },
    { "D3DCompiler_45.dll", { IID_ID3D11ShaderReflection } },
    // ...
};

const D3DCompiler* load(bx::WriterI* _messageWriter) {
    for (uint32_t ii = 0; ii < BX_COUNTOF(s_d3dcompiler); ++ii) {
        s_d3dcompilerdll = bx::dlopen(compiler->fileName);  // Native DLL load
        if (s_d3dcompilerdll) {
            D3DCompile     = (PFN_D3D_COMPILE)bx::dlsym(s_d3dcompilerdll, "D3DCompile");
            D3DDisassemble = (PFN_D3D_DISASSEMBLE)bx::dlsym(s_d3dcompilerdll, "D3DDisassemble");
            D3DReflect     = (PFN_D3D_REFLECT)bx::dlsym(s_d3dcompilerdll, "D3DReflect");
            D3DStripShader = (PFN_D3D_STRIP_SHADER)bx::dlsym(s_d3dcompilerdll, "D3DStripShader");
            return compiler;
        }
    }
}
```

**CURRENT BEHAVIOR:** Uses native Windows `bx::dlopen` which maps to `LoadLibrary`.
**NEEDED FOR LINUX:** Replace with d3d4linux function calls.

#### Required Functions

| Function | Purpose | d3d4linux Support |
|----------|---------|-------------------|
| D3DCompile | Compile HLSL source to DXBC bytecode | ✅ Yes |
| D3DReflect | Extract metadata (uniforms, samplers, semantics) | ✅ Yes (fixed) |
| D3DStripShader | Remove debug/reflection data from bytecode | ✅ Yes |
| D3DDisassemble | Convert bytecode to readable text (optional) | ✅ Yes |

#### Reflection Data Extraction (lines 282-400)
The `getReflectionDataD3D11()` function uses `ID3D11ShaderReflection` interface:
```cpp
ID3D11ShaderReflection* reflect = NULL;
hr = D3DReflect(code->GetBufferPointer(), code->GetBufferSize(), 
                IID_ID3D11ShaderReflection, (void**)&reflect);

// Extract shader description
D3D11_SHADER_DESC desc;
reflect->GetDesc(&desc);

// Get input parameters (for vertex attributes)
for (uint32_t ii = 0; ii < desc.InputParameters; ++ii) {
    D3D11_SIGNATURE_PARAMETER_DESC spd;
    reflect->GetInputParameterDesc(ii, &spd);
}

// Get constant buffer uniforms
for (uint32_t jj = 0; jj < bufferDesc.Variables; ++jj) {
    ID3D11ShaderReflectionVariable* var = cbuffer->GetVariableByIndex(jj);
    D3D11_SHADER_VARIABLE_DESC varDesc;
    var->GetDesc(&varDesc);
}

// Get bound resources (samplers/textures)
for (uint32_t ii = 0; ii < desc.BoundResources; ++ii) {
    D3D11_SHADER_INPUT_BIND_DESC bindDesc;
    reflect->GetResourceBindingDesc(ii, &bindDesc);
}
```
**d3d4linux provides:** All these structs and interfaces via IPC to Wine.

### Shader Profile Mapping

From `shaderc.cpp` lines 107-145:

| Profile | Lang | ID | Description |
|---------|------|-----|-------------|
| s_4_0 | HLSL | 400 | Shader Model 4.0 (D3D10) |
| s_5_0 | HLSL | 500 | Shader Model 5.0 (D3D11) |
| spirv | SPIR-V | 1010 | Vulkan 1.0 |
| metal | Metal | 1210 | Metal 1.2 |
| 100_es | ESSL | 100 | OpenGL ES 2.0 |
| 300_es | ESSL | 300 | OpenGL ES 3.0 |
| 120-440 | GLSL | 120-440 | OpenGL 2.1-4.4 |

**Target for D3D shaders:** `s_4_0` (SM 4.0) and `s_5_0` (SM 5.0)

### Build System - scripts/shaderc.lua

Key sections for modification:
```lua
-- Line 540: shaderc project definition
project "shaderc"
    kind "ConsoleApp"
    
    includedirs {
        path.join(BGFX_DIR, "3rdparty/dxsdk/include"),  -- Windows only
        -- ...
    }
    
    files {
        path.join(BGFX_DIR, "tools/shaderc/**.cpp"),
        path.join(BGFX_DIR, "tools/shaderc/**.h"),
    }
```

**Needed changes:**
1. Add d3d4linux include path on Linux
2. Link with d3d4linux library on Linux
3. Set `SHADERC_CONFIG_HLSL=1` on Linux when using d3d4linux

### Shader Compilation Flow (runtime)

From `scripts/shader.mk`:
```makefile
# TARGET=0 or 1: Windows D3D11 shaders
VS_FLAGS=--platform windows -p s_5_0 -O 3
FS_FLAGS=--platform windows -p s_5_0 -O 3
SHADER_PATH=shaders/dx11

# Command executed:
$(SHADERC) $(VS_FLAGS) --type vertex -o $@ -f $< --disasm
```

The makefile currently only enables D3D11 target on Windows:
```makefile
.PHONY: build
build:
ifeq ($(OS), windows)
	@make -s --no-print-directory TARGET=0 all
	@make -s --no-print-directory TARGET=1 all
endif
	@make -s --no-print-directory TARGET=3 all  # ESSL
	@make -s --no-print-directory TARGET=4 all  # GLSL
```

### Integration Points for d3d4linux

#### Option A: Replace DLL Loading (Minimal Changes)

Modify `shaderc_hlsl.cpp` to use d3d4linux functions instead of native DLL loading:

```cpp
#if BX_PLATFORM_LINUX
#include <d3d4linux.h>

const D3DCompiler* load(bx::WriterI* _messageWriter) {
    // d3d4linux provides these functions directly
    D3DCompile     = ::D3DCompile;
    D3DReflect     = ::D3DReflect;
    D3DStripShader = ::D3DStripShader;
    D3DDisassemble = ::D3DDisassemble;
    
    static D3DCompiler compiler = { 
        "d3d4linux",
        { IID_ID3D11ShaderReflection47 }
    };
    return &compiler;
}
#endif
```

#### Option B: Separate Implementation File
Create `shaderc_hlsl_linux.cpp` that implements the same interface using d3d4linux.

### Files to Modify

| File | Change |
|------|--------|
| tools/shaderc/shaderc.h | Change `SHADERC_CONFIG_HLSL` define for Linux |
| tools/shaderc/shaderc_hlsl.cpp | Add d3d4linux code path for Linux |
| scripts/shaderc.lua | Add d3d4linux include/library paths, enable HLSL on Linux |
| scripts/shader.mk | Allow TARGET=0/1 on Linux when d3d4linux is available |

### Environment Variables for d3d4linux

The d3d4linux library uses environment variables for configuration:

| Variable | Description | Example |
|----------|-------------|---------|
| D3D4LINUX_WINE | Path to Wine executable | `/usr/bin/wine` |
| D3D4LINUX_EXE | Path to d3d4linux.exe | `$(BGFX_DIR)/3rdparty/d3d4linux/d3d4linux.exe` |
| D3D4LINUX_DLL | Path to d3dcompiler DLL | `z:$(BGFX_DIR)/3rdparty/d3d4linux/d3dcompiler_47.dll` |
| D3D4LINUX_VERBOSE | Enable debug output | `1` |

### Testing Strategy

1. **Unit Test:** Compile a single shader with shaderc
```bash
./tools/bin/linux/shaderc -f examples/01-cubes/vs_cubes.sc \
    -o /tmp/vs_cubes.bin --type vertex \
    --platform windows -p s_5_0 \
    -i examples/common -i src
```

2. **Integration Test:** Build all example shaders
```bash
cd examples/01-cubes
make TARGET=0 all  # Should work on Linux with d3d4linux
```

3. **Validation:** Verify bytecode matches Windows output
   - Compare `.bin` files byte-for-byte
   - Or compare disassembly output

### Summary

The d3d4linux integration requires:

1. Enabling `SHADERC_CONFIG_HLSL=1` on Linux
2. Providing d3d4linux's D3D functions instead of loading native DLL
3. Setting up environment variables or embedding paths in shaderc
4. Updating build scripts to allow D3D11 shader compilation on Linux

The architecture is well-designed for this modification - all D3D-specific code is isolated in `shaderc_hlsl.cpp` and the configuration is controlled by a single preprocessor define.

---

## 2026-02-03: Scope Clarification - DXC Excluded from This Pull Request

### Decision

**This pull request will ONLY implement legacy D3D shader compilation support (SM 2.0 - 5.1).**

DXC (DirectXShaderCompiler) is explicitly excluded from this PR for the following reasons:

### Rationale

1. **Native Cross-Platform Support:** DXC already provides native binaries for:
   - **Linux:** `libdxcompiler.so`, `libdxil.so`, `dxc` executable
   - **macOS:** Native binaries available
   - **Windows:** `dxcompiler.dll`, `dxil.dll`, `dxc.exe`
   
2. **No Wine Required:** Unlike legacy d3dcompiler_47.dll which requires Wine on Linux, DXC can run natively. Adding DXC to d3d4linux would be redundant and add unnecessary complexity.

3. **Separate Integration Path:** DXC integration should be handled as a separate feature:
   - Use native platform libraries directly (no Wine overhead)
   - Different API (IDxcCompiler3 vs ID3D11ShaderReflection)
   - Would require changes to shaderc for SM 6.0+ profile support

4. **Scope Management:** Keeping this PR focused on legacy support makes it:
   - Easier to review
   - Lower risk
   - Faster to merge
   - Addresses the original issue (#1869) completely

### Compiler Support Summary

| Compiler | Shader Models | This PR | Future Work |
|----------|---------------|---------|-------------|
| Legacy FXC (d3dcompiler_47.dll) | SM 2.0 - 5.1 | ✅ Yes (via Wine + d3d4linux) | N/A |
| Modern DXC (dxcompiler) | SM 6.0 - 6.9 | ❌ No | Native integration (no Wine needed) |

### Conclusion

The d3d4linux integration addresses the original issue (#1869) by enabling legacy HLSL shader compilation on Linux. Modern DXC support can be added in a future PR using native platform libraries, which is the correct approach since DXC doesn't require Wine.

---

## 2026-02-03: bgfx Shaderc Integration

### Files Modified

#### 1. tools/shaderc/shaderc.h
- Added `SHADERC_CONFIG_HLSL_D3D4LINUX` preprocessor define
- Modified `SHADERC_CONFIG_HLSL` to enable on Linux/macOS when d3d4linux is configured
- Logic: Windows always enabled, Linux/macOS enabled when `SHADERC_CONFIG_HLSL_D3D4LINUX=1`

#### 2. tools/shaderc/shaderc_hlsl.cpp
- Added conditional include for `<d3d4linux.h>` when `SHADERC_CONFIG_HLSL_D3D4LINUX` is defined
- Wrapped Windows-specific function pointer typedefs with `#if !SHADERC_CONFIG_HLSL_D3D4LINUX`
- Modified `load()` function to return d3d4linux compiler info on Linux
- Modified `unload()` function to be a no-op on d3d4linux (no DLL to unload)
- d3d4linux provides `D3DCompile`, `D3DReflect`, `D3DDisassemble`, `D3DStripShader` as inline functions

#### 3. scripts/shaderc.lua
- Added `D3D4LINUX` path variable
- Added d3d4linux include path for Linux/macOS configurations
- Added comment explaining the `SHADERC_CONFIG_HLSL_D3D4LINUX` feature flag

### How to Enable

To build shaderc with d3d4linux support on Linux:

```bash
# Add to your build configuration:
defines { "SHADERC_CONFIG_HLSL_D3D4LINUX=1" }

# Or via command line:
-DSHADERC_CONFIG_HLSL_D3D4LINUX=1
```

### Environment Variables Required at Runtime

When running shaderc with d3d4linux, set these environment variables:

```bash
export D3D4LINUX_WINE="/usr/bin/wine"
export D3D4LINUX_EXE="/path/to/bgfx/3rdparty/d3d4linux/d3d4linux.exe"
export D3D4LINUX_DLL="z:/path/to/bgfx/3rdparty/d3d4linux/d3dcompiler_47.dll"
```

### Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                     shaderc (Linux)                              │
├─────────────────────────────────────────────────────────────────┤
│  shaderc_hlsl.cpp                                                │
│  ┌─────────────────────────────────────────────────────────────┐│
│  │ #if SHADERC_CONFIG_HLSL_D3D4LINUX                           ││
│  │   #include <d3d4linux.h>                                    ││
│  │   → D3DCompile()    (inline, calls d3d4linux::compile)      ││
│  │   → D3DReflect()    (inline, calls d3d4linux::reflect)      ││
│  │   → D3DStripShader() (inline, calls d3d4linux::strip_shader)││
│  │   → D3DDisassemble() (inline, calls d3d4linux::disassemble) ││
│  └─────────────────────────────────────────────────────────────┘│
│                              │                                   │
│                              ▼                                   │
│  ┌─────────────────────────────────────────────────────────────┐│
│  │                    d3d4linux_impl.h                          ││
│  │   fork() → Wine process with d3d4linux.exe                  ││
│  │   IPC via pipes (stdin/stdout)                               ││
│  └─────────────────────────────────────────────────────────────┘│
│                              │                                   │
│                              ▼                                   │
│  ┌─────────────────────────────────────────────────────────────┐│
│  │         Wine + d3d4linux.exe + d3dcompiler_47.dll            ││
│  │   Actual D3D compilation happens here                        ││
│  └─────────────────────────────────────────────────────────────┘│
└─────────────────────────────────────────────────────────────────┘
```

### Testing

Build shaderc with d3d4linux support and test with:

```bash
# Set environment
export D3D4LINUX_WINE="/usr/bin/wine"
export D3D4LINUX_EXE="$PWD/3rdparty/d3d4linux/d3d4linux.exe"
export D3D4LINUX_DLL="z:$PWD/3rdparty/d3d4linux/d3dcompiler_47.dll"

# Compile a shader
./shaderc -f examples/01-cubes/vs_cubes.sc \
    -o /tmp/vs_cubes.bin --type vertex \
    --platform windows -p s_5_0 \
    -i examples/common -i src
```

---

## 2026-02-03: Shaderc Integration Complete

### Build System Changes

**scripts/shaderc.lua:**
- Added `D3D4LINUX` path variable pointing to `3rdparty/d3d4linux`
- Added configuration for `linux* or osx*`:
  - Define `SHADERC_CONFIG_HLSL_D3D4LINUX=1`
  - Include path to d3d4linux headers

### shaderc Source Changes

**tools/shaderc/shaderc.h:**
- Modified `SHADERC_CONFIG_HLSL` to enable when `SHADERC_CONFIG_HLSL_D3D4LINUX` is defined

**tools/shaderc/shaderc_hlsl.cpp:**
- Restructured with `#if SHADERC_CONFIG_HLSL_D3D4LINUX` conditionals
- Separate `load()` and `unload()` implementations:
  - d3d4linux: No-op (functions are inline from headers)
  - Windows: LoadLibrary/GetProcAddress for d3dcompiler_*.dll
- Use integer `IID_ID3D11ShaderReflection` for d3d4linux instead of GUID
- Fixed null pointer crash when D3DCompile returns error without message
- Initialize all ID3DBlob pointers to NULL

### Additional d3d4linux Fixes

**d3d4linux_enums.h:**
- Added missing D3DCOMPILE_* flags used by shaderc

**d3d4linux.h:**
- Added `ID3D11ShaderReflectionType` struct with `GetDesc()` method
- Added `GetType()` method to `ID3D11ShaderReflectionVariable`
- Updated Wine path default from `wine64` to `wine` for Wine 11+ compatibility
- Added `D3D4LINUX_WINE_FALLBACK` for older Wine versions

**d3d4linux_impl.h:**
- Added Wine path fallback logic with `access()` check
- Fixed D3DDisassemble IPC protocol bug (only write comment string when present)

### Final Test Results

```bash
D3D4LINUX_EXE=/path/to/d3d4linux.exe \
./shadercRelease -f examples/01-cubes/vs_cubes.sc \
    -o /tmp/vs_cubes.bin --type vertex \
    --platform windows -p s_5_0 \
    -i src -i examples/common \
    --varyingdef examples/01-cubes/varying.def.sc
```

| Shader | Output Size | Status |
|--------|-------------|--------|
| vs_cubes.sc (vertex) | 618 bytes | ✅ |
| fs_cubes.sc (fragment) | 270 bytes | ✅ |
| vs_bump.sc (vertex) | 2650 bytes | ✅ |

All D3D functions verified working through shaderc:
- D3DCompile ✅
- D3DReflect ✅
- D3DStripShader ✅
- D3DDisassemble ✅

### Commits

1. `2bc66540f` - Add d3d4linux to 3rdparty for Linux HLSL shader compilation
2. `ee4802134` - d3d4linux: Complete shaderc HLSL integration with Wine

### Documentation

- Created `docs/d3d4linux-shaderc-support.md` - User guide with prerequisites, usage, and troubleshooting
