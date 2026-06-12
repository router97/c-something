#include <stdio.h>

int a(int x);
int b(int x);
int c(int x);
int d(int x);


int main(int argc, char const *argv[])
{
    return 0;
}

int a(int x) {
    return x && 1;
}
int b(int x) {
    return !!(~x);
}
int c(int x) {
    int least_byte = x & 0x000000FF;
    return least_byte && 1;
}
int d(int x) {
    int most_byte = x & 0xFF000000;
    return !!(~(most_byte | 0x00FFFFFF));
}