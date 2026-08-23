/*
We considered the task of polynomial evaluation in Practice Problems 5.5 and 5.6,
with both a direct evaluation and an evaluation by Horner's method. Try to write
faster versions of the function using the optimization techniques we have explored,
including loop unrolling, parallel accumulation, and reassociation. You will find
many different ways of mixing together Horner's scheme and direct evaluation
with these optimization techniques.

Ideally, you should be able to reach a CPE close to the throughput limit of
your machine. Our best version achieves a CPE of 1.07 on our reference machine.
*/
#include <assert.h>

double poly(double a[], double x, long degree);
double poly4x4(double a[], double x, long degree);

int main(int argc, char const *argv[])
{
    double a[10] = {1.0, 3.0, 5.0, 1.0, 294.0, 29142.0, 29142.0, 29142.0, 29142.0, 29142.0};
    for (long d = 0; d < 10; d++) {
        double result1 = poly(a, 4.0, 4);
        double result2 = poly4x4(a, 4.0, 4);
        assert(result1 == result2);
    }
    return 0;
}

/* a[0] + a[1]*x + a[2]*x^2 + ... + a[n]*x^n */
double poly(double a[], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr = x; /* Equals x^i at start of loop */
    for (i = 1; i <= degree; i++) {
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}

/* a[0] + a[1]*x + a[2]*x^2 + ... + a[n]*x^n */
double poly4x4(double a[], double x, long degree)
{
    long i = 0;

    double result0 = 0;
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double xpwr0 = 1;
    double xpwr1 = x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;

    double x4 = xpwr3 * x;
    long limit = degree - 4 + 1;

    for (; i <= limit; i += 4) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        result3 += a[i+3] * xpwr3;

        xpwr0 *= x4;
        xpwr1 *= x4;
        xpwr2 *= x4;
        xpwr3 *= x4;
    }
    result0 += result1 + result2 + result3;

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }
    return result0;
}
