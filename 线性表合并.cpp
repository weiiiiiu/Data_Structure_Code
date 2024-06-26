
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType *elem; // 元素指针
    int length;     // 线性表的当前长度
    int listsize;   // 线性表当前分配的大小
} SqList;

Status lnitList_Sq(SqList &L)
{
    // 初始化一个顺序线性表L。
    // 根据初始大小分配内存空间。
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        return OVERFLOW;         // 内存分配失败。
    L.length = 0;                // 将长度初始化为0
    L.listsize = LIST_INIT_SIZE; // 初始存储容量
    return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    // 在顺序线性表L的第i个位置之前插入一个新元素e。
    // i 应该在范围 1 <= i <= ListLength_Sq(L)+1 内。
    ElemType *p;
    if (i < 1 || i > L.length + 1)
        return ERROR; // i 的值不合法
    if (L.length >= L.listsize)
    {
        // 如果当前存储空间已满，则增加容量
        ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return OVERFLOW;         // 内存分配失败
        L.elem = newbase;            // 更新基地址
        L.listsize += LISTINCREMENT; // 增加存储容量
    }
    ElemType *q = &(L.elem[i - 1]);                // &是求地址 *求指针存储元素 要插入的位置
    for (p = &(L.elem[L.length - 1]); p >= q; --p) // 最后的元素先动 前面元素才能动
        *(p + 1) = *p;
    *q = e;     // 插入 e
    ++L.length; // 增加长度
    return OK;
}

void ListTraverse_Sq(SqList &L)
{
    // 遍历顺序线性表并打印其元素。
    printf("当前线性表的元素为：\n");
    for (int i = 0; i < L.length; i++)
    {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

int GetLength_Sq(SqList &L)
{
    // 获取顺序线性表的长度
    return L.length;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    // 删除顺序线性表L中的第i个元素，并将其值保存在e中。
    // i 应该在范围 1 ≤ i ≤ ListLength_Sq(L) 内。
    ElemType *p;
    if ((i < 1) || (i > L.length))
        return ERROR;
    p = &(L.elem[i - 1]);                // 要删除的元素
    e = *p;                              // 保存删除的元素
    ElemType *q = L.elem + L.length - 1; // 最后一个元素
    for (++p; p <= q; ++p)               // 从删除的元素开始，后面的元素前移
        *(p - 1) = *p;
    --L.length;
    return OK;
}

/**
 * @description:    查找顺序线性表L中第一个与e匹配的元素的位置。
 * 如果找到，返回其在L中的位置，否则返回0。
 * @param {SqList} L
 * @param {ElemType} e
 * @return {*}
 */
int LocateElem_Sq(SqList L, ElemType e)
{

    int i;
    ElemType *p;
    i = 1;
    p = L.elem;
    while (i <= L.length && !(*p++ == e)) // 一直没找到i就一直加
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

/**
 * @description: 有序顺序线性表 La 和 Lb 合并新有序顺序线性表 Lc。
 * @param {SqList} La
 * @param {SqList} Lb
 * @param {SqList} &Lc
 * @return {*}
 */
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
    // 分别用于指向La的当前元素（pa）、Lb的当前元素（pb）、Lc的当前元素（pc）、La的最后一个元素（pa_last）和Lb的最后一个元素（pb_last）。
    ElemType *pa, *pb, *pc, *pa_last, *pb_last;
    pa = La.elem;
    pb = Lb.elem;
    Lc.listsize = Lc.length = La.length + Lb.length;
    pc = Lc.elem = (ElemType *)malloc(Lc.listsize * sizeof(ElemType));
    if (!Lc.elem)
        exit(OVERFLOW);
    pa_last = La.elem + La.length - 1;
    pb_last = Lb.elem + Lb.length - 1;

    // 当有序表La和Lb都有剩余元素时，比较当前元素的大小，并将较小的元素添加到Lc中。
    while (pa <= pa_last && pb <= pb_last)
    {
        if (*pa <= *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while (pa <= pa_last)
        *pc++ = *pa++;
    while (pb <= pb_last)
        *pc++ = *pb++;
}

int main()
{
    SqList l;
    ElemType e1, e2, e3;
    int loc1, loc2, loc3;

    lnitList_Sq(l);
    int i;
    for (i = 1; i <= 10; i++)
    {
        ListInsert_Sq(l, i, rand() % 50);
    }
    ListTraverse_Sq(l);
    printf("当前线性表长度是：%d\n", GetLength_Sq(l));

    // 在指定位置插入一个元素
    printf("请输入需要插入的位置及元素值：\n");
    scanf("%d %d", &loc1, &e1);
    ListInsert_Sq(l, loc1, e1);
    ListTraverse_Sq(l);
    printf("当前线性表长度是：%d\n", GetLength_Sq(l));

    // 删除指定位置的元素
    printf("请输入需要删除的位置：\n");
    scanf("%d", &loc2);
    ListDelete_Sq(l, loc2, e2);
    printf("删除的元素为:%d\n", e2);
    ListTraverse_Sq(l);
    printf("当前线性表长度是:%d\n", GetLength_Sq(l));

    // 查找指定元素的位置
    printf("请输入想要查找的元素值:\n");
    scanf("%d", &e3);
    loc3 = LocateElem_Sq(l, e3);
    printf("刚刚查找的元素位置为:%d\n", loc3);
    printf("\n");

    // 合并两个有序线性表
    SqList la, lb, lc;
    lnitList_Sq(la);
    lnitList_Sq(lb);
    for (i = 1; i <= 5; i++)
    {
        ListInsert_Sq(la, i, rand() % 50);
    }
}