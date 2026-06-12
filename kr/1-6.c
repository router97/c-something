#include <stdio.h>

int main(int argc, char const *argv[])
{
    int c;
    int expr;

    while (expr=((c = getchar()) != EOF)) {
        printf("EXPRESSION VALUE: 0x%x\n", expr);
    }
    printf("EXPRESSION VALUE: 0x%x\n", expr);

    return 0;
}
