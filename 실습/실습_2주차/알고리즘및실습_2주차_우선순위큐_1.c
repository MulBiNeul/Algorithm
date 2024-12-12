#include <stdio.h>
#include <stdlib.h>

// 함수 원형
void selectionSort(int *, int);
void printArray(int *, int);

int main()
{
    int arr_size;
    scanf("%d", &arr_size); // 배열의 크기 입력

    int *arr;
    // arr 동적 할당 및 메모리 할당 여부 검사
    arr = (int *)malloc(sizeof(int) * arr_size);
    if (arr == NULL)
    {
        printf("Memory Allocation Failed!");
    }

    // 배열의 원소 입력
    for (int i = 0; i < arr_size; i++)
    {
        scanf("%d", &arr[i]);
    }

    selectionSort(arr, arr_size); // 선택 정렬
    printArray(arr, arr_size);    // 정렬된 배열 출력

    free(arr);

    return 0;
}

// 선택 정렬 함수
void selectionSort(int *arr, int arr_size)
{
    int maxidx, tmp;
    for (int i = arr_size - 1; i > 0; i--)
    {
        maxidx = i; // 최대값 설정
        // i 이전의 최대값 찾기
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[maxidx] < arr[j])
            {
                maxidx = j;
            }
        }
        // 원소 교환
        tmp = arr[maxidx];
        arr[maxidx] = arr[i];
        arr[i] = tmp;
    }
}

// 배열 출력 함수
void printArray(int *arr, int arr_size)
{
    // 배열 원소 출력
    for (int i = 0; i < arr_size; i++)
    {
        printf(" %d", arr[i]);
    }
}