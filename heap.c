#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

typedef int Item;
typedef Item *Heap;

void swap(Heap h, int i, int j);
int father(int i);
int cmp(Item a, Item b);
void heapify_up(Heap h, int i);

struct pqueue
{
    Heap heap;
    int size, count;
} pqueue;

typedef struct pqueue *Pqueue;

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

Bitnode bit_new(Item item)
{
    Bitnode new = malloc(sizeof(Bitnode));
    new->item = item;
    new->l = new->r = NULL;
    return new;
}

void stampa(Heap h, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d-> %d ", i, h[i]);
    }
    printf("\n");
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

int father(int i)
{
    if (i > 1)
    {
        return i / 2;
    }
    return i;
}

int cmp(Item a, Item b)
{
    if (a < b)
        return -1;
    if (a == b)
        return 0;
    if (a > b)
        return 1;
}

void heapify_up(Heap h, int i)
{
    if (i > 1)
    {
        int j = father(i);
        if (cmp(h[i], h[j]) < 0)
        {
            swap(h, i, j);
            heapify_up(h, j);
        }
    }
}

void heapify_down(Heap h, int i, int n)
{
    //i ha almeno un figlio
    if (i * 2 <= n)
    {
        int j;
        if (i * 2 == n)
        {
            //i ha solo il figlio sinistro
            j = 2 * i;
        }
        else
        {
            j = cmp(h[2 * i], h[2 * i + 1]) < 0 ? 2 * i : 2 * i + 1;
        }

        if (cmp(h[j], h[i]) < 0)
        {
            swap(h, i, j);
            heapify_down(h, j, n);
        }
    }
}

void swap(Heap h, int i, int j)
{
    Item ap = h[i];
    h[i] = h[j];
    h[j] = ap;
}

int main()
{
    Heap h = malloc(100 * sizeof(Item));
    h[1] = 1;
    h[2] = 2;
    h[3] = 5;
    h[4] = 10;
    h[5] = 3;
    h[6] = 7;
    h[7] = 11;
    h[8] = 15;
    h[9] = 17;
    h[10] = 20;
    h[11] = 9;
    h[12] = 15;
    h[13] = 8;
    h[14] = 16;
    h[15] = 4;

    Bitnode b = bit_arr2tree(h, 16, 0);
    print2DUtil(b, 0);
    printf("-------------------------------------------------------\n");
    int i = 2;
    int n = 16;
    swap(h, n-1, i);
    n--;
    int j = father(i);
    if (cmp(h[i], h[j]) < 0)
    {
        printf("up\n");
        heapify_up(h, i);
    }
    else if (cmp(h[i], h[i * 2]) > 0 || cmp(h[i], h[i * 2 + 1]) > 0)
    {
        printf("down\n");
        heapify_down(h, i, n);
    }
    b = bit_arr2tree(h, n, 0);
    print2DUtil(b, 0);
}
