#include <stdio.h>

int main (void)
{
    int num1, num2, result;
    char action;
    result = 0;

    scanf("%d%c%d", &num1, &action, &num2);

    switch (action)
    {
    case '+':
        result = num1 + num2;
        break;
    
    case '-':
        result = num1 - num2;
        break;
    
    case '*':
        result = num1 * num2;
        break;
    
    case '/':
        if (num2 != 0) {
            result = num1 / num2;
        } else {
            printf("Cannot divide by zero.");
        }
        break;
    
    case '%':
        if (num2 != 0) {
            result = num1 % num2;
        } else {
            printf("Cannot divide by zero.");
        }
        break;
    
    default:
        printf("Unknown action.");
    }

    printf("Result: %d", result);
    
    return 0;
}
