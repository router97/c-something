#include <stdio.h>

int main(int argc, char const *argv[])
{
    int c;
    c = 0;

    while ((c = getchar()) != EOF) {
        switch (c)
        {   
            case '\t':
                c = 't';
                putchar('\\');
                break;
            
            case '\b':
                c = 'b';
                putchar('\\');
                break;
            
            case '\\':
                c = '\\';
                putchar('\\');
                break;
            
            default:
                break;
        }
        putchar(c);
    }

    return 0;
}
