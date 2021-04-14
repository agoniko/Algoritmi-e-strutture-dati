#include <stdio.h>
#include <stdlib.h>

typedef int Item;
typedef Item *Heap;

void swap(Heap h, int i, int j);
int father(int i);
int cmp(Item a, Item b);
void heapify_up(Heap h, int i);

struct pqueue
{
    Heap heap;
    int size, count;
} pqueue;

typedef struct pqueue *Pqueue;

void stampa(Heap h, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d: %d\n", i, h[i]);
    }
}

int father(int i)
{
    if (i > 1)
    {
        return i / 2;
    }
    return i;
}

int cmp(Item a, Item b)
{
    if (a < b)
        return -1;
    if (a == b)
        return 0;
    if (a > b)
        return 1;
}

void heapify_up(Heap h, int i)
{
    if (i > 1)
    {
        int j = father(i);
        if (cmp(h[i], h[j]) < 0)
        {
            swap(h, i, j);
            heapify_up(h, j);
        }
    }
}

int main()
{
    Heap h = malloc(sizeof(Item));
    for (int i = 1; i < 7; i++)
    {
        h[i] = 5-i;
    }
    stampa(h, 6);
    heapify_up(h,5);
    stampa(h, 6);
}

void swap(Heap h, int i, int j)
{
    Item ap = h[i];
    h[i] = h[j];
    h[j] = ap;
}