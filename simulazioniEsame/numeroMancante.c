#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

void riempiArray(int a[], int size)
{
    int mancante = rand() % size;
    int cont = 0;
    int num = 0;
    while (cont < size)
    {
        if (num == mancante)
        {
            num++;
        }
        a[cont] = num;
        cont++;
        num++;
    }
}

void stampa(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// dx è ultimo indice
int valoreMancante(int a[], int sx, int dx)
{
    int m = sx + (dx - sx) / 2;
    printf("m: %d\n", m);
    if (m == 0)
    {
        return 0;
    }
    if (m == N - 1)
    {
        return N;
    }
    if (m < a[m])
    {
        if (m - 1 == a[m - 1])
        {
            return m;
        }
        else
        {
            return valoreMancante(a, sx, m);
        }
    }
    else
    {
        if (m + 1 != a[m + 1])
        {
            return m + 1;
        }
        return valoreMancante(a, m + 1, dx);
    }
}

int main(void)
{
    srand(time(0));
    int a[N];
    riempiArray(a, N);
    stampa(a, N);
    int manca = valoreMancante(a, 0, N - 1);
    printf("%d\n", manca);
    return (0);
}