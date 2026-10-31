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
    g_pHead = NULL;
    g_pTail = NULL;
    g_nSize = 0;
}

void ReleaseList(void)
{
    NODE* pTmp;
    while(pTmp!=NULL){
        NODE* pDelete = pTmp;
        pTmp = pTmp->next;

        printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
        free(pDelete);
    }
    g_pHead = 0;
    g_pTail = 0;
    g_nSize = 0;
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
    snprintf(pNode->szData, sizeof(pNode->szData), "%s", pszData);

    if(g_pHead==NULL)
    {
        g_pHead = pNode;
        g_pTail = pNode;
    }
    else
    {
        pNode->next = g_pHead;
        g_pHead->prev = pNode;
        g_pHead = pNode;
    }
    g_nSize++;
    return 1;
}

int InsertAtTail(const char* pszData)
{
    NODE* pNode = (NODE*)malloc(sizeof(NODE));
    memset(pNode, 0, sizeof(NODE));
    snprintf(pNode->szData, sizeof(pNode->szData), "%s", pszData);

    if(g_pTail==NULL)
    {
        g_pHead = pNode;
        g_pTail = pNode;
    }
    else
    {
        g_pTail->next = pNode;
        pNode->prev = g_pTail;
        g_pTail = pNode;
    }
    g_nSize++;
    return 1;
}

int DeleteNode(const char* pszData)
{
    NODE* pTmp = g_pHead;
    while(pTmp!=NULL){
        if(strcmp(pTmp->szData, pszData)==0){
            if(pTmp->prev!=NULL){
                pTmp->prev->next = pTmp->next;
            }
            else{
                g_pHead = pTmp->next;
            }
            if(pTmp->next != NULL){
                pTmp->next->prev = pTmp->prev;
            }
            else{
                g_pTail = pTmp->prev;
            }

            free(pTmp);
            g_nSize--;
            return 1;
        }
        pTmp = pTmp->next;
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

int main(void)
{


    InsertAtHead("TEST01");
    InsertAtHead("TEST02");
    InsertAtHead("TEST03");

    PrintList();

    DeleteNode("TEST03");

    PrintList();
    return 0;
}