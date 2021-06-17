#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct heap
{
    int *a;
    int size;
};

typedef struct heap *Heap;

Heap creaHeap(int n)
{
    Heap h = calloc(1, sizeof(Heap));
    h->a = calloc(4*n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        h->a[i] = i;
    }
    h->size = n;
    return h;
}

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

int left(int n)
{
    return n * 2 + 1;
}

int right(int n)
{
    return n * 2 + 2;
}

void swap(int *a, int i, int j)
{
    int ap = a[i];
    a[i] = a[j];
    a[j] = ap;
}

void printHeapAsSummary(Heap h, int spaces, int curr)
{
    if (curr >= h->size)
        return;
    printSpaces(spaces);
    printf("*%d\n", h->a[curr]);
    printHeapAsSummary(h, spaces + 2, curr * 2 + 1);
    printHeapAsSummary(h, spaces + 2, curr * 2 + 2);
}

void max_heapify(Heap h, int curr)
{
    int l, r, largest = curr;
    l = left(curr);
    r = right(curr);
    if (l < h->size && h->a[l] > h->a[largest])
    {
        largest = l;
    }
    if (r < h->size && h->a[r] > h->a[largest])
    {
        largest = r;
    }
    if (largest != curr)
    {
        swap(h->a, curr, largest);
        max_heapify(h, largest);
    }
}

void min_heapify(Heap h, int curr)
{
    int l, r, smallest = curr;
    l = left(curr);
    r = right(curr);
    if (l < h->size && h->a[l] < h->a[smallest])
    {
        smallest = l;
    }
    if (r < h->size && h->a[r] < h->a[smallest])
    {
        smallest = r;
    }
    if (smallest != curr)
    {
        swap(h->a, smallest, curr);
        min_heapify(h, smallest);
    }
}

void build_max_heap(Heap h)
{
    int size = h->size / 2;
    for (int i = size; i >= 0; i--)
    {
        max_heapify(h, i);
    }
}

void build_min_heap(Heap h)
{
    int size = h->size / 2;
    for (int i = size; i >= 0; i--)
    {
        min_heapify(h, i);
    }
}

int father(int i){
    if(i > 1){
        return (i-1)/2;
    }
}

void heapify_up_min(Heap h, int i){
    if(i < 1)
        return;
    int f = father(i);
    if(h->a[f] > h->a[i]){
        swap(h->a,f,i);
        heapify_up_min(h,f);
    }
}


void insert_min_heap(Heap h, int n){
    int curr = h->size;
    int f = father(curr);
    h->a[curr] = n;
    h->size++;
    if(h->a[curr] < h->a[f]){
        min_heapify(h,f);
    }    
}

int search(Heap h, int n){
    for(int i = 0; i<h->size; i++){
        if(h->a[i] == n)
            return i;
    }
    return -1;
}

void delete_min_heap(Heap h, int n){
    int index = search(h,n);
    if(index == -1)
        return;
    swap(h->a,index,h->size-1);
    min_heapify(h,index);
    h->a[h->size-1] = 0;
    h->size--;    
}

int main(void)
{
    Heap h = creaHeap(10);
    build_min_heap(h);
    for(int i = 100; i>=90; i--){
        insert_min_heap(h,i);
    }
    delete_min_heap(h,5);
    printHeapAsSummary(h,0,0);
    return (0);
}