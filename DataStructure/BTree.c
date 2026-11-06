#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define T 3 // 최소 차수 (최대 키: 2*T - 1 = 5, 최대 자식: 2*T = 6)

typedef struct BTreeNode {
    int num_keys;                      // 현재 노드에 들어있는 키의 개수
    char keys[2 * T - 1][64];          // 키 배열 (문자열 저장)
    struct BTreeNode* children[2 * T]; // 자식 노드 포인터 배열
    bool is_leaf;                      // 리프 노드 여부 (true면 자식 없음)
} BTreeNode;

// 1. 새 노드를 동적 할당하고 초기화하는 함수
BTreeNode* create_node(bool is_leaf) {
    BTreeNode* pNewNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    if(pNewNode==NULL) return NULL;

    memset(pNewNode, 0, sizeof(BTreeNode));
    pNewNode->is_leaf = is_leaf;
    pNewNode->num_keys = 0;
    // TODO: malloc으로 메모리 할당 후 is_leaf 설정, num_keys = 0, 자식/키 초기화
    return pNewNode;
}

// 2. B-Tree에서 특정 키를 탐색하는 함수
// 찾은 노드의 주소를 반환하거나, 없으면 NULL 반환
BTreeNode* search(BTreeNode* root, const char* key) {
    if(root==NULL) return NULL;

    int i = 0;
    while(i < root->num_keys && strcmp(key, root->keys[i]) > 0){
        i++;
    }

    if(i < root->num_keys && strcmp(key, root->keys[i]) == 0){
        return root;
    }

    if(root->is_leaf) return NULL;

    return search(root->children[i], key);
    // TODO: 
    // 1. 현재 노드의 키들을 순회하며 key가 있는지 확인
    // 2. 찾았으면 현재 노드 반환
    // 3. 못 찾았고 리프 노드면 NULL 반환
    // 4. 내부 노드라면 적절한 자식 노드로 내려가서 재귀 탐색
}

// 3. 가득 찬 자식 노드(Full Child)를 둘로 쪼개는 함수 (삽입의 핵심)
// parent: 부모 노드, i: 꽉 찬 자식의 인덱스, child: 꽉 찬 자식 노드
void split_child(BTreeNode* parent, int i, BTreeNode* child) {
    BTreeNode* bro = create_node(child->is_leaf);
    bro->num_keys = T-1;

    for(int j = 0; j < T-1; ++j){
        strcpy(bro->keys[j], child->keys[j+T]);
    } //child T이후 노드 bro로 복사

    if(!child->is_leaf){
        for(int j = 0; j < T; ++j){
            bro->children[j] = child->children[j+T];
        }
    } //child의 children도 복사

    child->num_keys = T-1;

    for(int j = parent->num_keys; j >= i+1; j--){
        parent->children[j+1] = parent->children[j];
    }
    parent->children[i+1] = bro; //bro 들어갈 자리 만들고 넣기

    for(int j = parent->num_keys-1; j >= i; j--){
        strcpy(parent->keys[j+1], parent->keys[j]);
    }
    strcpy(parent->keys[i], child->keys[T-1]); //child->key들어갈 자리 만들고 넣기

    parent->num_keys++;
    
    // TODO:
    // 1. child 노드의 중간 키를 추출하여 parent의 적절한 위치로 올림
    // 2. child 노드를 반으로 쪼개어 새로운 형제 노드를 만듦
    // 3. parent의 자식 포인터 배열과 키 배열을 알맞게 재정렬
}

// 4. 가득 차지 않은 노드에 키를 삽입하는 내부 헬퍼 함수
void insert_non_full(BTreeNode* node, const char* key) {
    int i = node->num_keys-1;
    if(node->is_leaf){
        while(i>=0 && strcmp(key, node->keys[i]) < 0){
            strcpy(node->keys[i+1], node->keys[i]);
            i--;
        }
        strcpy(node->keys[i+1], key);
        node->num_keys++;
    }
    else{
        while(i >= 0 && strcmp(key, node->keys[i]) < 0){
            i--;
        }
        i++;

        if(node->children[i]->num_keys == 2*T-1){
            split_child(node, i, node->children[i]);
            if(strcmp(key, node->keys[i])>0){
                i++;
            }
        }
        insert_non_full(node->children[i], key);
    }
    // TODO:
    // 1. 리프 노드라면, 알맞은 자리를 찾아 문자열 정렬 순서에 맞게 삽입
    // 2. 내부 노드라면, 어떤 자식으로 내려가야 할지 결정
    // 3. 내려갈 자식 노드가 가득 차(2*T-1개) 있다면 split_child를 먼저 호출한 후 자식으로 이동
}

// 5. B-Tree에 새로운 키를 삽입하는 메인 함수
BTreeNode* insert(BTreeNode* root, const char* key) {
    if(root->num_keys == 2*T-1){
        BTreeNode* new_root = create_node(false);
        new_root->children[0] = root;
        split_child(new_root, 0, root);

        int i = 0;
        if(strcmp(key, new_root->keys[0])>0){
            i++;
        }
        insert_non_full(new_root->children[i], key);
        return new_root;
    }
    else{
        insert_non_full(root, key);
        return root;
    }
    // TODO:
    // 1. 루트 노드가 가득 차 있는 경우 예외 처리 (새로운 루트를 만들고 split_child 수행)
    // 2. 루트가 가득 차지 않았다면 insert_non_full 호출
}

void print_tree(BTreeNode* root, int level){
    if(root != NULL){
        printf("Level %d [ ", level);
        for(int i = 0; i < root->num_keys; i++){
            printf("%s ", root->keys[i]);
        }
        printf("]\n");

        for(int i =0; i <= root->num_keys; i++){
            print_tree(root->children[i], level+1);
        }
    }
}






int main() {
    // 최초 루트 노드 생성 (리프 상태로 시작)
    BTreeNode* root = create_node(true);

    // 테스트용 데이터 삽입 (영어 단어들)
    const char* words[] = {"apple", "banana", "grape", "orange", "pear", "peach", "mango", "berry", "melon"};
    int n = sizeof(words) / sizeof(words[0]);

    printf("=== B-Tree 키 삽입 시작 ===\n");
    for (int i = 0; i < n; i++) {
        printf("Insert: %s\n", words[i]);
        root = insert(root, words[i]);
    }

    printf("\n=== B-Tree 구조 출력 (Preorder) ===\n");
    print_tree(root, 0);

    // 검색 테스트
    printf("\n=== 검색 테스트 ===\n");
    const char* targets[] = {"mango", "melon", "durian"};
    for (int i = 0; i < 3; i++) {
        BTreeNode* res = search(root, targets[i]);
        if (res != NULL) {
            printf("Target '%s' FOUND in tree!\n", targets[i]);
        } else {
            printf("Target '%s' NOT FOUND.\n", targets[i]);
        }
    }

    return 0;
}