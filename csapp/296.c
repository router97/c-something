/*
Following the bit-level floating-point coding rules, implement the function with
the following prototype:

* Compute (int) f.
* If conversion causes overflow or f is NaN, return 0x80000000

int float_f2i(float_bits f);

For floating-point number f , this function computes (int) f . Your function
should round toward zero. If f cannot be represented as an integer (e.g., it is out
of range, or it is NaN), then the function should return 0x80000000.

Test your function by evaluating it for all 2^32 values of argument f and comparing the result to what 
would be obtained using your machine's floating-point operations.
*/

typedef unsigned float_bits;

int float_f2i(float_bits f);

int main(int argc, char const *argv[])
{
    return 0;
}

#define bias 127
#define m 23

int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned real_mantissa = frac | 0x800000;
    int result;

    if (exp > 30 + bias) {
        return 0x80000000;
    }
    if (exp < 0 + bias) {
        return 0;
    }
    
    if (exp >= m + bias) {
        result = real_mantissa << ((exp-bias) - m);
        if (sign) {
            result = -result;
        }
        return result;
    }
    
    result = real_mantissa >> m - (exp-bias);
    
    if (sign) {
        result = -result;
    }
    return result;
}
