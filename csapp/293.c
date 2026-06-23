/*
Following the bit-level floating-point coding rules, implement the function with
the following prototype:

// Compute |f|. If f is NaN, then return f.
float_bits float_absval(float_bits f);

For floating-point number f , this function computes |f |. If f is NaN, your
function should simply return f .

Test your function by evaluating it for all 2^32 values of argument f and comparing the result to what would be obtained using 
your machine’s floating-point
operations.
*/
#include <assert.h>
#include <math.h>

typedef unsigned float_bits;

float_bits float_absval(float_bits f);

int main(int argc, char const *argv[])
{
    for (float_bits counter = 0;; counter++) {
        float fcounter = *(float*)&counter;
        float absfcounter = fabs(fcounter);
        float_bits bitabsfcounter = *(float_bits*)&absfcounter;

        // will fail on Nan but for it not to i will have to not simply return f
        assert(float_absval(counter) == bitabsfcounter);

        if (counter == ~0) {
            break;
        }
    }
    return 0;
}


float_bits float_absval(float_bits f) {
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF && frac != 0x0) {
        return f;
    }

    return f & 0x7FFFFFFFu;
}
