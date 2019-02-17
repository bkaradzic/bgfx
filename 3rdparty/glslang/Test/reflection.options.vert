#version 440 core

struct VertexInfo {
    float position[3];
    float normal[3];
};

struct TriangleInfo {
    VertexInfo v[3];
};

buffer VertexCollection {
    TriangleInfo t[5];
    uint padding[10];
};

buffer MultipleArrays {
    TriangleInfo tri[5];
    VertexInfo vert[5];
    float f[5];
} multiarray;

uniform UBO {
    VertexInfo verts[2];
    float flt[8];
    uvec4 unused;
} ubo;

struct OutputStruct {
    float val;
    vec3 a;
    vec2 b[4];
    mat2x2 c;
};

out OutputStruct outval;

void main()
{
    float f;
    f += t[0].v[0].position[0];
    f += t[gl_InstanceID].v[gl_InstanceID].position[gl_InstanceID];
    f += t[gl_InstanceID].v[gl_InstanceID].normal[gl_InstanceID];
    f += multiarray.tri[gl_InstanceID].v[0].position[0];
    f += multiarray.vert[gl_InstanceID].position[0];
    f += multiarray.f[gl_InstanceID];
    f += ubo.verts[gl_InstanceID].position[0];
    f += ubo.flt[gl_InstanceID];
    TriangleInfo tlocal[5] = t;
    outval.val = f;
}
