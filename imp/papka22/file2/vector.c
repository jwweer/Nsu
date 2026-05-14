#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct vector {
    int* data;
    size_t size;
    size_t capacity;
};

#define VECTOR_INIT_CAPACITY 4

vector_t* vector_create(size_t capacity) {
    if (capacity == 0) {
        capacity = VECTOR_INIT_CAPACITY;
    }
    
    vector_t* vec = (vector_t*)malloc(sizeof(vector_t));
    if (!vec) {
        return NULL;
    }
    
    vec->data = (int*)malloc(sizeof(int) * capacity);
    if (!vec->data) {
        free(vec);
        return NULL;
    }
    
    vec->size = 0;
    vec->capacity = capacity;
    return vec;
}

void vector_destroy(vector_t* vec) {
    if (!vec) {
        return;
    }
    if (vec->data) {
        free(vec->data);
    }
    free(vec);
}

static bool vector_ensure_capacity(vector_t* vec, size_t needed) {
    if (vec->capacity >= needed) {
        return true;
    }
    
    size_t new_capacity = vec->capacity * 2;
    if (new_capacity < needed) {
        new_capacity = needed;
    }
    
    int* new_data = (int*)realloc(vec->data, sizeof(int) * new_capacity);
    if (!new_data) {
        return false;
    }
    
    vec->data = new_data;
    vec->capacity = new_capacity;
    return true;
}

bool vector_push_back(vector_t* vec, int value) {
    if (!vec) {
        return false;
    }
    
    if (!vector_ensure_capacity(vec, vec->size + 1)) {
        return false;
    }
    
    vec->data[vec->size++] = value;
    return true;
}

bool vector_pop_back(vector_t* vec) {
    if (!vec || vec->size == 0) {
        return false;
    }
    
    vec->size--;
    return true;
}

int* vector_at(vector_t* vec, size_t index) {
    if (!vec || index >= vec->size) {
        return NULL;
    }
    return &vec->data[index];
}

int vector_front(vector_t* vec) {
    if (!vec || vec->size == 0) {
        return 0;
    }
    return vec->data[0];
}

int vector_back(vector_t* vec) {
    if (!vec || vec->size == 0) {
        return 0;
    }
    return vec->data[vec->size - 1];
}

size_t vector_size(const vector_t* vec) {
    return vec ? vec->size : 0;
}

size_t vector_capacity(const vector_t* vec) {
    return vec ? vec->capacity : 0;
}

void vector_resize(vector_t* vec, size_t new_size, int default_value) {
    if (!vec) {
        return;
    }
    
    if (new_size > vec->size) {
        if (!vector_ensure_capacity(vec, new_size)) {
            return;
        }
        for (size_t i = vec->size; i < new_size; i++) {
            vec->data[i] = default_value;
        }
    }
    
    vec->size = new_size;
}

void vector_clear(vector_t* vec) {
    if (!vec) {
        return;
    }
    vec->size = 0;
}

bool vector_empty(const vector_t* vec) {
    return vec ? (vec->size == 0) : true;
}

void vector_print(const vector_t* vec) {
    if (!vec || vec->size == 0) {
        printf("[]");
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < vec->size; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", vec->data[i]);
    }
    printf("]");
}