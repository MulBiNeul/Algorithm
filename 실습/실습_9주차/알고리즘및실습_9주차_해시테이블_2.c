#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define DELETED -1

// 해시 테이블 구조체 정의
typedef struct HashTable
{
    int *table;
    int size;
} HashTable;

// 함수 원형
HashTable *createHashTable(int);
int hashFunction(int, int);
void insert(HashTable *, int);
void search(HashTable *, int);
void freeHashTable(HashTable *);

int main()
{
    int M, n, key;
    char command;

    scanf("%d %d", &M, &n);                    // 해시 테이블의 크기와 최대 입력 횟수 입력
    HashTable *hashTable = createHashTable(M); // 해시 테이블 생성

    while (1)
    {
        /*
        i <x> : 키 x를 해시테이블에 삽입
        s <x> : 키 x가 해시테이블에 존재하는지 탐색
        e : 프로그램 종료
        */
        scanf(" %c", &command); // 명령어 입력
        // 'e' 입력 시 프로그램 종료
        if (command == 'e')
        {
            freeHashTable(hashTable); // 해시 테이블 해제
            break;
        }
        // 'i' 입력 시 키 삽입
        if (command == 'i')
        {
            scanf("%d", &key);
            insert(hashTable, key); // insert 호출
        }
        // 's' 입력 시 키 탐색
        else if (command == 's')
        {
            scanf("%d", &key);
            search(hashTable, key); // search 호출
        }
    }

    return 0;
}

// creeateHashTable 함수
HashTable *createHashTable(int size)
{
    // hashTable 동적 할당 및 메모리 할당 여부 검사
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (hashTable == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    /// hashTable 초기화
    hashTable->size = size;
    hashTable->table = (int *)malloc(size * sizeof(int)); // 테이블 동적 할당
    // table 메모리 할당 여부 검사
    if (hashTable->table == NULL)
    {
        printf("Memory allocation failed.\n");
        free(hashTable);
        exit(1);
    }

    // 각 요소를 EMPTY로 초기화
    for (int i = 0; i < size; i++)
    {
        hashTable->table[i] = EMPTY;
    }

    return hashTable;
}

// hashFunction 함수
int hashFunction(int key, int size)
{
    return key % size; // 해시 함수
}

// insert 함수
void insert(HashTable *hashTable, int key)
{
    int v = hashFunction(key, hashTable->size); // 해시 함수를 통한 idx 연산
    int i = 0;

    // 선형조사법
    while (i < hashTable->size)
    {
        int idx = (v + i) % hashTable->size; // 해시 함수를 통한 idx 연산
        // 빈 공간 발견 시 키 삽입
        if (hashTable->table[idx] == EMPTY || hashTable->table[idx] == DELETED)
        {
            hashTable->table[idx] = key; // 키 삽입
            // 충돌 횟수만큼 C 출력
            for (int j = 0; j < i; j++)
            {
                printf("C");
            }
            printf("%d\n", idx); // idx 출력
            return;
        }
        // 이미 키가 존재하는 경우
        else if (hashTable->table[idx] == key)
        {
            return;
        }
        i++; // i update
    }
}

// search 함수
void search(HashTable *hashTable, int key)
{
    int v = hashFunction(key, hashTable->size); // 해시 함수를 통한 idx 연산
    int i = 0;

    while (i < hashTable->size)
    {
        int idx = (v + i) % hashTable->size; // 해시 함수를 통한 idx 연산
        // table이 비어 있는 경우
        if (hashTable->table[idx] == EMPTY)
        {
            printf("-1\n"); // -1 출력
            return;
        }
        // table의 값이 key와 같은 경우
        else if (hashTable->table[idx] == key)
        {
            printf("%d %d\n", idx, hashTable->table[idx]); // idx, key 출력
            return;
        }
        i++; // i update
    }
}

// freeHashTable 함수
void freeHashTable(HashTable *hashTable)
{
    // 해시 테이블 해제
    free(hashTable->table);
    free(hashTable);
}

/*

7 3
i 17011112
i 17012345
i 17012687
s 17011111
e

13 10
i 16110243
i 17011111
i 17012331
i 17012354
i 17013672
i 16012342
i 15013986
i 102067
i 113478
i 14012322
s 16110243
e
\

*/
