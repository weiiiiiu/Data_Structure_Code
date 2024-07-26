# 代码

赋值号记为等号会不会好记一点    给出图片中代码 注释以及伪代码

## 线性表数组实现（顺序表）

> 基于数组

```c
typedef struct seqList
{
  int n;									// 顺序表的长度
  int maxLength;					// 顺序表的最大允许长度
  ElemType *element;  	  // 指针 element 指向顺序表的存储空间的首地址
}SeqList;
```

### 遍历数组

```c
int main() {
    int a[10]; // 定义一个大小为10的整数数组
    
    // 通过循环从用户输入读取10个整数并存储到数组中
    for (int i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }

    return 0;
}

```

### 顺序表查找

```c
Bool Find(SeqList L, int i, ElemType *x)
{
  //越界判断
  if(i<0 || i>L.n-1)
    return 0;
 
  *x = L.element[i];
  return 1;
}


int find(SeqList L, int x) {
    // 遍历顺序表中的所有元素
    for (int i = 0; i < L.n; i++) {
        // 如果找到元素 x，返回其位置 i+1（假设返回1表示第一个位置）
        if (x == L.element[i])
            return 1;
    }
    // 如果未找到元素 x，返回 0
    return 0;
}

```

### 顺序表的插入

```c
Bool Insert(SeqList L, int i, ElemType x)
{
  int j;
  if(i<-1 || i>L->n-1)									// 判断下标 i 是否越界
    return 0;
  if(L->n == L->maxLength)						 	// 判断顺序表存储空间是否已满
    return 0;
  
  for(j = L->n-1; j>i; j--)
    L->element[j+1] = L->element[j];	 	// 从前往后逐个后移元素
  
  L->element[i+1] = x;									// 将新元素 x 放入下标 i+1 的位置
  L->n = L->n +1;
  return 1;
}
```

顺序表插入算法的平均时间复杂度为 O(n)，插入一个新元素时需移动元素的平均次数为
$$
E_i = \sum_{i=-1}^{n-1}{n-i-1} = \frac{n}{2}
$$

### 顺序表的删除

```c
Bool Delete(SeqList L, int i, ElemType x)
{
  int j;
  if(i<0 || i>L->n-1)										// 判断下标 i 是否越界
    return 0;
  if(!L->n)						 									// 判断顺序表是否为空
    return 0;
  
  for(j = i+1; j<L->n; j++)
    L->element[j-1] = L->element[j]; 		// 从前往后逐个前移元素
  L->n--;																// 表长减 1
  return 1;
}
```

顺序表删除算法的平均时间复杂度为 O(n)，删除一个新元素时需要移动元素的平均次数为
$$
E_d = \sum_{i=0}^{n-1}{n-i-1} = \frac{n-1}{2}
$$





## 线性表链表实现（链表）

> 第一个元素所在的节点为头结点  存放头结点地址的指针为头指针first  空链表则first指向NULL 链表尾节点指针域指向NULL

### 定义

```c
typedef struct node
{
  ElemType element;					// 结点的数据域
  struct node *link;				// 结点的指针域
}Node;

typedef struct singleList
{  
  Node *first;              //存放头结点地址的指针
  int n;                    //元素个数
}SingleList;
```

### 单链表的查找

```c
Bool find(SingleList L, int x)
{
    Node* P;
    P = L->first;  // P指向链表的第一个节点
    while (P != NULL)  // 遍历链表直到链表结束
    {
        if (P->element == x)  // 如果找到元素 x
            return 1;
        P = P->link;  // P指向下一个节点
    }
    return 0;  // 未找到元素 x，返回 0
}

```

### 单链表中查找第 `i` 个节点的值

```c
int find(SingleList L, int i)
{
    if (i <= 0 || i > L.n) return -1;  // 检查 i 是否在合法范围内
    Node* P = L->first;                   // P 指向链表的第一个节点
    while (i > 0)  // 遍历链表直到找到第 i 个节点
    {
        P = P->link;  // P 指向下一个节点
        i--;  // 减少 i 的值
    }
    return P->element;  // 返回第 i 个节点的值
}

```

### 单链表的非头插入p q

```c
void Add(SingleList *L, Node *p, Node *q)
{
    q->link = p->link;  // 将节点 q 的 link 指针指向节点 p 的下一个节点 (p->link)
    p->link = q;        // 将节点 p 的 link 指针指向节点 q
    L->n++;             // 更新链表的长度
}

```

