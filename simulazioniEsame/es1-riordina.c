#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void stampa(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void scambia(int *a, int i, int j){
    int ap = a[i];
    a[i] = a[j];
    a[j] = ap;
}

void riordina(int *a, int size){
    bool scambiato = true;
    int n = size -1;
    int cont = 0;
    while(scambiato){
        scambiato = false;
        for(int i = 0; i<n; i++){
            if(a[i] > a[i+1]){
                scambia(a,i,i+1);
                scambiato = true;
            }
            cont++;
        }
        n--;
    }
    printf("connfronti: %d\n",cont);
}

int main(void)
{
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    stampa(a,n);
    riordina(a,n);
    stampa(a,n);
    return (0);
}
