/*
// Consider the following functions:

long min(long x, long y) { return x < y ? x : y; }
long max(long x, long y) { return x < y ? y : x; }
void incr(long *xp, long v) { *xp += v; }
long square(long x) { return x*x; }
*/

#include <stdio.h>

long minc, maxc, incrc, squarec;

long min(long x, long y) { 
    minc++;
    return x < y ? x : y; 
}
long max(long x, long y) { 
    maxc++;
    return x < y ? y : x; 
}
void incr(long *xp, long v) { 
    incrc++;
    *xp += v; 
}
long square(long x) { 
    squarec++;
    return x*x; 
}

int main(int argc, char const *argv[])
{
    long i, x, y, t;
    x = 10;
    y = 100;
    t = 0;

    /*
    // The following three code fragments call these functions:

    // A
    for (i = min(x, y); i < max(x, y); incr(&i, 1))
        t += square(i);

    // B
    for (i = max(x, y) - 1; i >= min(x, y); incr(&i, -1))
        t += square(i);

    // C
    long low = min(x, y);
    long high = max(x, y);
    for (i = low; i < high; incr(&i, 1))
        t += square(i);
    */

    printf("min: %3d\nmax: %3d\nincr: %3d\nsquare: %3d\n", minc, maxc, incrc, squarec);

    return 0;
}

/*
Assume x equals 10 and y equals 100. Fill in the following table indicating the
number of times each of the four functions is called in code fragments A-C:

| Code | min | max | incr | square |
|------|-----|-----|------|--------|
| A    | 1   | 91  | 90   | 90     |
| B    | 91  | 1   | 90   | 90     |
| C    | 1   | 1   | 90   | 90     |
*/
