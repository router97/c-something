#include <stdio.h>

float ftoc(float);

int main(int argc, char const *argv[])
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("%3s %6s\n", "FAH", "CEL");

    fahr = lower;
    while (fahr <= upper) {
        celsius = ftoc(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}

float ftoc(float fahr)
{
    return (5.0/9.0) * (fahr-32.0);
}
