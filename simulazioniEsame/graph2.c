#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int v;
    struct node *next;
};

struct graph
{
    int V;           //numero Vertici
    int E;           //numero archi
    struct node **A; //Array di liste di adiacenza
};

struct node *enqueue(struct node *head, int val)
{
    struct node *ap = malloc(sizeof(struct node));
    ap->v = val;
    ap->next = NULL;
    if (head == NULL)
    {
        head = ap;
    }
    else
    {
        struct node *p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = ap;
    }
    return head;
}

bool emptyq(struct node *head)
{
    return head == NULL ? true : false;
}

int dequeue(struct node **head)
{
    int v = (*head)->v;
    struct node *ap = *head;
    (*head) = (*head)->next;
    free(ap);
    return v;
}

void printQueue(struct node *head)
{
    struct node *ap = head;
    while (ap != NULL)
    {
        printf("%d -> ", ap->v);
        ap = ap->next;
    }
    printf("\n");
}

struct graph *createGraph(FILE *fp)
{
    int ne, nv;
    fscanf(fp, "%d %d", &nv, &ne);
    struct graph *g = malloc(sizeof(struct graph));
    g->E = ne;
    g->V = nv;
    g->A = calloc(nv, sizeof(struct node *));
    return g;
}

struct node *vertexinsert(struct node *p, int k)
{
    struct node *q = malloc(sizeof(struct node));
    q->v = k;
    q->next = p;
    return q;
}

void readgraph(struct graph *g, FILE *fp)
{
    int i, v1, v2;
    for (int i = 0; i < g->E; i++)
    {
        fscanf(fp, "%d %d", &v1, &v2);
        g->A[v1] = vertexinsert(g->A[v1], v2);
    }
}

void dfs1(struct graph *g, int i, bool *aux)
{
    aux[i] = true;
    struct node *t;
    for (t = g->A[i]; t != NULL; t = t->next)
    {
        if (!aux[t->v])
        {
            printf("%d, ", t->v);
            dfs1(g, t->v, aux);
        }
    }
}

void dfs(struct graph *g)
{
    bool *aux = calloc(g->V, sizeof(bool));
    for (int i = 0; i < g->V; i++)
    {
        if (!aux[i])
        {
            printf("\n%d, ", i);
            dfs1(g, i, aux);
        }
    }
    free(aux);
    printf("\n");
}

void bfs1(struct graph *g, int i, bool *aux){
    struct node *queue = NULL;
    queue = enqueue(queue,i);

    while(!emptyq(queue)){
        int V = dequeue(&queue);
        aux[V] = true;
        struct node *t;
        for(t = g->A[i]; t != NULL; t = t->next){
            if(!aux[t->v]){
                queue = enqueue(queue,t->v);
                printf("%d, ",t->v);
                aux[t->v] = 1;
            }
        }
    }    
}

void bfs(struct graph *g){
    struct node *queue = NULL;
    bool *aux = calloc(g->V, sizeof(bool));
    for(int i = 0; i<g->V; i++){
        if(!aux[i]){
            printf("\n%d, ",i);
            bfs1(g,i,aux);
        }
    }
}


int main(void)
{
    FILE *fp = fopen("grafo.txt", "r");
    if (fp == NULL)
    {
        printf("error\n");
        return 0;
    }
    struct graph *g;
    g = createGraph(fp);
    readgraph(g, fp);
    dfs(g);

   bfs(g);

    return (0);
}