#include <stdio.h>
#include <stdlib.h>

// 상수 정의
#define MIN_VERTEX 1
#define MAX_VERTEX 100
#define MIN_EDGE 1
#define MAX_EDGE 1000

// Edge 구조체 정의
typedef struct Edge
{
    int u, v, weight;
} Edge;

// 전역 변수 선언
Edge edges[MAX_EDGE];
int parent[MAX_VERTEX + 1];
int rank[MAX_VERTEX + 1];

// 함수 원형
void Kruskal(int, int);
int find(int);
void union_sets(int, int);
void quicksort(Edge[], int, int);
int partition(Edge[], int, int);

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

    // 간선 정보 입력
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight); // u: 시작 정점, v: 도착 정점, weight: 가중치
    }

    Kruskal(n, m); // Kruskal 알고리즘 실행

    return 0;
}

void Kruskal(int n, int m)
{
    int total_weight = 0;
    int edge_count = 0;

    // 퀵 정렬을 사용하여 간선을 가중치 순으로 정렬
    quicksort(edges, 0, m - 1);

    // parent, rank 배열 초기화
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    // 간선을 가중치 순으로 처리
    for (int i = 0; i < m && edge_count < n - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        // 사이클을 형성하지 않는 경우에만 MST에 추가
        if (find(u) != find(v))
        {
            printf(" %d", weight); // MST 간선 무게 출력
            total_weight += weight;
            union_sets(u, v); // 두 집합을 union
            edge_count++;
        }
    }

    printf("\n%d\n", total_weight); //  MST 총 무게 출력
}

// find 함수
int find(int v)
{
    // 루트 노드를 찾을 때까지 재귀 ghcnf
    if (v != parent[v])
    {
        parent[v] = find(parent[v]);
    }

    return parent[v];
}

// union_sets 함수
void union_sets(int u, int v)
{
    int root_u = find(u); // u의 루트 노드 찾기
    int root_v = find(v); // v의 루트 노드 찾기

    // union algorithm
    if (root_u != root_v)
    {
        // root_u의 rank가 root_v보다 크면
        if (rank[root_u] > rank[root_v])
        {
            parent[root_v] = root_u; // root_v를 root_u의 자식으로 설정
        }
        // root_u의 rank가 root_v보다 작으면
        else if (rank[root_u] < rank[root_v])
        {
            parent[root_u] = root_v; // root_u를 root_v의 자식으로 설정
        }
        /// root_u의 rank가 root_v와 같으면
        else
        {
            parent[root_v] = root_u; // root_v를 root_u의 자식으로 설정
            rank[root_u]++;          // root_u의 rank update
        }
    }
}

// quicksort 함수
void quicksort(Edge arr[], int low, int high)
{
    // low가 high보다 작을 때만 실행
    if (low < high)
    {
        int pi = partition(arr, low, high); // partition 시행

        quicksort(arr, low, pi - 1);  // 왼쪽 부분 배열 정렬
        quicksort(arr, pi + 1, high); // 오른쪽 부분 배열 정렬
    }
}

// partition 함수
int partition(Edge arr[], int low, int high)
{
    int pivot = arr[high].weight; // pivot 설정
    int i = (low - 1);            // i 초기화

    for (int j = low; j <= high - 1; j++)
    {
        // 현재 가중치가 pivot보다 작으면
        if (arr[j].weight < pivot)
        {
            i++; // i 증가
            // swap
            Edge temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // swap
    Edge temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1); // pivot의 위치 반환
}

/*

6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37

5 7
1 2 75
1 4 95
1 3 51
2 4 9
4 3 19
4 5 42
3 5 31

*/
