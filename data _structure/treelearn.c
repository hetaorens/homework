/*
ADT BinaryTree
{
    .data:set or NULL


    .func:
        Creat(bt);
        NewNode(x,in,rn);
        is_empty();
        Clear_tree();
        Root(bt,x);
        MakeTree();
        preOrderTree();
        inOrderTree();
        PostOrderTree();



}


*/

typedef struct btnode
{
    ElemType element;
    struct btnode *lChild;
    struct btnode *rChild;
} BTNode;
typedef struct binarytree
{
    BTNode *root;
} BinaryTree;
// binTree 的链接表示
/*
如果add one parent that can point to their parent


struct btnode *parent

*/
/*
Create(bt);
NewNode(x,ln,rn);
Root(bt,x);
MakeTree(bt,x,left,right);


*/

// Create(bt)
// {

// }
int Root(BinaryTree *bt, ElemType *x)
{
    if (bt->root)
    {
        x = &bt->root->element;
        return true;
    }
    else
    {
        return FALSE;
    }
}
void Create(BinaryTree *bt)
{
    bt->root = NULL;//根节点
}
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn)//新节点

{
    BTNode *p = (BTNode *)malloc(sizeof(BTNode));//为新节点赋空间
    //数据和左右子树的初始
    p->element = x;
    p->lChild = ln;
    p->rChild = rn;
    return p;
}
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right)
{
    if (bt->root || left == right)//空树
        return;
    bt->root = NewNode(e, left->root, right->root);//更新节点
    left->root = right->root = NULL;//叶子赋空
}

//先序
void PreOrderTree(BinaryTree *bt)
{
    PreOrder(bt->root);
}
void PreOder(BTNode *t)
{
    if (!t)
        return;
    printf("%c", t->element);//V
    PreOder(t->lChild);//L
    PreOder(t->rChild);//R
}
//中序
void inOrder(BinaryTree *bt)
{
    Inorder(bt->root);
}
void Inorder(BTNode *t)
{
    Inorder(t->lChild);//L
    printf("%c", t->element);//V
    Inorder(t->rChild);//R
}

//后续
void postOrder(BinaryTree *bt)
{
    PostOrder(bt->root);
}
void PostOrder(BTNode *t)
{
    PostOrder(t->lChild);//L
    PostOrder(t->rChild);//R
    printf("%c", t->element);//V
}

#define QUEUESIZE 100
void LevelOrderTree(BinaryTree *tree)
{
    Queue Q;
    BTNode *p;
    if (!tree->root)
        return;
    Create(&Q, QUEUEUSIZE);
    EnQueue(&Q, tree->root);
    while (!isEmpty(&Q))
    {
        Front(&Q, &p);
        DeQueue(&Q);
        printf("%c", p->element);
        if (p->lChild)
            EnQueue(&Q, p->Child);
        if (p->rChild)
            EnQueue(&Q, p->rChild);
    }
    Destroy(&Q);
}

/*
1.给定一颗二叉树,可以得出先序后续,中序,层次遍历;
2.已知二叉树的先序遍历和中序遍历,可以唯一的确定二叉树;
3.同后序遍历和中序遍历
4.若二叉树中节点数量n>1,在已知的二叉树的先序遍历和后续遍历的情况下无法唯一确定一颗二叉树.


计算二叉树的节点总数量
{
    若位空返回0
    若非空,分别计算左右的节点数并加上1
}


*/
int TreeSize(BinaryTree *bt)
{
    return Size(bt->root);
}

int Size(BTNode *bt)
{
    if (!t)
        return 0;
    else
    {
        return Size(t->lChild) + Size(t->rChild) + 1;
    }
}
/*
if empty return ;


else
del lChild
del rChild
del root
*/

void TreeClear(BinaryTree *bt)
{
    Clear(bt->root);
}
void Clear(BTNode *t)
{
    if (!t)
        return;
    Clear(t->lChild);
    Clear(t->rChild);
    free(t);
}

