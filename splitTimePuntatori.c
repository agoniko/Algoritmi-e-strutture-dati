#include <stdio.h>

void split_time(long int tot_sec, int *h, int *m, int *s)
{
    *h = (int)tot_sec / 3600;
    tot_sec %= 3600;
    *m = tot_sec / 60;
    *s = tot_sec % 60;
    printf("%d %d %d", *h, *m, *s);
}

void scambia(int *p, int *q)
{
    int ap = *p;
    *p = *q;
    *q = ap;
}

int main()
{
    int h, m, s;
    long int tot_sec = 1835;
    split_time(tot_sec, &h, &m, &s);
    printf("\n%d %d %d", h, m, s);
    scambia(&m,&s);
    printf("\n%d %d %d", h, m, s);


}