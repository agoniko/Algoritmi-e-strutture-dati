#include <stdio.h>

int main(int argc, char *argv[])
{
    char *p = argv[1];
    int i = 0;
    char *q;
    q = p;
    while (*q != '\0')
    {
        q++;
        i++;
    }
    q--;
    i /= 2;
    int isPalindroma = 1;
    while (i > 0)
    {
        if (*q != *p)
        {
            isPalindroma = 0;
            break;
        }
        i--;
        p++;
        q--;
    }
    if (isPalindroma == 1)
    {
        printf("La parola inserita è palindroma\n");
    }
    else
    {
        printf("La parola inserita non è palindroma\n");
    }
}