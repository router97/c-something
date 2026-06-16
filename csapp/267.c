#include <stdio.h>

int int_size_is_32();

int main(int argc, char const *argv[])
{
    printf("%d\n", int_size_is_32());
    return 0;
}

int int_size_is_32() {
    int test16 = 0x7FFF;
    int zero = 0x0;
    
    if ((test16 + 1) < zero) {
        return 0;
    }
    int test32 = 0x7FFFFFFF;

    if ((test32 + 1) < zero) {
        return 1;
    }
    return 0;
}

