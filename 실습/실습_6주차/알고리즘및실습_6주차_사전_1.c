#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 함수 원형
int rFE(int[], int, int, int);
int findElement(int[], int, int);

int main()
{
    int n, k;

    // n, k 입력
    scanf("%d", &n);
    scanf("%d", &k);

    // 배열 A 동적 할당 및 메모리 할당 여부 검사
    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    // 배열 A 입력
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    int result = findElement(A, n, k); // 결과 저장

    // k와 정확히 일치하는 값이 있는 경우
    if (A[result] == k)
    {
        printf("%d\n", result);
    }
    // 조건을 만족하는 값이 없는 경우
    else if (result == -1)
    {
        printf("-1\n");
    }
    // k보다 작은 가장 큰 값을 찾은 경우
    else
    {
        printf("%d\n", result);
    }

    free(A); // 메모리 해제

    return 0;
}

// findElement 함수
int findElement(int A[], int n, int k)
{
    return rFE(A, k, 0, n - 1); // rFE 함수 호출
}

// 재귀 이진 탐색 함수
int rFE(int A[], int k, int l, int r)
{
    // 만족하는 값이 없는 경우
    if (l > r)
    {
        // 탐색 종료 후에도 찾지 못한 경우
        if (r < 0)
        {
            return -1; // -1 반환
        }
        return r; // r 반환
    }

    int mid = (l + r) / 2; // 중간 인덱스 계산

    // 중간 값이 k와 같은 경우
    if (A[mid] == k)
    {
        return mid; // mid 반환
    }
    // 중간 값이 k보다 큰 경우
    else if (A[mid] > k)
    {
        return rFE(A, k, l, mid - 1); // 왼쪽 절반 탐색
    }
    // 중간 값이 k보다 작은 경우
    else
    {
        return rFE(A, k, mid + 1, r); // 오른쪽 절반 탐색
    }
}
