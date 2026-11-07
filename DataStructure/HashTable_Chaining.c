#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct HashNode{
    char* key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable
{
    int capacity;
    HashNode** buckets;
} HashTable;

unsigned long hash_function(const char* str, int capacity){
    unsigned long hash = 5381;
    int c;
    while((c= *str++)){
        hash = ((hash << 5)+hash) + c; // multi 33 + c -> avalanche
    }
    return hash % capacity;
}

HashTable* create_table(int capacity){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->capacity = capacity;
    table->buckets = (HashNode**)calloc(capacity, sizeof(HashNode*));
    return table;
}

void ht_insert(HashTable* table, const char* key, int value){
    unsigned long idx = hash_function(key, table->capacity);

    HashNode* current = table->buckets[idx];
    while(current != NULL){
        if(strcmp(current->key, key)==0){
            current->value = value;
            return;
        }
        current = current->next;
    }

    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = table->buckets[idx];
    table->buckets[idx] = new_node;
}

int ht_search(HashTable* table, const char* key, int* out_value){
    unsigned long idx = hash_function(key, table->capacity);

    HashNode* current = table->buckets[idx];
    while(current != NULL){
        if(strcmp(current->key, key)==0){
            *out_value = current->value;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void free_table(HashTable* table){
    for(int i = 0; i < table->capacity; i++){
        HashNode* current = table->buckets[i];
        while(current != NULL){
            HashNode* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}


int main() {
    HashTable* table = create_table(TABLE_SIZE);

    // Insert key-value pairs
    ht_insert(table, "apple", 100);
    ht_insert(table, "banana", 200);
    ht_insert(table, "cherry", 300);
    
    // Test updating an existing key
    ht_insert(table, "apple", 150);

    // Search tests
    int val;
    if (ht_search(table, "apple", &val)) {
        printf("Found 'apple': %d\n", val);
    }
    if (ht_search(table, "banana", &val)) {
        printf("Found 'banana': %d\n", val);
    }
    if (!ht_search(table, "grape", &val)) {
        printf("'grape' not found in table.\n");
    }

    // Cleanup memory
    free_table(table);
    return 0;
}