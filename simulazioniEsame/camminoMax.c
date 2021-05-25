/* alberi binari */

#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *left;
    struct node *right;
    int key;
};

typedef struct node *Bit_node;

Bit_node bit_new(int k)
{
    Bit_node new = malloc(sizeof(struct node));

    if (new == NULL)
    {
        printf("err malloc\n");
        exit(-1);
    }

    new->left = new->right = NULL;
    new->key = k;
    return new;
}

// stampa (ricorsivamente) l'albero binario di radice p in forma di sommario
void bit_printassummary(Bit_node p, int spaces)
{
    int i;
    for (i = 0; i < spaces; i++)
        printf("  ");
    printf("*");

    if (p)
    {
        printf("%d\n", p->key);
        if (p->left || p->right)
        {
            bit_printassummary(p->left, spaces + 1);
            bit_printassummary(p->right, spaces + 1);
        }
    }
    else
        printf("\n");
}

// costruisce (ricorsivamente) un albero binario a partire dalle n chiavi contenute nel vettore a, partendo dalla posizione i
// per ogni indice i < n, i figli del nodo di chiave a[i] hanno chiavi a[2*i+1] e a[2*i+2].
Bit_node bit_arr2tree(int *a, int n, int i)
{
    Bit_node p = NULL;

    if (i >= n)
        return NULL;

    if (a[i] > 0)
    {
        p = bit_new(a[i]);
        p->left = bit_arr2tree(a, n, 2 * i + 1);
        p->right = bit_arr2tree(a, n, 2 * i + 2);
    }

    return p;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int costoMax(Bit_node root)
{
    if (root == NULL)
        return 0;
    int cost = root->key;
    return cost + max(costoMax(root->left), costoMax(root->right));
}

int main()
{
    int n;
    printf("Quante foglie deve avere l'albero? ");
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    Bit_node root = bit_arr2tree(a, n, 0);

    bit_printassummary(root, 0);
    printf("\n");
    printf("%d\n", costoMax(root));

    return 0;
}