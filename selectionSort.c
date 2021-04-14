#include <stdio.h>

void selectionSort(int a[], int n)
{
    if (n < 1)
        return;
    int index = 0, max = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
            index = i;
        }
    }
   
        int ap = a[n - 1];
        a[n - 1] = max;
        a[index] = ap;
        return selectionSort(a, n - 1);
}

void stampa(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int a[] = {2, 6, 3, 9, 0, 1, 3};
    stampa(a, sizeof(a) / 4);
    selectionSort(a, sizeof(a) / 4);
    stampa(a, sizeof(a) / 4);
}