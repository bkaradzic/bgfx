//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  File:       D3D10Shader.h
//  Content:    D3D10 Shader Types and APIs
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __D3D10SHADER_H__
#define __D3D10SHADER_H__


#include "d3d10.h"




//---------------------------------------------------------------------------
// D3D10_TX_VERSION:
// --------------
// Version token used to create a procedural texture filler in effects
// Used by D3D10Fill[]TX functions
//---------------------------------------------------------------------------
#define D3D10_TX_VERSION(_Major,_Minor) (('T' << 24) | ('X' << 16) | ((_Major) << 8) | (_Minor))


//----------------------------------------------------------------------------
// D3D10SHADER flags:
// -----------------
// D3D10_SHADER_DEBUG
//   Insert debug file/line/type/symbol information.
//
// D3D10_SHADER_SKIP_VALIDATION
//   Do not validate the generated code against known capabilities and
//   constraints.  This option is only recommended when compiling shaders
//   you KNOW will work.  (ie. have compiled before without this option.)
//   Shaders are always validated by D3D before they are set to the device.
//
// D3D10_SHADER_SKIP_OPTIMIZATION 
//   Instructs the compiler to skip optimization steps during code generation.
//   Unless you are trying to isolate a problem in your code using this option 
//   is not recommended.
//
// D3D10_SHADER_PACK_MATRIX_ROW_MAJOR
//   Unless explicitly specified, matrices will be packed in row-major order
//   on input and output from the shader.
//
// D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR
//   Unless explicitly specified, matrices will be packed in column-major 
//   order on input and output from the shader.  This is generally more 
//   efficient, since it allows vector-matrix multiplication to be performed
//   using a series of dot-products.
//
// D3D10_SHADER_PARTIAL_PRECISION
//   Force all computations in resulting shader to occur at partial precision.
//   This may result in faster evaluation of shaders on some hardware.
//
// D3D10_SHADER_FORCE_VS_SOFTWARE_NO_OPT
//   Force compiler to compile against the next highest available software
//   target for vertex shaders.  This flag also turns optimizations off, 
//   and debugging on.  
//
// D3D10_SHADER_FORCE_PS_SOFTWARE_NO_OPT
//   Force compiler to compile against the next highest available software
//   target for pixel shaders.  This flag also turns optimizations off, 
//   and debugging on.
//
// D3D10_SHADER_NO_PRESHADER
//   Disables Preshaders. Using this flag will cause the compiler to not 
//   pull out static expression for evaluation on the host cpu
//
// D3D10_SHADER_AVOID_FLOW_CONTROL
//   Hint compiler to avoid flow-control constructs where possible.
//
// D3D10_SHADER_PREFER_FLOW_CONTROL
//   Hint compiler to prefer flow-control constructs where possible.
//
// D3D10_SHADER_ENABLE_STRICTNESS
//   By default, the HLSL/Effect compilers are not strict on deprecated syntax.
//   Specifying this flag enables the strict mode. Deprecated syntax may be
//   removed in a future release, and enabling syntax is a good way to make sure
//   your shaders comply to the latest spec.
//
// D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY
//   This enables older shaders to compile to 4_0 targets.
//
//----------------------------------------------------------------------------

#define D3D10_SHADER_DEBUG                          (1 << 0)
#define D3D10_SHADER_SKIP_VALIDATION                (1 << 1)
#define D3D10_SHADER_SKIP_OPTIMIZATION              (1 << 2)
#define D3D10_SHADER_PACK_MATRIX_ROW_MAJOR          (1 << 3)
#define D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR       (1 << 4)
#define D3D10_SHADER_PARTIAL_PRECISION              (1 << 5)
#define D3D10_SHADER_FORCE_VS_SOFTWARE_NO_OPT       (1 << 6)
#define D3D10_SHADER_FORCE_PS_SOFTWARE_NO_OPT       (1 << 7)
#define D3D10_SHADER_NO_PRESHADER                   (1 << 8)
#define D3D10_SHADER_AVOID_FLOW_CONTROL             (1 << 9)
#define D3D10_SHADER_PREFER_FLOW_CONTROL            (1 << 10)
#define D3D10_SHADER_ENABLE_STRICTNESS              (1 << 11)
#define D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY (1 << 12)
#define D3D10_SHADER_IEEE_STRICTNESS                (1 << 13)
#define D3D10_SHADER_WARNINGS_ARE_ERRORS            (1 << 18)
#define D3D10_SHADER_RESOURCES_MAY_ALIAS            (1 << 19)
#define D3D10_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES    (1 << 20)
#define D3D10_ALL_RESOURCES_BOUND                   (1 << 21)


