/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

// progressive poisson-like pattern; x, y are in [-1, 1] range, .z is length( vec2(x,y) ), .w is log2( z )
#define INTELSSAO_MAIN_DISK_SAMPLE_COUNT (32)
CONST(vec4 g_samplePatternMain[INTELSSAO_MAIN_DISK_SAMPLE_COUNT]) =
{
   { 0.78488064,  0.56661671,  1.500000, -0.126083},    { 0.26022232, -0.29575172,  1.500000, -1.064030},    { 0.10459357,  0.08372527,  1.110000, -2.730563},    {-0.68286800,  0.04963045,  1.090000, -0.498827},
   {-0.13570161, -0.64190155,  1.250000, -0.532765},    {-0.26193795, -0.08205118,  0.670000, -1.783245},    {-0.61177456,  0.66664219,  0.710000, -0.044234},    { 0.43675563,  0.25119025,  0.610000, -1.167283},
   { 0.07884444,  0.86618668,  0.640000, -0.459002},    {-0.12790935, -0.29869005,  0.600000, -1.729424},    {-0.04031125,  0.02413622,  0.600000, -4.792042},    { 0.16201244, -0.52851415,  0.790000, -1.067055},
   {-0.70991218,  0.47301072,  0.640000, -0.335236},    { 0.03277707, -0.22349690,  0.600000, -1.982384},    { 0.68921727,  0.36800742,  0.630000, -0.266718},    { 0.29251814,  0.37775412,  0.610000, -1.422520},
   {-0.12224089,  0.96582592,  0.600000, -0.426142},    { 0.11071457, -0.16131058,  0.600000, -2.165947},    { 0.46562141, -0.59747696,  0.600000, -0.189760},    {-0.51548797,  0.11804193,  0.600000, -1.246800},
   { 0.89141309, -0.42090443,  0.600000,  0.028192},    {-0.32402530, -0.01591529,  0.600000, -1.543018},    { 0.60771245,  0.41635221,  0.600000, -0.605411},    { 0.02379565, -0.08239821,  0.600000, -3.809046},
   { 0.48951152, -0.23657045,  0.600000, -1.189011},    {-0.17611565, -0.81696892,  0.600000, -0.513724},    {-0.33930185, -0.20732205,  0.600000, -1.698047},    {-0.91974425,  0.05403209,  0.600000,  0.062246},
   {-0.15064627, -0.14949332,  0.600000, -1.896062},    { 0.53180975, -0.35210401,  0.600000, -0.758838},    { 0.41487166,  0.81442589,  0.600000, -0.505648},    {-0.24106961, -0.32721516,  0.600000, -1.665244}
};

// these values can be changed (up to SSAO_MAX_TAPS) with no changes required elsewhere; values for 4th and 5th preset are ignored but array needed to avoid compilation errors
// the actual number of texture samples is two times this value (each "tap" has two symmetrical depth texture samples)
CONST(uint g_numTaps[5]) = { 3, 5, 12, 0, 0 };

// an example of higher quality low/medium/high settings
// CONST(uint g_numTaps[5])  = { 4, 9, 16, 0, 0 };

