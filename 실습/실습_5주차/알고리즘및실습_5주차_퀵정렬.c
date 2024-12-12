#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

// 함수 원형
int findPivot(int L[], int l, int r);
void inPlacePartition(int L[], int l, int r, int pivot, int *a, int *b);
void inPlaceQuickSort(int L[], int l, int r);

int main()
{
    int n;
    scanf("%d", &n); // 배열의 크기 입력

    // 배열 L 동적 할당 및 메모리 할당 여부 검사
    int *L = (int *)malloc(n * sizeof(int));
    if (L == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    srand(time(NULL)); // 무작위 난수 시드 설정

    // n개의 정수를 입력 받아 배열에 저장
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &L[i]);
    }

    inPlaceQuickSort(L, 0, n - 1); // 퀵 정렬 실행

    // 정렬된 배열 출력
    for (int i = 0; i < n; i++)
    {
        printf("%d ", L[i]);
    }

    free(L); // 동적 메모리 해제
    return 0;
}

// findPivot 함수
int findPivot(int L[], int l, int r)
{
    int randidx = l + rand() % (r - l + 1); // l과 r 사이에서 random index 선택
    return L[randidx];                      // random index 값 반환
}

// inPlacePartition 함수
void inPlacePartition(int L[], int l, int r, int pivot, int *a, int *b)
{
    int i = l; // 왼쪽 포인터
    int j = r; // 오른쪽 포인터

    // i과 j가 교차하지 않을 때까지 반복
    while (i <= j)
    {
        // 피벗보다 작은 값을 찾을 때까지 오른쪽으로 이동
        while (L[i] < pivot)
        {
            i++;
        }
        // 피벗보다 큰 값을 찾을 때까지 왼쪽으로 이동
        while (L[j] > pivot)
        {
            j--;
        }

        // i와 j가 교차하지 않은 경우
        if (i <= j)
        {
            // 값 교환
            int temp = L[i];
            L[i] = L[j];
            L[j] = temp;
            // 포인터 이동
            i++;
            j--;
        }
    }

    // a와 b의 값을 update
    *a = j + 1;
    *b = i - 1;
}

// inPlaceQuickSort 함수
void inPlaceQuickSort(int L[], int l, int r)
{ // 왼쪽 원소가 오른쪽 원소보다 크거나 같을 경우
    if (l >= r)
    {
        return; // 종료
    }

    int pivot = findPivot(L, l, r); // 피벗 선택
    int a, b;
    inPlacePartition(L, l, r, pivot, &a, &b); // 분할 수행
    inPlaceQuickSort(L, l, a - 1);            // 피벗보다 작은 부분 정렬
    inPlaceQuickSort(L, b + 1, r);            // 피벗보다 큰 부분 정렬
}