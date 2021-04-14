#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    int info;
    struct node *next;
};

typedef struct node *Node;
Node search(Node n, int info)
{
    while (n != NULL && n->info != info)
    {
        n = n->next;
    }
    return n;
}

void insert_after(Node first, int info)
{
    if (search(first, info) != NULL)
        return;
    Node n = first;
    while (n->next != NULL)
    {
        n = n->next;
    }
    Node new = malloc(sizeof(Node));
    n->next = new;
    new->info = info;
    new->next = NULL;
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

void print_menu()
{
    printf("----------------------MENU-------------------------\n");
    printf("|+ n: Inserisci un numero all'insieme             |\n");
    printf("|- n: Elimina un numero dall'insieme (se presente)|\n");
    printf("|? n: Cerca l'elemento nell'insieme               |\n");
    printf("|  c: Stampa il numero di elementi nell'insisme   |\n");
    printf("|  p: Stampa gli elementi dell'insieme            |\n");
    printf("|  d: Cancella tutti gli elementi dell'insieme    |\n");
    printf("|  f: Termina l'esecuzione                        |\n");
    printf("---------------------------------------------------\n");
    printf("*nota: non puoi inserire zero e il numero può avere al massimo 7 cifre\n");
    printf("\n\n");
    printf("Inserisci comando: ");
}

int conta_elementi(Node head)
{
    Node n = head;
    int cont = 0;
    while (n != NULL)
    {
        cont++;
        n = n->next;
    }
    return cont;
}

//elimina tutti gli elementi e restituisce una nuova testa
Node delete_all(Node head)
{
    Node n = head;
    while (n != NULL)
    {
        free(head);
        n = n->next;
        head = n;
    }
    Node newHead = malloc(sizeof(Node));
    newHead->info = 0;
    newHead->next = NULL;
}

int main()
{

    Node n = malloc(sizeof(Node));
    Node head = n;

    int esci = 0;
    while (esci == 0)
    {
        print_menu();
        char *input = malloc(10 * sizeof(char));
        fgets(input, 10, stdin);
        char sub[10];
        memcpy(sub, &input[1], 8);
        sub[9] = '\0';
        int n = atoi(sub);

        switch (input[0])
        {
        case '+':
            insert_after(head, n);
            break;
        case '-':
            delete (head, n);
            break;
        case '?':
            if (search(head, n) != NULL)
            {
                printf("Elemento presente\n");
            }
            else
            {
                printf("Elemento non presente\n");
            }
            break;
        case 'c':
            printf("Nell'insieme ci sono %d elementi\n", conta_elementi(head));
            break;
        case 'p':
            print_list(head);
            break;
        case 'd':
            head = delete_all(head);
            break;
        case 'f':
            printf("Arrivederci\n");
            esci = 1;
            break;
        default:
            printf("Input non valido, riprovare\n");
            break;
        }
    }
}