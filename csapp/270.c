#include <stdio.h>

int fits_bits(int x, int n);

int main(int argc, char const *argv[])
{
    printf("-129 -> %d, -128 -> %d", fits_bits(-129, 8), fits_bits(-128, 8));
    printf(", 0 -> %d", fits_bits(0, 8));
    printf(", 127 -> %d, 128 -> %d\n", fits_bits(127, 8), fits_bits(128, 8));
    return 0;
}

int fits_bits(int x, int n) {
    int result;
    int w = sizeof(int)<<3;

    int shrunk_bits = x & (~0u << n-1);
    int signbit = x >> w-1;

    return (signbit & (~0u << n-1)) == shrunk_bits;
}