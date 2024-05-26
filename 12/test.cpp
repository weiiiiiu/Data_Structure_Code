#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
#define MAX_NAME 5 // 顶点字符串最大长度
#define MAX_INFO 20
// 定义顶点类型，顶点类型是一个 5 个字符长度的字符串

typedef char VertexType[MAX_NAME];
// 定义弧度量信息单位类型为整型
typedef int VRType;
// 定义弧说明信息
typedef char InfoType;
/* 定义邻接矩阵图结构：
   MGraph 表示邻接矩阵图；
   ArcCell 表示弧变量；
   AdjMatrix 表示邻接 (adj) 矩阵 (Matrix)
*/
// 用整型最大值表示不可达
#define INFINITY INT_MAX
// 定义一个图中最多顶点数不超过 26 个
#define MAX_VERTEX_NUM 26
// 定义图类型名
enum GraphKind
{
    DG,
    DN,
    UDG,
    UDN
};
// 定义弧结构
typedef struct
{
    // 描述两个顶点之间的联系信息
    // 对于无权图而言，用整型 0,1 表示两者是否相邻
    // 对于有权图而言，是权值类型
    VRType adj;
    InfoType *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 定义图结构
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;
    int vexnum;
    int arcnum;
    GraphKind kind;
} MGraph;

/*
// 访问定点内容的操作函数
Void visit (VertexType e){
   printf ("% s",e);
}
*/

/* 在顶点数组中定位元素的序号 */
int LocateVex(MGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (strcmp(G.vexs[i], u) == 0)
            return i;
    return -1;
}

/* 从文件中创建无向网 */
void CreateFUDN(MGraph &G)
{
    int i, j, k, w;
    VertexType va, vb; // 顶点元素内容
    FILE *file;
    file = fopen("fudn.txt", "r");
    // 读入元素的个数和弧的个数
    fscanf(file, "%d", &G.vexnum); // fscanf 从一个流中执行格式化输入，fscanf 遇到空格和换行时结束
    fscanf(file, "%d", &G.arcnum); //% d: 读入一个十进制整数
    // 把顶点元素的内容读入到数组中
    for (i = 0; i < G.vexnum; i++)
        fscanf(file, "%s", &G.vexs[i]); //% s: 读入一个字符串，遇空格结束
    // 初始化邻接矩阵
    for (i = 0; i < G.vexnum; i++)
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j].adj = INFINITY;
            G.arcs[i][j].info = NULL;
        }
    // 输入弧
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
/* 获得指定元素内容的第一个邻接顶点序号
  在邻接矩阵中 i 行元素反应了以 i 顶点出发的所有出弧；
  在邻接矩阵中 j 行元素反应了以 j 顶点出发的所有出弧；
  顶点的第一个邻接顶点指第 i 行上第一个不等于默认值的元素的列号对应的顶点

  注意：邻接矩阵中默认的弧次序，是按照邻接顶点序号确定的

*/
int FirstAdjVex(MGraph G, VertexType v)
{
    int i, j, k = 0;
    i = LocateVex(G, v);
    if (G.kind % 2) // 奇数为网，小于 2 为有向边 DG,DN,UDG,UDN
        k = INFINITY;
    for (j = 0; j < G.vexnum; j++)
        if (G.arcs[i][j].adj != k)
            return j;
    return -1;
}
/* 获得指定元素以及它的某个邻接点之后，要求获得下一个邻接顶点序号 */
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

/* 深度优先遍历图：
访问起始点 v;
若 v 的第 1 个邻接点没访问过，深度遍历此邻接点；
若当前邻接点已访问过，再找 v 的第 2 个邻接点重新遍历。
*/

// oid (*VisitFunc)(VertexType v);    // 定义了一个全局的函数变量

bool visited[MAX_VERTEX_NUM]; // 定义一个访问的标志数组

void DFS(MGraph G, int v)
{ // 深度遍历访问从 v 开始的图
    int w;
    visited[v] = TRUE; // 设置当前顶点被访问过
    printf("%s", G.vexs[v]);
    for (w = FirstAdjVex(G, G.vexs[v]); w >= 0; w = NextAdjVex(G, G.vexs[v], G.vexs[w]))
        if (!visited[w])
            DFS(G, w);
}
void DFSTraverse(MGraph G)
{
    int v;
    for (v = 0; v < G.vexnum; v++)
        visited[v] = FALSE;
    for (v = 0; v < G.vexnum; v++)
        if (!visited[v])
            DFS(G, v);
}
int main()
{
    MGraph G;
    // 从文件创建无向网
    CreateFUDN(G);
    printf("当前图按照深度遍历的次序为:\n");
    DFSTraverse(G); // a b d h c g f e
    printf("\n");
}