// ** WARNING ** if changing anything here, please remember to update the corresponding C++ code!

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Optional parts that can be enabled for a required quality preset level and above (0 == Low, 1 == Medium, 2 == High, 3 == Highest/Adaptive, 4 == reference/unused )
// Each has its own cost. To disable just set to 5 or above.
//
// (experimental) tilts the disk (although only half of the samples!) towards surface normal; this helps with effect uniformity between objects but reduces effect distance and has other side-effects
#define SSAO_TILT_SAMPLES_ENABLE_AT_QUALITY_PRESET                      (99)        // to disable simply set to 99 or similar
#define SSAO_TILT_SAMPLES_AMOUNT                                        (0.4)
//
#define SSAO_HALOING_REDUCTION_ENABLE_AT_QUALITY_PRESET                 (1)         // to disable simply set to 99 or similar
#define SSAO_HALOING_REDUCTION_AMOUNT                                   (0.6)       // values from 0.0 - 1.0, 1.0 means max weighting (will cause artifacts, 0.8 is more reasonable)
//
#define SSAO_NORMAL_BASED_EDGES_ENABLE_AT_QUALITY_PRESET                (2)         // to disable simply set to 99 or similar
#define SSAO_NORMAL_BASED_EDGES_DOT_THRESHOLD                           (0.5)       // use 0-0.1 for super-sharp normal-based edges
//
#define SSAO_DETAIL_AO_ENABLE_AT_QUALITY_PRESET                         (1)         // whether to use DetailAOStrength; to disable simply set to 99 or similar
//
#define SSAO_DEPTH_MIPS_ENABLE_AT_QUALITY_PRESET                        (2)         // !!warning!! the MIP generation on the C++ side will be enabled on quality preset 2 regardless of this value, so if changing here, change the C++ side too
#define SSAO_DEPTH_MIPS_GLOBAL_OFFSET                                   (-4.3)      // best noise/quality/performance tradeoff, found empirically
//
// !!warning!! the edge handling is hard-coded to 'disabled' on quality level 0, and enabled above, on the C++ side; while toggling it here will work for 
// testing purposes, it will not yield performance gains (or correct results)
#define SSAO_DEPTH_BASED_EDGES_ENABLE_AT_QUALITY_PRESET                 (1)     
//
#define SSAO_REDUCE_RADIUS_NEAR_SCREEN_BORDER_ENABLE_AT_QUALITY_PRESET  (99)        // 99 means disabled; only helpful if artifacts at the edges caused by lack of out of screen depth data are not acceptable with the depth sampler in either clamp or mirror modes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SAMPLER2D(s_viewspaceDepthSource,  0); 
SAMPLER2D(s_viewspaceDepthSourceMirror,  1); 
IMAGE2D_RO(s_normalmapSource, rgba8, 2);
BUFFER_RO(s_loadCounter, uint, 3); 
SAMPLER2D(s_importanceMap,  4); 
IMAGE2D_ARRAY_RO(s_baseSSAO, rg8, 5);
IMAGE2D_ARRAY_WR(s_target, rg8, 6);

// packing/unpacking for edges; 2 bits per edge mean 4 gradient values (0, 0.33, 0.66, 1) for smoother transitions!
float PackEdges( vec4 edgesLRTB )
{
//    ivec4 edgesLRTBi = ivec4( saturate( edgesLRTB ) * 3.0 + 0.5 );
//    return ( (edgesLRTBi.x << 6) + (edgesLRTBi.y << 4) + (edgesLRTBi.z << 2) + (edgesLRTBi.w << 0) ) / 255.0;

    // optimized, should be same as above
    edgesLRTB = round( saturate( edgesLRTB ) * 3.05 );
    return dot( edgesLRTB, vec4( 64.0 / 255.0, 16.0 / 255.0, 4.0 / 255.0, 1.0 / 255.0 ) ) ;
}

vec3 NDCToViewspace( vec2 pos, float viewspaceDepth )
{
    vec3 ret;

    ret.xy = (u_ndcToViewMul * pos.xy + u_ndcToViewAdd) * viewspaceDepth;

    ret.z = viewspaceDepth;

    return ret;
}

// calculate effect radius and fit our screen sampling pattern inside it
void CalculateRadiusParameters( const float pixCenterLength, const vec2 pixelDirRBViewspaceSizeAtCenterZ, out float pixLookupRadiusMod, out float effectRadius, out float falloffCalcMulSq )
{
    effectRadius = u_effectRadius;

    // leaving this out for performance reasons: use something similar if radius needs to scale based on distance
    //effectRadius *= pow( pixCenterLength, u_radiusDistanceScalingFunctionPow);

    // when too close, on-screen sampling disk will grow beyond screen size; limit this to avoid closeup temporal artifacts
    const float tooCloseLimitMod = saturate( pixCenterLength * u_effectSamplingRadiusNearLimitRec ) * 0.8 + 0.2;
    
    effectRadius *= tooCloseLimitMod;

    // 0.85 is to reduce the radius to allow for more samples on a slope to still stay within influence
    pixLookupRadiusMod = (0.85 * effectRadius) / pixelDirRBViewspaceSizeAtCenterZ.x;

    // used to calculate falloff (both for AO samples and per-sample weights)
    falloffCalcMulSq= -1.0f / (effectRadius*effectRadius);
}

vec4 CalculateEdges( const float centerZ, const float leftZ, const float rightZ, const float topZ, const float bottomZ )
{
    // slope-sensitive depth-based edge detection
    vec4 edgesLRTB = vec4( leftZ, rightZ, topZ, bottomZ ) - centerZ;
    vec4 edgesLRTBSlopeAdjusted = edgesLRTB + edgesLRTB.yxwz;
    edgesLRTB = min( abs( edgesLRTB ), abs( edgesLRTBSlopeAdjusted ) );
    return saturate( ( 1.3 - edgesLRTB / (centerZ * 0.040) ) );

    // cheaper version but has artifacts
    // edgesLRTB = abs( vec4( leftZ, rightZ, topZ, bottomZ ) - centerZ; );
    // return saturate( ( 1.3 - edgesLRTB / (pixZ * 0.06 + 0.1) ) );
}

