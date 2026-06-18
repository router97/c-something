#include <assert.h>

int mul3div4(int x);

int main(int argc, char const *argv[])
{
    assert(mul3div4(4) == 3);
    assert(mul3div4(12) == 9);
    assert(mul3div4(0) == 0);
    return 0;
}

int mul3div4(int x) {
    int w = sizeof(int) << 3;
    int prod = (x << 1) + x;
    int prods = prod >> (w-1);
    int bias = 3 & prods;
    int quot = (prod + bias) >> 2;
    return quot;
}
