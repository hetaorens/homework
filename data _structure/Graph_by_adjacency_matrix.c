#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
typedef int BOOL;

typedef int ElemType;
typedef struct
{
    ElemType **a;    //邻接矩阵
    int n;           //图的当前顶点数
    int e;           //图的当前边数
    ElemType noEdge; //两顶点间无边时的值
} mGraph;
typedef struct eNode
{
    int adjVex;
    ElemType w;
    struct eNode *nextArc;
} eNode;
typedef struct
{
    int n;
    //任意顶点u相邻接的顶点 //边的权值 //指向下一个边结点
    //图的当前顶点数
    int e; //图的当前边数 eNode **a; //指向一维指针数组
} lGraph;
typedef struct
{
    int front;
    int rear;
    int maxSize;
    int *element;
} Queue;
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
typedef struct
{
    int **a; //二维数组的邻接矩阵
    int n;   //图的顶点数
    int e;   //图的边数
} mar_Graph;

void Init(mar_Graph *mg, int nSize)
{

    int i, j;
    mg->n = nSize;
    mg->e = 0;
    mg->a = (int **)malloc(nSize * sizeof(int *));
    for (i = 0; i < mg->n; i++)
    { //初始化权重为-1
        mg->a[i] = (int *)malloc(nSize * sizeof(int));
        for (j = 0; j < mg->n; j++)
        {
            mg->a[i][j] = -1;
        }
        mg->a[i][i] = 0; //自回路设置为0
    }
}

void Insert(mar_Graph *mg, int u, int v, int w)
{
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v)
        return; //错误输入
    if (mg->a[u][v] != -1)
        return;      //边已存在
    mg->a[u][v] = w; //插入新边
    mg->e++;
}

int Exist(mar_Graph *mg, int u, int v)
{
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v)
        return 0; //错误输入
    if (mg->a[u][v] == -1)
        return 0; //边不存在
    return 1;
}

int Remove(mar_Graph *mg, int u, int v)
{
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v)
        return 0; //错误输入
    if (mg->a[u][v] == -1)
        return 1;     //边不存在
    mg->a[u][v] = -1; //删除边
    mg->e--;
    return 1;
}

int Destory(mar_Graph *mg)
{
    int i;
    for (i = 0; i < mg->n; i++)
    {
        free(mg->a[i]);
    }
    free(mg->a);
    return 1;
}

//单一连通DFS
void DFS(int i, int visited[], mar_Graph g)
{
    printf("%d ", i);
    visited[i] = 1; //修改访问标记
    for (int j = 0; j < g.n; j++)
    { //遍历邻接点
        if (!visited[j] && g.a[i][j] > 0)
        { //若未被访问且有权值
            DFS(j, visited, g);
        }
    }
}

// DFS
void DFSGraph(mar_Graph g)
{
    int *visited = (int *)malloc(g.n * sizeof(int)); //访问标记
    for (int i = 0; i < g.n; i++)
    {
        visited[i] = 0;
    }
    for (int i = 0; i < g.n; i++)
    {
        if (!visited[i])
        { //若未被访问
            DFS(i, visited, g);
        }
    }
    free(visited);
}

//单一连通分量BFS
void BFS(int i, int visited[], mar_Graph g)
{
    Queue q;
    Create(&q, g.n);
    visited[i] = 1;
    printf("%d ", i);
    EnQueue(&q, i); //入队操作
    while (!IsEmpty(&q))
    {
        DeQueue(&q, &i); //出队操作
        for (int j = 0; j < g.n; j++)
        { //对邻接矩阵的邻边遍历
            if (!visited[j] && g.a[i][j] > 0)
            { //若未被访问且有权值
                visited[j] = 1;
                printf("%d ", j);
                EnQueue(&q, j); //入队操作
            }
        }
    }
}

// BFS
void BFSGraph(mar_Graph g)
{
    int *visited = (int *)malloc(g.n * sizeof(int)); //访问标记数组
    for (int i = 0; i < g.n; i++)
    {
        visited[i] = 0;
    }
    for (int i = 0; i < g.n; i++)
    {
        if (!visited[i])
        { //若未被访问
            BFS(i, visited, g);
        }
    }
    free(visited);
}

int main()
{
    mar_Graph g;
    int nSize, edge, u, v, w, i;

    printf("输入顶点的个数:");
    scanf("%d", &nSize);
    //邻接矩阵的初始化
    Init(&g, nSize);
    printf("输入总的边的个数:");
    scanf("%d", &edge);
    //邻接矩阵边的插入
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
    //邻接矩阵边的搜索
    if (Exist(&g, u, v))
        printf("成功搜素\n");
    else
        printf("暂无这条边\n");
    //邻接矩阵边的删除
    if (Remove(&g, u, v))
        printf("成功删除\n");
    else
        printf("删除失败\n");
    //邻接矩阵撤销操作
    if (Destory(&g))
        printf("完成图的撤销\n");
    else
        printf("失败请重试\n");
    return 0;
}