// optimization level flags
#define D3D10_SHADER_OPTIMIZATION_LEVEL0            (1 << 14)
#define D3D10_SHADER_OPTIMIZATION_LEVEL1            0
#define D3D10_SHADER_OPTIMIZATION_LEVEL2            ((1 << 14) | (1 << 15))
#define D3D10_SHADER_OPTIMIZATION_LEVEL3            (1 << 15)




typedef D3D_SHADER_MACRO D3D10_SHADER_MACRO;
typedef D3D10_SHADER_MACRO* LPD3D10_SHADER_MACRO;


typedef D3D_SHADER_VARIABLE_CLASS D3D10_SHADER_VARIABLE_CLASS;
typedef D3D10_SHADER_VARIABLE_CLASS* LPD3D10_SHADER_VARIABLE_CLASS;

typedef D3D_SHADER_VARIABLE_FLAGS D3D10_SHADER_VARIABLE_FLAGS;
typedef D3D10_SHADER_VARIABLE_FLAGS* LPD3D10_SHADER_VARIABLE_FLAGS;

typedef D3D_SHADER_VARIABLE_TYPE D3D10_SHADER_VARIABLE_TYPE;
typedef D3D10_SHADER_VARIABLE_TYPE* LPD3D10_SHADER_VARIABLE_TYPE;

typedef D3D_SHADER_INPUT_FLAGS D3D10_SHADER_INPUT_FLAGS;
typedef D3D10_SHADER_INPUT_FLAGS* LPD3D10_SHADER_INPUT_FLAGS;

typedef D3D_SHADER_INPUT_TYPE D3D10_SHADER_INPUT_TYPE;
typedef D3D10_SHADER_INPUT_TYPE* LPD3D10_SHADER_INPUT_TYPE;

typedef D3D_SHADER_CBUFFER_FLAGS D3D10_SHADER_CBUFFER_FLAGS;
typedef D3D10_SHADER_CBUFFER_FLAGS* LPD3D10_SHADER_CBUFFER_FLAGS;

typedef D3D_CBUFFER_TYPE D3D10_CBUFFER_TYPE;
typedef D3D10_CBUFFER_TYPE* LPD3D10_CBUFFER_TYPE;

typedef D3D_NAME D3D10_NAME;

typedef D3D_RESOURCE_RETURN_TYPE D3D10_RESOURCE_RETURN_TYPE;

typedef D3D_REGISTER_COMPONENT_TYPE D3D10_REGISTER_COMPONENT_TYPE;

typedef D3D_INCLUDE_TYPE D3D10_INCLUDE_TYPE;

// ID3D10Include has been made version-neutral and moved to d3dcommon.h.
typedef interface ID3DInclude ID3D10Include;
typedef interface ID3DInclude* LPD3D10INCLUDE;
#define IID_ID3D10Include IID_ID3DInclude


//----------------------------------------------------------------------------
// ID3D10ShaderReflection:
//----------------------------------------------------------------------------

//
// Structure definitions
//

typedef struct _D3D10_SHADER_DESC
{
    UINT                    Version;                     // Shader version
    LPCSTR                  Creator;                     // Creator string
    UINT                    Flags;                       // Shader compilation/parse flags
    
    UINT                    ConstantBuffers;             // Number of constant buffers
    UINT                    BoundResources;              // Number of bound resources
    UINT                    InputParameters;             // Number of parameters in the input signature
    UINT                    OutputParameters;            // Number of parameters in the output signature

    UINT                    InstructionCount;            // Number of emitted instructions
    UINT                    TempRegisterCount;           // Number of temporary registers used 
    UINT                    TempArrayCount;              // Number of temporary arrays used
    UINT                    DefCount;                    // Number of constant defines 
    UINT                    DclCount;                    // Number of declarations (input + output)
    UINT                    TextureNormalInstructions;   // Number of non-categorized texture instructions
    UINT                    TextureLoadInstructions;     // Number of texture load instructions
    UINT                    TextureCompInstructions;     // Number of texture comparison instructions
    UINT                    TextureBiasInstructions;     // Number of texture bias instructions
    UINT                    TextureGradientInstructions; // Number of texture gradient instructions
    UINT                    FloatInstructionCount;       // Number of floating point arithmetic instructions used
    UINT                    IntInstructionCount;         // Number of signed integer arithmetic instructions used
    UINT                    UintInstructionCount;        // Number of unsigned integer arithmetic instructions used
    UINT                    StaticFlowControlCount;      // Number of static flow control instructions used
    UINT                    DynamicFlowControlCount;     // Number of dynamic flow control instructions used
    UINT                    MacroInstructionCount;       // Number of macro instructions used
    UINT                    ArrayInstructionCount;       // Number of array instructions used
    UINT                    CutInstructionCount;         // Number of cut instructions used
    UINT                    EmitInstructionCount;        // Number of emit instructions used
    D3D10_PRIMITIVE_TOPOLOGY GSOutputTopology;           // Geometry shader output topology
    UINT                    GSMaxOutputVertexCount;      // Geometry shader maximum output vertex count
} D3D10_SHADER_DESC;

