
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100 // ������˳���ĳ�ʼ��С
#define LISTINCREMENT 10   // ÿ�����ݵ�������
#define OK 1               // �����˺���ִ��״̬�ķ���ֵ��
#define ERROR 0
#define OVERFLOW -2
typedef int ElemType; // ������Ԫ������ ElemType ��״̬���� Status����Ϊ���͡�
typedef int Status;

/**
 * @description: ������˳���Ľṹ�壬
 * ������Ԫ������ elem����ǰ���� length �ͱ�Ĵ�С listsize��
 */
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

/**
 * @description: ��ʼ��˳�������Ϊ˳�������ʼ�ռ�
 * @param {SqList} &L
 * @return {*}
 */
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        return OVERFLOW;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

/**
 * @description: ��˳����ָ��λ�ò���Ԫ�صĺ�����
 * @param {SqList} &L
 * @param {int} i
 * @param {ElemType} e
 * @return {*}
 */
Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    ElemType *p;
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= L.listsize)
    {
        ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return OVERFLOW;
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    ElemType *q = &(L.elem[i - 1]);
    for (p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p + 1) = *p;
    *q = e;
    ++L.length;
    return OK;
}

/**
 * @description: ����˳������Ԫ�صĺ���
 * @param {SqList} &L
 * @return {*}
 */
void ListTraverse_Sq(SqList &L)
{
    printf("��ǰ���Ա��Ԫ��Ϊ��\n");
    for (int i = 0; i < L.length; i++)
    {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

/**
 * @description: ��ȡ˳����ȵĺ���
 * @param {SqList} &L
 * @return {*}
 */
int GetLength_Sq(SqList &L)
{
    return L.length;
}

void main()
{
    // ������˳��� l���Լ�һЩ�������ڴ洢�û������Ԫ�غ�λ����Ϣ
    SqList l;
    ElemType e1;
    ElemType e2;
    ElemType e3;
    int loc1;
    int loc2;
    int loc3;

    // ���ó�ʼ��˳�������ʼ��˳��� l
    InitList_Sq(l);
    int i;
    // ѭ����˳����в���10���������Ԫ�ء�
    for (i = 1; i <= 10; i++)
    {
        ListInsert_Sq(l, i, rand() % 50);
    }
    ListTraverse_Sq(l);
    printf("��ǰ���Ա����ǣ�%d\n", GetLength_Sq(l));

    printf("��������Ҫ�����λ�ü�Ԫ��ֵ��\n");
    scanf("%d %d", &loc1, &e1);
    // ���ò��뺯����Ԫ�ز���ָ��λ��
    ListInsert_Sq(l, loc1, e1);
    // �������Ԫ�غ��˳���
    ListTraverse_Sq(l);
    printf("��ǰ���Ա�ĳ����ǣ�%d\n", GetLength_Sq(l));
}
