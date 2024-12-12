#include <stdio.h>
#pragma warning(disable : 4996)

#define MAX_NODES 6 // 정점의 최대 개수

int graph[MAX_NODES][MAX_NODES]; // 그래프 인접 행렬

// 함수 원형
void initializeGraph();
void printAdjacentNodes(int node);
void addEdge(int src, int dest, int weight);
void removeEdge(int src, int dest);
void modifyEdge(int a, int b, int weight);

int main()
{
    initializeGraph(); // 그래프 초기화

    char command;
    int node, a, b, weight;

    while (1)
    {
        /*
        a <node number>:
        <node number>를 가지는 node와 인접한 node와 그 node까지의 간선 가중치를 모두 인쇄
        단, <node number>의 오름차순으로 인쇄, a가 존재하지 않으면 아무 것도 하지 않고 -1을 출력

        m a b w:
        간선 (a, b)의 가중치 w로 변경.
        그러한 간선이 존재하지 않을 때는 가중치 w인 새로운 간선 (a, b)를 생성.
        w = 0이면 간선 (a, b)를 삭제.
        그래프에 정점 a 혹은 b가 존재하지 않으면 아무 것도 하지 않고 -1을 출력

        q:
        프로그램 종료
        */
        scanf(" %c", &command); // 명령어 입력
        // 'q' 입력 시
        if (command == 'q')
        {
            break; // 프로그램 종료
        }
        // 'a' 입력 시
        else if (command == 'a')
        {
            scanf("%d", &node);
            printAdjacentNodes(node); // 인접한 노드 정보 출력
        }
        // 'm' 입력 시
        else if (command == 'm')
        {
            scanf("%d %d %d", &a, &b, &weight);
            modifyEdge(a, b, weight); // 간선 가중치 변경 또는 추가/삭제
        }
    }

    return 0;
}

// initializeGraph 함수
void initializeGraph()
{
    // 그래프 초기화
    for (int i = 0; i < MAX_NODES; i++)
    {
        for (int j = 0; j < MAX_NODES; j++)
        {
            graph[i][j] = 0;
        }
    }

    // 간선 추가
    addEdge(1, 2, 1);
    addEdge(1, 3, 1);
    addEdge(1, 4, 1);
    addEdge(1, 6, 2);
    addEdge(2, 3, 1);
    addEdge(3, 5, 4);
    addEdge(5, 6, 3);
    addEdge(5, 5, 4);
}

// printAdjacentNodes 함수
void printAdjacentNodes(int node)
{
    // 유효하지 않은 노드 번호인 경우
    if (node < 1 || node > MAX_NODES)
    {
        printf("-1\n"); // -1 출력 후 함수 종료
        return;
    }

    int hasAdjacent = 0;
    // 인접한 노드 정보 출력
    for (int i = 0; i < MAX_NODES; i++)
    {
        if (graph[node - 1][i] != 0)
        {
            printf(" %d %d", i + 1, graph[node - 1][i]);
            hasAdjacent = 1; // 인접한 노드가 있음을 표시
        }
    }
    // 인접한 노드가 없는 경우
    if (!hasAdjacent)
    {
        printf("-1"); // -1 출력
    }
    printf("\n");
}

// addEdge 함수
void addEdge(int src, int dest, int weight)
{
    graph[src - 1][dest - 1] = weight;
    if (src != dest) // 무방향 그래프이므로 반대 방향도 추가
    {
        graph[dest - 1][src - 1] = weight;
    }
}

// removeEdge 함수
void removeEdge(int src, int dest)
{
    graph[src - 1][dest - 1] = 0;
    if (src != dest) // 무방향 그래프이므로 반대 방향도 삭제
    {
        graph[dest - 1][src - 1] = 0;
    }
}

// modifyEdge 함수
void modifyEdge(int a, int b, int weight)
{
    // 유효하지 않은 노드 번호인 경우
    if (a < 1 || a > MAX_NODES || b < 1 || b > MAX_NODES)
    {
        printf("-1\n"); // -1 출력 후 함수 종료
        return;
    }
    // 가중치가 0인 경우
    if (weight == 0)
    {
        removeEdge(a, b); // 간선 (a, b) 삭제
    }
    // 가중치가 0이 아닌 경우
    else
    {
        addEdge(a, b, weight); // 간선 (a, b) 추가
    }
}
