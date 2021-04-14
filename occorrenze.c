#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define length 10

typedef struct occorrenza
{
    char word[length];
    int qnt;
} occorrenza;
typedef struct occorrenza *Occorrenza;
typedef struct node
{
    Occorrenza occ;
    struct node *l;
    struct node *r;
} node;

typedef struct node *BistNode;

void bist_orderprint(BistNode p);
void bist_invorderprint(BistNode p);

Occorrenza newOccorrenza(char word[10])
{
    Occorrenza o = malloc(sizeof(Occorrenza));
    strcpy(o->word, word);
    o->qnt = 1;
    return o;
}

BistNode newNode(char word[length])
{
    BistNode n = malloc(sizeof(BistNode));
    n->occ = newOccorrenza(word);
    n->l = NULL;
    n->r = NULL;
    return n;
}

BistNode bistInsert(BistNode n, char word[length])
{
    if (n == NULL)
    {
        n = newNode(word);
        return n;
    }
    if (strcmp(n->occ->word, word) == 0)
    {
        n->occ->qnt++;
    }
    else if (strcmp(n->occ->word, word) < 0)
    {
        n->r = bistInsert(n->r, word);
    }
    else
    {
        n->l = bistInsert(n->l, word);
    }
    return n;
}

void bist_orderprint(BistNode n)
{
    if (n == NULL)
        return;
    bist_orderprint(n->l);
    printf("%s: %d\n", n->occ->word, n->occ->qnt);
    bist_orderprint(n->r);
}
void bist_invorderprint(BistNode n)
{
    if (n == NULL)
        return;
    bist_invorderprint(n->r);
    printf("%s: %d\n", n->occ->word, n->occ->qnt);
    bist_invorderprint(n->l);
}

BistNode search(BistNode n, char word[length])
{
    if (n == NULL)
    {
        return NULL;
    }
    if (strcmp(n->occ->word, word) == 0)
    {
        return n;
    }
    else if (strcmp(n->occ->word, word) < 0)
    {
        search(n->r, word);
    }
    else
    {
        search(n->l, word);
    }
}
void toLower(char *s)
{
    int i;
    for (i = 0; i < strlen(s); i++)
        // Se il carattere corrispondente della stringa è
        // un carattere maiuscolo, ovvero è compreso tra A e Z...

        if ((s[i] >= 'A') && (s[i] <= 'Z'))
            s[i] += 32; // spazio che esiste in codice ASCII tra i caratteri maiuscoli e minuscoli
}

int main()
{
    printf("Inserisci testo qui di seguito: \n");
    char *testo = malloc(1000 * sizeof(char));
    fgets(testo, 100, stdin);
    char *p = strtok(testo, " ");
    char buff[length];
    BistNode head = NULL;

    while(scanf("%s",testo) == 1){
        printf("%s",testo);
    }



    /*
    while (p != NULL)
    {
        char *capo = strchr(p, '\n');
        if (capo != NULL)
        {
            *capo = '\0';
        }
        capo = strchr(p, ',');
        if (capo != NULL)
        {
            *capo = '\0';
        }
        capo = strchr(p, '.');
        if (capo != NULL)
        {
            *capo = '\0';
        }
        strcpy(buff, p);
        toLower(buff);
        head = bistInsert(head, buff);
        p = strtok(NULL, " ");
    }

    bist_orderprint(head);*/
}
