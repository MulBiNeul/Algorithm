#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 연결리스트 구조
typedef struct Node
{
    char elem;
    struct Node *prev;
    struct Node *next;
} Node;

// 이중연결리스트 구조
typedef struct DoubleLinkedList
{
    Node *header;
    Node *trailer;
    int size;
} DoubleLinkedList;

// 함수 원형
Node *makenode(char);
DoubleLinkedList *__init__(DoubleLinkedList *);
void add(DoubleLinkedList *, int, char);
void delete(DoubleLinkedList *, int);
char get(DoubleLinkedList *, int);
void print(DoubleLinkedList *);
void NODE_FREE(DoubleLinkedList *);

int main()
{
    int number_of_operation, rank;
    char command, elem;
    DoubleLinkedList *DLL = __init__(NULL);

    // 연산의 개수 입력 후 공백 받기
    scanf("%d", &number_of_operation);
    getchar();

    // 연산의 개수만큼 반복
    for (int i = 0; i < number_of_operation; i++)
    {
        scanf(" %c", &command); // 명령 입력
        // add
        if (command == 'A')
        {
            scanf(" %d %c", &rank, &elem);
            add(DLL, rank, elem);
        }
        // delete
        else if (command == 'D')
        {
            scanf(" %d", &rank);
            delete (DLL, rank);
        }
        // get
        else if (command == 'G')
        {
            scanf(" %d", &rank);
            char tmp = get(DLL, rank);
            if (tmp != 0)
            {
                printf("%c\n", tmp);
            }
        }
        // print
        else if (command == 'P')
        {
            print(DLL);
        }
    }

    // 메모리 해제
    NODE_FREE(DLL);
    free(DLL);
    return 0;
}

// 노드 생성 함수
Node *makenode(char elem)
{
    // newnode 동적 할당 및 메모리 할당 여부 검사
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory Allocation Failed");
    }

    // newnode 초기화
    newnode->elem = elem;
    newnode->prev = NULL;
    newnode->next = NULL;

    return newnode;
}

// 이중연결리스트 초기화
DoubleLinkedList *__init__(DoubleLinkedList *DLL)
{
    // 이중연결리스트 동적 할당 및 메모리 할당 여부 검사
    DoubleLinkedList *newList = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
    Node *header = (Node *)malloc(sizeof(Node));
    Node *trailer = (Node *)malloc(sizeof(Node));

    if (newList == NULL)
    {
        printf("Memory Allocation Failed");
    }
    if (header == NULL)
    {
        printf("Memory Allocation Failed");
    }
    if (trailer == NULL)
    {
        printf("Memory Allocation Failed");
    }

    // 이중연결리스트 header 초기화
    newList->header = header;
    header->prev = NULL;
    header->next = trailer;
    // 이중연결리스트 trailer 초기화
    newList->trailer = trailer;
    trailer->prev = header;
    trailer->next = NULL;
    // 이중연결리스트 size 초기화
    newList->size = 0;

    return newList;
}

// add 함수
void add(DoubleLinkedList *newList, int rank, char elem)
{
    // 순위가 유효하지 않을 경우
    if (rank < 1 || rank > newList->size + 1)
    { // 경고문 출력 후 함수 종료
        printf("invalid position\n");
        return;
    }

    Node *newnode = makenode(elem); // 추가할 노드 생성
    Node *curr = newList->header;   // 현재 위치를 나타내는 노드
    // 원하는 순위까지 이동
    for (int i = 1; i < rank; i++)
    {
        curr = curr->next;
    }
    // newnode와 기존 연결리스트 연결
    newnode->prev = curr;
    newnode->next = curr->next;
    curr->next->prev = newnode;
    curr->next = newnode;

    newList->size++; // 이중연결리스트 size update
}

// delete 함수
void delete(DoubleLinkedList *newList, int rank)
{
    // 순위가 유효하지 않을 경우
    if (rank < 1 || rank > newList->size)
    { // 경고문 출력 후 함수 종료
        printf("invalid position\n");
        return;
    }

    Node *curr = newList->header; // 현재 위치를 나타내는 노드
    // 원하는 순위까지 이동
    for (int i = 1; i <= rank; i++)
    {
        curr = curr->next;
    }
    // 해당 순위의 앞과 뒤를 연결
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;

    free(curr);      // 삭제할 노드 메모리 해제
    newList->size--; // 이중연결리스트 size update
}

// get 함수
char get(DoubleLinkedList *newList, int rank)
{
    // 순위가 유효하지 않을 경우
    if (rank < 1 || rank > newList->size)
    { // 경고문 출력 후 함수 종료
        printf("invalid position\n");
        return 0;
    }

    Node *curr = newList->header; // 현재 위치를 나타내는 노드
    // 원하는 순위까지 이동
    for (int i = 1; i <= rank; i++)
    {
        curr = curr->next;
    }

    return curr->elem; // 원하는 순위 노드의 정보 반환
}

// print 함수
void print(DoubleLinkedList *newList)
{
    Node *curr = newList->header; // 현재 위치를 나타내는 노드
    // 이중연결리스트를 순회하며 각 노드의 정보 출력
    for (int i = 1; i <= newList->size; i++)
    {
        curr = curr->next;
        printf("%c", curr->elem);
    }
    printf("\n");
}

// 메모리 해제 함수
void NODE_FREE(DoubleLinkedList *newList)
{
    Node *curr = newList->header; // 현재 위치를 나타내는 노드
    Node *next;

    // 각 노드를 순회하며 동적 메모리 해제
    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}