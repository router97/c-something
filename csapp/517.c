/*
The library function memset has the following prototype:

void *memset(void *s, int c, size_t n);
This function fills n bytes of the memory area starting at s with copies of the loworder byte of c. 
For example, it can be used to zero out a region of memory by
giving argument 0 for c, but other values are possible.

The following is a straightforward implementation of memset:
*/

/* Basic implementation of memset */
/*
void *basic_memset(void *s, int c, size_t n)
{
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    return s;
}
*/

/*
Implement a more efficient version of the function by using a word of data
type unsigned long to pack eight copies of c, and then step through the region
using word-level writes. You might find it helpful to do additional loop unrolling
as well. On our reference machine, we were able to reduce the CPE from 1.00 for
the straightforward implementation to 0.127. That is, the program is able to write
8 bytes every clock cycle.

Here are some additional guidelines. To ensure portability, let K denote the
value of sizeof(unsigned long) for the machine on which you run your program.

. You may not call any library functions.

. Your code should work for arbitrary values of n, including when it is not a
multiple of K. You can do this in a manner similar to the way we finish the
last few iterations with loop unrolling.

. You should write your code so that it will compile and run correctly on any
machine regardless of the value of K. Make use of the operation sizeof to
do this.

. On some machines, unaligned writes can be much slower than aligned ones.
(On some non-x86 machines, they can even cause segmentation faults.) Write
your code so that it starts with byte-level writes until the destination address
is a multiple of K, then do word-level writes, and then (if necessary) finish
with byte-level writes.

. Beware of the case where cnt is small enough that the upper bounds on
some of the loops become negative. With expressions involving the sizeof
operator, the testing may be performed with unsigned arithmetic. (See Section 2.2.8 and Problem 2.72.)
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

void *basic_memset(void *s, int c, size_t n)
{
    size_t cnt = 0;
    unsigned char *schar = s;
    unsigned char cc = (unsigned char) c;
    size_t K = sizeof(unsigned long);
    
    unsigned long nc = cc;
    for (size_t temp = K-1; temp != 0; temp--) {
        nc |= nc << 8;
    }
    
    for (; ((uintptr_t) schar % K) && cnt < n; cnt++) {
        *schar++ = cc;
    }
    
    size_t limit = n - K + 1;
    if ((n - cnt) < K) {
        limit = 0;
    }

    unsigned long *slong = (unsigned long *)schar;
    for (; cnt < limit; cnt+=K) {
        *slong++ = nc;
    }
    
    schar = (unsigned char*)slong;
    for (; cnt < n; cnt++) {
        *schar++ = (unsigned char) c;
    }
    return s;
}

int main(int argc, char const *argv[])
{
    size_t array_size = sizeof(int)*44;
    int *array = (int*)malloc(array_size);
    array = (int *)((unsigned long)array);

    memset(array, 0xffu, array_size);
    basic_memset(array, 0, 1);
    assert(array[0] == 0xFFFFFF00);
    assert(array[1] == 0xFFFFFFFF);
    assert(array[2] == 0xFFFFFFFF);
    assert(array[3] == 0xFFFFFFFF);
    assert(array[4] == 0xFFFFFFFF);


    memset(array, 0xffu, array_size);
    basic_memset(array, 0, 2);
    assert(array[0] == 0xFFFF0000);
    assert(array[1] == 0xFFFFFFFF);
    assert(array[2] == 0xFFFFFFFF);
    assert(array[3] == 0xFFFFFFFF);
    assert(array[4] == 0xFFFFFFFF);

    memset(array, 0xffu, array_size);
    basic_memset(array, 0, 3);
    assert(array[0] == 0xFF000000);
    assert(array[1] == 0xFFFFFFFF);
    assert(array[2] == 0xFFFFFFFF);
    assert(array[3] == 0xFFFFFFFF);
    assert(array[4] == 0xFFFFFFFF);

    memset(array, 0xffu, array_size);
    basic_memset(array, 0, 4);
    assert(array[0] == 0x00000000);
    assert(array[1] == 0xFFFFFFFF);
    assert(array[2] == 0xFFFFFFFF);
    assert(array[3] == 0xFFFFFFFF);
    assert(array[4] == 0xFFFFFFFF);

    memset(array, 0xffu, array_size);
    basic_memset(array, 0, 7);
    assert(array[0] == 0x00000000);
    assert(array[1] == 0xFF000000);
    assert(array[2] == 0xFFFFFFFF);
    assert(array[3] == 0xFFFFFFFF);
    assert(array[4] == 0xFFFFFFFF);

    memset(array, 0xffu, array_size);
    basic_memset(array, 0, 8);
    assert(array[0] == 0x00000000);
    assert(array[1] == 0x00000000);
    assert(array[2] == 0xFFFFFFFF);
    assert(array[3] == 0xFFFFFFFF);
    assert(array[4] == 0xFFFFFFFF);

    memset(array, 0xffu, array_size);
    basic_memset(array, 0, 9);
    assert(array[0] == 0x00000000);
    assert(array[1] == 0x00000000);
    assert(array[2] == 0xFFFFFF00);
    assert(array[3] == 0xFFFFFFFF);
    assert(array[4] == 0xFFFFFFFF);

    memset(array, 0xffu, array_size);
    basic_memset(array, 0, 20);
    assert(array[0] == 0x00000000);
    assert(array[1] == 0x00000000);
    assert(array[2] == 0x00000000);
    assert(array[3] == 0x00000000);
    assert(array[4] == 0x00000000);
    assert(array[5] == 0xFFFFFFFF);

    return 0;
}
