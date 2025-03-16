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
    static std::fstream custs;
    static std::fstream trans;
    

    inline void initialize() {
        bankCycle++;
        accs.open("records/Accounts/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out | std::ios::trunc);
        custs.open("records/Customers/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out | std::ios::trunc);
        trans.open("records/Transactions/records.txt" + std::to_string(bankCycle), std::ios::in | std::ios::out | std::ios::trunc);
    }

    inline void close() {
        accs.close();
        custs.close();
        trans.close();
    }

    inline void writeAccs(const Account& acc) {
        bool found = false;
        std::string id = std::to_string(acc.getId());
        std::string line;
        std::vector<std::string> lines;

        accs.seekg(0, std::ios::beg);

        while(std::getline(accs,line)) {
            if(locateAccLine(line, id)) {
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

    inline void writeCust(const Customer& c) {
        bool found = false;

        std::string id = std::to_string(c.getId());
        std::string line;
        std::vector<std::string> lines;

        custs.seekg(0, std::ios::beg);

        while(std::getline(custs, line)) {
            if(locateCustLine(line, id)) {
                found = true;
                line = c.print();
            }
            lines.push_back(line);
        }

        if(!found) lines.push_back(c.print());

        custs.clear();
        custs.seekp(0, std::ios::beg);

        for(std::string& l : lines) custs << l << '\n';
        custs.flush();
    }

    inline void writeTrans(const Transaction& t) {
        std::string line = t.source + ("-" + std::to_string(t.amount)) + "->" + t.destination;
        trans << line << '\n';
        
    }

};



#endif