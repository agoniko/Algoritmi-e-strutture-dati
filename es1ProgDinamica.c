#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

typedef struct intervallo
{
    int i, f, v;
} intervallo;

void riempiIntervallo(intervallo intervallo[])
{
    for (int j = 0; j < N; j++)
    {
        intervallo[j].i = rand() % 13 + 7;
        intervallo[j].f = intervallo[j].i + rand() % 2 + 1;
        intervallo[j].v = rand() % 15 + 10;
    }
}
void scambia(intervallo inter[], int i, int j)
{
    intervallo ap = inter[i];
    inter[i] = inter[j];
    inter[j] = ap;
}

int partition(intervallo inter[], int low, int high)
{
    int i = low;
    int j = high;
    while (i <= j)
    {
        while (inter[j].f > inter[low].f)
        {
            j--;
        }
        while (i <= j && inter[i].f <= inter[low].f)
        {
            i++;
        }
        if (i < j)
        {
            scambia(inter, i, j);
            i++;
            j--;
        }
    }
    scambia(inter, low, j);
    return j;
}

void quickSort(intervallo inter[], int low, int high)
{
    if (high > low)
    {
        int p = partition(inter, low, high);
        quickSort(inter, low, p - 1);
        quickSort(inter, p + 1, high);
    }
}

void stampaIntervalli(intervallo inter[], int size)
{
    printf("\n---------------------------------\n");
    for (int i = 0; i < size; i++)
    {
        printf("inizio: %d, fine: %d, studenti: %d\n", inter[i].i, inter[i].f, inter[i].v);
    }
    printf("---------------------------------\n");
}

//l'intervallo che gli arriva deve essere già ordinato
int getP(intervallo inter[], int j)
{
    int index = -1;
    for (int i = 0; i < j; i++)
    {
        if (inter[i].f <= inter[j].i)
        {
            index = i;
        }
    }
    return index;
}
int max(int i, int j)
{
    return (i > j) ? i : j;
}

int getOpt(intervallo inter[], int j)
{
    if (j > 0)
    {
        return max(inter[j].v + getOpt(inter, j - 1), getOpt(inter, j - 2));
    }
    return inter[0].f;
}

int getSoluzioneOttimale(intervallo inter[], intervallo *soluzione)
{
    int index[N];
    int cont = 0;
    for (int i = N - 1; i > 0; i--)
    {
        int j = getP(inter, i);
        if (j != -1)
        {
            index[cont] = j;
            cont++;
            i = j+1;
        }
    }
    soluzione = realloc(soluzione, cont+1 * sizeof(intervallo));
    soluzione[0] = inter[N-1];
    for (int i = 1; i <= cont; i++)
    {
        soluzione[i] = inter[index[i-1]];
    }

    return cont+1;
}

int main()
{
    srand(time(0));
    intervallo inter[N];
    riempiIntervallo(inter);
    quickSort(inter, 0, N - 1);
    stampaIntervalli(inter, N);
    intervallo *soluzione = malloc(sizeof(intervallo));
    int size = getSoluzioneOttimale(inter, soluzione);
    stampaIntervalli(soluzione, size);
}