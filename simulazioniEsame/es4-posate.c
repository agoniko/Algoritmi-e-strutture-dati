#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum posata
{
    forchetta = 'F',
    coltello = 'K',
    libero = 'Z'
};

typedef enum posata Posata;

typedef struct node
{
    Posata posata;
    struct node *next;
} node;
typedef struct node *Node;

typedef struct pila
{
    Node head, tail;
    int length;
} pila;
typedef struct pila *Pila;

Pila creaPila()
{
    Pila p = malloc(sizeof(Pila));
    p->head = NULL;
    p->tail = NULL;
    p->length = 0;
    return p;
}

void push(Pila p, Posata posata)
{
    if (p->length == 0)
    {
        p->head = malloc(sizeof(Node));
        p->tail = malloc(sizeof(Node));
        p->head->posata = posata;
        p->tail->posata = posata;
        p->head->next = NULL;
        p->tail = p->head;
        p->length++;
    }
    else
    {
        p->head->next = malloc(sizeof(Node));
        p->head = p->head->next;
        p->head->posata = posata;
        p->head->next = NULL;
        p->length++;
    }
}

void stampaPila(Pila pila)
{
    Node ap = pila->tail;
    printf("tail -> head\n");
    for (int i = 0; i < pila->length; i++)
    {
        printf("%c -> ", ap->posata);
        ap = ap->next;
    }
    printf("\n");
}

Posata pop(Pila pila)
{
    Posata p = pila->head->posata;
    Node n = pila->tail;
    if (pila->length < 2)
    {
        n = NULL;
    }
    for (int i = 0; i < pila->length - 1; i++)
    {
        n = n->next;
    }
    pila->head = n;
    pila->length--;
    return p;
}

typedef struct robot
{
    Posata l, r;
} robot;
typedef struct robot *Robot;

bool isEmpty(Pila pila)
{
    if (pila->head == NULL)
    {
        return true;
    }
    return false;
}

void esegui()
{
    Pila pila = creaPila();
    Robot robot = calloc(1, sizeof(Robot));
    int scatola = 0;
    robot->l = 'Z';
    robot->r = 'Z';
    char *seq = calloc(15, sizeof(char));
    scanf("%s", seq);
    char *c = seq;
    while (*c != '\0')
    {
        //printf("%c \n%c  %c\n", *c, robot->l, robot->r);
        if (robot->l != 'Z' && robot->r != 'Z' && robot->l != robot->r)
        {
            robot->r = robot->l = 'Z';
            scatola++;
            printf("+1\n");
        }
        else if (robot->l != 'Z' && robot->r != 'Z' && robot->l == robot->r)
        {
            push(pila, robot->r);
            printf("dx push %c\n", robot->r);
            robot->r = 'Z';
        }
        else if (robot->l == 'Z' && robot->r == 'Z')
        {
            robot->l = *c;
            c++;
            printf("sx %c\n", robot->l);
        }
        else if (robot->l != 'Z' && robot->r == 'Z')
        {
            if (!isEmpty(pila) && pila->head->posata != robot->l)
            {
                robot->r = pop(pila);
                printf("dx pop %c\n", robot->r);
            }
            else
            {
                robot->r = *c;
                c++;
                printf("dx %c\n", robot->r);
            }
        }
    }
    printf("%d %c %c\n", scatola, robot->l, robot->r);
    stampaPila(pila);
}

int main(void)
{
    esegui();

    return (0);
}