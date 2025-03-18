#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <thread>
#include <mutex>
#include <semaphore>


#include "Bank/Bank.h"
#include "Bank/CustomerNotFoundException.h"
#include "Bank/TransactionException.h"
#include "Customers/Customer.h"
#include "Accounts/Account.h"
#include "Accounts/SavingsAccount.h"
#include "Transactions/Transaction.h"
#include "Utilities/utilities.cpp"
#include "Test.cpp"

#ifndef NUM_CUSTOMERS
    #define NUM_CUSTOMERS 500
#endif

#ifndef NUM_TRANSACTIONS
    #define NUM_TRANSACTIONS 10000
#endif
//#define NDEBUG
//#define CONCURRENCY

bool transactionExecutor(Bank& bank, std::unordered_map<int,std::vector<int>>& customerAccIds, std::vector<int>& customerIds) {
    thread_local std::random_device rd;
    thread_local std::mt19937 rng(rd());
    thread_local std::uniform_real_distribution<double> amountDist(-500.0,2000);
    thread_local std::uniform_int_distribution<int> customerDist(0, NUM_CUSTOMERS-1);

    for (int i = 0; i < NUM_TRANSACTIONS; ++i) {
        int senderIdx = customerDist(rng);
        int receiverIdx = customerDist(rng);
        while (receiverIdx == senderIdx) receiverIdx = customerDist(rng); // Ensure different customers

        int senderId = customerIds[senderIdx];
        int receiverId = customerIds[receiverIdx];

        if (customerAccIds[senderId].empty() || customerAccIds[receiverId].empty()) continue; // Skip if no accounts

        int senderAccId = customerAccIds[senderId][rand() % customerAccIds[senderId].size()];
        int receiverAccId = customerAccIds[receiverId][rand() % customerAccIds[receiverId].size()];

        double amount = amountDist(rng); // Random amount (-500 to 1500), allowing invalid cases

        Transaction txn = {amount, senderAccId, receiverAccId};
        {
            std::lock_guard<std::mutex> lock(log_mtx);
            std::cout << "[TRANSACTION] $" << amount << " wire from "  << '[' << senderId << ']' << " (Acc: " << senderAccId 
                << ") to " << receiverId << " (Acc: " << receiverAccId << ")\n";
        }
        bank.executeTransaction(txn);
    }

    return true;
}

bool multithreadedBank() {

    std::cout << "INITIALIZING CONCURRENT BANK\n";
    Bank concurrentBank;
    std::unordered_map<int, std::vector<int>> customerAccIds;
    std::vector<int> customerIds;

    // Create customers with random accounts
    for (int i = 1; i <= NUM_CUSTOMERS; ++i) {
        Customer* customer = new Customer("Customer " + std::to_string(i));
        customerAccIds[customer->getId()] = {};
        customerIds.push_back(customer->getId());
        int numAccounts = 1 + rand() % 3; // 1 to 3 accounts

        for (int j = 0; j < numAccounts; ++j) {
            double initialDeposit = 100.0 + rand() % 100000; // Random deposit between 100-1099
            customer->openAccount(initialDeposit);
        }

        concurrentBank.addCustomer(*customer);
        for (Account* account : customer->getAccounts()) {
            concurrentBank.addAccount(*account);
            customerAccIds[customer->getId()].push_back(account->getId());
        }
    }


    srand(time(nullptr));
    int noThreads = rand() % 15 + 1;
    //noThreads = 1;
    std::vector<std::thread> threads(noThreads);

    for(int i = 0; i < noThreads; i++) {
        threads[i] = std::thread(transactionExecutor, std::ref(concurrentBank), std::ref(customerAccIds), std::ref(customerIds));
    }

    std::cout << "THREAD CREATION DONE, TIMING EXECUTION\n";
    /// TIMING
    using Clock = std::chrono::high_resolution_clock;
    auto initialTime = Clock::now();


    for(auto& t : threads) t.join();

    auto endTime = Clock::now();
    auto duration = std::chrono::duration<double>(endTime - initialTime);
    std::cout << "[FINISHED] Multi-threaded simulation lasted " << duration.count() << "s\n";


    return true;
}

