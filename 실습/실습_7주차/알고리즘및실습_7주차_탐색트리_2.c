#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable : 4996)

// node 구조체
typedef struct node
{
    struct node *parent;
    int key;
    int height;
    struct node *lChild;
    struct node *rChild;
} NODE;

NODE *root = NULL; // root 초기화

// 함수 원형
bool isRoot(NODE *);
bool isExternal(NODE *);
bool isInternal(NODE *);
bool isBalanced(NODE *);
NODE *makeNode(NODE *, int);
NODE *treeSearch(NODE *, int);
int findElement(int);
void insertItem(int);
void expandExternal(NODE *);
void searchAndFixAfterInsertion(NODE *);
NODE *restructure(NODE *, NODE *, NODE *);
void updateHeight(NODE *);
void preOrderTraversal(NODE *);

int main()
{
    int k;
    char command;

    /*
    #######################################################################################
    i <키> : 입력 <키>에 대한 노드 생성 및 트리에 삽입
    s <키> : 입력 <키>가 트리에 존재하면 해당 키를 출력, 없으면 ‘X’를 출력
    p : 현재 트리를 전위순회로 인쇄
    q : 프로그램 종료
    #######################################################################################
    */
    while (1)
    {
        scanf(" %c", &command); // 명령어 입력
        // 삽입 명령어 입력
        if (command == 'i')
        {
            scanf("%d", &k); // 삽입할 키 입력
            insertItem(k);   // insertItem 시행
        }
        // 삭제 명령어 입력
        else if (command == 's')
        {
            scanf("%d", &k);          // 탐색할 키 입력
            if (findElement(k) != -1) // 탐색 성공 시
            {
                printf("%d\n", k); // key 출력
            }
            else // 탐색 실패 시
            {
                printf("X\n"); // X 출력
            }
        }
        // 인쇄 명령어 입력
        else if (command == 'p')
        {
            preOrderTraversal(root); // preOrderTraversal 시행
            printf("\n");
        }
        // 종료 명령어 입력
        else if (command == 'q')
        {
            break; // 반복문 종료
        }
    }

    return 0;
}

// isRoot 함수
bool isRoot(NODE *w)
{
    return (w->parent == NULL); // 루트 노드인 경우 true 반환
}

// isExternal 함수
bool isExternal(NODE *w)
{
    return (w->lChild == NULL && w->rChild == NULL); // 외부 노드인 경우 true 반환
}

// isInternal 함수
bool isInternal(NODE *w)
{
    return (w->lChild != NULL || w->rChild != NULL); // 내부 노드인 경우 true 반환
}

bool isBalanced(NODE *w)
{ // 외부 노드인 경우
    if (isExternal(w))
    {
        return true;
    }

    int leftHeight = (w->lChild != NULL) ? w->lChild->height : 0;
    int rightHeight = (w->rChild != NULL) ? w->rChild->height : 0;

    // 높이 차이가 -1, 0, 1인 경우에만 true 반환
    int heightDifference = leftHeight - rightHeight;
    if (heightDifference >= -1 && heightDifference <= 1)
    {
        return true;
    }
    return false;
}

// makeNode 함수
NODE *makeNode(NODE *w, int key)
{ //  newNode 동적 할당 및 메모리 할당 여부 검사
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Memory Allocation Failed\n");
        exit(1);
    }
    // newNode 초기화
    newNode->parent = w;
    newNode->key = key;
    newNode->height = 0;
    newNode->lChild = newNode->rChild = NULL;
    return newNode; // newNode 반환
}

// treeSearch 함수
NODE *treeSearch(NODE *w, int key)
{ // 루트가 NULL인 경우 처리
    if (w == NULL)
    {
        return NULL; // NULL 반환
    }

    // 현재 노드가 외부 노드인 경우
    if (isExternal(w))
    {
        return w; // 현재 노드 반환
    }

    if (key == w->key) // 현재 노드의 키와 탐색하는 키가 같은 경우
    {
        return w; // w 반환
    }
    else if (key < w->key) // 현재 노드의 키가 탐색하는 키보다 큰 경우
    {
        return treeSearch(w->lChild, key); // 좌측 자식 노드 탐색
    }
    else // 현재 노드의 키가 탐색하는 키보다 작은 경우
    {
        return treeSearch(w->rChild, key); // 우측 자식 노드 탐색
    }
}

// findElement 함수
int findElement(int k)
{
    NODE *tmp = treeSearch(root, k); // 찾는 키에 해당하는 노드 탐색
    // 찾는 키가 없는 경우
    if (tmp == NULL || isExternal(tmp))
    {
        return -1; // -1 반환
    }
    return tmp->key; // 찾은 키 반환
}

