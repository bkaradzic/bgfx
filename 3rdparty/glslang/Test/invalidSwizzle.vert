#version 420

void f();

void main() {
    f().xx; // Scalar swizzle does not apply to void
    f().xy; // Vector swizzle does not apply either
}