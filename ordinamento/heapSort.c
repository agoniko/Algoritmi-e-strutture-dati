#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define N 15

void stampaNodo(int heap[], int i, int size, int spaces);
void stampaLeftSlash(int spaces);
void stampaRightSlash(int spaces);
void scambia(int a[], int i, int j);
void max_heapify(int a[], int i, int size);

void build_max_heap(int heap[], int size)
{
    for (int i = size / 2; i > 0; i--)
    {
        max_heapify(heap, i, size);
    }
}

//Questa procedura serve per risistemare l'heap.
//Sostanzialmente prende un padre ed i figli e controlla che essi siano inferiori.
//Se sono maggiori non vale la proprietà di max heap (si fa al contrario per min_heap)
//Quindi prende il figlio con chiave più grande e lo scambia con se stesso.
//Se è avvenuto uno scambio si procede ricorsivamente verso il basso in modo da portare le chiavi minori verso il basso.
/*
HeapSort `e un algoritmo di ordinamento in loco che, per ordinare n elementi, effettua Θ(n log n)
confronti. Pertanto, se ciascun confronto viene effettuato in tempo O(1), il tempo complessivo
`e Θ(n log n).
Si pu`o verificare che questo metodo non `e stabile (provate ad esempio a vedere cosa succede
ordinando un array contenente 3 record, con chiavi 10, 10 e 20).
*/
void max_heapify(int a[], int i, int size)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int max = i;
    if (size >= left && a[left] > a[max])
    {
        max = left;
    }
    if (size >= right && a[right] > a[max])
    {
        max = right;
    }
    if (max != i)
    {
        scambia(a, max, i);
        max_heapify(a, max, size);
    }
}

void scambia(int a[], int i, int j)
{
    int ap = a[i];
    a[i] = a[j];
    a[j] = ap;
}

void riempiInverso(int a[], int size)
{
    for (int i = 1; i <= size; i++)
    {
        a[i] = size - i;
    }
}
void stampaSeparatore()
{
    printf("\n");
    for (int i = 0; i < N * 4; i++)
    {
        printf("-");
    }
    printf("\n");
}

void stampaInAmpiezza(int heap[], int size, int i, int spaces)
{
    stampaSeparatore();
    int n = 1;
    int cont = 0;
    for (int i = 1; i <= size; i++)
    {
        if (cont == n)
        {
            n = n * 2;
            cont = 0;
            spaces = spaces / 2;
            printf("\n\n");
        }
        if (cont == 0)
        {
            stampaNodo(heap, i, size, spaces + N - log2((double)n));
            cont++;
        }
        else
        {
            stampaNodo(heap, i, size, spaces * 2);
            cont++;
        }
    }
    stampaSeparatore();
    printf("%f", log2(n));
}

void stampaLeftSlash(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    printf("/");
}
void stampaRightSlash(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    printf("\\");
}
void stampaNodo(int heap[], int i, int size, int spaces)
{
    if (i <= size)
    {
        if (heap[i] > 10)
            spaces++;

        for (int i = 0; i < spaces; i++)
        {
            printf(" ");
        }
        printf("%d", heap[i]);
    }
}

void riempiRandom(int a[], int size)
{
    for (int i = 1; i <= size; i++)
    {
        a[i] = rand() % N;
    }
}

void riempiDritto(int a[], int size)
{
    for (int i = 1; i <= size; i++)
    {
        a[i] = i;
    }
}

int main()
{
    srand(time(0));
    int heap[N + 1];
    riempiDritto(heap, N);
    stampaInAmpiezza(heap, N, 1, N * 2);
    build_max_heap(heap, N);
    stampaInAmpiezza(heap, N, 1, N * 2);
}