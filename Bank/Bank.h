#ifndef BANK_H
#define BANK_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include "../Customers/Customer.h"
#include "../Accounts/Account.h"
#include "../Transactions/Transaction.h"
#include "TransactionException.h"

class Bank {
private:
    std::vector<Customer> customers;
    std::unordered_map<int, Account> mappings;

public:
    Bank() {}

    void addCustomer(Customer c) {
        customers.push_back(c);
    }

    void addAccount(Account a) {
        mappings[a.getId()] = a;
    }

    void executeTransaction(Transaction transact);
};

#endif
