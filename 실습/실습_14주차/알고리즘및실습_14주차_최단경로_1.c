#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MIN_VERTEX 1
#define MAX_VERTEX 100
#define MIN_EDGE 1
#define MAX_EDGE 1000
#define INT_MAX 30000

// Edge 구조체
typedef struct Edge
{
    int u;
    int v;
    int weight;
} Edge;

/// Graph 구조체
typedef struct Graph
{
    int n;
    int adj_mat[MAX_VERTEX][MAX_VERTEX];
} Graph;

// PriorityQueue 구조체
typedef struct PriorityQueue
{
    int heap[MAX_VERTEX];
    int heap_size;
    int key[MAX_VERTEX];
    int position[MAX_VERTEX];
} PriorityQueue;

// 전역변수
Graph graph;
PriorityQueue pq;
int dist[MAX_VERTEX];
int path[MAX_VERTEX];
int visited[MAX_VERTEX];

// 함수 원형
void init_graph(int n);
void init_pq(PriorityQueue *pq);
void insert_edge(int u, int v, int w);
int is_empty(PriorityQueue *pq);
void push(PriorityQueue *pq, int x);
int pop(PriorityQueue *pq);
void replace_key(PriorityQueue *pq, int vertex, int new_key);
void heapify_up(PriorityQueue *pq, int index);
void heapify_down(PriorityQueue *pq, int index);
void DijkstraShortestPaths(int s);

int main()
{
    int n, m;
    int u, v, w;
    int s;

    scanf("%d %d %d", &n, &m, &s); // n: 정점의 개수, m: 간선의 개수, s: 시작 정점
    init_graph(n);                 // 그래프 초기화
    init_pq(&pq);                  // 우선순위 큐 초기화

    // 간선 정보 입력
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        insert_edge(u, v, w); // 간선 정보 삽입
    }
    DijkstraShortestPaths(s); // 다익스트라 알고리즘 수행

    return 0;
}

// init_graph 함수
void init_graph(int n)
{
    // 그래프 초기화
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph.adj_mat[i][j] = 0;
        }
    }
    graph.n = n; // 정점의 개수 설정
}

// init_pq 함수
void init_pq(PriorityQueue *pq)
{
    pq->heap_size = 0; // 힙 크기 초기화
    // 우선순위 큐 초기화
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        pq->key[i] = INT_MAX;
        pq->position[i] = -1;
    }
}

// insert_edge 함수
void insert_edge(int u, int v, int w)
{
    // 간선 정보 삽입
    graph.adj_mat[u - 1][v - 1] = w;
    graph.adj_mat[v - 1][u - 1] = w;
}

// is_empty 함수
int is_empty(PriorityQueue *pq)
{
    return pq->heap_size == 0; // 힙이 비어있으면 1 반환, 아니면 0 반환
}

// push 함수
void push(PriorityQueue *pq, int x)
{
    pq->heap[++pq->heap_size] = x;
    pq->position[x] = pq->heap_size;
    heapify_up(pq, pq->heap_size);
}

// pop 함수
int pop(PriorityQueue *pq)
{
    int item = pq->heap[1];
    pq->heap[1] = pq->heap[pq->heap_size--];
    pq->position[pq->heap[1]] = 1;
    heapify_down(pq, 1);
    pq->position[item] = -1;
    return item;
}

// replace_key 함수
void replace_key(PriorityQueue *pq, int vertex, int new_key)
{
    pq->key[vertex] = new_key; // 키 값 갱신
    // 힙 내에서 키 값 갱신
    heapify_up(pq, pq->position[vertex]);
    heapify_down(pq, pq->position[vertex]);
}

// heapify_up 함수
void heapify_up(PriorityQueue *pq, int index)
{
    // 부모 노드와 비교하여 자신이 더 작으면 교환
    while (index > 1 && pq->key[pq->heap[index]] < pq->key[pq->heap[index / 2]])
    {
        swap(&pq->heap[index], &pq->heap[index / 2]); // swap
        // 힙 내에서 위치 갱신
        pq->position[pq->heap[index]] = index;
        pq->position[pq->heap[index / 2]] = index / 2;
        index /= 2; // idx 갱신
    }
}

// heapify_down 함수
void heapify_down(PriorityQueue *pq, int index)
{
    int smallest = index;
    int left = 2 * index;
    int right = 2 * index + 1;

    // 자식 노드와 비교하여 자신이 더 크면 교환
    if (left <= pq->heap_size && pq->key[pq->heap[left]] < pq->key[pq->heap[smallest]])
    {
        smallest = left; // 왼쪽 자식 노드
    }
    // 자식 노드와 비교하여 자신이 더 크면 교환
    if (right <= pq->heap_size && pq->key[pq->heap[right]] < pq->key[pq->heap[smallest]])
    {
        smallest = right; // 오른쪽 자식 노드
    }
    // 자신이 더 크면 교환
    if (smallest != index)
    {
        swap(&pq->heap[index], &pq->heap[smallest]);
        pq->position[pq->heap[index]] = index;
        pq->position[pq->heap[smallest]] = smallest;
        heapify_down(pq, smallest); // 재귀적으로 힙 재구성
    }
}

// DijkstraShortestPaths 함수
void DijkstraShortestPaths(int s)
{
    // 초기화
    for (int i = 0; i < graph.n; i++)
    {
        dist[i] = INT_MAX;
        path[i] = -1;
        visited[i] = 0;
    }
    dist[s - 1] = 0;   // 시작 정점의 거리 초기화
    push(&pq, s - 1);  // 시작 정점 우선순위 큐에 삽입
    pq.key[s - 1] = 0; // 시작 정점의 키 값 초기화

    // 우선순위 큐에서 정점 하나씩 꺼내기
    while (!is_empty(&pq))
    {
        int u = pop(&pq); // 정점 pop
        // 이미 방문한 정점은 무시
        if (visited[u])
        {
            continue;
        }
        visited[u] = 1; // 방문 표시

        // 인접한 정점들 확인
        for (int v = 0; v < graph.n; v++)
        {
            // 인접한 정점이면서 방문하지 않은 정점이면서 거리가 갱신될 수 있는 경우
            if (graph.adj_mat[u][v] && !visited[v] && dist[v] > dist[u] + graph.adj_mat[u][v])
            {
                dist[v] = dist[u] + graph.adj_mat[u][v]; // 거리 갱신
                path[v] = u;                             // 경로 저장
                if (pq.position[v] == -1)
                {
                    push(&pq, v); // 우선순위 큐에 삽입
                }
                replace_key(&pq, v, dist[v]); // 우선순위 큐에서 키 값 갱신
            }
        }
    }
    // 출발 정점 s에서 다른 모든 정점으로의 최단거리 출력
    for (int i = 0; i < graph.n; i++)
    {
        if (i != s - 1 && dist[i] != INT_MAX)
        {
            printf("%d %d\n", i + 1, dist[i]);
        }
    }
}

// swap 함수
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*

5 7 1
1 2 1
1 4 5
5 1 10
3 5 3
4 3 1
3 1 2
2 3 2

8 12 7
1 2 1
2 4 2
4 7 7
3 6 1
6 1 4
7 6 9
7 8 1
1 3 2
2 7 5
1 4 1
2 5 2
7 5 2

5 3 2
1 2 1
1 3 1
1 4 1

*/
