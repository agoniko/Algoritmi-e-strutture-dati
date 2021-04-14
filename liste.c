#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *next;
};

typedef struct node *Node;

Node insert_before(Node first, int info)
{
    Node new = malloc(sizeof(Node));
    new->info = info;
    new->next = first;
    return new;
}

Node insert_after(Node first, int info)
{
    Node n = first;
    while (n->next != NULL)
    {
        n = n->next;
    }
    Node new = malloc(sizeof(Node));
    n->next = new;
    new->info = info;
    new->next = NULL;
    return new;
}

Node search(Node n, int info)
{
    while (n != NULL && n->info != info)
    {
        n = n->next;
    }
    return n;
}

void delete (Node head, int info)
{
    Node prev = NULL, curr = head;
    while (curr != NULL && curr->info != info)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL)
    {
        head = head->next;
        free(curr);
    }
    else if (curr != NULL)
    {
        prev->next = curr->next;
        free(curr);
    }
}

Node olist_insert(Node n, int info)
{
    Node head = n;
    Node new = malloc(sizeof(Node));
    new->next = NULL;
    new->info = info;
    Node prev = NULL;
    while (n != NULL && n->info < info)
    {
        prev = n;
        n = n->next;
    }
    if (prev == NULL)
    {
        new->next = n;
        return new;
    }
    else
    {
        prev->next = new;
        new->next = n;
        return head;
    }
}

//inserisce l'elemento nella giusta posizione e restituisce il primo elemento della lista della lista
Node olist_search(Node head, int info)
{
    Node n = head;
    while (n != NULL && n->info <= info)
    {
        if (n->info == info)
        {
            return n;
        }
        n = n->next;
    }
    return NULL;
}

void print_list(Node head)
{
    Node n = head;
    while (n != NULL)
    {
        printf("%d -> ", n->info);
        n = n->next;
    }
    printf("\n");
}

int main()
{
    Node n = malloc(sizeof(Node));
    n->next = NULL;
    n->info = 0;
    Node head = n;
    for (int i = 2; i < 5; i = i + 2)
    {
        head = olist_insert(n, i);
    }
    print_list(head);
    head = olist_insert(head, -1);
    //delete(head,2);
    print_list(head);
    Node ricercato = olist_search(head, 1);
    if (ricercato != NULL)
    {
        printf("elemento trovato\n");
    }
    else
    {
        printf("Elemento non trovato\n");
    }
}