typedef struct _D3D10_SHADER_BUFFER_DESC
{
    LPCSTR                  Name;           // Name of the constant buffer
    D3D10_CBUFFER_TYPE      Type;           // Indicates that this is a CBuffer or TBuffer
    UINT                    Variables;      // Number of member variables
    UINT                    Size;           // Size of CB (in bytes)
    UINT                    uFlags;         // Buffer description flags
} D3D10_SHADER_BUFFER_DESC;

typedef struct _D3D10_SHADER_VARIABLE_DESC
{
    LPCSTR                  Name;           // Name of the variable
    UINT                    StartOffset;    // Offset in constant buffer's backing store
    UINT                    Size;           // Size of variable (in bytes)
    UINT                    uFlags;         // Variable flags
    LPVOID                  DefaultValue;   // Raw pointer to default value
} D3D10_SHADER_VARIABLE_DESC;

typedef struct _D3D10_SHADER_TYPE_DESC
{
    D3D10_SHADER_VARIABLE_CLASS Class;          // Variable class (e.g. object, matrix, etc.)
    D3D10_SHADER_VARIABLE_TYPE  Type;           // Variable type (e.g. float, sampler, etc.)
    UINT                        Rows;           // Number of rows (for matrices, 1 for other numeric, 0 if not applicable)
    UINT                        Columns;        // Number of columns (for vectors & matrices, 1 for other numeric, 0 if not applicable)
    UINT                        Elements;       // Number of elements (0 if not an array)
    UINT                        Members;        // Number of members (0 if not a structure)
    UINT                        Offset;         // Offset from the start of structure (0 if not a structure member) 
} D3D10_SHADER_TYPE_DESC;

typedef struct _D3D10_SHADER_INPUT_BIND_DESC
{
    LPCSTR                      Name;           // Name of the resource
    D3D10_SHADER_INPUT_TYPE     Type;           // Type of resource (e.g. texture, cbuffer, etc.)
    UINT                        BindPoint;      // Starting bind point
    UINT                        BindCount;      // Number of contiguous bind points (for arrays)
    
    UINT                        uFlags;         // Input binding flags
    D3D10_RESOURCE_RETURN_TYPE  ReturnType;     // Return type (if texture)
    D3D10_SRV_DIMENSION         Dimension;      // Dimension (if texture)
    UINT                        NumSamples;     // Number of samples (0 if not MS texture)
} D3D10_SHADER_INPUT_BIND_DESC;

typedef struct _D3D10_SIGNATURE_PARAMETER_DESC
{
    LPCSTR                      SemanticName;   // Name of the semantic
    UINT                        SemanticIndex;  // Index of the semantic
    UINT                        Register;       // Number of member variables
    D3D10_NAME                  SystemValueType;// A predefined system value, or D3D10_NAME_UNDEFINED if not applicable
    D3D10_REGISTER_COMPONENT_TYPE ComponentType;// Scalar type (e.g. uint, float, etc.)
    BYTE                        Mask;           // Mask to indicate which components of the register
                                                // are used (combination of D3D10_COMPONENT_MASK values)
    BYTE                        ReadWriteMask;  // Mask to indicate whether a given component is 
                                                // never written (if this is an output signature) or
                                                // always read (if this is an input signature).
                                                // (combination of D3D10_COMPONENT_MASK values)
    
} D3D10_SIGNATURE_PARAMETER_DESC;


