#include <algorithm>
#include "Bank.h"
#include "TransactionException.h"
#include "CustomerNotFoundException.h"
#include "../Customers/Customer.h"  // Include full definition of Customer
#include "../Accounts/Account.h"    // Include full definition of Account
#include "../Transactions/Transaction.h"  // Include full definition of Transaction


double globalInterestRate = 200.0000;

Bank::Bank() {
    Recording::initialize();
}
Bank::~Bank() {
    Recording::close();
    std::cout << "Deleting each customer in customers from Bank.cpp\n";
    //for(Customer* c : customers) delete c; 
    customers.clear();
    std::cout << "Deleting each Account in mappings from Bank.cpp\n";
    //for(auto it = mappings.begin(); it != mappings.end(); ++it) delete it->second;
    mappings.clear();

}

void Bank::addCustomer(Customer& c) {
    customers.push_back(&c);
}


void Bank::addAccount(Account& account) {
    mappings[account.getId()] = &account;  // Use the actual account reference
    Recording::accs.close();
}

Account* Bank::getCustomerAccount(int customerId, int accountId) {
    auto it = std::find_if(customers.begin(), customers.end(), 
        [customerId] (const Customer* c) { 
            return c->getId() == customerId; 
        });

    if(it == customers.end()) throw CustomerNotFoundException();   
    else if(mappings.find(accountId) == mappings.end() || !mappings.count(accountId)) throw CustomerNotFoundException("Account not found");
    // this time the exception propagates up(expected)
    return mappings[accountId];
}

void Bank::executeTransaction(Transaction transact) {
    try {
        if (transact.amount <= 0)  throw TransactionException("Invalid amount submitted");

        auto sourceIt = mappings.find(transact.source);
        auto destIt = mappings.find(transact.destination);

        if (sourceIt == mappings.end() || destIt == mappings.end())  throw TransactionException("One or more of Accounts not found");

        if (transact.amount > sourceIt->second->getBalance())  throw TransactionException("Payment greater than account balance");

        // Perform the transaction
        sourceIt->second->withdraw(transact.amount);
        destIt->second->deposit(transact.amount);
    } 
    catch (TransactionException& e) {
        std::cerr << e.what() << "^^^^^" << '\n';
    }
}
