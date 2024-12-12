#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MAX_VERTEX 100
#define MAX_EDGE 1000
#define TRUE 1
#define FALSE 0

typedef struct QueueType
{
    int queue[MAX_VERTEX];
    int front, rear;
} QueueType;

int adj_matrix[MAX_VERTEX + 1][MAX_VERTEX + 1];
int visited[MAX_VERTEX + 1];

// 함수 원형
void initMatrix(int n);
void insertEdge(int u, int v);
void bfs_matrix(int start, int n);
int is_empty(QueueType *q);
int is_full(QueueType *q);
void initQueue(QueueType *q);
void enqueue(QueueType *q, int item);
int dequeue(QueueType *q);

int main()
{
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s); // 정점의 개수 n, 간선의 개수 m, 시작 정점 s

    if (n < 1 || n > MAX_VERTEX || m < 1 || m > MAX_EDGE || s < 1 || s > n)
    {
        printf("Invalid input!\n");
        return 1;
    }

    initMatrix(n);

    int u, v;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        insertEdge(u, v);
    }

    bfs_matrix(s, n);

    return 0;
}

void initMatrix(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            adj_matrix[i][j] = 0;
        }
    }
}

void insertEdge(int u, int v)
{
    adj_matrix[u][v] = 1;
    adj_matrix[v][u] = 1;
}

void bfs_matrix(int start, int n)
{
    QueueType q;
    initQueue(&q);

    for (int i = 1; i <= n; i++)
    {
        visited[i] = FALSE;
    }

    visited[start] = TRUE;
    printf("%d ", start);
    enqueue(&q, start);

    while (!is_empty(&q))
    {
        int v = dequeue(&q);
        for (int i = 1; i <= n; i++)
        {
            if (adj_matrix[v][i] && !visited[i])
            {
                visited[i] = TRUE;
                printf("%d ", i);
                enqueue(&q, i);
            }
        }
    }
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
