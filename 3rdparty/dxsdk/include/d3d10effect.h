
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  File:       D3D10Effect.h
//  Content:    D3D10 Stateblock/Effect Types & APIs
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __D3D10EFFECT_H__
#define __D3D10EFFECT_H__



#include "d3d10.h"

//////////////////////////////////////////////////////////////////////////////
// File contents:
//
// 1) Stateblock enums, structs, interfaces, flat APIs
// 2) Effect enums, structs, interfaces, flat APIs
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3D10_DEVICE_STATE_TYPES:
//
// Used in ID3D10StateBlockMask function calls
//
//----------------------------------------------------------------------------

typedef enum _D3D10_DEVICE_STATE_TYPES
{
    
    D3D10_DST_SO_BUFFERS=1,             // Single-value state (atomical gets/sets)
    D3D10_DST_OM_RENDER_TARGETS,        // Single-value state (atomical gets/sets)
    D3D10_DST_OM_DEPTH_STENCIL_STATE,   // Single-value state
    D3D10_DST_OM_BLEND_STATE,           // Single-value state

    D3D10_DST_VS,                       // Single-value state
    D3D10_DST_VS_SAMPLERS,              // Count: D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT
    D3D10_DST_VS_SHADER_RESOURCES,      // Count: D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
    D3D10_DST_VS_CONSTANT_BUFFERS,      // Count:			

    D3D10_DST_GS,                       // Single-value state
    D3D10_DST_GS_SAMPLERS,              // Count: D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT
    D3D10_DST_GS_SHADER_RESOURCES,      // Count: D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
    D3D10_DST_GS_CONSTANT_BUFFERS,      // Count: D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT

    D3D10_DST_PS,                       // Single-value state
    D3D10_DST_PS_SAMPLERS,              // Count: D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT
    D3D10_DST_PS_SHADER_RESOURCES,      // Count: D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
    D3D10_DST_PS_CONSTANT_BUFFERS,      // Count: D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
    
    D3D10_DST_IA_VERTEX_BUFFERS,        // Count: D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT
    D3D10_DST_IA_INDEX_BUFFER,          // Single-value state
    D3D10_DST_IA_INPUT_LAYOUT,          // Single-value state
    D3D10_DST_IA_PRIMITIVE_TOPOLOGY,    // Single-value state

    D3D10_DST_RS_VIEWPORTS,             // Single-value state (atomical gets/sets)
    D3D10_DST_RS_SCISSOR_RECTS,         // Single-value state (atomical gets/sets)
    D3D10_DST_RS_RASTERIZER_STATE,      // Single-value state

    D3D10_DST_PREDICATION,              // Single-value state
} D3D10_DEVICE_STATE_TYPES;

//----------------------------------------------------------------------------
// D3D10_DEVICE_STATE_TYPES:
//
// Used in ID3D10StateBlockMask function calls
//
//----------------------------------------------------------------------------

#ifndef D3D10_BYTES_FROM_BITS
#define D3D10_BYTES_FROM_BITS(x) (((x) + 7) / 8)
#endif // D3D10_BYTES_FROM_BITS

typedef struct _D3D10_STATE_BLOCK_MASK
{
    BYTE VS;
    BYTE VSSamplers[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT)];
    BYTE VSShaderResources[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)];
    BYTE VSConstantBuffers[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT)];
    
    BYTE GS;
    BYTE GSSamplers[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT)];
    BYTE GSShaderResources[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)];
    BYTE GSConstantBuffers[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT)];
    
    BYTE PS;
    BYTE PSSamplers[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT)];
    BYTE PSShaderResources[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)];
    BYTE PSConstantBuffers[D3D10_BYTES_FROM_BITS(D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT)];
    
    BYTE IAVertexBuffers[D3D10_BYTES_FROM_BITS(D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT)];
    BYTE IAIndexBuffer;
    BYTE IAInputLayout;
    BYTE IAPrimitiveTopology;
    
    BYTE OMRenderTargets;
    BYTE OMDepthStencilState;
    BYTE OMBlendState;
    
    BYTE RSViewports;
    BYTE RSScissorRects;
    BYTE RSRasterizerState;
    
    BYTE SOBuffers;
    
    BYTE Predication;
} D3D10_STATE_BLOCK_MASK;

//////////////////////////////////////////////////////////////////////////////
// ID3D10StateBlock //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10StateBlock ID3D10StateBlock;
typedef interface ID3D10StateBlock *LPD3D10STATEBLOCK;

// {0803425A-57F5-4dd6-9465-A87570834A08}
DEFINE_GUID(IID_ID3D10StateBlock, 
0x803425a, 0x57f5, 0x4dd6, 0x94, 0x65, 0xa8, 0x75, 0x70, 0x83, 0x4a, 0x8);

#undef INTERFACE
#define INTERFACE ID3D10StateBlock

