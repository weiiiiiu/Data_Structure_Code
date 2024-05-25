#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXQSIZE 100 // ���г���
#define TRUE 1
#define FALSE 0
typedef int QElemType; // ����ѭ�����е�����Ԫ�ص�����
typedef int Status;
// ����ѭ������
typedef struct
{
    QElemType *base;
    int front;
    int rear;
} SqQueue;

/*����һ���ն���*/
Status InitQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base)
        exit(OVERFLOW);
    Q.front = 0;
    Q.rear = 0;
    return OK;
}

/*��ն���*/
void ClearQueue(SqQueue &Q)
{
    Q.front = 0;
    Q.rear = 0;
}

/*���ٶ���*/
void DestroyQueue(SqQueue &Q)
{
    if (Q.base)
        free(Q.base);
    Q.base = NULL;
    Q.front = 0;
    Q.rear = 0;
}

/*�ж�ѭ���Ƿ�Ϊ�������99Ԫ��*/
Status QueueFull(SqQueue &Q)
{
    if ((Q.rear + 1) % MAXQSIZE == Q.front)
        return TRUE;
    else
        return FALSE;
}

/*�ж϶����Ƿ�Ϊ��*/
Status QueueEmpty(SqQueue &Q)
{
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

/*������*/
Status EnQueue(SqQueue &Q, QElemType e)
{
    if (QueueFull(Q))
        return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

/*������*/
Status DeQueue(SqQueue &Q, QElemType &e)
{
    if (QueueEmpty(Q))
        return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

/*������������*/
void QueueTraverse(SqQueue Q)
{
    if (QueueEmpty(Q))
        printf("��ǰ����Ϊ��\n");
    else
    {
        printf("��ǰ����Ԫ��Ϊ:");
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
        printf("���ӵ�Ԫ����%d\n", e);
        QueueTraverse(Q);
    }
}