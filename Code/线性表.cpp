
#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100 // 定义了顺序表的初始大小
#define LISTINCREMENT 10   // 每次扩容的增量。
#define OK 1               // 定义了函数执行状态的返回值。
#define ERROR 0
#define OVERFLOW -2
typedef int ElemType; // 定义了元素类型 ElemType 和状态类型 Status，均为整型。
typedef int Status;

/**
 * @description: 定义了顺序表的结构体，
 * 包含了元素数组 elem、当前长度 length 和表的大小 listsize。
 */
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

/**
 * @description: 初始化顺序表函数，为顺序表分配初始空间
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
 * @description: 在顺序表的指定位置插入元素的函数。
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
 * @description: 遍历顺序表并输出元素的函数
 * @param {SqList} &L
 * @return {*}
 */
void ListTraverse_Sq(SqList &L)
{
    printf("当前线性表的元素为：\n");
    for (int i = 0; i < L.length; i++)
    {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

/**
 * @description: 获取顺序表长度的函数
 * @param {SqList} &L
 * @return {*}
 */
int GetLength_Sq(SqList &L)
{
    return L.length;
}

void main()
{
    // 定义了顺序表 l，以及一些变量用于存储用户输入的元素和位置信息
    SqList l;
    ElemType e1;
    ElemType e2;
    ElemType e3;
    int loc1;
    int loc2;
    int loc3;

    // 调用初始化顺序表函数初始化顺序表 l
    InitList_Sq(l);
    int i;
    // 循环向顺序表中插入10个随机整数元素。
    for (i = 1; i <= 10; i++)
    {
        ListInsert_Sq(l, i, rand() % 50);
    }
    ListTraverse_Sq(l);
    printf("当前线性表长度是：%d\n", GetLength_Sq(l));

    printf("请输入需要插入的位置及元素值：\n");
    scanf("%d %d", &loc1, &e1);
    // 调用插入函数将元素插入指定位置
    ListInsert_Sq(l, loc1, e1);
    // 输出插入元素后的顺序表
    ListTraverse_Sq(l);
    printf("当前线性表的长度是：%d\n", GetLength_Sq(l));
}
