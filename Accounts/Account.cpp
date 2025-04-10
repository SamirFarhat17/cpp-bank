#include "Account.h"
#include <algorithm>
#include <iostream>
#include <atomic>

std::atomic<int> Account::_next_id(1000); // Myultithreaded account creation means this shoiuld be atomic to prevent account creation with same id

Account::Account() : accId(++_next_id) { std::cout << "-Constructed Account-"; }
Account::Account(double deposit) : accId(++_next_id), balance(deposit) { std::cout << "-Constructed Account-"; }

Account::Account(const Account& other) {
    std::cout<<"Account copy constructor ";
    if(!transactions.empty()) {
        for(Transaction* transact : transactions) delete transact;
        transactions.clear();
    }
    for(Transaction* transact : other.transactions) transactions.push_back(new Transaction(*transact));
    accId = other.accId;
    balance = other.balance;
}

Account Account::operator=(const Account& other) {
    std::cout<<"Account assignment constructor ";
    if(this != &other) {
        for(Transaction* transact : transactions) delete transact;
        transactions.clear();

        accId = other.accId;
        balance = other.balance;

        for(Transaction* transact : other.transactions) {
            transactions.push_back(new Transaction(*transact));
        }
    }

    return *this;
}

bool Account::operator>(const Account& other) const {
    return balance > other.balance;
}

Account::~Account() {
    std::cout<<"Account destructor ";
    for(Transaction* transact : transactions) delete transact;
    transactions.clear();
}


double Account::getBalance() const {
    return balance;
}

int Account::getId() const { return accId; }

std::vector<Transaction*> Account::getTransactions() {
    return transactions;
}

void Account::withdraw(double amnt) {
    balance -= amnt; // Corrected to subtract the amount from balance
}

void Account::deposit(double amnt) {
    balance += amnt;
}


Account Account::operator+(const Account& other) const {
    return Account(balance + other.balance);
}

Account operator+(const Account& acc, const double amnt) {
    return Account(acc.balance + amnt);
}

Account operator+(const double amnt, const Account& acc) {
    return Account(acc.balance + amnt);
}

Account Account::operator-(const Account& other) const {
    return Account(std::min((double)0, balance - other.balance));
}

bool operator>(const Account& a1, const Account& a2)  {
    return a1.getBalance() > a2.getBalance();
}

void Account::printThis() {
    std::cout << "Print account\n";
}

std::string Account::print() const {
    return "ACCOUNT ID: " + std::to_string(accId) + " BALANCE: " + std::to_string(balance) + " Transactions " + std::to_string(transactions.size());
}

std::ostream& operator<<(std::ostream& os, const Account& acc) {
    os << "Account id: " << acc.getId() << " balance: " << acc.getBalance() << std::endl;
    return os;
}