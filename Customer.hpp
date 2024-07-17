#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

/* Customer.hpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
----------------------------------------------------------------------
This module, Customer.hpp, hides the implementation of Customer class. 
Customer.hpp keeps its high cohesion by encapsulating all possible customer entries in the system.
----------------------------------------------------------------------*/
#include <iostream>
#include <filesystem>
#include <string>
#include "Globals.hpp"

using namespace std;

/*----------------------------------------------------------------------
Exported constants/types/variables
Types:
 - Object of Class Customer 
----------------------------------------------------------------------*/
class Customer
{
    public:
        Customer(
            const char *name, // in
                                // Name of the customer
            const char *email,// in
                                // Email of the customer
            const char *phone // in
                                // Phone number of the customer
        );
        /* Customer(string &name, string &email, int &phone) is the non-default constructor for the Customer class. It takes in details of a customer, and creates the customer object (validation also happens). CustID generation is automatic and handled by templated function T IDGenerator(string &type, int &precision) from Globals.hpp.
        ----------------------------------------------------------------------*/
        void DisplayDetails(
            ostream &out       // in/out
                               // ostream object to handle << operation
        ) const;
        /* void DisplayDetails(ostream &out) handles printing of Customer type objects. 
        The data of each customer object is properly formatted, and indented with spaces. 
        This will come handy when displaying reports or details from the UI. 
        This function will fail if the calling Customer object is a dangling pointer.
        ----------------------------------------------------------------------*/
        bool operator==(const Customer &other) const;
        friend ostream& operator<<(ostream &out, const Customer &c);
    private:
        char custID[10]; 
        char name[31];
        char email[31];
        char phone[14];
        
};
// ----------------------------------------------------------------------
int ValidateCustomer(
    const char *name,     // in
                            // Name of the customer
    const char *email,    // in
                            // Email of the customer
    const char *phone     // Phone number of the customer
    
);
/* int ValidateCustomer(const string &name, const string &email, const string &phone) is a function used for validating the inputs provided by the user i.e; Customer Support Person or a Software Developer. 
This function returns whether the user inputs are valid or not. If same data already exists in system it returns 0, if the format is invalid it returns -1 else 1. 
This function performs checks on formats of phone number, email, and name of the customer. 
Call this function with details of the user to check whether the user info is valid.
----------------------------------------------------------------------*/
Customer CreateCustomer(
    const char *name,     // in
                            // Name of the customer
    const char *email,    // in
                            // Email of the customer
    const char *phone     // in
                            // Phone number of the customer
);
/* Customer CreateCustomer(string &name, string &email, int &phone) is a function used for creating a customer object. CustID generation is automatic and handled by templated function T IDGenerator(string &type, int &precision) from Globals.hpp.
This function will be called from ScenarioControl.hpp. This function internally calls ValidateCustomer(string &name, string &email, int &phone) to check 
if details of the customer are valid. If it is invalid then it raises the following exceptions:
    - InvalidCustomerData: Customer already exists!
    or 
    - InvalidCustomerData: {field} is invalid! (where field stands for name or email or phone)
This function returns a Customer object.
----------------------------------------------------------------------*/
void CommitCustomer(
    const Customer &customer,                   // in
                                                // Customer object to be written into Customers.bin
    streampos &startPos = CUSTOMERFILEPOINTER,  // in
                                                // startPos is the position in Customers.bin for writing into the file (CUSTOMERFILEPOINTER).
    const string &FILENAME = FILENAMES[0]       // in
                                                // FILENAME is the name of the file to read from. By default it is FILENAMES[0] which is "Customers.bin"
    
);
/* void CommitCustomer(streampos &startPos, const string &FILENAME, const Customer &customer) uses the global variables streampos CHANGEFILEPOINTER, FILENAME, and a Customer object to find the location to add Customer record in Customers binary file. If file does not exist, a new one is created and a confirmation message is shown to the user. If a record already exists, a message is displayed to the user saying that the record already exists. Further, if file I/O fails, an exception is raised:
FileWriteFailed: There was an error in writing to the file.
Otherwise, the Customer object is added into the file. 
----------------------------------------------------------------------*/
Customer GetCustomerDetails(
    streampos startPos = CUSTOMERFILEPOINTER,   // in
                                                // startPos is the position in Customers.bin for reading the file (CUSTOMERFILEPOINTER).
    const string &FILENAME = FILENAMES[0]       // in
                                                // FILENAME is the name of the file to read from. By default it is FILENAMES[0] which is "Customers.bin"
); 
/* Customer GetDetails(streampos startPos, const string &FILENAME) uses the global variables streampos CUSTOMERFILEPOINTER and FILENAME to find the location to read records from. 
It reads the information to create a customer object. 
This function will work only if there is atleast 1 record of a customer in the binary file else an exception will be raised:
    FileReadFailed: There was an error in reading the file.
----------------------------------------------------------------------*/
int InitCustomer(){
    filesystem::create_directory(DIRECTORY);
    if (!filesystem::exists(DIRECTORY + FILENAMES[0]))
    {
        ofstream file(DIRECTORY + FILENAMES[0], ios::binary);
        if (!file)
        {
            return -1;
        } else
        {
            return 1;
        } 
        file.close();
    } 
    else
    {
        return 0;
    }
    return -1;
}
/* int InitCustomer() uses the global variables streampos CUSTOMERFILEPOINTER and FILENAMES[0] to check if binary file "Customers.bin" exist in the DIRECTORY to essentially check if the program is being run for the first time. If it does, then it returns 0, if it doesn't then the file is created. If file was created successfully, it returns 1 else -1. The function does not fail.
----------------------------------------------------------------------*/
#endif