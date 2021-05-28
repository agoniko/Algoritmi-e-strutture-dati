#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 6

typedef struct intervallo
{
    int i, f, v;
} intervallo;

typedef struct intervallo *Intervallo;

Intervallo new_intervallo(int i, int f, int v)
{
    Intervallo inter = malloc(sizeof(Intervallo));
    inter->i = i;
    inter->f = f;
    inter->v = v;
    return inter;
}

void scambia(Intervallo inter[], int i, int j)
{
    Intervallo ap = new_intervallo(inter[i]->i, inter[i]->f, inter[i]->v);
    inter[i] = inter[j];
    inter[j] = ap;
}

void bubbleSort(Intervallo inter[], int size)
{
    int scambiato = 1;
    int n = size - 2;
    while (scambiato == 1)
    {
        scambiato = 0;
        for (int i = 0; i < n + 1; i++)
        {
            if (inter[i]->f > inter[i + 1]->f)
            {
                scambia(inter, i, i + 1);
                scambiato = 1;
            }
        }
        n--;
    }
}

void stampaIntervalli(Intervallo inter[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d-%d: %d\n", inter[i]->i, inter[i]->f, inter[i]->v);
    }
}

void riempiRandom(Intervallo inter[], int size)
{
    for (int j = 0; j < N; j++)
    {
        int i = rand() % 10;
        int f = rand() % 5 + i + 1;
        int v = rand() % 20;
        inter[j] = new_intervallo(i, f, v);
    }
}

int p(Intervallo inter[], int size, int j)
{
    int i = 0;
    int inizioJ = inter[j]->i;
    while (inter[i]->f < inizioJ)
    {
        i++;
    }
    return i - 1;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int cerca(int s[], int size, int elem)
{
    for (int i = 0; i < size; i++)
    {
        if (s[i] == elem)
        {
            return i;
        }
    }
    return -1;
}

int opt(Intervallo inter[], int size, int j)
{
    if (j >= 0)
    {
        return max(inter[j]->v + opt(inter, size, p(inter, N, j)), opt(inter, N, j - 1));
    }
    return 0;
}

//s ha stessa dimensione di inter
int optWithVector(Intervallo inter[], int size, int s[], int cont, int j)
{
    if (j >= 0)
    {
        int v1 = inter[j]->v + optWithVector(inter, size, s, cont + 1, p(inter, N, j));
        int v2 = optWithVector(inter, N, s, cont + 1, j - 1);
        int mx = max(v1, v2);
        if (mx != v1)
        {
            s[cont] = j;
        }
        return mx;
    }
    return 0;
}

void stampaBestIntervalli(Intervallo inter[], int s[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (s[i] != -1)
        {
            printf("%d-%d: %d\n", inter[s[i]]->i, inter[s[i]]->f, inter[s[i]]->v);
        }
    }
}

void inizializzaS(int s[], int size)
{
    for (int i = 0; i < size; i++)
    {
        s[i] = -1;
    }
}

void riempiInter(Intervallo inter[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int j, f, v;
        scanf("%d-%d %d", &j, &f, &v);
        inter[i] = new_intervallo(j, f, v);
    }
}

int main(void)
{
    srand(time(0));
    Intervallo inter[N];
    //riempiRandom(inter, N);
    riempiInter(inter, N);
    bubbleSort(inter, N);
    stampaIntervalli(inter, N);
    int s[N];
    inizializzaS(s, N);
    printf("%d\n", opt(inter, N, N - 1));
    //stampaBestIntervalli(inter, s, N);
    return (0);
}