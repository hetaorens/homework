#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
typedef int BOOL;
typedef struct
{
    int front;
    int rear;
    int maxSize;
    int *element;
} Queue;

//初始化队列
void Create(Queue *Q, int mSize)
{
    Q->maxSize = mSize;
    Q->element = (int *)malloc(sizeof(int) * mSize);
    Q->front = Q->rear = 0;
}

//队列是否为空
BOOL IsEmpty(Queue *Q)
{
    return Q->front == Q->rear;
}

//队列是否已满
BOOL IsFULL(Queue *Q)
{
    return (Q->rear + 1) % (Q->maxSize) == Q->front;
}

//入队
BOOL EnQueue(Queue *Q, int x)
{
    if (IsFULL(Q))
        return 0;
    Q->rear = (Q->rear + 1) % (Q->maxSize);
    Q->element[Q->rear] = x;
    return 1;
}

//出队
BOOL DeQueue(Queue *Q, int *x)
{
    if (IsEmpty(Q))
        return 0;
    *x = Q->element[(Q->front + 1) % (Q->maxSize)];
    if (IsEmpty(Q))
        return 0;
    Q->front = (Q->front + 1) % (Q->maxSize);
    return TRUE;
}

typedef struct ENode
{
    int adjVex;         //边指向的顶点
    int w;              //边的权值
    struct ENode *next; //下一条邻边的指针
} ENode;

typedef struct
{
    int n;     //顶点数
    int e;     //边数
    ENode **a; //取一维指针数组，下标指当前顶点，值为当前顶点的邻边
} List_Graph;

void Init(List_Graph *g, int n)
{
    int i;
    g->n = n;
    g->e = 0;
    g->a = (ENode **)malloc(n * sizeof(ENode *)); //创建一维指针数组，即创建顶点
    for (i = 0; i < g->n; i++)
    {
        g->a[i] = NULL; //所有顶点的邻边置零
    }
    return;
}

BOOL Exist(List_Graph *g, int u, int v)
{
    if (u < 0 || v < 0 || u > g->n - 1 || v > g->n - 1 || u == v)
        return 0;       //输入错误
    ENode *p = g->a[u]; // 初始化为u点的第一条邻边
    while (p != NULL && p->adjVex != v)
    {
        p = p->next;
    }
    if (p)
        return 1; //找到此边
    else
        return 0;
}

void Insert(List_Graph *g, int u, int v, int w)
{ //头插法插入邻接表
    if (u < 0 || v < 0 || u > g->n - 1 || v > g->n - 1 || u == v)
        return; //输入错误
    if (Exist(g, u, v))
        return; //边已存在
    ENode *p = (ENode *)malloc(sizeof(ENode));
    p->adjVex = v;     //插入边指向的顶点
    p->w = w;          //插入边的权值
    p->next = g->a[u]; //插入边当作第一个邻边
    g->a[u] = p;
    g->e++;
}

BOOL Remove(List_Graph *g, int u, int v)
{
    if (u < 0 || v < 0 || u > g->n - 1 || v > g->n - 1 || u == v)
        return 0; //输入错误
    ENode *p = g->a[u];
    ENode *pre = NULL;
    while (p && p->adjVex != v)
    {
        pre = p; // q是p前驱
        p = p->next;
    }
    if (!p)
        return 0; //失败未找到
    if (pre)
        pre->next = p->next; //删除此边
    else
        g->a[u] = p->next;
    free(p);
    g->e--;
    return 1;
}

int Destory(List_Graph *g)
{
    ENode *p, *q;
    for (int i = 0; i < g->n; i++)
    {
        p = g->a[i];
        q = p;
        while (p)
        {
            p = p->next;
            free(q);
            q = p;
        }
    }
    free(g->a);
    return 1;
}

//单一连通分量DFS
void DFS(int i, int visited[], List_Graph g)
{
    printf("%d ", i); //访问
    visited[i] = 1;
    ENode *w; //创建一条新边指针
    for (w = g.a[i]; w; w = w->next)
    {
        if (!visited[w->adjVex])
        { //若邻接结点未被访问
            DFS(w->adjVex, visited, g);
        }
    }
}

// DFS
void DFSGraph(List_Graph g)
{
    int *visited = (int *)malloc(g.n * sizeof(int)); //访问标记
    for (int i = 0; i < g.n; i++)
    {
        visited[i] = 0;
    }
    for (int i = 0; i < g.n; i++)
    {
        if (!visited[i])
        {
            DFS(i, visited, g);
        }
    }
    free(visited);
}

//单一连通分量BFS
void BFS(int v, int visited[], List_Graph g)
{
    printf("%d ", v);
    visited[v] = 1;
    ENode *w;
    Queue q;
    Create(&q, g.n);
    EnQueue(&q, v); //入队操作
    while (!IsEmpty(&q))
    {
        DeQueue(&q, &v); //出队操作
        for (w = g.a[v]; w; w = w->next)
        {
            if (!visited[w->adjVex])
            { //未被访问
                printf("%d ", w->adjVex);
                visited[w->adjVex] = 1;
                EnQueue(&q, w->adjVex); //入队操作
            }
        }
    }
}

// BFS
void BFSGraph(List_Graph g)
{
    int *visited = (int *)malloc(g.n * sizeof(int));
    for (int i = 0; i < g.n; i++)
    {
        visited[i] = 0;
    }
    for (int i = 0; i < g.n; i++)
    {
        if (!visited[i])
        {
            BFS(i, visited, g);
        }
    }
    free(visited);
}

int main()
{
    List_Graph g;
    int nSize, edge, u, v, w, i;
    printf("输入顶点的个数:");
    scanf("%d", &nSize);
    //邻接表的初始化
    Init(&g, nSize);
    printf("输入总的边的个数:");
    scanf("%d", &edge);
    //邻接表边的插入
    for (i = 0; i < edge; i++)
    {
        printf("输入待插入的边:");
        scanf("%d%d%d", &u, &v, &w);
        Insert(&g, u, v, w);
    }
    //深度优先遍历 DFS
    printf("DFS:");
    DFSGraph(g);
    //宽度优先遍历 BFS
    printf("\nBFS:");
    BFSGraph(g);
    printf("\n输入搜索且删除的边:");
    scanf("%d%d", &u, &v);
    //邻接表的搜索
    if (Exist(&g, u, v))
        printf("成功搜素\n");
    else
        printf("暂无这条边\n");
    //邻接表边的删除
    if (Remove(&g, u, v))
        printf("成功删除\n");
    else
        printf("删除失败\n");
    //邻接矩阵边的操作
    if (Destory(&g))
        printf("完成图的撤销\n");
    else
        printf("失败请重试\n");
    return 0;
}
