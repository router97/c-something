#include <assert.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum);

int main(int argc, char const *argv[])
{
    assert(xbyte(0x54FF3183, 2) == 0xFFFFFFFF);
    assert(xbyte(0x54FF3183, 0) == 0xFFFFFF83);
    assert(xbyte(0x54FF3183, 3) == 0x00000054);
    assert(xbyte(0x54FF3183, 1) == 0x00000031);
    return 0;
}

int xbyte(packed_t word, int bytenum) {
    int most_has_byte = word << ((3 - bytenum) << 3);
    int least_has_byte = most_has_byte >> 24;
    return least_has_byte;
}