### 单链表插入一个节点 `q` 到第 `i` 个位置之后

```c
Bool Add(SingleList *L, int i)
{
    // 判断越界
    if (i < 0 || i >= L->n)
        return 0;
        
    Node *p = L->first;  // 从头节点开始
    while (i > 0)
    {
        p = p->link;  // 移动到第 i 个节点
        i--;
    }
    
    // 插入操作
    q->link = p->link;  // 新节点 q 的 link 指向 p 的下一个节点
    p->link = q;        // p 的 link 指向新节点 q
    
    L->n++;  // 更新链表长度
    
    return 1;
}

```

### 单链表中第 `i` 个位置插入一个值为 `x` 的新节点

```c
Bool Add(SingleList *L, int i, int x)
{
    // 判断越界
    if (i < 0 || i > L->n) return 0;

    // 分配内存给新节点并赋值
    Node *q = (Node*)malloc(sizeof(Node));
    q->element = x;

    Node *p = L->first;
    while (i > 0)
    {
        p = p->link;  // 移动到第 i 个节点
        i--;
    }
    
    // 插入操作
    q->link = p->link;  // 新节点 q 的 link 指向 p 的下一个节点
    p->link = q;        // p 的 link 指向新节点 q

    L->n++;  // 更新链表长度

    return 1;
}
```

### 头插

```c
//非头部插入
    q->link = p->link;  
    p->link = q; 
//头部插入
	q->link = L->first;  
	L->first = q;
```

### 单链表删除一个节点

```c
void Delete(SingleList *L)
{
    Node* p = L->first;   //将指针 p 初始化为指向链表的第一个节点

    while (p->link != q)
        p = p->link;      //找到指向目标节点 q 的前驱节点 p

    p->link = q->link;    //将前驱节点 p 的 link 指针指向目标节点 q 的下一个节点
    free(q);
    L->n--;
}
```

### 单链表中删除指定元素节点

```c
void Delete(SingleList *L)
{
    Node *p = L->first, *q = p, *k;    //将指针 p 和 q 初始化为指向链表的第一个节点，指针 k 用于临时存储中间节点

    //找到元素为 a 的前驱节点
    while (p->link->element != a)    
    {
        p = p->link;
        k = p->link;
    }

    //找到元素为 b 的节点
    while (q->element != b) 
    {
        q = q->link;
    }

    k->link = q;
    p->link = q;
}
```

### 单链表中删除指定值的节点

```c
void Delete(SingleList *L, int x)
{
    Node *p = L->first, *q;

    //找到值为 x 的节点
    while (p != NULL)
    {
        while (p->link->element != x) 
        {
            p = p->link;
        }

        q = p->link;
        p->link = p->link->link;
        free(q);
        L.n--;
    }
}
/*
将指针 q 指向要删除的节点。
修改前驱节点 p 的 link 指针，跳过要删除的节点 q，指向下一个节点。
释放 q 指向的节点内存。
更新链表节点计数 L.n。
*/
```

### 顺序表逆置

```c
void Reverse(SeqList *L)
{
    int temp;
    for (int i = 0; i < L->n / 2; i++)
    {
        temp = L->element[i];
        L->element[i] = L->element[L->n - i - 1];
        L->element[L->n - i - 1] = temp;
    }
}
```

### ???顺序表删除某个区间内的节点

```c
void Delete(SingleList *L)
{
    Node *p = L->first, *q = p, *k;

    while (p->link->element != a) {
        p = p->link;
    }
    k = p->link;
    
    while (q->element != b) {
        q = q->link;
    }
    q = q->link;
    p->link = q;
    while(k->link != q){
      p = p->link;
      free(k);
      k = p;
      L.n--;
    }
}
```

### 带表头节点 找到最小 插到最前面（考试画阴影）

```c
void MoveMinToHead(SingleList *L)
{
    Node *p = L->first;
    int min = p->element;
    while (p != NULL)
    {
        if (p->element < min)
            min = p->element;
        p = p->link;        //p指向最小节点
    }

    Node *q = L->first;     //q跟first都是指向第一个节点
    while (q->link->element != min)
        q = q->link;        //q指向最小节点前一个节点
    q = L.first;
  	p->link = L->first; 
    L->first = q;
}
```