vec3 DecodeNormal( vec3 encodedNormal )
{
    vec3 normal = encodedNormal * u_normalsUnpackMul.xxx + u_normalsUnpackAdd.xxx;

#if SSAO_ENABLE_NORMAL_WORLD_TO_VIEW_CONVERSION
	normal = vec3( dot(normal, u_normalsWorldToViewspaceMatrix0.xyz),
					dot(normal, u_normalsWorldToViewspaceMatrix1.xyz),
					dot(normal, u_normalsWorldToViewspaceMatrix2.xyz));
#endif

    // normal = normalize( normal );    // normalize adds around 2.5% cost on High settings but makes little (PSNR 66.7) visual difference when normals are as in the sample (stored in R8G8B8A8_UNORM,
    //                                  // decoded in the shader), however it will likely be required if using different encoding/decoding or the inputs are not normalized, etc.

    return normal;
}

vec3 LoadNormal( ivec2 pos )
{
    vec3 encodedNormal = imageLoad(s_normalmapSource, pos).xyz;
    return DecodeNormal( encodedNormal );
}

vec3 LoadNormal( ivec2 pos, ivec2 offset )
{
    vec3 encodedNormal = imageLoad(s_normalmapSource, pos + offset ).xyz;
    return DecodeNormal( encodedNormal );
}

// all vectors in viewspace
float CalculatePixelObscurance( vec3 pixelNormal, vec3 hitDelta, float falloffCalcMulSq )
{
  float lengthSq = dot( hitDelta, hitDelta );
  float NdotD = dot(pixelNormal, hitDelta) / sqrt(lengthSq);

  float falloffMult = max( 0.0, lengthSq * falloffCalcMulSq + 1.0 );

  return max( 0, NdotD - u_effectHorizonAngleThreshold ) * falloffMult;
}

void SSAOTapInner( const int qualityLevel, inout float obscuranceSum, inout float weightSum, const vec2 samplingUV, const float mipLevel, const vec3 pixCenterPos, const vec3 negViewspaceDir,vec3 pixelNormal, const float falloffCalcMulSq, const float weightMod, const int dbgTapIndex)
{
    // get depth at sample
    float viewspaceSampleZ = texture2DLod(s_viewspaceDepthSource, samplingUV.xy, mipLevel ).x;

    // convert to viewspace
    vec3 hitPos = NDCToViewspace( samplingUV.xy, viewspaceSampleZ ).xyz;
    vec3 hitDelta = hitPos - pixCenterPos;

    float obscurance = CalculatePixelObscurance( pixelNormal, hitDelta, falloffCalcMulSq );
    float weight = 1.0;
 
    if( qualityLevel >= SSAO_HALOING_REDUCTION_ENABLE_AT_QUALITY_PRESET )
    {
        //float reduct = max( 0, dot( hitDelta, negViewspaceDir ) );
        float reduct = max( 0, -hitDelta.z ); // cheaper, less correct version
        reduct = saturate( reduct * u_negRecEffectRadius + 2.0 ); // saturate( 2.0 - reduct / u_effectRadius );
        weight = SSAO_HALOING_REDUCTION_AMOUNT * reduct + (1.0 - SSAO_HALOING_REDUCTION_AMOUNT);
    }
    weight *= weightMod;
    obscuranceSum += obscurance * weight;
    weightSum += weight;
}

