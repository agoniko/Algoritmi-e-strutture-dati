#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node *l, *r;
};

typedef struct node *Node;

Node new_node(int v)
{
    Node n = malloc(sizeof(Node));
    n->val = v;
    n->l = NULL;
    n->r = NULL;
}

Node creaAlbero(int *arr, int size, int cont)
{
    if (cont >= size)
        return NULL;
    if (arr[cont] == 0)
        return NULL;
    Node root = new_node(arr[cont]);
    root->l = creaAlbero(arr, size, cont * 2 + 1);
    root->r = creaAlbero(arr, size, cont * 2 + 2);
    return root;
}

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

void printAsSummary(Node root, int spaces)
{
    printSpaces(spaces);
    printf("*");
    if (root != NULL)
    {
        printf("%d\n", root->val);
        if (root->l != NULL)
        {
            printAsSummary(root->l, spaces + 2);
            printAsSummary(root->r, spaces + 2);
        }
    }
    else
    {
        printf("\n");
    }
}

void riempi(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int costoMax(Node root)
{
    if (root == NULL)
        return 0;
    return root->val + max(costoMax(root->l), costoMax(root->r));
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int arr[n];
    riempi(arr, n);
    Node root = creaAlbero(arr, n, 0);
    printAsSummary(root, 0);
    printf("%d\n",costoMax(root));
    return (0);
}