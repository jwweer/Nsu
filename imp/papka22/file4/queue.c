#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct queue_node {
    int value;
    struct queue_node* next;
} queue_node_t;

struct queue {
    queue_node_t* front;
    queue_node_t* rear;
    size_t size;
};

queue_t* queue_create(void) {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void queue_destroy(queue_t* q) {
    if (!q) {
        return;
    }
    queue_clear(q);
    free(q);
}

bool queue_push(queue_t* q, int value) {
    if (!q) {
        return false;
    }
    
    queue_node_t* node = (queue_node_t*)malloc(sizeof(queue_node_t));
    if (!node) {
        return false;
    }
    
    node->value = value;
    node->next = NULL;
    
    if (q->rear) {
        q->rear->next = node;
    } else {
        q->front = node;
    }
    q->rear = node;
    q->size++;
    
    return true;
}

int queue_pop(queue_t* q) {
    if (!q || q->size == 0) {
        return 0;
    }
    
    queue_node_t* node = q->front;
    int value = node->value;
    
    q->front = node->next;
    if (!q->front) {
        q->rear = NULL;
    }
    
    free(node);
    q->size--;
    
    return value;
}

int queue_peek(const queue_t* q) {
    if (!q || q->size == 0) {
        return 0;
    }
    return q->front->value;
}

size_t queue_size(const queue_t* q) {
    return q ? q->size : 0;
}

bool queue_empty(const queue_t* q) {
    return q ? (q->size == 0) : true;
}

void queue_clear(queue_t* q) {
    if (!q) {
        return;
    }
    
    queue_node_t* current = q->front;
    while (current) {
        queue_node_t* next = current->next;
        free(current);
        current = next;
    }
    
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

void queue_print(const queue_t* q) {
    if (!q || q->size == 0) {
        printf("[]");
        return;
    }
    
    printf("[");
    queue_node_t* current = q->front;
    size_t index = 0;
    while (current) {
        if (index > 0) {
            printf(", ");
        }
        printf("%d", current->value);
        current = current->next;
        index++;
    }
    printf("]");
}