### 两个单链表 `LA` 和 `LB` 的合并，并将结果存储在新链表 `LC` 

```c
void Move(SingleList *LA, SingleList *LB, SingleList *LC)
{
    Node *PA, *PB, *PC;
  	int min;
    PA = LA->first;
    PB = LB->first;
    PC = LC->first;

    // 遍历链表 LA 和 LB，直到其中一个到达末尾
    while (PA != NULL && PB != NULL)
    {
        if (PA->element < PB->element)
        {
            min = PA->element;
            PA = PA->link; // PA 指向下一个节点
        }
        else
        {
            min = PB->element;
            PB = PB->link; // PB 指向下一个节点
        }

        // 创建一个新节点 q 并将其元素设置为 min
        Node *q = (Node *)malloc(sizeof(Node));
        q->element = min;

        // 插入 q 到链表 LC 的尾部
        PC->link = q;
        PC = q;
        q->link = NULL;
        LC->n++;
    }

    // 如果 PA 不为空，将剩余的 PA 链接到 LC
    if (PA != NULL && PB == NULL)
    {
        PC->link = PA;
        LC->n++;
    }

    // 如果 PB 不为空，将剩余的 PB 链接到 LC
    if (PB != NULL && PA == NULL)
    {
        PC->link = PB;
        LC->n++;
    }
}
```

### 单链表中删除第 `i` 个元素

```c
bool Delete(SingleList *L, int i)
{
    // 如果 i 的值无效（小于 1 或大于链表长度），返回 false
    if (i <= 0 || i > L->n) return 0;

    // 初始化指针 p 和临时指针 q
    Node *p = L->first, *q;

    // 遍历链表找到第 i-1 个节点
    for (int j = 0; j < i - 2; j++)
        p = p->link;

    // q 指向第 i 个节点
    q = p->link;

    // 将第 i 个节点从链表中移除
    p->link = p->link->link;

    // 释放第 i 个节点的内存
    free(q);

    // 链表长度减 1
    L->n--;

    // 返回 true，表示删除成功
    return 1;
}
```

### 两个数组（或链表）之间的交集

```c
int C[100], int k = 0; // 定义结果数组 C 和索引 k

// 遍历数组 A
for (int i = 0; i < A.n; i++)
{
    // 遍历数组 B
    for (int j = 0; j < B.n; j++)
    {
        // 如果 A[i] 等于 B[j]
        if (A.element[i] == B.element[j])
        {
            // 将 A[i] 添加到结果数组 C 中
            C[k++] = A.element[i];
        }
    }
}
```

### 两个单链表 `A` 和 `B` 中的公共元素

```c
void FindCommonElements(SingleList *A, SingleList *B)
{
    Node *PA = A->first; // 定义指向链表 A 的指针 PA，初始指向链表 A 的第一个节点
    Node *PB; // 定义指向链表 B 的指针 PB

    while (PA != NULL) // 遍历链表 A
    {
        PB = B->first; // 每次开始遍历 B 之前，将 PB 重置为指向链表 B 的第一个节点
        while (PB != NULL) // 遍历链表 B
        {
            if (PA->element == PB->element) // 如果 PA 指向的元素等于 PB 指向的元素
            {
                printf("%d ", PA->element); // 输出公共元素
                break; // 找到公共元素后，跳出内层循环
            }
            PB = PB->link; // 移动 PB 指针到下一个节点
        }
        PA = PA->link; // 移动 PA 指针到下一个节点
      	PB = B->first;
    }
}
```

## 顺序栈定义

```c
typedef struct stack
{
  int top;
  int maxSize;
  ElemType *element     //数组
}Stack;
```

```c
//入栈
S.element[++top]  //top指向-1  移top再赋值
S.element[top++]  //top指向0   先赋值后移top
//出栈
S.element[--top]   
S.element[top--]
```

## 队列定义

```c
typedef struct queue
{
  int front;
  int rear;
  int maxSize;
  ElemType *element;
}Queue;
```

## 二叉树

### 定义

```c
//节点
typedef struct btnode {
    ElemType element;
    struct btnode* lChild;
    struct btnode* rChild;
} BTNode;

//树
typedef struct binarytree {
		BTNode *root;              // 指向二叉树根节点的指针
} BinartTree;
```

### 先序遍历

