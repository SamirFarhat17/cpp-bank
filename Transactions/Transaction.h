#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

struct Transaction {
    const double amount;
    const int source;
    const int destination;
};

#endif
