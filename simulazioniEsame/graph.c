#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct listnode
{
    struct listnode *next;
    int v;
};

typedef struct graph
{
    int n; //numero di vertici
    struct listnode **a;
} Grafo;

Grafo *new (int n)
{
    Grafo *g = malloc(sizeof(Grafo));
    g->n = n;
    g->a = calloc(n, sizeof(struct listnode));
    for (int i = 0; i < n; i++)
    {
        g->a[i] = calloc(1, sizeof(struct listnode));
        g->a[i]->v = i;
        g->a[i]->next = NULL;
    }
    g->a[3]->next = malloc(sizeof(struct listnode));
    g->a[3]->next->v = 1;
    g->a[3]->next->next = malloc(sizeof(struct listnode));
    g->a[3]->next->next->v = 2;
    g->a[3]->next->next->next = NULL;
    return g;
}

void stampaGrafo(Grafo *g)
{
    struct listnode *ap;
    for (int i = 0; i < g->n; i++)
    {
        ap = g->a[i];
        while (ap != NULL)
        {
            printf("%d -> ", ap->v);
            ap = ap->next;
        }
        printf("\n");
    }
}

void inverti(Grafo *g, int v, int w)
{
    if (w > g->n || v > g->n)
        return;
    struct listnode *ap = g->a[v];
    struct listnode *target = g->a[w];
    while (ap->next != NULL && ap->next->v != target->v)
    {
        ap = ap->next;
    }
    if (ap->next != NULL)
    {
        while (target->next != NULL)
        {
            target = target->next;
        }
        target->next = malloc(sizeof(struct listnode));
        target->next->v = v;
        target->next->next = NULL;
        struct listnode *c = ap->next;
        ap->next = ap->next->next;
        free(c);
    }
}
void scambia(int *arr, int i, int j)
{
    int ap = arr[i];
    arr[i] = arr[j];
    arr[j] = ap;
}

void bubblesort(int *arr, int size)
{
    bool scambiato = true;
    int n = size - 1;
    while (scambiato)
    {
        scambiato = false;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                scambia(arr, i, i + 1);
                scambiato = true;
            }
        }
        n--;
    }
}

int *contaGradi(Grafo *g)
{
    int *arr = calloc(g->n, sizeof(int));
    for (int i = 0; i < g->n; i++)
    {
        struct listnode *ap = g->a[i];
        int cont = 0;
        while (ap->next != NULL)
        {
            ap = ap->next;
            cont++;
        }
        arr[i] = cont;
    }
    bubblesort(arr, g->n);
    return arr;
}
void stampaGradi(Grafo *g)
{
    printf("--------\n");
    int *arr = contaGradi(g);
    for (int i = 0; i < g->n; i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("--------\n");
}

int main(void)
{
    Grafo *g = new (6);

    stampaGrafo(g);
    stampaGradi(g);

    inverti(g, 3, 1);
    stampaGradi(g);

    return (0);
}
