#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.c"
#include <math.h>
#include <time.h>

struct graph
{
    int n, m; // n= vertici, m = archi
    int **A;  //matrice di adiacenza
};

typedef struct graph *Graph;

/* crea un grafo con n nodi */
Graph graph_new(int n);

/* distrugge il grafo g */
void graph_destroy(Graph g);

/* inserisce l’arco (v,w) nel grafo g */
void graph_edgeinsert(Graph g, int v, int w, int peso);

/* legge da standard input un grafo (specificare il formato!!) */
Graph graph_read(void);

/* stampa su standard output un grafo (specificare il formato!!) */
void graph_print(Graph g);

Graph graph_new(int n)
{
    Graph g = malloc(sizeof(struct graph));
    g->A = calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        g->A[i] = calloc(n, sizeof(int));
    }
    g->n = n;
    g->m = 0;
    return g;
}

void dfs1(Graph g, int curr, bool *visti)
{
    visti[curr] = true;
    for (int i = 0; i < g->n; i++)
    {
        if (!visti[i] && g->A[curr][i] > 0)
        {
            printf("%d, ", i);
            dfs1(g, i, visti);
        }
    }
}

void dfs(Graph g)
{
    printf("DFS: ");

    bool *visti = calloc(g->n, sizeof(bool));
    for (int i = 0; i < g->n; i++)
    {
        if (!visti[i])
        {
            printf("\n%d, ", i);
            dfs1(g, i, visti);
        }
    }
    printf("\n");
}

void graph_edgeinsert(Graph g, int v, int w, int peso)
{
    if (v >= g->n || w >= g->n)
        return;
    g->A[v][w] = peso;
}

Graph graph_read()
{
    FILE *file = fopen("grafo.txt", "r");
    int nv, nm;
    fscanf(file, "%d %d", &nv, &nm);
    Graph g = graph_new(nv);
    int cont = 0;
    while (!feof(file))
    {
        int v1, v2, w;
        fscanf(file, "%d %d %d", &v1, &v2, &w);
        graph_edgeinsert(g, v1, v2, w);
        cont++;
    }
    fclose(file);
    g->m = cont;
    return g;
}

void bfs1(Graph g, int k, bool *visti)
{
    Queue q = NULL;
    enqueue(&q, k);
    while (!emptyq(q))
    {
        int curr = dequeue(&q);
        printf("%d, ", curr);
        visti[curr] = true;
        for (int i = 0; i < g->n; i++)
        {
            if (!visti[i] && g->A[curr][i] > 0)
            {
                enqueue(&q, i);
                visti[i] = true;
            }
        }
    }
    printf("\n");
}

void bfs(Graph g)
{
    printf("BFS: \n");
    bool *visti = calloc(g->n, sizeof(bool));
    for (int i = 0; i < g->n; i++)
    {
        if (!visti[i])
        {
            bfs1(g, i, visti);
        }
    }
}

int degree(Graph g, int v)
{
    int cont = 0;
    for (int i = 0; i < g->n; i++)
    {
        if (g->A[v][i] == 1)
            cont++;
    }
    return cont;
}

void initialize(int *prec, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        prec[i] = -1;
    }
}

void dfsPath(Graph g, int *prec, bool *visti, int v, int w)
{
    visti[v] = true;
    for (int i = 0; i < g->n; i++)
    {
        if (!visti[i] && g->A[v][i] == 1)
        {
            prec[i] = v;
            if (i == w)
                return;
            dfsPath(g, prec, visti, i, w);
        }
    }
}

int *path(Graph g, int v, int w)
{
    int *prec = calloc(g->n, sizeof(int));
    bool *visti = calloc(g->n, sizeof(visti));
    initialize(prec, g->n);
    dfsPath(g, prec, visti, v, w);
    if (prec[w] == -1)
        return NULL;
    return prec;
}

void stampaPrec(int *prec, int w)
{
    while (prec[w] != -1)
    {
        printf("%d ", w);
        w = prec[w];
    }
    printf("%d\n", w);
}

void cc(Graph g, int v)
{
    bool *visti = calloc(g->n, sizeof(bool));
    int *prec = calloc(g->n, sizeof(int));
    initialize(prec, g->n);

    for (int i = 0; i < g->n; i++)
    {
        if (!visti[i] && g->A[v][i] > 0)
        {
            dfsPath(g, prec, visti, i, v);
            if (prec[v] != -1)
                break;
        }
    }
    if (prec[v] != -1)
    {
        stampaPrec(prec, v);
    }
    else
    {
        printf("pd\n");
    }
}

int minKey(Graph g, int *dist, bool *visti)
{
    int min = (int)INFINITY;
    int indexMin;
    for (int i = 0; i < g->n; i++)
    {
        if (!visti[i] && dist[i] < min)
        {
            min = dist[i];
            indexMin = i;
        }
    }
    return indexMin;
}

