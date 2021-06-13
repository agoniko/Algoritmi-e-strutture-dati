#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct queue
{
    int v;
    struct queue *next;
} queue;

typedef struct queue *Queue;

void enqueue(Queue *q, int val)
{
    struct queue *ap = malloc(sizeof(struct queue));
    ap->v = val;
    ap->next = NULL;
    if (*q == NULL)
    {
        *q = ap;
    }
    else
    {
        ap->next = *q;
        *q = ap;
    }
}

void printq(Queue q)
{
    while (q != NULL)
    {
        printf("%d -> ", q->v);
        q = q->next;
    }
    printf("\n");
}

int dequeue(Queue *q)
{
    if (*q == NULL)
        return -1;
    if ((*q)->next == NULL)
    {
        int v = (*q)->v;
        free(*q);
        *q = NULL;
        return v;
    }
    else
    {
        Queue p = *q;
        while (p->next->next != NULL)
        {
            p = p->next;
        }
        int v = p->next->v;
        free(p->next);
        p->next = NULL;
        return v;
    }
}

bool emptyq(Queue q)
{
    return q == NULL ? true : false;
}

void delete (Queue *q, int val)
{
    if (emptyq(*q))
        return;
    if ((*q)->v == val)
    {
        Queue p = *q;
        *q = (*q)->next;
        free(p);
        return;
    }
    else
    {
        Queue p = *q;
        while (p->next->v != val && p->next != NULL)
        {
            p = p->next;
        }
        if (p->next == NULL)
            return;
        Queue ap = p->next;
        p->next = ap->next;
        free(ap);
        return;
    }
}
