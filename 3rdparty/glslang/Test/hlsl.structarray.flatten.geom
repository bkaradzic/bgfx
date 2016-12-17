
struct VertexData {
	float4 position : POSITION;
	float4 color    : COLOR0;
	float2 uv       : TEXCOORD0;
};

[maxvertexcount(4)]
void main(line VertexData vin[2], inout TriangleStream<VertexData> outStream)
{
    VertexData vout;

    vout.color = vin[0].color;
    vout.uv = vin[0].uv;
    vout.position = vin[0].position;
    outStream.Append(vout);
}
