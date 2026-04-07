#ifndef ARRAY_DEF_H
#define ARRAY_DEF_H

#include <string.h>

static const int INITIAL_CAPACITY = 8;

void NAME##_init(NAME *vec) {
    vec->n = 0;
    vec->capacity = 0;
    vec->arr = NULL;
}

void NAME##_destroy(NAME *vec) {
    if (vec->arr) {
        free(vec->arr);
        vec->arr = NULL;
    }
    vec->n = 0;
    vec->capacity = 0;
}

void NAME##_reserve(NAME *vec, int capacity) {
    if (capacity > vec->capacity) {
        vec->capacity = capacity;
        vec->arr = (TYPE*)realloc(vec->arr, vec->capacity * sizeof(TYPE));
    }
}

int NAME##_push(NAME *vec, TYPE value) {
    if (vec->n >= vec->capacity) {
        int new_cap = vec->capacity == 0 ? INITIAL_CAPACITY : vec->capacity * 2;
        NAME##_reserve(vec, new_cap);
    }
    vec->arr[vec->n] = value;
    return vec->n++;
}

TYPE NAME##_pop(NAME *vec) {
    if (vec->n > 0) {
        return vec->arr[--vec->n];
    }
    return (TYPE)0;
}

void NAME##_resize(NAME *vec, int newCnt, TYPE fill) {
    if (newCnt > vec->n) {
        NAME##_reserve(vec, newCnt);
        for (int i = vec->n; i < newCnt; i++) {
            vec->arr[i] = fill;
        }
    }
    vec->n = newCnt;
}

void NAME##_insert(NAME *vec, int where, TYPE *arr, int num) {
    if (num == 0) return;
    
    int new_size = vec->n + num;
    NAME##_reserve(vec, new_size);
    
    // Сдвигаем элементы вправо
    memmove(vec->arr + where + num, vec->arr + where, (vec->n - where) * sizeof(TYPE));
    
    // Копируем новые элементы
    memcpy(vec->arr + where, arr, num * sizeof(TYPE));
    
    vec->n = new_size;
}

void NAME##_erase(NAME *vec, int where, int num) {
    if (num == 0) return;
    
    int new_size = vec->n - num;
    memmove(vec->arr + where, vec->arr + where + num, (vec->n - where - num) * sizeof(TYPE));
    vec->n = new_size;
}

#endif