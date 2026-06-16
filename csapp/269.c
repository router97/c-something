#include <stdio.h>

unsigned rotate_left(unsigned x, int n);

int main(int argc, char const *argv[])
{
    printf("x = 0x12345678\n");
    printf("n=4 -> 0x%x, n=20 -> 0x%x\n", rotate_left(0x12345678, 4), rotate_left(0x12345678, 20));
    printf("n=0 -> 0x%x, n=28 -> 0x%x", rotate_left(0x12345678, 0), rotate_left(0x12345678, 28));
    return 0;
}

unsigned rotate_left(unsigned x, int n) {
    unsigned result;
    unsigned lsh = x << n;
    unsigned mask = x >> (32-n);

    result = lsh | mask;
    return result;
}
