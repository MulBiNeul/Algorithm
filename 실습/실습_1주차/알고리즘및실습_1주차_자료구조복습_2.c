#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 이진트리 구조체
typedef struct BinaryTree
{
    int id;
    struct BinaryTree *leftchild;
    struct BinaryTree *rightchild;
} BinaryTree;

// 함수 원형
BinaryTree *makeroot(BinaryTree *, int);
void leftnode(BinaryTree *, int);
void rightnode(BinaryTree *, int);
void makeBinaryTree(BinaryTree *, int, int);
BinaryTree *search(BinaryTree *, int);
void freeTree(BinaryTree *);

int main()
{
    int number_of_node, number_of_search;
    int root_id, left_id, right_id;
    char command[100];

    BinaryTree *root = NULL;
    BinaryTree *ptr = NULL;

    scanf("%d", &number_of_node); // 노드 개수 입력
    // 노드 개수만큼 입력
    for (int i = 0; i < number_of_node; i++)
    {
        scanf("%d %d %d", &root_id, &left_id, &right_id); // 각 노드의 정보 입력

        // root 생성
        if (i == 0)
        {
            root = makeroot(root, root_id);
            makeBinaryTree(root, left_id, right_id);
        }
        // 노드 id를 찾고 트리를 생성
        else
        {
            ptr = search(root, root_id);
            makeBinaryTree(ptr, left_id, right_id);
        }
    }

    scanf("%d", &number_of_search); // 탐색 횟수 입력
    // 탐색 횟수만큼 반복
    for (int i = 0; i < number_of_search; i++)
    {
        BinaryTree *search_ptr = root; // root부터 시작
        scanf("%s", command);          // 탐색 명령 입력
        printf(" %d", search_ptr->id); // 탐색 결과 출력
        // 명령의 개수만큼 입력
        for (int i = 0; i < strlen(command); i++)
        {
            if (command[i] == 'L') // 좌측 이동 명령
            {
                search_ptr = search_ptr->leftchild; //
                printf(" %d", search_ptr->id);
            }
            else if (command[i] == 'R') // 우측 이동 명령
            {
                search_ptr = search_ptr->rightchild;
                printf(" %d", search_ptr->id);
            }
        }
        printf("\n");
    }

    // 메모리 해제
    freeTree(root);
    return 0;
}

// root 생성 함수
BinaryTree *makeroot(BinaryTree *root, int id)
{
    // rootnode 동적 할당 및 메모리 할당 여부 검사
    BinaryTree *rootnode = (BinaryTree *)malloc(sizeof(BinaryTree));
    if (rootnode == NULL)
    {
        printf("Memory Allocation Failed!");
    }

    // rootnode 초기화
    rootnode->id = id;
    rootnode->leftchild = NULL;
    rootnode->rightchild = NULL;

    return rootnode;
}

// leftnode 생성 함수
void leftnode(BinaryTree *upper, int id)
{
    // childenode 동적 할당 및 메모리 할당 여부 검사
    BinaryTree *childnode = (BinaryTree *)malloc(sizeof(BinaryTree));
    if (childnode == NULL)
    {
        printf("Memory Allocation Failed!");
    }

    // childenode 초기화
    childnode->id = id;
    childnode->leftchild = NULL;
    childnode->rightchild = NULL;

    upper->leftchild = childnode; // 부모 노드의 좌측으로 연결
}

// rightnode 생성 함수
void rightnode(BinaryTree *upper, int id)
{
    // childenode 동적 할당 및 메모리 할당 여부 검사
    BinaryTree *childnode = (BinaryTree *)malloc(sizeof(BinaryTree));
    if (childnode == NULL)
    {
        printf("Memory Allocation Failed!");
    }

    // childenode 초기화
    childnode->id = id;
    childnode->leftchild = NULL;
    childnode->rightchild = NULL;

    upper->rightchild = childnode; // 부모 노드의 우측으로 연결
}

// 이진 트리 생성 함수
void makeBinaryTree(BinaryTree *root, int left_id, int right_id)
{
    // left_id가 0이 아니면 leftnode 생성
    if (left_id != 0)
    {
        leftnode(root, left_id);
    }
    // right_id가 0이 아니면 rightnode todtjd
    if (right_id != 0)
    {
        rightnode(root, right_id);
    }
}

// 탐색 함수 생성
BinaryTree *search(BinaryTree *root, int id)
{
    // 정보가 없는 경우
    if (root == NULL)
    {
        return NULL;
    }
    // root의 id와 일치할 경우 해당 정보 반환
    if (root->id == id)
    {
        return root;
    }
    // 재귀 호출하여 id 탐색 진행
    else
    {
        BinaryTree *leftResult = search(root->leftchild, id);
        BinaryTree *rightResult = search(root->rightchild, id);

        if (leftResult != NULL)
        {
            return leftResult;
        }

        if (rightResult != NULL)
        {
            return rightResult;
        }
        return NULL;
    }
}

// 메모리 해제 함수
void freeTree(BinaryTree *root)
{
    if (root == NULL)
    {
        return;
    }

    // 재귀적으로 좌우 자식 노드의 메모리 해제
    freeTree(root->leftchild);
    freeTree(root->rightchild);

    // 현재 노드의 메모리 해제
    free(root);
}