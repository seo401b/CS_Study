#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE {
    char szData[64];
    struct NODE* next;
} NODE;

NODE* g_pHead = NULL;
NODE* g_pTail = NULL;

//연결 리스트 전체 데이터 출력
void PrintList(void){
    NODE* pHead = g_pHead;
    while(pHead != NULL){
        printf("[%p] %s, next[%p]\n", pHead, pHead->szData, pHead->next);
        pHead = pHead->next;
    }
}

int InsertAtHead(const char* pszData){
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    snprintf(pNode->szData, sizeof(pNode->szData), "%s", pszData);

    if(g_pHead == NULL) 
    {
        g_pHead = pNode;
        g_pTail = pNode;
    }
    else
    {
        pNode->next = g_pHead;
        g_pHead = pNode;
    }
    return 1;
}

int InsertAtTail(const char* pszData){
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    snprintf(pNode->szData, sizeof(pNode->szData), "%s", pszData);

    if(g_pTail ==NULL)
    {
        g_pHead = pNode;
        g_pTail = pNode;
    }
    else
    {
        g_pTail->next = pNode;
        g_pTail = pNode;
    }
    return 1;
}

void ReleaseList(void){
    NODE* pTmp = g_pHead;
    while(pTmp!=NULL){
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;

        printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
        free(pDelete);
    }
    g_pHead = 0;
    g_pTail = 0;
}

int DeleteData(char* pszData){
    NODE* pTmp = g_pHead;
    NODE* pPrev = NULL;
    while(pTmp != NULL){
        if(strcmp(pTmp->szData, pszData)==0)
        {
            if(pPrev != NULL)
                pPrev->next = pTmp->next;
            else 
                g_pHead = pTmp->next;
            if(pTmp == g_pTail)
                g_pTail = pPrev;
            free(pTmp);
            return 1;
        }
        pPrev = pTmp;
        pTmp = pTmp->next;
    }
    return 0;
}

int main(){

    InsertAtHead("TEST01");
    InsertAtHead("TEST02");
    InsertAtHead("TEST03");

    PrintList();

    DeleteData("TEST03");

    PrintList();

    return 0;
}