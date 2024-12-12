#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MAX_SIZE 100

// 노드 구조체 정의
typedef struct Node
{
    int key;
    struct Node *next;
} Node;

// 해시 테이블 구조체 정의
typedef struct HashTable
{
    Node *table[MAX_SIZE];
    int size;
} HashTable;

// 함수 원형
HashTable *createHashTable(int);
Node *createNode(int);
int hashFunction(int, int);
void insert(HashTable *, int);
int search(HashTable *, int);
void delete(HashTable *, int);
void printHashTable(HashTable *);
void freeHashTable(HashTable *);

int main()
{
    int M, key;
    char command;
    scanf("%d", &M); // 해시 테이블의 크기 입력

    HashTable *hashTable = createHashTable(M); // 해시 테이블 생성

    while (1)
    {
        /*
        i <x> : 키 x를 해시테이블에 삽입
        s <x> : 키 x가 해시테이블에 존재하는지 탐색
        d <x> : 키 x가 해시테이블에 존재하면 삭제
        p : 해시테이블에 저장된 키들을 순서대로 인쇄
        e : 프로그램 종료
        */

        scanf(" %c", &command); // 명령어 입력
        // 'e' 입력 시 프로그램 종료
        if (command == 'e')
        {
            freeHashTable(hashTable);
            break;
        }
        // 'i' 입력 시 키 삽입
        if (command == 'i')
        {
            scanf("%d", &key);
            insert(hashTable, key); // 키 삽입
        }
        // 's' 입력 시 키 탐색
        else if (command == 's')
        {
            scanf("%d", &key);
            int result = search(hashTable, key); // 탐색 결과 저장
            printf("%d\n", result);              // 탐색 결과 출력
        }
        // 'd' 입력 시 키 삭제
        else if (command == 'd')
        {
            scanf("%d", &key);
            int result = search(hashTable, key); // 탐색 결과 저장
            delete (hashTable, key);             // 키 삭제
            printf("%d\n", result);              // 탐색 결과 출력
        }
        else if (command == 'p')
        {
            printHashTable(hashTable); // 해시 테이블 출력
        }
    }

    return 0;
}

// createHashTable 함수
HashTable *createHashTable(int size)
{
    // hashTable 동적 할당 및 메모리 할당 여부 검사
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (hashTable == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // hashTable 초기화
    hashTable->size = size;
    for (int i = 0; i < size; i++)
    {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// createNode 함수
Node *createNode(int key)
{
    // newNode동적 할당 및 메모리 할당 여부 검사
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // newNode 초기화
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// hashFunction 함수
int hashFunction(int key, int size)
{
    return key % size; // 해시 함수
}

// insert 함수
void insert(HashTable *hashTable, int key)
{
    int index = hashFunction(key, hashTable->size); // 해시 함수를 통한 idx 연산
    Node *newNode = createNode(key);                // 노드 할당
    // 해시 테이블의 해당 인덱스에 노드 연결
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

// search 함수
int search(HashTable *hashTable, int key)
{
    int index = hashFunction(key, hashTable->size); // 해시 함수를 통한 idx 연산
    Node *current = hashTable->table[index];        // 현재 노드 초기화
    int position = 1;                               // position 초기값 설정

    while (current != NULL)
    { // key 값 탐색에 성공하면 possition 반환
        if (current->key == key)
        {
            return position;
        }
        // current, position update
        current = current->next;
        position++;
    }

    return 0;
}

// delete 함수
void delete(HashTable *hashTable, int key)
{
    int index = hashFunction(key, hashTable->size); // 해시 함수를 통한 idx 연산
    Node *current = hashTable->table[index];        // 현재 노드 초기화
    Node *prev = NULL;                              // 이전 노드 초기화

    while (current != NULL)
    {
        // key 값 탐색에 성공하면 해당 노드 삭제
        if (current->key == key)
        {
            if (prev == NULL)
            {
                hashTable->table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        // current, prev update
        prev = current;
        current = current->next;
    }
}

// printHashTable 함수
void printHashTable(HashTable *hashTable)
{
    for (int i = 0; i < hashTable->size; i++)
    {
        Node *current = hashTable->table[i]; // 현재 노드 초기화
        // 순회하면서 키 출력
        while (current != NULL)
        {
            printf(" %d", current->key);
            current = current->next;
        }
    }
    printf("\n");
}

// freeHashTable 함수
void freeHashTable(HashTable *hashTable)
{
    for (int i = 0; i < hashTable->size; i++)
    {
        Node *current = hashTable->table[i];
        // 순회하면서 노드 해제
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    // 해시 테이블 메모리 해제
    free(hashTable);
}

/*

13
i 34
i 23
i 26
i 21
s 36
s 26
s 34
s 21
p
d 21
s 34
d 8
e

*/
