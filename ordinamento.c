#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 20
void selectionsort(int a[], int n);
void mergesort(int a[], int sx, int dx);
void merge(int a[], int sx, int m, int dx);

void stampa(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void riempiArrayRandom(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }
}

int main()
{
    srand(time(0));
    int a[size];
    riempiArrayRandom(a, size);
    stampa(a, size);
    mergesort(a, 0, size);
    stampa(a, size);
}

void selectionsort(int a[], int n)
{
    if (n > 1)
    {
        int max = a[0];
        int index = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i] > max)
            {
                max = a[i];
                index = i;
            }
        }
        int ap = a[n - 1];
        a[n - 1] = max;
        a[index] = ap;
        selectionsort(a, n - 1);
    }
}

void mergesort(int a[], int sx, int dx)
{
    if (sx >= dx)
        return;
    int m = sx + (dx - sx) / 2;
    mergesort(a, sx, m);
    mergesort(a, m + 1, dx);
    merge(a, sx, m, dx);
}

void merge(int a[], int sx, int m, int dx)
{
    int dim1 = m + 1 - sx, dim2 = dx - m;
    int k[dim1], j[dim2];
    for (int i = 0; i < dim1; i++)
    {
        k[i] = a[sx + i];
    }
    for (int i = 0; i < dim2; i++)
    {
        j[i] = a[m + 1 + i];
    }

    int i1 = 0, i2 = 0;
    int cont = sx;
    while (i1 < dim1 && i2 < dim2)
    {
        if (k[i1] <= j[i2])
        {
            a[cont] = k[i1];
            i1++;
        }
        else
        {
            a[cont] = j[i2];
            i2++;
        }
        cont++;
    }

    while(i1 < dim1){
        a[cont] = k[i1];
        i1++;
        cont++;
    }

    while(i2<dim2){
        a[cont] = j[i2];
        i2++;
        cont++;
    }

}