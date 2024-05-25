#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXQSIZE 100 // 队列长度
#define TRUE 1
#define FALSE 0
typedef int QElemType; // 定义循环队列的数据元素的类型
typedef int Status;
// 定义循环队列
typedef struct
{
    QElemType *base;
    int front;
    int rear;
} SqQueue;

/*构造一个空队列*/
Status InitQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base)
        exit(OVERFLOW);
    Q.front = 0;
    Q.rear = 0;
    return OK;
}

/*清空队列*/
void ClearQueue(SqQueue &Q)
{
    Q.front = 0;
    Q.rear = 0;
}

/*销毁队列*/
void DestroyQueue(SqQueue &Q)
{
    if (Q.base)
        free(Q.base);
    Q.base = NULL;
    Q.front = 0;
    Q.rear = 0;
}

/*判断循环是否为满，最多99元素*/
Status QueueFull(SqQueue &Q)
{
    if ((Q.rear + 1) % MAXQSIZE == Q.front)
        return TRUE;
    else
        return FALSE;
}

/*判断队列是否为空*/
Status QueueEmpty(SqQueue &Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

/*进队列*/
Status EnQueue(SqQueue &Q, QElemType e)
{
    if (QueueFull(Q))
        return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

/*出队列*/
Status DeQueue(SqQueue &Q, QElemType &e)
{
    if (QueueEmpty(Q))
        return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

/*遍历整个队列*/
void QueueTraverse(SqQueue Q)
{
    if (QueueEmpty(Q))
        printf("当前队列为空\n");
    else
    {
        printf("当前队列元素为:");
        while (Q.front != Q.rear)
        {
            printf("%d ", Q.base[Q.front]);
            Q.front = (Q.front + 1) % MAXQSIZE;
        }
        printf("\n");
    }
}

void main()
{
    int i;
    QElemType e;
    SqQueue Q;
    InitQueue(Q);

    for (i = 1; i <= 6; i++)
        EnQueue(Q, rand() % 50);
    QueueTraverse(Q);

    while (!QueueEmpty(Q))
    {
        DeQueue(Q, e);
        printf("出队的元素是%d\n", e);
        QueueTraverse(Q);
    }
}