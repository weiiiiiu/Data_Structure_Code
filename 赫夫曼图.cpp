#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

/*������������*/
typedef struct
{
    int weight; // �ڵ�Ȩ��
    int parent; // ���ڵ�����
    int lchild; // ���ӽڵ�����
    int rchild; // ���ӽڵ�����
} HTNode, *HuffmanTree;

typedef char **HuffmanCode; // ����շ����������������

 * @param {int} i
 * @return {*}
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
 * @description: �ںշ�����HT��ǰi���ڵ��У�
 * �ҵ�����Ȩֵ��С��δ��ѡ�еĽڵ㣬�����ǵ������ֱ�ֵ��s1��s2
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

// ���ɺշ�������
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
    HuffmanTree HT;                          // �շ�����
    HuffmanCode HC;                          // �շ�������
    int w[8] = {5, 29, 7, 8, 14, 23, 3, 11}; // �ڵ�Ȩ��
    HuffmanCoding(HT, HC, w, 8);             // ����շ������������ɺշ�������
    for (int i = 1; i <= 8; i++)             // ����շ�������
        puts(HC[i]);
}