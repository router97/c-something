/*
Rewrite the code for psum1 (Figure 5.1) so that it does not need to repeatedly
retrieve the value of p[i] from memory. You do not need to use loop unrolling.
We measured the resulting code to have a CPE of 3.00, limited by the latency of
floating-point addition.
*/

/* Compute prefix sum of vector a */
void psum1(float a[], float p[], long n)
{
    long i;
    p[0] = a[0];
    for (i = 1; i < n; i++)
        p[i] = p[i-1] + a[i];
}



/* Compute prefix sum of vector a */
void psum1(float a[], float p[], long n)
{
    float acc = 0;
    for (long i = 0; i < n; i++) {
        acc += a[i];
        p[i] = acc;
    }
}