```c
void PreOrderTree(BinaryTree *bt)
{
  PreOrder(bt->root);
}

void PreOrder(BTNode *T)
{
  if(!T)
    return;
  
  printf("%c", T->element);
  PreOrder(T->lChild);
  PreOrder(T->rChild);
}
```

### 中序遍历

```c
void InOrderTree(BinaryTree *bt)
{
  InOrder(bt->root);
}

void InOrder(BTNode *T)
{
  if(!T)
    return;
  
  InOrder(T->lChild);
  printf("%c", T->element);
  InOrder(T->rChild);
}
```

### 后序遍历

```c
void PostOrderTree(BinaryTree *bt)
{
  InOrder(bt->root);
}

void PostOrder(BTNode *T)
{
  if(!T)
    return;
  
  PostOrder(T->lChild);
  PostOrder(T->rChild);
  printf("%c", T->element);
}
```

### 先序构造二叉树

```c
BTNode* PreCreateBT(BTNode *t)
{
    int x;
    scanf("%d", &x); // 从输入中读取一个整数
    if (x == 0)      // 如果读取的整数是0，那么创建一个空节点
        T = NULL;
    else
    {
        // 为新的节点分配内存
        T = (binary_tree_node *)malloc(sizeof(binary_tree_node));
        T->data = x;                   // 将读取的整数赋值给新节点的数据域
        Binary_tree_Create(T->lchild); // 递归地创建左子树
        Binary_tree_Create(T->rchild); // 递归地创建右子树
    }
    return t;
}

void PreMakeTree(BinaryTree *bt){
  bt->root = PreCreate(bt->root);
}
```

### 交换二叉树的左右子树

```c
// 交换二叉树左右子树的函数
void SwapTree(BinaryTree *bt) {
    Swap(bt->root);
}

// 递归函数：交换二叉树节点的左右子树
void Swap(BTNode *t) {
    if (!t) return;
    BTNode *temp = t->lChild;
    t->lChild = t->rChild;
    t->rChild = temp;
    Swap(t->lChild);
    Swap(t->rChild);
}
```

不需要管具体实现 按照实现逻辑写

### 二叉树求节点个数

```c
// 计算二叉树 bt 中非叶子节点的数量
int CountTree(BinaryTree *bt)
{
    return Count(bt->root);
}

// 计算以 t 为根节点的子树中非叶子节点的数量
int Count(BINode *t)
{
    if (!t) // 如果 t 为空，返回 0
        return 0;
		return 1 + Count(t->lChild) + Count(t->rChild); // 返回 1 加上左子树和右子树中的非叶子节点数量
}
```

### 二叉树叶节点的个数

```c
// 计算二叉树 bt 中非叶子节点的数量
int CountTree(BinaryTree *bt)
{
    return Count(bt->root);
}

// 计算以 t 为根节点的子树中非叶子节点的数量
int Count(BINode *t)
{
    if (!t) // 如果 t 为空，返回 0
        return 0;

    if (t->lChild != NULL || t->rChild != NULL) // 如果 t 有左子节点或右子节点   ||短路特性  否条件
        return Count(t->lChild) + Count(t->rChild); // 不是叶子结点继续递归
    else
        return 1; // 自己是 ➕1
}
```

### 二叉树度为2的节点

```c
// 统计二叉树中度为2的节点个数
int CountTree(BinaryTree *bt) {
    return Count(bt->root);
}

// 递归函数：统计度为2的节点个数
int Count(BINode *t) {
    if (!t) return 0;
    if (t->rChild != NULL && t->lChild != NULL)
        return Count(t->rChild) + Count(t->lChild) + 1;   //自己是 ➕自己
    else
        return Count(t->rChild) + Count(t->lChild);      //自己不是不加自己
}
```

### 二叉树度为1

```c
// 统计二叉树中度为1的节点个数
int CountTree(BinaryTree *bt) {
    return Count(bt->root);
}

// 递归函数：统计度为1的节点个数
int Count(BINode *t) {
    if (!t) return 0;
    if ((t->rChild != NULL && t->lChild == NULL) || (t->rChild == NULL && t->lChild != NULL))
        return Count(t->rChild) + Count(t->lChild) + 1;
    else
        return Count(t->rChild) + Count(t->lChild);
}
```

### 计算二叉树高度(左右子树判断)

