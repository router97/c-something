#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char c;

    if (argc < 2) {
        printf("Argument expected.\n");
        return 1;
    } else if (argc > 2) {
        printf("Too many arguments.\n");
        return 1;
    }

    if (strcmp(argv[1], "-l") == 0) {
        while ((c = getchar()) != EOF) {
            putchar(tolower(c));
        }
    } else if (strcmp(argv[1], "-u") == 0) {
        while ((c = getchar()) != EOF) {
            putchar(toupper(c));
        }
    } else {
        printf("Unknown argument.\n");
        return 1;
    }

    return 0;
}
