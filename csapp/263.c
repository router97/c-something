#include <stdio.h>

unsigned srl(unsigned x, int k);
int sra(int x, int k);

int main(int argc, char const *argv[])
{
    return 0;
}

unsigned srl(unsigned x, int k) {
    if (k == 0) {
        return x;
    }
    int w = 8*sizeof(int);
    unsigned xsra = (int) x >> k; /* Perform shift arithmetically */
    unsigned mask = ~(0);
    mask = mask << (w-k);
    mask = ~mask;
    return xsra & mask;
}

int sra(int x, int k) {
    if (k == 0) {
        return x;
    }
    int w = 8*sizeof(int);
    int xsrl = (unsigned) x >> k; /* Perform shift logically */
    if (x >= 0) {
        return xsrl;
    }
    unsigned mask = ~0;
    mask = mask << (w-k);
    return xsrl | mask;
}
