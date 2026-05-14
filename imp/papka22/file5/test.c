#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "priority_queue.h"
#include <stdlib.h>

static int *make_test_data(int value) {
    int *data = (int *)malloc(sizeof(int));
    *data = value;
    return data;
}

static void test_create_destroy(void **state) {
    priority_queue_t *pq = pq_create(10);
    assert_non_null(pq);
    assert_int_equal(pq_size(pq), 0);
    assert_true(pq_is_empty(pq));
    assert_false(pq_is_full(pq));
    pq_destroy(pq, NULL);
}

static void test_create_unlimited(void **state) {
    priority_queue_t *pq = pq_create(0);
    assert_non_null(pq);
    assert_int_equal(pq_size(pq), 0);
    pq_destroy(pq, NULL);
}

static void test_create_capacity_one(void **state) {
    priority_queue_t *pq = pq_create(1);
    assert_non_null(pq);
    
    int *data = make_test_data(42);
    assert_true(pq_push(pq, data, 10));
    assert_true(pq_is_full(pq));
    assert_false(pq_push(pq, NULL, 20));
    
    pq_destroy(pq, free);
}

static void test_push(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *d1 = make_test_data(1);
    int *d2 = make_test_data(2);
    int *d3 = make_test_data(3);
    
    assert_true(pq_push(pq, d1, 5));
    assert_true(pq_push(pq, d2, 10));
    assert_true(pq_push(pq, d3, 1));
    
    assert_int_equal(pq_size(pq), 3);
    
    pq_destroy(pq, free);
}

static void test_push_priority(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *d1 = make_test_data(1);
    int *d2 = make_test_data(2);
    int *d3 = make_test_data(3);
    
    pq_push(pq, d1, 5);
    pq_push(pq, d2, 15);
    pq_push(pq, d3, 10);
    
    void *data;
    int priority;
    
    assert_true(pq_pop(pq, &data, &priority));
    assert_int_equal(priority, 15);
    assert_int_equal(*(int *)data, 2);
    free(data);
    
    assert_true(pq_pop(pq, &data, &priority));
    assert_int_equal(priority, 10);
    assert_int_equal(*(int *)data, 3);
    free(data);
    
    assert_true(pq_pop(pq, &data, &priority));
    assert_int_equal(priority, 5);
    assert_int_equal(*(int *)data, 1);
    free(data);
    
    pq_destroy(pq, NULL);
}

// Тест: peek
static void test_peek(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *d1 = make_test_data(100);
    pq_push(pq, d1, 42);
    
    void *data;
    int priority;
    
    assert_true(pq_peek(pq, &data, &priority));
    assert_int_equal(priority, 42);
    assert_int_equal(*(int *)data, 100);
    assert_int_equal(pq_size(pq), 1);
    
    pq_pop(pq, NULL, NULL);
    assert_false(pq_peek(pq, &data, &priority));
    
    pq_destroy(pq, free);
}

// Тест: переполнение
static void test_overflow(void **state) {
    priority_queue_t *pq = pq_create(2);
    
    int *d1 = make_test_data(1);
    int *d2 = make_test_data(2);
    int *d3 = make_test_data(3);
    
    assert_true(pq_push(pq, d1, 1));
    assert_true(pq_push(pq, d2, 2));
    assert_false(pq_push(pq, d3, 3));
    
    pq_destroy(pq, free);
}

static void test_clear(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    for (int i = 0; i < 5; i++) {
        int *data = make_test_data(i);
        pq_push(pq, data, i);
    }
    
    assert_int_equal(pq_size(pq), 5);
    pq_clear(pq, free);
    assert_int_equal(pq_size(pq), 0);
    assert_true(pq_is_empty(pq));
    
    pq_destroy(pq, NULL);
}

static void test_empty_operations(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    void *data;
    int priority;
    
    assert_false(pq_pop(pq, &data, &priority));
    assert_false(pq_peek(pq, &data, &priority));
    assert_true(pq_is_empty(pq));
    assert_int_equal(pq_size(pq), 0);
    
    pq_destroy(pq, NULL);
}