DECLARE_INTERFACE_(ID3D10StateBlock, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    
    STDMETHOD(Capture)(THIS) PURE;
    STDMETHOD(Apply)(THIS) PURE;
    STDMETHOD(ReleaseAllDeviceObjects)(THIS) PURE;
    STDMETHOD(GetDevice)(_Out_ THIS_ ID3D10Device **ppDevice) PURE;
};

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//----------------------------------------------------------------------------
// D3D10_STATE_BLOCK_MASK and manipulation functions
// -------------------------------------------------
//
// These functions exist to facilitate working with the D3D10_STATE_BLOCK_MASK
// structure.
//
// D3D10_STATE_BLOCK_MASK *pResult or *pMask
//   The state block mask to operate on
//
// D3D10_STATE_BLOCK_MASK *pA, *pB
//   The source state block masks for the binary union/intersect/difference
//   operations.
//
// D3D10_DEVICE_STATE_TYPES StateType
//   The specific state type to enable/disable/query
//
// UINT RangeStart, RangeLength, Entry
//   The specific bit or range of bits for a given state type to operate on.
//   Consult the comments for D3D10_DEVICE_STATE_TYPES and 
//   D3D10_STATE_BLOCK_MASK for information on the valid bit ranges for 
//   each state.
//
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10StateBlockMaskUnion(_In_ D3D10_STATE_BLOCK_MASK *pA, _In_ D3D10_STATE_BLOCK_MASK *pB, _Out_ D3D10_STATE_BLOCK_MASK *pResult);
HRESULT WINAPI D3D10StateBlockMaskIntersect(_In_ D3D10_STATE_BLOCK_MASK *pA, _In_ D3D10_STATE_BLOCK_MASK *pB, _Out_ D3D10_STATE_BLOCK_MASK *pResult);
HRESULT WINAPI D3D10StateBlockMaskDifference(_In_ D3D10_STATE_BLOCK_MASK *pA, _In_ D3D10_STATE_BLOCK_MASK *pB, _Out_ D3D10_STATE_BLOCK_MASK *pResult);
HRESULT WINAPI D3D10StateBlockMaskEnableCapture(_Inout_ D3D10_STATE_BLOCK_MASK *pMask, D3D10_DEVICE_STATE_TYPES StateType, UINT RangeStart, UINT RangeLength);
HRESULT WINAPI D3D10StateBlockMaskDisableCapture(_Inout_ D3D10_STATE_BLOCK_MASK *pMask, D3D10_DEVICE_STATE_TYPES StateType, UINT RangeStart, UINT RangeLength);
HRESULT WINAPI D3D10StateBlockMaskEnableAll(_Out_ D3D10_STATE_BLOCK_MASK *pMask);
HRESULT WINAPI D3D10StateBlockMaskDisableAll(_Out_ D3D10_STATE_BLOCK_MASK *pMask);
BOOL    WINAPI D3D10StateBlockMaskGetSetting(_In_ D3D10_STATE_BLOCK_MASK *pMask, D3D10_DEVICE_STATE_TYPES StateType, UINT Entry);

//----------------------------------------------------------------------------
// D3D10CreateStateBlock
// ---------------------
//
// Creates a state block object based on the mask settings specified
//   in a D3D10_STATE_BLOCK_MASK structure.
//
// ID3D10Device *pDevice
//      The device interface to associate with this state block
//
// D3D10_STATE_BLOCK_MASK *pStateBlockMask
//      A bit mask whose settings are used to generate a state block
//      object.
//
// ID3D10StateBlock **ppStateBlock
//      The resulting state block object.  This object will save/restore
//      only those pieces of state that were set in the state block
//      bit mask
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10CreateStateBlock(_In_ ID3D10Device *pDevice, _In_ D3D10_STATE_BLOCK_MASK *pStateBlockMask, _Out_ ID3D10StateBlock **ppStateBlock);

#ifdef __cplusplus
}
#endif //__cplusplus

//----------------------------------------------------------------------------
// D3D10_COMPILE & D3D10_EFFECT flags:
// -------------------------------------
//
// These flags are passed in when creating an effect, and affect
// either compilation behavior or runtime effect behavior
//
// D3D10_EFFECT_COMPILE_CHILD_EFFECT
//   Compile this .fx file to a child effect. Child effects have no initializers
//   for any shared values as these are initialied in the master effect (pool).
//
// D3D10_EFFECT_COMPILE_ALLOW_SLOW_OPS
//   By default, performance mode is enabled.  Performance mode disallows
//   mutable state objects by preventing non-literal expressions from appearing in
//   state object definitions.  Specifying this flag will disable the mode and allow
//   for mutable state objects.
//
// D3D10_EFFECT_SINGLE_THREADED
//   Do not attempt to synchronize with other threads loading effects into the
//   same pool.
//
//----------------------------------------------------------------------------

#define D3D10_EFFECT_COMPILE_CHILD_EFFECT              (1 << 0)
#define D3D10_EFFECT_COMPILE_ALLOW_SLOW_OPS            (1 << 1)
#define D3D10_EFFECT_SINGLE_THREADED                   (1 << 3)


//----------------------------------------------------------------------------
// D3D10_EFFECT_VARIABLE flags:
// ----------------------------
//
// These flags describe an effect variable (global or annotation),
// and are returned in D3D10_EFFECT_VARIABLE_DESC::Flags.
//
// D3D10_EFFECT_VARIABLE_POOLED
//   Indicates that the this variable or constant buffer resides
//   in an effect pool. If this flag is not set, then the variable resides
//   in a standalone effect (if ID3D10Effect::GetPool returns NULL)
//   or a child effect (if ID3D10Effect::GetPool returns non-NULL)
//
// D3D10_EFFECT_VARIABLE_ANNOTATION
//   Indicates that this is an annotation on a technique, pass, or global
//   variable. Otherwise, this is a global variable. Annotations cannot
//   be shared.
//
// D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT
//   Indicates that the variable has been explicitly bound using the
//   register keyword.
//----------------------------------------------------------------------------

#define D3D10_EFFECT_VARIABLE_POOLED                  (1 << 0)
#define D3D10_EFFECT_VARIABLE_ANNOTATION              (1 << 1)
#define D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT     (1 << 2)

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectType //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3D10_EFFECT_TYPE_DESC:
//
// Retrieved by ID3D10EffectType::GetDesc()
//----------------------------------------------------------------------------

typedef struct _D3D10_EFFECT_TYPE_DESC
{
    LPCSTR  TypeName;               // Name of the type 
                                    // (e.g. "float4" or "MyStruct")

    D3D10_SHADER_VARIABLE_CLASS    Class;  // (e.g. scalar, vector, object, etc.)
    D3D10_SHADER_VARIABLE_TYPE     Type;   // (e.g. float, texture, vertexshader, etc.)
    
    UINT    Elements;               // Number of elements in this type
                                    // (0 if not an array) 
    UINT    Members;                // Number of members
                                    // (0 if not a structure)
    UINT    Rows;                   // Number of rows in this type
                                    // (0 if not a numeric primitive)
    UINT    Columns;                // Number of columns in this type
                                    // (0 if not a numeric primitive)
    
    UINT    PackedSize;             // Number of bytes required to represent
                                    // this data type, when tightly packed
    UINT    UnpackedSize;           // Number of bytes occupied by this data
                                    // type, when laid out in a constant buffer
    UINT    Stride;                 // Number of bytes to seek between elements,
                                    // when laid out in a constant buffer
} D3D10_EFFECT_TYPE_DESC;

