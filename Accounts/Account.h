#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include "../Transactions/Transaction.h"

class Account {
private:
    static int _next_id;
    int accId;
    double balance = 0;
    std::vector<Transaction> transactions;

public:
    Account() : accId(++_next_id) {}
    Account(double deposit) : accId(++_next_id), balance(deposit) {}

    int getId() { return accId; }
    double getBalance();
    std::vector<Transaction> getTransactions();
    void deposit(double amnt);
    void withdraw(double amnt);
};

#endif
