#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MAX_NODES 6 // 정점의 최대 개수

// 간선 구조체
typedef struct Edge
{
    int dest;
    int weight;
    struct Edge *next;
} Edge;

// 노드 구조체
typedef struct Node
{
    Edge *head;
} Node;

Node graph[MAX_NODES];

// 함수 원형
void initializeGraph();
void printAdjacentNodes(int);
void addEdge(int, int, int);
void removeEdge(int, int);
void modifyEdge(int, int, int);
void sortEdges(Edge *[], int);
int edgeExists(int, int);

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
        graph[i].head = NULL;
    }

    // 간선 추가
    addEdge(1, 2, 1);
    addEdge(2, 1, 1);
    addEdge(1, 3, 1);
    addEdge(3, 1, 1);
    addEdge(1, 4, 1);
    addEdge(4, 1, 1);
    addEdge(1, 6, 2);
    addEdge(6, 1, 2);
    addEdge(2, 3, 1);
    addEdge(3, 2, 1);
    addEdge(3, 5, 4);
    addEdge(5, 3, 4);
    addEdge(5, 6, 3);
    addEdge(6, 5, 3);
    addEdge(5, 5, 4);
}

// printAdjacentNodes 함수
void printAdjacentNodes(int node)
{
    // 유효하지 않은 노드 번호인 경우
    if (node < 1 || node > MAX_NODES)
    {
        printf("-1\n");
        return;
    }

    Edge *edges[20];
    int count = 0;
    Edge *current = graph[node - 1].head;

    // 인접 리스트의 모든 간선을 배열에 저장
    while (current != NULL)
    {
        edges[count++] = current;
        current = current->next;
    }

    sortEdges(edges, count); // sortEdges 시행

    // count가 0인 경우
    if (count == 0)
    {
        printf("-1\n"); // -1 출력
    }
    // count가 0이 아닌 경우
    else
    {
        // 간선 정보 출력
        for (int i = 0; i < count; i++)
        {
            printf(" %d %d", edges[i]->dest, edges[i]->weight);
        }
        printf("\n");
    }
}

// sortEdges 함수
void sortEdges(Edge *edges[], int count)
{
    // 삽입 정렬 알고리즘
    for (int i = 1; i < count; i++)
    {
        Edge *key = edges[i];
        int j = i - 1;

        while (j >= 0 && edges[j]->dest > key->dest)
        {
            edges[j + 1] = edges[j];
            j--;
        }
        edges[j + 1] = key;
    }
}

// edgeExists 함수
int edgeExists(int src, int dest)
{
    Edge *current = graph[src - 1].head;
    // 인접 리스트 순회
    while (current != NULL)
    {
        // 간선이 존재하는 경우
        if (current->dest == dest)
        {
            return 1; // 1 반환
        }
        current = current->next;
    }
    return 0; // 0 반환
}

// addEdge 함수
void addEdge(int src, int dest, int weight)
{
    // 중복 간선이 추가되지 않도록 확인
    if (!edgeExists(src, dest))
    {
        // newEdge 동적 할당 및 메모리 할당 여부 검사
        Edge *newEdge = (Edge *)malloc(sizeof(Edge));
        if (newEdge == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        // newEdge 초기화
        newEdge->dest = dest;
        newEdge->weight = weight;
        newEdge->next = graph[src - 1].head;
        graph[src - 1].head = newEdge; // graph[src - 1].head 업데이트
    }
}

// 간선 삭제 함수
void removeEdge(int src, int dest)
{
    Edge *current = graph[src - 1].head;
    Edge *prev = NULL;

    // 인접 리스트 순회
    while (current != NULL)
    {
        // 간선이 존재하는 경우
        if (current->dest == dest)
        {
            // head 노드인 경우
            if (prev == NULL)
            {
                graph[src - 1].head = current->next;
            }
            // head 노드가 아닌 경우
            else
            {
                prev->next = current->next;
            }
            free(current); // 메모리 해제
            return;
        }
        // 찾지 못한 경우
        prev = current;
        current = current->next;
    }
}

// modifyEdge 함수
void modifyEdge(int a, int b, int weight)
{
    // 유효하지 않은 노드 번호인 경우
    if (a < 1 || a > MAX_NODES || b < 1 || b > MAX_NODES)
    {
        printf("-1\n");
        return;
    }

    // 가중치가 0인 경우
    if (weight == 0)
    {
        removeEdge(a, b); // 간선 (a, b) 삭제
        if (a != b)
        {
            removeEdge(b, a); // 무방향 그래프이므로 반대 방향도 삭제
        }
    }
    // 가중치가 0이 아닌 경우
    else
    {
        removeEdge(a, b); // 간선 (a, b) 삭제
        if (a != b)
        {
            removeEdge(b, a); // 무방향 그래프이므로 반대 방향도 삭제
        }
        addEdge(a, b, weight); // 간선 (a, b) 추가
        if (a != b)
        {
            addEdge(b, a, weight); // 무방향 그래프이므로 반대 방향도 추가
        }
    }
}