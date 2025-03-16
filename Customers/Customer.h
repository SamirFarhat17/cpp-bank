#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <random>

class Account;

class Customer {
private:
    int _id;
    std::string name;
    std::vector<Account*> accounts;
    int generateCustomerID();
protected:
    static std::unordered_set<int> customerIDs;
public:
    Customer(std::string n);    
    Customer(const Customer& c);
    Customer& operator=(const Customer& other);
    ~Customer();

    std::string getName();
    void openAccount(double deposit);
    void openAccount(Account acc);
    int getId() const;
    std::vector<Account*> getAccounts();
    std::string print() const;

    friend std::ostream& operator<<(std::ostream& os, const Customer& c);
};

#endif
