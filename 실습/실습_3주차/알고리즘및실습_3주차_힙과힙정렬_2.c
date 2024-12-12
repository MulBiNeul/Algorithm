#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 전역 변수 선언
int Heap[99];
int n;

// 함수 원형
// void rBuildHeap(int);
void buildHeap();
void downHeap(int);
void printHeap();

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &Heap[i]);
    }
    buildHeap();
    printHeap();

    return 0;
}

// void rBuildHeap(int i)
// {
//     if (i > n)
//     {
//         return;
//     }
//     rBuildHeap(2 * i);
//     rBuildHeap(2 * i + 1);
// }

void buildHeap()
{
    for (int i = n / 2; i >= 1; i--)
    {
        downHeap(i);
    }
}

void downHeap(int i)
{
    int left_child = 2 * i;
    int right_child = 2 * i + 1;
    int target;

    if (left_child > n)
    {
        return;
    }

    if (Heap[left_child] > Heap[right_child])
    {
        target = left_child;
    }
    else
    {
        target = right_child;
    }

    if (Heap[target] > Heap[i])
    {
        int tmp = Heap[target];
        Heap[target] = Heap[i];
        Heap[i] = tmp;
    }

    downHeap(target);
}

void printHeap()
{
    for (int i = 0; i < n; i++)
    {
        printf(" %d", Heap[i + 1]);
    }
}