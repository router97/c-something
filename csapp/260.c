#include <stdio.h>

unsigned replace_byte (unsigned x, int i, unsigned char b);

int main(int argc, char const *argv[])
{
    unsigned result1 = replace_byte(0x12345678, 2, 0xAB);
    unsigned result2 = replace_byte(0x12345678, 0, 0xAB);

    printf("%x\n%x\n", result1, result2);
    return 0;
}

unsigned replace_byte (unsigned x, int i, unsigned char b) {
    unsigned mask = ~(0xFFU << i*8);
    unsigned mask2 = (b) << i*8;
    unsigned result = (x & mask) | mask2;
    return result;
}
