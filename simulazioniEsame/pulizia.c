#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

int **getMatrix(int n)
{
    int **a = calloc(n + 1, sizeof(int *));
    for (int i = 1; i <= n; i++)
    {
        a[i] = calloc(n + 1, sizeof(int));
        for (int j = 1; j <= n; j++)
        {
            a[i][j] = rand() % (n + 1);
        }
    }
    return a;
}

void stampaMatrix(int **a, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int min(int *a, int n, bool *visti)
{
    int m = (int)INFINITY;
    int indexMin = -1;
    for (int i = 1; i <= n; i++)
    {
        if (m > a[i] && !visti[i])
        {
            m = a[i];
            indexMin = i;
        }
    }
    return indexMin;
}

int *greedy(int **a, int n)
{
    int *r = calloc(n + 1, sizeof(int));
    bool *visti = calloc(n + 1, sizeof(bool));
    r[1] = 1;
    visti[1] = true;
    for (int i = 2; i <= n; i++)
    {
        int m = min(a[r[i - 1]], n, visti);
        if (m != -1)
        {
            r[i] = m;
            visti[r[i]] = true;
        }
    }
    return r;
}

int main(void)
{
    srand(time(0));
    int n = 5;
    int **a = getMatrix(n);
    stampaMatrix(a, n);
    int *result = greedy(a, n);
    printf("seq: \n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
    return (0);
}