void initializeDist(Graph g, int *dist, int v)
{
    for (int i = 0; i < g->n; i++)
    {
        dist[i] = (int)INFINITY;
    }
    dist[v] = 0;
}

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

int **initializeSon(int size)
{
    int **son = calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        son[i] = calloc(size, sizeof(int));
        initialize(son[i], size);
    }
    return son;
}

void insertSon(int **son, int father, int s, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (son[i][father] == -1)
        {
            son[i][father] = s;
            break;
        }
    }
}
Queue creaCoda(Graph g)
{
    Queue q = NULL;
    for (int i = g->n - 1; i >= 0; i--)
    {
        enqueue(&q, i);
    }
    return q;
}

int extractMin(int *dist, bool *visti, int n)
{
    int min = (int)INFINITY;
    int indexMin = -1;
    for (int i = 0; i < n; i++)
    {
        if (min > dist[i] && !visti[i])
        {
            min = dist[i];
            indexMin = i;
        }
    }
    return indexMin;
}

bool isSon(int **son, int s, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
        }
    }
}

int **prim(Graph g, int v)
{
    bool *visti = calloc(g->n, sizeof(bool));
    bool *isSon = calloc(g->n, sizeof(bool));
    int **son = initializeSon(g->n);
    int *dist = calloc(g->n, sizeof(int));
    initializeDist(g, dist, v);
    Queue q = creaCoda(g);

    while (!emptyq(q))
    {
        int u = extractMin(dist, visti, g->n);
        delete (&q, u);
        visti[u] = true;
        for (int j = 0; j < g->n; j++)
        {
            if (g->A[u][j] > 0 && !isSon[j] && dist[u] + g->A[u][j] < dist[j])
            {
                insertSon(son, u, j, g->n);
                isSon[j] = true;
                dist[j] = dist[u] + g->A[u][j];
            }
        }
    }
    for (int i = 0; i < g->n; i++)
    {
        printf("%d ", dist[i]);
    }
    printf("\n");
    return son;
}

void relax(int *dist, int *prec, int start, int target, int peso)
{
    if (dist[target] > dist[start] + peso)
    {
        dist[target] = dist[start] + peso;
        prec[target] = start;
    }
}

void shortestPath(Graph g, int start, int target)
{
    bool *visti = calloc(g->n, sizeof(bool));
    int *dist = calloc(g->n, sizeof(int));
    int *prec = calloc(g->n, sizeof(int));
    initializeDist(g, dist, start);
    initialize(prec, g->n);
    Queue q = creaCoda(g);

    while (!emptyq(q))
    {
        int curr = extractMin(dist, visti, g->n);
        delete (&q, curr);
        visti[curr] = true;
        for (int i = 0; i < g->n; i++)
        {
            if (g->A[curr][i] > 0)
            {
                relax(dist, prec, curr, i, g->A[curr][i]);
            }
        }
    }
    int pesoTot = 0;
    int v = target;
    while (prec[v] != -1)
    {
        pesoTot += g->A[prec[v]][v];
        v = prec[v];
    }
    stampaPrec(prec, target);
    printf("Peso: %d\n", pesoTot);
}

bool isBipartito1(Graph g, bool *visti, bool *color, int curr, bool colore)
{
    visti[curr] = true;
    color[curr] = colore;
    for (int i = 0; i < g->n; i++)
    {
        if (visti[i] && color[i] == colore && g->A[curr][i] > 0)
            return false;
        if (!visti[i] && g->A[curr][i] > 0)
        {
            if (!isBipartito1(g, visti, color, i, !colore))
                return false;
        }
    }
    return true;
}

bool isBipartito(Graph g)
{
    bool *visti = calloc(g->n, sizeof(bool));
    bool *color = calloc(g->n, sizeof(bool));
    for (int i = 0; i < g->n; i++)
    {
        if (!visti[i])
        {
            if (!isBipartito1(g, visti, color, i, true))
                return false;
        }
    }
    return true;
}

bool oddCycles(Graph g)
{
    if (isBipartito(g))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void printAsSummary(int **son, int size, int spaces, int curr)
{
    if (curr == -1)
        return;
    printSpaces(spaces);
    printf("*%d\n", curr);
    for (int i = 0; i < size; i++)
    {
        if (son[i][curr] == -1)
            break;
        else
        {
            printAsSummary(son, size, spaces + 2, son[i][curr]);
        }
    }
}

int main(void)
{
    Graph g = graph_read();

    int **son = prim(g, 0);
    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
        {
            printf("%d ", son[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printAsSummary(son, g->n, 0, 0);
    return (0);
}