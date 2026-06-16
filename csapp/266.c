#include <stdio.h>
#include <assert.h>

int leftmost_one(unsigned x);

int main(int argc, char const *argv[])
{
    printf("0xFF00 -> 0x%X, 0x6600 -> 0x%X\n", leftmost_one(0xFF00), leftmost_one(0x6600));
    assert(leftmost_one(0xFF00) == 0x8000);
    assert(leftmost_one(0x6600) == 0x4000);
    assert(leftmost_one(0x0000) == 0x0000);
    return 0;
}

int leftmost_one(unsigned x) {
    unsigned result = x;

    result = result | (result >> 16);
    result = result | (result >> 8);
    result = result | (result >> 4);
    result = result | (result >> 2);
    result = result | (result >> 1);
    
    unsigned resultrs = result >> 1;
    result = result ^ resultrs;
    
    return result;
}