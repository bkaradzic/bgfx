#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct main0_out
{
    half foo [[color(0)]];
    short bar [[color(1)]];
    ushort baz [[color(2)]];
};

fragment main0_out main0()
{
    main0_out out = {};
    out.foo = 1.0h;
    out.bar = 2;
    out.baz = 3u;
    return out;
}

