#include "Account.h"

int Account::_next_id = 1000;

double Account::getBalance() {
return balance;
}
std::vector<Transaction> Account::getTransactions() {
return transactions;
}
void Account::withdraw(double amnt) {
balance = amnt;
}
void Account::deposit (double amnt)
balance += amnt;
}