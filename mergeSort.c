#include <stdio.h>
void stampa(int a[], int sx, int dx)
{
    for (int i = sx; i < dx; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}


void merge(int a[], int sx, int m, int dx)
{
    int dim1 = m - sx + 1;
    int dim2 = dx - m;
    int l[dim1], r[dim2];
    for (int i = 0; i < dim1; i++)
    {
        l[i] = a[sx + i];
    }
    for (int i = 0; i < dim2; i++)
    {
        r[i] = a[m + 1 + i];
    }

    int i1 = 0, i2 = 0;
    int j = sx;
    while (i1 < dim1 && i2 < dim2)
    {
        if (l[i1] <= r[i2])
        {
            a[j] = l[i1];
            i1++;
        }
        else
        {
            a[j] = r[i2];
            i2++;
        }
        j++;
    }
    while (i1 < dim1)
    {
        a[j] = l[i1];
        i1++;
        j++;
    }

    while (i2 < dim2)
    {
        a[j] = r[i2];
        i2++;
        j++;
    }
}

void mergesort(int a[], int sx, int dx)
{
    if (sx >= dx)
        return;
    int m = sx + (dx - sx) / 2;
    mergesort(a, sx, m);
    stampa(a, sx, m);
    mergesort(a, m + 1, dx);
    stampa(a, m + 1, dx);
    merge(a, sx, m, dx);
    stampa(a,sx,dx);
}



int main()
{

    int a[] = {2, 6, 3, 9, 0, 1, 3};
    int size = sizeof(a) / sizeof(a[0]);
    stampa(a, 0, size);
    mergesort(a, 0, size);
    stampa(a, 0, size);
}
