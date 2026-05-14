#include "credit_account_p.h"
#include "credit_account.h"
#include <stdlib.h>

void credit_deposit(bank_account_t* acc, double amount) {
    if (!acc || amount <= 0) {
        return;
    }
    acc->balance += amount;
}

int credit_withdraw(bank_account_t* acc, double amount) {
    if (!acc || amount <= 0) {
        return 0;
    }
    
    credit_account_t* credit_acc = (credit_account_t*)acc;
    
    if (credit_acc->credit_limit < 0) {
        return 0;
    }
    
    double min_balance = -credit_acc->credit_limit;
    if (acc->balance - amount < min_balance) {
        return 0;
    }
    
    acc->balance -= amount;
    return 1;
}

double credit_get_balance(bank_account_t* acc) {
    if (!acc) {
        return 0.0;
    }
    return acc->balance;
}

const char* credit_get_type(bank_account_t* acc) {
    (void)acc;
    return "Credit";
}

static const bank_account_vtable_t credit_vtable_static = {
    .deposit = credit_deposit,
    .withdraw = credit_withdraw,
    .get_balance = credit_get_balance,
    .get_type = credit_get_type
};

const bank_account_vtable_t* credit_vtable = &credit_vtable_static;

bank_account_t* create_credit_account(int number, double credit_limit) {
    credit_account_t* acc = (credit_account_t*)malloc(sizeof(credit_account_t));
    if (!acc) {
        return NULL;
    }
    
    acc->base.account_number = number;
    acc->base.balance = 0.0;
    acc->base.vtable = credit_vtable;
    acc->credit_limit = credit_limit;
    
    return (bank_account_t*)acc;
}