typedef interface ID3D10EffectType ID3D10EffectType;
typedef interface ID3D10EffectType *LPD3D10EFFECTTYPE;

// {4E9E1DDC-CD9D-4772-A837-00180B9B88FD}
DEFINE_GUID(IID_ID3D10EffectType, 
0x4e9e1ddc, 0xcd9d, 0x4772, 0xa8, 0x37, 0x0, 0x18, 0xb, 0x9b, 0x88, 0xfd);

#undef INTERFACE
#define INTERFACE ID3D10EffectType

DECLARE_INTERFACE(ID3D10EffectType)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3D10_EFFECT_TYPE_DESC *pDesc) PURE;
    STDMETHOD_(ID3D10EffectType*, GetMemberTypeByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectType*, GetMemberTypeByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectType*, GetMemberTypeBySemantic)(THIS_ LPCSTR Semantic) PURE;
    STDMETHOD_(LPCSTR, GetMemberName)(THIS_ UINT Index) PURE;
    STDMETHOD_(LPCSTR, GetMemberSemantic)(THIS_ UINT Index) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectVariable //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3D10_EFFECT_VARIABLE_DESC:
//
// Retrieved by ID3D10EffectVariable::GetDesc()
//----------------------------------------------------------------------------

typedef struct _D3D10_EFFECT_VARIABLE_DESC
{
    LPCSTR  Name;                   // Name of this variable, annotation, 
                                    // or structure member
    LPCSTR  Semantic;               // Semantic string of this variable
                                    // or structure member (NULL for 
                                    // annotations or if not present)
    
    UINT    Flags;                  // D3D10_EFFECT_VARIABLE_* flags
    UINT    Annotations;            // Number of annotations on this variable
                                    // (always 0 for annotations)

    UINT    BufferOffset;           // Offset into containing cbuffer or tbuffer
                                    // (always 0 for annotations or variables
                                    // not in constant buffers)

    UINT    ExplicitBindPoint;      // Used if the variable has been explicitly bound
                                    // using the register keyword. Check Flags for
                                    // D3D10_EFFECT_VARIABLE_EXPLICIT_BIND_POINT;
} D3D10_EFFECT_VARIABLE_DESC;

typedef interface ID3D10EffectVariable ID3D10EffectVariable;
typedef interface ID3D10EffectVariable *LPD3D10EFFECTVARIABLE;

// {AE897105-00E6-45bf-BB8E-281DD6DB8E1B}
DEFINE_GUID(IID_ID3D10EffectVariable, 
0xae897105, 0xe6, 0x45bf, 0xbb, 0x8e, 0x28, 0x1d, 0xd6, 0xdb, 0x8e, 0x1b);

#undef INTERFACE
#define INTERFACE ID3D10EffectVariable

// Forward defines
typedef interface ID3D10EffectScalarVariable ID3D10EffectScalarVariable;
typedef interface ID3D10EffectVectorVariable ID3D10EffectVectorVariable;
typedef interface ID3D10EffectMatrixVariable ID3D10EffectMatrixVariable;
typedef interface ID3D10EffectStringVariable ID3D10EffectStringVariable;
typedef interface ID3D10EffectShaderResourceVariable ID3D10EffectShaderResourceVariable;
typedef interface ID3D10EffectRenderTargetViewVariable ID3D10EffectRenderTargetViewVariable;
typedef interface ID3D10EffectDepthStencilViewVariable ID3D10EffectDepthStencilViewVariable;
typedef interface ID3D10EffectConstantBuffer ID3D10EffectConstantBuffer;
typedef interface ID3D10EffectShaderVariable ID3D10EffectShaderVariable;
typedef interface ID3D10EffectBlendVariable ID3D10EffectBlendVariable;
typedef interface ID3D10EffectDepthStencilVariable ID3D10EffectDepthStencilVariable;
typedef interface ID3D10EffectRasterizerVariable ID3D10EffectRasterizerVariable;
typedef interface ID3D10EffectSamplerVariable ID3D10EffectSamplerVariable;

DECLARE_INTERFACE(ID3D10EffectVariable)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;

    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectScalarVariable ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectScalarVariable ID3D10EffectScalarVariable;
typedef interface ID3D10EffectScalarVariable *LPD3D10EFFECTSCALARVARIABLE;

// {00E48F7B-D2C8-49e8-A86C-022DEE53431F}
DEFINE_GUID(IID_ID3D10EffectScalarVariable, 
0xe48f7b, 0xd2c8, 0x49e8, 0xa8, 0x6c, 0x2, 0x2d, 0xee, 0x53, 0x43, 0x1f);

#undef INTERFACE
#define INTERFACE ID3D10EffectScalarVariable

DECLARE_INTERFACE_(ID3D10EffectScalarVariable, ID3D10EffectVariable)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT ByteOffset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT ByteOffset, UINT ByteCount) PURE;
    
    STDMETHOD(SetFloat)(THIS_ float Value) PURE;
    STDMETHOD(GetFloat)(THIS_ _Out_ float *pValue) PURE;    
    
    STDMETHOD(SetFloatArray)(THIS_ _In_reads_(Count) float *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetFloatArray)(THIS_ _Out_writes_(Count) float *pData, UINT Offset, UINT Count) PURE;
    
    STDMETHOD(SetInt)(THIS_ int Value) PURE;
    STDMETHOD(GetInt)(THIS_ _Out_ int *pValue) PURE;
    
    STDMETHOD(SetIntArray)(THIS_ _In_reads_(Count) int *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetIntArray)(THIS_ _Out_writes_(Count) int *pData, UINT Offset, UINT Count) PURE;
    
    STDMETHOD(SetBool)(THIS_ BOOL Value) PURE;
    STDMETHOD(GetBool)(THIS_ _Out_ BOOL *pValue) PURE;
    
    STDMETHOD(SetBoolArray)(THIS_ _In_reads_(Count) BOOL *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetBoolArray)(THIS_ _Out_writes_(Count) BOOL *pData, UINT Offset, UINT Count) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectVectorVariable ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectVectorVariable ID3D10EffectVectorVariable;
typedef interface ID3D10EffectVectorVariable *LPD3D10EFFECTVECTORVARIABLE;

// {62B98C44-1F82-4c67-BCD0-72CF8F217E81}
DEFINE_GUID(IID_ID3D10EffectVectorVariable, 
0x62b98c44, 0x1f82, 0x4c67, 0xbc, 0xd0, 0x72, 0xcf, 0x8f, 0x21, 0x7e, 0x81);

#undef INTERFACE
#define INTERFACE ID3D10EffectVectorVariable

DECLARE_INTERFACE_(ID3D10EffectVectorVariable, ID3D10EffectVariable)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE; 
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT ByteOffset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT ByteOffset, UINT ByteCount) PURE;
    
    STDMETHOD(SetBoolVector) (THIS_ BOOL *pData) PURE;
    STDMETHOD(SetIntVector)  (THIS_ int *pData) PURE;
    STDMETHOD(SetFloatVector)(THIS_ float *pData) PURE;

    STDMETHOD(GetBoolVector) (THIS_ BOOL *pData) PURE;
    STDMETHOD(GetIntVector)  (THIS_ int *pData) PURE;
    STDMETHOD(GetFloatVector)(THIS_ float *pData) PURE;

    STDMETHOD(SetBoolVectorArray) (THIS_ BOOL *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(SetIntVectorArray)  (THIS_ int *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(SetFloatVectorArray)(THIS_ float *pData, UINT Offset, UINT Count) PURE;

    STDMETHOD(GetBoolVectorArray) (THIS_ BOOL *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetIntVectorArray)  (THIS_ int *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetFloatVectorArray)(THIS_ float *pData, UINT Offset, UINT Count) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectMatrixVariable ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectMatrixVariable ID3D10EffectMatrixVariable;
typedef interface ID3D10EffectMatrixVariable *LPD3D10EFFECTMATRIXVARIABLE;

// {50666C24-B82F-4eed-A172-5B6E7E8522E0}
DEFINE_GUID(IID_ID3D10EffectMatrixVariable, 
0x50666c24, 0xb82f, 0x4eed, 0xa1, 0x72, 0x5b, 0x6e, 0x7e, 0x85, 0x22, 0xe0);

#undef INTERFACE
#define INTERFACE ID3D10EffectMatrixVariable

DECLARE_INTERFACE_(ID3D10EffectMatrixVariable, ID3D10EffectVariable)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT ByteOffset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT ByteOffset, UINT ByteCount) PURE;
    
    STDMETHOD(SetMatrix)(THIS_ float *pData) PURE;
    STDMETHOD(GetMatrix)(THIS_ float *pData) PURE;
    
    STDMETHOD(SetMatrixArray)(THIS_ float *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetMatrixArray)(THIS_ float *pData, UINT Offset, UINT Count) PURE;
    
    STDMETHOD(SetMatrixTranspose)(THIS_ float *pData) PURE;
    STDMETHOD(GetMatrixTranspose)(THIS_ float *pData) PURE;
    
    STDMETHOD(SetMatrixTransposeArray)(THIS_ float *pData, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetMatrixTransposeArray)(THIS_ float *pData, UINT Offset, UINT Count) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectStringVariable ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectStringVariable ID3D10EffectStringVariable;
typedef interface ID3D10EffectStringVariable *LPD3D10EFFECTSTRINGVARIABLE;

// {71417501-8DF9-4e0a-A78A-255F9756BAFF}
DEFINE_GUID(IID_ID3D10EffectStringVariable, 
0x71417501, 0x8df9, 0x4e0a, 0xa7, 0x8a, 0x25, 0x5f, 0x97, 0x56, 0xba, 0xff);

#undef INTERFACE
#define INTERFACE ID3D10EffectStringVariable

DECLARE_INTERFACE_(ID3D10EffectStringVariable, ID3D10EffectVariable)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(GetString)(THIS_ _Out_ LPCSTR *ppString) PURE;
    STDMETHOD(GetStringArray)(THIS_ _Out_writes_(Count) LPCSTR *ppStrings, UINT Offset, UINT Count) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectShaderResourceVariable ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectShaderResourceVariable ID3D10EffectShaderResourceVariable;
typedef interface ID3D10EffectShaderResourceVariable *LPD3D10EFFECTSHADERRESOURCEVARIABLE;

// {C0A7157B-D872-4b1d-8073-EFC2ACD4B1FC}
DEFINE_GUID(IID_ID3D10EffectShaderResourceVariable, 
0xc0a7157b, 0xd872, 0x4b1d, 0x80, 0x73, 0xef, 0xc2, 0xac, 0xd4, 0xb1, 0xfc);


#undef INTERFACE
#define INTERFACE ID3D10EffectShaderResourceVariable

DECLARE_INTERFACE_(ID3D10EffectShaderResourceVariable, ID3D10EffectVariable)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(SetResource)(THIS_ _In_opt_ ID3D10ShaderResourceView *pResource) PURE;
    STDMETHOD(GetResource)(THIS_ _Out_ ID3D10ShaderResourceView **ppResource) PURE;
    
    STDMETHOD(SetResourceArray)(THIS_ _In_reads_(Count) ID3D10ShaderResourceView **ppResources, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetResourceArray)(THIS_ _Out_writes_(Count) ID3D10ShaderResourceView **ppResources, UINT Offset, UINT Count) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectRenderTargetViewVariable //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectRenderTargetViewVariable ID3D10EffectRenderTargetViewVariable;
typedef interface ID3D10EffectRenderTargetViewVariable *LPD3D10EFFECTRENDERTARGETVIEWVARIABLE;

// {28CA0CC3-C2C9-40bb-B57F-67B737122B17}
DEFINE_GUID(IID_ID3D10EffectRenderTargetViewVariable, 
0x28ca0cc3, 0xc2c9, 0x40bb, 0xb5, 0x7f, 0x67, 0xb7, 0x37, 0x12, 0x2b, 0x17);

#undef INTERFACE
#define INTERFACE ID3D10EffectRenderTargetViewVariable

DECLARE_INTERFACE_(ID3D10EffectRenderTargetViewVariable, ID3D10EffectVariable)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(SetRenderTarget)(THIS_ _In_opt_ ID3D10RenderTargetView *pResource) PURE;
    STDMETHOD(GetRenderTarget)(THIS_ _Out_ ID3D10RenderTargetView **ppResource) PURE;
    
    STDMETHOD(SetRenderTargetArray)(THIS_ _In_reads_(Count) ID3D10RenderTargetView **ppResources, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetRenderTargetArray)(THIS_ _Out_writes_(Count) ID3D10RenderTargetView **ppResources, UINT Offset, UINT Count) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectDepthStencilViewVariable //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectDepthStencilViewVariable ID3D10EffectDepthStencilViewVariable;
typedef interface ID3D10EffectDepthStencilViewVariable *LPD3D10EFFECTDEPTHSTENCILVIEWVARIABLE;

// {3E02C918-CC79-4985-B622-2D92AD701623}
DEFINE_GUID(IID_ID3D10EffectDepthStencilViewVariable, 
0x3e02c918, 0xcc79, 0x4985, 0xb6, 0x22, 0x2d, 0x92, 0xad, 0x70, 0x16, 0x23);

#undef INTERFACE
#define INTERFACE ID3D10EffectDepthStencilViewVariable

DECLARE_INTERFACE_(ID3D10EffectDepthStencilViewVariable, ID3D10EffectVariable)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(SetDepthStencil)(THIS_ _In_opt_ ID3D10DepthStencilView *pResource) PURE;
    STDMETHOD(GetDepthStencil)(THIS_ _Out_ ID3D10DepthStencilView **ppResource) PURE;
    
    STDMETHOD(SetDepthStencilArray)(THIS_ _In_reads_(Count) ID3D10DepthStencilView **ppResources, UINT Offset, UINT Count) PURE;
    STDMETHOD(GetDepthStencilArray)(THIS_ _Out_writes_(Count) ID3D10DepthStencilView **ppResources, UINT Offset, UINT Count) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectConstantBuffer ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectConstantBuffer ID3D10EffectConstantBuffer;
typedef interface ID3D10EffectConstantBuffer *LPD3D10EFFECTCONSTANTBUFFER;

// {56648F4D-CC8B-4444-A5AD-B5A3D76E91B3}
DEFINE_GUID(IID_ID3D10EffectConstantBuffer, 
0x56648f4d, 0xcc8b, 0x4444, 0xa5, 0xad, 0xb5, 0xa3, 0xd7, 0x6e, 0x91, 0xb3);

#undef INTERFACE
#define INTERFACE ID3D10EffectConstantBuffer

DECLARE_INTERFACE_(ID3D10EffectConstantBuffer, ID3D10EffectVariable)
{
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(SetConstantBuffer)(THIS_ _In_opt_ ID3D10Buffer *pConstantBuffer) PURE;
    STDMETHOD(GetConstantBuffer)(THIS_ _Out_ ID3D10Buffer **ppConstantBuffer) PURE;
    
    STDMETHOD(SetTextureBuffer)(THIS_ _In_opt_ ID3D10ShaderResourceView *pTextureBuffer) PURE;
    STDMETHOD(GetTextureBuffer)(THIS_ _Out_ ID3D10ShaderResourceView **ppTextureBuffer) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectShaderVariable ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3D10_EFFECT_SHADER_DESC:
//
// Retrieved by ID3D10EffectShaderVariable::GetShaderDesc()
//----------------------------------------------------------------------------

typedef struct _D3D10_EFFECT_SHADER_DESC
{
    CONST BYTE *pInputSignature;    // Passed into CreateInputLayout,
                                    // valid on VS and GS only
    
    BOOL IsInline;                  // Is this an anonymous shader variable
                                    // resulting from an inline shader assignment?
    
    
    // -- The following fields are not valid after Optimize() --
    CONST BYTE *pBytecode;          // Shader bytecode
    UINT BytecodeLength;
    
    LPCSTR SODecl;                  // Stream out declaration string (for GS with SO)
    
    UINT NumInputSignatureEntries;  // Number of entries in the input signature
    UINT NumOutputSignatureEntries; // Number of entries in the output signature
} D3D10_EFFECT_SHADER_DESC;


typedef interface ID3D10EffectShaderVariable ID3D10EffectShaderVariable;
typedef interface ID3D10EffectShaderVariable *LPD3D10EFFECTSHADERVARIABLE;

// {80849279-C799-4797-8C33-0407A07D9E06}
DEFINE_GUID(IID_ID3D10EffectShaderVariable, 
0x80849279, 0xc799, 0x4797, 0x8c, 0x33, 0x4, 0x7, 0xa0, 0x7d, 0x9e, 0x6);

#undef INTERFACE
#define INTERFACE ID3D10EffectShaderVariable

DECLARE_INTERFACE_(ID3D10EffectShaderVariable, ID3D10EffectVariable)
{
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
        
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(GetShaderDesc)(THIS_ UINT ShaderIndex, _Out_ D3D10_EFFECT_SHADER_DESC *pDesc) PURE;
    
    STDMETHOD(GetVertexShader)(THIS_ UINT ShaderIndex, _Out_ ID3D10VertexShader **ppVS) PURE;
    STDMETHOD(GetGeometryShader)(THIS_ UINT ShaderIndex, _Out_ ID3D10GeometryShader **ppGS) PURE;
    STDMETHOD(GetPixelShader)(THIS_ UINT ShaderIndex, _Out_ ID3D10PixelShader **ppPS) PURE;
    
    STDMETHOD(GetInputSignatureElementDesc)(THIS_ UINT ShaderIndex, UINT Element, _Out_ D3D10_SIGNATURE_PARAMETER_DESC *pDesc) PURE;
    STDMETHOD(GetOutputSignatureElementDesc)(THIS_ UINT ShaderIndex, UINT Element, _Out_ D3D10_SIGNATURE_PARAMETER_DESC *pDesc) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectBlendVariable /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectBlendVariable ID3D10EffectBlendVariable;
typedef interface ID3D10EffectBlendVariable *LPD3D10EFFECTBLENDVARIABLE;

// {1FCD2294-DF6D-4eae-86B3-0E9160CFB07B}
DEFINE_GUID(IID_ID3D10EffectBlendVariable, 
0x1fcd2294, 0xdf6d, 0x4eae, 0x86, 0xb3, 0xe, 0x91, 0x60, 0xcf, 0xb0, 0x7b);

#undef INTERFACE
#define INTERFACE ID3D10EffectBlendVariable

DECLARE_INTERFACE_(ID3D10EffectBlendVariable, ID3D10EffectVariable)
{
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(GetBlendState)(THIS_ UINT Index, ID3D10BlendState **ppBlendState) PURE;
    STDMETHOD(GetBackingStore)(THIS_ UINT Index, D3D10_BLEND_DESC *pBlendDesc) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectDepthStencilVariable //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectDepthStencilVariable ID3D10EffectDepthStencilVariable;
typedef interface ID3D10EffectDepthStencilVariable *LPD3D10EFFECTDEPTHSTENCILVARIABLE;

// {AF482368-330A-46a5-9A5C-01C71AF24C8D}
DEFINE_GUID(IID_ID3D10EffectDepthStencilVariable, 
0xaf482368, 0x330a, 0x46a5, 0x9a, 0x5c, 0x1, 0xc7, 0x1a, 0xf2, 0x4c, 0x8d);

#undef INTERFACE
#define INTERFACE ID3D10EffectDepthStencilVariable

DECLARE_INTERFACE_(ID3D10EffectDepthStencilVariable, ID3D10EffectVariable)
{
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(GetDepthStencilState)(THIS_ UINT Index, _Out_ ID3D10DepthStencilState **ppDepthStencilState) PURE;
    STDMETHOD(GetBackingStore)(THIS_ UINT Index, _Out_ D3D10_DEPTH_STENCIL_DESC *pDepthStencilDesc) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectRasterizerVariable ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectRasterizerVariable ID3D10EffectRasterizerVariable;
typedef interface ID3D10EffectRasterizerVariable *LPD3D10EFFECTRASTERIZERVARIABLE;

// {21AF9F0E-4D94-4ea9-9785-2CB76B8C0B34}
DEFINE_GUID(IID_ID3D10EffectRasterizerVariable, 
0x21af9f0e, 0x4d94, 0x4ea9, 0x97, 0x85, 0x2c, 0xb7, 0x6b, 0x8c, 0xb, 0x34);

#undef INTERFACE
#define INTERFACE ID3D10EffectRasterizerVariable

DECLARE_INTERFACE_(ID3D10EffectRasterizerVariable, ID3D10EffectVariable)
{
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(GetRasterizerState)(THIS_ UINT Index, _Out_ ID3D10RasterizerState **ppRasterizerState) PURE;
    STDMETHOD(GetBackingStore)(THIS_ UINT Index, _Out_ D3D10_RASTERIZER_DESC *pRasterizerDesc) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectSamplerVariable ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectSamplerVariable ID3D10EffectSamplerVariable;
typedef interface ID3D10EffectSamplerVariable *LPD3D10EFFECTSAMPLERVARIABLE;

// {6530D5C7-07E9-4271-A418-E7CE4BD1E480}
DEFINE_GUID(IID_ID3D10EffectSamplerVariable, 
0x6530d5c7, 0x7e9, 0x4271, 0xa4, 0x18, 0xe7, 0xce, 0x4b, 0xd1, 0xe4, 0x80);

#undef INTERFACE
#define INTERFACE ID3D10EffectSamplerVariable

DECLARE_INTERFACE_(ID3D10EffectSamplerVariable, ID3D10EffectVariable)
{
    STDMETHOD_(ID3D10EffectType*, GetType)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_VARIABLE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetMemberBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetElement)(THIS_ UINT Index) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetParentConstantBuffer)(THIS) PURE;
    
    STDMETHOD_(ID3D10EffectScalarVariable*, AsScalar)(THIS) PURE;
    STDMETHOD_(ID3D10EffectVectorVariable*, AsVector)(THIS) PURE;
    STDMETHOD_(ID3D10EffectMatrixVariable*, AsMatrix)(THIS) PURE;
    STDMETHOD_(ID3D10EffectStringVariable*, AsString)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderResourceVariable*, AsShaderResource)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRenderTargetViewVariable*, AsRenderTargetView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilViewVariable*, AsDepthStencilView)(THIS) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, AsConstantBuffer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectShaderVariable*, AsShader)(THIS) PURE;
    STDMETHOD_(ID3D10EffectBlendVariable*, AsBlend)(THIS) PURE;
    STDMETHOD_(ID3D10EffectDepthStencilVariable*, AsDepthStencil)(THIS) PURE;
    STDMETHOD_(ID3D10EffectRasterizerVariable*, AsRasterizer)(THIS) PURE;
    STDMETHOD_(ID3D10EffectSamplerVariable*, AsSampler)(THIS) PURE;
    
    STDMETHOD(SetRawValue)(THIS_ _In_reads_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    STDMETHOD(GetRawValue)(THIS_ _Out_writes_bytes_(ByteCount) void *pData, UINT Offset, UINT ByteCount) PURE;
    
    STDMETHOD(GetSampler)(THIS_ UINT Index, _Out_ ID3D10SamplerState **ppSampler) PURE;
    STDMETHOD(GetBackingStore)(THIS_ UINT Index, _Out_ D3D10_SAMPLER_DESC *pSamplerDesc) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectPass //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3D10_PASS_DESC:
//
// Retrieved by ID3D10EffectPass::GetDesc()
//----------------------------------------------------------------------------

typedef struct _D3D10_PASS_DESC
{
    LPCSTR Name;                    // Name of this pass (NULL if not anonymous)    
    UINT Annotations;               // Number of annotations on this pass
    
    BYTE *pIAInputSignature;        // Signature from VS or GS (if there is no VS)
                                    // or NULL if neither exists
    SIZE_T IAInputSignatureSize;    // Singature size in bytes                                
                                    
    UINT StencilRef;                // Specified in SetDepthStencilState()
    UINT SampleMask;                // Specified in SetBlendState()
    FLOAT BlendFactor[4];           // Specified in SetBlendState()
} D3D10_PASS_DESC;

//----------------------------------------------------------------------------
// D3D10_PASS_SHADER_DESC:
//
// Retrieved by ID3D10EffectPass::Get**ShaderDesc()
//----------------------------------------------------------------------------

typedef struct _D3D10_PASS_SHADER_DESC
{
    ID3D10EffectShaderVariable *pShaderVariable;    // The variable that this shader came from.
                                                    // If this is an inline shader assignment,
                                                    //   the returned interface will be an 
                                                    //   anonymous shader variable, which is
                                                    //   not retrievable any other way.  It's
                                                    //   name in the variable description will
                                                    //   be "$Anonymous".
                                                    // If there is no assignment of this type in
                                                    //   the pass block, pShaderVariable != NULL,
                                                    //   but pShaderVariable->IsValid() == FALSE.
    
    UINT                        ShaderIndex;        // The element of pShaderVariable (if an array)
                                                    // or 0 if not applicable
} D3D10_PASS_SHADER_DESC;

typedef interface ID3D10EffectPass ID3D10EffectPass;
typedef interface ID3D10EffectPass *LPD3D10EFFECTPASS;

// {5CFBEB89-1A06-46e0-B282-E3F9BFA36A54}
DEFINE_GUID(IID_ID3D10EffectPass, 
0x5cfbeb89, 0x1a06, 0x46e0, 0xb2, 0x82, 0xe3, 0xf9, 0xbf, 0xa3, 0x6a, 0x54);

#undef INTERFACE
#define INTERFACE ID3D10EffectPass

DECLARE_INTERFACE(ID3D10EffectPass)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3D10_PASS_DESC *pDesc) PURE;
    
    STDMETHOD(GetVertexShaderDesc)(THIS_ D3D10_PASS_SHADER_DESC *pDesc) PURE;
    STDMETHOD(GetGeometryShaderDesc)(THIS_ D3D10_PASS_SHADER_DESC *pDesc) PURE;
    STDMETHOD(GetPixelShaderDesc)(THIS_ D3D10_PASS_SHADER_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD(Apply)(THIS_ UINT Flags) PURE;
    
    STDMETHOD(ComputeStateBlockMask)(THIS_ _Out_ D3D10_STATE_BLOCK_MASK *pStateBlockMask) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectTechnique /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3D10_TECHNIQUE_DESC:
//
// Retrieved by ID3D10EffectTechnique::GetDesc()
//----------------------------------------------------------------------------

typedef struct _D3D10_TECHNIQUE_DESC
{
    LPCSTR  Name;                   // Name of this technique (NULL if not anonymous)
    UINT    Passes;                 // Number of passes contained within
    UINT    Annotations;            // Number of annotations on this technique
} D3D10_TECHNIQUE_DESC;

typedef interface ID3D10EffectTechnique ID3D10EffectTechnique;
typedef interface ID3D10EffectTechnique *LPD3D10EFFECTTECHNIQUE;

// {DB122CE8-D1C9-4292-B237-24ED3DE8B175}
DEFINE_GUID(IID_ID3D10EffectTechnique, 
0xdb122ce8, 0xd1c9, 0x4292, 0xb2, 0x37, 0x24, 0xed, 0x3d, 0xe8, 0xb1, 0x75);

#undef INTERFACE
#define INTERFACE ID3D10EffectTechnique

DECLARE_INTERFACE(ID3D10EffectTechnique)
{
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3D10_TECHNIQUE_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetAnnotationByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectPass*, GetPassByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectPass*, GetPassByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD(ComputeStateBlockMask)(THIS_ _Out_ D3D10_STATE_BLOCK_MASK *pStateBlockMask) PURE;
};

//////////////////////////////////////////////////////////////////////////////
// ID3D10Effect //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3D10_EFFECT_DESC:
//
// Retrieved by ID3D10Effect::GetDesc()
//----------------------------------------------------------------------------

typedef struct _D3D10_EFFECT_DESC
{
    
    BOOL    IsChildEffect;          // TRUE if this is a child effect, 
                                    // FALSE if this is standalone or an effect pool.
                                    
    UINT    ConstantBuffers;        // Number of constant buffers in this effect,
                                    // excluding the effect pool.
    UINT    SharedConstantBuffers;  // Number of constant buffers shared in this
                                    // effect's pool.
                                    
    UINT    GlobalVariables;        // Number of global variables in this effect,
                                    // excluding the effect pool.
    UINT    SharedGlobalVariables;  // Number of global variables shared in this
                                    // effect's pool.
                                    
    UINT    Techniques;             // Number of techniques in this effect,
                                    // excluding the effect pool.
} D3D10_EFFECT_DESC;

typedef interface ID3D10Effect ID3D10Effect;
typedef interface ID3D10Effect *LPD3D10EFFECT;

// {51B0CA8B-EC0B-4519-870D-8EE1CB5017C7}
DEFINE_GUID(IID_ID3D10Effect, 
0x51b0ca8b, 0xec0b, 0x4519, 0x87, 0xd, 0x8e, 0xe1, 0xcb, 0x50, 0x17, 0xc7);

#undef INTERFACE
#define INTERFACE ID3D10Effect

DECLARE_INTERFACE_(ID3D10Effect, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    
    STDMETHOD_(BOOL, IsValid)(THIS) PURE;
    STDMETHOD_(BOOL, IsPool)(THIS) PURE;

    // Managing D3D Device
    STDMETHOD(GetDevice)(THIS_ _Out_ ID3D10Device** ppDevice) PURE;
    
    // New Reflection APIs
    STDMETHOD(GetDesc)(THIS_ _Out_ D3D10_EFFECT_DESC *pDesc) PURE;
    
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetConstantBufferByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectConstantBuffer*, GetConstantBufferByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD_(ID3D10EffectVariable*, GetVariableByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetVariableByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD_(ID3D10EffectVariable*, GetVariableBySemantic)(THIS_ LPCSTR Semantic) PURE;
    
    STDMETHOD_(ID3D10EffectTechnique*, GetTechniqueByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(ID3D10EffectTechnique*, GetTechniqueByName)(THIS_ LPCSTR Name) PURE;
    
    STDMETHOD(Optimize)(THIS) PURE;
    STDMETHOD_(BOOL, IsOptimized)(THIS) PURE;

};

//////////////////////////////////////////////////////////////////////////////
// ID3D10EffectPool //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef interface ID3D10EffectPool ID3D10EffectPool;
typedef interface ID3D10EffectPool *LPD3D10EFFECTPOOL;

// {9537AB04-3250-412e-8213-FCD2F8677933}
DEFINE_GUID(IID_ID3D10EffectPool, 
0x9537ab04, 0x3250, 0x412e, 0x82, 0x13, 0xfc, 0xd2, 0xf8, 0x67, 0x79, 0x33);

#undef INTERFACE
#define INTERFACE ID3D10EffectPool

DECLARE_INTERFACE_(ID3D10EffectPool, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    
    STDMETHOD_(ID3D10Effect*, AsEffect)(THIS) PURE;
    
    // No public methods
};

//////////////////////////////////////////////////////////////////////////////
// APIs //////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//----------------------------------------------------------------------------
// D3D10CreateEffectFromXXXX:
// --------------------------
// Creates an effect from a binary effect or file
//
// Parameters:
//
// [in]
//
//
//  pData
//      Blob of effect data, either ASCII (uncompiled, for D3D10CompileEffectFromMemory) or binary (compiled, for D3D10CreateEffect*)
//  DataLength
//      Length of the data blob
//
//  pSrcFileName
//      Name of the ASCII Effect file pData was obtained from
//
//  pDefines
//      Optional NULL-terminated array of preprocessor macro definitions.
//  pInclude
//      Optional interface pointer to use for handling #include directives.
//      If this parameter is NULL, #includes will be honored when compiling
//      from file, and will error when compiling from resource or memory.
//  HLSLFlags
//      Compilation flags pertaining to shaders and data types, honored by
//      the HLSL compiler
//  FXFlags
//      Compilation flags pertaining to Effect compilation, honored
//      by the Effect compiler
//  pDevice
//      Pointer to the D3D10 device on which to create Effect resources
//  pEffectPool
//      Pointer to an Effect pool to share variables with or NULL
//
// [out]
//
//  ppEffect
//      Address of the newly created Effect interface
//  ppEffectPool
//      Address of the newly created Effect pool interface
//  ppErrors
//      If non-NULL, address of a buffer with error messages that occurred 
//      during parsing or compilation
//
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10CompileEffectFromMemory(_In_reads_bytes_(DataLength) void *pData, SIZE_T DataLength, LPCSTR pSrcFileName, _In_opt_ CONST D3D10_SHADER_MACRO *pDefines, 
    _In_opt_ ID3D10Include *pInclude, UINT HLSLFlags, UINT FXFlags, 
    _Out_ ID3D10Blob **ppCompiledEffect, _Out_opt_ ID3D10Blob **ppErrors);

HRESULT WINAPI D3D10CreateEffectFromMemory(_In_reads_bytes_(DataLength) void *pData, SIZE_T DataLength, UINT FXFlags, _In_ ID3D10Device *pDevice, 
    _In_opt_ ID3D10EffectPool *pEffectPool, _Out_ ID3D10Effect **ppEffect);

HRESULT WINAPI D3D10CreateEffectPoolFromMemory(_In_reads_bytes_(DataLength) void *pData, SIZE_T DataLength, UINT FXFlags, _In_ ID3D10Device *pDevice,
    _Out_ ID3D10EffectPool **ppEffectPool);


//----------------------------------------------------------------------------
// D3D10DisassembleEffect:
// -----------------------
// Takes an effect interface, and returns a buffer containing text assembly.
//
// Parameters:
//  pEffect
//      Pointer to the runtime effect interface.
//  EnableColorCode
//      Emit HTML tags for color coding the output?
//  ppDisassembly
//      Returns a buffer containing the disassembled effect.
//----------------------------------------------------------------------------

HRESULT WINAPI D3D10DisassembleEffect(_In_ ID3D10Effect *pEffect, BOOL EnableColorCode, _Out_ ID3D10Blob **ppDisassembly);

#ifdef __cplusplus
}
#endif //__cplusplus


#endif //__D3D10EFFECT_H__


