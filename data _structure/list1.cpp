#define ERROR 0
#define OK 1
#define Overflower 2
#define Underflow 3
#define NorPresent 4
#define Duplicate 5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Status;
typedef int ElemType;

typedef struct seqlist
{
    int n;
    int maxlength;
    ElemType *elememt;
} SeqList;

Status Init(SeqList *L, int mSize)
{
    L->maxlength = mSize;
    L->n=0;
    L->elememt = (ElemType *)malloc(sizeof(ElemType) * mSize);
    if (!L->elememt)
        return ERROR;
    return OK;
}

Status Find(SeqList *L, int i, ElemType *x)
{
    if (i < 0 || i > L->n - 1)
        return ERROR;
    *x = L->elememt[i];
    return OK;
}

Status Insert(SeqList *L, int i, ElemType x)
{
    int j;
    if (i < -1 || i > L->n-1)
        return ERROR;
    if (L->n == L->maxlength)
        return ERROR;
    for (j = L->n-1; j > i; --j)
        L->elememt[j + 1] = L->elememt[j];
    L->elememt[i + 1] = x;
    L->n = (L->n + 1);
    return OK;
}

Status Output(SeqList *L)
{
    if (L->n == 0)
        return ERROR;
    for (int i = 0; i < L->n; ++i)
        printf("%d, ", L->elememt[i]);
    printf("\n");
    return OK;
}

Status Delete(SeqList *L, int i)
{
    int j;
    if (i < 0 || i > L->n-1)
        return ERROR;
    if (!L->n)
        return ERROR;
    for (j = i + 1; j < L->n; ++j)
        L->elememt[j - 1] = L->elememt[j];
    L->n = (L->n - 1);
    return OK;
}

void Destory(SeqList *L)
{
    L->maxlength = 0;
    L->n = 0;
    free(L->elememt);
}

int main()
{
    srand(time(NULL));
    SeqList List;
    Init(&List, 400);
    for (int i = 0; i < 300; ++i)
        Insert(&List, i - 1, rand());
    printf("The rand array is : ");
    Output(&List);
    printf("\n");
    printf("After removing the 0th, the array is : ");
    Delete(&List, 0);
    Output(&List);
    Destory(&List);
    getchar();
    return 0;
}
