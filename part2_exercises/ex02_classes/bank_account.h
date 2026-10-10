// Exercise 2: classes and the .h / .cc split
//
// Concepts: access specifiers, member initializer lists, const methods,
// defining members outside the class with BankAccount::, explicit constructors,
// Google-style naming (class data members end in _).
//
// The declarations below compile, but they are NOT finished:
//   1. Two keywords recommended by the crash course are missing. Hints: which
//      methods don't modify the object? Which constructor would let someone write
//      `BankAccount account = std::string("Ada");` by accident?
//      Fix the declarations here AND the matching definitions in bank_account.cc.
//   2. The class has no data members yet - add the ones you need.
//   3. Implement every method in bank_account.cc. Constructors should use a member
//      initializer list.
//
// Amounts are in cents (whole numbers), so there are no rounding problems.
// Tests: tests/test_ex02_classes.cpp    Run configuration: ex02_classes_test
#pragma once

#include <string>

class BankAccount {
 public:
  // Opens an account for `owner` with a balance of 0.
  BankAccount(std::string owner);

  // Opens an account with an initial balance.
  // Throws std::invalid_argument if initial_cents is negative.
  BankAccount(std::string owner, long initial_cents);

  std::string Owner();
  long Balance();

  // Number of successful deposits plus successful withdrawals. A successful
  // transfer counts as one withdrawal here and one deposit on the other account.
  int TransactionCount();

  // Adds `cents` to the balance. Throws std::invalid_argument if cents <= 0.
  void Deposit(long cents);

  // If the balance is at least `cents`, removes it and returns true. Otherwise
  // returns false and changes nothing. Throws std::invalid_argument if cents <= 0.
  bool Withdraw(long cents);

  // Moves `cents` from this account into `other`. Returns false (and changes
  // nothing on either account) if this account has insufficient funds.
  bool TransferTo(BankAccount& other, long cents);

 private:
  // TODO: data members.
};
