#include <stdio.h>

int lower_one_mask(int n);

int main(int argc, char const *argv[])
{
    printf("n = 1 --> 0x%x\n", lower_one_mask(1));
    printf("n = 6 --> 0x%x\n", lower_one_mask(6));
    printf("n = 17 --> 0x%x\n", lower_one_mask(17));
    printf("n = 32 --> 0x%x\n", lower_one_mask(32));
    return 0;
}

int lower_one_mask(int n) {
    return 0xFFFFFFFF >> (32-n);
}
