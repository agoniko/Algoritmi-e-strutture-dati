#include <stdio.h>
#include <stdlib.h>

//supponendo che le operazioni elementari costino O(1)
//Possiamo dire che questo algoritmo ha un costo computazionale pari
//ad O(n)
int calcolaMax(int P[], int size)
{
    int cont = 0, max = 1;
    for (int i = 0; i < size; i++)
    {
        if (i != 0 && P[i] >= P[i - 1])
        {
            cont++;
            if (max < cont)
            {
                max = cont;
            }
        }
        else
        {
            cont = 1;
        }
    }
    return max;
}

void stampa(int P[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", P[i]);
    }
    printf("\n");
}
int main()
{
    int n;
    printf("Quanti elementi vuoi iserire? ");
    scanf("%d", &n);
    int P[n];
    for (int i = 0; i < n; i++)
    {
        printf("Inserisci l'elemento in posizione %d:", i);
        scanf("%d", &P[i]);
    }
    int result = calcolaMax(P, n);
    stampa(P, n);
    printf("%d\n", result);
}