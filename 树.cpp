#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int TElemType;

/*�������洢������*/
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *Ichild, *rchild;
} BiTNode, *BiTree;

// ���򷨹��������
Status PreCreateBiTree(BiTree &T)
{
    int e;
    printf("������Ԫ��ֵ��");
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
// �ݹ��������
void PreOrderTraverse(BiTree T)
{
    if (T)
    {
        printf("%d", T->data);
        PreOrderTraverse(T->Ichild);
        PreOrderTraverse(T->rchild);
    }
}
// �ݹ�������
void PostOrderTraverse(BiTree T)
{
    if (T)
    {
        PostOrderTraverse(T->Ichild);
        PostOrderTraverse(T->rchild);
        printf("%d", T->data);
    }
}

void main()
{
    BiTree T;
    printf("�ݹ����򴴽�������(999Ϊ����);\n");
    PreCreateBiTree(T); // ��������:1 2 999 999 3 999 999
    printf("�ݹ��������: \n");
    PreOrderTraverse(T);
    printf("\n");
    printf("�ݹ��������: \n");
    PostOrderTraverse(T);
    printf("\n");
    printf("�ݹ�������: \n");
    PostOrderTraverse(T);
    printf("\n");
}