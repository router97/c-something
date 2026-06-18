#include <assert.h>

int odd_ones(unsigned x);
int odd_ones_byte(unsigned char x);
int odd_ones_unoptimized(unsigned x);

int main(int argc, char const *argv[])
{
    for (unsigned counter = 0; counter != ~0; counter++) {
        assert(odd_ones(counter) == odd_ones_unoptimized(counter));
    }
    assert(odd_ones(~0) == odd_ones_unoptimized(~0));
    
    return 0;
}

int odd_ones(unsigned x) {
    unsigned parity = x;
    parity = parity ^ (parity >> 16);
    parity = parity ^ (parity >> 8);
    parity = parity ^ (parity >> 4);
    parity = parity ^ (parity >> 2);
    parity = parity ^ (parity >> 1);
    parity = parity & 0x1u;
    return parity;
}

int odd_ones_unoptimized(unsigned x) {
    unsigned char b1 = x >> 24;
    unsigned char b2 = x >> 16;
    unsigned char b3 = x >> 8;
    unsigned char b4 = x;
    return !!((odd_ones_byte(b1) + odd_ones_byte(b2) + odd_ones_byte(b3) + odd_ones_byte(b4)) % 2);
}

int odd_ones_byte(unsigned char x) {
    int counter = 0;
    unsigned char current_bit;
    unsigned char bitmask;
    for (unsigned char i = 0; i < 8; i++) {
        bitmask = 1 << i;
        current_bit = x & bitmask;
        if (current_bit) {
            counter++;
        }
    }
    return !!(counter % 2);
}
