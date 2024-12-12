#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

// 함수 원형
int findK(int, int, char *, int);

int main()
{
    int a, b, info_cnt;
    char query[100]; // Y/N 정보가 들어올 배열

    // 입력 받기
    scanf("%d %d %d", &a, &b, &info_cnt); // a, b, YN 개수 입력
    scanf("%s", query);                   // Y/N 정보 입력

    int k = findK(a, b, query, 0); // findK 호출

    printf("%d\n", k); // 결과 출력

    return 0;
}

// findK 함수
int findK(int a, int b, char *query, int idx)
{
    // 친구는 세종이에게 k > m 인지, Y(예)/N(아니오)으로 알려준다.
    // 여기서 m은 a와 b사이의 중간값으로, m = (a + b)/2이다.
    // 답이 Y인 경우, m + 1 ≤ k ≤ b 이므로 a의 값을 m + 1로 바꾼다.
    // 답이 N인 경우, a ≤ k ≤ m 이므로 b를 m으로 바꾼다.
    // 위 과정을 a와 b가 같을 때까지 반복한다.

    // a와 b가 같은 경우
    if (a == b)
    {
        return a; // a 반환 및 탐색 종료
    }

    int mid = (a + b) / 2; // 중간 값 계산

    // 현재 idx값이 Y인 경우
    if (query[idx] == 'Y')
    {
        return findK(mid + 1, b, query, idx + 1); // 조건에 따른 범위 변경
    }
    // 현재 idx값이 N인 경우
    else
    {
        return findK(a, mid, query, idx + 1); // 조건에 따른 범위 변경
    }
}
