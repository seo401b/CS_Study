#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE
{
    char szData[64];

    struct NODE* prev;
    struct NODE* next;
} NODE;

NODE* g_pHead;
NODE* g_pTail;
int g_nSize;

void InitList(void)
{
    g_pHead = (NODE*)malloc(sizeof(NODE));
    g_pTail = (NODE*)malloc(sizeof(NODE));
    g_nSize = 0;
    memset(g_pHead, 0, sizeof(NODE));
    memset(g_pTail, 0, sizeof(NODE));

    snprintf(g_pHead->szData, sizeof(g_pHead->szData), "DUMMY HEAD");
    snprintf(g_pTail->szData, sizeof(g_pTail->szData), "DUMMY TAIL");

    g_pHead->next = g_pTail;
    g_pTail->prev = g_pHead;
}

void ReleaseList(void)
{
    NODE* pTmp = g_pHead;
    while(pTmp != NULL)
    {
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;

        free(pDelete);
    }
}

void PrintList(void)
{
    NODE* pPrint = g_pHead;
    while(pPrint!=NULL){
        printf("[%p]: %s, next[%p]\n", pPrint, pPrint->szData, pPrint->next);
        pPrint = pPrint->next;
    }
    printf("\n");
}

int InsertAtHead(const char* pszData)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    snprintf(pNode->szData, sizeof(pNode->szData), pszData);
    //새로 추가된 노드의 포인터 정리
    pNode->next = g_pHead->next;
    pNode->prev = g_pHead;

    //앞뒤 노드 포인터 정리
    g_pHead->next = pNode;
    pNode->next->prev = pNode;

    g_nSize++;

    return g_nSize;
}

int InsertAtTail(const char* pszData)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    snprintf(pNode->szData, sizeof(pNode->szData), pszData);
    //새로 추가된 노드 포인터 정리
    pNode->next = g_pTail;
    pNode->prev = g_pTail->prev;

    //앞뒤 노드 포인터 정리;
    g_pTail->prev = pNode;
    pNode->prev->next = pNode;

    g_nSize++;
    return g_nSize;
}

NODE* FindNode(const char* pszData){
    NODE* pTmp = g_pHead->next;
    while(pTmp != g_pTail)
    {
        if(strcmp(pTmp->szData, pszData)==0)
            return pTmp;
        pTmp = pTmp->next;
    }
    return NULL;
}

int DeleteNode(const char* pszData)
{
    NODE* pTmp = FindNode(pszData);

    pTmp->prev->next = pTmp->next;
    pTmp->next->prev = pTmp->prev;
    free(pTmp);

    g_nSize--;
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

int InsertAt(int idx, const char* pszData)
{
    if(idx<0 || idx>g_nSize) return 0;

    NODE* pTmp = g_pHead->next;
    int i = 0;
    while(i<idx)
    {
        pTmp = pTmp->next;
        ++i;
    }
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    snprintf(pNode->szData, sizeof(pNode->szData), "%s", pszData);

    pNode->next = pTmp;
    pNode->prev = pTmp->prev;

    pNode->prev->next = pNode;
    pNode->next->prev = pNode;

    g_nSize++;
    return 1;


    //0은 g_pHead
    // int tmpidx = 0;
    // NODE* pTmp = g_pHead;

    // NODE* pNode = (NODE*)malloc(sizeof(NODE));
    // memset(pNode, 0, sizeof(NODE));
    // snprintf(pNode->szData, sizeof(pNode->szData), pszData);

    // while(tmpidx < idx)
    // {
    //     pTmp = pTmp->next;
    //     tmpidx++;
    // }
    // pNode->next = pTmp->next;
    // pNode->prev = pTmp;

    // pTmp->next->prev = pNode;
    // pTmp->next = pNode;

    // return 0;
}

NODE* GetAt(int idx)
{
    int i = 0;
    NODE* pTmp = g_pHead->next;
    while(pTmp != g_pTail)
    {
        if(i==idx)
            return pTmp;
        pTmp = pTmp->next;
        ++i;
    }
    return NULL;
}

int main(void)
{

    InitList();

    InsertAtHead("TEST01");
    InsertAtHead("TEST02");
    InsertAtHead("TEST03");

    PrintList();

    if(FindNode("TEST01"))
        printf("Found\n");

    DeleteNode("TEST03");

    PrintList();
    return 0;
}