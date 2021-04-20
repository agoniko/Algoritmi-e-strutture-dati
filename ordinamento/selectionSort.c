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
}

/*
Si chiama così
perchè ad ogni iterazione inserisce il valore nella prima parte che non esamina più,
ovvero nella parte già ordinata. Questo comporta che al passo k i valori da V[0] a
V[k] siano ordinati tra loro.
Ottimo con i vettori già ordinati O(n-1), pessimo con i vettori al contrario.
Complessita O(n*n)
Caso migliore: n-1 confronti
*/
void selectionSort(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (a[j] < a[i])
            {
                scambia(a, i, j);
            }
        }
    }
}

int main()
{
    srand(time(0));
    int a[N];
    riempiOrdine(a, N);
    print(a, N);
    selectionSort(a, N);
    print(a, N);
}