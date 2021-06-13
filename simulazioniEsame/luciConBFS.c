#include <stdio.h>
#include <stdlib.h>
#include "queue.c"
#include <math.h>

void getPerm(bool **perm, int rows, int N)
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

bool **getPerms(int n)
{
    int m = (int)pow(2, (double)n);
    bool **perm = calloc(m, sizeof(bool *));
    for (int i = 0; i < m; i++)
    {
        perm[i] = calloc(n, sizeof(bool));
    }
    getPerm(perm, m, n);
    return perm;
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

int next(bool *perm, int N, int interruttore)
{
    int rows = (int)pow(2, (double)N);
    bool seq[N];
    for (int i = 0; i < N; i++)
    {
        seq[i] = perm[i];
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

void initialize(int *prec, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        prec[i] = -1;
    }
}

void stampaStato(bool *perm, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", perm[i]);
    }
    printf("\n");
}

int *searchBFS(int start, int target, int rows, int N)
{
    bool *visti = calloc(rows, sizeof(bool));
    int *prec = calloc(rows, sizeof(int));
    initialize(prec, rows);
    bool **perm = getPerms(N);
    Queue q = NULL;
    enqueue(&q, start);
    while (!emptyq(q))
    {
        int curr = dequeue(&q);
        visti[curr] = true;
        if (curr == target)
        {
            return prec;
        }
        for (int i = 0; i < N; i++)
        {
            int n = next(perm[curr], N, i);
            if (!visti[n])
            {
                visti[n] = true;
                prec[n] = curr;
                enqueue(&q, n);
            }
        }
    }
    return prec;
}

int main(void)
{
    int n = 5;
    bool **perm = getPerms(n);
    int rows = (int)pow(2, (int)n);
    bool *st = perm[5];

    int tar = 0, start = 13;
    int *prec = searchBFS(start, tar, rows, n);

    while (tar != -1)
    {
        stampaStato(perm[tar], n);
        tar = prec[tar];
    }

   /* for(int i = 0; i<rows; i++){
        printf("%d ",prec[i]);
    }*/

    return (0);
}