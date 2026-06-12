#include <stdio.h>

int main(int argc, char const *argv[])
{
    int c, nl, tab, blank;
    nl = tab = blank = 0;

    while ((c = getchar()) != EOF) {
        switch (c)
        {
            case '\n':
                ++nl;
                break;
            
            case '\t':
                ++tab;
                break;
            
            case ' ':
                ++blank;
                break;
            
            default:
                break;
        }
    }
    printf("NEWLINES: %d\n", nl);
    printf("TABS: %d\n", tab);
    printf("BLANKS: %d\n", blank);

    return 0;
}
