#version 460 core

struct S {
    float f;
    vec4 v;
};

in S s;

void main()
{
    interpolateAtCentroid(s.v);
    bool b1;
    b1 = anyInvocation(b1);
    b1 = allInvocations(b1);
    b1 = allInvocationsEqual(b1);
}
