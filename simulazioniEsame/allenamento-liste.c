#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node *next;
};

typedef struct node *Node;

Node new_node(int v)
{
    Node n = malloc(sizeof(Node));
    n->val = v;
    n->next = NULL;
    return n;
}

void printList(Node head)
{
    Node ap = head;
    while (ap != NULL)
    {
        printf("%d -> ", ap->val);
        ap = ap->next;
    }

    printf("\n");
}

Node move_to_front(Node head)
{
    Node p, q;
    q = NULL;
    p = head;
    while (p->next != NULL)
    {
        q = p;
        p = p->next;
    }
    q->next = NULL;
    p->next = head;
    head = p;
    return head;
}


int main(void)
{
    Node head = new_node(0);
    Node ap = head;
    for (int i = 1; i < 10; i++)
    {
        ap->next = new_node(i);
        ap = ap->next;
    }
    printf("%d \n",ap->val);
    printList(head);
    head = move_to_front(head);
    printList(head);
    return (0);
}