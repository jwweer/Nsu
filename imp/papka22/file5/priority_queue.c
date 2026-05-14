#include "priority_queue.h"
#include <stdlib.h>
#include <string.h>

struct priority_queue {
    pq_item_t *heap;
    size_t capacity;
    size_t size;
    bool unlimited;
};

static void swap(pq_item_t *a, pq_item_t *b) {
    pq_item_t temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(priority_queue_t *queue, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (queue->heap[parent].priority >= queue->heap[index].priority) {
            break;
        }
        swap(&queue->heap[parent], &queue->heap[index]);
        index = parent;
    }
}

static void heapify_down(priority_queue_t *queue, size_t index) {
    size_t left, right, largest;
    
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;
        
        if (left < queue->size && queue->heap[left].priority > queue->heap[largest].priority) {
            largest = left;
        }
        if (right < queue->size && queue->heap[right].priority > queue->heap[largest].priority) {
            largest = right;
        }
        
        if (largest == index) {
            break;
        }
        
        swap(&queue->heap[index], &queue->heap[largest]);
        index = largest;
    }
}

priority_queue_t *pq_create(size_t capacity) {
    priority_queue_t *queue = (priority_queue_t *)malloc(sizeof(priority_queue_t));
    if (!queue) {
        return NULL;
    }
    
    queue->unlimited = (capacity == 0);
    queue->capacity = queue->unlimited ? 16 : capacity;
    queue->size = 0;
    
    queue->heap = (pq_item_t *)malloc(sizeof(pq_item_t) * queue->capacity);
    if (!queue->heap) {
        free(queue);
        return NULL;
    }
    
    return queue;
}

void pq_destroy(priority_queue_t *queue, pq_free_func free_func) {
    if (!queue) {
        return;
    }
    
    pq_clear(queue, free_func);
    free(queue->heap);
    free(queue);
}

static bool ensure_capacity(priority_queue_t *queue) {
    if (!queue->unlimited || queue->size < queue->capacity) {
        return true;
    }
    
    size_t new_capacity = queue->capacity * 2;
    pq_item_t *new_heap = (pq_item_t *)realloc(queue->heap, sizeof(pq_item_t) * new_capacity);
    if (!new_heap) {
        return false;
    }
    
    queue->heap = new_heap;
    queue->capacity = new_capacity;
    return true;
}

bool pq_push(priority_queue_t *queue, void *data, int priority) {
    if (!queue) {
        return false;
    }
    
    if (!queue->unlimited && queue->size >= queue->capacity) {
        return false;
    }
    
    if (!ensure_capacity(queue)) {
        return false;
    }
    
    queue->heap[queue->size].data = data;
    queue->heap[queue->size].priority = priority;
    queue->size++;
    
    heapify_up(queue, queue->size - 1);
    
    return true;
}

bool pq_pop(priority_queue_t *queue, void **data, int *priority) {
    if (!queue || queue->size == 0) {
        return false;
    }
    
    if (data) {
        *data = queue->heap[0].data;
    }
    if (priority) {
        *priority = queue->heap[0].priority;
    }
    
    queue->size--;
    if (queue->size > 0) {
        queue->heap[0] = queue->heap[queue->size];
        heapify_down(queue, 0);
    }
    
    return true;
}

bool pq_peek(priority_queue_t *queue, void **data, int *priority) {
    if (!queue || queue->size == 0) {
        return false;
    }
    
    if (data) {
        *data = queue->heap[0].data;
    }
    if (priority) {
        *priority = queue->heap[0].priority;
    }
    
    return true;
}

size_t pq_size(const priority_queue_t *queue) {
    return queue ? queue->size : 0;
}

bool pq_is_empty(const priority_queue_t *queue) {
    return queue ? (queue->size == 0) : true;
}

bool pq_is_full(const priority_queue_t *queue) {
    if (!queue || queue->unlimited) {
        return false;
    }
    return queue->size >= queue->capacity;
}

void pq_clear(priority_queue_t *queue, pq_free_func free_func) {
    if (!queue) {
        return;
    }
    
    if (free_func) {
        for (size_t i = 0; i < queue->size; i++) {
            free_func(queue->heap[i].data);
        }
    }
    
    queue->size = 0;
}