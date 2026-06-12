#include <stdarg.h>
#include <stdio.h>

void minscanf(char *fmt, ...);

int main(int argc, char const *argv[])
{
    int i1, i2, i3;
    minscanf("%i %i %i", &i1, &i2, &i3);
    printf("%i %i %i", i1, i2, i3);
    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    int * ipointer;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            continue;
        }
        switch (*++p) {
            case 'i':
                ipointer = va_arg(ap, int *);
                scanf("%i", ipointer);
                break;
        }
    }
    va_end(ap);
}
