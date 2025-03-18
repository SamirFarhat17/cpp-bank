#ifndef BANK_H
#define BANK_H

#include <vector>
#include <unordered_map>
#include "../records/Recording.h"

#ifndef NUM_TRANSACTIONS
    #define FED_INTEREST_RATE 435.000
#endif


extern double globalInterestRate;

class Account;
class Customer;
class Transaction;

extern std::mutex log_mtx;

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