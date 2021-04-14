#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 10

void stampa(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void riempiRandom(int *a, int n)
{
    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }
}

void *my_malloc(size_t n)
{
    void *p;
    p = malloc(n);
    if (p == NULL)
    {
        exit(EXIT_FAILURE);
    }
    return p;
}

int *read_n(int *num)
{
    int *a;
    printf("Quanti numeri vuoi inserire? ");
    scanf("%d", num);

    a = my_malloc(*num * sizeof(int));
    printf("Inseriscili\n");
    for (int i = 0; i < *num; i++)
    {
        scanf("%d",&a[i]);
    }
    return a;
}

int main()
{
    int *a, b;
    a = read_n(&b);
    stampa(a,b);
}