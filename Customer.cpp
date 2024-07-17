#include "drivers.cpp"
#include "Customer.hpp"
#include "Globals.cpp"
#include <cstring>
#include <iostream>

using namespace std;

Customer::Customer(const char *name = "", const char *email = "", const char *phone = "")
{ // using a dummy ID
    const char *generatedID = IDGenerator('1', 10);
    strcpy(this->custID, generatedID);
    this->custID[sizeof(this->custID) - 1] = '\0';
    strcpy(this->name, name);
    this->name[sizeof(this->name) - 1] = '\0';
    strcpy(this->email, email);
    this->email[sizeof(this->email) - 1] = '\0';
    strcpy(this->phone, phone);
    this->phone[sizeof(this->phone) - 1] = '\0';
}

/*
Create Customer object using attrbibutes provided. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
bool Customer::operator==(const Customer &other) const{
    return (custID == other.custID || email == other.email || phone == other.phone);
}

/*
Checks if two Customer objects are equal based on custID or email or phone. 
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
bool Customer::operator==(const char *userID) const{
    return (custID == userID);
}

/*
Checks if a Customer object is equal to a given userID string.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
ostream& operator<< (ostream &out, const Customer &c){
    c.DisplayDetails(out);
    return out;
}

/*
Overload the Customer class and outputs the details of Customer object and returns output stream
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void Customer::DisplayDetails(ostream &out) const
{
    if (strlen(name) == 0 || strlen(email) == 0 || strlen(phone) == 0)
        out << "Error in reading Customer information. One or more attributes of customer do not have value(s)" << endl;
    // RAISE ERROR
    // exit(1);
    else
    {
        cout.width(32); cout << left << name;
        cout.width(24); cout << left << email << endl;
    }
}

/*
Print the attribute details of the Customer object to the console.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
Customer CreateCustomer(const char *name, const char *email, const char *phone)
{
    cout << ValidateCustomer(name, email, phone) << endl;

    if (ValidateCustomer(name, email, phone) == 1)
    {
        Customer newCust(name, email, phone);
        return newCust;
    }
    else
    {
        // RAISE EXCEPTION
        cout << "Could not create a new customer!" << endl;
    }
}

/*
Create new Customer object and also validates it.
No noticeable algorithm or data structure used.
--------------------------------------------------------------------*/
void CommitCustomer(const Customer &customer, streampos &startPos, const string &FILENAME)
{
    writeRecord(FILENAME, startPos, customer);
}

/*
Writes a Customer object to a specified file at a given position.
Uses the unsorted records data structure to add the Complaint object.
--------------------------------------------------------------------*/
Customer GetCustomerDetails(streampos &startPos, const string &FILENAME)
{
    Customer newCust = readRecord<Customer>(FILENAME, startPos);
    return newCust;
}

/*
Reads a Customer object from a specified file at a given position and returns it.
Uses the unsorted records data structure to read the Customer object.
--------------------------------------------------------------------*/
int ValidateCustomer(const char *name, const char *email, const char *phone)
{

    if (email == nullptr || *email == '\0' || name == nullptr || *name == '\0' || phone == nullptr || *phone == '\0')
        return -1;
    else
    {
        // validate email
        const char *atSign = strchr(email, '@');
        if (atSign == nullptr)
            return -1;
        const char *dotSign = strchr(atSign, '.');
        if (dotSign == nullptr)
            return -1;
        if (atSign == email || !isalpha(email[0]))
            return -1;
        if (dotSign == atSign + 1 || dotSign == atSign + 2 || *(dotSign + 1) == '\0')
            return -1;
        for (const char *p = email; p < atSign; ++p)
        {
            if (!std::isalnum(*p) && *p != '.' && *p != '-' && *p != '_')
            
            {
                cout << "Invalid character found in email" << endl;

                return -1; // Invalid character found
            }
        }

        // Check for invalid characters in the domain part (after '@')
        for (const char *p = atSign + 1; p < dotSign; ++p)
        {
            if (!std::isalnum(*p) && *p != '-' && *p != '_')
            {
                cout << "Invalid character found in email" << endl;
                return -1; // Invalid character found
            }
        }

        // validate phone num
        if (phone[0] != '1' || phone[1] != ' ' || !isdigit(phone[2]) || !isdigit(phone[3]) || !isdigit(phone[4]) || phone[5] != '-'|| !isdigit(phone[6]) || !isdigit(phone[7]) || !isdigit(phone[8]) || phone[9] != '-'|| !isdigit(phone[10]) || !isdigit(phone[11]) || !isdigit(phone[12]) ||!isdigit(phone[13]))
            {
                cout << "Invalid character found in phone" << endl;

                return -1;
            }
        
    }

    // check if record already exists
    Customer *dataptr = readFile<Customer>(FILENAMES[0], CUSTOMERFILEPOINTER);
    Customer dummy(name, email, phone);

    size_t size = sizeof(dataptr) / sizeof(dataptr[0]);
    for (int i = 0; i < size; i++)
    {
        if (dataptr[i] == dummy)
        {
            delete [] dataptr;
            cout << "Record already exists :/" << endl;
            return 0;
            // break;
        }
    }
    delete [] dataptr;
    cout << "Record is valid!" << endl;
    return 1;
}

/*
Validates that the Customer object attributes are acceptable and makes sure no duplicate Customer records exists.
A linear search algorithm is used to iterate through the Customer records.
--------------------------------------------------------------------*/