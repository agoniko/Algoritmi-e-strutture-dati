#include <stdio.h>
#include "/home/nic/Uni/algoritmi/Algoritmi-e-strutture-dati/ordinamento/mergeSort.c"

int numeroMax(int a[], int size, int L)
{
    int max = 0, sum = 0;

    mergeSort(a, 0, size - 1);
    for (int i = 0; i < size && sum <= L; i++)
    {
        sum += a[i];
        if (sum <= L)
            max++;
    }
    return max;
}

int main(void)
{
    int L, n;
    scanf("%d %d", &L, &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("%d\n", numeroMax(a, n, L));
    return (0);
}