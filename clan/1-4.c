#include <stdio.h>

int main(int argc, char const *argv[])
{
    float fahr, celsius;
    float lower, upper, step;

    lower = -17.8;
    upper = 148.9;
    step = 11.2;

    printf("%3s %6s\n", "FAH", "CEL");

    celsius = lower;
    while (celsius <= upper) {
        fahr = ((celsius * 9.0) / 5.0) + 32.0;
        printf("%3.0f %6.1f\n", fahr, celsius);
        celsius += step;
    }
    return 0;
}
