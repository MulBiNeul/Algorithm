#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 전역 변수 선언
int Heap[99];
int n;

// 함수 원형
void insertItem(int);
int removeMax();
void upHeap(int);
void downHeap(int);
void printHeap();

int main()
{
    int key;
    char command;

    while (1)
    {

        scanf("%c", &command);
        if (command == 'i')
        {
            scanf("%d", &key);
            insertItem(key);
            printf("0\n");
        }
        else if (command == 'd')
        {
            int delete_key = removeMax();
            printf("%d\n", delete_key);
        }
        else if (command == 'p')
        {
            printHeap();
        }
        else if (command == 'q')
        {
            break;
        }
    }

    return 0;
}

void insertItem(int key)
{
    n = n + 1;
    Heap[n] = key;
    upHeap(n);
}

int removeMax()
{
    int key = Heap[1];
    Heap[1] = Heap[n];
    n--;
    downHeap(1);
    return key;
}

void upHeap(int i)
{
    if (i == 1)
    {
        return;
    }

    int parent = i / 2;
    if (Heap[i] > Heap[parent])
    {
        int tmp = Heap[i];
        Heap[i] = Heap[parent];
        Heap[parent] = tmp;
    }
    upHeap(parent);
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