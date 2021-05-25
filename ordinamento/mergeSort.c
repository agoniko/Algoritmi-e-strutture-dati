#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define N 20

void merge(int a[], int sx, int m, int dx);

void stampaTrattini(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d",a[i]);
        for (int j = 0; j < a[i]; j++)
        {
            printf("-");
        }
        printf("\n");
    }
    sleep(1);
}

void riempiRandom(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % 10;
    }
}

void riempiOrdine(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = i;
    }
}

void print(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
void scambia(int a[], int i, int j)
{
    int ap = a[i];
    a[i] = a[j];
    a[j] = ap;
    stampaTrattini(a,N);
}

/*
Questo algoritmo non lavora in loco poichè sfrutta un'array di supporto.
Nel caso peggiore vengono eseguiti n-1 confronti per ogni ciclo.
La complessità è logaritmica perchè le divisioni vengono sempre fatte un numero
logaritmico di volte per arrivare al caso base.
Complessità O(n*logn)
*/
void mergeSort(int a[], int sx, int dx)
{

    if (sx >= dx)
        return;
    int m = sx + ((dx - sx) / 2);
    mergeSort(a, sx, m);
    mergeSort(a, m + 1, dx);
    merge(a, sx, m, dx);
}

void merge(int a[], int sx, int m, int dx)
{
    int sizeb = m - sx + 1;
    int sizec = dx - m;
    int c[sizec];
    int b[sizeb];

    int contb = 0;
    int contc = 0;
    int conta = sx;

    for (int i = 0; i < sizeb; i++)
    {
        b[i] = a[sx + i];
    }
    for (int i = 0; i < sizec; i++)
    {
        c[i] = a[m + 1 + i];
    }
    while (contb < sizeb && contc < sizec)
    {
        if (b[contb] <= c[contc])
        {
            a[conta] = b[contb];
            contb++;
        }
        else
        {
            a[conta] = c[contc];
            contc++;
        }
        conta++;
    }
    while (contb < sizeb)
    {
        a[conta] = b[contb];
        contb++;
        conta++;
    }
    while (contc < sizec)
    {
        a[conta] = c[contc];
        contc++;
        conta++;
    }
}

/*int main()
{
    srand(time(0));
    int a[N];
    riempiRandom(a, N);
    print(a, N);
    mergeSort(a, 0, N - 1);
    print(a, N);
}*/