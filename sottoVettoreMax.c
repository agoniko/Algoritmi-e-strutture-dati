#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

typedef struct result
{
    int inizio;
    int fine;
    int *somme;
} result;

typedef struct result *Result;

Result newResult(int inizio, int fine, int a[], int size)
{
    Result r = malloc(sizeof(Result));
    r->fine = fine;
    r->inizio = inizio;
    r->somme = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        r->somme[i] = a[i];
    }
    return r;
}

void riempiRandom(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % 12 - 6;
    }
}

void print(int *a, int size)
{
    int *p = a;
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *p);
        p++;
    }
    printf("\n");
}

Result maxSubVector(int a[], int size)
{
    int s[N] = {0};
    int fine = 0;
    s[0] = a[0];
    int max = s[0];
    for (int i = 1; i < size; i++)
    {
        if (s[i - 1] >= 0)
        {
            s[i] = s[i - 1] + a[i];
        }
        else
        {
            s[i] = a[i];
        }

        if (s[i] > max)
        {
            max = s[i];
            fine = i;
        }
    }
    int inizio = fine;
    while (s[inizio] != a[inizio])
    {
        inizio--;
    }

    return newResult(inizio, fine, s, size);
}

int main()
{
    srand(time(0));
    int a[N];
    riempiRandom(a, N);
    Result r = maxSubVector(a, N);
    print(a, N);
    print(r->somme, N);
    printf("Il sub vector inizia a %d e finisce a %d\n", r->inizio, r->fine);
}