//
// Interface definitions
//




typedef interface ID3D10ShaderReflectionType ID3D10ShaderReflectionType;
typedef interface ID3D10ShaderReflectionType *LPD3D10SHADERREFLECTIONTYPE;

// {C530AD7D-9B16-4395-A979-BA2ECFF83ADD}
interface DECLSPEC_UUID("C530AD7D-9B16-4395-A979-BA2ECFF83ADD") ID3D10ShaderReflectionType;
DEFINE_GUID(IID_ID3D10ShaderReflectionType, 
0xc530ad7d, 0x9b16, 0x4395, 0xa9, 0x79, 0xba, 0x2e, 0xcf, 0xf8, 0x3a, 0xdd);

#undef INTERFACE
#define INTERFACE ID3D10ShaderReflectionType

DECLARE_INTERFACE(ID3D10ShaderReflectionType)
{
    STDMETHOD(GetDesc)(THIS_ D3D10_SHADER_TYPE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10ShaderReflectionType*, GetMemberTypeByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10ShaderReflectionType*, GetMemberTypeByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(LPCSTR, GetMemberTypeName)(THIS_ UINT Index) PURE;
};

typedef interface ID3D10ShaderReflectionVariable ID3D10ShaderReflectionVariable;
typedef interface ID3D10ShaderReflectionVariable *LPD3D10SHADERREFLECTIONVARIABLE;

// {1BF63C95-2650-405d-99C1-3636BD1DA0A1}
interface DECLSPEC_UUID("1BF63C95-2650-405d-99C1-3636BD1DA0A1") ID3D10ShaderReflectionVariable;
DEFINE_GUID(IID_ID3D10ShaderReflectionVariable, 
0x1bf63c95, 0x2650, 0x405d, 0x99, 0xc1, 0x36, 0x36, 0xbd, 0x1d, 0xa0, 0xa1);

#undef INTERFACE
#define INTERFACE ID3D10ShaderReflectionVariable

DECLARE_INTERFACE(ID3D10ShaderReflectionVariable)
{
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_SHADER_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10ShaderReflectionType*, GetType)(THIS) PURE;
};

typedef interface ID3D10ShaderReflectionConstantBuffer ID3D10ShaderReflectionConstantBuffer;
typedef interface ID3D10ShaderReflectionConstantBuffer *LPD3D10SHADERREFLECTIONCONSTANTBUFFER;

// {66C66A94-DDDD-4b62-A66A-F0DA33C2B4D0}
interface DECLSPEC_UUID("66C66A94-DDDD-4b62-A66A-F0DA33C2B4D0") ID3D10ShaderReflectionConstantBuffer;
DEFINE_GUID(IID_ID3D10ShaderReflectionConstantBuffer, 
0x66c66a94, 0xdddd, 0x4b62, 0xa6, 0x6a, 0xf0, 0xda, 0x33, 0xc2, 0xb4, 0xd0);

#undef INTERFACE
#define INTERFACE ID3D10ShaderReflectionConstantBuffer

DECLARE_INTERFACE(ID3D10ShaderReflectionConstantBuffer)
{
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_SHADER_BUFFER_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10ShaderReflectionVariable*, GetVariableByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10ShaderReflectionVariable*, GetVariableByName)(THIS_ LPCSTR Name) PURE;
};

typedef interface ID3D10ShaderReflection ID3D10ShaderReflection;
typedef interface ID3D10ShaderReflection *LPD3D10SHADERREFLECTION;

// {D40E20B6-F8F7-42ad-AB20-4BAF8F15DFAA}
interface DECLSPEC_UUID("D40E20B6-F8F7-42ad-AB20-4BAF8F15DFAA") ID3D10ShaderReflection;
DEFINE_GUID(IID_ID3D10ShaderReflection, 
0xd40e20b6, 0xf8f7, 0x42ad, 0xab, 0x20, 0x4b, 0xaf, 0x8f, 0x15, 0xdf, 0xaa);

#undef INTERFACE
#define INTERFACE ID3D10ShaderReflection

