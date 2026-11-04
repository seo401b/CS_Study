#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct NODE
{
    char szData[64];
    int height;
    struct NODE* left;
    struct NODE* right;
} NODE;

NODE* g_pRoot;
int g_nSize;

int GetHeight(NODE* pNode){
    if(pNode==NULL) return 0;
    return pNode->height;
}

int GetBalanceFactor(NODE* pNode){
    if(pNode==NULL) return 0;
    return GetHeight(pNode->left) - GetHeight(pNode->right);
}

//x < y
NODE* LL(NODE* y){
    NODE* x = y->left;
    NODE* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x; // 기존 y의 자리를 x가 대체
}

NODE* RR(NODE* x){
    NODE* y = x->right;
    NODE* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return y;
}

NODE* LR(NODE* node){
    node->left = RR(node->left);
    return LL(node);
}

NODE* RL(NODE* node){
    node->right = LL(node->right);
    return RR(node);
}

void ReleaseTree(NODE* pParent)
{
    if(pParent==NULL) return;

    ReleaseTree(pParent->left);
    ReleaseTree(pParent->right);
    free(pParent);
    g_nSize = 0;
}

// void PrintTree(NODE* pParent)
// {
//     //Tree의 장점으로 정렬없이 출력 순서에 따라 정렬된다는 점이 있다
//     //In order
//     if(pParent == NULL) return;

//     PrintTree(pParent->left);
//     printf("[%p] %p, %s [%p]\n", pParent->left, pParent, pParent->szData, pParent->right);
//     PrintTree(pParent->right);
// }

NODE* _InsertNode(NODE* pNode, const char* pszData)
{
    if(pNode==NULL){
        NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
        memset(pNewNode, 0, sizeof(NODE));
        snprintf(pNewNode->szData, sizeof(pNewNode->szData), pszData);
        pNewNode->height = 1;
        return pNewNode;
    }

    int result = strcmp(pszData, pNode->szData);
    if(result < 0){
        pNode->left = _InsertNode(pNode->left, pszData);
    }
    else if(result > 0){
        pNode->right = _InsertNode(pNode->right, pszData);
    }
    else{
        return pNode;
    }

    pNode->height = max(GetHeight(pNode->left), GetHeight(pNode->right)) + 1;

    int balance = GetBalanceFactor(pNode);

    if(balance > 1 && strcmp(pszData, pNode->left->szData)<0){
        return LL(pNode);
    }
    if(balance < -1 && strcmp(pszData, pNode->right->szData)>0){
        return RR(pNode);
    }
    if(balance > 1 && strcmp(pszData, pNode->left->szData)>0){
        return LR(pNode);
    }
    if(balance < -1 && strcmp(pszData, pNode->right->szData)<0){
        return RL(pNode);
    }

    return pNode;
}

int InsertNode(const char* pszData){
    g_pRoot = _InsertNode(g_pRoot, pszData);
    g_nSize++;
    return 1;
}

NODE* FindNode(const char* pszData)
{
    NODE* pTmp = g_pRoot;
    while(pTmp != NULL)
    {
        int result = strcmp(pszData, pTmp->szData);

        if(result==0) return pTmp;
        else if(result<0) pTmp = pTmp->left;
        else pTmp = pTmp->right;
    }
    return NULL;
}

