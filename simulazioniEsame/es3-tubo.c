#include <stdio.h>
#include <stdlib.h>

void print(int *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void merge(int *a, int sx, int m, int dx)
{
    int dimSx = m - sx + 1;
    int dimDx = dx - m;
    int s[dimSx], d[dimDx];
    for (int i = 0; i < dimSx; i++)
    {
        s[i] = a[sx + i];
    }
    for (int i = 0; i < dimDx; i++)
    {
        d[i] = a[m + 1 + i];
    }
    int contS = 0, contD = 0;
    int contA = sx;
    while (contS < dimSx && contD < dimDx)
    {
        if (s[contS] < d[contD])
        {
            a[contA] = s[contS];
            contS++;
        }
        else
        {
            a[contA] = d[contD];
            contD++;
        }
        contA++;
    }

    while (contS < dimSx)
    {
        a[contA] = s[contS];
        contS++;
        contA++;
    }

    while (contD < dimDx)
    {
        a[contA] = d[contD];
        contD++;
        contA++;
    }
}

void mergeSort(int *a, int sx, int dx)
{
    if (sx < dx)
    {
        int m = (sx + dx) / 2;
        mergeSort(a, sx, m);
        mergeSort(a, m + 1, dx);
        merge(a, sx, m, dx);
    }
}

int maxTubi(int L, int l[], int n)
{
    mergeSort(l, 0, n - 1);
    int cont = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += l[i];
        if (sum <= L)
        {
            cont++;
        }
        else
        {
            break;
        }
    }
    return cont;
}

int sassi(int height){
    if(height <= 0)
        return 0;
    
    return (height * height) + sassi(height-1);
}

int main(void)
{
    int L;
    scanf("%d", &L);
    int n;
    scanf("%d", &n);
    int l[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &l[i]);
    }
    printf("%d\n", maxTubi(L, l, n));
    return (0);
}


