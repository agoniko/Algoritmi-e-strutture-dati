#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree
{
    int val;
    struct tree **son;
    int n;
    int i;
    bool tele;
} tree;
typedef struct tree *Tree;

Tree createTree()
{
    Tree s0 = malloc(sizeof(Tree));
    s0->val = 1;
    s0->son = calloc(1, sizeof(Tree));
    Tree s1 = malloc(sizeof(Tree));
    s0->son[0] = s1;
    s1->val = 1;
    s1->son = calloc(3, sizeof(Tree));
    Tree s2, s3, s4;
    s2 = malloc(sizeof(Tree));
    s2->val = 1;
    s2->son = NULL;
    s4 = malloc(sizeof(Tree));
    s4->val = 1;
    s4->son = NULL;
    s3 = malloc(sizeof(Tree));
    s3->val = 100;
    s3->son = calloc(3, sizeof(Tree));
    s1->son[0] = s2;
    s1->son[1] = s3;
    s1->son[2] = s4;
    Tree s5, s6, s7;
    s5 = malloc(sizeof(Tree));
    s5->val = 2;
    s5->son = NULL;
    s6 = malloc(sizeof(Tree));
    s6->val = 99;
    s6->son = NULL;
    s7 = malloc(sizeof(Tree));
    s7->val = 2;
    s7->son = NULL;
    s3->son[0] = s5;
    s3->son[1] = s6;
    s3->son[2] = s7;
    s0->n = 1;
    s1->n = 3;
    s2->n = 0;
    s3->n = 3;
    s4->n = 0;
    s5->n = 0;
    s6->n = 0;
    s7->n = 0;
    return s0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int postOrder(Tree t, bool prendi)
{
    if (t->n == 0)
    {
        if (prendi)
        {
            t->i = t->val;
            return t->val;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        int presi = 0;
        int nonPresi = 0;
        bool preso = false;
        for (int i = 0; i < t->n; i++)
        {
            if (prendi)
            {
                presi += postOrder(t->son[i], false);
                nonPresi += postOrder(t->son[i], true);
            }
            else
            {
                nonPresi += postOrder(t->son[i], true);
            }
        }
        if (prendi)
        {
            int a = max(presi + t->val, nonPresi);
            t->i = a;
            return a;
        }
        else
        {
            t->i = nonPresi;
            return nonPresi;
        }
    }
}

void printPreOrder(Tree t)
{
    if (t == NULL)
        return;
    printf("%d : %d\n", t->val, t->tele);
    for (int i = 0; i < t->n; i++)
    {
        printPreOrder(t->son[i]);
    }
}

int maxVal(Tree t)
{
    return max(postOrder(t, true), postOrder(t, false));
}

void assegna(Tree t, bool prendi)
{
    if (prendi)
    {
        int v = 0;
        for (int i = 0; i < t->n; i++)
        {
            v += t->son[i]->i;
        }
        if (t->i > v)
        {
            t->tele = true;
            for (int i = 0; i < t->n; i++)
            {
                assegna(t->son[i], false);
            }
        }else{
            t->tele = false;
            for(int i = 0; i<t->n; i++){
                assegna(t->son[i],true);
            }
        }
    }
    else
    {
        t->tele = false;
        for (int i = 0; i < t->n; i++)
        {
            assegna(t->son[i], true);
        }
    }
}

int main(void)
{
    Tree s0 = createTree();
    printf("val %d\n", maxVal(s0));
    assegna(s0,true);
    printPreOrder(s0);
    return (0);
}
