/*
We are running programs on a machine where values of type int have a 32-
bit two’s-complement representation. Values of type float use the 32-bit IEEE
format, and values of type double use the 64-bit IEEE format.
We generate arbitrary integer values x, y, and z, and convert them to values
of type double as follows:

// Create some arbitrary values
int x = random();
int y = random();
int z = random();

// Convert to double
double dx = (double) x;
double dy = (double) y;
double dz = (double) z;

For each of the following C expressions, you are to indicate whether or
not the expression always yields 1. If it always yields 1, describe the underlying
mathematical principles. Otherwise, give an example of arguments that make
it yield 0. Note that you cannot use an IA32 machine running gcc to test your
answers, since it would use the 80-bit extended-precision representation for both
float and double.

A. (float) x == (float) dx
B. dx - dy == (double) (x-y)
C. (dx + dy) + dz == dx + (dy + dz)
D. (dx * dy) * dz == dx * (dy * dz)
E. dx / dx == dz / dz
*/
#include <limits.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
    // Create some arbitrary values
    int x = INT_MAX;
    int y = 1;
    int z = 1;

    // Convert to double
    double dx = (double) x;
    double dy = (double) y;
    double dz = (double) z;

    // A
    assert((float) x == (float) dx);
    // if x > largest accurate integer (after which only even values come):
    // with both x and dx representing the accurate value (32bits fit in double mantissa), they will both be equally
    // inacurrate using the same rounding

    // B
    // assert(dx - dy == (double) (x-y));
    // integer x-y can overflow, while dx - dy won't.

    // C
    assert((dx + dy) + dz == dx + (dy + dz));
    // none of these operations will ever overflow to int not fitting into 54 bits. So it will be accurate

    // D
    // assert((dx * dy) * dz == dx * (dy * dz));
    // if all values are INT_MAX, it will overflow past the point of accuracy.
    // so two roundings can happen, losing information

    // E
    // assert(dx / dx == dz / dz);
    // No, because of division by zero, comparisons with NaN are always 0


    return 0;
}

