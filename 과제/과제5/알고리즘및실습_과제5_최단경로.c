#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 상수 정의
#define MIN_VERTEX 1
#define MAX_VERTEX 100
#define MIN_EDGE 1
#define MAX_EDGE 1000
#define INT_MAX 2147483647

// Graph 구조체
typedef struct Graph
{
    char vertices[MAX_VERTEX][2];
    int adj[MAX_VERTEX][MAX_VERTEX];
    int vertex_count;
} Graph;

// Node 구조체
typedef struct Node
{
    int vertex;
    int distance;
} Node;

/// PriorityQueue 구조체
typedef struct PriorityQueue
{
    Node heap[MAX_VERTEX];
    int size;
} PriorityQueue;

// 전역 변수
Graph graph;
int distances[MAX_VERTEX];
int ways[MAX_VERTEX];
int visited[MAX_VERTEX];

// 함수 원형
void init_graph();
void add_vertex(char *);
void add_edge(char *, char *, int);
int find_vertex_index(char *);
void dijkstra(char *, char *);
void init_priority_queue(PriorityQueue *);
void push(PriorityQueue *, int, int);
Node pop(PriorityQueue *);

int main()
{
    int n, m;
    char u[2], v[2];
    int w;
    char source[2], target[2];

    scanf("%d %d", &n, &m); // n: 정점의 개수, m: 간선의 개수
    init_graph();           // 그래프 초기화

    // 간선 정보 입력
    for (int i = 0; i < m; i++)
    {
        scanf("%s %s %d", u, v, &w); // u: 시작 정점, v: 도착 정점, w: 가중치
        add_vertex(u);
        add_vertex(v);
        add_edge(u, v, w);
    }

    printf("\nsource\ttarget\t최단거리\t최단경로 수\n");
    // Dijkstra 알고리즘 시행
    while (scanf("%s %s", source, target) != EOF)
    {
        dijkstra(source, target);
    }

    return 0;
}

// init_graph 함수
void init_graph()
{
    graph.vertex_count = 0; // 정점 개수 초기화
    // 인접 행렬 초기화
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        for (int j = 0; j < MAX_VERTEX; j++)
        {
            graph.adj[i][j] = (i == j) ? 0 : INT_MAX; // 자기 자신으로 가는 경로는 0, 나머지는 무한대로 초기화
        }
    }
}

// add_vertex 함수
void add_vertex(char *vertex)
{
    // 정점이 존재하지 않으면 추가
    if (find_vertex_index(vertex) == -1)
    {
        strcpy(graph.vertices[graph.vertex_count++], vertex);
    }
}

// find_vertex_index 함수
int find_vertex_index(char *vertex)
{
    // 정점 인덱스 반환
    for (int i = 0; i < graph.vertex_count; i++)
    {
        if (strcmp(graph.vertices[i], vertex) == 0)
        {
            return i;
        }
    }
    return -1; // 정점이 존재하지 않으면 -1 반환
}

// add_edge 함수
void add_edge(char *u, char *v, int weight)
{
    int u_idx = find_vertex_index(u); // 시작 정점 인덱스
    int v_idx = find_vertex_index(v); // 도착 정점 인덱스
    // 가중치 설정
    graph.adj[u_idx][v_idx] = weight;
    graph.adj[v_idx][u_idx] = weight;
}

