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
{ // 初始化第一个带头结点的双向循环链表
    L = (DuLinkList)malloc(sizeof(DuLNode));
    if (!L)
        exit(OVERFLOW);
    L->prior = L;
    L->next = L;
    return OK;
}

DuLinkList GetElemP_DuL(DuLinkList va, int i)
{
    // va为带头结点的双向循环链表的头指针
    // 当第i个元素节点存在时，返回第i个结点
    DuLinkList p;
    p = va->next;
    int j = 1;
    while (p != va && j < i)
    { // 指针向后查找，直到p指向第i个元素或p为头结点
        p = p->next;
        ++j;
    }
    if (p == va && j < i)
        return NULL; // 第i个元素不存在
    else
        return p;
}

Status ListInsert_DuL(DuLinkList &L, int i, ElemType e)
{ // 算法2.18
    // 在带头结点的双链循环线性表L的第i个元素之前插入元素e
    // i的合法值为1≤i≤表长+1
    DuLinkList p, s;
    if (!(p = GetElemP_DuL(L, i))) // 在L中确定第i个元素的位置指针p
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
{ // 算法2.19
    // 删除带头结点的双联循环线性表L的第i个元素，i的合法值为1≤≤表长
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
{ // 遍历带头结点的双向循环链表中的元素，并打印
    DuLinkList p;
    p = L->next;
    printf("当前双向循环链表的元素为:\n");
    while (p != L)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void CreateList_L(LinkList &L, int n)
{ // 算法2.11
    // 逆位序输入（随机产生）n个元素的值，建立带表头结点的单链线性表L
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
{ // 算法2.8
    // L为带头结点的单链表的头指针。
    // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
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
{ // 算法2.9
    // 在带头结点的单链线性表L的第i个元素之前插入元素e
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
{ // 算法2.10
    // 在带头结点的单链线性表L中，删除第i个元素，并由e返回其值
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
{ // 算法2.12
    // 已知单链线性表La和Lb的元素按
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
{ // 遍历单链表中的元素并打印
    LinkList p;
    p = L->next;
    printf("当前单链表元素为：\n");
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
    // 单链表la的基本操作
    CreateList_L(la, 10);
    ListTraverse_L(la);
    printf("请输入需要查找的元素位置：\n");
    scanf("%d", &loc1);
    GetElem_L(la, loc1, e1);
    printf("链表中第%d个位置上的元素是：%d \n", loc1, e1);
    printf("请输入需要插入的位置及元素值：\n");
    scanf("%d %d", &loc2, &e2);
    ListInsert_L(la, loc2, e2);
    ListTraverse_L(la);
    printf("请输入需要删除的位置：\n");
    scanf("%d", &loc3);
    ListDelete_L(la, loc3, e3);
    printf("删除的元素为：%d\n", e3);
    ListTraverse_L(la);
    printf("\n");

    // 合并lb,lc至ld
    CreateList_L(lb, 0);
    CreateList_L(lc, 0);
    int i, j;
    for (i = 1; i <= 4; i++)
    {
        ListInsert_L(lb, i, i);
    }
    printf("待合并Lb:\n");
    ListTraverse_L(lb);

    for (j = 1; j <= 3; j++)
    {
        ListInsert_L(lc, j, j);
    }
    printf("待合并Lc:\n");
    ListTraverse_L(lc);
    MergeList_L(lb, lc, ld);
    printf("合并后的单链表：\n");
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

    printf("请输入需要插入的位置及元素值: \n");
    scanf("%d %d", &lod1, &a1);
    ListInsert_DuL(L, lod1, a1);
    ListTraverse_DuL(L);

    printf("请输入需要删除的位置: \n");
    scanf("%d", &lod2

    );
    ListDelete_DuL(L, lod2, a2);
    printf("删除的元素为:%d\n", a2);
    ListTraverse_DuL(L);
}
