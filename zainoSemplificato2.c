#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define LIMITE 10
#define N 3

typedef struct oggetto
{
    int p, v;
} oggetto;

typedef struct oggetto *Oggetto;

int max(int a, int b)
{
    return a > b ? a : b;
}

Oggetto new_oggetto(int p, int v)
{
    Oggetto o = malloc(sizeof(Oggetto));
    o->p = p;
    o->v = v;
    return o;
}

void creaInsiemeOggetti(Oggetto oggetti[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int p = rand() % 9 + 2;
        int v = rand() % 9 + 1;
        oggetti[i] = new_oggetto(p, v);
    }
}

void stampaOggetti(Oggetto oggetti[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("p: %d, v: %d\n", oggetti[i]->p, oggetti[i]->v);
    }
}

void scambia(Oggetto oggetti[], int i, int j)
{
    Oggetto ap = oggetti[i];
    oggetti[i] = oggetti[j];
    oggetti[j] = ap;
}

void bubbleSort(Oggetto oggetti[])
{
    int scambiato = 1;
    int n = N - 2;
    while (scambiato == 1)
    {
        scambiato = 0;
        for (int i = 0; i < n + 1; i++)
        {
            if (oggetti[i]->p > oggetti[i + 1]->p)
            {
                scambiato = 1;
                scambia(oggetti, i, i + 1);
            }
            else if (oggetti[i]->p == oggetti[i + 1]->p)
            {
                if (oggetti[i]->v < oggetti[i + 1]->v)
                {
                    scambiato = 1;
                    scambia(oggetti, i, i + 1);
                }
            }
        }
        n--;
    }
}

int bestValueRec(Oggetto oggetti[], int pesoRimasto, int index)
{
    if (pesoRimasto < 0)
        return (int)-INFINITY;
    else if (index == -1 || pesoRimasto == 0)
    {
        return 0;
    }
    else
    {
        int nonPrendoIndex = bestValueRec(oggetti, pesoRimasto, index - 1);
        int prendoIndex = bestValueRec(oggetti, pesoRimasto - oggetti[index]->p, index - 1) + oggetti[index]->v;
        return max(nonPrendoIndex, prendoIndex);
    }
}

int bestValue(Oggetto oggetti[])
{
    return bestValueRec(oggetti, LIMITE, N - 1);
}

void stampa(int s[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", s[i]);
    }
    printf("\n");
}

int zaino(Oggetto oggetti[], int s[])
{
    int scambiato = 1;
    for (int i = 0; i < LIMITE + 1 && scambiato == 1; i++)
    {
        scambiato = 0;
        for (int j = 0; j < N; j++)
        {
            if (s[i + oggetti[j]->p] < s[i] + oggetti[j]->v)
            {
                scambiato = 1;
                s[i + oggetti[j]->p] = s[i] + oggetti[j]->v;
            }
        }
        stampa(s, LIMITE + 1);
    }
    return s[LIMITE];
}

//soluzione ottimale
// S = maxVal(P)

int zainoRic(Oggetto oggetti[], int s[], int peso)
{
    if (peso <= LIMITE)
    {
        for (int i = 0; i < N; i++)
        {
            int p = peso + oggetti[i]->p;
            if (p <= LIMITE)
            {
                if (s[p] < s[peso] + oggetti[i]->v)
                {
                    s[p] = s[peso] + oggetti[i]->v;
                }
            }
        }
        peso = peso + 1;
        return zainoRic(oggetti, s, peso);
    }
    return s[LIMITE];
}

void stampaPresi(Oggetto oggetti[], int presi[])
{
    int contPresi = 0;
    printf("Presi: \n");
    while (presi[contPresi] >= 0)
    {
        printf("p: %d, v: %d\n", oggetti[presi[contPresi]]->p, oggetti[presi[contPresi]]->v);
        contPresi++;
    }
}

void inizializzaPresi(int *presi, int size)
{
    for (int i = 0; i < size; i++)
    {
        presi[i] = -1;
    }
}

void inizializzaS(int *s, int size)
{
    for (int i = 0; i < size; i++)
    {
        s[i] = 0;
    }
}

int main(void)
{
    srand(time(0));

    Oggetto oggetti[N];
    creaInsiemeOggetti(oggetti, N);
    //bubbleSort(oggetti);

    stampaOggetti(oggetti, N);

    int s[LIMITE + 1];

    inizializzaS(s, LIMITE + 1);

    printf("maxVal: %d\n", zaino(oggetti, s));

    printf("---------------------------------------------\n");

    int v[LIMITE + 1];
    inizializzaS(v, LIMITE + 1);
    stampa(v, LIMITE * 1);

    printf("ric: %d\n", zainoRic(oggetti, v, 0));
    //stampaPresi(oggetti, oggettiPresi);
    return (0);
}