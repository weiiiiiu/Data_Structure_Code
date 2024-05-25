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
    printf("�������������\n");
    scanf("%d", &M.mu);
    printf("�������������\n");
    scanf("%d", &M.nu);
    printf("������������Ԫ����\n");
    scanf("%d", &M.tu);
    printf("���������ķ���Ԫ��\n");
    if (M.mu > 0 && M.nu > 0 && M.tu <= MAXSIZE)
    {
        for (t = 1; t <= M.tu; t++)
        {
            printf("�������%d��Ԫ�ص��к�:\n", t);
            scanf("%d", &M.data[t].i);
            printf("�������%d��Ԫ�ص��к�:\n", t);
            scanf("%d", &M.data[t].j);
            printf("�������%d��Ԫ�ص�ֵ:\n", t);
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
    printf("��ǰ�����еķ���Ԫ����Ԫ����:\n");
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
    printf("��ʼ��Ҫת�õľ���M:\n");
    flag = Init_TSMatrix(M);
    if (!flag)
    {
        printf("��ʼ������\n");
        exit(1);
    }
    TSMatrixTraverse(M);
    FastTransposeSMatrix(M, T);
    printf("ת�õľ���T:\n");
    TSMatrixTraverse(T);
}