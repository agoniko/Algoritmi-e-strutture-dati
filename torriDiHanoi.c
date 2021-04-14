#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 26
void hanoi(int n, int from, int temp, int to, int *mosse);
void stampa();
typedef char Stringa[N];

struct paletto
{
    Stringa dischi;
    int n;
} paletto;

typedef struct paletto Paletto;

Paletto p[3];



int main()
{
    int n;
    printf("Inserisci il numero di dischi: ");
    scanf("%d", &n);
    char *pointer = p[0].dischi;
    char c = 65;
    for (int i = 0; i < n; i++)
    {
        *pointer = c;
        c++;
        pointer++;
    }
    p[0].n = n;
    stampa();
    int mosse = 0;

    hanoi(n, 0, 1, 2, &mosse);
    printf("Per risolvere il quesito ho usato %d mosse\n",mosse);
}

void stampa()
{
    printf("%s , %s, %s\n", p[0].dischi, p[1].dischi, p[2].dischi);
}

void sposta(int from, int to)
{
    int nFrom = p[from].n;
    int nTo = p[to].n;

    p[to].dischi[nTo] = p[from].dischi[nFrom - 1];
    p[to].dischi[nTo + 1] = '\0';
    p[to].n++;

    p[from].dischi[nFrom - 1] = '\0';
    p[from].n--;
    stampa();
}

void hanoi(int n, int from, int temp, int to, int *mosse)
{
    *mosse=*mosse+1;
    if (n == 1)
    {
        sposta(from, to);
        return;
    }
    hanoi(n - 1, from, to, temp, mosse);
    sposta(from, to);
    hanoi(n - 1, temp, from, to, mosse);
}
