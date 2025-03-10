#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include "../Transactions/Transaction.h"
#include "../Bank/Bank.h"
 
class Account {
private:
    static int _next_id;
    int accId;
    double balance = 0;
    std::vector<Transaction*> transactions;
protected:
    void deposit(double amnt);
    void withdraw(double amnt);
    friend class Bank;
public:
    Account(); 
    Account(double deposit);
    Account(const Account& other); // copy constructor
    Account operator=(const Account& other); // assignment constructor
    ~Account(); //destructor

    int getId();
    double getBalance() const;
    std::vector<Transaction*> getTransactions();

    Account operator+(const Account& other);
    Account operator-(const Account& other);

    friend Account operator+(const Account& acc, const double amnt);
    friend Account operator+(const double amnt, const Account& acc);
    friend bool operator>(const Account& a1, const Account& a2);
    
};

#endif
