#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account 
{
private:
    int events = 0;
    double interest_rate;
    void accrueInterest() {
        if(events % 3 == 0) deposit(getBalance() * (interest_rate/10000));
    }
protected:
    virtual void deposit(double amnt) {
        Account::deposit(amnt);
        std::cout << "\nCalled inherited deposit\n";
        events++;
        accrueInterest();
    }
    virtual void withdraw(double amnt) {
        Account::withdraw(amnt);
        std::cout << "\nCalled inherited withdraw\n";
        events++;
        accrueInterest();
    }
public:
    SavingsAccount(double fed_rate = 0) : Account(), interest_rate(fed_rate) {
        std::cout << "-Constructed Savings Account-";
    }
    SavingsAccount(double deposit, double fed_rate = 0) : Account(deposit), interest_rate(fed_rate) {
        std::cout << "-Constructed Savings Account-";
    }
    void printThis() override {
        std::cout << "Print Savings account\n";
    }
};

#endif 