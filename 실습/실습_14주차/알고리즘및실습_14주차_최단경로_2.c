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
    int m;
    Edge edges[MAX_EDGE];
} Graph;

// 전역변수
Graph graph;
int dist[MAX_VERTEX];
int path[MAX_VERTEX];

// 함수 원형
void init_graph(int n, int m);
void insert_edge(int index, int u, int v, int w);
void BellmanFordShortestPaths(int s);

int main()
{
    int n, m;
    int u, v, w;
    int s;

    scanf("%d %d %d", &n, &m, &s); // n: 정점의 개수, m: 간선의 개수, s: 시작 정점
    init_graph(n, m);              // 그래프 초기화

    // 간선 정보 입력
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        insert_edge(i, u, v, w); // 간선 정보 삽입
    }
    BellmanFordShortestPaths(s); // 벨만-포드 알고리즘 수행

    return 0;
}

// init_graph 함수
void init_graph(int n, int m)
{
    graph.n = n; // 정점의 개수 설정
    graph.m = m; // 간선의 개수 설정
}

// insert_edge 함수
void insert_edge(int index, int u, int v, int w)
{
    // 간선 정보 삽입
    graph.edges[index].u = u - 1;
    graph.edges[index].v = v - 1;
    graph.edges[index].weight = w;
}

// BellmanFordShortestPaths 함수
void BellmanFordShortestPaths(int s)
{
    // 초기화
    for (int i = 0; i < graph.n; i++)
    {
        dist[i] = INT_MAX;
        path[i] = -1;
    }
    dist[s - 1] = 0; // 시작 정점의 거리 초기화

    // n-1번 반복하며 모든 간선에 대해 거리 갱신
    for (int i = 1; i < graph.n; i++)
    {
        for (int j = 0; j < graph.m; j++)
        {
            int u = graph.edges[j].u;           // 시작 정점
            int v = graph.edges[j].v;           // 도착 정점
            int weight = graph.edges[j].weight; // 가중치

            // 조건: dist[u]가 무한대가 아니고, dist[v]가 dist[u] + weight보다 크면 갱신
            if (dist[u] != INT_MAX && dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight; // 거리 갱신
                path[v] = u;                // 경로 저장
            }
        }
    }

    // 출발 정점 s에서 다른 모든 정점으로의 최단거리 출력
    for (int i = 0; i < graph.n; i++)
    {
        // 출발 정점 s에서 다른 모든 정점으로의 최단거리 출력
        if (i != s - 1 && dist[i] != INT_MAX)
        {
            printf("%d %d\n", i + 1, dist[i]);
        }
    }
}

/*

5 7 1
1 2 1
1 4 5
5 1 -2
3 5 3
3 4 1
1 3 2
3 2 -3

4 5 1
1 2 1
2 3 -2
3 1 2
3 4 1
1 4 5

*/
