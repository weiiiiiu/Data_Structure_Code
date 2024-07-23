
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;

// 单链表的节点
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// 双向循环链表的节点
typedef struct DuLNode
{
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, *DuLinkList;

// 初始化一个带头结点的双向循环链表。
Status ListInit_DuL(DuLinkList &L)
{
    L = (DuLinkList)malloc(sizeof(DuLNode));
    if (!L)
        exit(OVERFLOW);
    L->prior = L; // 将链表的头节点的前驱和后继都设置为自身，这样就形成了一个只有一个节点（头节点）的双向循环链表
    L->next = L;
    return OK;
}

// 获取双向循环链表中第i个元素的指针。
DuLinkList GetElemP_DuL(DuLinkList va, int i)
{
    DuLinkList p;
    p = va->next; // 链表的第一个节点（头节点的下一个节点）
    int j = 1;
    while (p != va && j < i) // j==i时，p指向第i个元素
    {
        p = p->next;
        ++j;
    }
    if (p == va && j < i) // 没有找到第i个元素
        return NULL;
    else
        return p;
}

// 在双向循环链表的第i个元素之前插入一个新元素。
Status ListInsert_DuL(DuLinkList &L, int i, ElemType e)
{
    DuLinkList p, s;               // 定义两个指向DuLNode的指针p和s
    if (!(p = GetElemP_DuL(L, i))) // 链表中没有第i个元素，函数将返回ERROR
        return ERROR;
    if (!(s = (DuLinkList)malloc(sizeof(DuLNode)))) // 为新元素分配内存，并将返回的指针赋值给s。
        return ERROR;
    s->data = e;
    s->prior = p->prior; // 从原本p前元素开始处理
    p->prior->next = s;
    s->next = p;
    p->prior = s;
    return OK;
}

// 删除双向循环链表的第i个元素。
Status ListDelete_DuL(DuLinkList &L, int i, ElemType &e)
{
    DuLinkList p;
    if (!(p = GetElemP_DuL(L, i)))
        return ERROR;
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}

// 遍历双向循环链表并打印元素
void ListTraverse_DuL(DuLinkList &L)
{
    DuLinkList p;
    p = L->next; // 定义一个指向DuLNode的指针p，并将其初始化为链表的第一个节点（头节点的下一个节点）。
    printf("当前双向循环链表的元素为:\n");
    while (p != L)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 创建一个带头结点的单链表，元素值是随机生成的。
void CreateList_L(LinkList &L, int n)
{
    LinkList p;
    int i;
    srand((unsigned)time(NULL));         // 生成随机数种子
    L = (LinkList)malloc(sizeof(LNode)); // 创建头结点
    L->next = NULL;
    for (i = n; i > 0; --i)
    {
        p = (LinkList)malloc(sizeof(LNode)); // 创建新节点
        p->data = rand() % 50;
        p->next = L->next;
        L->next = p;
    }
}

// 获取单链表中第i个元素的值。
Status GetElem_L(LinkList &L, int i, ElemType &e)
{
    LinkList p;
    p = L->next;
    int j = 1;
    while (p && j < i) // 这个条件检查当前节点是否存在。如果p是NULL，说明已经到达了链表的末尾，而链表中没有第i个元素
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;
    e = p->data;
    return OK;
}

// 单链表的第i个元素之前插入一个新元素。
Status ListInsert_L(LinkList &L, int i, ElemType e)
{
    LinkList p, s;
    p = L; // p指向头结点
    int j = 0;
    while (p && j < i - 1) // p后插入新元素
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

// 删除单链表的第i个元素。
Status ListDelete_L(LinkList &L, int i, ElemType &e)
{
    LinkList p, q;
    p = L; // p指向头结点
    int j = 0;
    while (p->next && j < i - 1)
    {
        p = p->next; // 截止p为要删除元素的前驱节点
        ++j;
    }
    if (!(p->next) || j > i - 1)
        return ERROR;
    q = p->next; // q为要删除的节点
    p->next = q->next;

    e = q->data;
    free(q);
    return OK;
}

void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
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

int main()
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
