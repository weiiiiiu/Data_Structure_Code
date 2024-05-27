#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义了一些常量和类型
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
#define MAX_NAME 5
#define MAX_INFO 20

typedef char VertexType[MAX_NAME]; // 顶点类型
typedef int VRType;                // 边的权值类型
typedef char InfoType;             // 附加信息类型

#define INFINITY INT_MAX  // 无穷大，用于表示无边
#define MAX_VERTEX_NUM 26 // 最大顶点数

// 图的类型：有向图、有向网、无向图、无向网
enum GraphKind
{
    DG,
    DN,
    UDG,
    UDN
};

// 弧的定义（用于邻接矩阵），包括权值和附加信息
typedef struct
{
    VRType adj;
    InfoType *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 图的定义，包括顶点数组、邻接矩阵、顶点数、边数和图的类型
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum;
    int arcnum;
    GraphKind kind;
} MGraph;

// 在图中查找给定的顶点，返回其位置，如果不存在，则返回-1
int LocateVex(MGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (strcmp(G.vexs[i], u) == 0)
            return i;
    return -1;
}

// 从文件"fudn.txt"中读取图的信息并创建图
void CreateFUDN(MGraph &G)
{
    int i, j, k, w;
    VertexType va, vb;
    FILE *file;
    file = fopen("fudn.txt", "r");
    fscanf(file, "%d", &G.vexnum);
    fscanf(file, "%d", &G.arcnum);
    for (i = 0; i < G.vexnum; i++)
        fscanf(file, "%s", &G.vexs[i]);
    for (i = 0; i < G.vexnum; i++)
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j].adj = INFINITY;
            G.arcs[i][j].info = NULL;
        }
    for (k = 0; k < G.arcnum; k++)
    {
        fscanf(file, "%s%s%d", va, vb, &w);
        i = LocateVex(G, va);
        j = LocateVex(G, vb);
        G.arcs[i][j].adj = w;
        G.arcs[j][i].adj = w;
    }
    fclose(file);
    G.kind = UDN;
}

// 找到给定顶点的第一个邻接顶点，如果不存在，则返回-1
int FirstAdjVex(MGraph G, VertexType v)
{
    int i, j, k = 0;
    i = LocateVex(G, v);
    if (G.kind % 2)
        k = INFINITY;
    for (j = 0; j < G.vexnum; j++)
        if (G.arcs[i][j].adj != k)
            return j;
    return -1;
}

// 找到给定顶点的下一个邻接顶点，如果不存在，则返回-1
int NextAdjVex(MGraph G, VertexType v, VertexType w)
{
    int a, b, i, k = 0;
    a = LocateVex(G, v);
    b = LocateVex(G, w);
    if (G.kind % 2)
        k = INFINITY;
    for (i = b + 1; i < G.vexnum; i++)
        if (G.arcs[a][i].adj != k)
            return i;
    return -1;
}

// 访问标志数组
bool visited[MAX_VERTEX_NUM];

// 深度优先搜索
void DFS(MGraph G, int v)
{
    int w;
    visited[v] = TRUE;
    printf("%s", G.vexs[v]);
    for (w = FirstAdjVex(G, G.vexs[v]); w >= 0; w = NextAdjVex(G, G.vexs[v], G.vexs[w]))
        if (!visited[w])
            DFS(G, w);
}

// 深度优先遍历
void DFSTraverse(MGraph G)
{
    int v;
    for (v = 0; v < G.vexnum; v++)
        visited[v] = FALSE;
    for (v = 0; v < G.vexnum; v++)
        if (!visited[v])
            DFS(G, v);
}

// 主函数
int main()
{
    MGraph G;
    CreateFUDN(G);
    printf("当前图按照深度遍历的次序为:\n");
    DFSTraverse(G);
    printf("\n");
}