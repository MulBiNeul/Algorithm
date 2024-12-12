#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define DELETED -1
#define MAX_SIZE 23

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
    int q, key;
    char command;

    HashTable *hashTable = createHashTable(MAX_SIZE, 7); // 해시 테이블 생성, q는 적절히 정의

    while (1)
    {
        /*
        f <x> : 키 x가 해시테이블에 존재하는지 탐색
        i <x> : 키 x를 입력받아 해시테이블에 삽입
        r <x> : 키 x가 해시테이블에 존재하면 삭제
        p : 현재의 해시테이블 인쇄
        q : 해시테이블 인쇄 후 프로그램 종료
        */
        scanf(" %c", &command); // 명령어 입력
        if (command == 'q')
        {
            freeHashTable(hashTable); // 해시 테이블 해제
            break;
        }
        // 'f' 입력 시 탐색
        if (command == 'f')
        {
            scanf("%d", &key);
            search(hashTable, key); // search 호출
        }
        // 'i' 입력 시 키 삽입
        else if (command == 'i')
        {
            scanf("%d", &key);
            insert(hashTable, key); // insert 호출
        }
        // 'r' 입력 시 키 제거
        else if (command == 'r')
        {
            scanf("%d", &key);
            delete (hashTable, key); // delete 호출
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
    hashTable->table = (int *)malloc(size * sizeof(int)); // table 동적 할당
    // table 메모리 할당 여부 검사
    if (hashTable->table == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // table 값 초기화
    for (int i = 0; i < size; i++)
    {
        hashTable->table[i] = EMPTY;
    }
    return hashTable;
}

// hashFunction1 함수
int hashFunction1(int key, int size)
{
    return key % size; // hasFunction1의 값
}

// hashFunction2 함수
int hashFunction2(int key, int q)
{
    return q - (key % q); // hasFunction2의 값
}

// insert 함수
void insert(HashTable *hashTable, int key)
{
    int idx = hashFunction1(key, hashTable->size); // 해시 함수1을 통한 idx 연산
    int step = hashFunction2(key, hashTable->q);   // 해시 함수2를 통한 step 연산
    int count = 0;

    // insert 조건
    while (hashTable->table[idx] != EMPTY && hashTable->table[idx] != DELETED && hashTable->table[idx] != key)
    {
        idx = (idx + step) % hashTable->size; // idx update
        count++;                              // count update
        // table 최대 크기 초과 여부 확인
        if (count >= hashTable->size)
        {
            printf("TABLE IS FULL!\n"); // 경고문 출력
            return;
        }
    }
    // 중복 키 확인
    if (hashTable->table[idx] == key)
    {
        printf("DUPLICATE KEY!\n");
        return;
    }

    hashTable->table[idx] = key;                             // key 삽입
    printf("idx %d에 %d이(가) 삽입되었습니다.\n", idx, key); // 삽입된 idx 출력
}

// delete 함수
void delete(HashTable *hashTable, int key)
{
    int idx = hashFunction1(key, hashTable->size); // 해시 함수1을 통한 idx 연산
    int step = hashFunction2(key, hashTable->q);   // 해시 함수2를 통한 step 연산
    int count = 0;

    // delete 조건
    while (hashTable->table[idx] != EMPTY)
    {
        // table 값과 key 값이 일치하는 경우
        if (hashTable->table[idx] == key)
        {
            hashTable->table[idx] = DELETED;                            // 삭제 marking
            printf("idx %d의 값 %d이(가) 삭제되었습니다.\n", idx, key); // 삭제된 idx와 key출력
            return;
        }
        idx = (idx + step) % hashTable->size; // idx update
        count++;                              // count update
    }
    printf("No Such Key!\n"); // 경고문 출력
}

// search 함수
void search(HashTable *hashTable, int key)
{
    int idx = hashFunction1(key, hashTable->size); // 해시 함수1을 통한 idx 연산
    int step = hashFunction2(key, hashTable->q);   // 해시 함수2를 통한 step 연산
    int count = 0;

    /// search 조건
    while (hashTable->table[idx] != EMPTY)
    {
        // table 값과 key 값이 일치하는 경우
        if (hashTable->table[idx] == key)
        {
            printf("idx %d의 값은 %d입니다.\n", idx, key); // 일치하는 idx와 key 값 출력
            return;
        }
        idx = (idx + step) % hashTable->size; // idx update
        count++;                              // count update
    }

    printf("No Such Key!\n"); // 경고문 출력
}

// printHashTable 함수
void printHashTable(HashTable *hashTable)
{
    // table의 idx 출력
    for (int i = 0; i < hashTable->size; i++)
    {
        printf("%2d ", i);
    }
    printf("\n");

    // table idx에 해당하는 key 출력
    for (int i = 0; i < hashTable->size; i++)
    {
        // 해당 idx의 table이 비어 있는 경우 .으로 표시
        if (hashTable->table[i] == EMPTY)
        {
            printf(" . ");
        }
        // 해당 idx의 table이 삭제된 경우 .으로 표시
        else if (hashTable->table[i] == DELETED)
        {
            printf(" . ");
        }
        // 해당 idx에 key가 존재하는 경우 해당 key 출력
        else
        {
            printf(" %2d", hashTable->table[i]);
        }
    }
    printf("\n");
}

// freeHashTable 함수
void freeHashTable(HashTable *hashTable)
{
    // hashTable 메모리 해제
    free(hashTable->table);
    free(hashTable);
}
