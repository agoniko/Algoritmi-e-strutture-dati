#include <stdio.h>

#define LENGTH 100

int main(void)
{
    int a[LENGTH];
    int *p;

    for (p = a; p < a + LENGTH; p++)
    {
        scanf("%d", p);
        if (*p == 0)
            break;
    }

    while (--p >= a)
        printf("%d ", *p);

    printf("\n");
    return 0;
}