// dijkstra 함수
void dijkstra(char *source, char *target)
{
    int n = graph.vertex_count; // 정점 개수
    PriorityQueue pq;
    init_priority_queue(&pq); // 우선순위 큐 초기화

    for (int i = 0; i < n; i++)
    {
        distances[i] = INT_MAX; // 거리 초기화
        ways[i] = 0;            // 경로 수 초기화
    }

    int source_idx = find_vertex_index(source); // 시작 정점 인덱스
    int target_idx = find_vertex_index(target); // 도착 정점 인덱스
    distances[source_idx] = 0;                  // 시작 정점의 거리는 0
    ways[source_idx] = 1;                       // 시작 노드의 경로 수는 1
    push(&pq, source_idx, 0);                   // 시작 정점 우선순위 큐에 삽입

    while (pq.size > 0)
    {
        Node current = pop(&pq); // 현재 노드 선택
        int u = current.vertex;  // 현재 노드 인덱스

        // 거리가 더 큰 경우
        if (current.distance > distances[u])
        {
            continue;
        }

        for (int v = 0; v < n; v++)
        {
            if (u == v) // 자기 자신으로 가는 경우는 제외
            {
                continue;
            }
            // 인접한 노드 확인
            if (graph.adj[u][v] != INT_MAX)
            {
                int new_dist = distances[u] + graph.adj[u][v]; // 거리 계산
                // 거리가 더 짧은 경우
                if (new_dist < distances[v])
                {
                    distances[v] = new_dist; // 거리 갱신
                    ways[v] = ways[u];       // 경로 수 갱신
                    push(&pq, v, new_dist);  // 우선순위 큐에 삽입
                }
                // 거리가 같은 경우
                else if (new_dist == distances[v])
                {
                    ways[v] += ways[u]; // 경로 수 갱신
                }
            }
        }
    }

    // 거리가 무한대인 경우
    if (distances[target_idx] == INT_MAX)
    {
        printf("%s\t%s\tINT_MAX\t0\n", source, target);
    }
    // 거리가 무한대가 아닌 경우
    else
    {
        printf("%s\t%s\t%d\t%d\n", source, target, distances[target_idx], ways[target_idx]);
    }
}

// init_priority_queue 함수
void init_priority_queue(PriorityQueue *pq)
{
    pq->size = 0; // 큐의 크기 초기화
}

// push 함수
void push(PriorityQueue *pq, int vertex, int distance)
{
    pq->heap[pq->size].vertex = vertex;     // 정점 설정
    pq->heap[pq->size].distance = distance; // 거리 설정
    int i = pq->size++;                     // 큐의 크기 증가

    // 조건에 따라 우선순위 큐 정렬
    while (i > 0 && pq->heap[i].distance < pq->heap[(i - 1) / 2].distance)
    {
        Node temp = pq->heap[i];             // 임시 노드 생성
        pq->heap[i] = pq->heap[(i - 1) / 2]; // 부모 노드와 자식 노드 교환
        pq->heap[(i - 1) / 2] = temp;        // 임시 노드와 부모 노드 교환
        i = (i - 1) / 2;                     // 부모 노드 인덱스로 이동
    }
}

// pop 함수
Node pop(PriorityQueue *pq)
{
    Node min_node = pq->heap[0];        // 최소 노드 설정
    pq->heap[0] = pq->heap[--pq->size]; // 마지막 노드를 루트 노드로 이동
    int i = 0;                          // 루트 노드 인덱스

    while (1)
    {
        // left, right, smallest 설정
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        // 좌측 자식 노드가 존재하고, 좌측 자식 노드가 최소 노드인 경우
        if (left < pq->size && pq->heap[left].distance < pq->heap[smallest].distance)
        {
            smallest = left; // 최소 노드 갱신
        }
        // 우측 자식 노드가 존재하고, 우측 자식 노드가 최소 노드인 경우
        if (right < pq->size && pq->heap[right].distance < pq->heap[smallest].distance)
        {
            smallest = right; // 최소 노드 갱신
        }
        // 최소 노드가 루트 노드인 경우
        if (smallest == i)
        {
            break; // 종료
        }
        // 최소 노드와 루트 노드 교환
        Node temp = pq->heap[i];
        pq->heap[i] = pq->heap[smallest];
        pq->heap[smallest] = temp;
        i = smallest; // 인덱스 갱신
    }

    return min_node;
}

// 예시 입력
/*

6 9
A C 1
A B 8
A D 4
B C 7
B E 4
C D 5
C E 3
C F 9
D F 4
C A
C F
F C
B D

*/

// 예시 출력
/*

source	target	최단거리	최단경로 수
C	A	1	1
C	F	9	3
F	C	9	3
B	D	12	5

*/
