#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "stateQueue.c"

typedef State *Rete;

bool *premiInterruttore(State s, int interruttore, int n);
State getState(int val, Queue *q, int n);

void copiaStato(State s, bool *perm, int n)
{
    for (int i = 0; i < n; i++)
    {
        s->val[i] = perm[i];
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

State bfs(State start, bool *target, int n)
{
    Queue q = NULL;
    int rows = (int)pow(2, (double)n);
    int check[rows];
    for (int i = 0; i < rows; i++)
    {
        check[i] = 0;
    }
    q = enqueue(q, start, n);
    check[binaryToInt(start->val, n)] = 1;
    while (!emptyq(q))
    {
        State current = dequeue(&q);
        if (equals(current, target, n))
        {
            return current;
        }
        for (int j = 0; j < n; j++)
        {
            State s = current->i[j];
            int decValue = binaryToInt(s->val, n);
            if (check[decValue] != 1)
            {
                check[decValue] = 1;
                q = enqueue(q, s, n);
            }
        }
    }
    return NULL;
}

//restituisce indirizzo stato 0 0 0.. 0
State creaGrafo(int n, Queue q)
{
    int rows = (int)pow(2, (double)n);
    bool perm[rows][n];
    int limit = 1;
    for (int j = n - 1; j >= 0; j--)
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
    State start = creaStato(n);
    copiaStato(start, perm[0], n);
    q = enqueue(q, start, n);

    Queue daVisitare = NULL;
    daVisitare = enqueue(daVisitare, start, n);
    int cont = 0;
    while (!emptyq(daVisitare))
    {
        cont++;
        State ap = dequeue(&daVisitare);
        for (int i = 0; i < n; i++)
        {
            bool *val = premiInterruttore(ap, i, n);
            State s = inQueue(q, val, n);
            if (s == NULL)
            {
                ap->i[i] = creaStato(n);
                copiaStato(ap->i[i], val, n);
                q = enqueue(q, ap->i[i], n);
                daVisitare = enqueue(daVisitare, ap->i[i], n);
            }
            else
            {
                ap->i[i] = s;
            }
        }
    }
    printf("cont: %d, tot: %d\n", cont, cont * n);
    return start;
}

bool *premiInterruttore(State s, int interruttore, int n)
{
    if (interruttore >= n || interruttore < 0)
        return NULL;
    bool *perm = calloc(n, sizeof(bool));
    for (int i = 0; i < n; i++)
    {
        perm[i] = s->val[i];
    }
    perm[interruttore] = !perm[interruttore];
    if (interruttore == 0)
    {
        perm[1] = !perm[1];
        perm[n - 1] = !perm[n - 1];
        return perm;
    }
    else if (interruttore == n - 1)
    {
        perm[0] = !perm[0];
        perm[n - 2] = !perm[n - 2];
        return perm;
    }
    else
    {
        perm[interruttore + 1] = !perm[interruttore + 1];
        perm[interruttore - 1] = !perm[interruttore - 1];
        return perm;
    }
}

void initializeSingleSource(int *dist, int *precedente, int size)
{
    for (int i = 0; i < size; i++)
    {
        dist[i] = (int)INFINITY;
        precedente[i] = -1;
    }
    dist[0] = 0;
}

void relax(int *dist, int *precedente, int target, int start, int size)
{
    if (dist[target] > dist[start] + 1)
    {
        dist[target] = dist[start] + 1;
        precedente[target] = start;
    }
}

int min(int *dist, bool *presi, int size)
{
    int min = -1;
    for (int i = 0; i < size; i++)
    {
        if (dist[i] != (int)INFINITY && presi[i] == false)
        {
            min = i;
            break;
        }
    }
    for (int i = min; i < size; i++)
    {
        if (dist[min] > dist[i] && presi[i] == false)
        {
            min = i;
        }
    }
    presi[min] = true;
    return min;
}

State getState(int val, Queue *q, int n)
{
    Queue ap = *q;
    Queue previous = ap;
    ap = ap->next;
    if (val == binaryToInt(previous->v->val, n))
    {
        *q = (*q)->next;
        return previous->v;
    }
    else
    {
        while (ap != NULL)
        {
            State s = ap->v;
            if (val == binaryToInt(s->val, n))
            {
                previous->next = ap->next;
                free(ap);
                return s;
            }
            previous = ap;
            ap = ap->next;
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

int *dijkstra(State start, int n, Queue V, int *dist, int *precedente, int rows)
{
    bool *presi = calloc(rows, sizeof(int));
    initializeSingleSource(dist, precedente, rows); //La sistanza dal nodo di partenza viene settata a 0

    while (!emptyq(V))
    {
        int key = min(dist, presi, rows);
        //prende min da dist e quindi prende sempre 0 che hai tolto dalla queue
        State s = getState(key, &V, n);
        if (dist[key] == (int)INFINITY)
        {
            break;
        }
        for (int i = 0; i < n; i++)
        {
            int nextVal = binaryToInt(s->i[i]->val, n);
            relax(dist, precedente, nextVal, key, rows);
        }
    }
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

int main(void)
{
    int n = 8;
    Queue listaNodi = NULL;
    listaNodi = enqueue(listaNodi, creaStato(n), n);
    State s = creaGrafo(n, listaNodi);
    listaNodi = listaNodi->next;

    int rows = (int)pow(2, (double)n);
    int *dist = calloc(rows, sizeof(int));
    int *precedente = calloc(rows, sizeof(int));

    dijkstra(s, n, listaNodi, dist, precedente, rows);

    bool *target = calloc(n,sizeof(bool));
    for(int i = 0; i<n; i++){
        scanf("%d",&target[i]);
    }


    int targetVal = binaryToInt(target, n);

    printf("devi accendere %d interruttori\n", dist[targetVal]);
    Queue q = NULL;
    while (precedente[targetVal] != -1)
    {
        State s = creaStato(n);
        copiaStato(s,decimalToBinary(targetVal),n);
        stampaStato(s,n);
        targetVal = precedente[targetVal];
    }

    //stampaDist(dist, precedente, rows);

    return (0);
}