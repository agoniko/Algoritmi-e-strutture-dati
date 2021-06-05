#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct state
{
    bool *val;
    //per ogni stato ho un numero n di stati a cui posso arrivare
    //(la pressione di n interruttori)
    struct state **i;
} state;

typedef struct state *State;

typedef struct queue{
    State v;
    struct queue *next;
}queue;

typedef struct queue *Queue;

bool equals(State s, bool *perm, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (s->val[i] != perm[i])
        {
            return false;
        }
    }
    return true;
}

State creaStato(int size)
{
    State s = calloc(1, sizeof(State));
    s->val = calloc(size, sizeof(bool));
    s->i = calloc(size, sizeof(State));
    return s;
}

State inQueue(Queue q, bool *val, int n){
    Queue ap = q;
    while(ap != NULL){
        if(equals(ap->v,val,n)){
            return ap->v;
        }else{
            ap = ap->next;
        }
    }
    return NULL;
}

Queue enqueue(Queue q, State s, int n)
{
    if(q == NULL){
        q = malloc(sizeof(Queue));
        //q->v = creaStato(n);
        q->v = s;
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
        p->next->v = s;
        p->next->next = NULL;
        return q;
    }
}

bool emptyq(Queue q)
{
    return q == NULL ? true : false;
}

State dequeue(Queue *q)
{
   if(!emptyq(*q)){
       Queue p = *q;
       *q = (*q)->next;
       State v = p->v;
       free(p);
       return v;
   }
   *q = NULL;
   return NULL;
}

void stampaStato(State s, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", s->val[i]);
    }
    printf("\n");
}

void stampaS(State s, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", s->val[i]);
    }
    printf("-> ");
}

void printQueue(Queue q, int n){
    Queue ap = q;
    while(ap != NULL){
        stampaS(ap->v,n);
        ap = ap->next;
    }
    printf("\n");
}


