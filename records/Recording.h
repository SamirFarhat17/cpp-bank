#ifndef RECORDING_H
#define RECORDING_H

#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>

#include "../Accounts/Account.h"
#include "../Customers/Customer.h"
#include "../Transactions/Transaction.h"

//#include "../Utilities/utilities.cpp"

namespace Recording {
    static int bankCycle = 0;

    static std::fstream accs; // static as opposed to extern to hide in translatio unit(file)
    static std::fstream cust;
    static std::fstream trans;
    
    bool locateAccLine(std::string line, std::string id) {
        if(line.empty() || line[0] != 'A') return false;
        int idx = 0;
        std::string matcher;
        while(matcher != "ACCOUNT ID: ") {
            matcher += line[idx];
            idx++;
        }
        matcher.clear();
        while(line[idx] != ' ') {
            matcher += line[idx];
            idx++;
        }
        return matcher == id;
    
    }

    static void initialize() {
        bankCycle++;
        accs.open("Accounts/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out);
        cust.open("Accounts/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out);
        trans.open("Customers/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out);
    }

    static void close() {
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
            if(locateAccLine(line,id) != std::string::npos) {
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