#include "bank_account_p.h"
#include <stdlib.h>

void deposit(bank_account_t* acc, double amount) {
    if (!acc || !acc->vtable || !acc->vtable->deposit) {
        return;
    }
    acc->vtable->deposit(acc, amount);
}

int withdraw(bank_account_t* acc, double amount) {
    if (!acc || !acc->vtable || !acc->vtable->withdraw) {
        return 0;
    }
    return acc->vtable->withdraw(acc, amount);
}

double get_balance(bank_account_t* acc) {
    if (!acc || !acc->vtable || !acc->vtable->get_balance) {
        return 0.0;
    }
    return acc->vtable->get_balance(acc);
}

const char* get_type(bank_account_t* acc) {
    if (!acc || !acc->vtable || !acc->vtable->get_type) {
        return "Unknown";
    }
    return acc->vtable->get_type(acc);
}

void destroy_account(bank_account_t* acc) {
    if (!acc) {
        return;
    }
    free(acc);
}

bank_account_t* bank_account_base_create(int number, const bank_account_vtable_t* vtable) {
    bank_account_t* acc = (bank_account_t*)malloc(sizeof(bank_account_t));
    if (!acc) {
        return NULL;
    }
    acc->account_number = number;
    acc->balance = 0.0;
    acc->vtable = vtable;
    return acc;
}

void bank_account_base_destroy(bank_account_t* acc) {
    free(acc);
}