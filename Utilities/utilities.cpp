#pragma once

#include "../Customers/Customer.h"
#include "../Accounts/Account.h"
#include "../Transactions/Transaction.h"

// Overloading
inline double add(Customer& x, Customer& y) {
    double c1 = 0, c2 = 0;
    for(Account* acc1 : x.getAccounts()) c1 += acc1->getBalance();
    for(Account* acc2 : y.getAccounts()) c2 += acc2->getBalance();

    return c1 + c2;
}

inline double add(Account a1, Account a2) {
    return a1.getBalance() + a2.getBalance();
}

inline double add(Transaction t1, Transaction t2) {
    return t1.amount + t2.amount;
}

inline double add(Customer c, Account a) {
    double cSum = 0;
    for(Account* acc : c.getAccounts()) cSum += acc->getBalance();
    return cSum + a.getBalance();
}

inline double add(Account a, Transaction t) {
    return a.getBalance() + t.amount;
}

template<typename T, typename U, typename V>
inline double add(T t, U u, V v) {
    return add(t,u) + add(u, v);
}

inline bool locateAccLine(std::string line, std::string id) {
    if(line.empty() || line[0] != 'A') return false;
    int idx = 0;
    std::string matcher;
    while(matcher != "ACCOUNT ID: ") {
        matcher += line[idx];
        idx++;
    }
    matcher.clear();
    while(line[idx] != ' ') {
        matcher += line[idx];
        idx++;
    }
    return matcher == id;

}