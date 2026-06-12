#include <stdarg.h>
#include <stdio.h>

void minprintf(char*, ...);

int main(int argc, char const *argv[])
{
    minprintf("value: %d, %%, %c, %s, %o", 3, 0x32, "string", 10);
    return 0;
}

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    char cval;
    int oval, xval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'o':
                oval = va_arg(ap, int);
                printf("%o", oval);
                break;
            case 'x':
                xval = va_arg(ap, int);
                printf("%x", xval);
                break;
            case 'X':
                xval = va_arg(ap, int);
                printf("%X", xval);
                break;
            case 'u':
                ival = va_arg(ap, int);
                printf("%u", ival);
                break;
            case 'c':
                cval = va_arg(ap, int);
                putchar(cval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++) {
                    putchar(*sval);
                }
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 'e':
                dval = va_arg(ap, double);
                printf("%e", dval);
                break;
            case 'E':
                dval = va_arg(ap, double);
                printf("%E", dval);
                break;
            case 'g':
                dval = va_arg(ap, double);
                printf("%g", dval);
                break;
            case 'G':
                dval = va_arg(ap, double);
                printf("%G", dval);
                break;
            case '%':
                putchar('%');
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}
