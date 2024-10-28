#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

/* Customer.hpp
REVISION HISTORY:
Rev. 2 - 24/07/16 Added another class operator by Jason Lee
Rev. 1 - 24/07/03 Original by Sanchit Jain
----------------------------------------------------------------------
This module, Customer.hpp, hides the implementation of Customer class.
Customer.hpp keeps its high cohesion by encapsulating all possible customer entries in the system.
----------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <filesystem>

#include "drivers.hpp"
#include "Exceptions.hpp"
#include "Globals.hpp"

/*----------------------------------------------------------------------
Exported constants/types/variables
Types:
 - Object of Class Customer
----------------------------------------------------------------------*/

class Customer
{
public:

    /*
    Customer() is the default constructor for the Customer class. It initializes all member variables to their default values.
    ----------------------------------------------------------------------*/
    Customer(

    );
    /* 
    Customer(const char *custID, const char *name, const char *email, const char *phone) is the non-default constructor for the Customer class. 
    It takes in details of a customer, and creates the customer object. custID if passed takes in the value 
    otherwise creates a random ID of type C-string handled by const char* IDGenerator(const char &type, const int &precision) from Globals.hpp.
    ----------------------------------------------------------------------*/   
    Customer(
        const char *custID, // in: Unique ID of customer
        const char *name,   // in: Name of customer
        const char *email,  // in: Email of customer
        const char *phone   // in: Phone number of customer
    );
    /* 
    Customer(const Customer &other) is the copy constructor for the Customer class. 
    It takes in a customer object and makes a deep copy of it using an overloaded assignment operator function.
    ----------------------------------------------------------------------*/ 
    Customer(
        const Customer &other   // in: Other customer object to copy from
    );
    /* 
    ~Customer() is the destructor for the class and does not have anything in it since nothing has been assigned/created on the heap memory.
    ----------------------------------------------------------------------*/
    ~Customer(
    
    );
    /* 
    void DisplayDetails(std::ostream& out) const is a helper function to display details of a Customer object using << operator.
    It fails to show the required output if any of the member variables/C-strings have only null-character in them.
    ----------------------------------------------------------------------*/
    void DisplayDetails(
        std::ostream &out       // inout: ostream object to handle calling with << operator
    ) const;
    /* 
    Customer& operator=(const Customer& other) is an = operator overloader function that deeply assigns the contents of one Customer object to another. 
    It fails or provides no recognizable output if the memory address of the calling object is same as the object at the RHS.
    ----------------------------------------------------------------------*/
    Customer &operator=(
        const Customer &other   // in: Other customer object to assign from
    );
    /* 
    bool operator==(const Customer &other) is an == comparison operator overloader function that compares the calling object with another Customer object.
    ----------------------------------------------------------------------*/
    bool operator==(
        const Customer &other   // in: Other customer object to compare to
    ) const;
   
    // returns ID of customer
    const char *getCustID() const {return custID; }
    
    // returns name of customer
    const char *getName() const {return name; }
    
    // returns email of customer
    const char *getEmail() const {return email; }
    
    // returns phone number of customer
    const char *getPhone() const {return phone; }
    
private:

    char custID[10]; // in: Unique ID of customer
    char name[31];   // in: Name of customer
    char email[31];  // in: Email of customer
    char phone[12];  // in: Phone number of customer
};

/* 
Customer CreateCustomer(const char *name, const char *email, const char *phone) takes in details of the customer, 
checks if input is valid by calling ValidateCustomer and returns a customer object. If the input is invalid, a message is displayed.
----------------------------------------------------------------------*/
Customer CreateCustomer(
    const char *name,  // in: name of the customer
    const char *email, // in: email of the customer
    const char *phone  // in: phone number of the customer
);
/* 
void CommitCustomer(const Customer &customer, std::startpos &startPos, const std::string &FILENAME) 
takes in a customer object, file pointer, and name of file and adds a record in the binary file. 
This function fails if there is an error in writing to the file.
----------------------------------------------------------------------*/
void CommitCustomer(
    const Customer &customer,   // in: Customer to add in binary file
    std::streampos &startPos,   // inout: File pointer of the binary file
    const std::string &FILENAME // in: Location-name of file
);
/* 
Customer GetCustomerDetails(std::streampos &startPos, const std::string &FILENAME) takes in a file pointer, 
reads the file and returns the record at startPos by converting to Customer object. 
This function fails if there is an error in reading the file or casting information.
----------------------------------------------------------------------*/
Customer GetCustomerDetails(
    std::streampos &startPos,   // in: File pointer of the binary file
    const std::string &FILENAME // in: Location-name of file
);
/* 
void PrintAllCustomers(const std::string &FILENAME) takes in location of binary file and prints all records in a tabulated form. 
This function fails if there is an error in reading the file or casting information.
----------------------------------------------------------------------*/
void PrintAllCustomers(
    const std::string &FILENAME // in: Location-name of file
);
/* 
int ValidateCustomer(const char *name, const char *email, const char *phone) is a function used for validating the inputs provided by the user i.e; Customer Support Person or a Software Developer. 
This function returns whether the user inputs are valid or not. If same data already exists in system it returns 0, if the format is invalid it returns -1 else 1. 
This function performs checks on formats of phone number, email, and name of the customer. 
Call this function with details of the user to check whether the user info is valid.
----------------------------------------------------------------------*/
int ValidateCustomer(
    const char *name,   // in: Name of customer
    const char *email,  // in: Email of customer
    const char *phone   // in: Phone number of customer
);

bool checkDup(const char *otherCustID);
/* 
int InitCustomer() uses the global variables streampos CUSTOMERFILEPOINTER and FILENAMES[0] to check if binary file "Customers.bin" exist in the DIRECTORY 
to essentially check if the program is being run for the first time. If it does, then it returns 0, if it doesn't then the file is created. 
If file was created successfully, it returns 1 else -1. The function does not fail.
----------------------------------------------------------------------*/
int InitCustomer();

#endif // CUSTOMER_HPP
