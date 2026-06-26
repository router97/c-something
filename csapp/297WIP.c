/*
Following the bit-level floating-point coding rules, implement the function with
the following prototype:

// Compute (float) i
float_bits float_i2f(int i);

For argument i, this function computes the bit-level representation of
(float) i.

Test your function by evaluating it for all 2^32 values of argument f and comparing the result 
to what would be obtained using your machine’s floating-point
operations.
*/
#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_i2f(int i);

int main(int argc, char const *argv[])
{
    int ivalue = 0;
    while (true) {
        if (ivalue == 0) {
            printf("\n\nZERO\n\n");
        }
        ivalue++;
        float_bits i2fb = float_i2f(ivalue);
        float i2f = *(float*)&i2fb;
        if ((float)ivalue != i2f) {
            printf("%d failed.\nMine: %f\nCorrect: %f\n", ivalue, i2f, (float)ivalue);
        }
    }
    return 0;
}

#define bias 127
#define m 23

float_bits float_i2f(int i) {
    float_bits result;
    unsigned sign = (i >> 31) & 0x1;
    unsigned exp;
    unsigned frac;
    
    if (i == 0) {
        return sign << 31;
    }

    unsigned absolute_value = i;
    if (i < 0) {
        absolute_value = ~absolute_value + 1;
    }

    unsigned first_one = absolute_value;
    first_one |= first_one >> 16;
    first_one |= first_one >> 8;
    first_one |= first_one >> 4;
    first_one |= first_one >> 2;
    first_one |= first_one >> 1;
    first_one ^= first_one >> 1;
    
    frac = absolute_value;

    unsigned temp = first_one;
    int e = 0;

    exp = bias;
    unsigned first_one_which_bit = 0; 
    while (true) {
        temp >>= 1;
        if (temp > 0) {
            first_one_which_bit++;
        } else {
            break;
        }
    }
    exp += first_one_which_bit;

    temp = first_one;
    unsigned latest_discarded = 0;
    unsigned sticky = 0;

    while (temp != 0x800000) {
        if (temp > 0x800000) {
            sticky |= latest_discarded;
            latest_discarded = frac & 0x1u;
            temp >>= 1;
            frac >>= 1;
        } else if (temp < 0x800000) {
            temp <<= 1;
            frac <<= 1;
        }
    }
    if (latest_discarded && (sticky || (frac & 0x1))) {
        frac++;
        if (frac & 0x1000000) {
            exp++;
            frac >>= 1;
        }
    }
    frac &= 0x7FFFFF;


    return (sign << 31) | (exp << 23) | frac;
}
