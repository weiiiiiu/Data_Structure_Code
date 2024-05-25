#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int TElemType;

/*定义链存储二叉树*/
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *Ichild, *rchild;
} BiTNode, *BiTree;

// 先序法构造二叉树
Status PreCreateBiTree(BiTree &T)
{
    int e;
    printf("请输入元素值：");
    scanf("%d", &e);
    if (e == 999)
    {
        T = NULL;
    }
    else
    {
        if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data = e;
        PreCreateBiTree(T->Ichild);
        PreCreateBiTree(T->rchild);
    }
    return OK;
}
// 非递归中序遍历
void NlnOrderTraverse(BiTree T)
{
    BiTree S[100], p;
    int top = 0;

    if (T)
    {
        S[top] = T;
        top++;
    }
    while (top != 0)
    {
        while (S[top - 1])
        {
            S[top] = S[top - 1]->Ichild;
            top++;
        }
        top--;
        if (top != 0)
        {
            p = S[top - 1];
            top--;
            printf("%d", p->data);
            S[top] = p->rchild;
            top++;
        }
    }
}
// 求二叉树结点个数
int NodeCount(BiTree T)
{
    if (T == NULL)
        return 0;
    else
        return NodeCount(T->Ichild) + NodeCount(T->rchild) + 1;
}
// 求二叉树叶子结点个数
int LeafCount(BiTree T)
{
    if (!T)
        return 0;
    else if (!T->Ichild && !T->rchild)
        return 1;
    else
        return (LeafCount(T->Ichild) + LeafCount(T->rchild));
}
// 求二叉树的深度
int GetHeight(BiTree T)
{
    if (!T)
        return 0;
    else
    {
        int m, n;
        m = GetHeight(T->Ichild);
        n = GetHeight(T->rchild);
        return m > n ? ++m : ++n;
    }
}
void main()
{
    BiTree T;
    int nodes, leafs, height;
    printf("递归先序创建二叉树(999代表空树):\n");
    PreCreateBiTree(T); // 测试输入 1 2 4 999 6 999 999 999 3 5 999 999 999
    printf("非递归中序遍历:\n");
    NlnOrderTraverse(T); // 4 6 2 1 5 3
    printf("\n");
    nodes = NodeCount(T); // 求结点个数 6
    printf("该二叉树的节点个数为:%d\n", nodes);
    leafs = LeafCount(T); // 求二叉树叶子结点个数 2
    printf("该二叉树的叶子节点个数为:%d\n", leafs);
    height = GetHeight(T); // 求二叉树的深度 4
    printf("该二叉树的深度为;%d\n", height);
}