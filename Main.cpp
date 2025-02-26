#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Bank/Bank.h"
#include "Customers/Customer.h"
#include "Accounts/Account.h"
#include "Transactions/Transaction.h"
#include "Bank/TransactionException.h"

#define NUM_CUSTOMERS 500  // Change this value to scale
#define NUM_TRANSACTIONS 10000 // Increase for more transactions

int main() {
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
    return true;
}
