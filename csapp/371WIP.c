/*
Write a function good_echo that reads a line from standard input and writes it to
standard output. Your implementation should work for an input line of arbitrary
length. You may use the library function fgets, but you must make sure your
function works correctly even when the input line requires more space than you
have allocated for your buffer. Your code should also check for error conditions
and return when one is encountered. Refer to the definitions of the standard I/O
functions for documentation [45, 61].
*/
#include <stdio.h>

int good_echo();

int main(int argc, char const *argv[])
{
    good_echo();
    return 0;
}

int good_echo() {
    char buf[64];
    char* status;

    while (1) {
        status = fgets(buf, 64, stdin);
        if (!status) {
            break;
        }
        printf("%s", buf);
    }
    return 0;
}