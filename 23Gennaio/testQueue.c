#include <stdio.h>
#include <stdlib.h>
#include "../simulazioniEsame/queue.c"

int main()
{
    Queue q;
    q = enqueue(q, 5);
    q = enqueue(q, 4);
    q = enqueue(q, 3);
    printQueue(q);

    int v = dequeue(&q);
    printQueue(q);
}