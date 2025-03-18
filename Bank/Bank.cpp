#include <algorithm>
#include <mutex>
#include <semaphore>
#include "Bank.h"
#include "TransactionException.h"
#include "CustomerNotFoundException.h"
#include "../Customers/Customer.h"  // Include full definition of Customer
#include "../Accounts/Account.h"    // Include full definition of Account
#include "../Transactions/Transaction.h"  // Include full definition of Transaction
#include "../Utilities/Semaphore.cpp"

double globalInterestRate = 200.0000;
std::mutex mtx;
std::mutex log_mtx;
Semaphore semaphore(1);

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
    std::lock_guard<std::mutex> lock(mtx); // Protects multithreaded customer creation preventing dupes, lock destroyed on function exit(out of scope)
    customers.push_back(&c);
    Recording::writeCust(c);
}


void Bank::addAccount(Account& account) {
    mappings[account.getId()] = &account;  // Use the actual account reference
    Recording::writeAccs(account);
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
    SemaphoreGuard semaphore_guard(semaphore); // SO that it releases when out of scope no matter if exception is thrown
    try {
        if (transact.amount <= 0)  throw TransactionException("Invalid amount submitted");

        auto sourceIt = mappings.find(transact.source);
        auto destIt = mappings.find(transact.destination);

        if (sourceIt == mappings.end() || destIt == mappings.end())  throw TransactionException("One or more of Accounts not found");

        if (transact.amount > sourceIt->second->getBalance())  throw TransactionException("Payment greater than account balance");

        // Perform the transaction
        sourceIt->second->withdraw(transact.amount);
        destIt->second->deposit(transact.amount);
        Recording::writeTrans(transact);
        Recording::writeAccs(*sourceIt->second);
        Recording::writeAccs(*destIt->second);
    } 
    catch (TransactionException& e) {
        // Use a lock to ensure error messages are printed atomically
        std::lock_guard<std::mutex> lock(log_mtx);

        std::cerr << "[ERROR] Transaction failed: " << e.what() 
                  << " | Amount: $" << transact.amount 
                  << " | Source: " << transact.source 
                  << " | Destination: " << transact.destination
                  << '\n';
    }
    
};