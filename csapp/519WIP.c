/*
In Problem 5.12, we were able to reduce the CPE for the prefix-sum computation
to 3.00, limited by the latency of floating-point addition on this machine. Simple
loop unrolling does not improve things.

Using a combination of loop unrolling and reassociation, write code for a
prefix sum that achieves a CPE less than the latency of floating-point addition
on your machine. Doing this requires actually increasing the number of additions
performed. For example, our version with two-way unrolling requires three additions per iteration, 
while our version with four-way unrolling requires five. Our
best implementation achieves a CPE of 1.67 on our reference machine.

Determine how the throughput and latency limits of your machine limit the
minimum CPE you can achieve for the prefix-sum operation.
*/
#include <assert.h>

void psum1(float a[], float p[], long n);
void psum5a(float a[], float p[], long n);

int main(int argc, char const *argv[])
{
    return 0;
}

/* p[0] = a[0] */
/* p[i] = p[i−1] + a[i], 1 <= i < n */
void psum1(float a[], float p[], long n)
{
    long i;
    p[0] = a[0];
    for (i = 1; i < n; i++)
        p[i] = p[i-1] + a[i];
}

void psum5a(float a[], float p[], long n)
{
    long i;
    float acc = 0.0f;
    float ta0, t12, t34, ta01, ta012, t1234, ta0123, ta01234;
    float a0, a1, a2, a3, a4;

    for (i = 0; i + 4 < n; i += 5) {
        a0 = a[i]; a1 = a[i+1];
        a2 = a[i+2]; a3 = a[i+3];
        a4 = a[i+4];

        // ###
        ta0     = acc + a0;
        t12     = a1 + a2;
        t34     = a3 + a4;
        // ###

        // ###
        ta01    = ta0 + a1;
        ta012   = t12 + ta0;
        t1234   = t12 + t34;
        // ###

        // ###
        // -
        ta0123  = ta012 + a3;
        ta01234 = ta0 + t1234;
        // ###

        p[i] = ta0;
        p[i+1] = ta01;
        p[i+2] = ta012;
        p[i+3] = ta0123;
        p[i+4] = ta01234;

        acc = ta01234;
    }

    for (; i < n; i++) {
        acc += a[i];
        p[i] = acc;
    }
}

/*
  │        │        │        │        │        │        │        │        │        │        │        │  
  │   0    │   1    │   2    │   3    │   4    │   5    │   6    │   7    │   8    │   9    │   10   │  
  ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼──
  │   a0   │   a0   │   a0   │  a01   │  a01   │  a01   │   -    │  -     │   -    │   -    │    -   │  
──┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼──
  │        │   12   │   12   │   12   │  a012  │  a012  │  a012  │ a0123  │ a0123  │ a0123  │        │  
──┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼──
  │        │        │   34   │   34   │   34   │  1234  │  1234  │  1234  │ a01234 │ a01234 │ a01234 │  
  │        │        ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤  
                             ▼                          ▼        ▼                          ▼        ▼  
                            a0                         a01     a012                       a0123   a01234
*/
