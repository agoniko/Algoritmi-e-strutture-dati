#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getC(int a[], int size)
{
    int *p = malloc(size * sizeof(int));
    p[0] = a[0];
    for (int j = 1; j < size; j++)
    {
        if ((a[j - 1] % 2 == 0 && a[j] % 2 == 0) || p[j - 1] < 0)
        {
            p[j] = a[j];
        }
        else
        {
            p[j] = p[j - 1] + a[j];
        }
    }
    int sommaMax = p[0];
    for (int i = 0; i < size; i++)
    {
        if (sommaMax < p[i])
        {
            sommaMax = p[i];
        }
    }
    return sommaMax;
}

int *getSub(int c[], int v[], int max, int size)
{
    int index;
    for (int i = 0; i < size; i++)
    {
        if (c[i] == max)
        {
            index = i;
            break;
        }
    }
    int somma = max;
    int *sub = malloc(sizeof(int) * size);
    while (somma != 0)
    {
        somma -= v[index];
        sub[index] = v[index];
        index--;
    }
    return sub;
}

void stampa(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int v[] = {-1, 2, 5, 4, 2, 3, -6, 7, -6, 3, 2, -2, 1, 4, -1, 4, 3, -4};
    int size = sizeof(v) / sizeof(int);
    stampa(v, size);
}