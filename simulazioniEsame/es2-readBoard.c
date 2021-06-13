#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.c"
#include <stdbool.h>

int *createJumps(int, int);
int bfs(int *jump, int size, int start);
int move(int *jump, int casella, int tiro, int dimensioneCampo);

void stampa(int *jump, int n){
	for (int i = 1; i <= n; i++)
		printf("%d ", jump[i]);
	printf("\n");
}

int main()
{
	int r, c;
	scanf("%d%d", &r, &c);
	int *jump = createJumps(r, c);

	int n = r * c;
	printf("%d\n", n);
	stampa(jump,n);

	printf("con jumps: %d\n", bfs(jump,n,1));
	printf("senza jumps: %d\n", bfsSenzaSalti(jump,n,1));

	return 0;
}

int *createJumps(int r, int c)
{
	int n = r * c;
	int *jump = calloc(n + 1, sizeof(int)); //aggiunto n+1 perchè vogliamo avere indici da 1 a n compresi

	int s, m, t;
	scanf("%d", &s);
	while (s > 0)
	{
		scanf("%d%d", &m, &t);
		jump[m] = t; //scambiati m e t (da mouth vado a t)
		s--;		 //aggiunto decremento altrimenti era un ciclo infinito
	}

	int l, start, len;
	scanf("%d", &l);
	for (int i = 0; i < l; i++)
	{
		scanf("%d%d", &start, &len);
		int row, col, end;
		row = r - 1 - (start - 1) / c;
		col = (start - 1) % c;
		if ((row + r) % 2 == 0)
			col = c - col - 1; //aggiunto -1

		row = row - len + 1;
		end = c * (r - row);
		if ((row + r) % 2 == 0)
			end -= col;
		else
			end += col - c + 1;

		jump[start] = end;
	}

	return jump;
}

int move(int *jump, int casella, int tiro, int dimensioneCampo)
{
	casella += tiro;
	if (casella > dimensioneCampo)
	{
		return -1;
	}
	else
	{
		if (jump[casella] == 0)
			return casella;
		else
			return jump[casella];
	}
}

/*  
funzione BFS(G,v):
2      crea coda Q
3      inserisci v in Q
4      marca v
5      while Q non è vuota:
6          t ← Q.toglidallacoda()
7          if t è quello che stavamo cercando:
8              return t
9          for all lati e in G.latiincidenti(t) do
12             u ← G.nodiadiacenti(t,e)
13             if u non è marcato:
14                  marca u
15                  inserisci u in Q
16     return none
*/

void initializeToNegativeOne(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = -1;
	}
}

int bfs(int *jump, int size, int start)
{
	Queue q = NULL;
	enqueue(&q, start);

	int *dist = malloc(sizeof(int) * (size + 1));
	initializeToNegativeOne(dist, size + 1);

	dist[start] = 0;
	int curr;

	while (!emptyq(q))
	{
		curr = dequeue(&q);

		for (int i = 1; i <= 6; i++)
		{
			int casellaArrivo = move(jump, curr, i, size);
			if (dist[casellaArrivo] != -1 || casellaArrivo < 0)
				continue;

			dist[casellaArrivo] = dist[curr] + 1;

			if(casellaArrivo == size){
				return dist[casellaArrivo];
			}else{
				enqueue(&q,casellaArrivo);
			}

		}
		stampa(dist,size-1);
	}
	return dist[size];
}


int moveSenzaSalti(int *jump, int casella, int tiro, int dimensioneCampo)
{
	casella += tiro;
	if (casella > dimensioneCampo)
	{
		return -1;
	}
	else
	{
		if (jump[casella] == 0)
			return casella;
		else
			return -1;
	}
}

/*  
funzione BFS(G,v):
2      crea coda Q
3      inserisci v in Q
4      marca v
5      while Q non è vuota:
6          t ← Q.toglidallacoda()
7          if t è quello che stavamo cercando:
8              return t
9          for all lati e in G.latiincidenti(t) do
12             u ← G.nodiadiacenti(t,e)
13             if u non è marcato:
14                  marca u
15                  inserisci u in Q
16     return none
*/


int bfsSenzaSalti(int *jump, int size, int start)
{
	Queue q = NULL;
	q = enqueue(q, start);

	int *dist = malloc(sizeof(int) * (size + 1));
	initializeToNegativeOne(dist, size + 1);

	dist[start] = 0;
	int curr;

	while (!emptyq(q))
	{
		curr = dequeue(&q);

		for (int i = 1; i <= 6; i++)
		{
			int casellaArrivo = moveSenzaSalti(jump, curr, i, size);
			if (dist[casellaArrivo] != -1 || casellaArrivo < 0)
				continue;

			dist[casellaArrivo] = dist[curr] + 1;

			if(casellaArrivo == size){
				return dist[casellaArrivo];
			}else{
				q = enqueue(q,casellaArrivo);
			}

		}
	}
	return dist[size];
}