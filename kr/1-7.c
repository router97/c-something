#include <stdio.h>

int main(int argc, char const *argv[])
{
    int c;

    while ((c = getchar()) != EOF) {
        putchar(c);
    }
    printf("%x", c);

    return 0;
}
