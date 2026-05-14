#ifndef BANK_ACCOUNT_P_H
#define BANK_ACCOUNT_P_H

#include "bank_account.h"

#ifdef __cplusplus
extern "C" {
#endif

bank_account_t* bank_account_base_create(int number, const bank_account_vtable_t* vtable);

void bank_account_base_destroy(bank_account_t* acc);

#ifdef __cplusplus
}
#endif

#endif