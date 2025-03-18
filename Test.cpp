#pragma once

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


namespace BankTests {
    
    bool test() {
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

        // New test
        try {
            testBank.getCustomerAccount(999, 999); // Non-existent customer and account
        } catch (const CustomerNotFoundException& e) {
            exceptionCaught = true;
            std::cout << "Caught expected CustomerNotFoundException: " << e.what() << std::endl;
        }
        assert(exceptionCaught && "Invalid customer/account get should have thrown an exception!");
        
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

        assert(max(acc2,acc3).getBalance() == acc2.getBalance() && "Template max function failed with acc2 > acc3");
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

    bool testInheritance() {
        std::cout << "[TEST] Running Inheritance Tests...\n";

        Bank inheritanceBank;


        Customer c1 = Customer("Blake Lively");
        Customer c2 = Customer("Johnny Dep");
        Customer c3 = Customer("Frank Lampard");

        Account acc1(500000);
        SavingsAccount savingAcc1(500, globalInterestRate);
        SavingsAccount savingAcc2(10000, FED_INTEREST_RATE);


        c1.openAccount(acc1);
        c2.openAccount(savingAcc1);
        c3.openAccount(savingAcc2);

        inheritanceBank.addCustomer(c1);
        inheritanceBank.addAccount(acc1);
        inheritanceBank.addCustomer(c2);
        inheritanceBank.addAccount(savingAcc1);
        inheritanceBank.addCustomer(c3);
        inheritanceBank.addAccount(savingAcc2);

        std::vector<Transaction> transacts;
        transacts.push_back(Transaction{100.0, acc1.getId(), savingAcc1.getId()});
        transacts.push_back(Transaction{8.0, acc1.getId(), savingAcc1.getId()});
        transacts.push_back(Transaction{6.3, acc1.getId(), savingAcc1.getId()});
        transacts.push_back(Transaction{54.2, acc1.getId(), savingAcc1.getId()});
        transacts.push_back(Transaction{100.0, acc1.getId(), savingAcc2.getId()});
        transacts.push_back(Transaction{8.0, acc1.getId(), savingAcc2.getId()});
        transacts.push_back(Transaction{6.3, acc1.getId(), savingAcc2.getId()});
        transacts.push_back(Transaction{54.2, acc1.getId(), savingAcc2.getId()});

        for(Transaction t : transacts) {
            inheritanceBank.executeTransaction(t);
        }
        
        assert(inheritanceBank.getCustomerAccount(c1.getId(),acc1.getId())->getBalance() == 499663 && "Assertion failed: ACC1 balance is off");
        assert(inheritanceBank.getCustomerAccount(c2.getId(),savingAcc1.getId())->getBalance() == 680.786 && "Assertion failed: SavingsACC1 balance is off");
        assert(inheritanceBank.getCustomerAccount(c3.getId(),savingAcc2.getId())->getBalance() <= 10608.6);

        std::vector<Account*> accs(3);
        accs[0] = &acc1;
        accs[1] = &savingAcc1;
        accs[2] = &savingAcc2;
        for(const Account* ac : accs) {
            std::cout << *ac; 
        }
        
        // Compile time polymorphism
        assert(inheritanceBank.getCustomerAccount(c2.getId(),savingAcc1.getId())->getBalance() > 34.12);
        // Runtime polymorphism(virtual function and dynamic dispatch)
        accs[0]->printThis();
        accs[1]->printThis();


        std::cout << "[SUCCESS] All Inheritance Tests Passed!\n";
        return true;
    }
};