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

#define NUM_CUSTOMERS 5000  // Change this value to scale
#define NUM_TRANSACTIONS 100000 // Increase for more transactions

int main() {
    srand(time(nullptr));  // Random seed
    auto start = std::chrono::high_resolution_clock::now();
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
                      << sender.getName() << " (Acc: " << sender.getAccounts()[senderAccIdx].getId() << "," << sender.getAccounts()[senderAccIdx].getBalance()
                      << ") to " << receiver.getName() << " (Acc: " << receiver.getAccounts()[receiverAccIdx].getId() << ")"
                      << std::endl;

        masterBank.executeTransaction(txn);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() * 1000 << " milliseconds" << std::endl;

    return 0;
}

bool test() {
    return true;
}