/*
bool test(); // forward declaration
bool testOverload();
bool testOperatorOverload();
bool testInheritance();
*/
int main() {
    std::cout << "FED INTEREST RATE=" << FED_INTEREST_RATE << '\n';
#ifdef NDEBUG
    std::cerr << "NDEBUG is enabled";
    std::abort();
#endif
#ifdef TEST_MODE
    if(!BankTests::testInheritance()) {
        std::cerr << "Test failed, exiting.\n";
        return 0;
    }
    if(!BankTests::testOperatorOverload()) {
        std::cerr << "Test failed, exiting.\n";
        return 0;
    }

    if(!BankTests::testOverload()) {
        std::cerr << "Test failed, exiting.\n";
        return 0;
    }

    if (!BankTests::test()) {
        std::cerr << "Test failed, exiting.\n";
        return 0;
    }
    std::cout << "[TESTS] ALL TESTS CONCLUDED SUCCESSFULLY\n";
    return 0;
#endif
#ifdef CONCURRENCY
    multithreadedBank();
    return 0;
#endif
    srand(time(nullptr));  // Random seed
    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();
    
    Bank masterBank;
    std::vector<Customer*> customers; // Store pointers to ensure proper memory management

    // Create customers with random accounts
    for (int i = 1; i <= NUM_CUSTOMERS; ++i) {
        Customer* customer = new Customer("Customer " + std::to_string(i));
        int numAccounts = 1 + rand() % 3; // 1 to 3 accounts

        for (int j = 0; j < numAccounts; ++j) {
            double initialDeposit = 100.0 + rand() % 1000; // Random deposit between 100-1099
            customer->openAccount(initialDeposit);
        }

        masterBank.addCustomer(*customer);
        customers.push_back(customer);
    }

    // Add accounts to the bank's mappings
    for (Customer* customer : customers) {
        for (Account* account : customer->getAccounts()) {
            masterBank.addAccount(*account);
        }
    }

    // Perform random transactions
    for (int i = 0; i < NUM_TRANSACTIONS; ++i) {
        int senderIdx = rand() % NUM_CUSTOMERS;
        int receiverIdx = rand() % NUM_CUSTOMERS;
        while (receiverIdx == senderIdx) receiverIdx = rand() % NUM_CUSTOMERS; // Ensure different customers

        Customer* sender = customers[senderIdx];
        Customer* receiver = customers[receiverIdx];

        if (sender->getAccounts().empty() || receiver->getAccounts().empty()) continue; // Skip if no accounts

        int senderAccIdx = rand() % sender->getAccounts().size();
        int receiverAccIdx = rand() % receiver->getAccounts().size();

        double amount = (rand() % 200000) / 100.0; // Random amount (-500 to 1500), allowing invalid cases

        Transaction txn = {amount, sender->getAccounts()[senderAccIdx]->getId(), receiver->getAccounts()[receiverAccIdx]->getId()};
        std::cout << "[TRANSACTION] $" << amount << " wire from " 
                  << sender->getName() << '[' << sender->getId() << ']' 
                  << " (Acc: " << sender->getAccounts()[senderAccIdx]->getId() << ", " 
                  << sender->getAccounts()[senderAccIdx]->getBalance() << ") to " 
                  << receiver->getName() << " (Acc: " << receiver->getAccounts()[receiverAccIdx]->getId() << ")"
                  << std::endl;

        masterBank.executeTransaction(txn);
    }

    auto end = Clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() * 1000 << " milliseconds" << std::endl;

    // Clean up dynamically allocated memory
    for (Customer* customer : customers) {
        delete customer;
    }
    customers.clear();

    return 0;
}
