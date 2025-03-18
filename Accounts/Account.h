#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <atomic>
#include "../Transactions/Transaction.h"
 
class Account {
private:
    static std::atomic<int> _next_id;
    int accId;
    double balance = 0;
    std::vector<Transaction*> transactions;
protected:
    virtual void deposit(double amnt);
    virtual void withdraw(double amnt);
    friend class Bank;
public:
    Account(); 
    Account(double deposit);
    Account(const Account& other); // copy constructor
    Account operator=(const Account& other); // assignment constructor
    virtual ~Account(); //destructor

    int getId() const;
    double getBalance() const;
    std::vector<Transaction*> getTransactions();

    Account operator+(const Account& other) const;
    Account operator-(const Account& other) const;

    template<typename T>
    bool operator>(const T val) {
        return balance > val;
    }

    virtual void printThis();
    std::string print() const;

    friend Account operator+(const Account& acc, const double amnt);
    friend Account operator+(const double amnt, const Account& acc);
    friend bool operator>(const Account& a1, const Account& a2);
    
    friend std::ostream& operator<<(std::ostream& os, const Account& acc);
};

#endif
