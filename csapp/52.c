/*
Later in this chapter we will start with a single function and generate many different variants that preserve the function’s behavior, but with different performance
characteristics. For three of these variants, we found that the run times (in clock
cycles) can be approximated by the following functions:

Version 1: 60 + 35n
Version 2: 136 + 4n
Version 3: 157 + 1.25n

For what values of n would each version be the fastest of the three? Remember
that n will always be an integer.
*/

#include <stdio.h>

int main(int argc, char const *argv[])
{
    double v1, v2, v3;
    for (double n = 1.0; n < 100.0; n++) {
        v1 = 60.0 + 35.0*n;
        v2 = 136.0 + 4.0*n;
        v3 = 157.0 + 1.25*n;
        printf("n = %2.0f : ", n);

        if (v1 <= v2 && v1 <= v3) {
            printf("Version 1\n");
        } else if (v2 <= v1 && v2 <= v3) {
            printf("Version 2\n");
        } else {
            printf("Version 3\n");
        }
    }
    return 0;
}

/*
n =  1 : Version 1
n =  2 : Version 1
n =  3 : Version 2
n =  4 : Version 2
n =  5 : Version 2
n =  6 : Version 2
n =  7 : Version 2
n =  8 : Version 3
n =  9 : Version 3
...
n = 99 : Version 3
*/
