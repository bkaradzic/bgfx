# d3d4linux Shaderc Support

This document describes how to compile HLSL shaders for Direct3D on Linux and macOS using shaderc with d3d4linux.

## Overview

d3d4linux enables HLSL shader compilation on non-Windows platforms by running Microsoft's `d3dcompiler_47.dll` through Wine. This allows building D3D11/D3D12 shaders without a Windows machine.

## Prerequisites

### Wine

Install Wine (version 11.0 or later recommended):

**Ubuntu/Debian:**
```bash
sudo dpkg --add-architecture i386
sudo mkdir -pm755 /etc/apt/keyrings
wget -O - https://dl.winehq.org/wine-builds/winehq.key | sudo gpg --dearmor -o /etc/apt/keyrings/winehq-archive.key
sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/ubuntu/dists/$(lsb_release -cs)/winehq-$(lsb_release -cs).sources
sudo apt update
sudo apt install --install-recommends winehq-stable
```

**Arch Linux:**
```bash
sudo pacman -S wine
```

**macOS (Homebrew):**
```bash
brew install --cask wine-stable
```

### MinGW-w64 Cross Compiler

Required to build d3d4linux.exe:

**Ubuntu/Debian:**
```bash
sudo apt install mingw-w64
```

**Arch Linux:**
```bash
sudo pacman -S mingw-w64-gcc
```

**macOS (Homebrew):**
```bash
brew install mingw-w64
```

## Building d3d4linux

Navigate to the d3d4linux directory and build:

```bash
cd 3rdparty/d3d4linux
make
```

This creates `d3d4linux.exe` - a Windows executable that Wine runs to access D3DCompiler functions.

## Building shaderc with d3d4linux Support

Build shaderc normally:

```bash
make shaderc
```

On Linux/macOS, shaderc is automatically built with `SHADERC_CONFIG_HLSL_D3D4LINUX=1`, enabling the d3d4linux backend.

## Usage

### Environment Variables

| Variable | Required | Description |
|----------|----------|-------------|
| `D3D4LINUX_EXE` | **Yes** | Path to `d3d4linux.exe` |
| `D3D4LINUX_WINE` | No | Path to Wine binary (default: `/usr/bin/wine`) |
| `D3D4LINUX_VERBOSE` | No | Set to `1` for debug output |

### Compiling Shaders

```bash
# Set the path to d3d4linux.exe
export D3D4LINUX_EXE=/path/to/bgfx/3rdparty/d3d4linux/d3d4linux.exe

# Compile a vertex shader
./shaderc -f shader.sc -o shader.bin \
    --type vertex \
    --platform windows \
    -p s_5_0 \
    -i include/path

# Compile a fragment/pixel shader
./shaderc -f shader.sc -o shader.bin \
    --type fragment \
    --platform windows \
    -p s_5_0 \
    -i include/path
```

### Supported Shader Models

| Profile | Description |
|---------|-------------|
| `s_3_0` | Shader Model 3.0 (D3D9) |
| `s_4_0` | Shader Model 4.0 (D3D10) |
| `s_4_1` | Shader Model 4.1 (D3D10.1) |
| `s_5_0` | Shader Model 5.0 (D3D11) |

### With Disassembly Output

```bash
D3D4LINUX_EXE=/path/to/d3d4linux.exe \
./shaderc -f shader.sc -o shader.bin \
    --type vertex \
    --platform windows \
    -p s_5_0 \
    --disasm
```

This creates `shader.bin.disasm` with the D3D assembly listing.

### Verbose Mode

For troubleshooting, enable verbose output:

```bash
D3D4LINUX_VERBOSE=1 \
D3D4LINUX_EXE=/path/to/d3d4linux.exe \
./shaderc -f shader.sc -o shader.bin \
    --type vertex \
    --platform windows \
    -p s_5_0
```

## Troubleshooting

### "Cannot fork in d3d4linux::compile()"

Wine is not installed or the Wine executable cannot be found. Ensure Wine is installed and accessible.

### D3DCompile returns E_FAIL (0x80004005)

- Check that `D3D4LINUX_EXE` points to a valid `d3d4linux.exe`
- Verify Wine can run the executable: `wine /path/to/d3d4linux.exe`
- On Wine 11+, the binary is `/usr/bin/wine` (not `wine64`)

### First Run is Slow

Wine may need to initialize its prefix on first run. This is normal and subsequent runs will be faster.

### Missing d3dcompiler_47.dll

Wine includes d3dcompiler_47.dll. If missing, you can copy it from a Windows installation to your Wine prefix:
```bash
cp /path/to/d3dcompiler_47.dll ~/.wine/drive_c/windows/system32/
```

## How It Works

1. shaderc preprocesses the `.sc` shader file
2. d3d4linux forks a child process running Wine with `d3d4linux.exe`
3. The Wine process loads `d3dcompiler_47.dll` and provides D3DCompile, D3DReflect, D3DStripShader, and D3DDisassemble functions
4. Communication happens via pipes using a simple IPC protocol
5. The compiled DXBC bytecode is returned to shaderc

## Limitations

- **Shader Model 5.1 and below**: This integration uses d3dcompiler_47.dll (FXC) which supports up to SM 5.1
- **Performance**: Slightly slower than native Windows compilation due to Wine overhead
- **Wine dependency**: Requires Wine to be installed and configured

## References

- [bgfx Issue #1869](https://github.com/bkaradzic/bgfx/issues/1869) - Original feature request
- [d3d4linux](https://github.com/AshleyScirworern/d3d4linux) - Wine-based D3DCompiler wrapper
