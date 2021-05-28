#include "./lib/es1-struttura.c"
#include <stdio.h>

typedef struct struttura *Struttura;
typedef struct listnode *Listnode;

void stampa(Struttura s)
{
    printf("a: ");
    if (s->a != NULL)
    {
        Listnode l = s->a;
        while (l != NULL)
        {
            printf("%d ", l->v);
            l = l->next;
        }
    }
    printf("\nb: ");
    if (s->b != NULL)
    {
        Listnode l = s->b;
        while (l != NULL)
        {
            printf("%d ", l->v);
            l = l->next;
        }
    }
    printf("\n");
}

int main()
{
    Struttura s = createStruttura();
    f1(s, 5);
    f1(s, 8);
    f1(s, 12);
    stampa(s);
    f2(s);
    stampa(s);
}