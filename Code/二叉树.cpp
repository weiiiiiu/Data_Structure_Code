
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int TElemType;

// 定义链存储二叉树
typedef struct BiTNode
{
    TElemType data;                  // 节点存储的数据
    struct BiTNode *Ichild, *rchild; // 左子节点和右子节点的指针。
} BiTNode, *BiTree;

// 初始化二叉树
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
        PreCreateBiTree(T->Ichild); // 递归创建左子树
        PreCreateBiTree(T->rchild); // 递归创建右子树
    }
    return OK;
}
// 非递归中序遍历
void NlnOrderTraverse(BiTree T)
{
    BiTree S[100], p; // 定义一个栈存储访问的节点，p为当前访问的节点
    int top = 0;
    if (T)
    {
        S[top] = T;
        top++; // top为要插入的位置
    }
    while (top != 0) // 栈不为空
    {
        while (S[top - 1]) // 当前二叉树节点不为空
        {
            S[top] = S[top - 1]->Ichild; // 将左子树节点入栈 第二轮遍历右节点的左子树
            top++;
        }
        top--; // 将NULL出栈 左子树遍历完成
        if (top != 0)
        {
            p = S[top - 1]; // 左子树节点依次出栈NULL
            top--;
            printf("%d", p->data);
            S[top] = p->rchild; // 将右子树节点入栈   右节点的左子树可能为NULL
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
    else if (!T->Ichild && !T->rchild) // 当前为叶子节点
        return 1;
    else
        return (LeafCount(T->Ichild) + LeafCount(T->rchild)); // 计算左子树和右子树的叶子节点数量
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
        n = GetHeight(T->rchild); // 根节点也算一层
        return m > n ? ++m : ++n;
    }
}

int main()
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