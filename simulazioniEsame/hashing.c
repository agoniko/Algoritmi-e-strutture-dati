#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define print(x) printf("%d ", x);
#define MAX 5

struct hashTable
{
    bool presente;
    struct hashTable *next;
};

typedef struct hashTable **Hash;

Hash createTable(int *b, int m)

{
    Hash table = calloc(MAX,sizeof(Hash));
    for (int i = 0; i < m; i++)
    {
        if (table[b[i]] == NULL)
        {
            table[b[i]] = malloc(sizeof(struct hashTable));
            table[b[i]]->presente = true;
        }
    }
    return table;
}

void riempiRandom(int *a, int size){
    for(int i = 0; i<size; i++){
        a[i] = rand()%MAX;
        print(a[i]);
    }
    printf("\n");
}

void printTable(Hash table, int m){
    for(int i = 0; i<MAX; i++){
        if(table[i] != NULL){
            print(i);
        }
    }
}

bool cerca(int a[], int b[], int n, int m){
    Hash table = createTable(b,m);
    bool found = true;
    for(int i = 0; i<n; i++){
        if(table[a[i]] == NULL){
            found = false; 
        }
        if(!found){
            return found;
        }
    }
    return found;
}

int main(void)
{
    srand(time(0));
    int n = 3;
    int m = 5;
    int a[n],b[m];
    riempiRandom(a,n);
    riempiRandom(b,m);
    
    print(cerca(a,b,n,m));
    
    return (0);
}