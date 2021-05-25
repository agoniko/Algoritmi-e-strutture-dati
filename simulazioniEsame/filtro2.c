
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char *w;
    struct node *next;

} node;

typedef struct node *Node;

char *fstring(char *w, Node l)
{
    if (l->next == NULL)
        return strcat(w, l->w);

    return strcat(fstring(w, l->next), l->w);
}

Node flist(Node l)
{
    if (l->w[0] != '\0' && l->w[1] == '\0')
        return l;
    Node n = malloc(sizeof(struct node));
    n->w = (l->w) + 1;
    n->next = l;
    return flist(n);
}

char *cut(char *w){
    char *result = malloc(100*sizeof(char));
    int cont = 0;
    while(*(w+1) != '\0'){
        result[cont] = *w;
        w++;
        cont++;
    }
    return result;
}

Node flist2(Node l){
    if (l->w[0] != '\0' && l->w[1] == '\0')
        return l;
    Node n = malloc(sizeof(struct node));
    n->w = cut(l->w);
    n->next = l;
    return flist2(n);
}

Node build(char *w)
{
    Node lista = malloc(sizeof(struct node));
    lista->w = w;
    lista->next = NULL;
    return flist(lista);
}

Node build2(char *w)
{
    Node lista = malloc(sizeof(struct node));
    lista->w = w;
    lista->next = NULL;
    return flist2(lista);
}



char *strappend(char *dest, char *src)
{
    char *result = malloc(100 * sizeof(char));
    int cont = 0;
    while (*dest != '\0')
    {
        result[cont] = *dest;
        dest++;
        cont++;
    }
    while (*src != '\0')
    {
        result[cont] = *src;
        src++;
        cont++;
    }
    return result;
}

char *fstring_iter(char *w, Node l)
{

    char *result = "";
    while (l != NULL)
    {
        result = strappend(l->w, result);
        l = l->next;
    }
    result = strappend(w, result);
    return result;
}

int main()
{
    char stringa[100] = "kappa";
    Node n = build(stringa);
    char ap[10] = "";
    char *append = fstring_iter(ap, n);
    printf("%s\n", append);
    append = fstring(ap, n);
    printf("%s\n", append);
}