#include <stdio.h>

int any_odd_one(unsigned x);

int main(int argc, char const *argv[])
{
    return 0;
}

int any_odd_one(unsigned x) {
    return !!(x & 0xAAAAAAAAu);
}
