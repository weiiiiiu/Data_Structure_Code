#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int KeyType;

typedef struct
{
    KeyType key;
} ElemType;

typedef struct
{
    ElemType *elem;
    int length;
} SSTable;

Status Create_SSTable(SSTable &ST)
{
    ST.elem = (ElemType *)malloc((TABLE_SIZE + 1) * sizeof(ElemType));
    if (!ST.elem)
        return OVERFLOW;
    ST.length = TABLE_SIZE;
    return OK;
}

int Search_Seq(SSTable ST, KeyType key)
{
    int i = 0;
    ST.elem[0].key = key;
    for (i = ST.length; ST.elem[i].key != key; --i)
        ;
    return i;
}

int Search_Bin(SSTable ST, KeyType key)
{
    int low, high, mid;
    low = 1;
    high = ST.length;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (key == ST.elem[mid].key)
            return mid;
        else if (key < ST.elem[mid].key)
            high = mid - 1;

        else
            low = mid + 1;
    }
    return 0;
}

void Traverse_SSTable(SSTable ST)
{
    printf("当前静态查找表中的关键字为: ");
    for (int i = 1; i <= ST.length; i++)
    {
        printf("%d	", ST.elem[i].key);
    }
    printf("\n");
}

int main()
{
    SSTable ST;
    int i;
    KeyType key1, key2;
    int result1, result2;
    Create_SSTable(ST);
    for (i = 1; i <= ST.length; i++)
    {
        ST.elem[i].key = i;
    }
    Traverse_SSTable(ST);
    printf("请输入需要顺序查找的关键字: \n");
    scanf("%d", &key1);
    result1 = Search_Seq(ST, key1);
    if (!result1)
        printf("顺序查找失败!表中不存在该关键字。 \n");
    else
        printf("顺序查找成功!该关键字在表中的位置为: %d\n", result1);
    printf("请输入需要折半查找的关键字: \n");
    scanf("%d", &key2);
    result2 = Search_Bin(ST, key2);
    if (!result2)
        printf("折半查找失败!表中不存在该关键字。 \n");
    else
        printf("折半查找成功!该关键字在表中的位置为:%d\n", result2);
}