#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

#define HASHMAP_EXPORTS
#include "hashmap.h"

static int find_index(const HashMap *self, cpvoid key, int *found) {
    if (self->capacity == 0) return -1;
    
    uint32_t h = self->hash(key);
    int idx = h % self->capacity;
    *found = 0;
    
    for (int i = 0; i < self->capacity; i++) {
        int probe = (idx + i) % self->capacity;
        if (self->keys[probe] == NULL) {
            return probe;
        }
        if (self->eq(self->keys[probe], key)) {
            *found = 1;
            return probe;
        }
    }
    return -1;
}

HashMap HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap hm;
    hm.capacity = size;
    hm.size = 0;
    hm.eq = ef;
    hm.hash = hf;
    hm.keys = (cpvoid*)calloc(size, sizeof(cpvoid));
    hm.values = (cpvoid*)calloc(size, sizeof(cpvoid));
    return hm;
}

void HM_Destroy(HashMap *self) {
    if (self->keys) free((void*)self->keys);
    if (self->values) free((void*)self->values);
    self->keys = NULL;
    self->values = NULL;
    self->capacity = 0;
    self->size = 0;
}

cpvoid HM_Get(const HashMap *self, cpvoid key) {
    int found;
    int idx = find_index(self, key, &found);
    if (found && idx >= 0) {
        return self->values[idx];
    }
    return NULL;
}

void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    int found;
    int idx = find_index(self, key, &found);
    if (idx >= 0) {
        if (!found) {
            self->keys[idx] = key;
            self->size++;
        }
        self->values[idx] = value;
    }
}