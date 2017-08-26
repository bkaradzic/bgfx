struct S {
    float4 pos   : SV_Position;
    float  clip  : SV_ClipDistance0;
    float  cull  : SV_CullDistance0;
};

[maxvertexcount(3)]
void main(triangle in float4 pos[3] : SV_Position, 
          triangle in uint VertexID[3] : VertexID,
          inout LineStream<S> OutputStream,
          triangle in float clip[3] : SV_ClipDistance,  // scalar float
          triangle in float cull[3] : SV_CullDistance)  // scalar float
{
    S s;

    s.pos = pos[0];
    s.clip = clip[0];
    s.cull = cull[0];

    OutputStream.Append(s);
}

