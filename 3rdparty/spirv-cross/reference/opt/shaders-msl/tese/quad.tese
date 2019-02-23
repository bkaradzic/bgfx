#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct main0_out
{
    float4 gl_Position [[position]];
};

struct main0_patchIn
{
    float gl_TessLevelInner_0 [[attribute(0)]];
    float gl_TessLevelInner_1 [[attribute(1)]];
    float gl_TessLevelOuter_0 [[attribute(2)]];
    float gl_TessLevelOuter_1 [[attribute(3)]];
    float gl_TessLevelOuter_2 [[attribute(4)]];
    float gl_TessLevelOuter_3 [[attribute(5)]];
};

[[ patch(quad, 0) ]] vertex main0_out main0(main0_patchIn patchIn [[stage_in]], float2 gl_TessCoord [[position_in_patch]])
{
    main0_out out = {};
    float gl_TessLevelInner[2] = {};
    float gl_TessLevelOuter[4] = {};
    gl_TessLevelInner[0] = patchIn.gl_TessLevelInner_0;
    gl_TessLevelInner[1] = patchIn.gl_TessLevelInner_1;
    gl_TessLevelOuter[0] = patchIn.gl_TessLevelOuter_0;
    gl_TessLevelOuter[1] = patchIn.gl_TessLevelOuter_1;
    gl_TessLevelOuter[2] = patchIn.gl_TessLevelOuter_2;
    gl_TessLevelOuter[3] = patchIn.gl_TessLevelOuter_3;
    out.gl_Position = float4(((gl_TessCoord.x * as_type<float>(gl_TessLevelInner[0])) * as_type<float>(gl_TessLevelOuter[0])) + (((1.0 - gl_TessCoord.x) * as_type<float>(gl_TessLevelInner[0])) * as_type<float>(gl_TessLevelOuter[2])), ((gl_TessCoord.y * as_type<float>(gl_TessLevelInner[1])) * as_type<float>(gl_TessLevelOuter[1])) + (((1.0 - gl_TessCoord.y) * as_type<float>(gl_TessLevelInner[1])) * as_type<float>(gl_TessLevelOuter[3])), 0.0, 1.0);
    return out;
}

