#include "Customer.h"
#include <random>
#include "../Accounts/Account.h"


std::unordered_set<int> Customer::customerIDs;

Customer::Customer(std::string n) : name(n) {
    _id = generateCustomerID();
    customerIDs.insert(_id);
}

std::string Customer::getName() { 
    return name; 
}
int Customer::getId() { 
    return _id; 
}

std::vector<Account> Customer::getAccounts() { return accounts; }

int Customer::generateCustomerID() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1000000, 2000000);
    int rand = distrib(gen);
    
    while (customerIDs.count(rand)) {
        rand = distrib(gen);
    }
    
    return rand;
}

void Customer::openAccount(double deposit) {
    accounts.push_back(Account(deposit));
}
