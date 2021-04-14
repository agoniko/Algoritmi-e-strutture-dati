#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define size 10

typedef struct
{
    int i, j;
} posizione;

posizione nextMove(char parco[size][size], int i, int j)
{
    posizione pos;
    pos.i = i;
    pos.j = j;
    int val = rand() % 4;
    switch (val)
    {
    case 0:
        if (i > 0 && parco[i - 1][j] == '.')
        {
            pos.i--;
            return pos;
        }
        break;
    case 1:
        if (j < size-1 && parco[i][j + 1] == '.')
        {
            pos.j++;
            return pos;
        }
        break;
    case 2:
        if (i < size-1 && parco[i + 1][j] == '.')
        {
            pos.i++;
            return pos;
        }
        break;
    case 3:
        if (j > 0 && parco[i][j - 1] == '.')
        {
            pos.j--;
            return pos;
        }
        break;
    }
    return pos;
}

void inizializzaParco(char parco[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            parco[i][j] = '.';
        }
    }
}

void stampaParco(char parco[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%c ", parco[i][j]);
        }
        printf("\n");
    }
}
int numberOfAvailableMoves(char parco[size][size], int i, int j)
{
    int n = 0;
    if (parco[i - 1][j] == '.')
        n++;
    if (parco[i][j + 1] == '.')
        n++;
    if (parco[i + 1][j] == '.')
        n++;
    if (parco[i][j - 1] == '.')
        n++;
    return n;
}

void passeggia(char parco[size][size])
{
    char n = 65;
    int i = 0, j = 0;
    parco[i][j] = n;
    n++;
    while (n < 91)
    {
        if(numberOfAvailableMoves(parco,i,j) > 0){
            posizione p;
            p.i = i;
            p.j = j;
            while(p.i == i && p.j == j){
                p = nextMove(parco,i,j);
            }
            i = p.i;
            j = p.j;
            parco[i][j] = n;
            n++;
        }else{
            return;
        }
    }
}





int main()
{
    srand(time(0));
    char parco[size][size];
    inizializzaParco(parco);
    passeggia(parco);
   stampaParco(parco);
}