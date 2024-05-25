#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

typedef struct DuLNode
{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, *DuLinkList;

Status ListInit_DuL(DuLinkList &L)
{ // ��ʼ����һ����ͷ����˫��ѭ������
    L = (DuLinkList)malloc(sizeof(DuLNode));
    if (!L)
        exit(OVERFLOW);
    L->prior = L;
    L->next = L;
    return OK;
}

DuLinkList GetElemP_DuL(DuLinkList va, int i)
{
    // vaΪ��ͷ����˫��ѭ�������ͷָ��
    // ����i��Ԫ�ؽڵ����ʱ�����ص�i�����
    DuLinkList p;
    p = va->next;
    int j = 1;
    while (p != va && j < i)
    { // ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪͷ���
        p = p->next;
        ++j;
    }
    if (p == va && j < i)
        return NULL; // ��i��Ԫ�ز�����
    else
        return p;
}

Status ListInsert_DuL(DuLinkList &L, int i, ElemType e)
{ // �㷨2.18
    // �ڴ�ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
    // i�ĺϷ�ֵΪ1��i�ܱ�+1
    DuLinkList p, s;
    if (!(p = GetElemP_DuL(L, i))) // ��L��ȷ����i��Ԫ�ص�λ��ָ��p
        return ERROR;
    if (!(s = (DuLinkList)malloc(sizeof(DuLNode))))
        return ERROR;
    s->data = e;
    s->prior = p->prior;
    p->prior->next = s;
    s->next = p;
    p->prior = s;
    return OK;
}

Status ListDelete_DuL(DuLinkList &L, int i, ElemType &e)
{ // �㷨2.19
    // ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ�أ�i�ĺϷ�ֵΪ1�ܡܱ�
    DuLinkList p;
    if (!(p = GetElemP_DuL(L, i)))
        return ERROR;
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}

void ListTraverse_DuL(DuLinkList &L)
{ // ������ͷ����˫��ѭ�������е�Ԫ�أ�����ӡ
    DuLinkList p;
    p = L->next;
    printf("��ǰ˫��ѭ�������Ԫ��Ϊ:\n");
    while (p != L)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void CreateList_L(LinkList &L, int n)
{ // �㷨2.11
    // ��λ�����루���������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L
    LinkList p;
    int i;
    srand((unsigned)time(NULL));
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    for (i = n; i > 0; --i)
    {
        p = (LinkList)malloc(sizeof(LNode));
        p->data = rand() % 50;
        p->next = L->next;
        L->next = p;
    }
}

Status GetElem_L(LinkList &L, int i, ElemType &e)
{ // �㷨2.8
    // LΪ��ͷ���ĵ������ͷָ�롣
    // ����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
    LinkList p;
    p = L->next;
    int j = 1;
    while (p && j < i)
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;
    e = p->data;
    return OK;
}

Status ListInsert_L(LinkList &L, int i, ElemType e)
{ // �㷨2.9
    // �ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
    LinkList p, s;
    p = L;
    int j = 0;
    while (p && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1)
        return ERROR;
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status ListDelete_L(LinkList &L, int i, ElemType &e)
{ // �㷨2.10
    // �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
    LinkList p, q;
    p = L;
    int j = 0;
    while (p->next && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i - 1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}

void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{ // �㷨2.12
    // ��֪�������Ա�La��Lb��Ԫ�ذ�
    LinkList pa, pb, pc;
    pa = La->next;
    pb = Lb->next;
    Lc = pc = La;
    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(Lb);
}

void ListTraverse_L(LinkList &L)
{ // �����������е�Ԫ�ز���ӡ
    LinkList p;
    p = L->next;
    printf("��ǰ������Ԫ��Ϊ��\n");
    while (p)
    {
        printf("%d  ", p->data);
        p = p->next;
    }
    printf("\n");
}

void main()
{
    LinkList la, lb, lc, ld;
    ElemType e1, e2, e3;
    int loc1, loc2, loc3;
    //*
    // ������la�Ļ�������
    CreateList_L(la, 10);
    ListTraverse_L(la);
    printf("��������Ҫ���ҵ�Ԫ��λ�ã�\n");
    scanf("%d", &loc1);
    GetElem_L(la, loc1, e1);
    printf("�����е�%d��λ���ϵ�Ԫ���ǣ�%d \n", loc1, e1);
    printf("��������Ҫ�����λ�ü�Ԫ��ֵ��\n");
    scanf("%d %d", &loc2, &e2);
    ListInsert_L(la, loc2, e2);
    ListTraverse_L(la);
    printf("��������Ҫɾ����λ�ã�\n");
    scanf("%d", &loc3);
    ListDelete_L(la, loc3, e3);
    printf("ɾ����Ԫ��Ϊ��%d\n", e3);
    ListTraverse_L(la);
    printf("\n");

    // �ϲ�lb,lc��ld
    CreateList_L(lb, 0);
    CreateList_L(lc, 0);
    int i, j;
    for (i = 1; i <= 4; i++)
    {
        ListInsert_L(lb, i, i);
    }
    printf("���ϲ�Lb:\n");
    ListTraverse_L(lb);

    for (j = 1; j <= 3; j++)
    {
        ListInsert_L(lc, j, j);
    }
    printf("���ϲ�Lc:\n");
    ListTraverse_L(lc);
    MergeList_L(lb, lc, ld);
    printf("�ϲ���ĵ�����\n");
    ListTraverse_L(ld);

    DuLinkList L;
    ElemType a, a1, a2;
    int lod1, lod2;

    ListInit_DuL(L);
    for (int k = 1; k <= 5; k++)
    {
        a = rand() % 50;
        ListInsert_DuL(L, k, a);
    }
    ListTraverse_DuL(L);

    printf("��������Ҫ�����λ�ü�Ԫ��ֵ: \n");
    scanf("%d %d", &lod1, &a1);
    ListInsert_DuL(L, lod1, a1);
    ListTraverse_DuL(L);

    printf("��������Ҫɾ����λ��: \n");
    scanf("%d", &lod2

    );
    ListDelete_DuL(L, lod2, a2);
    printf("ɾ����Ԫ��Ϊ:%d\n", a2);
    ListTraverse_DuL(L);
}
