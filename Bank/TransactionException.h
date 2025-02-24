#ifndef TRANSACTIONEXCEPTION_H
#define TRANSACTIONEXCEPTION_H

#include <exception>
#include <string>

class TransactionException : public std::exception {
private:
    std::string message;

public:
    explicit TransactionException(const std::string& msg) : message(msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif
