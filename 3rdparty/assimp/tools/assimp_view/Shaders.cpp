/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2015, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the following 
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/
#include "assimp_view.h"

namespace AssimpView  {

// ------------------------------------------------------------------------------------------------
std::string g_szNormalsShader = std::string(

    // World * View * Projection matrix\n"
    // NOTE: Assume that the material uses a WorldViewProjection matrix\n"
    "float4x4 WorldViewProjection	: WORLDVIEWPROJECTION;\n"
    "float4 OUTPUT_COLOR;\n"
    
    // Vertex shader input structure
    "struct VS_INPUT\n"
    "{\n"
        "// Position\n"
        "float3 Position : POSITION;\n"
    "};\n"

    // Vertex shader output structure for pixel shader usage
    "struct VS_OUTPUT\n"
  "{\n"
        "float4 Position : POSITION;\n"
    "};\n"

    // Vertex shader output structure for FixedFunction usage
    "struct VS_OUTPUT_FF\n"
    "{\n"
        "float4 Position : POSITION;\n"
    "float4 Color : COLOR;\n"
    "};\n"

    // Vertex shader for rendering normals using pixel shader
    "VS_OUTPUT RenderNormalsVS(VS_INPUT IN)\n"
    "{\n"
        "// Initialize the output structure with zero\n"
        "VS_OUTPUT Out = (VS_OUTPUT)0;\n"

        "// Multiply with the WorldViewProjection matrix\n"
        "Out.Position = mul(float4(IN.Position,1.0f),WorldViewProjection);\n"

        "return Out;\n"
    "}\n"

    // Vertex shader for rendering normals using fixed function pipeline
    "VS_OUTPUT_FF RenderNormalsVS_FF(VS_INPUT IN)\n"
  "{\n"
        "VS_OUTPUT_FF Out;\n"
        "Out.Position = mul(float4(IN.Position,1.0f),WorldViewProjection);\n"
    "Out.Color = OUTPUT_COLOR;\n"
        "return Out;\n"
    "}\n"

    // Pixel shader
    "float4 RenderNormalsPS() : COLOR\n"
    "{\n"
        "return OUTPUT_COLOR;\n"
    "}\n"

    // Technique for the normal rendering effect (ps_2_0)
    "technique RenderNormals\n"
    "{\n"
        "pass p0\n"
        "{\n"
        "CullMode=none;\n"
        "PixelShader = compile ps_2_0 RenderNormalsPS();\n"
        "VertexShader = compile vs_2_0 RenderNormalsVS();\n"
        "}\n"
    "};\n"

    // Technique for the normal rendering effect (fixed function)
    "technique RenderNormals_FF\n"
    "{\n"
        "pass p0\n"
        "{\n"
          "CullMode=none;\n"
          "VertexShader = compile vs_2_0 RenderNormalsVS_FF();\n"
      "ColorOp[0] = SelectArg1;\n"
      "ColorArg0[0] = Diffuse;\n"
      "AlphaOp[0] = SelectArg1;\n"
      "AlphaArg0[0] = Diffuse;\n"
        "}\n"
    "};\n"
    );

// ------------------------------------------------------------------------------------------------
std::string g_szSkyboxShader = std::string(

    // Sampler and texture for the skybox
    "textureCUBE lw_tex_envmap;\n"
    "samplerCUBE EnvironmentMapSampler = sampler_state\n"
    "{\n"
      "Texture = (lw_tex_envmap);\n"
      "AddressU = CLAMP;\n"
      "AddressV = CLAMP;\n"
      "AddressW = CLAMP;\n"

      "MAGFILTER = linear;\n"
      "MINFILTER = linear;\n"
    "};\n"

    // World * View * Projection matrix\n"
    // NOTE: Assume that the material uses a WorldViewProjection matrix\n"
    "float4x4 WorldViewProjection	: WORLDVIEWPROJECTION;\n"
    
    // Vertex shader input structure
    "struct VS_INPUT\n"
    "{\n"
        "float3 Position : POSITION;\n"
        "float3 Texture0 : TEXCOORD0;\n"
    "};\n"

    // Vertex shader output structure
    "struct VS_OUTPUT\n"
    "{\n"
        "float4 Position : POSITION;\n"
        "float3 Texture0 : TEXCOORD0;\n"
    "};\n"

    // Vertex shader
    "VS_OUTPUT RenderSkyBoxVS(VS_INPUT IN)\n"
    "{\n"
        "VS_OUTPUT Out;\n"

        // Multiply with the WorldViewProjection matrix
        "Out.Position = mul(float4(IN.Position,1.0f),WorldViewProjection);\n"

        // Set z to w to ensure z becomes 1.0 after the division through w occurs
        "Out.Position.z = Out.Position.w;\n"
    
        // Simply pass through texture coordinates
        "Out.Texture0 = IN.Texture0;\n"

        "return Out;\n"
    "}\n"

    // Pixel shader
    "float4 RenderSkyBoxPS(float3 Texture0 : TEXCOORD0) : COLOR\n"
    "{\n"
        // Lookup the skybox texture
        "return texCUBE(EnvironmentMapSampler,Texture0) ;\n"
    "}\n"

    // Technique for the skybox shader (ps_2_0)
    "technique RenderSkyBox\n"
    "{\n"
        "pass p0\n"
        "{\n"
          "ZWriteEnable = FALSE;\n"
          "FogEnable = FALSE;\n"
          "CullMode = NONE;\n"

          "PixelShader = compile ps_2_0 RenderSkyBoxPS();\n"
          "VertexShader = compile vs_2_0 RenderSkyBoxVS();\n"
        "}\n"
    "};\n"

  // -------------- same for static background image -----------------
    "texture TEXTURE_2D;\n"
    "sampler TEXTURE_SAMPLER = sampler_state\n"
    "{\n"
        "Texture = (TEXTURE_2D);\n"
    "};\n"

    "struct VS_OUTPUT2\n"
    "{\n"
        "float4 Position : POSITION;\n"
        "float2 TexCoord0 : TEXCOORD0;\n"
    "};\n"

    "VS_OUTPUT2 RenderImageVS(float4 INPosition : POSITION, float2 INTexCoord0 : TEXCOORD0 )\n"
    "{\n"
        "VS_OUTPUT2 Out;\n"

        "Out.Position.xy = INPosition.xy;\n"
        "Out.Position.z = Out.Position.w = 1.0f;\n"
        "Out.TexCoord0 = INTexCoord0;\n"

        "return Out;\n"
    "}\n"

    "float4 RenderImagePS(float2 IN : TEXCOORD0) : COLOR\n"
    "{\n"
        "return tex2D(TEXTURE_SAMPLER,IN);\n"
    "}\n"

    // Technique for the background image shader (ps_2_0)
    "technique RenderImage2D\n"
    "{\n"
        "pass p0\n"
        "{\n"
            "ZWriteEnable = FALSE;\n"
            "FogEnable = FALSE;\n"
            "CullMode = NONE;\n"
    
            "PixelShader = compile ps_2_0 RenderImagePS();\n"
            "VertexShader = compile vs_2_0 RenderImageVS();\n"
        "}\n"
    "};\n"
    );

std::string g_szDefaultShader = std::string(

    // World * View * Projection matrix
    // NOTE: Assume that the material uses a WorldViewProjection matrix
    "float4x4 WorldViewProjection	: WORLDVIEWPROJECTION;\n"
    "float4x4 World					: WORLD;\n"
    "float4x3 WorldInverseTranspose	: WORLDINVERSETRANSPOSE;\n"

    // light colors
    "float3 afLightColor[5];\n"
    // light direction
    "float3 afLightDir[5];\n"

    // position of the camera in worldspace\n"
    "float3 vCameraPos : CAMERAPOSITION;\n"

    // Bone matrices
//	"#ifdef AV_SKINNING \n"
    "float4x3 gBoneMatrix[60]; \n"
//	"#endif // AV_SKINNING \n"

    // Vertex shader input structure
    "struct VS_INPUT\n"
    "{\n"
        "float3 Position : POSITION;\n"
        "float3 Normal : NORMAL;\n"
//		"#ifdef AV_SKINNING \n"
            "float4 BlendIndices : BLENDINDICES;\n"
            "float4 BlendWeights : BLENDWEIGHT;\n"
//		"#endif // AV_SKINNING \n"
    "};\n"

    // Vertex shader output structure for pixel shader usage
    "struct VS_OUTPUT\n"
    "{\n"
        "float4 Position : POSITION;\n"
        "float3 ViewDir : TEXCOORD0;\n"
        "float3 Normal : TEXCOORD1;\n"
    "};\n"

    // Vertex shader output structure for fixed function
    "struct VS_OUTPUT_FF\n"
    "{\n"
        "float4 Position : POSITION;\n"
        "float4 Color : COLOR;\n"
    "};\n"

    // Vertex shader for pixel shader usage
    "VS_OUTPUT DefaultVShader(VS_INPUT IN)\n"
    "{\n"
        "VS_OUTPUT Out;\n"

//		"#ifdef AV_SKINNING \n"
        "float4 weights = IN.BlendWeights; \n"
        "weights.w = 1.0f - dot( weights.xyz, float3( 1, 1, 1)); \n"
        "float4 localPos = float4( IN.Position, 1.0f); \n"
        "float3 objPos = mul( localPos, gBoneMatrix[IN.BlendIndices.x]) * weights.x; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.y]) * weights.y; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.z]) * weights.z; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.w]) * weights.w; \n"
//		"#else \n"
//		"float3 objPos = IN.Position; \n"
//		"#endif // AV_SKINNING \n"

        // Multiply with the WorldViewProjection matrix
        "Out.Position = mul( float4( objPos, 1.0f), WorldViewProjection);\n"
        "float3 WorldPos = mul( float4( objPos, 1.0f), World);\n"
        "Out.ViewDir = vCameraPos - WorldPos;\n"
        "Out.Normal = mul(IN.Normal,WorldInverseTranspose);\n"

        "return Out;\n"
    "}\n"

    // Vertex shader for fixed function pipeline
    "VS_OUTPUT_FF DefaultVShader_FF(VS_INPUT IN)\n"
    "{\n"
        "VS_OUTPUT_FF Out;\n"

//		"#ifdef AV_SKINNING \n"
        "float4 weights = IN.BlendWeights; \n"
        "weights.w = 1.0f - dot( weights.xyz, float3( 1, 1, 1)); \n"
        "float4 localPos = float4( IN.Position, 1.0f); \n"
        "float3 objPos = mul( localPos, gBoneMatrix[IN.BlendIndices.x]) * weights.x; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.y]) * weights.y; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.z]) * weights.z; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.w]) * weights.w; \n"
//		"#else \n"
//		"float3 objPos = IN.Position; \n"
//		"#endif // AV_SKINNING \n"

        // Multiply with the WorldViewProjection matrix
        "Out.Position = mul( float4( objPos, 1.0f), WorldViewProjection);\n"

        "float3 worldNormal = normalize( mul( IN.Normal, (float3x3) WorldInverseTranspose)); \n"

        // per-vertex lighting. We simply assume light colors of unused lights to be black
        "Out.Color = float4( 0.2f, 0.2f, 0.2f, 1.0f); \n"
        "for( int a = 0; a < 2; a++)\n"
        "  Out.Color.rgb += saturate( dot( afLightDir[a], worldNormal)) * afLightColor[a].rgb; \n"
            "return Out;\n"
    "}\n"

    // Pixel shader for one light
    "float4 DefaultPShaderSpecular_D1(VS_OUTPUT IN) : COLOR\n"
    "{\n"
        "float4 OUT = float4(0.0f,0.0f,0.0f,1.0f);\n"

        "float3 Normal = normalize(IN.Normal);\n"
        "float3 ViewDir = normalize(IN.ViewDir);\n"

        "{\n"
            "float L1 = dot(Normal,afLightDir[0]) * 0.5f + 0.5f;\n"
            "float3 Reflect = reflect (Normal,afLightDir[0]);\n"
            "float fHalfLambert = L1*L1;\n"
            "OUT.rgb += afLightColor[0] * (fHalfLambert +\n"
                "saturate(fHalfLambert * 4.0f) * pow(dot(Reflect,ViewDir),9));\n"
        "}\n"
        "return OUT;\n"
    "}\n"

    // Pixel shader for two lights
    "float4 DefaultPShaderSpecular_D2(VS_OUTPUT IN) : COLOR\n"
    "{\n"
        "float4 OUT = float4(0.0f,0.0f,0.0f,1.0f);\n"

        "float3 Normal = normalize(IN.Normal);\n"
        "float3 ViewDir = normalize(IN.ViewDir);\n"

        "{\n"
            "float L1 = dot(Normal,afLightDir[0]) * 0.5f + 0.5f;\n"
            "float3 Reflect = reflect (ViewDir,Normal);\n"
            "float fHalfLambert = L1*L1;\n"
            "OUT.rgb += afLightColor[0] * (fHalfLambert +\n"
            "saturate(fHalfLambert * 4.0f) * pow(dot(Reflect,afLightDir[0]),9));\n"
        "}\n"
        "{\n"
            "float L1 = dot(Normal,afLightDir[1]) * 0.5f + 0.5f;\n"
            "float3 Reflect = reflect (ViewDir,Normal);\n"
            "float fHalfLambert = L1*L1;\n"
            "OUT.rgb += afLightColor[1] * (fHalfLambert +\n"
            "saturate(fHalfLambert * 4.0f) * pow(dot(Reflect,afLightDir[1]),9));\n"
        "}\n"
        "return OUT;\n"
    "}\n"
    // ----------------------------------------------------------------------------
    "float4 DefaultPShaderSpecular_PS20_D1(VS_OUTPUT IN) : COLOR\n"
    "{\n"
        "float4 OUT = float4(0.0f,0.0f,0.0f,1.0f);\n"

        "float3 Normal = normalize(IN.Normal);\n"
        "float3 ViewDir = normalize(IN.ViewDir);\n"

        "{\n"
            "float L1 = dot(Normal,afLightDir[0]);\n"
            "float3 Reflect = reflect (Normal,afLightDir[0]);\n"
            "OUT.rgb += afLightColor[0] * ((L1) +\n"
            "pow(dot(Reflect,ViewDir),9));\n"
        "}\n"

        "return OUT;\n"
    "}\n"
    // ----------------------------------------------------------------------------
    "float4 DefaultPShaderSpecular_PS20_D2(VS_OUTPUT IN) : COLOR\n"
    "{\n"
        "float4 OUT = float4(0.0f,0.0f,0.0f,1.0f);\n"

        "float3 Normal = normalize(IN.Normal);\n"
        "float3 ViewDir = normalize(IN.ViewDir);\n"

        "{\n"
            "float L1 = dot(Normal,afLightDir[0]);\n"
            "float3 Reflect = reflect (Normal,afLightDir[0]);\n"
            "OUT.rgb += afLightColor[0] * ((L1) +\n"
            "pow(dot(Reflect,ViewDir),9));\n"
        "}\n"
        "{\n"
            "float L1 = dot(Normal,afLightDir[1]);\n"
            "float3 Reflect = reflect (Normal,afLightDir[1]);\n"
            "OUT.rgb += afLightColor[1] * ((L1) +\n"
            "pow(dot(Reflect,ViewDir),9));\n"
        "}\n"
        "return OUT;\n"
    "}\n"


    // Technique for the default effect
    "technique DefaultFXSpecular_D1\n"
    "{\n"
        "pass p0\n"
        "{\n"
            "CullMode=none;\n"
            "PixelShader = compile ps_3_0 DefaultPShaderSpecular_D1();\n"
            "VertexShader = compile vs_3_0 DefaultVShader();\n"
        "}\n"
    "};\n"
    "technique DefaultFXSpecular_D2\n"
    "{\n"
        "pass p0\n"
        "{\n"
            "CullMode=none;\n"
            "PixelShader = compile ps_3_0 DefaultPShaderSpecular_D2();\n"
            "VertexShader = compile vs_3_0 DefaultVShader();\n"
        "}\n"
    "};\n"

    // Technique for the default effect (ps_2_0)
    "technique DefaultFXSpecular_PS20_D1\n"
    "{\n"
        "pass p0\n"
    "{\n"
          "CullMode=none;\n"
          "PixelShader = compile ps_2_0 DefaultPShaderSpecular_PS20_D1();\n"
          "VertexShader = compile vs_2_0 DefaultVShader();\n"
        "}\n"
    "};\n"
    "technique DefaultFXSpecular_PS20_D2\n"
    "{\n"
        "pass p0\n"
        "{\n"
          "CullMode=none;\n"
          "PixelShader = compile ps_2_0 DefaultPShaderSpecular_PS20_D2();\n"
          "VertexShader = compile vs_2_0 DefaultVShader();\n"
        "}\n"
    "};\n"

    // Technique for the default effect using the fixed function pixel pipeline
    "technique DefaultFXSpecular_FF\n"
    "{\n"
        "pass p0\n"
        "{\n"
            "CullMode=none;\n"
            "VertexShader = compile vs_2_0 DefaultVShader_FF();\n"
            "ColorOp[0] = SelectArg1;\n"
            "ColorArg0[0] = Diffuse;\n"
            "AlphaOp[0] = SelectArg1;\n"
            "AlphaArg0[0] = Diffuse;\n"
        "}\n"
    "};\n"
  );


std::string g_szMaterialShader = std::string(

    // World * View * Projection matrix
  // NOTE: Assume that the material uses a WorldViewProjection matrix
    "float4x4 WorldViewProjection	: WORLDVIEWPROJECTION;\n"
    "float4x4 World					: WORLD;\n"
    "float4x3 WorldInverseTranspose	: WORLDINVERSETRANSPOSE;\n"

    "#ifndef AV_DISABLESSS\n"
    "float4x3 ViewProj;\n"
    "float4x3 InvViewProj;\n"
    "#endif\n"

    "float4 DIFFUSE_COLOR;\n"
    "float4 SPECULAR_COLOR;\n"
    "float4 AMBIENT_COLOR;\n"
    "float4 EMISSIVE_COLOR;\n"

    "#ifdef AV_SPECULAR_COMPONENT\n"
    "float SPECULARITY;\n"
    "float SPECULAR_STRENGTH;\n"
    "#endif\n"
    "#ifdef AV_OPACITY\n"
    "float TRANSPARENCY;\n"
    "#endif\n"

    // light colors (diffuse and specular)
    "float4 afLightColor[5];\n"
    "float4 afLightColorAmbient[5];\n"

    // light direction
    "float3 afLightDir[5];\n"

    // position of the camera in worldspace
    "float3 vCameraPos : CAMERAPOSITION;\n"

    // Bone matrices
    "#ifdef AV_SKINNING \n"
    "float4x3 gBoneMatrix[60]; \n"
    "#endif // AV_SKINNING \n"

    "#ifdef AV_DIFFUSE_TEXTURE\n"
        "texture DIFFUSE_TEXTURE;\n"
        "sampler DIFFUSE_SAMPLER\n"
        "{\n"
          "Texture = <DIFFUSE_TEXTURE>;\n"
          "#ifdef AV_WRAPU\n"
          "AddressU = WRAP;\n"
          "#endif\n"
          "#ifdef AV_MIRRORU\n"
          "AddressU = MIRROR;\n"
          "#endif\n"
          "#ifdef AV_CLAMPU\n"
          "AddressU = CLAMP;\n"
          "#endif\n"
          "#ifdef AV_WRAPV\n"
          "AddressV = WRAP;\n"
          "#endif\n"
          "#ifdef AV_MIRRORV\n"
          "AddressV = MIRROR;\n"
          "#endif\n"
          "#ifdef AV_CLAMPV\n"
          "AddressV = CLAMP;\n"
          "#endif\n"
        "};\n"
    "#endif // AV_DIFFUSE_TEXTUR\n"

    "#ifdef AV_DIFFUSE_TEXTURE2\n"
        "texture DIFFUSE_TEXTURE2;\n"
        "sampler DIFFUSE_SAMPLER2\n"
        "{\n"
          "Texture = <DIFFUSE_TEXTURE2>;\n"
        "};\n"
    "#endif // AV_DIFFUSE_TEXTUR2\n"

    "#ifdef AV_SPECULAR_TEXTURE\n"
        "texture SPECULAR_TEXTURE;\n"
        "sampler SPECULAR_SAMPLER\n"
        "{\n"
          "Texture = <SPECULAR_TEXTURE>;\n"
        "};\n"
    "#endif // AV_SPECULAR_TEXTUR\n"

    "#ifdef AV_AMBIENT_TEXTURE\n"
        "texture AMBIENT_TEXTURE;\n"
        "sampler AMBIENT_SAMPLER\n"
        "{\n"
          "Texture = <AMBIENT_TEXTURE>;\n"
        "};\n"
    "#endif // AV_AMBIENT_TEXTUR\n"

    "#ifdef AV_LIGHTMAP_TEXTURE\n"
        "texture LIGHTMAP_TEXTURE;\n"
        "sampler LIGHTMAP_SAMPLER\n"
        "{\n"
          "Texture = <LIGHTMAP_TEXTURE>;\n"
        "};\n"
    "#endif // AV_LIGHTMAP_TEXTURE\n"

    "#ifdef AV_OPACITY_TEXTURE\n"
        "texture OPACITY_TEXTURE;\n"
        "sampler OPACITY_SAMPLER\n"
        "{\n"
          "Texture = <OPACITY_TEXTURE>;\n"
        "};\n"
    "#endif // AV_OPACITY_TEXTURE\n"

    "#ifdef AV_EMISSIVE_TEXTURE\n"
        "texture EMISSIVE_TEXTURE;\n"
        "sampler EMISSIVE_SAMPLER\n"
        "{\n"
          "Texture = <EMISSIVE_TEXTURE>;\n"
        "};\n"
    "#endif // AV_EMISSIVE_TEXTUR\n"

    "#ifdef AV_NORMAL_TEXTURE\n"
        "texture NORMAL_TEXTURE;\n"
        "sampler NORMAL_SAMPLER\n"
        "{\n"
          "Texture = <NORMAL_TEXTURE>;\n"
        "};\n"
    "#endif // AV_NORMAL_TEXTURE\n"

    "#ifdef AV_SKYBOX_LOOKUP\n"
        "textureCUBE lw_tex_envmap;\n"
        "samplerCUBE EnvironmentMapSampler = sampler_state\n"
        "{\n"
          "Texture = (lw_tex_envmap);\n"
          "AddressU = CLAMP;\n"
          "AddressV = CLAMP;\n"
          "AddressW = CLAMP;\n"

          "MAGFILTER = linear;\n"
          "MINFILTER = linear;\n"
        "};\n"
    "#endif // AV_SKYBOX_LOOKUP\n"

    // Vertex shader input structure
    "struct VS_INPUT\n"
    "{\n"
        "float3 Position : POSITION;\n"
        "float3 Normal : NORMAL;\n"
        "float4 Color : COLOR0;\n"
        "float3 Tangent   : TANGENT;\n"
        "float3 Bitangent : BINORMAL;\n"
        "float2 TexCoord0 : TEXCOORD0;\n"
        "#ifdef AV_TWO_UV \n"
        "float2 TexCoord1 : TEXCOORD1;\n"
        "#endif \n"
          "#ifdef AV_SKINNING \n"
            "float4 BlendIndices : BLENDINDICES;\n"
            "float4 BlendWeights : BLENDWEIGHT;\n"
         "#endif // AV_SKINNING \n"
    "};\n"

    // Vertex shader output structure for pixel shader usage
    "struct VS_OUTPUT\n"
    "{\n"
        "float4 Position : POSITION;\n"
        "float3 ViewDir : TEXCOORD0;\n"

        "float4 Color : COLOR0;\n"

        "#ifndef AV_NORMAL_TEXTURE\n"
        "float3 Normal  : TEXCOORD1;\n"
        "#endif\n"

        "float2 TexCoord0 : TEXCOORD2;\n"
        "#ifdef AV_TWO_UV \n"
        "float2 TexCoord1 : TEXCOORD3;\n"
        "#endif \n"

        "#ifdef AV_NORMAL_TEXTURE\n"
        "float3 Light0 : TEXCOORD3;\n"
        "float3 Light1 : TEXCOORD4;\n"
        "#endif\n"
    "};\n"

    // Vertex shader output structure for fixed function pixel pipeline
    "struct VS_OUTPUT_FF\n"
    "{\n"
        "float4 Position : POSITION;\n"
        "float4 DiffuseColor : COLOR0;\n"
        "float4 SpecularColor : COLOR1;\n"
        "float2 TexCoord0 : TEXCOORD0;\n"
    "};\n"


    // Selective SuperSampling in screenspace for reflection lookups
    "#define GetSSSCubeMap(_refl) (texCUBElod(EnvironmentMapSampler,float4(_refl,0.0f)).rgb) \n"


    // Vertex shader for pixel shader usage and one light
    "VS_OUTPUT MaterialVShader_D1(VS_INPUT IN)\n"
    "{\n"
        "VS_OUTPUT Out = (VS_OUTPUT)0;\n"

        "#ifdef AV_SKINNING \n"
        "float4 weights = IN.BlendWeights; \n"
        "weights.w = 1.0f - dot( weights.xyz, float3( 1, 1, 1)); \n"
        "float4 localPos = float4( IN.Position, 1.0f); \n"
        "float3 objPos = mul( localPos, gBoneMatrix[IN.BlendIndices.x]) * weights.x; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.y]) * weights.y; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.z]) * weights.z; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.w]) * weights.w; \n"
        "#else \n"
        "float3 objPos = IN.Position; \n"
        "#endif // AV_SKINNING \n"

        // Multiply with the WorldViewProjection matrix
        "Out.Position = mul( float4( objPos, 1.0f), WorldViewProjection);\n"
        "float3 WorldPos = mul( float4( objPos, 1.0f), World);\n"
        "Out.TexCoord0 = IN.TexCoord0;\n"
        "#ifdef AV_TWO_UV \n"
        "Out.TexCoord1 = IN.TexCoord1;\n"
        "#endif\n"
        "Out.Color = IN.Color;\n"

        "#ifndef AV_NORMAL_TEXTURE\n"
        "Out.ViewDir = vCameraPos - WorldPos;\n"
        "Out.Normal = mul(IN.Normal,WorldInverseTranspose);\n"
        "#endif\n"
        
        "#ifdef AV_NORMAL_TEXTURE\n"
        "float3x3 TBNMatrix = float3x3(IN.Tangent, IN.Bitangent, IN.Normal);\n"
        "float3x3 WTTS      = mul(TBNMatrix, (float3x3)WorldInverseTranspose);\n"
        "Out.Light0         = normalize(mul(WTTS, afLightDir[0] ));\n"
        "Out.ViewDir = normalize(mul(WTTS, (vCameraPos - WorldPos)));\n"
        "#endif\n"
        "return Out;\n"
    "}\n"

    // Vertex shader for pixel shader usage and two lights
    "VS_OUTPUT MaterialVShader_D2(VS_INPUT IN)\n"
    "{\n"
        "VS_OUTPUT Out = (VS_OUTPUT)0;\n"

        "#ifdef AV_SKINNING \n"
        "float4 weights = IN.BlendWeights; \n"
        "weights.w = 1.0f - dot( weights.xyz, float3( 1, 1, 1)); \n"
        "float4 localPos = float4( IN.Position, 1.0f); \n"
        "float3 objPos = mul( localPos, gBoneMatrix[IN.BlendIndices.x]) * weights.x; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.y]) * weights.y; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.z]) * weights.z; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.w]) * weights.w; \n"
        "#else \n"
        "float3 objPos = IN.Position; \n"
        "#endif // AV_SKINNING \n"

        // Multiply with the WorldViewProjection matrix
        "Out.Position = mul( float4( objPos, 1.0f), WorldViewProjection);\n"
        "float3 WorldPos = mul( float4( objPos, 1.0f), World);\n"
        "Out.TexCoord0 = IN.TexCoord0;\n"
        "#ifdef AV_TWO_UV \n"
        "Out.TexCoord1 = IN.TexCoord1;\n"
        "#endif\n"
        "Out.Color = IN.Color;\n"

        "#ifndef AV_NORMAL_TEXTURE\n"
        "Out.ViewDir = vCameraPos - WorldPos;\n"
        "Out.Normal = mul(IN.Normal,WorldInverseTranspose);\n"
        "#endif\n"

        "#ifdef AV_NORMAL_TEXTURE\n"
        "float3x3 TBNMatrix = float3x3(IN.Tangent, IN.Bitangent, IN.Normal);\n"
        "float3x3 WTTS      = mul(TBNMatrix, (float3x3)WorldInverseTranspose);\n"
        "Out.Light0         = normalize(mul(WTTS, afLightDir[0] ));\n"
        "Out.Light1         = normalize(mul(WTTS, afLightDir[1] ));\n"
        "Out.ViewDir = normalize(mul(WTTS, (vCameraPos - WorldPos)));\n"
        "#endif\n"
        "return Out;\n"
    "}\n"

    // Vertex shader for zero to five lights using the fixed function pixel pipeline
    "VS_OUTPUT_FF MaterialVShader_FF(VS_INPUT IN)\n"
    "{\n"
        "VS_OUTPUT_FF Out = (VS_OUTPUT_FF)0;\n"

        "#ifdef AV_SKINNING \n"
        "float4 weights = IN.BlendWeights; \n"
        "weights.w = 1.0f - dot( weights.xyz, float3( 1, 1, 1)); \n"
        "float4 localPos = float4( IN.Position, 1.0f); \n"
        "float3 objPos = mul( localPos, gBoneMatrix[IN.BlendIndices.x]) * weights.x; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.y]) * weights.y; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.z]) * weights.z; \n"
        "objPos += mul( localPos, gBoneMatrix[IN.BlendIndices.w]) * weights.w; \n"
        "#else \n"
        "float3 objPos = IN.Position; \n"
        "#endif // AV_SKINNING \n"

        // Multiply with the WorldViewProjection matrix
        "Out.Position = mul( float4( objPos, 1.0f), WorldViewProjection);\n"
        "float3 worldPos = mul( float4( objPos, 1.0f), World);\n"
        "float3 worldNormal = normalize( mul( IN.Normal, (float3x3) WorldInverseTranspose)); \n"
        "Out.TexCoord0 = IN.TexCoord0;\n"

        // calculate per-vertex diffuse lighting including ambient part
        "float4 diffuseColor = float4( 0.0f, 0.0f, 0.0f, 1.0f); \n"
        "for( int a = 0; a < 2; a++) \n"
        "  diffuseColor.rgb += saturate( dot( afLightDir[a], worldNormal)) * afLightColor[a].rgb; \n"
        // factor in material properties and a bit of ambient lighting
        "Out.DiffuseColor = diffuseColor * DIFFUSE_COLOR + float4( 0.2f, 0.2f, 0.2f, 1.0f) * AMBIENT_COLOR; ; \n"

        // and specular including emissive part
        "float4 specularColor = float4( 0.0f, 0.0f, 0.0f, 1.0f); \n"
        "#ifdef AV_SPECULAR_COMPONENT\n"
        "float3 viewDir = normalize( worldPos - vCameraPos); \n"
        "for( int a = 0; a < 2; a++) \n"
        "{ \n"
        "  float3 reflDir = reflect( afLightDir[a], worldNormal); \n"
        "  float specIntensity = pow( saturate( dot( reflDir, viewDir)), SPECULARITY) * SPECULAR_STRENGTH; \n"
        "  specularColor.rgb += afLightColor[a] * specIntensity; \n"
        "} \n"
        "#endif // AV_SPECULAR_COMPONENT\n"
        // factor in material properties and the emissive part
        "Out.SpecularColor = specularColor * SPECULAR_COLOR + EMISSIVE_COLOR; \n"

        "return Out;\n"
    "}\n"


    // Pixel shader - one light
    "float4 MaterialPShaderSpecular_D1(VS_OUTPUT IN) : COLOR\n"
    "{\n"
        "float4 OUT = float4(0.0f,0.0f,0.0f,1.0f);\n"

        "#ifdef AV_NORMAL_TEXTURE\n"
        "float3 IN_Light0 = normalize(IN.Light0);\n"
        "float3 Normal  =  normalize(2.0f * tex2D(NORMAL_SAMPLER, IN.TexCoord0).rgb - 1.0f);\n"
        "#else\n"
        "float3 Normal = normalize(IN.Normal);\n"
        "#endif \n"
        "float3 ViewDir = normalize(IN.ViewDir);\n"
        "#ifdef AV_SPECULAR_COMPONENT\n"
            "float3 Reflect = normalize(reflect (-ViewDir,Normal));\n"
        "#endif // !AV_SPECULAR_COMPONENT\n"

        "{\n"
        "#ifdef AV_NORMAL_TEXTURE\n"
            "float L1 =  dot(Normal,IN_Light0) * 0.5f + 0.5f;\n"
            "#define AV_LIGHT_0 IN_Light0\n"
            // would need to convert the reflection vector into world space ....
            // simply let it ...
        "#else\n"
            "float L1 = dot(Normal,afLightDir[0]) * 0.5f + 0.5f;\n"
            "#define AV_LIGHT_0 afLightDir[0]\n"
        "#endif\n"
        "#ifdef AV_DIFFUSE_TEXTURE2\n"
            "float fHalfLambert = 1.f;\n"
        "#else\n"
            "float fHalfLambert = L1*L1;\n"
        "#endif \n"
        "#ifdef AV_DIFFUSE_TEXTURE\n"
            "OUT.rgb += afLightColor[0].rgb * DIFFUSE_COLOR.rgb * tex2D(DIFFUSE_SAMPLER,IN.TexCoord0).rgb * fHalfLambert * IN.Color.rgb +\n"
        "#else\n"
            "OUT.rgb += afLightColor[0].rgb * DIFFUSE_COLOR.rgb * fHalfLambert * IN.Color.rgb +\n"
        "#endif // !AV_DIFFUSE_TEXTURE\n"

        
        "#ifdef AV_SPECULAR_COMPONENT\n"
            "#ifndef AV_SKYBOX_LOOKUP\n"
                "#ifdef AV_SPECULAR_TEXTURE\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_0),SPECULARITY)) + \n"
                "#else\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_0),SPECULARITY)) + \n"
                "#endif // !AV_SPECULAR_TEXTURE\n"
            "#else\n"
                "#ifdef AV_SPECULAR_TEXTURE\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * GetSSSCubeMap(Reflect) * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_0),SPECULARITY)) + \n"
                "#else\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * GetSSSCubeMap(Reflect) * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_0),SPECULARITY)) + \n"
                "#endif // !AV_SPECULAR_TEXTURE\n"
            "#endif // !AV_SKYBOX_LOOKUP\n"
        "#endif // !AV_SPECULAR_COMPONENT\n"

        "#ifdef AV_AMBIENT_TEXTURE\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[0].rgb * tex2D(AMBIENT_SAMPLER,IN.TexCoord0).rgb +\n"
        "#else\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[0].rgb + \n"
        "#endif // !AV_AMBIENT_TEXTURE\n"
            "#ifdef AV_EMISSIVE_TEXTURE\n"
            "EMISSIVE_COLOR.rgb * tex2D(EMISSIVE_SAMPLER,IN.TexCoord0).rgb;\n"
        "#else \n"
            "EMISSIVE_COLOR.rgb;\n"
        "#endif // !AV_EMISSIVE_TEXTURE\n"
        "}\n"
        "#ifdef AV_OPACITY\n"
        "OUT.a = TRANSPARENCY;\n"
        "#endif\n"
        "#ifdef AV_LIGHTMAP_TEXTURE\n"
        "OUT.rgb *= tex2D(LIGHTMAP_SAMPLER,AV_LIGHTMAP_TEXTURE_UV_COORD).rgb*LM_STRENGTH;\n"
        "#endif\n"
        "#ifdef AV_OPACITY_TEXTURE\n"
        "OUT.a *= tex2D(OPACITY_SAMPLER,IN.TexCoord0). AV_OPACITY_TEXTURE_REGISTER_MASK;\n"
        "#endif\n"
        "return OUT;\n"

        "#undef AV_LIGHT_0\n"
    "}\n"

    // Pixel shader - two lights
    "float4 MaterialPShaderSpecular_D2(VS_OUTPUT IN) : COLOR\n"
    "{\n"
        "float4 OUT = float4(0.0f,0.0f,0.0f,1.0f);\n"

        "#ifdef AV_NORMAL_TEXTURE\n"
        "float3 IN_Light0 = normalize(IN.Light0);\n"
        "float3 IN_Light1 = normalize(IN.Light1);\n"
        "float3 Normal  =  normalize(2.0f * tex2D(NORMAL_SAMPLER, IN.TexCoord0).rgb - 1.0f);\n"
        "#else\n"
        "float3 Normal = normalize(IN.Normal);\n"
        "#endif \n"
        "float3 ViewDir = normalize(IN.ViewDir);\n"
        "#ifdef AV_SPECULAR_COMPONENT\n"
            "float3 Reflect = -normalize(reflect (ViewDir,Normal));\n"
        "#endif // !AV_SPECULAR_COMPONENT\n"

        "{\n"
        
        "#ifdef AV_NORMAL_TEXTURE\n"
            "float L1 = dot(Normal,IN_Light0) * 0.5f + 0.5f;\n"
            "#define AV_LIGHT_0 IN_Light0\n"
        "#else\n"
            "float L1 = dot(Normal,afLightDir[0]) * 0.5f + 0.5f;\n"
            "#define AV_LIGHT_0 afLightDir[0]\n"
        "#endif\n"
            "float fHalfLambert = L1*L1;\n"
            
        "#ifdef AV_DIFFUSE_TEXTURE\n"
            "OUT.rgb += afLightColor[0].rgb * DIFFUSE_COLOR.rgb * tex2D(DIFFUSE_SAMPLER,IN.TexCoord0).rgb * fHalfLambert  * IN.Color.rgb +\n"
        "#else\n"
            "OUT.rgb += afLightColor[0].rgb * DIFFUSE_COLOR.rgb * fHalfLambert  * IN.Color.rgb +\n"
        "#endif // !AV_DIFFUSE_TEXTURE\n"

        "#ifdef AV_SPECULAR_COMPONENT\n"
            "#ifndef AV_SKYBOX_LOOKUP\n"
                "#ifdef AV_SPECULAR_TEXTURE\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_0),SPECULARITY)) + \n"
                "#else\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_0),SPECULARITY)) + \n"
                "#endif // !AV_SPECULAR_TEXTURE\n"
            "#else\n"
                "#ifdef AV_SPECULAR_TEXTURE\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * GetSSSCubeMap(Reflect) * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_0),SPECULARITY)) + \n"
                "#else\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * GetSSSCubeMap(Reflect) * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_0),SPECULARITY)) + \n"
                "#endif // !AV_SPECULAR_TEXTURE\n"
            "#endif // !AV_SKYBOX_LOOKUP\n"
        "#endif // !AV_SPECULAR_COMPONENT\n"
        "#ifdef AV_AMBIENT_TEXTURE\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[0].rgb * tex2D(AMBIENT_SAMPLER,IN.TexCoord0).rgb + \n"
        "#else\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[0].rgb + \n"
        "#endif // !AV_AMBIENT_TEXTURE\n"
        "#ifdef AV_EMISSIVE_TEXTURE\n"
            "EMISSIVE_COLOR.rgb * tex2D(EMISSIVE_SAMPLER,IN.TexCoord0).rgb;\n"
        "#else \n"
            "EMISSIVE_COLOR.rgb;\n"
        "#endif // !AV_EMISSIVE_TEXTURE\n"
        "}\n"
        "{\n"
        "#ifdef AV_NORMAL_TEXTURE\n"
            "float L1 = dot(Normal,IN_Light1) * 0.5f + 0.5f;\n"
            "#define AV_LIGHT_1 IN_Light1\n"
        "#else\n"
            "float L1 = dot(Normal,afLightDir[1]) * 0.5f + 0.5f;\n"
            "#define AV_LIGHT_1 afLightDir[1]\n"
        "#endif\n"
            "float fHalfLambert = L1*L1;\n"
        "#ifdef AV_DIFFUSE_TEXTURE\n"
            "OUT.rgb += afLightColor[1].rgb * DIFFUSE_COLOR.rgb * tex2D(DIFFUSE_SAMPLER,IN.TexCoord0).rgb * fHalfLambert  * IN.Color.rgb +\n"
        "#else\n"
            "OUT.rgb += afLightColor[1].rgb * DIFFUSE_COLOR.rgb * fHalfLambert   * IN.Color.rgb +\n"
        "#endif // !AV_DIFFUSE_TEXTURE\n"

        "#ifdef AV_SPECULAR_COMPONENT\n"
            "#ifndef AV_SKYBOX_LOOKUP\n"
                "#ifdef AV_SPECULAR_TEXTURE\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[1].rgb * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_1),SPECULARITY)) + \n"
                "#else\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[1].rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_1),SPECULARITY)) + \n"
                "#endif // !AV_SPECULAR_TEXTURE\n"
            "#else\n"
                "#ifdef AV_SPECULAR_TEXTURE\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[1].rgb * GetSSSCubeMap(Reflect) * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_1),SPECULARITY)) + \n"
                "#else\n"
                    "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[1].rgb * GetSSSCubeMap(Reflect) * (saturate(fHalfLambert * 2.0f) * pow(dot(Reflect,AV_LIGHT_1),SPECULARITY)) + \n"
                "#endif // !AV_SPECULAR_TEXTURE\n"
            "#endif // !AV_SKYBOX_LOOKUP\n"
        "#endif // !AV_SPECULAR_COMPONENT\n"
        "#ifdef AV_AMBIENT_TEXTURE\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[1].rgb * tex2D(AMBIENT_SAMPLER,IN.TexCoord0).rgb + \n"
        "#else\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[1].rgb + \n"
        "#endif // !AV_AMBIENT_TEXTURE\n"
        "#ifdef AV_EMISSIVE_TEXTURE\n"
            "EMISSIVE_COLOR.rgb * tex2D(EMISSIVE_SAMPLER,IN.TexCoord0).rgb;\n"
        "#else \n"
            "EMISSIVE_COLOR.rgb;\n"
        "#endif // !AV_EMISSIVE_TEXTURE\n"
        "}\n"
        "#ifdef AV_OPACITY\n"
        "OUT.a = TRANSPARENCY;\n"
        "#endif\n"
        "#ifdef AV_LIGHTMAP_TEXTURE\n"
        "OUT.rgb *= tex2D(LIGHTMAP_SAMPLER,AV_LIGHTMAP_TEXTURE_UV_COORD).rgb*LM_STRENGTH;\n"
        "#endif\n"
        "#ifdef AV_OPACITY_TEXTURE\n"
        "OUT.a *= tex2D(OPACITY_SAMPLER,IN.TexCoord0). AV_OPACITY_TEXTURE_REGISTER_MASK;\n"
        "#endif\n"
        "return OUT;\n"

        "#undef AV_LIGHT_0\n"
        "#undef AV_LIGHT_1\n"
    "}\n"

    // Same pixel shader again, one light
    "float4 MaterialPShaderSpecular_PS20_D1(VS_OUTPUT IN) : COLOR\n"
    "{\n"
        "float4 OUT = float4(0.0f,0.0f,0.0f,1.0f);\n"

        "#ifdef AV_NORMAL_TEXTURE\n"
        "float3 IN_Light0 = normalize(IN.Light0);\n"
        "float3 Normal  =  normalize(2.0f * tex2D(NORMAL_SAMPLER, IN.TexCoord0).rgb - 1.0f);\n"
        "#else\n"
        "float3 Normal = normalize(IN.Normal);\n"
        "#endif \n"
        "float3 ViewDir = normalize(IN.ViewDir);\n"

        "{\n"
        "#ifdef AV_NORMAL_TEXTURE\n"
        "float L1 = dot(Normal,IN_Light0) * 0.5f + 0.5f;\n"
        "float3 Reflect = reflect (Normal,IN_Light0);\n"
        "#else\n"
        "float L1 = dot(Normal,afLightDir[0]) * 0.5f + 0.5f;\n"
        "float3 Reflect = reflect (Normal,afLightDir[0]);\n"
        "#endif\n"
        "#ifdef AV_DIFFUSE_TEXTURE\n"
            "OUT.rgb += afLightColor[0].rgb * DIFFUSE_COLOR.rgb * tex2D(DIFFUSE_SAMPLER,IN.TexCoord0).rgb * L1 +\n"
        "#else\n"
            "OUT.rgb += afLightColor[0].rgb * DIFFUSE_COLOR.rgb * L1 +\n"
        "#endif // !AV_DIFFUSE_TEXTURE\n"

        "#ifdef AV_SPECULAR_COMPONENT\n"
        "#ifdef AV_SPECULAR_TEXTURE\n"
            "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(L1 * 4.0f) * pow(dot(Reflect,ViewDir),SPECULARITY)) + \n"
        "#else\n"
            "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * (saturate(L1 * 4.0f) * pow(dot(Reflect,ViewDir),SPECULARITY)) + \n"
        "#endif // !AV_SPECULAR_TEXTURE\n"
        "#endif // !AV_SPECULAR_COMPONENT\n"
        "#ifdef AV_AMBIENT_TEXTURE\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[0].rgb * tex2D(AMBIENT_SAMPLER,IN.TexCoord0).rgb +\n"
        "#else\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[0].rgb +\n"
        "#endif // !AV_AMBIENT_TEXTURE\n"
        "#ifdef AV_EMISSIVE_TEXTURE\n"
            "EMISSIVE_COLOR.rgb * tex2D(EMISSIVE_SAMPLER,IN.TexCoord0).rgb;\n"
        "#else \n"
            "EMISSIVE_COLOR.rgb;\n"
        "#endif // !AV_EMISSIVE_TEXTURE\n"
        "}\n"

        "#ifdef AV_OPACITY\n"
        "OUT.a = TRANSPARENCY;\n"
        "#endif\n"
        "#ifdef AV_OPACITY_TEXTURE\n"
        "OUT.a *= tex2D(OPACITY_SAMPLER,IN.TexCoord0). AV_OPACITY_TEXTURE_REGISTER_MASK;\n"
        "#endif\n"
        "return OUT;\n"
    "}\n"

    // Same pixel shader again, two lights
    "float4 MaterialPShaderSpecular_PS20_D2(VS_OUTPUT IN) : COLOR\n"
    "{\n"
        "float4 OUT = float4(0.0f,0.0f,0.0f,1.0f);\n"

        "#ifdef AV_NORMAL_TEXTURE\n"
        "float3 IN_Light0 = normalize(IN.Light0);\n"
        "float3 IN_Light1 = normalize(IN.Light1);\n"
        "float3 Normal  =  normalize(2.0f * tex2D(NORMAL_SAMPLER, IN.TexCoord0) - 1.0f);\n"
        "#else\n"
        "float3 Normal = normalize(IN.Normal);\n"
        "#endif \n"
        "float3 ViewDir = normalize(IN.ViewDir);\n"

        "{\n"
        "#ifdef AV_NORMAL_TEXTURE\n"
        "float L1 = dot(Normal,IN_Light0) * 0.5f + 0.5f;\n"
        "float3 Reflect = reflect (Normal,IN_Light0);\n"
        "#else\n"
        "float L1 = dot(Normal,afLightDir[0]) * 0.5f + 0.5f;\n"
        "float3 Reflect = reflect (Normal,afLightDir[0]);\n"
        "#endif\n"
        "#ifdef AV_DIFFUSE_TEXTURE\n"
            "OUT.rgb += afLightColor[0].rgb * DIFFUSE_COLOR.rgb * tex2D(DIFFUSE_SAMPLER,IN.TexCoord0).rgb * L1 +\n"
        "#else\n"
            "OUT.rgb += afLightColor[0].rgb * DIFFUSE_COLOR.rgb * L1 +\n"
        "#endif // !AV_DIFFUSE_TEXTURE\n"

        "#ifdef AV_SPECULAR_COMPONENT\n"
        "#ifdef AV_SPECULAR_TEXTURE\n"
            "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(L1 * 4.0f) * pow(dot(Reflect,ViewDir),SPECULARITY)) + \n"
        "#else\n"
            "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[0].rgb * (saturate(L1 * 4.0f) * pow(dot(Reflect,ViewDir),SPECULARITY)) + \n"
        "#endif // !AV_SPECULAR_TEXTURE\n"
        "#endif // !AV_SPECULAR_COMPONENT\n"
        "#ifdef AV_AMBIENT_TEXTURE\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[0].rgb * tex2D(AMBIENT_SAMPLER,IN.TexCoord0).rgb +\n"
        "#else\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[0].rgb +\n"
        "#endif // !AV_AMBIENT_TEXTURE\n"
        "#ifdef AV_EMISSIVE_TEXTURE\n"
            "EMISSIVE_COLOR.rgb * tex2D(EMISSIVE_SAMPLER,IN.TexCoord0).rgb;\n"
        "#else \n"
            "EMISSIVE_COLOR.rgb;\n"
        "#endif // !AV_EMISSIVE_TEXTURE\n"
        "}\n"
        "{\n"
        "#ifdef AV_NORMAL_TEXTURE\n"
        "float L1 = dot(Normal,IN_Light1) * 0.5f + 0.5f;\n"
        "float3 Reflect = reflect (Normal,IN_Light1);\n"
        "#else\n"
        "float L1 = dot(Normal,afLightDir[1]) * 0.5f + 0.5f;\n"
        "float3 Reflect = reflect (Normal,afLightDir[1]);\n"
        "#endif\n"
        "#ifdef AV_DIFFUSE_TEXTURE\n"
            "OUT.rgb += afLightColor[1].rgb * DIFFUSE_COLOR.rgb * tex2D(DIFFUSE_SAMPLER,IN.TexCoord0).rgb * L1 +\n"
        "#else\n"
            "OUT.rgb += afLightColor[1].rgb * DIFFUSE_COLOR.rgb * L1 +\n"
        "#endif // !AV_DIFFUSE_TEXTURE\n"

        "#ifdef AV_SPECULAR_COMPONENT\n"
        "#ifdef AV_SPECULAR_TEXTURE\n"
            "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[1].rgb * tex2D(SPECULAR_SAMPLER,IN.TexCoord0).rgb * (saturate(L1 * 4.0f) * pow(dot(Reflect,ViewDir),SPECULARITY)) + \n"
        "#else\n"
            "SPECULAR_COLOR.rgb * SPECULAR_STRENGTH * afLightColor[1].rgb * (saturate(L1 * 4.0f) * pow(dot(Reflect,ViewDir),SPECULARITY)) + \n"
        "#endif // !AV_SPECULAR_TEXTURE\n"
        "#endif // !AV_SPECULAR_COMPONENT\n"
        "#ifdef AV_AMBIENT_TEXTURE\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[1].rgb * tex2D(AMBIENT_SAMPLER,IN.TexCoord0).rgb +\n"
        "#else\n"
            "AMBIENT_COLOR.rgb * afLightColorAmbient[1].rgb + \n"
        "#endif // !AV_AMBIENT_TEXTURE\n"
        "#ifdef AV_EMISSIVE_TEXTURE\n"
            "EMISSIVE_COLOR.rgb * tex2D(EMISSIVE_SAMPLER,IN.TexCoord0).rgb;\n"
        "#else \n"
            "EMISSIVE_COLOR.rgb;\n"
        "#endif // !AV_EMISSIVE_TEXTURE\n"
        "}\n"

        "#ifdef AV_OPACITY\n"
        "OUT.a = TRANSPARENCY;\n"
        "#endif\n"
        "#ifdef AV_OPACITY_TEXTURE\n"
        "OUT.a *= tex2D(OPACITY_SAMPLER,IN.TexCoord0). AV_OPACITY_TEXTURE_REGISTER_MASK;\n"
        "#endif\n"
        "return OUT;\n"
    "}\n"


    // Technique for the material effect
    "technique MaterialFXSpecular_D1\n"
    "{\n"
        "pass p0\n"
        "{\n"
            "#ifdef AV_OPACITY_TEXTURE\n"
            "AlphaBlendEnable=TRUE;"
            "SrcBlend = srcalpha;\n"
            "DestBlend = invsrcalpha;\n"
            "#else\n"
            "#ifdef AV_OPACITY\n"
            "AlphaBlendEnable=TRUE;"
            "SrcBlend = srcalpha;\n"
            "DestBlend = invsrcalpha;\n"
            "#endif \n"
            "#endif\n"

            "PixelShader = compile ps_3_0 MaterialPShaderSpecular_D1();\n"
            "VertexShader = compile vs_3_0 MaterialVShader_D1();\n"
        "}\n"
    "};\n"
    "technique MaterialFXSpecular_D2\n"
    "{\n"
        "pass p0\n"
        "{\n"
            "#ifdef AV_OPACITY_TEXTURE\n"
            "AlphaBlendEnable=TRUE;"
            "SrcBlend = srcalpha;\n"
            "DestBlend = invsrcalpha;\n"
            "#else\n"
            "#ifdef AV_OPACITY\n"
            "AlphaBlendEnable=TRUE;"
            "SrcBlend = srcalpha;\n"
            "DestBlend = invsrcalpha;\n"
            "#endif \n"
            "#endif\n"

            "PixelShader = compile ps_3_0 MaterialPShaderSpecular_D2();\n"
            "VertexShader = compile vs_3_0 MaterialVShader_D2();\n"
        "}\n"
    "};\n"

    // Technique for the material effect (ps_2_0)
    "technique MaterialFXSpecular_PS20_D1\n"
    "{\n"
        "pass p0\n"
    "{\n"
          "#ifdef AV_OPACITY_TEXTURE\n"
          "AlphaBlendEnable=TRUE;"
          "SrcBlend = srcalpha;\n"
          "DestBlend = invsrcalpha;\n"
          "#else\n"
          "#ifdef AV_OPACITY\n"
          "AlphaBlendEnable=TRUE;"
          "SrcBlend = srcalpha;\n"
          "DestBlend = invsrcalpha;\n"
          "#endif \n"
          "#endif\n"

          "PixelShader = compile ps_2_0 MaterialPShaderSpecular_PS20_D1();\n"
          "VertexShader = compile vs_2_0 MaterialVShader_D1();\n"
        "}\n"
    "};\n"

    "technique MaterialFXSpecular_PS20_D2\n"
    "{\n"
        "pass p0\n"
      "{\n"
          "//CullMode=none;\n"

          "#ifdef AV_OPACITY_TEXTURE\n"
          "AlphaBlendEnable=TRUE;"
          "SrcBlend = srcalpha;\n"
          "DestBlend = invsrcalpha;\n"
          "#else\n"
          "#ifdef AV_OPACITY\n"
          "AlphaBlendEnable=TRUE;"
          "SrcBlend = srcalpha;\n"
          "DestBlend = invsrcalpha;\n"
          "#endif \n"
          "#endif\n"

          "PixelShader = compile ps_2_0 MaterialPShaderSpecular_PS20_D2();\n"
          "VertexShader = compile vs_2_0 MaterialVShader_D2();\n"
        "}\n"
    "};\n"

    // Technique for the material effect using fixed function pixel pipeline
    "technique MaterialFX_FF\n"
    "{\n"
        "pass p0\n"
        "{\n"
            "//CullMode=none;\n"
            "SpecularEnable = true; \n"
            "VertexShader = compile vs_2_0 MaterialVShader_FF();\n"
            "ColorOp[0] = Modulate;\n"
            "ColorArg0[0] = Texture;\n"
            "ColorArg1[0] = Diffuse;\n"
            "AlphaOp[0] = Modulate;\n"
            "AlphaArg0[0] = Texture;\n"
            "AlphaArg1[0] = Diffuse;\n"
        "}\n"
    "};\n"
    );

std::string g_szPassThroughShader = std::string(
        "texture TEXTURE_2D;\n"
        "sampler TEXTURE_SAMPLER = sampler_state\n"
        "{\n"
            "Texture = (TEXTURE_2D);\n"
            "MinFilter = POINT;\n"
            "MagFilter = POINT;\n"
        "};\n"

    // Vertex Shader output for pixel shader usage
        "struct VS_OUTPUT\n"
        "{\n"
            "float4 Position : POSITION;\n"
            "float2 TexCoord0 : TEXCOORD0;\n"
        "};\n"

    // vertex shader for pixel shader usage
        "VS_OUTPUT DefaultVShader(float4 INPosition : POSITION, float2 INTexCoord0 : TEXCOORD0 )\n"
        "{\n"
            "VS_OUTPUT Out;\n"

            "Out.Position = INPosition;\n"
            "Out.TexCoord0 = INTexCoord0;\n"

            "return Out;\n"
        "}\n"

        // simply lookup a texture
        "float4 PassThrough_PS(float2 IN : TEXCOORD0) : COLOR\n"
        "{\n"
        "  return tex2D(TEXTURE_SAMPLER,IN);\n"
        "}\n"

        // visualize the alpha channel (in black) -> use a
        "float4 PassThroughAlphaA_PS(float2 IN : TEXCOORD0) : COLOR\n"
        "{\n"
        "  return float4(0.0f,0.0f,0.0f,tex2D(TEXTURE_SAMPLER,IN).a);\n"
        "}\n"

        // visualize the alpha channel (in black) -> use r
        "float4 PassThroughAlphaR_PS(float2 IN : TEXCOORD0) : COLOR\n"
        "{\n"
        "  return float4(0.0f,0.0f,0.0f,tex2D(TEXTURE_SAMPLER,IN).r);\n"
        "}\n"

        // Simple pass-through technique
        "technique PassThrough\n"
        "{\n"
            "pass p0\n"
            "{\n"
                "FillMode=Solid;\n"
                "ZEnable = FALSE;\n"
                "CullMode = none;\n"
                "AlphaBlendEnable = TRUE;\n"
                "SrcBlend =srcalpha;\n"
                "DestBlend =invsrcalpha;\n"
                "PixelShader = compile ps_2_0 PassThrough_PS();\n"
                "VertexShader = compile vs_2_0 DefaultVShader();\n"
            "}\n"
        "};\n"

        // Pass-through technique which visualizes the texture's alpha channel
        "technique PassThroughAlphaFromA\n"
        "{\n"
            "pass p0\n"
            "{\n"
                "FillMode=Solid;\n"
                "ZEnable = FALSE;\n"
                "CullMode = none;\n"
                "AlphaBlendEnable = TRUE;\n"
                "SrcBlend =srcalpha;\n"
                "DestBlend =invsrcalpha;\n"
                "PixelShader = compile ps_2_0 PassThroughAlphaA_PS();\n"
                "VertexShader = compile vs_2_0 DefaultVShader();\n"
            "}\n"
        "};\n"

        // Pass-through technique which visualizes the texture's red channel
        "technique PassThroughAlphaFromR\n"
        "{\n"
            "pass p0\n"
            "{\n"
                "FillMode=Solid;\n"
                "ZEnable = FALSE;\n"
                "CullMode = none;\n"
                "AlphaBlendEnable = TRUE;\n"
                "SrcBlend =srcalpha;\n"
                "DestBlend =invsrcalpha;\n"
                "PixelShader = compile ps_2_0 PassThroughAlphaR_PS();\n"
                "VertexShader = compile vs_2_0 DefaultVShader();\n"
            "}\n"
        "};\n"

        // technique for fixed function pixel pipeline
        "technique PassThrough_FF\n"
        "{\n"
            "pass p0\n"
            "{\n"
                "ZEnable = FALSE;\n"
                "CullMode = none;\n"
                "AlphaBlendEnable = TRUE;\n"
                "SrcBlend =srcalpha;\n"
                "DestBlend =invsrcalpha;\n"
                "VertexShader = compile vs_2_0 DefaultVShader();\n"
        "ColorOp[0] = SelectArg1;\n"
        "ColorArg0[0] = Texture;\n"
        "AlphaOp[0] = SelectArg1;\n"
        "AlphaArg0[0] = Texture;\n"
            "}\n"
        "};\n"
    );

std::string g_szCheckerBackgroundShader = std::string(

        // the two colors used to draw the checker pattern
        "float3 COLOR_ONE = float3(0.4f,0.4f,0.4f);\n"
        "float3 COLOR_TWO = float3(0.6f,0.6f,0.6f);\n"

        // size of a square in both x and y direction
        "float SQUARE_SIZE = 10.0f;\n"

    // vertex shader output structure
        "struct VS_OUTPUT\n"
        "{\n"
            "float4 Position : POSITION;\n"	
        "};\n"

    // vertex shader 
        "VS_OUTPUT DefaultVShader(float4 INPosition : POSITION, float2 INTexCoord0 : TEXCOORD0 )\n"
        "{\n"
            "VS_OUTPUT Out;\n"

            "Out.Position = INPosition;\n"
            "return Out;\n"
        "}\n"

        // pixel shader
        "float4 MakePattern_PS(float2 IN : VPOS) : COLOR\n"
        "{\n"
          "float2 fDiv = IN / SQUARE_SIZE;\n"
          "float3 fColor = COLOR_ONE;\n"
          "if (0 == round(fmod(round(fDiv.x),2)))\n"
          "{\n"
          "  if (0 == round(fmod(round(fDiv.y),2))) fColor = COLOR_TWO;\n"
          "}\n"
          "else if (0 != round(fmod(round(fDiv.y),2)))fColor = COLOR_TWO;\n"
          "return float4(fColor,1.0f);"
        "}\n"
    
        // technique to generate a pattern
        "technique MakePattern\n"
        "{\n"
          "pass p0\n"
          "{\n"
            "FillMode=Solid;\n"
            "ZEnable = FALSE;\n"
            "CullMode = none;\n"
            "PixelShader = compile ps_3_0 MakePattern_PS();\n"
            "VertexShader = compile vs_3_0 DefaultVShader();\n"
          "}\n"
        "};\n"
        );
    };