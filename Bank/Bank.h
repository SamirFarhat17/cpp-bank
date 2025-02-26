#ifndef BANK_H
#define BANK_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include "TransactionException.h"

#define FED_INTEREST_RATE 435.000

extern double globalInterestRate;

class Account;
class Customer;
class Transaction;

class Bank {
private:
    std::vector<Customer*> customers;
    std::unordered_map<int, Account*> mappings;
public:
    Bank();
    ~Bank();

    void addCustomer(Customer& c);

    void addAccount(Account& a);

    void executeTransaction(Transaction transact);

    Account* getCustomerAccount(int customerId, int accountId);
};

#endif
