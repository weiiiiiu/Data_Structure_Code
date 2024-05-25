#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100 // ջ�洢�ռ�ĳ�ʼ������
#define STACKINCREMENT 10   // ջ�洢�ռ�ķ�������
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
typedef int SElemType;
typedef int Status;

typedef struct
{
    SElemType *base; // ջ�ռ��ַ
    SElemType *top;  // ջ��ָ��
    int stacksize;   // ��ǰ�����ջ�ռ��С
} SqStack;

/*��ʼ��һ��˳��ջ*/
Status InitStack(SqStack &S)
{ // ����һ����ջ
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)
        exit(OVERFLOW);
    S.top = S.base; // ջ�յı�־Ϊbase��top���
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

/*����˳��ջ*/
void DestroyStack(SqStack &S)
{ // ����ջʱ�ͷſռ䣬����ʹ��base,topΪNULL
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
}
/*���˳��ջ*/
void ClearStack(SqStack &S)
{
    S.top = S.base;
}

/*�ж�˳��ջ�Ƿ�Ϊ��*/
Status StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

/*���ջ��Ԫ�ظ���*/
int StackLength(SqStack S)
{
    return S.top - S.base;
}
/*���ջ��Ԫ�أ������e��*/
Status GetTop(SqStack S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}
/*ѹһ��Ԫ�ؽ�ջ���ռ䲻����ʱ��Ҫ������*/
Status Push(SqStack &S, SElemType e)
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize = S.stacksize + STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}
/*����ջ��Ԫ�أ���ŵ�e��*/
Status Pop(SqStack &S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

void StackTraverse(SqStack S)
{
    if (S.base == S.top)
    {
        printf("��ǰջΪ��ջ\n");
    }
    else
    {
        printf("��ǰ��ջ�׵�ջ����Ԫ��Ϊ: \n");
        while (S.top > S.base)
            printf("%d ", *S.base++);
        printf("\n");
    }
}

void conversion(int Num)
{ // �㷨3.1
    SElemType e;
    SqStack S;
    InitStack(S);
    while (Num)
    {
        Push(S, Num % 8);
        Num = Num / 8;
    }
    while (!StackEmpty(S))
    {
        Pop(S, e);
        printf("%d ", e);
    }
    printf("\n");
} // conversion

void main()
{
    SqStack s;
    SElemType e1, e2;
    int i;
    InitStack(s);
    for (i = 1; i <= 5; i++)
        Push(s, rand() % 50);
    StackTraverse(s);
    GetTop(s, e1);
    printf("��ǰջ��Ԫ��Ϊ:%d\n", e1);
    printf("\n");
    printf("Ԫ�������ջ:\n");
    while (!StackEmpty(s))
    {
        Pop(s, e2);
        printf("��ǰ��ջԪ��Ϊ:%d\n", e2);
        StackTraverse(s);
    }
    printf("\n");

    // ʮ����ת�˽���
    int num;
    printf("��������Ҫת���ķǸ�ʮ��������: \n");
    scanf("%d", &num);
    printf("���Ϊ: \n");
    conversion(num);
}