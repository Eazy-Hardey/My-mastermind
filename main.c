#include "mastermind.h"
#include <stdio.h>

int custom_atoi_read(const char *string)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    while (string[i] == ' ' || string[i] == '\t' || string[i] == '\n') i=i+1;

    if (string[i] == '-')
    {
        sign = -1;
        i=i+1;
    }
    else if (string[i] == '+')
    {
        i=i+1;
    }

    while (string[i] >= '0' && string[i] <= '9')
    {
        result = result * 10 + (string[i] - '0');
        i++;
    }

    return sign * result;
}

int main(int argument, char *alternate[])
{
    char *code = NULL;
    int attempts = 10;
    if (argument > 1)
    {
        for (int i = 1; i < argument; i++)
        {
            if (alternate[i][0] == '-' && alternate[i][1] == 'c')
            {
                code = alternate[i + 1];
            }
            else if (alternate[i][0] == '-' && alternate[i][1] == 't')
            {
                attempts = custom_atoi_read(alternate[i + 1]);
            }
        }
    }

    play_mastermind(code, attempts);

    return 0;
}


