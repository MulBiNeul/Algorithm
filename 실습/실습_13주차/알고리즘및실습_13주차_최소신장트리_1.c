#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 상수 정의
#define MIN_VERTEX 1
#define MAX_VERTEX 100
#define MIN_EDGE 1
#define MAX_EDGE 1000
#define INT_MAX 2147483647

// Edge 구조체 정의
typedef struct Edge
{
    int u, v, weight;
} Edge;

// 전역 변수 선언
int graph[MAX_VERTEX + 1][MAX_VERTEX + 1];
int selected[MAX_VERTEX + 1];
int key[MAX_VERTEX + 1];
int parent[MAX_VERTEX + 1];

// 함수 원형
void Prim_Jarnik(int n);

int main()
{
    int n, m;
    scanf("%d %d", &n, &m); // n: 정점의 개수, m: 간선의 개수

    // 정점과 간선 개수 유효성 검사
    if (n < MIN_VERTEX || n > MAX_VERTEX || m < MIN_EDGE || m > MAX_EDGE)
    {
        printf("Invalid input!\n");
        return 1;
    }

    // 그래프 초기화
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            graph[i][j] = INT_MAX; // 무한대로 초기화
        }
    }

    int u, v, weight;
    // 간선 정보 입력
    for (int i = 0; i < m; i++)
    {

        scanf("%d %d %d", &u, &v, &weight); // u: 시작 정점, v: 도착 정점, weight: 가중치
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    Prim_Jarnik(n); // Prim-Jarnik 알고리즘 실행

    return 0;
}

void Prim_Jarnik(int n)
{
    int total_weight = 0;

    // selected, key, parent 배열 초기화
    for (int i = 1; i <= n; i++)
    {
        selected[i] = 0;
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[1] = 0;     // 시작 정점의 key 값을 0으로 설정
    parent[1] = -1; // 시작 정점의 부모를 -1로 설정

    for (int count = 0; count < n; count++)
    {
        int min_key = INT_MAX;
        int u = -1;

        for (int i = 1; i <= n; i++)
        {
            // 선택되지 않은 정점 중 가장 작은 key 값을 가진 정점 선택
            if (!selected[i] && key[i] < min_key)
            {
                min_key = key[i];
                u = i;
            }
        }

        selected[u] = 1;
        printf(" %d", u); // MST 생성 시 추가되는 정점 출력

        for (int v = 1; v <= n; v++)
        {
            // 선택되지 않은 정점 중 선택된 정점과 연결된 간선의 가중치가 더 작은 경우 업데이트
            if (graph[u][v] != INT_MAX && !selected[v] && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    printf("\n");

    for (int i = 2; i <= n; i++)
    {
        // 최소 신장 트리의 가중치 계산
        if (parent[i] != -1)
        {
            total_weight += graph[parent[i]][i];
        }
    }

    printf("%d\n", total_weight); // MST 총 무게 출력
}

/*

5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6

*/
