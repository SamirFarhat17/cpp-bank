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
#include "Utilities/utilities.cpp"

#define NUM_CUSTOMERS 500  // Change this value to scale
#define NUM_TRANSACTIONS 10000 // Increase for more transactions

//#define NDEBUG

bool test(); // forward declaration
bool testOverload();
bool testOperatorOverload();

int main() {
    if(!testOperatorOverload()) {
        std::cerr << "Test failed, exiting.\n";
        return 0;
    }

    if(!testOverload()) {
        std::cerr << "Test failed, exiting.\n";
        return 0;
    }

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

bool testOverload() {
    std::cout << "[TEST] Running Overload Tests...\n";

    // Create customers
    Customer* customer1 = new Customer("Alice");
    Customer* customer2 = new Customer("Bob");

    // Open accounts with initial deposits
    customer1->openAccount(1000.0);
    customer1->openAccount(500.0);
    customer2->openAccount(1200.0);

    // Retrieve accounts
    Account* acc1 = customer1->getAccounts()[0];
    Account* acc2 = customer1->getAccounts()[1];
    Account* acc3 = customer2->getAccounts()[0];

    // Create transactions
    Transaction t1{250.0, acc1->getId(), acc2->getId()};
    Transaction t2{400.0, acc2->getId(), acc3->getId()};

    // Test Account + Account
    assert(add(*acc1, *acc2) == (acc1->getBalance() + acc2->getBalance()));

    // Test Transaction + Transaction
    assert(add(t1, t2) == (t1.amount + t2.amount));

    // Test Customer + Customer
    double totalBalance1 = 0;
    double totalBalance2 = 0;
    for (Account* a : customer1->getAccounts()) totalBalance1 += a->getBalance();
    for (Account* a : customer2->getAccounts()) totalBalance2 += a->getBalance();
    assert(add(*customer1, *customer2) == totalBalance1 + totalBalance2);

    // Test Customer + Account
    assert(add(*customer1, *acc3) == (totalBalance1 + acc3->getBalance()));

    // Test Account + Transaction
    assert(add(*acc1, t1) == (acc1->getBalance() + t1.amount));
  
    // Test three-parameter add function
    assert(add(*customer1, *acc2, t1) == (totalBalance1 + (2*acc2->getBalance()) + t1.amount));

    std::cout << "[SUCCESS] All Overload Tests Passed!\n";

    return true;
}

bool testOperatorOverload() {
    std::cout << "[TEST] Running Operator Overload Tests...\n";

    // Create test accounts
    Account acc1(1000.0);  // Account with a balance of 1000
    Account acc2(500.0);   // Account with a balance of 500
    Account acc3(300.0);   // Account with a balance of 300

    // Test Account + Account
    Account result1 = acc1 + acc2;
    assert(result1.getBalance() == (acc1.getBalance() + acc2.getBalance()) && "Account + Account overload failed!");

    // Test Account + double
    Account result2 = acc1 + 200.0;  // Adding 200 to acc1
    assert(result2.getBalance() == (acc1.getBalance() + 200.0) && "Account + double overload failed!");

    // Test double + Account
    Account result3 = 150.0 + acc1;  // Adding 150 to acc1
    assert(result3.getBalance() == (150.0 + acc1.getBalance()) && "double + Account overload failed!");

    // Test Account - Account
    Account result4 = acc1 - acc2;  // Subtracting acc2 balance from acc1 balance
    assert(result4.getBalance() == std::min(0.0, acc1.getBalance() - acc2.getBalance()) && "Account - Account overload failed!");

    Customer cust("Steve Martin");
    std::cout << cust;

    // Test Account > Account (operator >)
    assert(acc1 > acc2 && "Account 1 should be greater than Account 2!");
    assert(!(acc2 > acc1) && "Account 2 should not be greater than Account 1!");
    assert(!(acc3 > acc2) && "Account 3 should not be greater than Account 2!");
    assert(acc1 > acc3 && "Account 1 should be greater than Account 3!");

    std::cout << "[SUCCESS] All Operator Overload Tests Passed!\n";
    return true;
}