void SSAOTap( const int qualityLevel, inout float obscuranceSum, inout float weightSum, const int tapIndex, const mat2 rotScale, const vec3 pixCenterPos, const vec3 negViewspaceDir, vec3 pixelNormal, const vec2 normalizedScreenPos, const float mipOffset, const float falloffCalcMulSq, float weightMod, vec2 normXY, float normXYLength)
{
    vec2  sampleOffset;
    float   samplePow2Len;

    // patterns
    {
        vec4 newSample = g_samplePatternMain[tapIndex];
        sampleOffset    = mul( rotScale, newSample.xy );
        samplePow2Len   = newSample.w;                      // precalculated, same as: samplePow2Len = log2( length( newSample.xy ) );
        weightMod *= newSample.z;
    }

    // snap to pixel center (more correct obscurance math, avoids artifacts)
    sampleOffset                    = round(sampleOffset);

    // calculate MIP based on the sample distance from the centre, similar to as described 
    // in http://graphics.cs.williams.edu/papers/SAOHPG12/.
    float mipLevel = ( qualityLevel < SSAO_DEPTH_MIPS_ENABLE_AT_QUALITY_PRESET )?(0):(samplePow2Len + mipOffset);

#if BGFX_SHADER_LANGUAGE_GLSL
	sampleOffset.y = -sampleOffset.y;
#endif
    vec2 samplingUV = sampleOffset * u_viewport2xPixelSize + normalizedScreenPos;

    SSAOTapInner( qualityLevel, obscuranceSum, weightSum, samplingUV, mipLevel, pixCenterPos, negViewspaceDir, pixelNormal, falloffCalcMulSq, weightMod, tapIndex * 2);

    // for the second tap, just use the mirrored offset
    vec2 sampleOffsetMirroredUV    = -sampleOffset;

    // tilt the second set of samples so that the disk is effectively rotated by the normal
    // effective at removing one set of artifacts, but too expensive for lower quality settings
    if( qualityLevel >= SSAO_TILT_SAMPLES_ENABLE_AT_QUALITY_PRESET )
    {
        float dotNorm = dot( sampleOffsetMirroredUV, normXY );
        sampleOffsetMirroredUV -= dotNorm * normXYLength * normXY;
        sampleOffsetMirroredUV = round(sampleOffsetMirroredUV);
    }

    // snap to pixel center (more correct obscurance math, avoids artifacts)
    vec2 samplingMirroredUV = sampleOffsetMirroredUV * u_viewport2xPixelSize + normalizedScreenPos;

    SSAOTapInner( qualityLevel, obscuranceSum, weightSum, samplingMirroredUV, mipLevel, pixCenterPos, negViewspaceDir, pixelNormal, falloffCalcMulSq, weightMod, tapIndex * 2 + 1);
}

