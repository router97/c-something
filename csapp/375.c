/*
ISO C99 includes extensions to support complex numbers. Any floating-point type
can be modified with the keyword complex. Here are some sample functions that
work with complex data and that call some of the associated library functions:
*/

#include <complex.h>

double c_imag(double complex x) {
    return cimag(x);
}

double c_real(double complex x) {
    return creal(x);
}

double complex c_sub(double complex x, double complex y) {
    return x - y;
}

/*
When compiled, gcc generates the following assembly code for these functions:

double c_imag(double complex x)
xmm0 = real x
xmm1 = imag x

c_imag:
    movapd %xmm1, %xmm0
    ret


double c_real(double complex x)
xmm0 = real x
xmm1 = imag x

c_real:
    rep; ret


double complex c_sub(double complex x, double complex y)
xmm0 = real x
xmm1 = imag x
xmm2 = real y
xmm3 = imag y

c_sub:
    subsd %xmm2, %xmm0 // real x -= real y
    subsd %xmm3, %xmm1 // imag x -= imag y
    ret


Based on these examples, determine the following:

A. How are complex arguments passed to a function?
if the real part is stored in xmm(X), the imaginary is stored in xmm(X+1)

B. How are complex values returned from a function?
real part in xmm0, imaginary part is xmm1
*/
