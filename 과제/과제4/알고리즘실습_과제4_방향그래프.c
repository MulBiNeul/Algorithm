#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

// 상수 정의
#define MAX 30
#define INFINITY 2147483647

// 전역 변수 선언
int A[MAX];
int H[MAX];

// 함수 원형
void initializeArrays();
int airtelDC(int);
int airtelDP(int);
void printCPUTime(clock_t, clock_t, int, int, int, char *, int);

int main()
{
    initializeArrays(); // 배열 초기화

    printf("n\ts\td\tmincost\tversion\tcputime\n"); // 헤더 출력

    int n = 6;
    int testCases[3][2] = {{0, 4}, {2, 5}, {2, 4}}; // 테스트 배열 생성
    // 테스트 실행
    for (int i = 0; i < 3; i++)
    {
        int s = testCases[i][0];
        int d = testCases[i][1];

        /*               airtelDC(분할통치 버전)             */
        clock_t start = clock();                          // 시간 측정 시작
        int mincost = airtelDC(n);                        // DC 호출
        clock_t end = clock();                            // 시간 측정 종료
        printCPUTime(start, end, n, s, d, "DC", mincost); // 측정된 시간 출력

        /*             airtelDP(동적프로그래밍 버전)           */
        start = clock();                                  // 시간 측정 시작
        mincost = airtelDP(n);                            // DP 호출
        end = clock();                                    // 시간 측정 종료
        printCPUTime(start, end, n, s, d, "DP", mincost); // 측정된 시간 출력
    }

    n = MAX; // 최대 크기로 설정
    int s = 1, d = n - 2;

    /*              airtelDC(분할통치 버전)              */
    clock_t start = clock();                          // // 시간 측정 시작
    int mincost = airtelDC(n);                        // DC 호출
    clock_t end = clock();                            //    시간 측정 종료
    printCPUTime(start, end, n, s, d, "DC", mincost); // 측정된 시간 출력

    /*             airtelDP(동적프로그래밍 버전)           */
    start = clock();                                  // 시간 측정 시작
    mincost = airtelDP(n);                            // DP 호출
    end = clock();                                    // 시간 측정 종료
    printCPUTime(start, end, n, s, d, "DP", mincost); // 측정된 시간 출력

    return 0;
}

// initializeArrays 함수
void initializeArrays()
{
    // A 배열 초기화
    A[0] = 0;
    A[1] = 1;

    for (int i = 2; i < MAX; i++)
    {
        A[i] = A[i - 1] + A[i - 1] % 5 + 3;
    }

    // H 배열 초기화
    H[0] = 0;
    H[1] = 5;
    for (int i = 2; i < MAX; i++)
    {
        H[i] = (H[i - 1] + i) % 9 + 1;
    }
}

// rAirtelDC 함수
int rAirtelDC(int d)
{
    // d가 0이면 0 반환
    if (d == 0)
    {
        return 0;
    }

    int minCost = INFINITY; // 최소 비용 초기화
    // d가 0이 아니면 최소 비용 계산
    for (int k = 0; k < d; k++)
    {
        int cost = rAirtelDC(k) + H[k] + A[d - k]; // 재귀 호출 및 비용 계산
        // 최소 비용 업데이트
        if (cost < minCost)
        {
            minCost = cost;
        }
    }
    return minCost;
}

// airtelDC 함수
int airtelDC(int n)
{
    return rAirtelDC(n - 1); // rAirtelDC 호출
}

// airtelDP 함수
int airtelDP(int n)
{
    // 배열 m 초기화
    int m[MAX];
    m[0] = 0;

    // 동적 프로그래밍 알고리즘 수행
    for (int d = 1; d < n; d++)
    {
        m[d] = INFINITY; // 최소 비용 초기화
        // 최소 비용 계산
        for (int k = 0; k < d; k++)
        {
            int cost = m[k] + H[k] + A[d - k]; // 비용 계산
            // 최소 비용 업데이트
            if (cost < m[d])
            {
                m[d] = cost;
            }
        }
    }
    return m[n - 1];
}

// printCPUTime 함수
void printCPUTime(clock_t start, clock_t end, int n, int s, int d, char *version, int mincost)
{
    double cpu_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;         // 실행 시간 계산
    printf("%d\t%d\t%d\t%d\t%s\t%.6f\n", n, s, d, mincost, version, cpu_time); // 결과 출력
}
