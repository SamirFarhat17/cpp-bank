#ifndef CUSTOMER_NOT_FOUND_H
#define CUSTOMER_NOT_FOUND_H

#include <exception>
#include <string>

class CustomerNotFoundException : public std::exception {
private:
    std::string msg = "customer not found";

public:
    CustomerNotFoundException() {}
    CustomerNotFoundException(std::string m) : msg(m) {}

    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};

#endif