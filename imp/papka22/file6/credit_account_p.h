#ifndef CREDIT_ACCOUNT_P_H
#define CREDIT_ACCOUNT_P_H

#include "bank_account_p.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct credit_account {
    bank_account_t base;
    double credit_limit;
} credit_account_t;

extern const bank_account_vtable_t credit_vtable;

void credit_deposit(bank_account_t* acc, double amount);
int credit_withdraw(bank_account_t* acc, double amount);
double credit_get_balance(bank_account_t* acc);
const char* credit_get_type(bank_account_t* acc);

#ifdef __cplusplus
}
#endif

#endif