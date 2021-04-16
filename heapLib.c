#include <stdio.h>
#include <stdlib.h>


typedef int Item;
typedef Item *Heap;

void swap(Heap h, int i, int j);
int father(int i);
int cmp(Item a, Item b);
void heapify_up(Heap h, int i);
Pqueue pqueue_sort(Item a[], int l, int r);
void deleteNode (Heap h, int i, int *n);

struct pqueue
{
    Heap heap;
    int size, count;
} pqueue;

typedef struct pqueue *Pqueue;

typedef struct bit_node
{
    Item item;
    struct bit_node *l, *r;
} bit_node;








void stampa(Heap h, int size)
{
    for (int i = 1; i <= size; i++)
    {
        printf("%d ", h[i]);
    }
    printf("\n");
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

void heapify_down(Heap h, int i, int n)
{
    
    //i ha almeno un figlio
    if (i * 2 <= n)
    {
        int j;
        
        if (i * 2 == n)
        {
            //i ha solo il figlio sinistro
            j = 2 * i;
        }
        else
        {
            j = cmp(h[2 * i], h[2 * i + 1]) < 0 ? 2 * i : 2 * i + 1;
        }
        
        if (cmp(h[j], h[i]) < 0)
        {
            swap(h, i, j);
            heapify_down(h, j, n);
        }
    }
}

Pqueue pqueue_sort(Item a[], int l, int r)
{
    Pqueue p = malloc(sizeof(Pqueue));
    p->heap = malloc(20 * sizeof(Heap));
    p->size = r - l + 1;
    p->count = 0;
    for (int i = 0; i < p->size; i++)
    {
        p->heap[i + 1] = a[l + i];
        heapify_up(p->heap, i);
    }
    return p;
}

void deleteNode (Heap h, int i, int *n)
{
    swap(h, *n, i);
    *n = *n - 1;
    int j = father(i);
    
    if (cmp(h[i], h[j]) < 0)
    {
        heapify_up(h, i);
    }
    else if (cmp(h[i], h[i * 2]) > 0 || cmp(h[i], h[i * 2 + 1]) > 0)
    {
        heapify_down(h, i, *n);
    }
    
}

void swap(Heap h, int i, int j)
{
    Item ap = h[i];
    h[i] = h[j];
    h[j] = ap;
}