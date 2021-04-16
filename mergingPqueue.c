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
        a[i] = rand() % 100;
    }
}

int main()
{

    srand(time(0));
    Pqueue p = malloc(sizeof(Pqueue));
    p->heap = malloc(N*sizeof(Heap));

    Pqueue lists[K];
    for(int i = 0; i<K;i++){
        Item temp[N/K];
        riempiArrayRandom(temp,N/K);
        lists[i] = pqueue_sort(temp,0,N/K);
    }

}