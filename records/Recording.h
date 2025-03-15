#ifndef RECORDING_H
#define RECORDING_H

#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>

#include "../Customers/Customer.h"
#include "../Transactions/Transaction.h"
#include "../Accounts/Account.h"

namespace Recording {
    static int bankCycle = 0;

    static std::fstream accs; // static as opposed to extern to hide in translatio unit(file)
    static std::fstream cust;
    static std::fstream trans;
    
    static void initialize() {
        bankCycle++;
        accs.open("Accounts/records.txt" + std::to_string(bankCycle));
        cust.open("Accounts/records.txt" + std::to_string(bankCycle));
        trans.open("Customers/records.txt" + std::to_string(bankCycle));
    }

    static void close() {
        accs.close();
        cust.close();
        trans.close();
    }

    inline void writeAccs(const Account& acc) {

    }

    inline std::string readAccs(std::string id) {
        return "";
    }

    inline void writeCust(const Customer& c) {

    }

    inline std::string readCust(std::string id) {
        return "";
    }

    inline void writeTrans(const Transaction& trans) {

    }

    inline std::string readTrans() {
        return "";
    }

};

#endif