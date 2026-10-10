// Tests for Exercise 2. Don't edit - make them pass by editing bank_account.h/.cc.
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <type_traits>

#include "bank_account.h"

namespace {

// True if Owner(), Balance() and TransactionCount() can be called on a const T.
template <typename T>
constexpr bool kGettersAreConst = requires(const T& account) {
  account.Owner();
  account.Balance();
  account.TransactionCount();
};

}  // namespace

TEST(Ex02_Classes, NewAccountHasZeroBalance) {
  BankAccount account(std::string("Ada"));
  EXPECT_EQ(account.Owner(), "Ada");
  EXPECT_EQ(account.Balance(), 0);
  EXPECT_EQ(account.TransactionCount(), 0);
}

TEST(Ex02_Classes, InitialBalance) {
  BankAccount account("Grace", 1500);
  EXPECT_EQ(account.Owner(), "Grace");
  EXPECT_EQ(account.Balance(), 1500);
  EXPECT_EQ(account.TransactionCount(), 0) << "Opening an account is not a transaction";
}

TEST(Ex02_Classes, NegativeInitialBalanceThrows) {
  EXPECT_THROW({ BankAccount account("Eve", -1); }, std::invalid_argument);
}

TEST(Ex02_Classes, DepositIncreasesBalance) {
  BankAccount account("Ada", 100);
  account.Deposit(250);
  account.Deposit(1);
  EXPECT_EQ(account.Balance(), 351);
  EXPECT_EQ(account.TransactionCount(), 2);
}

TEST(Ex02_Classes, NonPositiveDepositThrows) {
  BankAccount account("Ada", 100);
  EXPECT_THROW(account.Deposit(0), std::invalid_argument);
  EXPECT_THROW(account.Deposit(-5), std::invalid_argument);
  EXPECT_EQ(account.Balance(), 100);
  EXPECT_EQ(account.TransactionCount(), 0);
}

TEST(Ex02_Classes, WithdrawWithSufficientFunds) {
  BankAccount account("Ada", 100);
  EXPECT_TRUE(account.Withdraw(100));
  EXPECT_EQ(account.Balance(), 0);
  EXPECT_EQ(account.TransactionCount(), 1);
}

TEST(Ex02_Classes, WithdrawWithInsufficientFundsChangesNothing) {
  BankAccount account("Ada", 100);
  EXPECT_FALSE(account.Withdraw(101));
  EXPECT_EQ(account.Balance(), 100);
  EXPECT_EQ(account.TransactionCount(), 0) << "A failed withdrawal is not a transaction";
}

TEST(Ex02_Classes, NonPositiveWithdrawalThrows) {
  BankAccount account("Ada", 100);
  EXPECT_THROW(account.Withdraw(0), std::invalid_argument);
}

TEST(Ex02_Classes, TransferMovesMoney) {
  BankAccount from("Ada", 500);
  BankAccount to("Grace", 10);
  EXPECT_TRUE(from.TransferTo(to, 200));
  EXPECT_EQ(from.Balance(), 300);
  EXPECT_EQ(to.Balance(), 210) << "TransferTo must modify `other` - is it passed by reference?";
  EXPECT_EQ(from.TransactionCount(), 1);
  EXPECT_EQ(to.TransactionCount(), 1);
}

TEST(Ex02_Classes, FailedTransferChangesNothing) {
  BankAccount from("Ada", 50);
  BankAccount to("Grace", 10);
  EXPECT_FALSE(from.TransferTo(to, 51));
  EXPECT_EQ(from.Balance(), 50);
  EXPECT_EQ(to.Balance(), 10);
  EXPECT_EQ(from.TransactionCount(), 0);
  EXPECT_EQ(to.TransactionCount(), 0);
}

TEST(Ex02_Design, GettersAreConstMethods) {
  EXPECT_TRUE(kGettersAreConst<BankAccount>)
      << "Owner(), Balance() and TransactionCount() don't modify the account, so they "
         "should be const methods - otherwise they can't be called on a const "
         "BankAccount& (e.g. a parameter passed by const reference).";
}

TEST(Ex02_Design, SingleArgumentConstructorIsExplicit) {
  EXPECT_TRUE((std::is_constructible_v<BankAccount, std::string>));
  EXPECT_FALSE((std::is_convertible_v<std::string, BankAccount>))
      << "BankAccount(std::string) allows `BankAccount a = std::string(\"Ada\");` and "
         "silent conversions when calling functions. Mark single-argument constructors "
         "explicit.";
}
