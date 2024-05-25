#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

#define MAXSIZE 12500
typedef struct
{
    int i, j;
    ElemType e;
} Triple;

typedef struct
{
    Triple data[MAXSIZE + 1];
    int mu, nu, tu;
} TSMatrix;

Status Init_TSMatrix(TSMatrix &M)
{
    int t;
    printf("请输入矩阵行数\n");
    scanf("%d", &M.mu);
    printf("请输入矩阵列数\n");
    scanf("%d", &M.nu);
    printf("请输入矩阵非零元个数\n");
    scanf("%d", &M.tu);
    printf("请输入矩阵的非零元素\n");
    if (M.mu > 0 && M.nu > 0 && M.tu <= MAXSIZE)
    {
        for (t = 1; t <= M.tu; t++)
        {
            printf("请输入第%d个元素的行号:\n", t);
            scanf("%d", &M.data[t].i);
            printf("请输入第%d个元素的列号:\n", t);
            scanf("%d", &M.data[t].j);
            printf("请输入第%d个元素的值:\n", t);
            scanf("%d", &M.data[t].e);
            if (M.data[t].i > M.mu || M.data[t].j > M.nu)
            {
                return ERROR;
            }
        }
    }
    else
        return ERROR;
    return OK;
}

Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    int col, t, p, q;
    int num[20], cpot[20];
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu)
    {
        for (col = 1; col <= M.nu; ++col)
            num[col] = 0;
        for (t = 1; t <= M.tu; ++t)
            ++num[M.data[t].j];
        cpot[1] = 1;
        for (col = 2; col <= M.nu; ++col)
            cpot[col] = cpot[col - 1] + num[col - 1];
        for (p = 1; p <= M.tu; ++p)
        {
            col = M.data[p].j;
            q = cpot[col];
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];
        }
    }
    return OK;
}
Status TSMatrixTraverse(TSMatrix M)
{
    printf("当前矩阵中的非零元素三元组有:\n");
    int t;
    for (t = 1; t <= M.tu; t++)
    {
        printf("(");
        printf("%d.", M.data[t].i);
        printf("%d.", M.data[t].j);
        printf("%d", M.data[t].e);
        printf(").");
    }
    printf("\n");
    return OK;
}
void main()
{
    TSMatrix M, T;
    int flag;
    printf("初始化要转置的矩阵M:\n");
    flag = Init_TSMatrix(M);
    if (!flag)
    {
        printf("初始化错误！\n");
        exit(1);
    }
    TSMatrixTraverse(M);
    FastTransposeSMatrix(M, T);
    printf("转置的矩阵T:\n");
    TSMatrixTraverse(T);
}