// this function is designed to only work with half/half depth at the moment - there's a couple of hardcoded paths that expect pixel/texel size, so it will not work for full res
void GenerateSSAOShadowsInternal( out float outShadowTerm, out vec4 outEdges, out float outWeight, 
	const vec2 SVPos, const int qualityLevel, bool adaptiveBase)
{
    vec2 SVPosRounded = trunc( SVPos );
    uvec2 SVPosui = uvec2( SVPosRounded ); //same as uvec2( SVPos )

    const uint numberOfTaps = (adaptiveBase)?(SSAO_ADAPTIVE_TAP_BASE_COUNT) : ( g_numTaps[qualityLevel] );
    float pixZ, pixLZ, pixTZ, pixRZ, pixBZ;

#if BGFX_SHADER_LANGUAGE_GLSL  
    vec4 valuesUL     = textureGather(s_viewspaceDepthSourceMirror, SVPosRounded * u_halfViewportPixelSize + vec2(0.0,u_halfViewportPixelSize.y), 0).wzyx;
    vec4 valuesBR     = textureGatherOffset(s_viewspaceDepthSourceMirror, SVPosRounded * u_halfViewportPixelSize + vec2(0.0,u_halfViewportPixelSize.y), ivec2( 1, -1 ), 0).wzyx;
#else
    vec4 valuesUL     = textureGather(s_viewspaceDepthSourceMirror, SVPosRounded * u_halfViewportPixelSize, 0);
    vec4 valuesBR     = textureGatherOffset(s_viewspaceDepthSourceMirror, SVPosRounded * u_halfViewportPixelSize, ivec2( 1, 1 ), 0);
#endif

    // get this pixel's viewspace depth
    pixZ = valuesUL.y; 

    // get left right top bottom neighbouring pixels for edge detection (gets compiled out on qualityLevel == 0)
    pixLZ   = valuesUL.x;
    pixTZ   = valuesUL.z;
    pixRZ   = valuesBR.z;
    pixBZ   = valuesBR.x;

    vec2 normalizedScreenPos = SVPosRounded * u_viewport2xPixelSize + u_viewport2xPixelSize_x_025;
    vec3 pixCenterPos = NDCToViewspace( normalizedScreenPos, pixZ ); // g

    // Load this pixel's viewspace normal
    uvec2 fullResCoord = uvec2(SVPosui * 2 + u_perPassFullResCoordOffset.xy);
    vec3 pixelNormal = LoadNormal( ivec2(fullResCoord) );

    const vec2 pixelDirRBViewspaceSizeAtCenterZ = pixCenterPos.z * u_ndcToViewMul * u_viewport2xPixelSize;  // optimized approximation of:  vec2 pixelDirRBViewspaceSizeAtCenterZ = NDCToViewspace( normalizedScreenPos.xy + u_viewportPixelSize.xy, pixCenterPos.z ).xy - pixCenterPos.xy;

    float pixLookupRadiusMod;
    float falloffCalcMulSq;

    // calculate effect radius and fit our screen sampling pattern inside it
    float effectViewspaceRadius;
    CalculateRadiusParameters( length( pixCenterPos ), pixelDirRBViewspaceSizeAtCenterZ, pixLookupRadiusMod, effectViewspaceRadius, falloffCalcMulSq );

    // calculate samples rotation/scaling
    mat2 rotScale;
    {
        // reduce effect radius near the screen edges slightly; ideally, one would render a larger depth buffer (5% on each side) instead
        if( !adaptiveBase && (qualityLevel >= SSAO_REDUCE_RADIUS_NEAR_SCREEN_BORDER_ENABLE_AT_QUALITY_PRESET) )
        {
            float nearScreenBorder = min( min( normalizedScreenPos.x, 1.0 - normalizedScreenPos.x ), min( normalizedScreenPos.y, 1.0 - normalizedScreenPos.y ) );
            nearScreenBorder = saturate( 10.0 * nearScreenBorder + 0.6 );
            pixLookupRadiusMod *= nearScreenBorder;
        }

        // load & update pseudo-random rotation matrix
#if BGFX_SHADER_LANGUAGE_GLSL
        uint pseudoRandomIndex = uint( (imageSize(s_target).y-1.0-SVPosRounded.y) * 2 + SVPosRounded.x ) % 5;
#else
        uint pseudoRandomIndex = uint( SVPosRounded.y * 2 + SVPosRounded.x ) % 5;
#endif
        vec4 rs = u_patternRotScaleMatrices( pseudoRandomIndex );
        rotScale = mat2( rs.x * pixLookupRadiusMod, rs.y * pixLookupRadiusMod, rs.z * pixLookupRadiusMod, rs.w * pixLookupRadiusMod );
    }

    // the main obscurance & sample weight storage
    float obscuranceSum = 0.0;
    float weightSum = 0.0;

    // edge mask for between this and left/right/top/bottom neighbour pixels - not used in quality level 0 so initialize to "no edge" (1 is no edge, 0 is edge)
    vec4 edgesLRTB = vec4( 1.0, 1.0, 1.0, 1.0 );

    // Move center pixel slightly towards camera to avoid imprecision artifacts due to using of 16bit depth buffer; a lot smaller offsets needed when using 32bit floats
    pixCenterPos *= u_depthPrecisionOffsetMod;

    if( !adaptiveBase && (qualityLevel >= SSAO_DEPTH_BASED_EDGES_ENABLE_AT_QUALITY_PRESET) )
    {
        edgesLRTB = CalculateEdges( pixZ, pixLZ, pixRZ, pixTZ, pixBZ );
    }

    // adds a more high definition sharp effect, which gets blurred out (reuses left/right/top/bottom samples that we used for edge detection)
    if( !adaptiveBase && (qualityLevel >= SSAO_DETAIL_AO_ENABLE_AT_QUALITY_PRESET) )
    {
        // disable in case of quality level 4 (reference)
        if( qualityLevel != 4 )
        {
            //approximate neighbouring pixels positions (actually just deltas or "positions - pixCenterPos" )
            vec3 viewspaceDirZNormalized = vec3( pixCenterPos.xy / pixCenterPos.zz, 1.0 );
            vec3 pixLDelta  = vec3( -pixelDirRBViewspaceSizeAtCenterZ.x, 0.0, 0.0 ) + viewspaceDirZNormalized * (pixLZ - pixCenterPos.z); // very close approximation of: vec3 pixLPos  = NDCToViewspace( normalizedScreenPos + vec2( -u_halfViewportPixelSize.x, 0.0 ), pixLZ ).xyz - pixCenterPos.xyz;
            vec3 pixRDelta  = vec3( +pixelDirRBViewspaceSizeAtCenterZ.x, 0.0, 0.0 ) + viewspaceDirZNormalized * (pixRZ - pixCenterPos.z); // very close approximation of: vec3 pixRPos  = NDCToViewspace( normalizedScreenPos + vec2( +u_halfViewportPixelSize.x, 0.0 ), pixRZ ).xyz - pixCenterPos.xyz;
#if BGFX_SHADER_LANGUAGE_GLSL
            vec3 pixTDelta  = vec3( 0.0, +pixelDirRBViewspaceSizeAtCenterZ.y, 0.0 ) + viewspaceDirZNormalized * (pixTZ - pixCenterPos.z); // very close approximation of: vec3 pixTPos  = NDCToViewspace( normalizedScreenPos + vec2( 0.0, -u_halfViewportPixelSize.y ), pixTZ ).xyz - pixCenterPos.xyz;
            vec3 pixBDelta  = vec3( 0.0, -pixelDirRBViewspaceSizeAtCenterZ.y, 0.0 ) + viewspaceDirZNormalized * (pixBZ - pixCenterPos.z); // very close approximation of: vec3 pixBPos  = NDCToViewspace( normalizedScreenPos + vec2( 0.0, +u_halfViewportPixelSize.y ), pixBZ ).xyz - pixCenterPos.xyz;
#else
            vec3 pixTDelta  = vec3( 0.0, -pixelDirRBViewspaceSizeAtCenterZ.y, 0.0 ) + viewspaceDirZNormalized * (pixTZ - pixCenterPos.z); // very close approximation of: vec3 pixTPos  = NDCToViewspace( normalizedScreenPos + vec2( 0.0, -u_halfViewportPixelSize.y ), pixTZ ).xyz - pixCenterPos.xyz;
            vec3 pixBDelta  = vec3( 0.0, +pixelDirRBViewspaceSizeAtCenterZ.y, 0.0 ) + viewspaceDirZNormalized * (pixBZ - pixCenterPos.z); // very close approximation of: vec3 pixBPos  = NDCToViewspace( normalizedScreenPos + vec2( 0.0, +u_halfViewportPixelSize.y ), pixBZ ).xyz - pixCenterPos.xyz;
#endif

            const float rangeReductionConst         = 4.0f;                         // this is to avoid various artifacts
            const float modifiedFalloffCalcMulSq    = rangeReductionConst * falloffCalcMulSq;

            vec4 additionalObscurance;
            additionalObscurance.x = CalculatePixelObscurance( pixelNormal, pixLDelta, modifiedFalloffCalcMulSq );
            additionalObscurance.y = CalculatePixelObscurance( pixelNormal, pixRDelta, modifiedFalloffCalcMulSq );
            additionalObscurance.z = CalculatePixelObscurance( pixelNormal, pixTDelta, modifiedFalloffCalcMulSq );
            additionalObscurance.w = CalculatePixelObscurance( pixelNormal, pixBDelta, modifiedFalloffCalcMulSq );

            obscuranceSum += u_detailAOStrength * dot( additionalObscurance, edgesLRTB );
        }
    }

    // Sharp normals also create edges - but this adds to the cost as well
    if( !adaptiveBase && (qualityLevel >= SSAO_NORMAL_BASED_EDGES_ENABLE_AT_QUALITY_PRESET ) )
    {
        vec3 neighbourNormalL  = LoadNormal( ivec2(fullResCoord), ivec2( -2,  0 ) );
        vec3 neighbourNormalR  = LoadNormal( ivec2(fullResCoord), ivec2(  2,  0 ) );
#if BGFX_SHADER_LANGUAGE_GLSL
        vec3 neighbourNormalT  = LoadNormal( ivec2(fullResCoord), ivec2(  0,  2 ) );
        vec3 neighbourNormalB  = LoadNormal( ivec2(fullResCoord), ivec2(  0, -2 ) );
#else
        vec3 neighbourNormalT  = LoadNormal( ivec2(fullResCoord), ivec2(  0, -2 ) );
        vec3 neighbourNormalB  = LoadNormal( ivec2(fullResCoord), ivec2(  0,  2 ) );
#endif

        const float dotThreshold = SSAO_NORMAL_BASED_EDGES_DOT_THRESHOLD;

        vec4 normalEdgesLRTB;
        normalEdgesLRTB.x = saturate( (dot( pixelNormal, neighbourNormalL ) + dotThreshold ) );
        normalEdgesLRTB.y = saturate( (dot( pixelNormal, neighbourNormalR ) + dotThreshold ) );
        normalEdgesLRTB.z = saturate( (dot( pixelNormal, neighbourNormalT ) + dotThreshold ) );
        normalEdgesLRTB.w = saturate( (dot( pixelNormal, neighbourNormalB ) + dotThreshold ) );

//#define SSAO_SMOOTHEN_NORMALS // fixes some aliasing artifacts but kills a lot of high detail and adds to the cost - not worth it probably but feel free to play with it
#ifdef SSAO_SMOOTHEN_NORMALS
        //neighbourNormalL  = LoadNormal( fullResCoord, ivec2( -1,  0 ) );
        //neighbourNormalR  = LoadNormal( fullResCoord, ivec2(  1,  0 ) );
        //neighbourNormalT  = LoadNormal( fullResCoord, ivec2(  0, -1 ) );
        //neighbourNormalB  = LoadNormal( fullResCoord, ivec2(  0,  1 ) );
        pixelNormal += neighbourNormalL * edgesLRTB.x + neighbourNormalR * edgesLRTB.y + neighbourNormalT * edgesLRTB.z + neighbourNormalB * edgesLRTB.w;
        pixelNormal = normalize( pixelNormal );
#endif

        edgesLRTB *= normalEdgesLRTB;
    }

    const float globalMipOffset     = SSAO_DEPTH_MIPS_GLOBAL_OFFSET;
    float mipOffset = ( qualityLevel < SSAO_DEPTH_MIPS_ENABLE_AT_QUALITY_PRESET ) ? ( 0 ) : ( log2( pixLookupRadiusMod ) + globalMipOffset );

    // Used to tilt the second set of samples so that the disk is effectively rotated by the normal
    // effective at removing one set of artifacts, but too expensive for lower quality settings
    vec2 normXY = vec2( pixelNormal.x, pixelNormal.y );
    float normXYLength = length( normXY );
    normXY /= vec2( normXYLength, -normXYLength );
    normXYLength *= SSAO_TILT_SAMPLES_AMOUNT;

    const vec3 negViewspaceDir = -normalize( pixCenterPos );

    // standard, non-adaptive approach
    if( (qualityLevel != 3) || adaptiveBase )
    {
        // [unroll] // <- doesn't seem to help on any platform, although the compilers seem to unroll anyway if const number of tap used!
        for( uint i = 0; i < numberOfTaps; i++ )
        {
            SSAOTap( qualityLevel, obscuranceSum, weightSum, int(i), rotScale, pixCenterPos, negViewspaceDir, pixelNormal, normalizedScreenPos, mipOffset, falloffCalcMulSq, 1.0, normXY, normXYLength);
        }
    }
    else // if( qualityLevel == 3 ) adaptive approach
    {
        // add new ones if needed
        vec2 fullResUV = normalizedScreenPos + u_perPassFullResUVOffset.xy;
		float importance = texture2DLod(s_importanceMap, fullResUV, 0.0 ).x;

        // this is to normalize SSAO_DETAIL_AO_AMOUNT across all pixel regardless of importance
        obscuranceSum *= (SSAO_ADAPTIVE_TAP_BASE_COUNT / float(SSAO_MAX_TAPS)) + (importance * SSAO_ADAPTIVE_TAP_FLEXIBLE_COUNT / float(SSAO_MAX_TAPS));

        // load existing base values
        vec2 baseValues = imageLoad(s_baseSSAO, ivec3( SVPosui, u_passIndex ) ).xy;
        weightSum += baseValues.y * (float(SSAO_ADAPTIVE_TAP_BASE_COUNT) * 4.0);
        obscuranceSum += (baseValues.x) * weightSum;

        // increase importance around edges
        float edgeCount = dot( 1.0-edgesLRTB, vec4( 1.0, 1.0, 1.0, 1.0 ) );
        //importance += edgeCount / (float)SSAO_ADAPTIVE_TAP_FLEXIBLE_COUNT;

        float avgTotalImportance = float(s_loadCounter[0]) * u_loadCounterAvgDiv;

        float importanceLimiter = saturate( u_adaptiveSampleCountLimit / avgTotalImportance );
        importance *= importanceLimiter;

        float additionalSampleCountFlt = SSAO_ADAPTIVE_TAP_FLEXIBLE_COUNT * importance;

        const float blendRange = 3.0; // use 1 to just blend the last one; use larger number to blend over more for a more smooth transition
        const float blendRangeInv = 1.0 / blendRange;

        additionalSampleCountFlt += 0.5;
        uint additionalSamples   = uint( additionalSampleCountFlt );
        uint additionalSamplesTo = min( SSAO_MAX_TAPS, additionalSamples + SSAO_ADAPTIVE_TAP_BASE_COUNT );

        // additional manual unroll doesn't help unfortunately
        LOOP
        for( uint i = SSAO_ADAPTIVE_TAP_BASE_COUNT; i < additionalSamplesTo; i++ )
        {
            additionalSampleCountFlt -= 1.0f;
            float weightMod = saturate(additionalSampleCountFlt * blendRangeInv); // slowly blend in the last few samples
            SSAOTap( qualityLevel, obscuranceSum, weightSum, int(i), rotScale, pixCenterPos, negViewspaceDir, pixelNormal, normalizedScreenPos, mipOffset, falloffCalcMulSq, weightMod, normXY, normXYLength);
        }
    }

    // early out for adaptive base - just output weight (used for the next pass)
    if( adaptiveBase )
    {
        float obscurance = obscuranceSum / weightSum;

        outShadowTerm   = obscurance;
        outEdges        = vec4(0,0,0,0);
        outWeight       = weightSum;
        return;
    }

    // calculate weighted average
    float obscurance = obscuranceSum / weightSum;

    // calculate fadeout (1 close, gradient, 0 far)
    float fadeOut = saturate( pixCenterPos.z * u_effectFadeOutMul + u_effectFadeOutAdd );
  
    // Reduce the SSAO shadowing if we're on the edge to remove artifacts on edges (we don't care for the lower quality one)
    if( !adaptiveBase && (qualityLevel >= SSAO_DEPTH_BASED_EDGES_ENABLE_AT_QUALITY_PRESET) )
    {
        // float edgeCount = dot( 1.0-edgesLRTB, vec4( 1.0, 1.0, 1.0, 1.0 ) );

        // when there's more than 2 opposite edges, start fading out the occlusion to reduce aliasing artifacts
        float edgeFadeoutFactor = saturate( (1.0 - edgesLRTB.x - edgesLRTB.y) * 0.35) + saturate( (1.0 - edgesLRTB.z - edgesLRTB.w) * 0.35 );

        // (experimental) if you want to reduce the effect next to any edge
        // edgeFadeoutFactor += 0.1 * saturate( dot( 1 - edgesLRTB, vec4( 1, 1, 1, 1 ) ) );

        fadeOut *= saturate( 1.0 - edgeFadeoutFactor );
    }
    
    // same as a bove, but a lot more conservative version
    // fadeOut *= saturate( dot( edgesLRTB, vec4( 0.9, 0.9, 0.9, 0.9 ) ) - 2.6 );

    // strength
    obscurance = u_effectShadowStrength * obscurance;
    
    // clamp
    obscurance = min( obscurance, u_effectShadowClamp );
    
    // fadeout
    obscurance *= fadeOut;

    // conceptually switch to occlusion with the meaning being visibility (grows with visibility, occlusion == 1 implies full visibility), 
    // to be in line with what is more commonly used.
    float occlusion = 1.0 - obscurance;

    // modify the gradient
    // note: this cannot be moved to a later pass because of loss of precision after storing in the render target
    occlusion = pow( saturate( occlusion ), u_effectShadowPow );

    // outputs!
    outShadowTerm   = occlusion;    // Our final 'occlusion' term (0 means fully occluded, 1 means fully lit)
    outEdges        = edgesLRTB;    // These are used to prevent blurring across edges, 1 means no edge, 0 means edge, 0.5 means half way there, etc.
    outWeight       = weightSum;
}

NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy) + uvec2(u_rect.xy);
	if (all(lessThan(dtID.xy, u_rect.zw) ) )
	{ 
		float   outShadowTerm;
		float   outWeight;
		vec4  outEdges;
		GenerateSSAOShadowsInternal( outShadowTerm, outEdges, outWeight, vec2(dtID.xy), ASSAO_QUALITY, ASSAO_ADAPTIVE_BASE);
		vec2 out0;
		out0.x = outShadowTerm;

		if ( ASSAO_ADAPTIVE_BASE )
		{
			out0.y = outWeight / (float(SSAO_ADAPTIVE_TAP_BASE_COUNT) * 4.0); //0.0; //frac(outWeight / 6.0);// / (float)(SSAO_MAX_TAPS * 4.0);
		}
		else
		{
			if (ASSAO_QUALITY == 0)
				out0.y = PackEdges( vec4( 1, 1, 1, 1 ) ); // no edges in low quality
			else
				out0.y = PackEdges( outEdges );
		}
		imageStore(s_target, ivec3(dtID.xy, u_layer), out0.xyyy);
	}
}
