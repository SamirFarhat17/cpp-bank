#ifndef RECORDING_H
#define RECORDING_H

#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>

#include "../Accounts/Account.h"
#include "../Customers/Customer.h"
#include "../Transactions/Transaction.h"
#include "../Utilities/utilities.cpp"

namespace Recording {
    static int bankCycle = 0;

    static std::fstream accs; // static as opposed to extern to hide in translation unit(file)
    static std::fstream cust;
    static std::fstream trans;
    

    inline void initialize() {
        bankCycle++;
        accs.open("records/Accounts/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out | std::ios::trunc);
        cust.open("records/Customers/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out | std::ios::trunc);
        trans.open("records/Transactions/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out | std::ios::trunc);
    }

    inline void close() {
        accs.close();
        cust.close();
        trans.close();
    }

    inline void writeAccs(const Account& acc) {
        bool found = false;
        std::string id = std::to_string(acc.getId());
        std::string line;
        std::vector<std::string> lines;

        accs.seekg(0, std::ios::beg);

        while(std::getline(accs,line)) {
            if(locateAccLine(line,id)) {
                found = true;
                line = acc.print();
            }
            lines.push_back(line);
        }

        if(!found) lines.push_back(acc.print());

        accs.clear();
        accs.seekp(0, std::ios::beg);

        for(auto& l : lines) accs << l << '\n';
        accs.flush();

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