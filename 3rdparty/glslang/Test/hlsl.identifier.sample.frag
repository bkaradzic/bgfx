
struct MyStruct {
    sample        float a;
    noperspective float b;
    linear        float c;
    centroid      float d;
};

int sample(int x) { return x; } // HLSL allows this as an identifier as well.

float4 main() : SV_Target0
{
    // HLSL allows this as an identifier as well.
    // However, this is not true of other qualifier keywords such as "linear".
    int sample = 3;

    return float4(0,0,0,0);
}
