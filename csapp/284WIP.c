/*
Fill in the return value for the following procedure, which tests whether its first
argument is less than or equal to its second. Assume the function f2u returns an
unsigned 32-bit number having the same bit representation as its floating-point
argument. You can assume that neither argument is NaN. The two flavors of zero,
+0 and -0, are considered equal.

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);
    // Get the sign bits
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;
    // Give an expression using only ux, uy, sx, and sy
    return ;
}
*/
int float_le(float x, float y);

int main(int argc, char const *argv[])
{
    return 0;
}

int float_le(float x, float y) {
    unsigned ux = *(unsigned*)&x;
    unsigned uy = *(unsigned*)&y;

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    /*
    if both are zero, return 1
    compare the signs, if different, return 1 if x is the negative one, 0 if y
    if equal, go on to compare them normally if both positive, but reverse if negative
    */
    return ((ux & 0x7FFFFFFF) == 0) && ((uy & 0x7FFFFFFF) == 0) ? 1 : (
        sx > sy ? 1 : 
        (sy > sx ? 0 : 
            sx == 1 ?
                ((ux & 0x7FFFFFFF) >= (uy & 0x7FFFFFFF) ? 1 : 
                    0
                )
                :
                ((ux & 0x7FFFFFFF) <= (uy & 0x7FFFFFFF) ? 1 : 
                0
                )
        ));
}
