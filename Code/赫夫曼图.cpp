#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

/*定义数据类型*/
typedef struct
{
    int weight; // 节点权重
    int rchild; // 右子节点索引
    int lchild; // 左子节点索引
    int parent; // 父节点索引
} HTNode, *HuffmanTree;

typedef char **HuffmanCode; // 定义赫夫曼编码的数据类型

/**
 * @description:  找到权值最小且未被选中（即其parent属性为0）的节点的索引
 * @param {HuffmanTree} &HT
 * @param {int} i
 * @return {*}
 */
int min(HuffmanTree &HT, int i)
{
    int j, flag;
    int minv = 32767;
    for (j = 1; j <= i; j++)
        if (minv > HT[j].weight && HT[j].parent == 0)
        {
            minv = HT[j].weight;
            flag = j;
        }
    HT[flag].parent = 1;
    return flag;
}

/**
 * @description: 在赫夫曼树HT的前i个节点中，
 * 找到两个权值最小且未被选中的节点，将它们的索引分别赋值给s1和s2
 * @return {*}
 */
void Select(HuffmanTree &HT, int i, int &s1, int &s2)
{
    int t;
    s1 = min(HT, i);
    s2 = min(HT, i);
    if (s1 > s2)
    {
        t = s1;
        s1 = s2;
        s2 = t;
    }
}

// 生成赫夫曼编码
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
    int m, i, j;
    int s1, s2;
    int start;
    char *cd;
    HuffmanTree p;
    if (n <= 1)
        return;
    m = 2 * n - 1;
    HT = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1));
    if (!HT)
        exit(OVERFLOW);
    for (p = HT + 1, i = 1; i <= n; i++, w++, p++)
    {
        p->weight = *w;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }
    for (; i <= m; ++i, ++p)
    {
        p->weight = 0;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }
    for (i = n + 1; i <= m; i++)
    {
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
    cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for (i = 1; i <= n; i++)
    {
        start = n - 1;
        for (j = i; j < m; j = HT[j].parent)
            if (HT[HT[j].parent].lchild == j)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        HC[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
}

int main()
{
    HuffmanTree HT;                          // 赫夫曼树
    HuffmanCode HC;                          // 赫夫曼编码
    int w[8] = {5, 29, 7, 8, 14, 23, 3, 11}; // 节点权重
    HuffmanCoding(HT, HC, w, 8);             // 构造赫夫曼树，并生成赫夫曼编码
    for (int i = 1; i <= 8; i++)             // 输出赫夫曼编码
        puts(HC[i]);
}