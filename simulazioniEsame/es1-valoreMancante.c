#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ricercaBinaria(int *a, int sx, int dx)
{
    if (dx - sx == 1)
        if (a[sx] == sx)
        {
            return sx + 1;
        }
        else
        {
            return sx;
        }
    int m = (sx + dx) / 2;
    if (a[m] == m)
    {
        return ricercaBinaria(a, m, dx);
    }
    else if (a[m] > m)
    {
        return ricercaBinaria(a, sx, m);
    }
    return m;
}

void riempi(int *a, int size)
{
    int cont = rand() % size;
    for (int i = 0; i < size; i++)
    {
        if (i >= cont)
        {
            a[i] = i + 1;
        }
        else
        {
            a[i] = i;
        }
    }
}

void stampa(int *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int *a = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("%d \n", ricercaBinaria(a, 0, n));
    return (0);
}