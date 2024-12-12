#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// node 구조체
typedef struct node
{
    int key;
    struct node *parent;
    struct node *lChild;
    struct node *rChild;
} NODE;

NODE *root = NULL; // root 초기화

// 함수 원형
NODE *makeNode(NODE *, int);
int findElement(int);
void insertItem(int);
NODE *treeSearch(NODE *, int);
int removeElement(int);
bool isExternal(NODE *);
bool isInternal(NODE *);
NODE *inOrderSucc(NODE *);
void preOrderTraversal(NODE *);
NODE *reduceExternal(NODE *z);
NODE *sibling(NODE *w);
bool isRoot(NODE *w);

int main()
{
    int k;
    char command;

    /*
    #######################################################################################
    i <키> : 입력 <키>에 대한 노드 생성 및 트리에 삽입
    d <키> : 입력 <키>가 트리에 존재하면 해당 노드 삭제 후 삭제된 키를 출력, 없으면 ‘X’를 출력
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
        // 탐색 명령어 입력
        else if (command == 's')
        {
            scanf("%d", &k);             // 탐색할 키 입력
            int result = findElement(k); // findElement 시행 후 반환 값 저장

            // 반환 값이 -1이 아닌 경우
            if (result != -1)
            {
                printf("%d\n", result); // 저장된 반환 값 출력
            }
            // 반환 값이 -1인 경우
            else
            {
                printf("X\n"); // X 출력
            }
        }
        // 삭제 명령어 입력
        else if (command == 'd')
        {
            scanf("%d", &k);                // 삭제할 키 입력
            int removed = removeElement(k); // removeElement 시행 후 반환 값 저장
            // 반환 값이 -1이 아닌 경우
            if (removed != -1)
            {
                printf("%d\n", removed);
            }
            // 반환 값이 -1인 경우
            else
            {
                printf("X\n");
            }
        }
        // 인쇄 명령어 입력
        else if (command == 'p')
        {
            preOrderTraversal(root); // 전위 순회 시행
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

// makeNode 함수
NODE *makeNode(NODE *parent, int key)
{ // newNode 동적 할당 및 메모리 할당 여부 검사
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Memory Allocation Failed\n");
        exit(1);
    }
    // newNode 초기화
    newNode->key = key;
    newNode->parent = parent;
    newNode->lChild = newNode->rChild = NULL;
    return newNode; // newNode 반환
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

// isRoot 함수
bool isRoot(NODE *w)
{
    return w->parent == NULL; // 루트인 경우 true 반환
}

// sibling 함수
NODE *sibling(NODE *w)
{ // 현재 노드가 루트인 경우
    if (isRoot(w))
    {
        printf("Invalid Node Exception\n"); // 경고 출력
        return NULL;                        // NULL 반환
    }
    // 현재 노드가 좌측 자식인 경우
    if (w == w->parent->lChild)
    {
        return w->parent->rChild; // 우측 자식 반환
    }
    // 현재 노드가 우측 자식인 경우
    else
    {
        return w->parent->lChild; // 좌측 자식 반환
    }
}

// treeSearch 함수
NODE *treeSearch(NODE *node, int key)
{ // 루트가 NULL인 경우 처리
    if (node == NULL)
    {
        return NULL; // NULL 반환
    }

    // 현재 노드가 외부 노드인 경우
    if (isExternal(node))
    {
        return node; // 현재 노드 반환
    }
    // 찾는 키와 일치할 경우
    if (key == node->key)
    {
        return node; // 현재 노드 반환
    }
    // 찾는 키가 현재 노드의 키보다 작은 경우
    else if (key < node->key)
    {
        return treeSearch(node->lChild, key); // 좌측 자식 노드 탐색
    }
    // 찾는 키가 현재 노드의 키보다 큰 경우
    else
    {
        return treeSearch(node->rChild, key); // 우측 자식 노드 탐색
    }
}

// findElement 함수
int findElement(int k)
{
    NODE *tmp = treeSearch(root, k); // 찾는 키에 해당하는 노드 탐색
    // 찾는 키가 없는 경우
    if (isExternal(tmp))
    {
        return -1;
    }
    return tmp->key; // 찾은 키 반환
}

// insertItem 함수
void insertItem(int k)
{
    if (root == NULL)
    {
        root = makeNode(NULL, k);         // 루트가 비어 있으면 루트 생성
        root->lChild = makeNode(root, 0); // 외부 노드
        root->rChild = makeNode(root, 0); // 외부 노드
        return;
    }

    NODE *w = treeSearch(root, k); // 트리에서 적절한 위치 탐색
    if (isInternal(w))
    {
        printf("중복된 키\n"); // 중복 경고
        return;
    }
    // 새 노드 삽입
    w->key = k;
    w->lChild = makeNode(w, 0); // 외부 노드 생성
    w->rChild = makeNode(w, 0); // 외부 노드 생성
}

// inOrderSucc 함수
NODE *inOrderSucc(NODE *w)
{
    w = w->rChild; // 중위 순회 후속자는 오른쪽 서브 트리의 최솟값
    // 외부 노드에 도달한 경우
    if (isExternal(w))
    {
        printf("Invalid Node Exception.\n"); // 경고 출력
        exit(1);
    }
    // 외부 노드에 도달하지 않은 경우
    while (isInternal(w->lChild))
    {
        w = w->lChild; // 노드 이동
    }
    return w; // 중위 순회 후속자 반환
}

// reduceExternal 함수
NODE *reduceExternal(NODE *z)
{
    NODE *w = z->parent;   // 외부 노드 z의 부모 노드
    NODE *zs = sibling(z); // 외부 노드 z의 형제 노드

    // 부모가 루트인 경우
    if (isRoot(w))
    {
        root = zs;         // 형제 노드를 새로운 루트로 설정
        zs->parent = NULL; // 루트의 부모는 NULL로 설정
    }
    // 부모가 루트가 아닌 경우
    else
    {
        NODE *g = w->parent; // 외부 노드 z의 부모의 부모 노드
        zs->parent = g;      // 형제 노드가 부모의 자식으로 대체됨
        if (w == g->lChild)
        {
            g->lChild = zs; // 왼쪽 자식인 경우
        }
        else
        {
            g->rChild = zs; // 오른쪽 자식인 경우
        }
    }

    free(z); // 외부 노드 z 메모리 해제
    free(w); // 부모 노드 w 메모리 해제

    return zs; // 형제 노드 zs 반환
}

// removeElement 함수
int removeElement(int k)
{
    NODE *w = treeSearch(root, k); // 삭제할 노드 탐색
    // 삭제할 노드가 없는 경우
    if (isExternal(w))
    {
        return -1;
    }

    NODE *z, *y;
    // w의 자식 노드가 존재하는지 확인
    if (isExternal(w->lChild)) // 왼쪽 자식이 외부 노드인 경우
    {
        z = w->lChild; // z는 왼쪽 자식 노드
    }
    else if (isExternal(w->rChild)) // 오른쪽 자식이 외부 노드인 경우
    {
        z = w->rChild; // z는 오른쪽 자식 노드
    }
    // w의 자식 노드가 모두 내부 노드인 경우
    else
    {
        y = inOrderSucc(w); // 중위 순회 후속자 탐색
        w->key = y->key;    // 중위 순회 후속자의 키를 현재 노드의 키로 복사
        z = y->lChild;      // z는 중위 순회 후속자의 왼쪽 자식 노드
    }
    reduceExternal(z); // reduceExternal 시행
    return k;          // 삭제 key 반환
}

// preOrderTraversal 함수
void preOrderTraversal(NODE *node)
{ // 루트가 비어 있거나 외부 노드인 경우
    if (node == NULL || isExternal(node))
    {
        return; // 함수 종료
    }
    printf(" %d ", node->key);       // 현재 노드의 키 출력
    preOrderTraversal(node->lChild); // 왼쪽 서브 트리 순회
    preOrderTraversal(node->rChild); // 오른쪽 서브 트리 순회
}