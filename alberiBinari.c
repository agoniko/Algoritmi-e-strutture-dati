#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 10
#define COUNT 10

typedef int Item;
typedef struct bit_node
{
    Item item;
    struct bit_node *l, *r;
} bit_node;

typedef struct bit_node *Bitnode;

Bitnode bit_new(Item);
void bit_printAsSummary(Bitnode p, int spaces);
void bit_preorder(Bitnode);
void bit_inorder(Bitnode);
void bit_postorder(Bitnode);

void bit_preorder(Bitnode p)
{
    if (p == NULL)
        return;
    printf("%d ", p->item);
    bit_preorder(p->l);
    bit_preorder(p->r);
}

void bit_inorder(Bitnode p)
{
    if (p == NULL)
        return;
    bit_inorder(p->l);
    printf("%d ", p->item);
    bit_inorder(p->r);
}

void bit_postorder(Bitnode p)
{
    if (p == NULL)
        return;
    bit_postorder(p->l);
    bit_postorder(p->r);
    printf("%d ", p->item);
}

void print2DUtil(Bitnode root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->r, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->item);

    // Process left child
    print2DUtil(root->l, space);
}

void bit_printAsSummary(Bitnode p, int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    printf("*");
    if (p != NULL)
    {
        printf("%d\n", p->item);
        spaces += 2;
        bit_printAsSummary(p->l, spaces);
        bit_printAsSummary(p->r, spaces);
    }
    else
    {
        printf("\n");
    }
}

void riempiArrayRandom(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }
}

Bitnode bit_new(Item item)
{
    Bitnode new = malloc(sizeof(Bitnode));
    new->item = item;
    new->l = new->r = NULL;
    return new;
}

Bitnode bit_arr2tree(Item a[], int n, int i)
{
    if (i == 0)
    {
        Bitnode head = bit_new(a[0]);
        head->l = bit_arr2tree(a, n, 1);
        head->r = bit_arr2tree(a, n, 2);
        return head;
    }
    else
    {
        Bitnode temp = bit_new(a[i]);
        if (i < n / 2)
            temp->l = bit_arr2tree(a, n, i * 2 + 1);
        if (i < n / 2 - 1)
            temp->r = bit_arr2tree(a, n, i * 2 + 2);
        return temp;
    }
}

void StampaAlbero(Bitnode a)
{
    if (a == NULL)
    {
        printf("()");
        return;
    }

    printf("( %d ", a->item);
    StampaAlbero(a->l);
    StampaAlbero(a->r);
    printf(" ) ");
}

void stampa(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
int main()
{
    Item a[size] = {69, 89, 28, 39, 66, 44, 12, 2, 71};
    //riempiArrayRandom(a, size);
    //stampa(a, size-1);
    //Bitnode c = bit_new(a[0]);
    Bitnode b = bit_arr2tree(a, size, 0);
    bit_preorder(b);
    printf("\n");
    bit_inorder(b);
    printf("\n");
    bit_postorder(b);
    printf("\n");
}