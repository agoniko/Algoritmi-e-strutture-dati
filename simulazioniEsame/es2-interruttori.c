#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef bool *Bool;

void stampa(Bool a, int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void bubblesort(int arr[], int n)
{
    bool scambiato = true;
    int dim = n - 1;
    while (scambiato)
    {
        scambiato = false;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int ap = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = ap;
                scambiato = true;
            }
        }
        n--;
    }
}

Bool creaRete(Bool a, int n)
{
    a = calloc(n + 1, sizeof(Bool));
    return a;
}

//preme interruttore i su una rete di dimensione n
void accendi(Bool a, int n, int i)
{
    if (i <= 0 || i > n)
        return;
    if (i == 1)
    {
        a[n] = !a[n];
        a[1] = !a[1];
        a[2] = !a[2];
    }
    else if (i == n)
    {
        a[n] = !a[n];
        a[n - 1] = !a[n - 1];
        a[1] = !a[1];
    }
    else
    {
        a[i] = !a[i];
        a[i + 1] = !a[i + 1];
        a[i - 1] = !a[i - 1];
    }
}

void setState(Bool a, Bool state, int n)
{
    for (int i = 1; i <= n; i++)
    {
        a[i] = state[i];
    }
}

void o(Bool a, int n)
{
    Bool s = creaRete(s, n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &(s[i]));
    }
    setState(a, s, n);
    free(s);
}

void s(Bool a, int n)
{
    int interruttore;
    scanf("%d", &interruttore);
    if (interruttore <= 0 || interruttore > n)
        return;
    accendi(a, n, interruttore);
}

void S(Bool a, int n)
{
    int dim;
    scanf("%d", &dim);
    int arr[dim];
    for (int i = 0; i < dim; i++)
    {
        scanf("%d", &arr[i]);
    }
    bubblesort(arr, dim);
    for (int i = 0; i < dim; i++)
    {
        accendi(a, n, arr[i]);
    }
}

int main()
{
    int n;
    Bool a;

    char input = 'n';
    while (input != 'f')
    {
        scanf("%c", &input);
        switch (input)
        {
        case '+':
            scanf("%d", &n);
            a = creaRete(a, n);
            break;
        case 'o':
            o(a, n);
            break;
        case 'p':
            stampa(a, n);
            break;
        case 's':
            s(a, n);
            break;
        case 'S':
            S(a, n);
            break;
        case 'f':
            printf("\n");
            return 0;
        }
    }
}