#include "bank_account.h"

#include <stdexcept>

// TODO: implement every member function. Remember that if you change a
// declaration in bank_account.h, the definition here must match it exactly.

BankAccount::BankAccount(std::string owner) {
  throw std::logic_error("TODO: implement BankAccount(owner)");
}

BankAccount::BankAccount(std::string owner, long initial_cents) {
  throw std::logic_error("TODO: implement BankAccount(owner, initial_cents)");
}

std::string BankAccount::Owner() {
  throw std::logic_error("TODO: implement Owner");
}

long BankAccount::Balance() {
  throw std::logic_error("TODO: implement Balance");
}

int BankAccount::TransactionCount() {
  throw std::logic_error("TODO: implement TransactionCount");
}

void BankAccount::Deposit(long cents) {
  throw std::logic_error("TODO: implement Deposit");
}

bool BankAccount::Withdraw(long cents) {
  throw std::logic_error("TODO: implement Withdraw");
}

bool BankAccount::TransferTo(BankAccount& other, long cents) {
  throw std::logic_error("TODO: implement TransferTo");
}
