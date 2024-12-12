#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define DELETED -1

// 해시 테이블 구조체 정의
typedef struct HashTable
{
    int *table;
    int size;
    int q;
} HashTable;

// 함수 원형
HashTable *createHashTable(int, int);
int hashFunction1(int, int);
int hashFunction2(int, int);
void insert(HashTable *, int);
void search(HashTable *, int);
void delete(HashTable *, int);
void printHashTable(HashTable *);
void freeHashTable(HashTable *);

int main()
{
    int M, n, q, key;
    char command;

    scanf("%d %d %d", &M, &n, &q);                // M: 해시 테이블의 크기, n: 최대 삽입 개수, q: M보다 조금 작은 소수
    HashTable *hashTable = createHashTable(M, q); // 해시 테이블 생성

    while (1)
    {
        /*
        i <x> : 키 x를 입력받아 해시테이블에 삽입
        s <x> : 키 x가 해시테이블에 존재하는지 탐색
        p : 현재의 해시테이블 인쇄
        e : 해시테이블 인쇄 후 프로그램 종료
        */
        scanf(" %c", &command);
        if (command == 'e')
        {
            printHashTable(hashTable); // 해시 테이블 출력
            freeHashTable(hashTable);  // 해시 테이블 해제
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
        /// 'p' 입력 시 해시 테이블 출력
        else if (command == 'p')
        {
            printHashTable(hashTable); // 해시 테이블 출력
        }
    }

    return 0;
}

// createHashTable 함수
HashTable *createHashTable(int size, int q)
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
    hashTable->q = q;
    hashTable->table = (int *)malloc(size * sizeof(int)); // 테이블 동적 할당
    // 테이블 메모리 할당 여부 검사
    if (hashTable->table == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // 테이블 초기화
    for (int i = 0; i < size; i++)
    {
        hashTable->table[i] = EMPTY;
    }
    return hashTable;
}

// hashFunction1 함수
int hashFunction1(int key, int size)
{
    return key % size; // 해시 함수1
}

// hashFunction2 함수
int hashFunction2(int key, int q)
{
    return q - (key % q); // 해시 함수2
}

// insert 함수
void insert(HashTable *hashTable, int key)
{
    int idx = hashFunction1(key, hashTable->size); // 해시 함수1을 통한 idx 연산
    int step = hashFunction2(key, hashTable->q);   // 해시 함수2를 통한 step 연산
    int count = 0;

    // 이중 해시 처리
    while (hashTable->table[idx] != EMPTY && hashTable->table[idx] != DELETED && hashTable->table[idx] != key)
    {
        idx = (idx + step) % hashTable->size; // idx update
        count++;                              // count update
    }
    // 충돌 발생 횟수만큼 C 출력
    for (int i = 0; i < count; i++)
    {
        printf("C");
    }

    hashTable->table[idx] = key; // 키 값 저장
    printf("%d\n", idx);         // idx 출력
}

// search 함수
void search(HashTable *hashTable, int key)
{
    int idx = hashFunction1(key, hashTable->size); // 해시 함수1을 통한 idx 연산
    int step = hashFunction2(key, hashTable->q);   // 해시 함수2를 통한 step 연산
    int count = 0;

    // table에 key 값이 있는 경우
    while (hashTable->table[idx] != EMPTY)
    {
        // table 값과 key 값이 같은 경우
        if (hashTable->table[idx] == key)
        {
            printf("%d %d\n", idx, key); // idx, key 출력
            return;
        }
        idx = (idx + step) % hashTable->size; // idx update
        count++;                              // count update
    }

    printf("-1\n"); // 키 값이 없는 경우 -1 출력
}

// printHashTable 함수
void printHashTable(HashTable *hashTable)
{
    for (int i = 0; i < hashTable->size; i++)
    {
        // 테이블에 값이 있는 경우
        if (hashTable->table[i] != EMPTY && hashTable->table[i] != DELETED)
        {
            printf(" %d", hashTable->table[i]); // 테이블 값 출력
        }
        // 테이블에 값이 없는 경우
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

// freeHashTable 함수
void freeHashTable(HashTable *hashTable)
{
    // 해시 테이블 해제
    free(hashTable->table);
    free(hashTable);
}