#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heapLib.c"

#define N 100
#define K 4

void riempiArrayRandom(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = (rand() % 98) + 1;
    }
}

Pqueue merge(Pqueue i, Pqueue j, int Isize, int Jsize)
{
    Pqueue p = malloc(sizeof(Pqueue));
    p->heap = malloc((Isize + Jsize) * sizeof(Heap));
    p->size = Isize + Jsize;
    int *min;
}

int main()
{
    int size = N / K;
    srand(time(0));
    Pqueue p = malloc(sizeof(Pqueue));
    p->heap = malloc(N * sizeof(Heap));

    Pqueue lists[K];
    for (int i = 0; i < K; i++)
    {
        Item temp[size];
        riempiArrayRandom(temp, size);
        lists[i] = pqueue_sort(temp, 0, size);
    }
    p = merge(lists[0], lists[1], size, size);
    extractAllElements(lists[0]);
    extractAllElements(lists[1]);
    extractAllElements(p);
}