static void test_equal_priorities(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *d1 = make_test_data(1);
    int *d2 = make_test_data(2);
    int *d3 = make_test_data(3);
    
    pq_push(pq, d1, 10);
    pq_push(pq, d2, 10);
    pq_push(pq, d3, 10);
    
    assert_int_equal(pq_size(pq), 3);
    
    void *data;
    for (int i = 0; i < 3; i++) {
        assert_true(pq_pop(pq, &data, NULL));
        free(data);
    }
    
    pq_destroy(pq, NULL);
}

static void test_unlimited_queue(void **state) {
    priority_queue_t *pq = pq_create(0);
    
    for (int i = 0; i < 100; i++) {
        int *data = make_test_data(i);
        assert_true(pq_push(pq, data, i));
    }
    
    assert_int_equal(pq_size(pq), 100);
    
    pq_destroy(pq, free);
}

static void test_null_queue(void **state) {
    void *data = NULL;
    int priority;
    
    assert_false(pq_push(NULL, NULL, 0));
    assert_false(pq_pop(NULL, &data, &priority));
    assert_false(pq_peek(NULL, &data, &priority));
    assert_int_equal(pq_size(NULL), 0);
    assert_true(pq_is_empty(NULL));
    assert_false(pq_is_full(NULL));
    pq_clear(NULL, NULL);
    pq_destroy(NULL, NULL);
}

static void test_clear_no_free(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *d1 = make_test_data(1);
    int *d2 = make_test_data(2);
    pq_push(pq, d1, 1);
    pq_push(pq, d2, 2);
    
    pq_clear(pq, NULL);
    assert_int_equal(pq_size(pq), 0);
    
    free(d1);
    free(d2);
    pq_destroy(pq, NULL);
}

static void test_pop_peek_null_params(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(42);
    pq_push(pq, data, 100);
    
    assert_true(pq_pop(pq, NULL, NULL));
    assert_true(pq_is_empty(pq));
    
    int *data2 = make_test_data(43);
    pq_push(pq, data2, 200);
    
    int priority;
    assert_true(pq_peek(pq, NULL, &priority));
    assert_int_equal(priority, 200);
    
    void *data_ptr;
    assert_true(pq_peek(pq, &data_ptr, NULL));
    assert_int_equal(*(int *)data_ptr, 43);
    
    pq_destroy(pq, free);
}

static void test_pop_only_data(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(99);
    pq_push(pq, data, 50);
    
    void *out_data;
    assert_true(pq_pop(pq, &out_data, NULL));
    assert_int_equal(*(int *)out_data, 99);
    free(out_data);
    
    pq_destroy(pq, NULL);
}

static void test_pop_only_priority(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(88);
    pq_push(pq, data, 77);
    
    int priority;
    assert_true(pq_pop(pq, NULL, &priority));
    assert_int_equal(priority, 77);
    free(data);
    
    pq_destroy(pq, NULL);
}

static void test_peek_only_data(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(66);
    pq_push(pq, data, 55);
    
    void *out_data;
    assert_true(pq_peek(pq, &out_data, NULL));
    assert_int_equal(*(int *)out_data, 66);
    
    pq_destroy(pq, free);
}

static void test_peek_only_priority(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(44);
    pq_push(pq, data, 33);
    
    int priority;
    assert_true(pq_peek(pq, NULL, &priority));
    assert_int_equal(priority, 33);
    
    pq_destroy(pq, free);
}

static void test_heapify_up_single_element(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(1);
    assert_true(pq_push(pq, data, 5));
    assert_int_equal(pq_size(pq), 1);
    
    pq_destroy(pq, free);
}

static void test_heapify_down_single_element(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(1);
    pq_push(pq, data, 5);
    
    void *out_data;
    assert_true(pq_pop(pq, &out_data, NULL));
    free(out_data);
    assert_true(pq_is_empty(pq));
    
    pq_destroy(pq, NULL);
}

