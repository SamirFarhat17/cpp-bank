#include "Customer.h"
#include <random>

std::unordered_set<int> Customer::customerIDs;

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

Customer::Customer(std::string n) : name(n) {
    _id = generateCustomerID();
    customerIDs.insert(_id);
}

void Customer::openAccount(double deposit) {
    accounts.push_back(Account(deposit));
}
