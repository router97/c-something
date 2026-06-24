/*
Following the bit-level floating-point coding rules, implement the function with
the following prototype:

// Compute 2*f. If f is NaN, then return f.
float_bits float_twice(float_bits f);

For floating-point number f , this function computes 2.0 . f . If f is NaN, your
function should simply return f .

Test your function by evaluating it for all 2^32 values of argument f and comparing the result to what would 
be obtained using your machine's floating-point
operations.
*/
#include <assert.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f);

int main(int argc, char const *argv[])
{
    float_bits accumulator = 0x00000001;
    while (accumulator != 0x7F800000) {
        float fa = *(float*)&accumulator;
        float f2a = fa*2;
        float_bits bf2a = *(float_bits*)&f2a;
        accumulator = float_twice(accumulator);
        assert(accumulator == bf2a);
    }

    accumulator = 0x00000000;
    while (accumulator != 0xFFFFFFFF) {
        float fa = *(float*)&accumulator;
        float f2a = fa*2;
        float_bits bf2a = *(float_bits*)&f2a;
        assert(float_twice(accumulator) == bf2a); // fails
        accumulator++;
    }
    return 0;
}

float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF && frac != 0x0) {
        return f;
    }

    if (exp == 0 && !(frac & 0x400000)) {
        frac <<= 1;
    } else if (exp == 0 && (frac & 0x400000)) {
        exp = 1;
        frac <<= 1;
        frac &= 0x7FFFFF;
    } else if (exp < 0xFFu) {
        exp += 1;
    } else {
        exp = 0xFF;
        frac = 0;
    }
    
    return (sign << 31) | (exp << 23) | frac;
}
