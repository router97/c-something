int a(int x, int y);
int b(int x, int y);
int c(int x, int y);
int d(int x, int y);
int e(int x, int y);

int main(int argc, char const *argv[])
{
    return 0;
}

int a(int x, int y) {
    return (x<y) == (-x>-y);

    // -INT_MIN = INT_MIN
    // INT_MIN = 80...0
    // ~80...0 + 1 = 7F...F + 1 = 80...0

    // min < max != min > min+1
}

int b(int x, int y) {
    return ((x+y)<<4) + y-x == 17*y+15*x;

    // (x + y) * 16 + y - x == 15x + 17y
    // 16x + 16y + y - x == 15x + 17y
    // 15x + 17y == 15x + 17y

    // math is correct
    // overflow isn't a problem
}

int c(int x, int y) {
    return ~x+~y+1 == ~(x+y);

    // treat all as unsigned for easier math
    // NOT operator does (UINT_MAX - target)

    // UINT_MAX - x + UINT_MAX - y + 1 = UINT_MAX - (x + y)
    // (UINT_MAX + UINT_MAX) - x - y + 1 = UINT_MAX - x - y
    // (UINT_MAX + (1 + (UINT_MAX - 1))) - x - y + 1 = UINT_MAX - x - y
    //          UINT_MAX + 1 = 0
    // UINT_MAX - 1 - x - y + 1 = UINT_MAX - x - y
    // UINT_MAX - x - y = UINT_MAX - x - y
}

int d(int x, int y) {
    unsigned ux = (unsigned) x;
    unsigned uy = (unsigned) y;
    
    return (ux-uy) == -(unsigned)(y-x);

    // if ux > uy
    // ux - uy > 0
    // uy - ux = UINT_MAX - (ux - uy) + 1

    // unary minus does a NOT (UINT_MAX - target) and adds 1
    // ux - uy = UINT_MAX - (UINT_MAX - (ux - uy) + 1) + 1
    // ux - uy = UINT_MAX - UINT_MAX + (ux - uy) - 1 + 1
    // ux - uy = ux - uy

    // if ux < uy
    // ux - uy = UINT_MAX - (uy - ux) + 1
    // uy - ux > 0

    // ux - uy = UINT_MAX - uy + ux + 1
    //            UINT_MAX + 1 = 0
    // ux - uy = ux - uy
}

int e(int x, int y) {
    return ((x >> 2) << 2) <= x;
    // always true. only affects lowest 2 bits.
    // lowest 2 bits have positive weight, so clearing them can only decrease or not change the number
}