// insertItem 함수
void insertItem(int key)
{
    if (root == NULL)
    {
        root = makeNode(NULL, key); // 루트 노드 생성
        expandExternal(root);       // 외부 노드 확장
        return;
    }

    NODE *w = treeSearch(root, key); // 트리에서 삽입 위치 탐색
    // 삽입할 위치가 외부 노드인지 확인
    if (isExternal(w))
    {
        w->key = key;                  // 빈 노드에 키 값 할당
        expandExternal(w);             // 외부 노드 확장
        searchAndFixAfterInsertion(w); // 균형 조정
    }
}

// expandExternal 함수
void expandExternal(NODE *w)
{
    if (!isExternal(w)) // 이미 확장된 노드인지 검사
    {
        return; // 이미 확장된 외부 노드는 확장하지 않음
    }

    // 외부 노드를 자식 노드로 확장 (lChild, rChild)
    w->lChild = makeNode(w, -1); // 왼쪽 외부 노드 생성
    w->rChild = makeNode(w, -1); // 오른쪽 외부 노드 생성
    updateHeight(w);             // 노드 높이 갱신
}

// searchAndFixAfterInsertion 함수
void searchAndFixAfterInsertion(NODE *w)
{
    NODE *z = w;
    // z가 루트 노드가 아니고 균형이 유지되는 경우
    while (z != NULL && isBalanced(z))
    {
        updateHeight(z); // 높이 갱신
        z = z->parent;   // 부모 노드로 이동
    }

    // z가 NULL일 경우
    if (z == NULL)
    {
        return;
    }

    NODE *y = (z->lChild != NULL && z->lChild->height > z->rChild->height) ? z->lChild : z->rChild; // y의 위치 선택
    if (y == NULL)
    {
        return;
    }
    NODE *x = (y->lChild != NULL && y->lChild->height > y->rChild->height) ? y->lChild : y->rChild; // x의 위치 선택
    if (x == NULL)
    {
        return;
    }

    restructure(x, y, z); // restructure 시행
}

// restructure 함수
NODE *restructure(NODE *x, NODE *y, NODE *z)
{
    NODE *a = NULL, *b = NULL, *c = NULL;
    NODE *T0 = NULL, *T1 = NULL, *T2 = NULL, *T3 = NULL;
    // 중위순회 왼 -> 부모 -> 오 // 왼 < 부모 < 오
    if (z->key < y->key && y->key < x->key)
    {
        a = z;
        b = y;
        c = x;

        T0 = a->lChild;
        T1 = b->lChild;
        T2 = c->lChild;
        T3 = c->rChild;
    }
    else if (x->key < y->key && y->key < z->key)
    {
        a = x;
        b = y;
        c = z;

        T0 = a->lChild;
        T1 = a->rChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }
    else if (y->key < x->key && x->key < z->key)
    {
        a = y;
        b = x;
        c = z;

        T0 = a->lChild;
        T1 = b->lChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }
    else
    {
        a = z;
        b = x;
        c = y;

        T0 = a->lChild;
        T1 = b->lChild;
        T2 = b->rChild;
        T3 = c->rChild;
    }

    if (z->parent == NULL)
    {
        root = b;
        b->parent = NULL;
    }
    else
    {
        b->parent = z->parent;
        if (z->parent->lChild == z)
            z->parent->lChild = b;
        else if (z->parent->rChild == z)
            z->parent->rChild = b;
    }

    a->lChild = T0;
    a->rChild = T1;
    T0->parent = a;
    T1->parent = a;
    updateHeight(a);

    c->lChild = T2;
    c->rChild = T3;
    T2->parent = c;
    T3->parent = c;
    updateHeight(c);

    b->lChild = a;
    b->rChild = c;
    a->parent = b;
    c->parent = b;
    updateHeight(b);

    return b;
}

// updateHeight 함수
void updateHeight(NODE *w)
{
    // w가 NULL이거나 외부 노드인 경우
    if (w == NULL || isExternal(w))
    {
        return;
    }

    int leftHeight = (w->lChild != NULL) ? w->lChild->height : 0;  // 왼쪽 서브 트리의 높이
    int rightHeight = (w->rChild != NULL) ? w->rChild->height : 0; // 오른쪽 서브 트리의 높이

    w->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; // 높이 업데이트
}

// preOrderTraversal 함수
void preOrderTraversal(NODE *w)
{
    // w가 NULL이거나 -1인 경우 (외부 노드로 간주)
    if (w == NULL || w->key == -1)
    {
        return;
    }
    // 전위 순회 시행
    printf(" %d", w->key);
    preOrderTraversal(w->lChild);
    preOrderTraversal(w->rChild);
}
