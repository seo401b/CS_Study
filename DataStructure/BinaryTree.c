#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE
{
    char szData[64];

    struct NODE* left;
    struct NODE* right;
} NODE;

NODE* g_pRoot;
int g_nSize;

void ReleaseTree(NODE* pParent)
{
    if(pParent==NULL) return;

    ReleaseTree(pParent->left);
    ReleaseTree(pParent->right);
    free(pParent);
    g_nSize = 0;
}

void PrintTree(NODE* pParent)
{
    //Tree의 장점으로 정렬없이 출력 순서에 따라 정렬된다는 점이 있다
    //In order
    if(pParent == NULL) return;

    PrintTree(pParent->left);
    printf("[%p] %p, %s [%p]\n", pParent->left, pParent, pParent->szData, pParent->right);
    PrintTree(pParent->right);
}

int InsertNode(const char* pszData)
{
    NODE* pNewNode = (NODE*)malloc(sizeof(NODE));
    memset(pNewNode, 0, sizeof(NODE));
    snprintf(pNewNode->szData, sizeof(pNewNode->szData), pszData);

    if(g_pRoot == NULL)
    {
        g_pRoot = pNewNode;
        return 1;
    }

    NODE* pTmp = g_pRoot;
    while(pTmp != NULL)
    {
        if(strcmp(pTmp->szData, pNewNode->szData)>0)
        {
            if(pTmp->left==NULL)
            { 
            pTmp->left = pNewNode;
            break;
            }
            else
            {
                pTmp = pTmp->left;
                continue;
            }
        }
        else
        {
            if(pTmp->right==NULL)  
            {
                pTmp->right = pNewNode;
                break;
            }
            else
            {
                pTmp = pTmp->right;
                continue;
            }
        }
    }
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

int DeleteNode(const char* pszData)
{
    NODE* pParent = NULL;
    NODE* pTmp = g_pRoot;

    while(pTmp!=NULL)
    {
        int result = strcmp(pszData, pTmp->szData);
        if(result==0) break;

        pParent = pTmp;
        if(result<0)
        {
            pTmp = pTmp->left;
        }
        else
        {
            pTmp = pTmp->right;
        }
    }

    if(pTmp == NULL) return 0;

    if(pTmp->left==NULL || pTmp->right==NULL)
    {
        NODE* pChild = (pTmp->left != NULL) ? pTmp->left : pTmp->right;

        if(pTmp==g_pRoot){
            g_pRoot = pChild;
        }
        else if(pParent->left == pTmp){
            pParent->left = pChild;
        }
        else{
            pParent->right = pChild;
        }

        free(pTmp);
    }
    else{//자식 둘다 있음, 왼쪽 서브트리 가장 큰 값 또는 오른쪽 가장 작은 값 대체자 찾기
        NODE* pSuccParent = pTmp;
        NODE* pSucc = pTmp->right;

        while(pSucc->left != NULL)
        {
            pSuccParent = pSucc;
            pSucc = pSucc->left;
        }

        snprintf(pTmp->szData, sizeof(pTmp->szData), "%s", pSucc->szData);

        if(pSuccParent->left == pSucc){
            pSuccParent->left = pSucc->right;
        }
        else{
            pSuccParent->right = pSucc->right;
        }
        free(pSucc);
    }
    g_nSize--;
    return 1;
}

int GetSize(void)
{
    return g_nSize;
}

int GetLength(void)
{
    return GetSize();
}

int main(void)
{
// 1. 데이터 삽입 테스트
    InsertNode("5번");
    InsertNode("3번");
    InsertNode("7번");
    InsertNode("2번");
    InsertNode("4번");
    InsertNode("6번");
    InsertNode("8번");

    printf("=== 초기 트리 출력 (전체 개수: %d) ===\n", GetSize());
    PrintTree(g_pRoot);
    printf("\n");

    // 2. 검색 테스트
    NODE* pFound = FindNode("4번");
    if(pFound) {
        printf("검색 성공: %s 노드를 찾았습니다.\n\n", pFound->szData);
    }

    // 3. 삭제 테스트 (자식이 2개인 "5번" 또는 자식이 있는 "3번" 삭제해보기)
    printf("=== '3번' 노드 삭제 후 ===\n");
    DeleteNode("3번");
    PrintTree(g_pRoot);
    printf("현재 크기: %d\n\n", GetSize());

    // 4. 메모리 해제
    ReleaseTree(g_pRoot);
    g_pRoot = NULL;
    g_nSize = 0;
    printf("모든 메모리가 안전하게 해제되었습니다.\n");

    return 0;
    return 0;
}