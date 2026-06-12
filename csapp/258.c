#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian();

int main(int argc, char const *argv[])
{
    int result = is_little_endian();

    if (result == 0) {
        printf("Big endian\n");
    } else if (result == 1) {
        printf("Little endian\n");
    } else {
        printf("broken\n");
    };

    return 0;
}

int is_little_endian() {
    int test = 1;
    byte_pointer first_byte = (byte_pointer) &test;
    return (int) *first_byte;
}
