#ifndef DEBIT_ACCOUNT_P_H
#define DEBIT_ACCOUNT_P_H

#include "bank_account_p.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const bank_account_vtable_t debit_vtable;

void debit_deposit(bank_account_t* acc, double amount);
int debit_withdraw(bank_account_t* acc, double amount);
double debit_get_balance(bank_account_t* acc);
const char* debit_get_type(bank_account_t* acc);

#ifdef __cplusplus
}
#endif

#endif