#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define N 20

void stampaTrattini(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", a[i]);
        for (int j = 0; j < a[i]; j++)
        {
            printf("-");
        }
        printf("\n");
    }
    sleep(1);
}

void scambia(int a[], int i, int j)
{
    int ap = a[i];
    a[i] = a[j];
    a[j] = ap;
    stampaTrattini(a, N);
}


int partition(int a[], int p, int q)
{
    int i = p;
    int j = q;
    while (i <= j)
    {
        while (a[j] > a[p])
            j--;
        while (i <= j && a[i] <= a[p])
            i++;
        if (i < j)
        {
            scambia(a, i, j);
            i++;
            j--;
        }
    }
    scambia(a, j, p);
    return j;
}

void quickSort(int a[], int low, int high)
{
    if (high > low)
    {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

void riempiRandom(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % 20;
    }
}

void riempiOrdine(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = size - i;
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

int main()
{
    srand(time(0));
    int a[N];
    riempiOrdine(a, N);
    print(a, N);
    quickSort(a, 0, N - 1);
    print(a, N);
}