#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "Bank/Bank.h"
#include "Customers/Customer.h"
#include "Accounts/Account.h"
#include "Transactions/Transaction.h"
#include "Bank/TransactionException.h"

#define NUM_CUSTOMERS 500  // Change this value to scale
#define NUM_TRANSACTIONS 10000 // Increase for more transactions

bool test(); // forward declaration

int main() {
    if (!test()) {
        std::cerr << "Test failed, exiting.\n";
        return 0;
    }

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

        double amount = (rand() % 2000) - 500; // Random amount (-500 to 1500), allowing invalid cases

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

bool test() {
#ifdef NDEBUG
    std::cerr << "NDEBUG is enabled";
    std::abort();
#endif
    std::cout << "[TEST] Running Bank Application Unit Tests...\n";

    // Initialize test bank and customers
    Bank testBank;
    Customer* testCustomer = new Customer("Test User");
    testCustomer->openAccount(1000.0);
    Customer* receiver = new Customer("Receiver User");
    receiver->openAccount(500.0);

    // Retrieve accounts from testBank
    Account* testAccount = testCustomer->getAccounts().empty() ? nullptr : testCustomer->getAccounts()[0];
    Account* receiverAccount = receiver->getAccounts().empty() ? nullptr : receiver->getAccounts()[0];

    assert(testAccount && receiverAccount && "Failed to create accounts!");

    // Register customers and accounts with testBank
    testBank.addCustomer(*testCustomer);
    testBank.addCustomer(*receiver);
    testBank.addAccount(*testAccount);
    testBank.addAccount(*receiverAccount);

    // Ensure the bank manages the correct accounts
    Account* bankTestAccount = testBank.getCustomerAccount(testCustomer->getId(), testAccount->getId());
    Account* bankReceiverAccount = testBank.getCustomerAccount(receiver->getId(), receiverAccount->getId());

    assert(bankTestAccount && bankReceiverAccount && "Bank did not correctly track accounts!");

    double initialBalanceSender = bankTestAccount->getBalance();
    double initialBalanceReceiver = bankReceiverAccount->getBalance();

    // Perform a valid transaction
    double transferAmount = 200.0;
    Transaction validTransaction{transferAmount, bankTestAccount->getId(), bankReceiverAccount->getId()};
    testBank.executeTransaction(validTransaction);

    // Verify balance updates within testBank
    assert(bankTestAccount->getBalance() == initialBalanceSender - transferAmount && "Withdraw failed via transaction!");
    assert(bankReceiverAccount->getBalance() == initialBalanceReceiver + transferAmount && "Deposit failed via transaction!");

    std::cout << "[SUCCESS] Valid transaction test passed.\n";

    // Attempt an invalid transaction (overdraft)
    double invalidAmount = 5000.0;
    Transaction invalidTransaction{invalidAmount, bankTestAccount->getId(), bankReceiverAccount->getId()};

    bool exceptionCaught = false;
    try {
        testBank.executeTransaction(invalidTransaction);
    } catch (const TransactionException& e) {
        exceptionCaught = true;
        std::cout << "Caught expected TransactionException: " << e.what() << std::endl;
    }

    assert(!exceptionCaught && "Overdraft transaction should have thrown an exception!");
    std::cout << "[SUCCESS] Overdraft protection test passed.\n";

    // Clean up allocated memory
    delete testCustomer;
    delete receiver;

    std::cout << "[TEST] All tests passed successfully!\n";
    return true;
}


