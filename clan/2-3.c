#include <stdio.h>
#include <string.h>

int htoi(char[]);

int main(int argc, char const *argv[])
{
    char* input;
    int result;

    printf("%16s   %16s\n", "HEX", "INT");

    input = "ff";
    result = htoi(input);
    printf("%16s : %16d\n", input, result);

    input = "ffff";
    result = htoi(input);
    printf("%16s : %16d\n", input, result);

    return 0;
}

int htoi(char s[]) 
{
    int length = strlen(s);
    int i;
    int result = 0;
    int multiplier = 1;
    
    for (i = length-1; i >= 0; i--) {
        
        switch (s[i])
        {
            case 'f':
                result += 15 * multiplier;
                break;
            
            case 'e':
                result += 14 * multiplier;
                break;
            
            case 'd':
                result += 13 * multiplier;
                break;
            
            case 'c':
                result += 12 * multiplier;
                break;
            
            case 'b':
                result += 11 * multiplier;
                break;
            
            case 'a':
                result += 10 * multiplier;
                break;
            
            case '9':
                result += 9 * multiplier;
                break;
            
            case '8':
                result += 8 * multiplier;
                break;
            
            case '7':
                result += 7 * multiplier;
                break;

            case '6':
                result += 6 * multiplier;
                break;

            case '5':
                result += 5 * multiplier;
                break;

            case '4':
                result += 4 * multiplier;
                break;

            case '3':
                result += 3 * multiplier;
                break;

            case '2':
                result += 2 * multiplier;
                break;

            case '1':
                result += 1 * multiplier;
                break;
            
            default:
                break;
        }
        multiplier *= 16;
    }
    
    return result;
}
