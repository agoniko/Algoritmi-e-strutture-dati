#include <stdio.h>
#include <stdlib.h>

int maxLengthSubVect(int *v, int size)
{
    int max = 1;
    int cont = 1;
    for (int i = 1; i < size; i++)
    {
        if (v[i] >= v[i - 1])
        {
            cont++;
            if (cont > max)
                max = cont;
        }else{
            cont = 1;
        }
    }
    return max;
}

int main()
{
    int n;
    scanf("%d", &n);
    int v[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    printf("%d\n", maxLengthSubVect(v, n));

    return 0;
}