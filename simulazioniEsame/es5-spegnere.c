#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct luci
{
    bool luce;
    struct luci *l, *r;
} luci;

typedef struct luci *Luci;

void stampaOrario(Luci *l, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d -> ", l[i]->luce);
    }
    printf("\n");
}

void stampaAntiOrario(Luci *l, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        printf("<- %d ", l[i]->luce);
    }
    printf("\n");
}

Luci *create(int n)
{
    Luci *l = calloc((n), sizeof(Luci));
    for (int i = 0; i < n; i++)
    {
        l[i] = calloc(1, sizeof(Luci));
    }
    for (int i = 1; i < n - 1; i++)
    {
        l[i]->r = l[i + 1];
        l[i]->l = l[i - 1];
    }
    l[0]->l = l[n - 1];
    l[0]->r = l[1];
    l[n - 1]->r = l[0];
    l[n - 1]->l = l[n - 2];

    return l;
}

//gli interruttori vanno da 1 a n
void accendi(Luci *luci, int interruttore)
{
    Luci ap = luci[0];
    for (int i = 1; i < interruttore; i++)
    {
        ap = ap->r;
    }
    ap->luce = !ap->luce;
    ap->l->luce = !ap->l->luce;
    ap->r->luce = !ap->r->luce;
}

bool isBuio(Luci *luci, int n)
{
    bool buio = true;
    Luci ap = luci[0];
    for (int i = 0; i < n; i++)
    {
        if (ap->luce == true)
        {
            buio = false;
            return buio;
        }
    }
    return buio;
}

void spegniTutto(Luci *luci, int n)
{
    isBuio(luci, n) ? printf("spento\n") : printf("acceso\n");

    while (isBuio)
    {
        printf("dentro");
        Luci ap = luci[0];
        for (int i = 1; i <= n; i++)
        {
            if (ap->luce && ap->l->luce && ap->r->luce)
            {
                accendi(luci, i);
            }
            else if (!ap->luce && !ap->r->luce && ap->l->luce)
            {
                accendi(luci, i + 1);
            }
            ap = ap->r;
        }
        stampaOrario(luci, n);
    }
}

int main()
{
    int n = 5;
    Luci *luci = create(n);
    Luci ap;
    accendi(luci, n);
    isBuio(luci, n) ? printf("spento\n") : printf("acceso\n");
    spegniTutto(luci, n);
    printf("finito\n");
    return (0);
}