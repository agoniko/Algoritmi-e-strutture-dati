#include <stdio.h>
#include <stdlib.h>

int calcola(char c, char f)
{
    int i = 0;
    if (c > f)
    {
        i = c - f;
    }
    else
    {
        i = f - c;
    }
    return i+1;
}

int main()
{
    char c = 'b';
    char f = 'f';

    printf("%d\n", calcola(c,f));
}