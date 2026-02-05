# Fix reflection serialization for D3D11_SHADER_TYPE_DESC

## Summary

This PR fixes a critical bug in the shader reflection serialization that prevented bgfx (and potentially other users of d3d4linux) from extracting uniform/constant buffer information from compiled HLSL shaders.

**Note:** These fixes have also been submitted upstream to d3d4linux: https://github.com/samhocevar/d3d4linux/pull/1

The `d3d4linux.cpp` and `Makefile` are included in this PR so bgfx can build with the fixes while waiting for the upstream PR to be merged.

## The Problem

When bgfx compiles shaders using d3d4linux, it needs to extract reflection data to determine uniform names, types, and sizes. The reflection API provides this through:

```cpp
ID3D11ShaderReflectionVariable* var = cbuffer->GetVariableByIndex(i);
ID3D11ShaderReflectionType* type = var->GetType();
D3D11_SHADER_TYPE_DESC type_desc;
type->GetDesc(&type_desc);
```

However, d3d4linux was **not serializing** the `D3D11_SHADER_TYPE_DESC` data across the Wine IPC boundary. This meant that while variables were being enumerated, their **type information was garbage**, causing:

- Uniforms to have incorrect types (e.g., `mat4` appearing as unknown)
- Uniform sizes to be wrong or zero
- Shaders to fail at runtime due to incorrect constant buffer layouts

## The Fix

### Wine side (d3d4linux.cpp)

Added serialization of the type descriptor after each variable:

```cpp
// After writing variable descriptor...
ID3D11ShaderReflectionType *type = variable->GetType();
D3D11_SHADER_TYPE_DESC type_desc;
type->GetDesc(&type_desc);
p.write_raw(&type_desc, sizeof(type_desc));
p.write_string(type_desc.Name ? type_desc.Name : "");
```

### Client side (d3d4linux_impl.h)

Added deserialization to populate the `m_type` member:

```cpp
// After reading variable descriptor...
p.read_raw(&var.m_type.m_desc, sizeof(var.m_type.m_desc));
var.m_type.m_name = p.read_string();
```

### Min Precision Support (d3d4linux.h)

Added the `D3D_MIN_PRECISION` enum which was missing from the header. This enum is required by the `D3D11_SHADER_TYPE_DESC` structure to specify minimum precision requirements for shader variables (e.g., `D3D_MIN_PRECISION_DEFAULT`, `D3D_MIN_PRECISION_FLOAT_16`, etc.):

```cpp
enum D3D_MIN_PRECISION
{
    D3D_MIN_PRECISION_DEFAULT   = 0,
    D3D_MIN_PRECISION_FLOAT_16  = 1,
    D3D_MIN_PRECISION_FLOAT_2_8 = 2,
    D3D_MIN_PRECISION_RESERVED  = 3,
    D3D_MIN_PRECISION_SINT_16   = 4,
    D3D_MIN_PRECISION_UINT_16   = 5,
    D3D_MIN_PRECISION_ANY_16    = 0xf0,
    D3D_MIN_PRECISION_ANY_10    = 0xf1,
};
```

Without this enum, the `MinPrecision` field in `D3D11_SHADER_TYPE_DESC` would cause compilation errors or undefined behavior.

## Testing

Tested with bgfx shader compiler (shaderc) on Linux:

1. **Build**: Compiled shaderc with d3d4linux integration
2. **Compile**: Built cubes example shaders for dx11 profile
   ```
   shaderc -f vs_cubes.sc -o vs_cubes.bin --type vertex --platform windows -p vs_5_0
   shaderc -f fs_cubes.sc -o fs_cubes.bin --type fragment --platform windows -p ps_5_0
   ```
3. **Verify**: Confirmed `u_modelViewProj` uniform extracted correctly:
   - Type: `D3D_SVT_FLOAT` (matrix)
   - Rows: 4, Columns: 4
   - Size: 64 bytes
4. **Runtime**: Ran cubes example in Wine+DXVK - renders correctly with proper transforms

## Before/After

**Before:** Uniforms had garbage type data, causing runtime failures
```
Uniform: u_modelViewProj
  Type: 0 (unknown)
  Size: 0
```

**After:** Uniforms correctly identified
```
Uniform: u_modelViewProj  
  Type: D3D_SVT_FLOAT (matrix 4x4)
  Size: 64
```

## Compatibility

This change maintains backward compatibility with the IPC protocol - it only adds data that was previously missing. The `ID3D11ShaderReflectionType` stub class already had `m_desc` and `m_name` members; they just weren't being populated.