static void test_destroy_no_free(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(1);
    pq_push(pq, data, 1);
    
    pq_destroy(pq, NULL);
    free(data);
}

static void test_destroy_frees_queue(void **state) {
    priority_queue_t *pq = pq_create(5);
    assert_non_null(pq);
    pq_destroy(pq, NULL);
}

static void test_clear_resets_capacity(void **state) {
    priority_queue_t *pq = pq_create(20);
    
    for (int i = 0; i < 10; i++) {
        int *data = make_test_data(i);
        pq_push(pq, data, i);
    }
    
    assert_int_equal(pq_size(pq), 10);
    pq_clear(pq, free);
    assert_int_equal(pq_size(pq), 0);
    
    pq_destroy(pq, NULL);
}

static void test_pop_clears_last_element(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    int *data = make_test_data(123);
    pq_push(pq, data, 1);
    pq_push(pq, make_test_data(456), 2);
    
    void *out_data;
    pq_pop(pq, &out_data, NULL);
    free(out_data);
    pq_pop(pq, &out_data, NULL);
    free(out_data);
    
    assert_int_equal(pq_size(pq), 0);
    pq_destroy(pq, NULL);
}

static void test_heap_stability_up(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    for (int i = 0; i < 20; i++) {
        int *data = make_test_data(i);
        pq_push(pq, data, i % 10);
    }
    
    assert_int_equal(pq_size(pq), 20);
    pq_destroy(pq, free);
}

static void test_heap_stability_down(void **state) {
    priority_queue_t *pq = pq_create(10);
    
    for (int i = 0; i < 15; i++) {
        int *data = make_test_data(i);
        pq_push(pq, data, i);
    }
    
    for (int i = 0; i < 5; i++) {
        void *data;
        pq_pop(pq, &data, NULL);
        free(data);
    }
    
    pq_destroy(pq, free);
}

static void test_unlimited_queue_realloc(void **state) {
    priority_queue_t *pq = pq_create(0);
    
    for (int i = 0; i < 1000; i++) {
        int *data = make_test_data(i);
        assert_true(pq_push(pq, data, i));
    }
    
    assert_int_equal(pq_size(pq), 1000);
    pq_destroy(pq, free);
}

static void test_push_checks_overflow(void **state) {
    priority_queue_t *pq = pq_create(3);
    
    for (int i = 0; i < 3; i++) {
        int *data = make_test_data(i);
        assert_true(pq_push(pq, data, i));
    }
    
    int *extra = make_test_data(999);
    assert_false(pq_push(pq, extra, 999));
    free(extra);
    
    pq_destroy(pq, free);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_destroy),
        cmocka_unit_test(test_create_unlimited),
        cmocka_unit_test(test_create_capacity_one),
        cmocka_unit_test(test_push),
        cmocka_unit_test(test_push_priority),
        cmocka_unit_test(test_peek),
        cmocka_unit_test(test_overflow),
        cmocka_unit_test(test_clear),
        cmocka_unit_test(test_empty_operations),
        cmocka_unit_test(test_equal_priorities),
        cmocka_unit_test(test_unlimited_queue),
        cmocka_unit_test(test_null_queue),
        cmocka_unit_test(test_clear_no_free),
        cmocka_unit_test(test_pop_peek_null_params),
        cmocka_unit_test(test_pop_only_data),
        cmocka_unit_test(test_pop_only_priority),
        cmocka_unit_test(test_peek_only_data),
        cmocka_unit_test(test_peek_only_priority),
        cmocka_unit_test(test_heapify_up_single_element),
        cmocka_unit_test(test_heapify_down_single_element),
        cmocka_unit_test(test_destroy_no_free),
        cmocka_unit_test(test_destroy_frees_queue),
        cmocka_unit_test(test_clear_resets_capacity),
        cmocka_unit_test(test_pop_clears_last_element),
        cmocka_unit_test(test_heap_stability_up),
        cmocka_unit_test(test_heap_stability_down),
        cmocka_unit_test(test_unlimited_queue_realloc),
        cmocka_unit_test(test_push_checks_overflow),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}