#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 함수 원형
int findElement(int[], int, int);

int main()
{
    int n, k;

    // n, k 입력
    scanf("%d %d", &n, &k);

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

    // 조건을 만족하는 값이 있는 경우 그 위치 출력
    if (result < n)
    {
        printf("%d\n", result);
    }
    // 조건을 만족하는 값이 없는 경우 n 출력
    else
    {
        printf("%d\n", n);
    }

    free(A); // 메모리 해제

    return 0;
}

// findElement 함수
int findElement(int A[], int n, int k)
{
    // l, r 초기화
    int l = 0;
    int r = n - 1;

    int result = n; // 조건을 만족하는 값이 없는 경우 n이 되도록 설정

    // l, r이 교차할 때까지 반복
    while (l <= r)
    {
        int mid = (l + r) / 2; // 중간 값 계산

        // 중간 값이 k보다 크거나 같은 경우
        if (A[mid] >= k)
        {
            result = mid; // k보다 크거나 같은 첫 번째 값의 위치 갱신
            r = mid - 1;  // 왼쪽 절반 탐색
        }
        // 중간 값이 k보다 작은 경우
        else
        {
            l = mid + 1; // 오른쪽 절반 탐색
        }
    }

    return result; // 결과 반환
}