```c
// 计算二叉树高度
int HeightTree(BinaryTree *bt) {
    return Height(bt->root);
}

// 递归函数：计算二叉树节点高度
int Height(BINode *t) {
    if (!t) return 0;
    return max(Height(t->rChild), Height(t->lChild)) + 1;
}


/*
对每个节点 t，函数会分别递归计算其左右子树的高度，然后取两者的最大值，加 1 得到当前节点的高度。
递归会一直展开到叶子节点（即没有子节点的节点），叶子节点的高度为 1。
最终递归层层返回，根节点的高度即为整棵树的高度。
*/
```

### 判断一棵树是否为满二叉树（节点数与高度判断）

```c
Bool CheckFullTree(BinaryTree *bt) {
    return CheckFull(bt->root);
}

int Height(BINode *t) {
    // 实现不明确，假设已经实现
}

int Node(BINode *t) {
    // 实现不明确，假设已经实现
}

Bool CheckFull(BINode *t) {
    int h = Height(t);   // 获取树的高度
    int n = Node(t);     // 获取树的节点数
    // 判断是否满足满二叉树的条件：节点数 = 2^高度 - 1
    if (n == pow(2, h) - 1) return 1;
    return 0;
}
```

### ！！！判断一棵二叉树是否是最大堆

> 加入flag if判断反条件 flag置为0 

```c
int flag = 1;   

Bool CheckTree(BinaryTree *bt) {
    Check(bt->root);
    if (flag == 1) return 1;
    else return 0;
}

Bool Check(BINode *t) {
    if (!t) return 0;
    if ((t->element < t->lChild->element) || (t->element < t->rChild->element)) {
        flag = 0;
    }
    Check(t->lChild);
    Check(t->rChild);
}
/*
完全二叉树：所有层（除了最后一层）必须是满的，且最后一层的节点必须尽量左对齐。
堆序性：每个节点的值都必须大于或等于其子节点的值。
*/
```

### 折半搜索

### 判断是否是最小堆

```c
// 判断二叉树是否为最小堆的函数
Bool CheckTree(BinaryTree *bt) {
    Check(bt->root);
    return flag;
}

// 递归函数：检查二叉树节点是否满足最小堆性质
void Check(BTNode *t) {
    if (!t) return;
    // 检查左子节点
    if (t->lChild && t->element > t->lChild->element) {
        flag = 0;
    }
    // 检查右子节点
    if (t->rChild && t->element > t->rChild->element) {
        flag = 0;
    }
    Check(t->lChild);
    Check(t->rChild);
}
```

### 判断是否为二叉扩充树

```c
// 判断二叉树是否为扩充二叉树
bool CheckTree(BinaryTree *bt) {
    Check(bt->root);
    if (flag == 1) return true;
    else return false;
}

// 递归检查每个节点是否符合扩充二叉树的条件
void Check(BINode *t) {
    if (!t) return;
    
    // 如果一个节点有一个子节点而没有另一个子节点，设置标志为0
    if ((t->lChild == NULL && t->rChild != NULL) || (t->lChild != NULL && t->rChild == NULL)) {
        flag = 0;
    }
    
    Check(t->lChild);
    Check(t->rChild);
}
/*
完全二叉树：除了最后一层，所有层都必须是满的，而且最后一层的节点必须尽量左对齐。
扩充二叉树：每个节点都必须有两个子节点（无论是内部节点还是叶节点），叶节点的子节点都为NULL。
*/
```

### 判断是否是线性表是否是有序表

```c
int flag = 1;

// 判断线性表是否为升序有序表
Bool Check(SeqList *L) {
    for (int i = 0; i < L.n - 1; i++) {
        if (L.element[i]> L.element[i + 1]) {
            flag = 0;
        }
    }
  if(flag == 1) return 1;
  else return 0;
}
```

### 判断是否是二叉搜索树

```c
int flag = 1;

// 判断一棵二叉树是否为扩充二叉树
Bool CheckTree(BinaryTree *bt) {
    Check(bt->root);
    if (flag == 1) return 1;
    else return 0;
}

Bool Check(BINode *t) {
    if (!t) return 0; 
    if ((t->lChild->element > t->element) || (!t->rChild->element < t->element)) { // 一个子节点的情况
        flag = 0;
    }
    Check(t->lChild);
    Check(t->rChild);
}

/*
左子树的所有节点值都小于当前节点的值。
右子树的所有节点值都大于当前节点的值。
左右子树也必须是二叉搜索树。
*/
```

