#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MAX_VERTEX 100
#define MAX_EDGE 1000
#define TRUE 1
#define FALSE 0

typedef struct GraphNode
{
    int vertex;
    struct GraphNode *link;
} GraphNode;

typedef struct GraphType
{
    int n;
    GraphNode *adj_list[MAX_VERTEX + 1];
} GraphType;

typedef struct QueueType
{
    int queue[MAX_VERTEX + 1];
    int front, rear;
} QueueType;

// 함수 원형
void initGraph(GraphType *g, int n);
void insertEdge(GraphType *g, int u, int v);
void bfs_list(GraphType *g, int v);
void dfs(GraphType *, int, int[]);
void print_adj_list(GraphType *g, int);
int is_empty(QueueType *q);
int is_full(QueueType *q);
void initQueue(QueueType *q);
void enqueue(QueueType *q, int item);
int dequeue(QueueType *q);

int main()
{
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    if (n < 1 || n > MAX_VERTEX || m < 1 || m > MAX_EDGE || s < 1 || s > n)
    {
        printf("Invalid input!\n");
        return 1;
    }

    GraphType *g = (GraphType *)malloc(sizeof(GraphType));
    if (g == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }
    initGraph(g, n);

    int u, v;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        insertEdge(g, u, v);
    }

    bfs_list(g, s);
    print_adj_list(g, s);
    free(g);

    return 0;
}

void initGraph(GraphType *g, int n)
{
    g->n = n;
    for (int v = 1; v <= n; v++)
        g->adj_list[v] = NULL;
}

void insertEdge(GraphType *g, int u, int v)
{
    GraphNode *node_1 = (GraphNode *)malloc(sizeof(GraphNode));
    node_1->vertex = v;
    node_1->link = g->adj_list[u];
    g->adj_list[u] = node_1;

    GraphNode *node_2 = (GraphNode *)malloc(sizeof(GraphNode));
    node_2->vertex = u;
    node_2->link = g->adj_list[v];
    g->adj_list[v] = node_2;
}

void bfs_list(GraphType *g, int v)
{
    GraphNode *w;
    QueueType q;
    int visited[MAX_VERTEX + 1] = {FALSE};

    initQueue(&q);
    visited[v] = TRUE;
    enqueue(&q, v);

    while (!is_empty(&q))
    {
        v = dequeue(&q);
        for (w = g->adj_list[v]; w; w = w->link)
        {
            if (!visited[w->vertex])
            {
                visited[w->vertex] = TRUE;
                enqueue(&q, w->vertex);
            }
        }
    }
}

void dfs(GraphType *g, int v, int visited[])
{
    visited[v] = TRUE;
    printf("%d\n", v);

    GraphNode *adjNodes[MAX_VERTEX];
    int count = 0;
    for (GraphNode *w = g->adj_list[v]; w != NULL; w = w->link)
    {
        adjNodes[count++] = w;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (adjNodes[i]->vertex > adjNodes[j]->vertex)
            {
                GraphNode *temp = adjNodes[i];
                adjNodes[i] = adjNodes[j];
                adjNodes[j] = temp;
            }
        }
    }

    // 정점 순서대로 DFS 수행
    for (int i = 0; i < count; i++)
    {
        if (!visited[adjNodes[i]->vertex])
        {
            dfs(g, adjNodes[i]->vertex, visited);
        }
    }
}

void print_adj_list(GraphType *g, int start)
{
    int visited[MAX_VERTEX + 1] = {FALSE};
    dfs(g, start, visited);
}

int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

int is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_VERTEX == q->front);
}

void initQueue(QueueType *q)
{
    q->front = q->rear = 0;
}

void enqueue(QueueType *q, int item)
{
    if (is_full(q))
    {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_VERTEX;
    q->queue[q->rear] = item;
}

int dequeue(QueueType *q)
{
    if (is_empty(q))
    {
        printf("Queue is empty!\n");
        return -1;
    }
    q->front = (q->front + 1) % MAX_VERTEX;
    return q->queue[q->front];
}