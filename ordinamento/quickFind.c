#include <stdio.h>
#include <stdlib.h>
#define N 100

void makeSet(int elem, int ins[N], int size[N])
{
    if (elem < N)
    {
        if (ins[elem] == 0)
        {
            ins[elem] = -1;
            size[elem] = 1;
        }
        else
        {
            printf("error: elemento già presente nell'insieme\n");
        }
    }
}

void Union(int a, int b, int ins[N], int size[N])
{
    if (ins[a] == -1 && ins[b] == -1)
    {
        if (size[a] > size[b])
        {
            size[a] += size[b];
            size[b] = 0;
            ins[b] = a;
        }
        else
        {
            ins[a] = b;
            ins[b] = -1;
            size[b] += size[a];
            size[a] = 0;
        }
    }
}

int find(int elem, int ins[N])
{
    if (ins[elem] == -1)
        return elem;
    return find(ins[elem], ins);
}

int main()
{
    int ins[N] = {0};
    int size[N] = {0};
    makeSet(2, ins, size);
    makeSet(4, ins, size);
    makeSet(8,ins,size);
    Union(2,4,ins,size);
    Union(8,4,ins,size);
    makeSet(70,ins,size);
    Union(70,,ins,size);
    printf("%d\n",find(70,ins));
  
    
}