/*
You have been assigned the task of writing a C function to compute a floating point representation of 2^x. 
You decide that the best way to do this is to directly
construct the IEEE single-precision representation of the result. When x is too
small, your routine will return 0.0. When x is too large, it will return +∞. Fill in the
blank portions of the code that follows to compute the correct result. Assume the
function u2f returns a floating-point value having an identical bit representation
as its unsigned argument.
*/
float fpwr2(int x);

int main(int argc, char const *argv[])
{
    return 0;
}

#define BIAS 127
#define MAX_8BIT 255
#define M 23
#define LOWEST_POWER (1 - BIAS - M)
#define LOWEST_NORMALIZED_POWER (1 - BIAS)
#define HIGHEST_POWER (MAX_8BIT - 1 - BIAS)

float fpwr2(int x) {
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < LOWEST_POWER) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < LOWEST_NORMALIZED_POWER) {
        /* Denormalized result */
        exp = 0;
        frac = 0x00000001u << x - LOWEST_POWER;
    } else if (x < HIGHEST_POWER + 1) {
        /* Normalized result. */
        exp = x + BIAS;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 0xFFu;
        frac = 0;
    }
    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}
