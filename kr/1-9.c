#include <stdio.h>

int main(int argc, char const *argv[])
{
    int c, consec_blanks;
    c = consec_blanks = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++consec_blanks;
        } else {
            consec_blanks = 0;
        }

        if (consec_blanks <= 1) {
            putchar(c);
        }
    }

    return 0;
}
