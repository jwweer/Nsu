#include "debit_account_p.h"
#include "debit_account.h"
#include <stdlib.h>

void debit_deposit(bank_account_t* acc, double amount) {
    if (!acc || amount <= 0) {
        return;
    }
    acc->balance += amount;
}

int debit_withdraw(bank_account_t* acc, double amount) {
    if (!acc || amount <= 0) {
        return 0;
    }
    if (acc->balance < amount) {
        return 0;
    }
    acc->balance -= amount;
    return 1;
}

double debit_get_balance(bank_account_t* acc) {
    if (!acc) {
        return 0.0;
    }
    return acc->balance;
}

const char* debit_get_type(bank_account_t* acc) {
    (void)acc;
    return "Debit";
}

static const bank_account_vtable_t debit_vtable_static = {
    .deposit = debit_deposit,
    .withdraw = debit_withdraw,
    .get_balance = debit_get_balance,
    .get_type = debit_get_type
};

const bank_account_vtable_t* debit_vtable = &debit_vtable_static;

bank_account_t* create_debit_account(int number) {
    return bank_account_base_create(number, debit_vtable);
}