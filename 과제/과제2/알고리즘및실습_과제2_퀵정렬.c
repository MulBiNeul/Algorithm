#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT_SIZE 4
#define MODE_SIZE 4

// 전역 변수 선언
int n = 100000;
int Limit[] = {1, 100, 500, 1000};
char *modes[] = {"deterministic1", "deterministic3", "randomized1", "randomized3"};
char *currentMode;
int currentLimit;
int A[100000];

// 함수 원형
void createArray();
void quickSort(int[], int);
void rQuickSort(int[], int, int);
int findIndexOfMedianOfThree(int[], int, int, int);
int findPivot(int[], int, int);
void inPlacePartition(int[], int, int, int, int *, int *);
double printCPUTime(clock_t, clock_t);
void insertionSort(int[], int);

int main()
{
    srand(time(NULL)); // 난수 생성 시드 설정

    double results[LIMIT_SIZE][MODE_SIZE];
    clock_t start, end;
    int *pA;
    createArray(); // 배열 A 생성

    for (int i = 0; i < LIMIT_SIZE; i++)
    {
        for (int j = 0; j < MODE_SIZE; j++)
        {
            pA = A;                                   // 배열 A의 주소 저장
            currentLimit = Limit[i];                  // 현재 제한 크기 설정
            currentMode = modes[j];                   // 현재 모드 설정
            start = clock();                          // 시간 측정 시작
            quickSort(pA, n);                         // quickSort 호출
            end = clock();                            // 시간 측정 종료
            results[i][j] = printCPUTime(start, end); // 시간 측정 결과 저장
        }
    }

    // 결과 출력
    printf("Limit    결정적1     결정적3     무작위1     무작위3\n");
    for (int i = 0; i < LIMIT_SIZE; i++)
    {
        printf("%-7d", Limit[i]); // 현재 제한 크기
        for (int j = 0; j < MODE_SIZE; j++)
        {
            printf("  %.8lf", results[i][j]); // 시간 측정 결과 출력
        }
        printf("\n");
    }

    return 0;
}

// createArray 함수
void createArray()
{
    // 무작위 정수로 배열 A 생성
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % n + 1;
    }
}

// quickSort 함수
void quickSort(int A[], int n)
{
    rQuickSort(A, 0, n - 1); // rQuickSort 호출
    insertionSort(A, n);     // quickSort 종료 후 insetionSort 시행
}

// rQuickSort 함수
void rQuickSort(int A[], int l, int r)
{ // rQucikSort 시행 조건
    if (r - l > currentLimit)
    {
        int pivotIndex = findPivot(A, l, r); // pivot 선택
        int pivotValue = A[pivotIndex];      // pivot 값 저장
        int a, b;

        inPlacePartition(A, l, r, pivotValue, &a, &b); // inlacePartition 시행
        rQuickSort(A, l, a - 1);                       // 왼쪽 부분 재귀 호출
        rQuickSort(A, b + 1, r);                       // 오른쪽 부분 재귀 호출
    }
}

// findIndexOfMedianOfThree 함수
int findIndexOfMedianOfThree(int A[], int a, int b, int c)
{
    // 세 개의 원소 중 중간값 선택
    if ((A[a] <= A[b] && A[b] <= A[c]) || (A[c] <= A[b] && A[b] <= A[a]))
    {
        return b;
    }
    if ((A[b] <= A[a] && A[a] <= A[c]) || (A[c] <= A[a] && A[a] <= A[b]))
    {
        return a;
    }
    return c;
}

// findPivot 함수
int findPivot(int A[], int l, int r)
{
    // deterministic1 모드
    if (strcmp(currentMode, "deterministic1") == 0)
    {
        return r; // 마지막 원소 선택
    }

    // randomized1 모드
    if (strcmp(currentMode, "randomized1") == 0)
    {
        return l + rand() % (r - l + 1); // l과 r 사이에서 무작위 선택
    }

    // 원소가 두 개인 경우
    if (r - l == 1)
    {
        return l; // 두 개만 있으면 l 선택
    }

    int a, b, c;
    // deterministic3 또는 randomized3 모드
    switch (strcmp(currentMode, "deterministic3") == 0 ? 1 : (strcmp(currentMode, "randomized3") == 0 ? 2 : 0))
    {
    case 1: // deterministic3
        // l, (l + r)/2, r에서 중간값 선택
        a = l;
        b = (l + r) / 2;
        c = r;
        break;

    case 2: // randomized3
        // l과 r 사이에서 세 개의 무작위 위치 선택
        a = l + rand() % (r - l + 1);
        b = l + rand() % (r - l + 1);
        c = l + rand() % (r - l + 1);
        break;
    }

    return findIndexOfMedianOfThree(A, a, b, c); // a, b, c에서 중간값 선택하여 반환
}

// inPlacePartition 함수
void inPlacePartition(int A[], int l, int r, int pivot, int *a, int *b)
{
    int i = l;
    int j = r;

    // i와 j가 교차할 때까지 반복
    while (i <= j)
    {
        // A[i]가 pivot보다 작은 경우 i 증가
        while (A[i] < pivot)
        {
            i++;
        }
        // A[j]가 pivot보다 큰 경우 j 감소
        while (A[j] > pivot)
        {
            j--;
        }

        if (i <= j) // i와 j가 교차하지 않은 경우
        {
            // swap
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            // i, j update
            i++;
            j--;
        }
    }
    // a, b update
    *a = j + 1;
    *b = i - 1;
}

// 삽입 정렬 함수
void insertionSort(int A[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = A[i]; // key update
        int j = i - 1;
        // key가 들어갈 위치 찾기
        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j]; // 원소 이동
            j--;             // j update
        }
        A[j + 1] = key; // key 삽입
    }
}

// printCPUTime 함수
double printCPUTime(clock_t start, clock_t end)
{
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    return cpu_time_used; // cpu_time_used 계산 후 반환
}