### 判断一棵二叉搜索树是AVL

```c
int flag = 1; // 标志位，初始值为1，用于记录树是否平衡

// 检查二叉树是否是AVL树
Bool CheckTree(BinaryTree *bt) {
    Check(bt->root); // 检查根节点
    if (flag == 1) return 1; // 如果flag仍为1，说明树是平衡的
    else return 0; // 否则，树是不平衡的
}

// 计算节点的高度
int Height(BINode *t) {
    if (!t) return 0; // 如果节点为空，高度为0
    return max(Height(t->lChild), Height(t->rChild)) + 1; // 返回左右子树中较大的高度+1
}

// 递归检查节点及其子树是否平衡
Bool Check(BINode *t) {
    if (!t) return 0; // 如果节点为空，返回0
    // 如果左右子树高度差的绝对值大于1，设置flag为0，表示树不平衡
    if (abs(Height(t->lChild) - Height(t->rChild)) > 1) {
        flag = 0;
    }
    Check(t->lChild); // 递归检查左子树
    Check(t->rChild); // 递归检查右子树
}
/*
同时满足
二叉树的每个节点的左子树和右子树都是二叉搜索树。
二叉树的每个节点的左子树和右子树的高度差不超过1。
*/
```

### 判断是否是AVL搜索树

```c
int flag = 1; // 标志位，初始值为1，用于记录树是否平衡

// 检查二叉树是否是AVL树
Bool CheckTree(BinaryTree *bt) {
    Check(bt->root); // 检查根节点
    if (flag == 1) return 1; // 如果flag仍为1，说明树是平衡的
    else return 0; // 否则，树是不平衡的
}

// 计算节点的高度
int Height(BINode *t) {
    if (!t) return 0; // 如果节点为空，高度为0
    return max(Height(t->lChild), Height(t->rChild)) + 1; // 返回左右子树中较大的高度+1
}

// 递归检查节点及其子树是否平衡
Bool Check(BINode *t) {
    if (!t) return 0; // 如果节点为空，返回0
    // 如果左右子树高度差的绝对值大于1，设置flag为0，表示树不平衡
  	if ((t->lChild->element > t->element) || (!t->rChild->element < t->element))  // 一个子节点的情况
        flag = 0;
    if (abs(Height(t->lChild) - Height(t->rChild)) > 1) {
        flag = 0;
    Check(t->lChild); // 递归检查左子树
    Check(t->rChild); // 递归检查右子树
}
```

### 邻接矩阵表示的图中检查两点之间是否有直接的边

```c
// 不带权有向图边搜索
Bool Search(MGraph *mg, int u, int v) {
    // 检查 u 和 v 是否在合法范围内，并且 u 不能等于 v
    if (u < 0 || v < 0 || u >= mg->n || v >= mg->n || u == v)
        return 0; // 如果不在合法范围内，返回 0，表示无效的边

    // 检查邻接矩阵中是否存在边 u->v
    if (mg->a[u][v] == 1)
        return 1; // 如果存在边，返回 1

    return 0; // 如果不存在边，返回 0
}
```

### 计算一个节点的入度

```c
// 计算节点的入度
int InDegree(MGraph *mg, int v) {
    // 检查节点 v 是否在合法范围内
    if (v < 0 || v >= mg->n) 
        return 0; // 如果不在合法范围内，返回 0

    int cnt = 0; // 初始化计数器
    // 遍历所有节点，检查是否有边指向节点 v
    for (int i = 0; i < mg->n; i++) {
        if (mg->a[i][v] == 1) 
            cnt++; // 如果存在边 i -> v，计数器加 1
    }
    return cnt; // 返回入度计数
}
```

### 在图G中利用邻接表存储，在顶点u和v之间插入一条边

```c
// 在图G中利用邻接表存储，在顶点u和v之间插入一条边
Bool AddEdge(Graph *lg, int u, int v)
{
    // 检查u和v是否在合法范围内，以及是否u和v相同
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return 0;

    ENode *p = lg->a[u];
    // 遍历链表，检查是否已存在边u-v
    while (p != NULL) {
        if (p->adjvex == v) return 0; // 如果边已经存在，返回0
        p = p->nextArc;
    }

    // 如果边不存在，创建新节点
    p = (ENode *)malloc(sizeof(ENode));
    p->adjvex = v; // 设置节点的邻接点
    p->nextArc = lg->a[u]; // 插入新节点到链表的开头
    lg->a[u] = p; // 更新链表头指针
    lg->e++; // 边数加1

    return 1; // 返回1表示边插入成功
}
```

