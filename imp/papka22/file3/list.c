#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct list_node {
    int value;
    list_node_t* prev;
    list_node_t* next;
};

struct list {
    list_node_t* head;
    list_node_t* tail;
    size_t size;
};

list_t* list_create(void) {
    list_t* lst = (list_t*)malloc(sizeof(list_t));
    if (!lst) {
        return NULL;
    }
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
    return lst;
}

void list_destroy(list_t* lst) {
    if (!lst) {
        return;
    }
    list_clear(lst);
    free(lst);
}

bool list_push_back(list_t* lst, int value) {
    if (!lst) {
        return false;
    }
    
    list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
    if (!node) {
        return false;
    }
    
    node->value = value;
    node->next = NULL;
    node->prev = lst->tail;
    
    if (lst->tail) {
        lst->tail->next = node;
    } else {
        lst->head = node;
    }
    lst->tail = node;
    lst->size++;
    
    return true;
}

bool list_push_front(list_t* lst, int value) {
    if (!lst) {
        return false;
    }
    
    list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
    if (!node) {
        return false;
    }
    
    node->value = value;
    node->prev = NULL;
    node->next = lst->head;
    
    if (lst->head) {
        lst->head->prev = node;
    } else {
        lst->tail = node;
    }
    lst->head = node;
    lst->size++;
    
    return true;
}

int list_pop_back(list_t* lst) {
    if (!lst || lst->size == 0) {
        return 0;
    }
    
    list_node_t* node = lst->tail;
    int value = node->value;
    
    lst->tail = node->prev;
    if (lst->tail) {
        lst->tail->next = NULL;
    } else {
        lst->head = NULL;
    }
    
    free(node);
    lst->size--;
    
    return value;
}

int list_pop_front(list_t* lst) {
    if (!lst || lst->size == 0) {
        return 0;
    }
    
    list_node_t* node = lst->head;
    int value = node->value;
    
    lst->head = node->next;
    if (lst->head) {
        lst->head->prev = NULL;
    } else {
        lst->tail = NULL;
    }
    
    free(node);
    lst->size--;
    
    return value;
}

size_t list_size(const list_t* lst) {
    return lst ? lst->size : 0;
}

bool list_empty(const list_t* lst) {
    return lst ? (lst->size == 0) : true;
}

int list_front(const list_t* lst) {
    if (!lst || lst->size == 0) {
        return 0;
    }
    return lst->head->value;
}

int list_back(const list_t* lst) {
    if (!lst || lst->size == 0) {
        return 0;
    }
    return lst->tail->value;
}

void list_clear(list_t* lst) {
    if (!lst) {
        return;
    }
    
    list_node_t* current = lst->head;
    while (current) {
        list_node_t* next = current->next;
        free(current);
        current = next;
    }
    
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
}

void list_print(const list_t* lst) {
    if (!lst || lst->size == 0) {
        printf("[]");
        return;
    }
    
    printf("[");
    list_node_t* current = lst->head;
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