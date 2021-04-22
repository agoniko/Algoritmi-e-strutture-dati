
#include <stdio.h>

int moltiplicazione(int a, int b)
{
    int cont = 0;
    int prod = 0;
    cont++;
    while (b > 0)
    {
        cont++;
        prod += a;
        cont++;
        b--;
        cont++;
    }
    printf("Istruzioni eseguite: %d \n", cont+2);
    return prod;
}

int main()
{
    printf("Hello World\n");
    printf("Risultato: %d\n", moltiplicazione(5, 2));
}
