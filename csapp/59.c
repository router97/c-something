/*
The traditional implementation of the merge step of mergesort requires three
loops [98]:
*/

void merge(long src1[], long src2[], long dest[], long n) {
    long i1 = 0;
    long i2 = 0;
    long id = 0;
    while (i1 < n && i2 < n) {
        if (src1[i1] < src2[i2])
            dest[id++] = src1[i1++];
        else
            dest[id++] = src2[i2++];
    }
    while (i1 < n)
        dest[id++] = src1[i1++];
    while (i2 < n)
        dest[id++] = src2[i2++];
}

/*
The branches caused by comparing variables i1 and i2 to n have good prediction
performance—the only mispredictions occur when they first become false. The
comparison between values src1[i1] and src2[i2] (line 6), on the other hand,
is highly unpredictable for typical data. This comparison controls a conditional
branch, yielding a CPE (where the number of elements is 2n) of around 15.0 when
run on random data.

Rewrite the code so that the effect of the conditional statement in the first
loop (lines 6-9) can be implemented with a conditional move.
*/

void merge(long src1[], long src2[], long dest[], long n) {
    long i1 = 0;
    long i2 = 0;
    long id = 0;
    while (i1 < n && i2 < n) {
        long val1 = src1[i1]; long val2 = src2[i2];
        long cnd = val1 < val2;
        dest[id++] = cnd ? val1 : val2;
        i1 += cnd;
        i2 += 1-cnd;
    }
    while (i1 < n)
        dest[id++] = src1[i1++];
    while (i2 < n)
        dest[id++] = src2[i2++];
}