### 计算顶点u的出度

```c
// 在图G中利用邻接表存储，计算顶点u的出度
int OutDegree(Graph *lg, int u)
{
    // 检查顶点u是否在合法范围内
    if (u < 0 || u > lg->n - 1) return -1;

    ENode *p = lg->a[u];
    int cnt = 0;

    // 遍历链表，计算出度
    while (p != NULL) {
        cnt++;
        p = p->nextArc;
    }

    return cnt; // 返回出度
}
```

### 计算顶点u的入度

```c
// 在图G中利用邻接表存储，计算顶点u的入度
int InDegree(Graph *lg, int u)
{
    // 检查顶点u是否在合法范围内
    if (u < 0 || u > lg->n - 1) return -1;

    int cnt = 0;

    // 遍历每个顶点的邻接表，检查是否有指向u的边
    for (int i = 0; i < lg->n; i++) {
        ENode *p = lg->a[i];
        while (p != NULL) {
            if (p->adjvex == u) cnt++;
            p = p->nextArc;
        }
    }

    return cnt; // 返回入度
}
```

### 有向图 G 采用邻接表存储，求各顶点的出度

```c
// 有向图 G 采用邻接表存储，求各顶点的出度
void OutDegree (LGraph *lg , int * b) {
    for (int i = 0; i < lg->n; i++) {  // 遍历每个顶点
        ENode *p = lg->a[i];          // 获取顶点 i 的邻接表头指针
        while (p != NULL) {           // 遍历邻接表
            b[i]++;                   // 顶点 i 的出度加 1
            p = p->nextArc;           // 移动到下一个邻接点
        }
    }
}

```

### 有向图 G 采用邻接表存储，求各顶点的入度

```c
// 有向图 G 采用邻接表存储，求各顶点的入度
void InDegree (LGraph *lg , int * b) {
    for (int i = 0; i < lg->n; i++) {      // 遍历每个顶点
        for (int j = 0; j < lg->n; j++) {  // 遍历所有顶点的邻接表
            ENode *p = lg->a[j];           // 获取顶点 j 的邻接表头指针
            while (p != NULL) {            // 遍历邻接表
                if (p->adjVex == i)        // 如果顶点 j 的邻接点是顶点 i
                    b[i]++;                // 顶点 i 的入度加 1
                p = p->nextArc;            // 移动到下一个邻接点
            }
        }
    }
}
```

### 邻接表 G 转换为 邻接矩阵

````c

for(int i = 0; i < mg.n; i++){
  for(int j = 0;j < mg.n; j++){
    mg.a[i][j] = 0;
  }
}


// 邻接表 G 转换为 邻接矩阵
void LgToMg (LGraph *lg , mGraph *mg) {
    mg->e = lg->e;  // 复制边的数量
    mg->n = lg->n;  // 复制顶点的数量

    for (int i = 0; i < lg->n; i++) {  // 遍历每个顶点
        ENode *p = lg->a[i];           // 获取顶点 i 的邻接表头指针
        while (p != NULL) {            // 遍历邻接表
            mg->m[i][p->adjVex] = 1;   // 设置邻接矩阵对应位置为 1
            p = p->nextArc;            // 移动到下一个邻接点
        }
    }
}
````

### 邻接矩阵 G 转换为 邻接表

```c
// 邻接矩阵 G 转换为 邻接表
void MgToLg (mGraph *mg , LGraph *lg) {
    lg->e = 0;  // 初始化边的数量为 0
    lg->n = mg->n;  // 复制顶点的数量

    for (int i = 0; i < lg->n; i++) {  // 遍历每个顶点
        lg->a[i] = NULL;  // 初始化邻接表头指针为 NULL
        for (int j = 0; j < lg->n; j++) {  // 遍历邻接矩阵的每一列
            if (mg->a[i][j] == 1) {  // 如果存在边 (i, j)
                ENode *q = (ENode *) malloc(sizeof(ENode));  // 创建一个新的邻接表结点
                q->adjVex = j;  // 邻接点的顶点编号
                q->nextArc = lg->a[i];  // 插入到邻接表的头部
                lg->a[i] = q;  // 更新邻接表头指针
            }
        }
    }
}
```


