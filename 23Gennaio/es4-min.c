#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "../simulazioniEsame/queue.c"

int *createJumps(int, int);
void relax(int *d, int *prec, int u, int v)
{
    if (d[v] > d[u] + 1)
    {
        d[v] = d[u] + 1;
        prec[v] = u;
    }
}

int min(int *dist, bool *presi, int n)
{
    int indexMin = -1;
    int min = (int)INFINITY;
    for (int i = 1; i <= n; i++)
    {
        if (min > dist[i] && presi[i] == false)
        {
            indexMin = i;
            min = dist[i];
        }
    }
    if (indexMin != -1)
    {
        presi[indexMin] = true;
    }
    return indexMin;
}

void initializeSingleSource(int *dist, int *prec, int n, int start)
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = (int)INFINITY;
        prec[i] = -1;
    }
    dist[start] = 0;
}

int move(int *jump, int start, bool *presi, int dice, int n)
{
    int end = start + dice;
    if (end > n)
    {
        return -1;
    }
    if (jump[end] != 0)
    {
        presi[end] = true;
        return jump[end];
    }
    return end;
}

void initializeQueue(Queue *q, int n)
{
    for (int i = 1; i <= n; i++)
    {
        *q = enqueue(*q, i);
    }
}

bool allPresi(bool *presi, int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (presi[i] == false)
        {
            return false;
        }
    }
    return true;
}

void dijkstra(int *dist, int *prec, int *jump, int n)
{
    initializeSingleSource(dist, prec, n, 1);
    bool *presi = calloc(n + 1, sizeof(bool));

    while (!allPresi(presi, n))
    {
        int curr = min(dist, presi, n);
        printf("%d - %d\n", curr, dist[curr]);
        for (int i = 1; i <= 6; i++)
        {
            int next = move(jump, curr, presi, i, n);
            if (next > 0)
            {
                relax(dist, prec, curr, next);
            }
        }
    }
}

int main()
{
    int r, c;
    scanf("%d%d", &r, &c);

    int *jump = createJumps(r, c);

    int n = r * c;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("%d ", jump[i]);
    printf("\n");

    int *dist = calloc(n + 1, sizeof(dist));
    int *prec = calloc(n + 1, sizeof(dist));

    dijkstra(dist, prec, jump, n);
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", dist[i]);
    }
    printf("\n");
    int p = n;
    do
    {
        printf("%d <- ", p);
        p = prec[p];
    } while (prec[p] != -1);
    printf("%d",p);
    return 0;
}

int *createJumps(int r, int c)
{
    int n = r * c;
    int *jump = malloc((n + 1) * sizeof(int)); // aggiungo n+1 e tolto * a int

    int s, m, t;
    scanf("%d", &s);
    while (s > 0)
    {
        scanf("%d%d", &m, &t);
        jump[m] = t; //scambiato m con t
        s--;         //decremento il contatore altrimenti
                     // ricadiamo in un ciclo infinito
    }

    // c * caselle coperte + start % c - 1;

    int l, start, len;
    scanf("%d", &l);
    for (int i = 0; i < l; i++)
    {
        scanf("%d%d", &start, &len);
        int row, col, end;
        row = r - 1 - (start - 1) / c;
        col = (start - 1) % c;
        if ((row + r) % 2 == 0)
            col = c - col;

        row = row - len + 1;
        end = c * (r - row);
        if ((row + r) % 2 == 0)
            end -= col;
        else
            end += col - c; // tolto +1

        jump[start] = end;
    }

    return jump;
}
