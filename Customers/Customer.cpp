#include "Customer.h"
#include <random>
#include "../Accounts/Account.h"


std::unordered_set<int> Customer::customerIDs;

Customer::Customer(std::string n) : name(n) {
    _id = generateCustomerID();
    customerIDs.insert(_id);
}

Customer::Customer(const Customer& other) : _id(other._id), name(other.name) {
    std::cout<<"Customer Copy constructor ";
    for (Account* acc : other.accounts) {
        accounts.push_back(new Account(*acc));  // Deep copy
    }
}

Customer& Customer::operator=(const Customer& other) {
    std::cout<<"Customer Assignment operator ";
    if(this != &other) {
        for(Account* acc : accounts) delete acc;
        accounts.clear();
    }
    accounts.clear();

    _id = other._id;
    name = other.name;

    for (Account* acc : other.accounts) {
        accounts.push_back(new Account(*acc));  // Deep copy
    }

    return *this;
}


Customer::~Customer() {
    std::cout<<"Customer destructor ";
    for(Account* acc : accounts) delete acc;
    accounts.clear();
}


std::string Customer::getName() { 
    return name; 
}
int Customer::getId() const { 
    return _id; 
}

std::vector<Account*> Customer::getAccounts() { return accounts; }

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
    accounts.push_back(new Account(deposit));
}

void Customer::openAccount(Account acc) {
    accounts.push_back(new Account(acc));
}

std::ostream& operator<<(std::ostream& os, const Customer& c) {
    os << "id: " << c._id << " name: " << c.name << " accounts " << c.accounts.size() << '\n';
    return os;
}