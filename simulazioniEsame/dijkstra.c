#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "queue.c"
#define N 5

void removeVal(int val, Queue *q);

void getPerm(bool perm[][N], int rows)
{
    int limit = 1;
    for (int j = N - 1; j >= 0; j--)
    {
        int cont = 0;
        bool write = false;
        for (int i = 0; i < rows; i++)
        {
            if (cont == limit)
            {
                cont = 0;
                write = !write;
            }
            perm[i][j] = write;
            cont++;
        }
        limit = limit * 2;
    }
}

void stampaMatrix(bool perm[][N], int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", perm[i][j]);
        }
        printf("\n");
    }
}

int binaryToInt(bool *perm, int n)
{
    int num = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (perm[i])
        {
            num += (int)pow(2, (n - 1) - i);
        }
    }
    return num;
}

bool *decimalToBinary(int dec)
{
    bool *perm = calloc(10, sizeof(bool));
    for (int i = 0; dec > 0; i++)
    {
        perm[i] = dec % 2;
        dec /= 2;
    }
    return perm;
}

void stampaStato(bool *perm)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", perm[i]);
    }
    printf("\n");
}

int next(bool perm[][N], int row, int interruttore)
{
    int rows = (int)pow(2, (double)N);
    bool seq[N];
    for (int i = 0; i < N; i++)
    {
        seq[i] = perm[row][i];
    }
    if (interruttore == N - 1)
    {
        seq[N - 1] = !seq[N - 1];
        seq[0] = !seq[0];
        seq[N - 2] = !seq[N - 2];
    }
    else if (interruttore == 0)
    {
        seq[1] = !seq[1];
        seq[0] = !seq[0];
        seq[N - 1] = !seq[N - 1];
    }
    else
    {
        seq[interruttore] = !seq[interruttore];
        seq[interruttore - 1] = !seq[interruttore - 1];
        seq[interruttore + 1] = !seq[interruttore + 1];
    }
    return binaryToInt(seq, N);
}

void initializeSingleSource(int *dist, int *prec,bool *presi, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        dist[i] = (int)INFINITY;
        prec[i] = -1;
        presi[i] = false;
    }
    dist[0] = 0;
}

int min(int *dist, bool *presi, int rows, Queue *q)
{
    int min = -1;
    for (int i = 0; i < rows; i++)
    {
        if (dist[i] != (int)INFINITY && presi[i] == false)
        {
            min = i;
            break;
        }
    }
    for (int i = min; i < rows; i++)
    {
        if (dist[min] > dist[i] && presi[i] == false)
        {
            min = i;
        }
    }
    return min;
}

void removeVal(int val, Queue *q)
{
    Queue ap = *q;
    Queue previous = ap;
    ap = ap->next;
    if (val == previous->v)
    {
        *q = (*q)->next;
    }
    else
    {
        while (ap != NULL)
        {
            int s = ap->v;
            if (val == s)
            {
                previous->next = ap->next;
                free(ap);
            }
            previous = ap;
            ap = ap->next;
        }
    }
}

void relax(int *dist, int *prec, int start, int target)
{
    if (dist[target] > dist[start] + 1)
    {
        dist[target] = dist[start] + 1;
        prec[target] = start;
    }
}

void dijkstra(bool perm[][N], int *dist, int *prec, Queue *V)
{
    int rows = (int)pow(2, (double)N);
    bool *presi = calloc(rows, sizeof(bool));
    initializeSingleSource(dist, prec,presi, rows);
    while (!emptyq(*V))
    {
        int key = min(dist, presi, rows, V);
        removeVal(key,V);
        presi[key] = true;
        if (dist[key] == (int)INFINITY || key == -1)
        {
            break;
        }
        for (int i = 0; i < N; i++)
        {
            int state = next(perm, key, i);
            relax(dist, prec, key, state);
        }
    }
}


void stampaDist(int *dist, int *precedente, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        printf("%d: dist: %d, prec: %d\n", i, dist[i], precedente[i]);
    }
    printf("\n");
}

int main(void)
{
    int rows = (int)pow(2, (double)N);
    bool perm[rows][N];
    getPerm(perm, rows);
    Queue q = NULL;
    for (int i = 0; i < rows; i++)
    {
        enqueue(&q, i);
    }

    int *dist = calloc(rows, sizeof(int));
    int *prec = calloc(rows, sizeof(int));

    dijkstra(perm, dist, prec, &q);

    stampaDist(dist,prec,rows);
    int target = 31;
    while(target >= 0){
        stampaStato(perm[target]);
        target = prec[target];
    }

    return 0;
}