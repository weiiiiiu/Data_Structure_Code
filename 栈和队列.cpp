#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100 // 栈存储空间的初始分配量
#define STACKINCREMENT 10   // 栈存储空间的分配增量
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
typedef int SElemType;
typedef int Status;

typedef struct
{
    SElemType *base; // 栈空间基址
    SElemType *top;  // 栈顶指针
    int stacksize;   // 当前分配的栈空间大小
} SqStack;

/*初始化一个顺序栈*/
Status InitStack(SqStack &S)
{ // 构造一个空栈
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)
        exit(OVERFLOW);
    S.top = S.base; // 栈空的标志为base和top相等
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

/*销毁顺序栈*/
void DestroyStack(SqStack &S)
{ // 销毁栈时释放空间，并且使得base,top为NULL
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
}
/*清空顺序栈*/
void ClearStack(SqStack &S)
{
    S.top = S.base;
}

/*判断顺序栈是否为空*/
Status StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

/*获得栈内元素个数*/
int StackLength(SqStack S)
{
    return S.top - S.base;
}
/*获得栈顶元素，存放在e中*/
Status GetTop(SqStack S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}
/*压一个元素进栈，空间不够的时候要扩容量*/
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
/*弹出栈顶元素，存放到e中*/
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
        printf("当前栈为空栈\n");
    }
    else
    {
        printf("当前从栈底到栈顶的元素为: \n");
        while (S.top > S.base)
            printf("%d ", *S.base++);
        printf("\n");
    }
}

void conversion(int Num)
{ // 算法3.1
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
    printf("当前栈顶元素为:%d\n", e1);
    printf("\n");
    printf("元素逐个出栈:\n");
    while (!StackEmpty(s))
    {
        Pop(s, e2);
        printf("当前出栈元素为:%d\n", e2);
        StackTraverse(s);
    }
    printf("\n");

    // 十进制转八进制
    int num;
    printf("请输入需要转化的非负十进制整数: \n");
    scanf("%d", &num);
    printf("结果为: \n");
    conversion(num);
}