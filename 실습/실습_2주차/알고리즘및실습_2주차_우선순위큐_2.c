#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 함수 원형
void insertionSort(int *, int);
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

    insertionSort(arr, arr_size); // 삽입 정렬
    printArray(arr, arr_size);    // 정렬된 배열 출력

    free(arr);

    return 0;
}

// 삽입 정렬 함수
void insertionSort(int *arr, int arr_size)
{
    int key;
    for (int i = 1; i < arr_size; i++)
    {
        key = arr[i]; // 기준점 설정
        int j = i - 1;
        // 기준점 이전에 기준점 원소보다 큰 원소가 있을 경우 정렬 실행
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
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