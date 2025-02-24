#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "Bank/Bank.h"
#include "Customers/Customer.h"
#include "Accounts/Account.h"
#include "Transactions/Transaction.h"
#include "Bank/TransactionException.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Bank masterBank;

    // Create 10 customers with 1-3 accounts each
    std::vector<Customer*> customers;
    for (int i = 1; i <= 10; ++i) {
        Customer* customer = new Customer("Customer " + std::to_string(i));
        int numAccounts = 1 + rand() % 3; // 1 to 3 accounts
        for (int j = 0; j < numAccounts; ++j) {
            double initialDeposit = 100.0 + rand() % 1000; // Random initial deposit between 100 and 1099
            customer->openAccount(initialDeposit);
        }
        masterBank.addCustomer(customer);
        customers.push_back(customer);
    }

    // Add accounts to the bank's mappings
    for (auto& customer : customers) {
        for (auto& account : customer->getAccounts()) {
            masterBank.addAccount(&account);
        }
    }

    // Run some valid and invalid transactions
    try {
        // Valid transaction
        Transaction validTransaction = {50.0, customers[0]->getAccounts()[0].getId(), customers[1]->getAccounts()[0].getId()};
        masterBank.executeTransaction(validTransaction);

        // Invalid transaction: insufficient funds
        Transaction invalidTransaction1 = {5000.0, customers[2]->getAccounts()[0].getId(), customers[3]->getAccounts()[0].getId()};
        masterBank.executeTransaction(invalidTransaction1);

        // Invalid transaction: negative amount
        Transaction invalidTransaction2 = {-100.0, customers[4]->getAccounts()[0].getId(), customers[5]->getAccounts()[0].getId()};
        masterBank.executeTransaction(invalidTransaction2);

        // Invalid transaction: non-existent account
        Transaction invalidTransaction3 = {50.0, 999999, customers[6]->getAccounts()[0].getId()};
        masterBank.executeTransaction(invalidTransaction3);
    } catch (const TransactionException& e) {
        std::cerr << "Transaction error: " << e.what() << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() * 1000 << " milliseconds" << std::endl;

    return 0;
}

bool test() {
    return true;
}
