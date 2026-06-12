#include <stdio.h>

int int_shifts_are_arithmetic();

int main(int argc, char const *argv[])
{
    printf("%d", int_shifts_are_arithmetic());
    return 0;
}

int int_shifts_are_arithmetic() {
    return (-1 >> 1) == -1;
}
