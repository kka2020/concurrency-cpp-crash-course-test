#include "bank_account.h"

#include <stdexcept>

BankAccount::BankAccount(std::string owner)
    : owner_(owner), balance_cents_(0), transaction_count_(0) { }

BankAccount::BankAccount(std::string owner, long initial_cents)
    : owner_(owner), balance_cents_(initial_cents), transaction_count_(0) {
  if (initial_cents < 0) {
    throw std::invalid_argument("initial balance cannot be negative");
  }
}

const std::string& BankAccount::Owner() const {
  return owner_;
}

long BankAccount::Balance() const {
  return balance_cents_;
}

int BankAccount::TransactionCount() const {
  return transaction_count_;
}

void BankAccount::Deposit(long cents) {
  if (cents <= 0) {
    throw std::invalid_argument("deposit must be positive");
  }
  balance_cents_ += cents;
  transaction_count_++;
}

bool BankAccount::Withdraw(long cents) {
  if (cents <= 0) {
    throw std::invalid_argument("withdrawal must be positive");
  }
  if (balance_cents_ < cents) {
    return false;
  }
  balance_cents_ -= cents;
  transaction_count_++;
  return true;
}

bool BankAccount::TransferTo(BankAccount& other, long cents) {
  if (!Withdraw(cents)) {
    return false;
  }
  other.Deposit(cents);
  return true;
}
