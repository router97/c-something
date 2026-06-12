#include <stdio.h>
#include <math.h>


double calculate_distance(int, int, int, int);


int main(int argc, char const *argv[])
{   
    int x1, y1, x2, y2;
    double result;

    printf("p1x: ");
    scanf("%d", &x1);
    printf("p1y: ");
    scanf("%d", &y1);

    printf("p2x: ");
    scanf("%d", &x2);
    printf("p2y: ");
    scanf("%d", &y2);

    result = calculate_distance(x1, y1, x2, y2);

    printf("result: %f", result);

    printf("\n");

    return 0;
}


double calculate_distance(int x1, int y1, int x2, int y2)
{
    int pifagor1, pifagor2;
    double result;

    pifagor1 = x1 - x2;
    pifagor1 *= pifagor1;

    pifagor2 = y1 - y2;
    pifagor2 *= pifagor2;

    result = pifagor1 + pifagor2;
    result = sqrt(result);
    return result;
}
