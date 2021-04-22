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

void ordinaBubble(intervallo inter[]){
    
}

void stampaIntervalli(intervallo inter[])
{
    for (int i = 0; i < N; i++)
    {
        printf("inizio: %d, fine: %d, studenti: %d\n", inter[i].i, inter[i].f, inter[i].v);
    }
}

int main()
{
    srand(time(0));
    intervallo inter[N];
    riempiIntervallo(inter);
    stampaIntervalli(inter);
}