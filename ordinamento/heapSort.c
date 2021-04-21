#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define N 15

void stampaNodo(int heap[], int i, int size, int spaces);
void stampaLeftSlash(int spaces);
void stampaRightSlash(int spaces);
void scambia(int a[], int i, int j);
void max_heapify(int a[], int i, int size);

void build_max_heap(int heap[], int size){
    for(int i = size/2; i > 0; i--){
        max_heapify(heap,i,size);
    }
}

void max_heapify(int a[], int i, int size)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int max = i;
    if (size >= left && a[left] > a[max])
    {
        max = left;
    }
    if (size >= right && a[right] > a[max])
    {
        max = right;
    }
    if (max != i)
    {
        scambia(a, max, i);
        max_heapify(a, max, size);
    }
}

void scambia(int a[], int i, int j)
{
    int ap = a[i];
    a[i] = a[j];
    a[j] = ap;
}

void riempiInverso(int a[], int size)
{
    for (int i = 1; i <= size; i++)
    {
        a[i] = size - i;
    }
}

void stampaInAmpiezza(int heap[], int size, int i, int spaces)
{
    for (int i = 0; i < N * 4; i++)
    {
        printf("-");
    }
    printf("\n");
    int n = 1;
    int cont = 0;
    int rightSpaces;

    for (int i = 1; i <= size; i++)
    {
        if (cont == 0)
        {
            stampaNodo(heap, i, size, spaces);
            if (heap[i] < 10)
            {
                spaces++;
                rightSpaces = spaces * 2;
            }
            else
            {
                rightSpaces = spaces * 2 + 1;
            }
        }
        else
        {
            stampaNodo(heap, i, size, rightSpaces - 1);
        }
        cont++;
        if (cont == n)
        {
            n *= 2;
            cont = 0;
            printf("\n");
            spaces = spaces / 2;
            printf("\n");
        }
    }
    for (int i = 0; i < N * 4; i++)
    {
        printf("-");
    }
    printf("\n");
}

void stampaLeftSlash(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    printf("/");
}
void stampaRightSlash(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    printf("\\");
}
void stampaNodo(int heap[], int i, int size, int spaces)
{
    if (i <= size)
    {
        for (int i = 0; i < spaces; i++)
        {
            printf(" ");
        }
        printf("%d", heap[i]);
    }
}

void riempiRandom(int a[], int size){
    for(int i = 1; i<=size;i++){
        a[i] = rand()%N;
    }
}

int main()
{
    srand(time(0));
    int heap[N + 1];
    riempiRandom(heap, N);
    stampaInAmpiezza(heap, N, 1, N * 2);
    build_max_heap(heap, N);
    stampaInAmpiezza(heap, N, 1, N * 2);
}