/*堆的顺序表示k[len]
对于最小堆满足k[i]<k[2*i+1]&&k[i]<=k[2*k+2]
对于最大堆满足k[i]>=k[2*i+1]&&k[i]>=k[2*k+2]
//向下调整算法*/
void AdjustDown(ElEmType heap[],int current,int border)
{
    int p=current;
    int minChild;
    ElemType temp;
    while(2*p+1<=border)
    {
        if((2*p+2<=border)&&(heap[2*p+1]>heap[2*p+2]))
        minChild =2*p+2;
        else{
            minChild=2*p+1;
        }
        if(heap[p]<=heap[minChild])
            break;else{
                temp=heap[p];
                heap[p]=heap[minChild];
                heap[minChild]=temp;
                p=minChild;
            }
    }
}
void CreateHeap(ElemType heap[],int n)
{
    int i;
    for(i=(n-2)/2;i>-1;i--)
        AdjustDown(heap,i,n-1);
}

/*
my_adjust(Elemt heap[],int cur,int border)

{
    int p=cur;
    int mindChlid;
    Elemtent temp;
    while(2*p+1>=boder)
    {
        if(2*p+2<=boder&&heap[2*p+2]>heap[2*p+1])
            mindChild=2*p+2;
            else
            {
                mindChild=2*p+1;
            }
            if(heap[p]<=heap[mindChild])
            breal;
            else
            {
                swap(heap[p],heap[mindChild])
                p=mindChild;
            }
    }
}




*/
void AdjustUp(ElemType heap[],int cur)
{
    int p=cur;
    while(p>0)
    {
        if(heap[p]<heap[(p-1)]/2)
        {swap(heap[p],heap[(p-1)/2]);
            p=(p-1)/2
        }
        else{
            break;
        }
    }



}


/*
ADT priority_queue{
    .data:
        n>=0 `s heap
    .func:
        Crate(PQ,msize)
        Destroy(PQ)
        is_empty(PQ)
        is_full(PQ)
        size(PQ)
        Append(PQ,x)
        Serve(PQ,x)


}*/
void CreatPQ(PriorityQueue *PQ,int size)
{
    PQ->maxsize=size;
    PQ->n=0;
    PQ->elemts=(ElemType*)malloc(size*sizeof(ElemType));

}
void Destroy(PriorityQueue *PQ)
{
    free(PQ->elements);
    PQ->n=0;
    PQ->maxsize=0;
}

int is_empty(PriorityQueue *PQ)

{
    if(PQ->n=0) return True;
    else{
        return FALSE;
    }
}
int is_full(PriorityQueue *PQ)
{
    if(PQ->n==PQ->maxsize)


    {
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int size(PriorityQueue *PQ)
{
    return PQ->n;
}
void Append(PriorityQueue *PQ,ElemType x)
{
    if(is_full(PQ)) return;
    PQ->elements[PQ->n]=x;
    PQ->n++;
    AdjustUp(PQ->elements,PQ->n-1);

}
void Serve(PriorityQueue *PQ ,ElemType *x)
{
    if(is_empty(PQ)) return ;
    *x=PQ->element[0];
    PQ->n--;
    PQ->elements[0]=PQ->elements[PQ-n];
    AdjustDown(PQ->elements,0,PQ->n-1);
}




//哈夫曼
BinaryTree CreateHFMTree(int w[],int m)
{
    BinaryTree x,y,z;
    CreatePQ(PQ,m);
    for(int i=0;i<m;++i){
        MakeTree(x,w[i],NULL,NULL);
        Append(PQ,x);
    }
    while(PQ.n>1)
    {
        Serve(PQ,x);
        Serve(PQ,y);
        if(x.root.element<y.root.element)
        {
            MakeTree(z,x.root.element+y.root.element,x,y);
        }
        else{
            MakeTree(z,x.root.element+y.root.element,y,x);
        }
        Append(PQ,z);
    }
    Serve(PQ,x);
    return x;
}
