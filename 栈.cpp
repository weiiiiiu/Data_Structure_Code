
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
    SElemType *top;  // 指向栈顶的下一个位置 要插入的位置
    int stacksize;   // 当前分配的栈空间大小
} SqStack;

// 初始化一个顺序栈
Status InitStack(SqStack &S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S.base)
        exit(OVERFLOW);
    S.top = S.base; // 栈空的标志为base和top相等
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

// 销毁顺序栈
void DestroyStack(SqStack &S)
{ // 销毁栈时释放空间，并且使得base,top为NULL
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
}

// 清空顺序栈
void ClearStack(SqStack &S)
{
    S.top = S.base;
}

// 判断顺序栈是否为空
Status StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

// 获得栈内元素个数
int StackLength(SqStack S)
{
    return S.top - S.base; // 指针相减得到元素个数 4个字节自动为一个元素
}

// 获得栈顶元素，存放在e中
Status GetTop(SqStack S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

// 进栈
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

// 弹出栈顶元素，存放到e中
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
            printf("%d ", *S.base++); // 先输出S.top-1,加一后S.top截止
        printf("\n");
    }
}

/*
将给定的十进制数不断地整除N,直到商为0。
将每步计算所得到的余数(从第一步起依次记录),倒序排列。
根据余数的数位,以N为基数,组成N进制数。
*/
void conversion(int Num)
{
    SElemType e; // 用于存储从栈中弹出的元素。
    SqStack S;
    InitStack(S); // 初始化一个栈
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
}

int main()
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