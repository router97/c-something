#include <ctype.h>
#include <stdio.h>

#define LONGEST_LINE 40

int main(int argc, char const *argv[])
{
    char c;
    int line_chars = 0;

    while ((c = getchar()) != EOF) {
        line_chars += 1;
        if ((!isgraph(c)) && (!isblank(c)) && (c != '\n')) {
            printf("<0x%x>", c);
            continue;
        }

        if (c == '\n') {
            line_chars = 0;
        } else if (line_chars >= LONGEST_LINE) {
            putchar('\n');
            line_chars = 0;
        }

        putchar(tolower(c));
    }       
    return 0;
}
