#include "Customer.hpp"
#include "Globals.hpp"
#include "drivers.cpp"
#include<cstring>
#include<iostream>

using namespace std;

Customer::Customer(const char* name, const char *email, const char *phone): Record<const char *>(IDGenerator<const char*>('1', 9)){ // using a dummy ID
    strcpy(this->name, name);
    this->name[sizeof(this->name) - 1] = '\0';
    strcpy(this->email, email);
    this->email[sizeof(this->email) - 1] = '\0';
    strcpy(this->phone, phone);
    this->phone[sizeof(this->phone) - 1] = '\0';
}

void Customer::DisplayDetails(ostream &out) const{
    if (strlen(name) == 0 || strlen(email) == 0 || strlen(phone) == 0)
        out << "Error in reading Customer information. One or more attributes of customer do not have value(s)" << endl;
        // RAISE ERROR
        // exit(1);
    else{
        out << "CustID: " << getId() << endl;
        out << "name: " << name << endl;
        out << "email: " << email << endl;
        out << "phone: " << phone << endl;
    }
}


Customer CreateCustomer(const char* name, const char *email, const char *phone){

    if (ValidateCustomer(name, email, phone)){
        Customer newCust(name, email, phone);
        return newCust;
    }
    else{
        // RAISE EXCEPTION
        cout << "Could not create a new customer!" << endl;
    }
}

void CommitCustomer(const Customer &customer, streampos &startPos = CUSTOMERFILEPOINTER, const string &FILENAME = FILENAMES[0]){
    writeFile(FILENAME, startPos, customer);
}

Customer GetCustomerDetails(const streampos startpos = CUSTOMERFILEPOINTER, const string &FILENAME = FILENAMES[0]){
    Customer newCust = readFile(FILENAME, startPos);
}