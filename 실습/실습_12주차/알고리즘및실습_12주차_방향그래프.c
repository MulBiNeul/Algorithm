#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MAX_VERTEX 100
#define MAX_EDGE 1000

// LinkedList 구조체 정의
typedef struct LinkedList
{
    int element;
    struct LinkedList *next;
} LinkedList;

// GraphType 구조체 정의
typedef struct GraphType
{
    int n;
    int m;
    char vertices[MAX_VERTEX];
    int inDegree[MAX_VERTEX];
    LinkedList *outEdges[MAX_VERTEX];
    LinkedList *inEdges[MAX_VERTEX];
} GraphType;

// QueueType 구조체 정의
typedef struct QueueType
{
    int queue[MAX_VERTEX];
    int front, rear;
} QueueType;

// 전역 변수 선언
GraphType G;
int topOrder[MAX_VERTEX + 1];

// 함수 원형
void buildGraph();
void insertVertex(char vName, int i);
void insertDirectedEdge(char uName, char wName, int i);
int _index(char vName);
void addFirst(LinkedList **H, int i);
void topologicalSort();
void initQueue(QueueType *q);
int is_empty(QueueType *q);
void enqueue(QueueType *q, int item);
int dequeue(QueueType *q);

int main()
{
    buildGraph();      // 그래프 생성
    topologicalSort(); // 위상 정렬 수행

    // non-DAG, 방향싸이클 존재
    if (topOrder[0] == 0)
    {
        printf("0\n");
    }
    // DAG, 위상 정렬 결과 출력
    else
    {
        for (int i = 1; i <= G.n; i++)
        {
            printf("%c ", G.vertices[topOrder[i]]);
        }
        printf("\n");
    }

    return 0;
}

// builgraph 함수
void buildGraph()
{
    int n, m;
    char vName, wName;

    scanf("%d", &n); // 정점의 개수 n
    G.n = n;
    // 정점 입력
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &vName);   // 정점 이름 입력
        insertVertex(vName, i); // 정점 삽입
    }

    scanf("%d", &m); // 간선의 개수 m
    G.m = m;
    // 간선 입력
    for (int i = 0; i < m; i++)
    {
        scanf(" %c %c", &vName, &wName);     // 간선 입력
        insertDirectedEdge(vName, wName, i); // 간선 삽입
    }
}

// insertVertex 함수
void insertVertex(char vName, int i)
{
    G.vertices[i] = vName; // 정점 이름 저장
    G.outEdges[i] = NULL;  // 출력 간선 리스트 초기화
    G.inEdges[i] = NULL;   // 입력 간선 리스트 초기화
    G.inDegree[i] = 0;     // 진입 차수 초기화
}

// insertDirectedEdge 함수
void insertDirectedEdge(char uName, char wName, int i)
{
    int u = _index(uName);       // 출발 정점 인덱스 계산
    int w = _index(wName);       // 도착 정점 인덱스 계산
    addFirst(&G.outEdges[u], w); // 출력 간선 리스트에 도착 정점 추가
    addFirst(&G.inEdges[w], u);  // 입력 간선 리스트에 출발 정점 추가
    G.inDegree[w]++;             // 도착 정점의 진입 차수 증가
}

// _index 함수
int _index(char vName)
{
    for (int i = 0; i < G.n; i++)
    { // 정점 이름과 일치하는 정점 idx 반환
        if (G.vertices[i] == vName)
        {
            return i;
        }
    }
    return -1;
}

// addFirst 함수
void addFirst(LinkedList **H, int i)
{
    // node 동적 할당 및 메모리 할당 여부 검사
    LinkedList *node = (LinkedList *)malloc(sizeof(LinkedList));
    if (node == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    // node 초기화
    node->element = i;
    node->next = *H;
    *H = node;
}

// topologicalSort 함수
void topologicalSort()
{
    QueueType q;
    initQueue(&q); // 큐 초기화

    int in[MAX_VERTEX];
    for (int i = 0; i < G.n; i++)
    {
        in[i] = G.inDegree[i]; // 진입 차수 복사
        // 진입 차수가 0인 정점을 큐에 추가
        if (in[i] == 0)
        {
            enqueue(&q, i);
        }
    }

    int t = 1; // 위상 순위
    while (!is_empty(&q))
    {
        int u = dequeue(&q); // 큐에서 정점 추출
        topOrder[t++] = u;   // 위상 순위에 추가

        LinkedList *p = G.outEdges[u]; // 출력 간선 리스트 순회
        while (p != NULL)
        {
            int w = p->element; // 종점
            in[w]--;            // 진입 차수 감소
            // 정점 w의 진입 차수가 0인 경우
            if (in[w] == 0)
            {
                enqueue(&q, w); // 큐에 추가
            }
            p = p->next; // 다음 노드로 이동
        }
    }

    // non-DAG, 방향 싸이클 존재
    if (t <= G.n)
    {
        topOrder[0] = 0;
    }
    // DAG, 위상 정렬 결과 저장
    else
    {
        topOrder[0] = 1;
    }
}

// initQueue 함수
void initQueue(QueueType *q)
{
    q->front = q->rear = 0; // 큐 초기화
}

// is_empty 함수
int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

// enqueue 함수
void enqueue(QueueType *q, int item)
{
    // is_full
    if ((q->rear + 1) % MAX_VERTEX == q->front)
    {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_VERTEX; // 큐 포인터 이동
    q->queue[q->rear] = item;             // 큐에 원소 추가
}

// dequeue 함수
int dequeue(QueueType *q)
{
    // is_empty
    if (is_empty(q))
    {
        printf("Queue is empty!\n");
        return -1;
    }
    q->front = (q->front + 1) % MAX_VERTEX; // 큐 포인터 이동
    return q->queue[q->front];              // 큐에서 원소 반환
}

/*

3
A B C
3
A B
C A
C B

4
A B C D
6
A B
C A
C B
A D
B D
D C

8
A B C D E F G H
11
A B
C B
A D
C D
B D
D E
E F
E H
E G
F G
H G

*/