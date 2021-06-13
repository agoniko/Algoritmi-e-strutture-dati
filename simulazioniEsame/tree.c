#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct bitnode
{
    int val;
    struct bitnode *left, *right;
};

typedef struct bitnode *Node;

Node addNode(Node root, int v)
{
    if (root == NULL)
    {
        root = malloc(sizeof(Node));
        root->val = v;
        root->left = root->right = NULL;
    }
    else
    {
        if (root->val < v)
        {
            root->right = addNode(root->right, v);
        }
        else
        {
            root->left = addNode(root->left, v);
        }
    }
    return root;
}

void printInorder(Node root)
{
    if (root != NULL)
    {
        printInorder(root->left);

        printf("%d ", root->val);
        printInorder(root->right);
    }
}

//non funziona perchè salta alcuni
//rami dato che chiama direttamente il ramo root->left->left
// ma non root->left->right
void incrementa(Node root)
{
    if (root != NULL)
    {
        root->val++;
        if (root->left != NULL)
        {
            root->left->val++;
            incrementa(root->left->left);
        }
        if (root->right != NULL)
        {
            root->right->val++;
            incrementa(root->right->right);
        }
    }
}

void incrementaFunzionante(Node root)
{
    if (root != NULL)
    {
        root->val++;
        incrementaFunzionante(root->left);
        incrementaFunzionante(root->right);
    }
}

void print(int *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

Node creaAlberoDaPreOrderVector(int *a, int size)
{
    Node root = NULL;
    root = addNode(root, a[0]);
    
}

int main(void)
{
    srand(time(0));
    Node root = NULL;
    int a[9] = {28, 17, 10, 15, 25, 23, 36, 34, 44};

    return (0);
}