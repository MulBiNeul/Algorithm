#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// Node 구조체
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 함수 원형
Node *addNode(Node *, int);
void printList(Node *);
Node *mergeSort(Node *);
Node *merge(Node *, Node *);
Node *partition(Node *, int);
int getLength(Node *);

int main()
{
    int n, data;
    Node *L = NULL;

    scanf("%d", &n); // 원소의 개수 입력

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data);   // 원소 입력
        L = addNode(L, data); // 리스트에 원소 추가
    }

    L = mergeSort(L); // 합병 정렬 시행
    printList(L);     // 정렬된 리스트 출력

    return 0;
}

// addNode 함수
Node *addNode(Node *head, int data)
{
    // newNode 동적 할당 및 메모리 할당 여부 검사
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // newNode 초기화
    newNode->data = data;
    newNode->next = NULL;

    // 리스트가 비어 있는 경우
    if (!head)
    {
        return newNode; // newNode 반환
    }

    Node *curr = head; // 순회 노드 curr 생성
    // 리스트의 마지막 노드까지 이동
    while (curr->next)
    {
        curr = curr->next;
    }
    curr->next = newNode; // newNode 연결
    return head;          // head 반환
}

// printList 함수
void printList(Node *head)
{
    // head를 순회하며 데이터 출력
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// merge 함수
Node *merge(Node *L1, Node *L2)
{
    // L1이 NULL이면 L2 반환
    if (!L1)
    {
        return L2;
    }
    // L2가 NULL이면 L1 반환
    if (!L2)
    {
        return L1;
    }

    // L1의 data가 L2의 data보다 작은 경우
    if (L1->data < L2->data)
    {
        L1->next = merge(L1->next, L2); // L1의 다음 노드에 L2 연결
        return L1;                      // L1 반환
    }
    // L2의 data가 L1의 data보다 작은 경우
    else
    {
        L2->next = merge(L1, L2->next); // L2의 다음 노드에 L1 연결
        return L2;                      // L2 반환
    }
}

// partition 함수
Node *partition(Node *L1, int k)
{
    // 크기가 0이면 NULL 반환
    if (k == 0)
    {
        return NULL;
    }

    Node *curr = L1; // 순회 노드 curr 생성
    // k-1인 노드까지 이동
    for (int i = 1; i < k && curr->next; i++)
    {
        curr = curr->next;
    }

    Node *L2 = curr->next; // L1의 다음 노드부터 L2
    curr->next = NULL;     // L1의 다음 노드를 NULL로 설정

    return L2; // 분할된 L2 반환
}

// mergeSort 함수
Node *mergeSort(Node *L)
{
    if (!L || !L->next)
    {
        return L;
    }

    Node *middle = partition(L, getLength(L) / 2); // 리스트 분할
    Node *left = mergeSort(L);                     // 왼쪽 부분 합병 정렬
    Node *right = mergeSort(middle);               // 오른쪽 부분 합병 정렬

    return merge(left, right); // left와 right를 합병하여 반환
}

// 리스트 길이 계산 함수
int getLength(Node *head)
{
    int length = 0;
    // 리스트를 순회하며 길이 계산
    while (head)
    {
        length++;
        head = head->next;
    }
    return length; // 길이 반환
}