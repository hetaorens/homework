 
#define ERROR 0
#define OK 1
#define Overflower 2
#define Underflow 3
#define NorPresent 4
#define Duplicate 5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElemType;
typedef int Status;

typedef struct node
{
    ElemType elememt;
    struct node *link;
} Node;

typedef struct headerList
{
    Node *head;
    int n;
} HeaderList;

Status Init(HeaderList *L)
{
    L->head = (Node *)malloc(sizeof(Node));
    if (!L->head)
        return ERROR;
    L->head->link = NULL;
    L->n = 0;
    return OK;
}

Status Find(HeaderList *L, int i, ElemType *x)
{
    Node *p;
    if (i < 0 || i > L->n - 1)
        return ERROR;
    p = L->head->link;
    for (int j = 0; j < i; ++j)
        p = p->link;
    *x = p->elememt;
    return OK;
}

Status Insert(HeaderList *L, int i, ElemType x)
{
    Node *p, *q;
    if (i < -1 || i > L->n - 1)
        return ERROR;
    p = L->head;
    for (int j = 0; j <= i; ++j)
        p = p->link;
    q = (Node *)malloc(sizeof(Node));
    q->elememt = x;
    q->link = p->link;
    p->link = q;
    ++L->n;
    return OK;
}

Status Delete(HeaderList *L, int i)
{
    Node *p, *q;
    if (!L->n)
        return ERROR;
    if (i < 0 || i > L->n - 1)
        return ERROR;
    p = L->head;
    q = L->head;
    for (int j = 0; j < i; ++j)
        p = p->link;
    q = p->link;
    p->link = q->link;
    free(q);
    --L->n;
    return OK;
}

Status OutPut(HeaderList *L)
{
    Node *p;
    if (!L->n)
        return ERROR;
    p = L->head->link;
    while (p)
    {
        printf("%d, ", p->elememt);
        p = p->link;
    }
    printf("\n");
    return OK;
}

Status Destory(HeaderList *L)
{
    Node *p, *q;
    p = L->head;
    while (L->head)
    {
        p = L->head->link;
        free(L->head);
        L->head = p;
    }
    return OK;
}

void Reverse(HeaderList *L)
{
    Node *p, *q, *t;
    p = L->head->link;
    q = p->link;
    p->link = NULL;
    while (q)
    {
        t = q;
        q = q->link;
        t->link = p;
        p = t;
    }
    L->head->link = t;
}

int CmpIncrease(Node *node1, Node *node2)
{
    return node1->elememt > node2->elememt ? 1 : 0;
}

int CmpDecrease(Node *node1, Node *node2)
{
    return node1->elememt < node2->elememt ? 1 : 0;
}

void QSort(Node *head, Node *Left, Node *Right, int (*cmp)(Node *, Node *))
{
    if (Left == Right)
        return;
    Node *MidNode, *p, *t;
    MidNode = Left;
    p = Left->link;
    Node *Lp, *Rp;
    Node L, R;
    Lp = &L;
    Rp = &R;
    while (p != Right)
    {
        if (cmp(MidNode, p))
        {
            Lp->link = p;
            Lp = p;
        }
        else
        {
            Rp->link = p;
            Rp = p;
        }
        p = p->link;
    }
    if (cmp(MidNode, p))
    {
        Lp->link = p;
        Rp->link = p->link;
        Lp = p;
    }
    else
    {
        Rp->link = p;
        Rp = p;
    }
    Lp->link = MidNode;
    MidNode->link = R.link;
    head->link = L.link;
    if (Lp != &L)
        QSort(head, head->link, Lp, cmp);
    if (Rp != &R)
        QSort(MidNode, MidNode->link, Rp, cmp);
    return;
}

int check(HeaderList *L)
{
    Node *p;
    int t;
    p = L->head;
    t = p->elememt;
    p = p->link;
    while (p->link)
    {
        if (p->elememt < t)
        {
 
            getchar();
        }
        t = p->elememt;
        p = p->link;
    }
    return 0;
}

int main()
{
    srand(time(NULL));
    HeaderList List;
    Init(&List);
    for (int i = 0; i < 100; ++i)
    {
        Insert(&List, i - 1, rand());
    }
    OutPut(&List);
    Delete(&List, 0);
    OutPut(&List);
    Reverse(&List);
    OutPut(&List);
    Node *end;
    end = List.head;
    while (end->link)
        end = end->link;
    QSort(List.head, List.head->link, end, CmpIncrease);
    OutPut(&List);
    Destory(&List);
    getchar();
    return 0;
}
