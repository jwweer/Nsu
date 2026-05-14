#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct queue queue_t;

queue_t* queue_create(void);

void queue_destroy(queue_t* q);

bool queue_push(queue_t* q, int value);

int queue_pop(queue_t* q);

int queue_peek(const queue_t* q);

size_t queue_size(const queue_t* q);

bool queue_empty(const queue_t* q);

void queue_clear(queue_t* q);

void queue_print(const queue_t* q);

#ifdef __cplusplus
}
#endif

#endif