```C
/**
 * @description: DFS
 * @param {LGraph} *lg  指向图的指针
 * @param {int} v    当前访问的顶点
 * @param {int} *visited   数组:记录哪些顶点已经被访问过
 * @return {*}
 */
void DFS(LGraph *lg, int v, int *visited)
{
    visited[v] = 1;     // 将当前顶点 v 标记为已访问
    Node *p = lg->a[v]; // 指向顶点 v 的邻接表中的第一个节点
    while (p != NULL)   // 循环遍历顶点 v 的所有邻接点
    {
        if (visited[p->adjvex] == 0) // 当前邻接点 p->adjvex 未被访问，递归调用 DFS 访问该邻接点
        {
            DFS(lg, p->adjvex, visited); // p 移动到下一个邻接点
        }
        p = p->nextArc;
    }
}
```

### 检查一个图是否连通

> 先初始化所有顶点为未访问状态，然后从一个顶点开始进行DFS，标记所有连通的顶点。最后检查是否所有顶点都被访问过，从而判断图是否连通。

```c
Bool CheckConnected(LGraph *lg) 
{
    // 创建一个数组visited，用于记录每个顶点是否被访问过
    int visited[lg->n];
    
    // 初始化visited数组，所有元素置为0，表示所有顶点初始时都未被访问
    for (int i = 0; i < lg->n; i++) 
        visited[i] = 0;

    // 从第一个顶点（索引为0）开始进行深度优先搜索，标记所有连通的顶点
    DFS(lg, 0, visited);
    
    // 检查visited数组，如果有顶点未被访问过，则图不连通
    for (int i = 0; i < lg->n; i++) 
    {
        // 如果visited[i]仍为0，说明顶点i未被访问，图不连通
        if (visited[i] == 0)
            return 0; // 返回0表示图不连通
    }

    // 所有顶点都被访问过，图连通
    return 1; // 返回1表示图连通
}
```

### 计算图中连通分量数量

> 在无向图中，连通分量可以通过深度优先搜索（DFS）或广度优先搜索（BFS）来找到。每次从一个未被访问的顶点开始进行一次搜索，所访问到的所有顶点都属于同一个连通分量。当所有的顶点都被访问过之后，搜索的次数就等于图中连通分量的数量。

```c
int Count(LGraph *lg)
{
    // 定义一个数组 visited，大小为图中顶点的数量 lg->n
    int visited[lg->n];

    // 使用 for 循环将所有顶点的访问状态初始化为 0，表示所有顶点都未被访问过
    for (int i = 0; i < lg->n; i++) 
        visited[i] = 0;

    // 定义一个计数器 cnt，用于记录连通分量的数量
    int cnt = 0;

    // 使用 for 循环遍历图中所有的顶点
    for (int i = 0; i < lg->n; i++)
    {
        // 如果当前顶点 i 未被访问，则进入 if 语句块
        if (visited[i] == 0)
        {
            // 调用 DFS 函数对当前顶点 i 进行深度优先搜索，同时更新 visited 数组
            DFS(lg, i, visited);

            // 每当一个新的未被访问的顶点开始一次深度优先搜索时，表示发现了一个新的连通分量，因此计数器 cnt 加 1
            cnt++;
        }
    }

    // 返回连通分量的数量 cnt
    return cnt;
}
```

### 判断顶点i到顶点j是否有路径（只要给出顶点序号 都需要越界判断）

```c
Bool IsConnected(LGraph *lg, int i, int j)
{
    // 检查顶点i和顶点j是否在有效范围内，或者i和j是否相同
    if (i < 0 || j < 0 || i >= lg->n || j >= lg->n || i == j) 
        return 0;

    // 初始化一个访问数组，记录每个顶点是否被访问过
    int visited[lg->n];
    for (int k = 0; k < lg->n; k++)
        visited[k] = 0;

    // 从顶点i开始进行深度优先搜索  结束后数组保存可以访问到的所有节点的标记
    DFS(lg, i, visited);     

    // 检查顶点j是否被访问过
    if (visited[j] == 1)
        return 1;
    else 
        return 0;
}

```



