#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 전역 변수 선언
int Heap[100];
int n;

// 함수 원형
void insertItem(int);
void upHeap(int);
void downHeap(int);
void inPlaceHeapSort();
void printArray();

int main()
{
    int key_num, key;
    scanf("%d", &key_num); // 키의 개수 입력

    for (int i = 1; i <= key_num; i++)
    {
        scanf("%d", &key); // 키 입력
        insertItem(key);   // 키를 힙에 삽입
    }
    inPlaceHeapSort(); // 힙 정렬 실행
    printArray();      // 힙 출력

    return 0;
}

// 키 삽입 함수
void insertItem(int key)
{
    n = n + 1;     // 키 개수 update
    Heap[n] = key; // 힙에 키 삽입
    upHeap(n);     // 힙 상향 정렬 실행
}

// 힙 상향 정렬 함수
void upHeap(int i)
{
    // 현재 노드가 루트 노드인 경우 종료
    if (i == 1)
    {
        return;
    }

    int parent = i / 2; // 부모 노드 idx 계산
    // 현재 노드가 부모 노드보다 큰 경우
    if (Heap[i] > Heap[parent])
    { // swap
        int tmp = Heap[i];
        Heap[i] = Heap[parent];
        Heap[parent] = tmp;
    }
    upHeap(parent); // 힙 상향 정렬 재귀 호출
}

// 힙 하향 정렬 함수
void downHeap(int i)
{
    // 자식 노드의 idx 계산
    int left_child = 2 * i;
    int right_child = 2 * i + 1;

    // 자식 노드가 없는 경우 종료
    if (left_child > n)
    {
        return;
    }

    int target;
    // 왼쪽 자식 노드가 오른쪽 자식 노드보다 큰 경우
    if (right_child > n || Heap[left_child] > Heap[right_child])
    {
        target = left_child; // target update
    }
    // 오른쪽 자식 노드가 왼쪽 자식 노드보다 큰 경우
    else
    {
        target = right_child; // target update
    }

    // 자식 노드가 부모 노드보다 큰 경우
    if (Heap[target] > Heap[i])
    { // swap
        int tmp = Heap[target];
        Heap[target] = Heap[i];
        Heap[i] = tmp;
        downHeap(target); // 힙 하향 정렬 재귀 호출
    }
}

// 힙 정렬 함수
void inPlaceHeapSort()
{
    int originalSize = n; // 기존의 힙 크기 저장
    // 힙 정렬 실행
    for (int i = n; i > 1; i--)
    {
        int tmp = Heap[1];
        Heap[1] = Heap[i];
        Heap[i] = tmp;
        n--;
        downHeap(1); // 힙 하향 정렬 실행
    }
    n = originalSize; // 힙 크기 복구
}

// 힙 출력 함수
void printArray()
{
    // 순차적으로 힙 출력
    for (int i = 1; i <= n; i++)
    {
        printf(" %d", Heap[i]);
    }
    printf("\n");
}