NODE* _DeleteNode(NODE* pNode, const char* pszData, int* pDeleted)
{
    if(pNode==NULL) return NULL;

    int result = strcmp(pszData, pNode->szData);
    if(result<0){
        pNode->left = _DeleteNode(pNode->left, pszData, pDeleted);
    }
    else if(result>0){
        pNode->right = _DeleteNode(pNode->right, pszData, pDeleted);
    }
    else{
        *pDeleted = 1;
        if(pNode->left == NULL || pNode->right == NULL){ // 자식이 1이하
            NODE* pChild = (pNode->left != NULL) ? pNode->left : pNode->right;

            if(pChild == NULL){
                free(pNode);
                return NULL;
            }
            else{
                *pNode = *pChild;
                free(pChild);
            }
        }
        else{//자식 2
            NODE* pSucc = pNode->right;
            while(pSucc->left != NULL){
                pSucc = pSucc->left;
            }

            snprintf(pNode->szData, sizeof(pNode->szData), pSucc->szData);
            pNode->right = _DeleteNode(pNode->right, pSucc->szData, pDeleted);
        }
    }
    if(pNode == NULL) return NULL;

    pNode->height = max(GetHeight(pNode->left), GetHeight(pNode->right))+1;

    int balance = GetBalanceFactor(pNode);
    
    if(balance > 1 && GetBalanceFactor(pNode->left)>=0){
        return LL(pNode);
    }
    if(balance < -1 && GetBalanceFactor(pNode->right)>=0){
        return RR(pNode);
    }
    if(balance > 1 && GetBalanceFactor(pNode->left)<0){
        return LR(pNode);
    }
    if(balance >1 && GetBalanceFactor(pNode->right)<0){
        return RL(pNode);
    }
    return pNode;
}

int DeleteNode(const char* pszData){
    int deleted = 0;
    g_pRoot = _DeleteNode(g_pRoot, pszData, &deleted);
    if(deleted){
        g_nSize--;
        return 1;
    }
    return 0;
}

int GetSize(void)
{
    return g_nSize;
}

int GetLength(void)
{
    return GetSize();
}

void PrintTree(NODE* pNode, int space){
    if(pNode == NULL) return;
    space+= 10;
    PrintTree(pNode->right, space);

    //printf('\n');
    for(int i = 10; i < space; ++i) 
        printf(" ");
    printf("[%s] h:%d\n", pNode->szData, pNode->height);

    PrintTree(pNode->left, space);
}







int main(void)
{
    
    printf("-> InsertNode(\"10\")\n");
    InsertNode("10");
    PrintTree(g_pRoot, 0);

    printf("-> InsertNode(\"20\")\n");
    InsertNode("20");
    PrintTree(g_pRoot, 0);

    InsertNode("30"); 
    printf("-> InsertNode(\"30\")\n");
    PrintTree(g_pRoot, 0); // 회전 후 20이 루트로 올라온 모양을 볼 수 있음

    printf("-> InsertNode(\"40\")\n");
    InsertNode("40");
    PrintTree(g_pRoot, 0);

    InsertNode("50"); 
    printf("-> InsertNode(\"50\")\n");
    PrintTree(g_pRoot, 0); // 전체 균형이 다시 잡힌 모양 출력

    printf("현재 노드 개수: %d\n\n", GetSize());

    
    printf("-> InsertNode(\"25\")\n");
    InsertNode("25");
    PrintTree(g_pRoot, 0);

    printf("-> InsertNode(\"5\")\n");
    InsertNode("5");
    PrintTree(g_pRoot, 0); // 5가 들어가면서 왼쪽 서브트리에 불균형이 잡히는지 확인


    printf("=== [3단계] 노드 삭제 및 밸런스 재조정 추적 ===\n");
    
    printf("-> DeleteNode(\"30\") 수행 전:\n");
    PrintTree(g_pRoot, 0);
    
    DeleteNode("30");
    
    printf("-> DeleteNode(\"30\") 수행 후 (지워진 위치에서 연쇄적 회전 확인):\n");
    PrintTree(g_pRoot, 0);
    printf("삭제 후 크기: %d\n\n", GetSize());


    printf("=== [4단계] 예외 케이스 테스트 ===\n");
    if (FindNode("999") == NULL) {
        printf("[OK] 없는 데이터 검색 시 NULL 리턴 확인\n");
    }
    if (DeleteNode("999") == 0) {
        printf("[OK] 없는 데이터 삭제 시 0 리턴 확인\n");
    }
    printf("\n");


    ReleaseTree(g_pRoot);
    g_pRoot = NULL;
    g_nSize = 0;
    printf("=== 메모리 해제 완료 ===\n");

    return 0;
}