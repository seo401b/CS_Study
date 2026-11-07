#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 11 //use prime

typedef enum{
    SLOT_EMPTY, 
    SLOT_OCCUPIED, //Hold a key-value
    SLOT_DELETED //Tombstone (after free) / use when searching algorithm do not gives up early.
} SlotState;

typedef struct HashEntry{
    char* key;
    int value;
    SlotState state;
} HashEntry;

typedef struct HashTable
{
    int capacity;
    int size;
    HashEntry* entries;
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
    table->size = 0;
    table->entries = (HashEntry*)calloc(capacity, sizeof(HashEntry));
    return table;
}

void ht_insert(HashTable* table, const char* key, int value){
    unsigned long idx = hash_function(key, table->capacity);
    unsigned long start_idx = idx;

    while(table->entries[idx].state == SLOT_OCCUPIED){
        if(strcmp(table->entries[idx].key, key)==0){
            table->entries[idx].value = value;
            return;
        }
        idx = (idx+1)% table->capacity;
        if(idx == start_idx){
            printf("Table is full\n");
            return;
        }
    }
    if(table->entries[idx].state == SLOT_EMPTY){
        table->size++;
    }

    if(table->entries[idx].key != NULL){
        free(table->entries[idx].key);
    }

    table->entries[idx].key = strdup(key);
    table->entries[idx].value = value;
    table->entries[idx].state = SLOT_OCCUPIED;
}

int ht_search(HashTable* table, const char* key, int* out_value){
    unsigned long idx = hash_function(key, table->capacity);
    unsigned long start_idx = idx;

    while(table->entries[idx].state != SLOT_EMPTY){
        if(table->entries[idx].state == SLOT_OCCUPIED &&
            strcmp(table->entries[idx].key, key)==0){
            *out_value = table->entries[idx].value;
            return 1;
        }
        idx = (idx+1)% table->capacity;
        if(idx == start_idx) break;
    }
    return 0;
}

int ht_delete(HashTable* table, const char* key){
    unsigned long idx = hash_function(key, table->capacity);
    unsigned long start_idx = idx;

    while(table->entries[idx].state != SLOT_EMPTY){
        if(table->entries[idx].state == SLOT_OCCUPIED &&
            strcmp(table->entries[idx].key, key)==0){
            free(table->entries[idx].key);
            table->entries[idx].key = NULL;
            table->entries[idx].state = SLOT_DELETED;
            table->size--;
            return 1;
        }
        idx = (idx+1) % table->capacity;
        if(idx==start_idx) break;
    }
}

void free_table(HashTable* table){
    for(int i = 0; i < table->capacity; i++){
        if(table->entries[i].state == SLOT_OCCUPIED){
            free(table->entries[i].key);
        }
    }
    free(table->entries);
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