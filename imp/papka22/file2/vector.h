#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vector vector_t;

vector_t* vector_create(size_t capacity);

void vector_destroy(vector_t* vec);

bool vector_push_back(vector_t* vec, int value);

bool vector_pop_back(vector_t* vec);

int* vector_at(vector_t* vec, size_t index);

int vector_front(vector_t* vec);

int vector_back(vector_t* vec);

size_t vector_size(const vector_t* vec);

size_t vector_capacity(const vector_t* vec);

void vector_resize(vector_t* vec, size_t new_size, int default_value);

void vector_clear(vector_t* vec);

bool vector_empty(const vector_t* vec);

void vector_print(const vector_t* vec);

#ifdef __cplusplus
}
#endif

#endif