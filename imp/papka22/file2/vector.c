#include "vector.h"
#include <stdlib.h>

#define DEFAULT_CAP 4

struct vector_t {
    int* arr;
    size_t len;
    size_t cap;
};

static void expand_if_full(struct vector_t* v, size_t need) {
    if (need <= v->cap) return;
    
    size_t new_cap = v->cap;
    if (new_cap < DEFAULT_CAP) new_cap = DEFAULT_CAP;
    while (new_cap < need) new_cap <<= 1;
    
    int* new_arr = (int*)realloc(v->arr, new_cap * sizeof(int));
    if (new_arr) {
        v->arr = new_arr;
        v->cap = new_cap;
    }
}

vector_t* vector_create(void) {
    struct vector_t* v = (struct vector_t*)malloc(sizeof(struct vector_t));
    if (!v) return NULL;
    v->arr = NULL;
    v->len = 0;
    v->cap = 0;
    return v;
}

void vector_destroy(vector_t* v) {
    if (v) {
        free(v->arr);
        free(v);
    }
}

void vector_push_back(vector_t* v, int val) {
    if (!v) return;
    expand_if_full(v, v->len + 1);
    v->arr[v->len++] = val;
}

void vector_pop_back(vector_t* v) {
    if (v && v->len) v->len--;
}

size_t vector_size(const vector_t* v) {
    return v ? v->len : 0;
}

size_t vector_capacity(const vector_t* v) {
    return v ? v->cap : 0;
}

bool vector_at(const vector_t* v, size_t idx, int* out) {
    if (!v || idx >= v->len) return 0;
    if (out) *out = v->arr[idx];
    return 1;
}

bool vector_front(const vector_t* v, int* out) {
    if (!v || !v->len) return 0;
    if (out) *out = v->arr[0];
    return 1;
}

bool vector_back(const vector_t* v, int* out) {
    if (!v || !v->len) return 0;
    if (out) *out = v->arr[v->len - 1];
    return 1;
}

void vector_resize(vector_t* v, size_t new_len, int fill) {
    if (!v) return;
    if (new_len > v->len) {
        expand_if_full(v, new_len);
        for (size_t i = v->len; i < new_len; ++i)
            v->arr[i] = fill;
    }
    v->len = new_len;
}

void vector_clear(vector_t* v) {
    if (v) v->len = 0;
}

bool vector_empty(const vector_t* v) {
    return v ? v->len == 0 : 1;
}

const int* vector_data(const vector_t* v) {
    return v ? v->arr : NULL;
}

void vector_reserve(vector_t* v, size_t new_cap) {
    if (!v || new_cap <= v->cap) return;
    int* new_arr = (int*)realloc(v->arr, new_cap * sizeof(int));
    if (new_arr) {
        v->arr = new_arr;
        v->cap = new_cap;
    }
}