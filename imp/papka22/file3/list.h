#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_node list_node_t;
typedef struct list list_t;

list_t* list_create(void);

void list_destroy(list_t* lst);

bool list_push_back(list_t* lst, int value);

bool list_push_front(list_t* lst, int value);

int list_pop_back(list_t* lst);

int list_pop_front(list_t* lst);

size_t list_size(const list_t* lst);

bool list_empty(const list_t* lst);

int list_front(const list_t* lst);

int list_back(const list_t* lst);

void list_clear(list_t* lst);

void list_print(const list_t* lst);

#ifdef __cplusplus
}
#endif

#endif