#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <filesystem>
#include "Globals.hpp"

class Customer {
private:
    char custID[11];
    char name[31];
    char email[31];
    char phone[15];

public:
    Customer();
    Customer(const char* custID, const char* name, const char* email, const char* phone);
    Customer(const Customer& other);
    ~Customer();

    void DisplayDetails(std::ostream& out) const;

    Customer& operator=(const Customer& other);
    bool operator==(const Customer& other) const;

    const char* getCustID() const { return custID; }
    const char* getName() const { return name; }
    const char* getEmail() const { return email; }
    const char* getPhone() const { return phone; }
};

void safeStrCopy(char* dest, const char* src, size_t maxLen);

void CommitCustomer(const Customer& customer, std::streampos& startPos, const std::string& FILENAME);
Customer GetCustomerDetails(std::streampos& startPos, const std::string& FILENAME);
void PrintAllCustomers(const std::string& FILENAME);
int ValidateCustomer(const char* name, const char* email, const char* phone);
int InitCustomer();

#endif // CUSTOMER_HPP
