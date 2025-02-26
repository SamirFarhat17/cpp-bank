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

//#define NDEBUG false;

#define NUM_CUSTOMERS 500  // Change this value to scale
#define NUM_TRANSACTIONS 10000 // Increase for more transactions

bool test(); // forward declaration

int main() {
    if(!test()) return 0;

    #ifdef FED_INTEREST_RATE
        std::cout << "Fed interest rate is " << FED_INTEREST_RATE / 100 << "%" << '\n';
        std::cout << "Global interest rate is " << globalInterestRate/100 << "%" << '\n';
    #endif
    srand(time(nullptr));  // Random seed
    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();
    Bank masterBank;

    // Create customers with random accounts
    std::vector<Customer> customers;
    for (int i = 1; i <= NUM_CUSTOMERS; ++i) {
        Customer customer("Customer " + std::to_string(i));
        int numAccounts = 1 + rand() % 3; // 1 to 3 accounts

        for (int j = 0; j < numAccounts; ++j) {
            double initialDeposit = 100.0 + rand() % 1000; // Random deposit between 100-1099
            customer.openAccount(initialDeposit);
        }

        masterBank.addCustomer(customer);
        customers.push_back(customer);
    }

    // Add accounts to the bank's mappings
    for (auto& customer : customers) {
        for (auto& account : customer.getAccounts()) {
            masterBank.addAccount(account);
        }
    }

    // Perform random transactions
    for (int i = 0; i < NUM_TRANSACTIONS; ++i) {
        int senderIdx = rand() % NUM_CUSTOMERS;
        int receiverIdx = rand() % NUM_CUSTOMERS;
        while (receiverIdx == senderIdx) receiverIdx = rand() % NUM_CUSTOMERS; // Ensure different customers

        Customer& sender = customers[senderIdx];
        Customer& receiver = customers[receiverIdx];

        if (sender.getAccounts().empty() || receiver.getAccounts().empty()) continue; // Skip if no accounts

        int senderAccIdx = rand() % sender.getAccounts().size();
        int receiverAccIdx = rand() % receiver.getAccounts().size();

        double amount = (rand() % 2000) - 500; // Random amount (-500 to 1500), allowing invalid cases

        Transaction txn = {amount, sender.getAccounts()[senderAccIdx].getId(), receiver.getAccounts()[receiverAccIdx].getId()};
        std::cout << "[TRANSACTION] $" << amount << " wire from " 
                      << sender.getName() << '[' << sender.getId() << ']' << " (Acc: " << sender.getAccounts()[senderAccIdx].getId() << "," << sender.getAccounts()[senderAccIdx].getBalance()
                      << ") to " << receiver.getName() << " (Acc: " << receiver.getAccounts()[receiverAccIdx].getId() << ")"
                      << std::endl;

        masterBank.executeTransaction(txn);
    }

    auto end = Clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() * 1000 << " milliseconds" << std::endl;

    return 0;
}

bool test() {
#ifdef NDEBUG
    std::cerr << "NDEBUG is enabled";
    std::abort();
#endif

    std::cout << "[TEST] Running Bank Application Unit Tests...\n";

    // Create a test customer and account
    Customer testCustomer("Test User");
    testCustomer.openAccount(1000.0); // Initial deposit
    assert(testCustomer.getAccounts().size() == 1 && "Account creation failed!");

    Account& testAccount = testCustomer.getAccounts()[0];
    double initialBalance = testAccount.getBalance();
    
    // Create another customer for transaction testing
    Customer receiver("Receiver User");
    receiver.openAccount(500.0);
    Account& receiverAccount = receiver.getAccounts()[0];
    double receiverInitialBalance = receiverAccount.getBalance();

    Bank testBank;
    testBank.addCustomer(testCustomer);
    testBank.addCustomer(receiver);
    testBank.addAccount(testAccount);
    testBank.addAccount(receiverAccount);

    // Perform a valid transaction
    double transferAmount = 200.0;
    Transaction validTransaction{transferAmount, testAccount.getId(), receiverAccount.getId()};
    testBank.executeTransaction(validTransaction);
    std::printf("%.2f %.2f %.2f\n", initialBalance, transferAmount, testAccount.getBalance());
    assert(testBank.getCustomerAccount(testCustomer.getId(), testAccount.getId())->getBalance() == initialBalance - transferAmount && "Withdraw failed via transaction!");
    assert(receiverAccount.getBalance() == receiverInitialBalance + transferAmount && "Deposit failed via transaction!");

    // Attempt an invalid transaction (overdraft)
    double invalidAmount = 5000.0; // More than the sender has
    Transaction invalidTransaction{invalidAmount, testAccount.getId(), receiverAccount.getId()};

    try {
        testBank.executeTransaction(invalidTransaction);
        assert(false && "Overdraft transaction should have thrown an exception!");
    } catch (const TransactionException& e) {
        std::cout << "Caught expected TransactionException: " << e.what() << std::endl;
    }

    // 6️⃣ **Check Interest Rates**
    #ifdef FED_INTEREST_RATE
        assert(FED_INTEREST_RATE > 0 && "FED_INTEREST_RATE is invalid!");
        std::cout << "[SUCCESS] Fed interest rate check passed: " << FED_INTEREST_RATE / 100 << "%\n";
    #endif

    assert(globalInterestRate > 0 && "Global interest rate is invalid!");
    std::cout << "[SUCCESS] Global interest rate check passed: " << globalInterestRate / 100 << "%\n";

    std::cout << "[TEST] All tests passed successfully!\n";
    return true;
}
