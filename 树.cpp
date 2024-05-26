/*
 * @Author: wei weeiii826@gmail.com
 * @Date: 2024-04-22 12:25:29
 * @LastEditors: wei weeiii826@gmail.com
 * @LastEditTime: 2024-05-26 19:21:24
 * @FilePath: /数据结构代码/树.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置:
 * https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

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
// 递归先序遍历
void PreOrderTraverse(BiTree T)
{
    if (T)
    {
        printf("%d", T->data);
        PreOrderTraverse(T->Ichild);
        PreOrderTraverse(T->rchild);
    }
}
// 递归后序遍历
void PostOrderTraverse(BiTree T)
{
    if (T)
    {
        PostOrderTraverse(T->Ichild);
        PostOrderTraverse(T->rchild);
        printf("%d", T->data);
    }
}

int main()
{
    BiTree T;
    printf("递归先序创建二叉树(999为空树);\n");
    PreCreateBiTree(T); // 测试输入:1 2 999 999 3 999 999
    printf("递归先序遍历: \n");
    PreOrderTraverse(T);
    printf("\n");
    printf("递归中序遍历: \n");
    PostOrderTraverse(T);
    printf("\n");
    printf("递归后序遍历: \n");
    PostOrderTraverse(T);
    printf("\n");
}