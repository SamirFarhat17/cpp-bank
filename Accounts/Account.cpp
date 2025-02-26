#include "Account.h"

int Account::_next_id = 1000;

Account::Account() : accId(++_next_id) {}
Account::Account(double deposit) : accId(++_next_id), balance(deposit) {}
Account::Account(const Account& other) {

}
Account Account::operator=(const Account& other) {
    if(this != &other) {
        for(Transaction* transact : transactions) delete transact;
        transactions.clear();

        accId = other.accId;
        balance = other.balance;

        for(Transaction* transact : other.transactions) {
            transactions.push_back(transact);
        }
    }

    return *this;
}

Account::~Account() {
    std::cout<<"Account destructor";
    for(Transaction* transact : transactions) delete transact;
    transactions.clear();
}


double Account::getBalance() {
    return balance;
}

int Account::getId() { return accId; }

std::vector<Transaction*> Account::getTransactions() {
    return transactions;
}

void Account::withdraw(double amnt) {
    balance -= amnt; // Corrected to subtract the amount from balance
}

void Account::deposit(double amnt) {
    balance += amnt;
}
