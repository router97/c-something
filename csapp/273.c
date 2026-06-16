#include <stdio.h>
#include <assert.h>
#include <limits.h>

int saturating_add(int x, int y);

int main(int argc, char const *argv[])
{
    printf("0x%08X\n", saturating_add(0x7FFFFF00u, 0x0000FFFFu));
    printf("0x%08X\n", saturating_add(10, -12));
    printf("0x%08X\n", saturating_add(0x80002000u, 0x80000000u));

    assert(saturating_add(0x7FFFFF00u, 0x0000FFFFu) == INT_MAX);
    assert(saturating_add(10, -12) == -2);
    assert(saturating_add(0x80002000u, 0x80000000u) == INT_MIN);

    return 0;
}

int saturating_add(int x, int y) {
    int result = x + y;
    int saturated_result;
    int w = sizeof(int)<<3;

    int x_sign = x >> w-1;
    int y_sign = y >> w-1;
    int result_sign = result >> w-1;

    int same_sign_op = ~(x_sign ^ y_sign);
    int overflow_happened = same_sign_op & (result_sign ^ y_sign);

    saturated_result = (x_sign & INT_MIN) | (~x_sign & INT_MAX);

    return (overflow_happened & saturated_result) | (~overflow_happened & result);
}