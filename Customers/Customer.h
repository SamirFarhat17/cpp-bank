#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <unordered_set>
#include <random>
#include "../Accounts/Account.h"

class Customer {
private:
    int _id;
    const std::string name;
    std::vector<Account> accounts;
    
protected:
    static std::unordered_set<int> customerIDs;

public:
    Customer(std::string n);
    int generateCustomerID();
    void openAccount(double deposit);
    int getId() { return _id; }
    std::vector<Account> getAccounts() const { return accounts; }
};

#endif
