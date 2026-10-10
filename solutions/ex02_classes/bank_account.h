// Exercise 2 - model solution.
#pragma once

#include <string>

class BankAccount {
 public:
  // explicit: a std::string must not silently turn into a BankAccount.
  explicit BankAccount(std::string owner);
  BankAccount(std::string owner, long initial_cents);

  // Getters don't modify the object, so they are const - this makes them
  // callable on const objects and const references.
  const std::string& Owner() const;
  long Balance() const;
  int TransactionCount() const;

  void Deposit(long cents);
  bool Withdraw(long cents);
  bool TransferTo(BankAccount& other, long cents);

 private:
  std::string owner_;
  long balance_cents_;
  int transaction_count_;
};
