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
    // sorry

    unsigned ux = *(unsigned*)&x;
    unsigned uy = *(unsigned*)&y;

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    unsigned mx = ux & 0x007FFFFFu;
    unsigned my = uy & 0x007FFFFFu;

    unsigned ex = (ux >> 23) & 0x000000FFu;
    unsigned ey = (uy >> 23) & 0x000000FFu;

    if (ex == 0 && ey == 0 && mx == 0 && my == 0) {
        return 1;
    }
    if (sx > sy) {
        return 1;
    }
    if (sx < sy) {
        return 0;
    }

    if (sx) {
        unsigned temp;

        temp = mx;
        mx = my;
        my = temp;

        temp = ex;
        ex = ey;
        ey = temp;
    }

    if (ex < ey) {
        return 1;
    }
    if (ey < ex) {
        return 0;
    }

    if (mx < my) {
        return 1;
    }

    if (my < mx) {
        return 0;
    }
    return 1;
}
