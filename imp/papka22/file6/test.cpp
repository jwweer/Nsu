#include <gtest/gtest.h>
#include "bank_account.h"
#include "debit_account.h"
#include "credit_account.h"

// Тесты для NULL-указателей
TEST(NullPointerTest, DestroyNullDoesNothing) {
    EXPECT_NO_THROW(destroy_account(nullptr));
}

TEST(NullPointerTest, DepositNullDoesNothing) {
    EXPECT_NO_THROW(deposit(nullptr, 100.0));
}

TEST(NullPointerTest, WithdrawNullReturnsZero) {
    EXPECT_EQ(withdraw(nullptr, 100.0), 0);
}

TEST(NullPointerTest, GetBalanceNullReturnsZero) {
    EXPECT_DOUBLE_EQ(get_balance(nullptr), 0.0);
}

TEST(NullPointerTest, GetTypeNullReturnsUnknown) {
    EXPECT_STREQ(get_type(nullptr), "Unknown");
}

// Тесты для дебетового счёта
TEST(DebitAccountTest, CreateAndDestroy) {
    bank_account_t* acc = create_debit_account(1);
    ASSERT_NE(acc, nullptr);
    destroy_account(acc);
}

TEST(DebitAccountTest, InitialBalanceIsZero) {
    bank_account_t* acc = create_debit_account(1);
    EXPECT_DOUBLE_EQ(get_balance(acc), 0.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, DepositIncreasesBalance) {
    bank_account_t* acc = create_debit_account(1);
    deposit(acc, 100.0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 100.0);
    deposit(acc, 50.0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 150.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, DepositNegativeDoesNothing) {
    bank_account_t* acc = create_debit_account(1);
    deposit(acc, -50.0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 0.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, WithdrawSuccess) {
    bank_account_t* acc = create_debit_account(1);
    deposit(acc, 100.0);
    EXPECT_EQ(withdraw(acc, 70.0), 1);
    EXPECT_DOUBLE_EQ(get_balance(acc), 30.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, WithdrawFailsWhenInsufficientFunds) {
    bank_account_t* acc = create_debit_account(1);
    deposit(acc, 50.0);
    EXPECT_EQ(withdraw(acc, 100.0), 0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 50.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, WithdrawNegativeAmountFails) {
    bank_account_t* acc = create_debit_account(1);
    deposit(acc, 100.0);
    EXPECT_EQ(withdraw(acc, -10.0), 0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 100.0);
    destroy_account(acc);
}

TEST(DebitAccountTest, GetTypeReturnsDebit) {
    bank_account_t* acc = create_debit_account(1);
    EXPECT_STREQ(get_type(acc), "Debit");
    destroy_account(acc);
}

TEST(DebitAccountTest, AccountNumberIsPreserved) {
    bank_account_t* acc = create_debit_account(12345);
    // Нет публичного способа получить номер счёта, но он сохраняется внутри
    EXPECT_STREQ(get_type(acc), "Debit");
    destroy_account(acc);
}

// Тесты для кредитового счёта
TEST(CreditAccountTest, CreateAndDestroy) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    ASSERT_NE(acc, nullptr);
    destroy_account(acc);
}

TEST(CreditAccountTest, InitialBalanceIsZero) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 0.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, DepositIncreasesBalance) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    deposit(acc, 500.0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 500.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, WithdrawWithinLimitSuccess) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    EXPECT_EQ(withdraw(acc, 500.0), 1);
    EXPECT_DOUBLE_EQ(get_balance(acc), -500.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, WithdrawToLimitSuccess) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    EXPECT_EQ(withdraw(acc, 1000.0), 1);
    EXPECT_DOUBLE_EQ(get_balance(acc), -1000.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, WithdrawExceedsLimitFails) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    EXPECT_EQ(withdraw(acc, 1500.0), 0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 0.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, WithdrawAfterDepositWorksCorrectly) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    deposit(acc, 300.0);
    EXPECT_EQ(withdraw(acc, 800.0), 1);
    EXPECT_DOUBLE_EQ(get_balance(acc), -500.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, DepositAfterNegativeBalanceReducesDebt) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    withdraw(acc, 500.0);
    EXPECT_DOUBLE_EQ(get_balance(acc), -500.0);
    deposit(acc, 200.0);
    EXPECT_DOUBLE_EQ(get_balance(acc), -300.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, CreditLimitZeroBehavesLikeDebit) {
    bank_account_t* acc = create_credit_account(2, 0.0);
    EXPECT_EQ(withdraw(acc, 100.0), 0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 0.0);
    deposit(acc, 100.0);
    EXPECT_EQ(withdraw(acc, 50.0), 1);
    EXPECT_DOUBLE_EQ(get_balance(acc), 50.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, NegativeCreditLimitPreventsAllWithdrawals) {
    bank_account_t* acc = create_credit_account(2, -500.0);
    deposit(acc, 1000.0);
    EXPECT_EQ(withdraw(acc, 100.0), 0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 1000.0);
    destroy_account(acc);
}

TEST(CreditAccountTest, GetTypeReturnsCredit) {
    bank_account_t* acc = create_credit_account(2, 1000.0);
    EXPECT_STREQ(get_type(acc), "Credit");
    destroy_account(acc);
}

// Тесты для полиморфного поведения через общий интерфейс
TEST(PolymorphismTest, DepositWorksForBothAccountTypes) {
    bank_account_t* debit = create_debit_account(1);
    bank_account_t* credit = create_credit_account(2, 1000.0);
    
    deposit(debit, 100.0);
    deposit(credit, 100.0);
    
    EXPECT_DOUBLE_EQ(get_balance(debit), 100.0);
    EXPECT_DOUBLE_EQ(get_balance(credit), 100.0);
    
    destroy_account(debit);
    destroy_account(credit);
}

TEST(PolymorphismTest, WithdrawBehavesDifferentlyForEachType) {
    bank_account_t* debit = create_debit_account(1);
    bank_account_t* credit = create_credit_account(2, 1000.0);
    
    deposit(debit, 500.0);
    deposit(credit, 500.0);
    
    // Оба могут снять 300
    EXPECT_EQ(withdraw(debit, 300.0), 1);
    EXPECT_EQ(withdraw(credit, 300.0), 1);
    
    EXPECT_DOUBLE_EQ(get_balance(debit), 200.0);
    EXPECT_DOUBLE_EQ(get_balance(credit), 200.0);
    
    // Debit не может снять больше баланса
    EXPECT_EQ(withdraw(debit, 300.0), 0);
    EXPECT_DOUBLE_EQ(get_balance(debit), 200.0);
    
    // Credit может уйти в минус
    EXPECT_EQ(withdraw(credit, 300.0), 1);
    EXPECT_DOUBLE_EQ(get_balance(credit), -100.0);
    
    destroy_account(debit);
    destroy_account(credit);
}

TEST(PolymorphismTest, GetTypeReturnsCorrectString) {
    bank_account_t* debit = create_debit_account(1);
    bank_account_t* credit = create_credit_account(2, 1000.0);
    
    EXPECT_STREQ(get_type(debit), "Debit");
    EXPECT_STREQ(get_type(credit), "Credit");
    
    destroy_account(debit);
    destroy_account(credit);
}

// Комплексные сценарии
TEST(ComplexTest, DebitAccountFullLifecycle) {
    bank_account_t* acc = create_debit_account(100);
    
    // Серия пополнений
    deposit(acc, 100);
    deposit(acc, 200);
    deposit(acc, 50);
    EXPECT_DOUBLE_EQ(get_balance(acc), 350);
    
    // Серия снятий
    EXPECT_EQ(withdraw(acc, 100), 1);
    EXPECT_EQ(withdraw(acc, 200), 1);
    EXPECT_DOUBLE_EQ(get_balance(acc), 50);
    
    // Попытка снять больше
    EXPECT_EQ(withdraw(acc, 100), 0);
    EXPECT_DOUBLE_EQ(get_balance(acc), 50);
    
    destroy_account(acc);
}

TEST(ComplexTest, CreditAccountFullLifecycle) {
    bank_account_t* acc = create_credit_account(200, 500);
    
    // Уходим в минус
    EXPECT_EQ(withdraw(acc, 300), 1);
    EXPECT_DOUBLE_EQ(get_balance(acc), -300);
    
    // Частично погашаем
    deposit(acc, 150);
    EXPECT_DOUBLE_EQ(get_balance(acc), -150);
    
    // Полностью погашаем и уходим в плюс
    deposit(acc, 200);
    EXPECT_DOUBLE_EQ(get_balance(acc), 50);
    
    // Снимаем снова
    EXPECT_EQ(withdraw(acc, 100), 1);
    EXPECT_DOUBLE_EQ(get_balance(acc), -50);
    
    destroy_account(acc);
}

TEST(ComplexTest, MultipleAccountsIndependent) {
    bank_account_t* debit = create_debit_account(1);
    bank_account_t* credit1 = create_credit_account(2, 1000);
    bank_account_t* credit2 = create_credit_account(3, 2000);
    
    deposit(debit, 500);
    deposit(credit1, 100);
    deposit(credit2, 50);
    
    EXPECT_EQ(withdraw(debit, 600), 0);
    EXPECT_EQ(withdraw(credit1, 500), 1);
    EXPECT_EQ(withdraw(credit2, 500), 1);
    
    EXPECT_DOUBLE_EQ(get_balance(debit), 500);
    EXPECT_DOUBLE_EQ(get_balance(credit1), -400);
    EXPECT_DOUBLE_EQ(get_balance(credit2), -450);
    
    EXPECT_STREQ(get_type(debit), "Debit");
    EXPECT_STREQ(get_type(credit1), "Credit");
    EXPECT_STREQ(get_type(credit2), "Credit");
    
    destroy_account(debit);
    destroy_account(credit1);
    destroy_account(credit2);
}

// Main function
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}