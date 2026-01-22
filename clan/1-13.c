#include <stdio.h>

#define IN 1
#define OUT 0

int main(int argc, char const *argv[])
{
    int c, nl, nw, nc, state;
    int temp_length;
    int word_lengths[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int cur_index = -1;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;

        if (c == '\n') {
            ++nl;
        }

        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            cur_index += 1;
            word_lengths[cur_index] += 1;
            ++nw;
        } else {
            word_lengths[cur_index] += 1;
        }
    }

    int i, j;
    printf("\n");
    for (i = 0; i < 10; i++) {
        temp_length = word_lengths[i];
        printf("%d: ", i);
        for (j = temp_length; j > 0; j--) {
            printf("|");
        }
        printf("\n");
    }
    

    return 0;
}