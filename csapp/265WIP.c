/*
Return 1 when x contains an odd number of 1s; 0 otherwise.
Assume w=32

Your function should follow the bit-level integer coding rules (page 164),
except that you may assume that data type int has w = 32 bits.

Your code should contain a total of at most 12 arithmetic, bitwise, and logical
operations.
*/
#include <stdio.h>
#include <assert.h>

int odd_ones(unsigned x);

int main(int argc, char const *argv[])
{
    assert(odd_ones(0x0) == 0);
    assert(odd_ones(0x1) == 1);
    assert(odd_ones(~0) == 0);
    assert(odd_ones(0xFF0F100F) == 1);
    return 0;
}

int odd_ones(unsigned x) {
    return 0;
}
