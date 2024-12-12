#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 원형
void heapify(int[], int, int);
void buildMaxHeap(int[], int);
int findKthSmallest(int[], int, int);
void buildList(int[], int, int, int);
void writeList(int[], int);

int main()
{
    srand(time(NULL)); // 랜덤한 시드 설정

    int L[10];

    buildList(L, 10, 1, 100); // 1과 100 사이의 정수 10개로 이루어진 리스트 생성
    writeList(L, 10);         // 생성된 리스트 출력

    int output[3];
    // finkKthSmallest 함수 3회 호출
    for (int k = 1; k <= 3; k++)
    {
        output[k - 1] = findKthSmallest(L, 10, k); // 각 호출에 대한 결과 저장
    }
    printf("k=1: %d k=2: %d k=3: %d\n", output[0], output[1], output[2]); // 결과 출력

    int L_large[100000];
    buildList(L_large, 100000, 1, 1000000); // 1과 1000000 사이의 정수 100000개로 이루어진 리스트 생성

    int karray[] = {1, 100, 99900, 99999}; // k 값 배열
    // 각 k 값에 대해 실행 시간 측정 및 결과 출력
    for (int i = 0; i < 4; i++)
    {
        clock_t start = clock();                                            // 시간 측정 시작
        int result = findKthSmallest(L_large, 100000, karray[i]);           // k 값에 대한 결과 계산
        clock_t end = clock();                                              // 시간 측정 종료
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;    // 실행 시간 계산
        printf("k번째 원소: %d / CPU time: %.6f\n", result, cpu_time_used); // 실행 시간 출력
    }

    return 0;
}

// heapify 함수
void heapify(int heap[], int n, int i)
{
    // 노드 idx 초기화
    int parent_node = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    // 왼쪽 자식이 배열 범위 내이고 왼쪽 자식이 부모보다 클 경우
    if (left_child < n && heap[left_child] > heap[parent_node])
        parent_node = left_child; // 최대값 갱신

    // 오른쪽 자식이 배열 범위 내이고 오른쪽 자식이 부모보다 클 경우
    if (right_child < n && heap[right_child] > heap[parent_node])
        parent_node = right_child; // 최대값 갱신

    // 최대값이 부모가 아닐 경우
    if (parent_node != i)
    { // 부모 노드와 최대값 노드 교환
        int temp = heap[i];
        heap[i] = heap[parent_node];
        heap[parent_node] = temp;

        heapify(heap, n, parent_node); // heapify 재귀 호출
    }
}

// buildMaxHeap 함수
void buildMaxHeap(int heap[], int n)
{ // 반복문을 사용하여 힙 생성
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(heap, n, i);
    }
}

// findKthSmallest 함수
int findKthSmallest(int L[], int n, int k)
{
    int temp[100000];
    // L의 원소를 temp로 복사
    for (int i = 0; i < n; i++)
    {
        temp[i] = L[i];
    }

    buildMaxHeap(temp, k); // k개의 원소로 최대 힙 생성

    // k번째로 작은 원소 찾기
    for (int i = k; i < n; i++)
    {
        if (temp[i] < temp[0]) // 새로운 원소가 힙의 루트보다 작은 경우
        {
            temp[0] = temp[i];   // 루트를 새로운 원소로 교체
            heapify(temp, k, 0); // 최대 힙 유지
        }
    }

    return temp[0]; // k번째로 작은 값 반환
}

// buildList 함수
void buildList(int L[], int n, int min, int max)
{
    // 범위에 맞는 n개의 랜덤 정수 생성
    for (int i = 0; i < n; i++)
    {
        L[i] = rand() % (max - min + 1) + min;
    }
}

// writeList 함수
void writeList(int L[], int n)
{
    // 리스트 출력
    printf(("생성된 리스트: "));
    for (int i = 0; i < n; i++)
    {
        printf("%d ", L[i]);
    }
    printf("\n");
}
