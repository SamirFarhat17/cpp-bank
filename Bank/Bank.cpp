#include "Bank.h"
#include "TransactionException.h"

double globalInterestRate = 200.0000;

void Bank::executeTransaction(Transaction transact) {
    try {
        if (transact.amount <= 0) 
            throw TransactionException("Invalid amount submitted");

        auto sourceIt = mappings.find(transact.source);
        auto destIt = mappings.find(transact.destination);

        if (sourceIt == mappings.end() || destIt == mappings.end())  throw TransactionException("One or more of Accounts not found");

        if (transact.amount > sourceIt->second.getBalance())  throw TransactionException("Payment greater than account balance");

        // Perform the transaction
        sourceIt->second.withdraw(transact.amount);
        destIt->second.deposit(transact.amount);
    } 
    catch (TransactionException& e) {
        std::cerr << e.what() << "^^^^^" << '\n';
    }
}
