/*
Following the bit-level floating-point coding rules, implement the function with
the following prototype:

// Compute -f. If f is NaN, then return f.
float_bits float_negate(float_bits f);
For floating-point number f , this function computes −f . If f is NaN, your
function should simply return f .

Test your function by evaluating it for all 2^32 values of argument f and comparing the result to what would be 
obtained using your machine’s floating-point operations.
*/
#include <assert.h>
#include <stdio.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f);

int main(int argc, char const *argv[])
{
    float_bits max = ~0;
    for (float_bits counter = 0;; counter++) {
        float fcounter = *(float*)&counter;
        float negfcounter = -fcounter;
        float_bits bitnegfcounter = *(float_bits*)&negfcounter;

        // will fail on Nan but for it not to i will have to not simply return f
        assert(float_negate(counter) == bitnegfcounter);

        if (counter == ~0) {
            break;
        }
    }
    
    return 0;
}

float_bits float_negate(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF && frac != 0x0) {
        return f;
    }

    return ((sign^0x1u) << 31) | (exp << 23) | frac;
}
