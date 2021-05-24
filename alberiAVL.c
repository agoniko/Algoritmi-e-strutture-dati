#include <stdio.h>
#include <stdlib.h>
#define COUNT 7
#define true 1
#define false 0

typedef int Item;

typedef struct node
{
    struct node *l, *r;
    Item item;
} node;

typedef int boolean;

typedef struct node *Btree;

int max(int a, int b);
Btree rightRotation(Btree node);
Btree leftRotation(Btree node);
int treeHeight(Btree b);
Btree search(Btree head, Item item);
Btree balanceTree(Btree head, Item item);

Btree new_node(Item item)
{
    Btree b = malloc(sizeof(Btree));
    b->item = item;
    b->l = NULL;
    b->r = NULL;
    return b;
}

Btree search(Btree head, Item item)
{
    if (head != NULL)
    {
        Item i = head->item;
        if (i == item)
            return head;
        if (i > item)
            return search(head->l, item);
        if (i < item)
            return search(head->r, item);
    }
    return NULL;
}
Btree minValueNode(Btree node) {
  Btree current = node;

  while (current->l != NULL)
    current = current->l;

  return current;
}
int getBalance(Btree node){
    if(node == NULL)
        return 0;
    return treeHeight(node->l) - treeHeight(node->r);
}

Btree deleteNode(Btree root, int item) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (item < root->item)
    root->l = deleteNode(root->l, item);

  else if (item > root->item)
    root->r = deleteNode(root->r, item);

  else {
    if ((root->l == NULL) || (root->r == NULL)) {
      Btree temp = root->l ? root->l : root->r;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        root = temp;
      free(temp);
    } else {
      Btree temp = minValueNode(root->r);

      root->item = temp->item;

      root->r = deleteNode(root->r, temp->item);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  
  int balance = treeHeight(root->l) - treeHeight(root->r);
  if (balance > 1 && getBalance(root->l) >= 0)
    return rightRotation(root);

  if (balance > 1 && getBalance(root->l) < 0) {
    root->l = leftRotation(root->l);
    return rightRotation(root);
  }

  if (balance < -1 && getBalance(root->r) <= 0)
    return leftRotation(root);

  if (balance < -1 && getBalance(root->r) > 0) {
    root->r = rightRotation(root->r);
    return leftRotation(root);
  }

  return root;
}

Btree insert_Node(Btree head, Item item)
{
    if (head == NULL)
    {
        return new_node(item);
    }
    else if (head->item >= item)
    {
        head->l = insert_Node(head->l, item);
    }
    else
    {
        head->r = insert_Node(head->r, item);
    }
    return balanceTree(head,item);
}

Btree balanceTree(Btree head, Item item)
{
    int balance = treeHeight(head->l) - treeHeight(head->r);
    // If this node becomes unbalanced, then
    // there are 4 cases

    // l l Case
    if (balance > 1 && item <= head->l->item)
        return rightRotation(head);

    // r r Case
    if (balance < -1 && item >= head->r->item)
        return leftRotation(head);

    // l r Case
    if (balance > 1 && item >= head->l->item)
    {
        head->l = leftRotation(head->l);
        return rightRotation(head);
    }

    // r l Case
    if (balance < -1 && item <= head->r->item)
    {
        head->r = rightRotation(head->r);
        return leftRotation(head);
    }

    /* return the (unchanged) node pointer */
    return head;
}

void print_inorder(Btree head)
{
    if (head != NULL)
    {
        print_inorder(head->l);
        printf("%d ", head->item);
        print_inorder(head->r);
    }
}

void print2DUtil(Btree root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process r child first
    print2DUtil(root->r, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->item);

    // Process l child
    print2DUtil(root->l, space);
}

int treeHeight(Btree b)
{
    if (b == NULL)
        return 0;
    int leftH = treeHeight(b->l);
    int rightH = treeHeight(b->r);
    return 1 + max(leftH, rightH);
}

boolean isBilanciato(Btree head)
{
    int l = treeHeight(head->l);
    int r = treeHeight(head->r);
    if (abs(l - r) > 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Btree rightRotation(Btree node)
{
    Btree x = node->l;
    Btree T2 = x->r;

    x->r = node;
    node->l = T2;

    return x;
}

Btree leftRotation(Btree node)
{
    Btree y = node->r;
    Btree T2 = y->l;

    y->l = node;
    node->r = T2;

    return y;
}

void preOrder(Btree root)
{
    if (root != NULL)
    {
        printf("%d ", root->item);
        preOrder(root->l);
        preOrder(root->r);
    }
}

int main()
{
    boolean exit = false;
    Btree father = NULL;

    while (exit == false)
    {
        printf("Inserisci un numero, -1 per terminare: ");
        Item i;
        scanf("%d", &i);
        if (i == -1)
            exit = true;
        else
        {
            father = insert_Node(father, i);
            print2DUtil(father, 0);
            printf("\n--------------------------------------------------------\n");
        }
    }
    printf("Inserisci un numero da eliminare: ");
    Item i;
    scanf("%d", &i);
    father = deleteNode (father, i);
    print2DUtil(father, 0);
}