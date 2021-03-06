#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 20

void riempiRandom(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % 100;
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
}

/*
Risulta il miglior algoritmo tra i 3 elementari nonostante a caso peggiore e
migliore sia uguale all'InsertionSort, però in molti casi generici si comporta
meglio ed è stato anche impostato/studiato meglio.
Complessità O(n*n)
Caso migliore: n-1 confronti
*/

void bubbleSort(int a[], int size)
{
    int scambiato = 1;
    while (scambiato == 1)
    {
        scambiato = 0;
        for (int i = 0; i < size - 1; i++)
        {
            if (a[i] > a[i + 1])
            {
                scambia(a, i, i + 1);
                scambiato = 1;
            }
        }
    }
}



int main()
{
    srand(time(0));
    int a[N];
    riempiRandom(a, N);
    print(a, N);
    bubbleSort(a, N);
    print(a, N);
}