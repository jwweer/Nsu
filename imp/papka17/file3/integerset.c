#include "integerset.h"
#include <stdlib.h>
#include <string.h>

struct IntegerSet {
    int* keys;
    char* flags;  // 0 - empty, 1 - used, 2 - deleted
    int size;
    int capacity;
};

static const int INITIAL_CAPACITY = 16;
static const int HASH_MULTIPLIER = 2654435761U;

static int hash(int key, int capacity) {
    unsigned int h = (unsigned int)key;
    h = h * HASH_MULTIPLIER;
    return h % capacity;
}

IntegerSet* CreateSet(const int* arr, int size) {
    if (size < 0) return NULL;
    
    IntegerSet* set = (IntegerSet*)malloc(sizeof(IntegerSet));
    if (!set) return NULL;
    
    set->capacity = size > 0 ? size * 2 : INITIAL_CAPACITY;
    if (set->capacity < INITIAL_CAPACITY) {
        set->capacity = INITIAL_CAPACITY;
    }
    
    set->keys = (int*)malloc(set->capacity * sizeof(int));
    set->flags = (char*)calloc(set->capacity, sizeof(char));
    
    if (!set->keys || !set->flags) {
        free(set->keys);
        free(set->flags);
        free(set);
        return NULL;
    }
    
    set->size = 0;
    
    for (int i = 0; i < size; i++) {
        int h = hash(arr[i], set->capacity);
        
        // Поиск свободного места
        while (set->flags[h] == 1) {
            if (set->keys[h] == arr[i]) {
                // Найден дубликат
                free(set->keys);
                free(set->flags);
                free(set);
                return NULL;
            }
            h = (h + 1) % set->capacity;
        }
        
        set->keys[h] = arr[i];
        set->flags[h] = 1;
        set->size++;
    }
    
    return set;
}

int IsInSet(const IntegerSet* set, int value) {
    if (set == NULL || set->size == 0) return 0;
    
    int h = hash(value, set->capacity);
    int start = h;
    
    while (set->flags[h] != 0) {
        if (set->flags[h] == 1 && set->keys[h] == value) {
            return 1;
        }
        h = (h + 1) % set->capacity;
        if (h == start) break;
    }
    
    return 0;
}