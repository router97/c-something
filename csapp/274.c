#include <assert.h>
#include <limits.h>

int tsub_ok(int x, int y);

int main(int argc, char const *argv[])
{
    assert(tsub_ok(0, INT_MAX) == 1);
    assert(tsub_ok(INT_MAX, 0) == 1);

    assert(tsub_ok(0, INT_MIN) == 0);
    assert(tsub_ok(INT_MIN, 0) == 1);

    assert(tsub_ok(INT_MAX, INT_MIN) == 0);
    assert(tsub_ok(INT_MIN, INT_MAX) == 0);

    assert(tsub_ok(INT_MIN, INT_MIN) == 1);
    assert(tsub_ok(INT_MAX, INT_MAX) == 1);

    return 0;
}

int tsub_ok(int x, int y) {
    long lx = (long)x;
    long ly = (long)y;
    long ldiff = lx - ly;
    int diff = (int)ldiff;
    return ldiff == diff;
}