DECLARE_INTERFACE_(ID3D10ShaderReflection, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_SHADER_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10ShaderReflectionConstantBuffer*, GetConstantBufferByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10ShaderReflectionConstantBuffer*, GetConstantBufferByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD(GetResourceBindingDesc)(THIS_ UINT ResourceIndex, _Out_ D3D10_SHADER_INPUT_BIND_DESC *pDesc) PURE;
    
    STDMETHOD(GetInputParameterDesc)(THIS_ UINT ParameterIndex, _Out_ D3D10_SIGNATURE_PARAMETER_DESC *pDesc) PURE;
    STDMETHOD(GetOutputParameterDesc)(THIS_ UINT ParameterIndex, _Out_ D3D10_SIGNATURE_PARAMETER_DESC *pDesc) PURE;
    
};

//////////////////////////////////////////////////////////////////////////////
// APIs //////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//----------------------------------------------------------------------------
// D3D10CompileShader:
// ------------------
// Compiles a shader.
//
// Parameters:
//  pSrcFile
//      Source file name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module.
//  pSrcData
//      Pointer to source code.
//  SrcDataSize
//      Size of source code, in bytes.
//  pDefines
//      Optional NULL-terminated array of preprocessor macro definitions.
//  pInclude
//      Optional interface pointer to use for handling #include directives.
//      If this parameter is NULL, #includes will be honored when compiling
//      from file, and will error when compiling from resource or memory.
//  pFunctionName
//      Name of the entrypoint function where execution should begin.
//  pProfile
//      Instruction set to be used when generating code.  The D3D10 entry
//      point currently supports only "vs_4_0", "ps_4_0", and "gs_4_0".
//  Flags
//      See D3D10_SHADER_xxx flags.
//  ppShader
//      Returns a buffer containing the created shader.  This buffer contains
//      the compiled shader code, as well as any embedded debug and symbol
//      table info.  (See D3D10GetShaderConstantTable)
//  ppErrorMsgs
//      Returns a buffer containing a listing of errors and warnings that were
//      encountered during the compile.  If you are running in a debugger,
//      these are the same messages you will see in your debug output.
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10CompileShader(_In_reads_bytes_(SrcDataSize) LPCSTR pSrcData, SIZE_T SrcDataSize, _In_opt_ LPCSTR pFileName, _In_opt_ CONST D3D10_SHADER_MACRO* pDefines, _In_opt_ LPD3D10INCLUDE pInclude, 
    LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags, _Out_ ID3D10Blob** ppShader, _Out_opt_ ID3D10Blob** ppErrorMsgs);

//----------------------------------------------------------------------------
// D3D10DisassembleShader:
// ----------------------
// Takes a binary shader, and returns a buffer containing text assembly.
//
// Parameters:
//  pShader
//      Pointer to the shader byte code.
//  BytecodeLength
//      Size of the shader byte code in bytes.
//  EnableColorCode
//      Emit HTML tags for color coding the output?
//  pComments
//      Pointer to a comment string to include at the top of the shader.
//  ppDisassembly
//      Returns a buffer containing the disassembled shader.
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10DisassembleShader(_In_reads_bytes_(BytecodeLength) CONST void *pShader, SIZE_T BytecodeLength, BOOL EnableColorCode, _In_opt_ LPCSTR pComments, _Out_ ID3D10Blob** ppDisassembly);


//----------------------------------------------------------------------------
// D3D10GetPixelShaderProfile/D3D10GetVertexShaderProfile/D3D10GetGeometryShaderProfile:
// -----------------------------------------------------
// Returns the name of the HLSL profile best suited to a given device.
//
// Parameters:
//  pDevice
//      Pointer to the device in question
//----------------------------------------------------------------------------

LPCSTR WINAPI D3D10GetPixelShaderProfile(_In_ ID3D10Device *pDevice);

LPCSTR WINAPI D3D10GetVertexShaderProfile(_In_ ID3D10Device *pDevice);

LPCSTR WINAPI D3D10GetGeometryShaderProfile(_In_ ID3D10Device *pDevice);

//----------------------------------------------------------------------------
// D3D10ReflectShader:
// ------------------
// Creates a shader reflection object that can be used to retrieve information
// about a compiled shader
//
// Parameters:
//  pShaderBytecode
//      Pointer to a compiled shader (same pointer that is passed into
//      ID3D10Device::CreateShader)
//  BytecodeLength
//      Length of the shader bytecode buffer
//  ppReflector
//      [out] Returns a ID3D10ShaderReflection object that can be used to 
//      retrieve shader resource and constant buffer information
//
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10ReflectShader(_In_reads_bytes_(BytecodeLength) CONST void *pShaderBytecode, SIZE_T BytecodeLength, _Out_ ID3D10ShaderReflection **ppReflector);

