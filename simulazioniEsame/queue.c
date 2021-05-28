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

Queue createqueue()
{
    Queue q = malloc(sizeof(Queue));
    q->v = (int)-INFINITY;
    q->next = NULL;
    return q;
}


Queue enqueue(Queue q, int v)
{
    if(q == NULL){
        q = malloc(sizeof(Queue));
        q->v = v;
        q->next = NULL;
        return q;
    }
    else
    {
        Queue p = q;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = malloc(sizeof(Queue));
        p->next->v = v;
        p->next->next = NULL;
        return q;
    }
}

bool emptyq(Queue q)
{
    return q == NULL ? true : false;
}

int dequeue(Queue *q)
{
   if(!emptyq(*q)){
       Queue p = *q;
       *q = (*q)->next;
       int v = p->v;
       free(p);
       return v;
   }
   *q = NULL;
   printf("vuota\n");
   return -1;
}


void printQueue(Queue q)
{
    Queue p = q;
    while (p != NULL)
    {
        printf("%d -> ", p->v);
        p = p->next;
    }
    printf("\n");
}
