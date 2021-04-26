#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define P 15

typedef struct oggetto
{
    int p;
    int v;
} oggetto;

typedef oggetto *Oggetto;

Oggetto newOggetto(int peso, int valore)
{
    Oggetto o = malloc(sizeof(Oggetto));
    o->p = peso;
    o->v = valore;
    return o;
}

void scambia(Oggetto oggetti[], int i, int j)
{
    Oggetto ap = oggetti[i];
    oggetti[i] = oggetti[j];
    oggetti[j] = ap;
}
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getBestValue(Oggetto oggetti[], int i, int peso)
{
    if (i == -1)
    {
        return 0;
    }
    if (peso == 0)
    {
        return 0;
    }

    if (oggetti[i]->p > peso)
    {
        return getBestValue(oggetti, i - 1, peso);
    }
    else
    {
        return max(getBestValue(oggetti, i - 1, peso), oggetti[i]->v + getBestValue(oggetti, i - 1, peso - oggetti[i]->p));
    }
}

void creaOggetti(Oggetto oggetti[], int size)
{
    oggetti[0] = newOggetto(0,0);
    for (int i = 1; i < size; i++)
    {
        oggetti[i] = newOggetto(rand() % 5 + 1, rand() % 5 + 1);
    }
}

void stampaOggetti(Oggetto oggetti[], int size)
{
    for (int i = 1; i < size; i++)
    {
        printf("Peso: %d, Valore: %d\n", oggetti[i]->p, oggetti[i]->v);
    }
}

int getPesoTotaleOggetti(Oggetto oggetti[], int size)
{
    int pesoTot = 0;
    for (int i = 1; i < size; i++)
    {
        pesoTot += oggetti[i]->p;
    }
    return pesoTot;
}

int getValoreTotaleOggetti(Oggetto oggetti[], int size)
{
    int valoreTot = 0;
    for (int i = 1; i < size; i++)
    {
        valoreTot += oggetti[i]->v;
    }
    return valoreTot;
}

void stampaMatrix(int v[N][P])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < P; j++)
        {
            printf("%d ", v[i][j]);
        }
        printf("\n");
    }
}

int knapstack(Oggetto oggetti[], int a[], int v[N][P], int size)
{
    for (int w = 0; w < P; w++)
    {
        v[0][w] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        v[i][0] = 0;
    }
    for (int i = 1; i < N; i++)
    {
        for (int w = 1; w < P; w++)
        {
            if (oggetti[i]->p < w)
            {
                if (oggetti[i]->v + v[i - 1][w - oggetti[i]->p] > v[i - 1][w])
                {
                    v[i][w] = oggetti[i]->v + v[i - 1][w - oggetti[i]->p];
                    a[i] = 1;
                }
                else
                {
                    v[i][w] = v[i - 1][w];
                    a[i] = 0;
                }
            }
            else
            {
                v[i][w] = v[i - 1][w];
                a[i] = 0;
            }
        }
    }
}

int main()
{
    srand(time(0));
    Oggetto oggetti[N];
    creaOggetti(oggetti, N);
    stampaOggetti(oggetti, N);
    printf("peso totale oggetti: %d", getPesoTotaleOggetti(oggetti, N));
    printf(", valore totale: %d\n", getValoreTotaleOggetti(oggetti, N));
    int a[N];
    int v[N][P];
    knapstack(oggetti, a, v, N);
    stampaMatrix(v);
}