//----------------------------------------------------------------------------
// D3D10PreprocessShader
// ---------------------
// Creates a shader reflection object that can be used to retrieve information
// about a compiled shader
//
// Parameters:
//  pSrcData
//      Pointer to source code
//  SrcDataSize
//      Size of source code, in bytes
//  pFileName
//      Source file name (used for error output)
//  pDefines
//      Optional NULL-terminated array of preprocessor macro definitions.
//  pInclude
//      Optional interface pointer to use for handling #include directives.
//      If this parameter is NULL, #includes will be honored when assembling
//      from file, and will error when assembling from resource or memory.
//  ppShaderText
//      Returns a buffer containing a single large string that represents
//      the resulting formatted token stream
//  ppErrorMsgs
//      Returns a buffer containing a listing of errors and warnings that were
//      encountered during assembly.  If you are running in a debugger,
//      these are the same messages you will see in your debug output.
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10PreprocessShader(_In_reads_bytes_(SrcDataSize) LPCSTR pSrcData, SIZE_T SrcDataSize, _In_opt_ LPCSTR pFileName, _In_opt_ CONST D3D10_SHADER_MACRO* pDefines, 
    _In_opt_ LPD3D10INCLUDE pInclude, _Out_ ID3D10Blob** ppShaderText, _Out_opt_ ID3D10Blob** ppErrorMsgs);

//////////////////////////////////////////////////////////////////////////
//
// Shader blob manipulation routines
// ---------------------------------
//
// void *pShaderBytecode - a buffer containing the result of an HLSL
//  compilation.  Typically this opaque buffer contains several 
//  discrete sections including the shader executable code, the input
//  signature, and the output signature.  This can typically be retrieved 
//  by calling ID3D10Blob::GetBufferPointer() on the returned blob
//  from HLSL's compile APIs.
//
// UINT BytecodeLength - the length of pShaderBytecode.  This can 
//  typically be retrieved by calling ID3D10Blob::GetBufferSize() 
//  on the returned blob from HLSL's compile APIs.
//
// ID3D10Blob **ppSignatureBlob(s) - a newly created buffer that
//  contains only the signature portions of the original bytecode.
//  This is a copy; the original bytecode is not modified.  You may
//  specify NULL for this parameter to have the bytecode validated
//  for the presence of the corresponding signatures without actually
//  copying them and creating a new blob.
//
// Returns E_INVALIDARG if any required parameters are NULL
// Returns E_FAIL is the bytecode is corrupt or missing signatures
// Returns S_OK on success
//
//////////////////////////////////////////////////////////////////////////

HRESULT WINAPI D3D10GetInputSignatureBlob(_In_reads_bytes_(BytecodeLength) CONST void *pShaderBytecode, SIZE_T BytecodeLength, _Out_ ID3D10Blob **ppSignatureBlob);
HRESULT WINAPI D3D10GetOutputSignatureBlob(_In_reads_bytes_(BytecodeLength) CONST void *pShaderBytecode, SIZE_T BytecodeLength, _Out_ ID3D10Blob **ppSignatureBlob);
HRESULT WINAPI D3D10GetInputAndOutputSignatureBlob(_In_reads_bytes_(BytecodeLength) CONST void *pShaderBytecode, SIZE_T BytecodeLength, _Out_ ID3D10Blob **ppSignatureBlob);

//----------------------------------------------------------------------------
// D3D10GetShaderDebugInfo:
// -----------------------
// Gets shader debug info.  Debug info is generated by D3D10CompileShader and is
// embedded in the body of the shader.
//
// Parameters:
//  pShaderBytecode
//      Pointer to the function bytecode
//  BytecodeLength
//      Length of the shader bytecode buffer
//  ppDebugInfo
//      Buffer used to return debug info.  For information about the layout
//      of this buffer, see definition of D3D10_SHADER_DEBUG_INFO above.
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10GetShaderDebugInfo(_In_reads_bytes_(BytecodeLength) CONST void *pShaderBytecode, SIZE_T BytecodeLength, _Out_ ID3D10Blob** ppDebugInfo);

#ifdef __cplusplus
}
#endif //__cplusplus

    
#endif //__D3D10SHADER_H__

