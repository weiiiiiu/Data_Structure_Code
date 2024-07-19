#include <stdio.h>
#include <stdlib.h> //malloc() 和 free()
#include <string.h> //strcmp()

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0

#define MAX_NAME 3                 // 顶点字符串最大长度
typedef char VertexType[MAX_NAME]; // 定义了 VertexType 为一个字符数组类型，用于存储顶点信息
typedef int InfoType;              // 用于存储弧相关的信息
typedef int QElemType;             // 用于队列元素的类型

/**
 * @description: 定义邻接表图的结构
 * @return {*}
 */
#define MAX_VERTEX_NUM 20 // 定义了顶点的最大数量为20
enum GraphKind            // 包含四种图的类型：有向图(DG)、有向网(DN)、无向图(UDG)、无向网(UDN
{
    DG,
    DN,
    UDG,
    UDN
};

/**
 * @description: // 定义了一个结构体ArcNode，用于表示图的弧节点，
 * 其中包含邻接顶点的下标、指向下一个弧节点的指针以及弧相关的信息指针
 * @return {*}
 */
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    InfoType *info; // 弧相关的信息指针。通常情况下直接指向一个数值变量，可表示权重等。
} ArcNode;

/**
 * @description: 定义了一个结构体 VNode，用于表示图的顶点节点，
 * 其中包含顶点信息和指向第一条依附该顶点的弧的指针。AdjList
 * 是顶点数组类型，其元素类型为 VNode，长度为 MAX_VERTEX_NUM
 * @return {*}
 */
typedef struct VNode
{
    VertexType data;   // 顶点信息
    ArcNode *firstarc; // 指向第一条依附该顶点的弧的指针
} VNode, AdjList[MAX_VERTEX_NUM];

/**
 * @description: 结构体 ALGraph，用于表示邻接表表示的图
 * @return {*}
 */
typedef struct ALGraph
{
    AdjList vertices; // 顶点数组
    int vexnum;       // 图当前顶点数
    int arcnum;       // 图当前的弧数
    int kind;         // 图的类型标志
} ALGraph;

/**
 * @description: 用于定位顶点 u 在图 G 中的位置
 * @return int
 */
int LocateVex(ALGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (strcmp(G.vertices[i].data, u) == 0)
            return i;
    return -1;
}

/**
 * @description: 用于创建无向图
 * @param {ALGraph} &G
 * @return void
 */
void CreateUDG(ALGraph &G)
{
    int i, j, k;
    ArcNode *p1, *p2;
    VertexType va, vb;
    G.kind = UDG;
    printf("请输入顶点数和边数（空格隔开）:\n");
    scanf("%d %d", &G.vexnum, &G.arcnum);
    printf("请输入 %d 个顶点内容（空格隔开）:\n", G.vexnum);
    for (i = 0; i < G.vexnum; i++)
    {
        scanf("%s", G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }

    for (k = 0; k < G.arcnum; k++)
    {
        printf("请输入第 %d 个条边的尾顶点，头顶点（空格隔开）\n", k + 1);
        scanf("%s %s", va, vb);
        i = LocateVex(G, va);
        j = LocateVex(G, vb);
        // 构造一个弧节点 * p1
        p1 = (ArcNode *)malloc(sizeof(ArcNode));
        p1->adjvex = j;
        //
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1;
        //
        p2 = (ArcNode *)malloc(sizeof(ArcNode));
        p2->adjvex = i;
        //
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2;
    }
}

/**
 * @description:
用于获取顶点 v 的第一个邻接顶点
 * @param {ALGraph} G
 * @param {VertexType} v
 * @return {*}
 */
int FirstAdjvex(ALGraph G, VertexType v)
{
    int i;
    i = LocateVex(G, v);
    if (G.vertices[i].firstarc)
        return G.vertices[i].firstarc->adjvex;
    else
        return -1;
}

/**
 * @description: 用于获取顶点 v 的邻接顶点 w 的下一个邻接顶点
 * @param {ALGraph} G
 * @param {VertexType} v
 * @param {VertexType} w
 * @return {*}
 */
int NextAdjvex(ALGraph G, VertexType v, VertexType w)
{
    int i, j;
    ArcNode *p;
    i = LocateVex(G, v);
    j = LocateVex(G, w);
    p = G.vertices[i].firstarc;
    while (p->nextarc && p->adjvex != j)
        p = p->nextarc;
    if (p->nextarc)
        return p->nextarc->adjvex;
    else
        return -1;
}

/**
 * @description: 标记顶点是否被访问过。
 * @return {*}
 */
bool visited[MAX_VERTEX_NUM];

/**
 * @description: 用于广度优先搜索遍历图
 * @param {ALGraph} &G
 * @return {*}
 */
void BFSTraverse(ALGraph &G)
{

    int v, w;
    QElemType u;
    QElemType Q[100];
    int front, rear;
    for (v = 0; v < G.vexnum; v++)
        visited[v] = FALSE;
    front = 0, rear = 0; // 置空辅助队列 Q
    for (v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            Q[rear++] = v;
            printf("%s", G.vertices[v].data);
            visited[v] = TRUE;
            while (front < rear)
            {                   // 队列非空
                u = Q[front++]; // 队头元素出队列并置为 u
                for (w = FirstAdjvex(G, G.vertices[u].data); w >= 0;
                     w = NextAdjvex(G, G.vertices[u].data, G.vertices[w].data))
                {
                    if (!visited[w])
                    {
                        Q[rear++] = w; // w 入队列
                        visited[w] = TRUE;
                        printf("%s", G.vertices[w].data);
                    }
                }
            }
        }
    }
    printf("\n");
}

int main()
{

    ALGraph G;    // 声明了一个名为 G 的邻接表图
    CreateUDG(G); // 调用函数 CreateUDG() 来创建无向图
    printf("广度遍历的次序为：");
    BFSTraverse(G);
}