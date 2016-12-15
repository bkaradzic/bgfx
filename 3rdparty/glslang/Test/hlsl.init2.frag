
void Test1()
{
    struct mystruct { float2 a; };
    mystruct test1 = {
        { 1, 2, },          // test trailing commas in list
    };

    mystruct test2 = {
        float2(3, 4),
    };

    // mystruct test3 = {
    //     { { 5, 6, } },   // TODO: test unneeded levels
    // };

    float test4 = { 7, } ;   // test scalar initialization

    struct mystruct2 { float a; float b; float c; };
    mystruct2 test5 = { {8,}, {9,}, {10}, };
}

struct PS_OUTPUT { float4 color : SV_Target0; };

PS_OUTPUT main()
{
    Test1();

    PS_OUTPUT ps_output;
    ps_output.color = 1.0;
    return ps_output;
}
